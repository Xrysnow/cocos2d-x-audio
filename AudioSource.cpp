﻿#include "AudioSource.h"
#include "AudioSoundData.h"
#include "AudioDecoder.h"
#include "AudioEngine.h"
#include "AudioFilter.h"

using namespace audio;

constexpr double PI = 3.14159265358979323846;
constexpr double TORAD_ = PI / 180.0;
constexpr double TODEG_ = 180.0 / PI;
#define TORAD(x)	(float)(x*TORAD_)
#define TODEG(x)	(float)(x*TODEG_)

StaticDataBuffer::StaticDataBuffer(ALenum format, const ALvoid *data, ALsizei size, ALsizei freq)
	: buffer(0), size(size)
{
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, data, size, freq);
}

StaticDataBuffer::~StaticDataBuffer()
{
	alDeleteBuffers(1, &buffer);
}

Source::Source()
{
}

bool Source::initWithSoundData(SoundData* soundData)
{
	sourceType = Type::STATIC;
	pool = Pool::getInstance();
	if (!pool)
		return false;
	sampleRate = soundData->getSampleRate();
	channels = soundData->getChannelCount();
	bitDepth = soundData->getBitDepth();
	const auto fmt = Engine::getFormat(soundData->getBitDepth(), soundData->getChannelCount());
	if (fmt == AL_NONE)
	{
		InvalidFormatException(soundData->getChannelCount(), soundData->getBitDepth());
		return false;
	}

	staticBuffer = new (std::nothrow) StaticDataBuffer(fmt, soundData->getData(), (ALsizei)soundData->getSize(), sampleRate);
	if (!staticBuffer)
		return false;
	staticBuffer->autorelease();
	staticBuffer->retain();

	position.setZero();
	velocity.setZero();
	direction.setZero();

	for (int i = 0; i < Engine::getMaxSourceEffectCount(); i++)
		slotlist.push(i);
	return true;
}

bool Source::initWithDecoder(Decoder* _decoder)
{
	sourceType = Type::STREAM;
	pool = Pool::getInstance();
	if (!pool)
	{
		AINFO("failed for pool");
		return false;
	}
	decoder = _decoder;
	if (decoder)
		decoder->retain();
	else
	{
		AINFO("failed for decoder");
		return false;
	}
	sampleRate = decoder->getSampleRate();
	channels = decoder->getChannelCount();
	bitDepth = decoder->getBitDepth();
	buffers = DEFAULT_BUFFERS;
	if (Engine::getFormat(decoder->getBitDepth(), decoder->getChannelCount()) == AL_NONE)
	{
		AINFO("failed for format");
		InvalidFormatException(decoder->getChannelCount(), decoder->getBitDepth());
		return false;
	}

	for (int i = 0; i < buffers; i++)
	{
		ALuint buf;
		alGenBuffers(1, &buf);
		if (alGetError() == AL_NO_ERROR)
			unusedBuffers.push(buf);
		else
		{
			buffers = i;
			break;
		}
	}

	position.setZero();
	velocity.setZero();
	direction.setZero();

	for (int i = 0; i < Engine::getMaxSourceEffectCount(); i++)
		slotlist.push(i);
	return true;
}

bool Source::init(int _sampleRate, int _bitDepth, int _channels, int _buffers)
{
	sourceType = Type::QUEUE;
	pool = Pool::getInstance();
	if (!pool)
		return false;
	sampleRate = _sampleRate;
	channels = _channels;
	bitDepth = _bitDepth;
	buffers = _buffers;
	ALenum fmt = Engine::getFormat(bitDepth, channels);
	if (fmt == AL_NONE)
	{
		InvalidFormatException(channels, bitDepth);
		return false;
	}

	if (buffers < 1)
		buffers = DEFAULT_BUFFERS;
	if (buffers > MAX_BUFFERS)
		buffers = MAX_BUFFERS;

	for (int i = 0; i < buffers; i++)
	{
		ALuint buf;
		alGenBuffers(1, &buf);
		if (alGetError() == AL_NO_ERROR)
			unusedBuffers.push(buf);
		else
		{
			buffers = i;
			break;
		}
	}

	position.setZero();
	velocity.setZero();
	direction.setZero();

	for (int i = 0; i < Engine::getMaxSourceEffectCount(); i++)
		slotlist.push(i);
	return true;
}

bool Source::initWithOther(const Source &s)
{
	sourceType = s.sourceType;
	pool = s.pool;
	valid = false;
	staticBuffer = s.staticBuffer;
	pitch = s.pitch;
	volume = s.volume;
	relative = s.relative;
	looping = s.looping;
	minVolume = s.minVolume;
	maxVolume = s.maxVolume;
	referenceDistance = s.referenceDistance;
	rolloffFactor = s.rolloffFactor;
	maxDistance = s.maxDistance;
	cone = s.cone;
	offsetSamples = 0;
	sampleRate = s.sampleRate;
	channels = s.channels;
	bitDepth = s.bitDepth;
	decoder = nullptr;
	toLoop = 0;
	buffers = s.buffers;

	if (staticBuffer)
		staticBuffer->retain();
	if (sourceType == Type::STREAM)
	{
		if (s.decoder)
			decoder = s.decoder->clone();
		if (decoder)
			decoder->retain();
	}
	if (sourceType != Type::STATIC)
	{
		for (int i = 0; i < buffers; i++)
		{
			ALuint buf;
			alGenBuffers(1, &buf);
			if (alGetError() == AL_NO_ERROR)
				unusedBuffers.push(buf);
			else
			{
				buffers = i;
				break;
			}
		}
	}

	if (s.directfilter)
		directfilter = s.directfilter->clone();

	for (auto e : s.effectmap)
	{
		Filter *filter = e.second.filter ? e.second.filter->clone() : nullptr;
		effectmap[e.first] = { filter, e.second.slot, e.second.target };
	}

	position.setZero();
	velocity.setZero();
	direction.setZero();

	for (int i = 0; i < Engine::getMaxSourceEffectCount(); i++)
	{
		// filter out already taken slots
		bool push = true;
		for (auto& e : effectmap)
		{
			if (e.second.slot)
			{
				push = false;
				break;
			}
		}
		if (push)
			slotlist.push(i);
	}
	return true;
}

Source::~Source()
{
	Source::stop();

	if (sourceType != Type::STATIC)
	{
		while (!streamBuffers.empty())
		{
			alDeleteBuffers(1, &streamBuffers.front());
			streamBuffers.pop();
		}
		while (!unusedBuffers.empty())
		{
			alDeleteBuffers(1, &unusedBuffers.top());
			unusedBuffers.pop();
		}
	}

	delete directfilter;
	for (auto& e : effectmap)
		delete e.second.filter;
	if (staticBuffer)
		staticBuffer->release();
	if (decoder)
		decoder->release();
}

Source* Source::createFromSoundData(SoundData* soundData)
{
	auto ret = new (std::nothrow) Source();
	if (ret&&ret->initWithSoundData(soundData))
	{
		ret->autorelease();
		return ret;
	}
	return nullptr;
}

Source* Source::createFromDecoder(Decoder* decoder)
{
	auto ret = new (std::nothrow) Source();
	if (ret&&ret->initWithDecoder(decoder))
	{
		ret->autorelease();
		return ret;
	}
	return nullptr;
}

Source* Source::create(int sampleRate, int bitDepth, int channels, int buffers)
{
	auto ret = new (std::nothrow) Source();
	if (ret&&ret->init(sampleRate, bitDepth, channels, buffers))
	{
		ret->autorelease();
		return ret;
	}
	return nullptr;
}

Source *Source::clone()
{
	auto ret = new (std::nothrow) Source();
	if (ret&&ret->initWithOther(*this))
	{
		ret->autorelease();
		return ret;
	}
	return nullptr;
}

bool Source::play()
{
	auto l = pool->lock();
	ALuint out;
	char wasPlaying;
	if (!pool->assignSource(this, out, wasPlaying))
		return valid = false;
	if (!wasPlaying)
		return valid = playAtomic(out);
	resumeAtomic();
	return valid = true;
}

void Source::stop()
{
	auto l = pool->lock();
	if (!valid)
		return;
	releaseSource();
}

void Source::pause()
{
	if (pool->isPlaying(this)) // lock in isPlaying
		pauseAtomic();
}

bool Source::isPlaying() const
{
	if (!valid)
		return false;

	ALenum state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

bool Source::isFinished() const
{
	if (!valid)
		return false;

	if (sourceType == Type::STREAM && (isLooping() || !decoder->isFinished()))
		return false;

	ALenum state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	return state == AL_STOPPED;
}

bool Source::update()
{
	if (!valid)
		return false;

	switch (sourceType)
	{
	case Type::STATIC:
	{
		// Looping mode could have changed.
		// FIXME: make looping mode change atomically so this is not needed
		alSourcei(source, AL_LOOPING, isLooping() ? AL_TRUE : AL_FALSE);
		return !isFinished();
	}
	case Type::STREAM:
		if (!isFinished())
		{
/*
			ALint processed;
			ALuint buffers[MAX_BUFFERS];
			ALint curOffsetSamples, newOffsetSamples;
			const auto freq = decoder->getSampleRate();

			alGetSourcei(source, AL_SAMPLE_OFFSET, &curOffsetSamples);
			const double curOffsetSecs = (double)curOffsetSamples / freq;

			alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
			alSourceUnqueueBuffers(source, processed, buffers);

			alGetSourcei(source, AL_SAMPLE_OFFSET, &newOffsetSamples);
			const double newOffsetSecs = (double)newOffsetSamples / freq;

			offsetSamples += curOffsetSamples - newOffsetSamples;
			offsetSeconds += curOffsetSecs - newOffsetSecs;

			for (int i = 0; i < processed; i++)
				unusedBuffers.push(buffers[i]);
*/
			ALint processed;
			alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

			// It would theoretically be better to unqueue all processed
			// buffers in a single call to alSourceUnqueueBuffers, but on
			// iOS I observed occasional (every ~5-10 seconds) pops in the
			// streaming source test I was using, when doing that. Perhaps
			// there was a bug in this code when I was testing, or maybe
			// this code runs into the same problem but now it's much harder
			// to reproduce. The test I used is the play-stop-play .love
			// from https://bitbucket.org/rude/love/issues/1484/
			while (processed--)
			{
				int curOffsetSamples;
				alGetSourcei(source, AL_SAMPLE_OFFSET, &curOffsetSamples);

				ALuint buffer;
				alSourceUnqueueBuffers(source, 1, &buffer);

				int newOffsetSamples;
				alGetSourcei(source, AL_SAMPLE_OFFSET, &newOffsetSamples);

				offsetSamples += (curOffsetSamples - newOffsetSamples);

				if (streamAtomic(buffer, decoder) > 0)
					alSourceQueueBuffers(source, 1, &buffer);
				else
					unusedBuffers.push(buffer);
			}

			while (!unusedBuffers.empty())
			{
				auto b = unusedBuffers.top();
				if (streamAtomic(b, decoder) > 0)
				{
					alSourceQueueBuffers(source, 1, &b);
					unusedBuffers.pop();
				}
				else
					break;
			}
			return true;
		}
		return false;
	case Type::QUEUE:
	{
		ALint processed;
		ALuint buffers[MAX_BUFFERS];

		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
		alSourceUnqueueBuffers(source, processed, buffers);

		for (int i = 0; i < processed; i++)
		{
			ALint size;
			alGetBufferi(buffers[i], AL_SIZE, &size);
			bufferedBytes -= size;
			unusedBuffers.push(buffers[i]);
		}
		return !isFinished();
	}
	case Type::MAX_ENUM:
		break;
	}

	return false;
}

void Source::setPitch(float value)
{
	value = std::max(0.5f, std::min(value, 2.0f));
	if (valid)
		alSourcef(source, AL_PITCH, value);
	pitch = value;
}

float Source::getPitch() const
{
	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_PITCH, &f);
		return f;
	}
	// In case the Source isn't playing.
	return pitch;
}

void Source::setVolume(float value)
{
	value = std::max(0.f, value);
	if (valid)
		alSourcef(source, AL_GAIN, value);
	volume = value;
}

float Source::getVolume() const
{
	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_GAIN, &f);
		return f;
	}
	// In case the Source isn't playing.
	return volume;
}

void Source::seek(int64_t offset)
{
	auto l = pool->lock();
	auto offsetSamples = offset;
	//double offsetSeconds = (double)offset / sampleRate;
	const bool wasPlaying = isPlaying();
	switch (sourceType)
	{
	case Type::STATIC:
		if (valid)
		{
			alSourcei(source, AL_SAMPLE_OFFSET, offsetSamples);
			offsetSamples = 0;
		}
		break;
	case Type::STREAM:
		{
			// To drain all buffers
			if (valid)
				releaseSource();

			decoder->seek(offsetSamples);

			if (wasPlaying)
			{
				//play();
				ALuint out;
				char wasPlaying_;
				if (!pool->assignSource(this, out, wasPlaying_))
					valid = false;
				else if (!wasPlaying_)
					valid = playAtomic(out);
				else
				{					
					resumeAtomic();
					valid = true;
				}
			}

			break;
		}
	case Type::QUEUE:
		if (valid)
		{
			alSourcei(source, AL_SAMPLE_OFFSET, offsetSamples);
			offsetSamples = 0;
		}
		else
		{
			//emulate AL behavior, discarding buffer once playback head is past one
			while (!unusedBuffers.empty())
			{
				ALint size;
				const auto buffer = unusedBuffers.top();
				alGetBufferi(buffer, AL_SIZE, &size);

				const int bytesPerFrame = bitDepth / 8 * channels;
				if (offsetSamples < size / bytesPerFrame)
					break;

				unusedBuffers.pop();
				bufferedBytes -= size;
				offsetSamples -= size / bytesPerFrame;
			}
			if (unusedBuffers.empty())
				offsetSamples = 0;
			//offsetSeconds = (double)offsetSamples / sampleRate;
		}
		break;
	case Type::MAX_ENUM:
	default:
		break;
	}

	if (wasPlaying && (alGetError() == AL_INVALID_VALUE || sourceType == Type::STREAM && !isPlaying()))
	{
		releaseSource();
		if (isLooping())
		{
			//play();
			ALuint out;
			char wasPlaying_;
			if (!pool->assignSource(this, out, wasPlaying_))
				valid = false;
			else if (!wasPlaying_)
				valid = playAtomic(out);
			else
			{
				resumeAtomic();
				valid = true;
			}
		}
		return;
	}
	this->offsetSamples = offsetSamples;
}

int64_t Source::tell()
{
	auto l = pool->lock();

	ALint offset = 0;
	if (valid)
		alGetSourcei(source, AL_SAMPLE_OFFSET, &offset);
	offset += offsetSamples;
	return offset;
}

int64_t Source::getTotalFrames()
{
	auto l = pool->lock();

	switch (sourceType)
	{
	case Type::STATIC:
	{
		const ALsizei size = staticBuffer->getSize();
		const ALsizei samples = size / channels / (bitDepth / 8);
		return (int64_t)samples;
	}
	case Type::STREAM:
	{
		return decoder->getTotalFrames();
	}
	case Type::QUEUE:
	{
		const ALsizei samples = bufferedBytes / channels / (bitDepth / 8);
		return (int64_t)samples;
	}
	case Type::MAX_ENUM:
	default:
		return 0;
	}
}

void Source::setTime(double seconds)
{
	seek(seconds*sampleRate);
}

double Source::getTime()
{
	return (double)tell() / sampleRate;
}

double Source::getTotalTime()
{
	return (double)getTotalFrames() / sampleRate;
}

void Source::setPosition(const cocos2d::Vec3& v)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcefv(source, AL_POSITION, (float*)&v);

	position = v;
}

cocos2d::Vec3 Source::getPosition()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return {};
	}

	auto v = position;
	if (valid)
		alGetSourcefv(source, AL_POSITION, (float*)&v);
	return v;
}

void Source::setVelocity(const cocos2d::Vec3& v)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcefv(source, AL_VELOCITY, (float*)&v);

	velocity = v;
}

cocos2d::Vec3 Source::getVelocity()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return {};
	}

	auto v = position;
	if (valid)
		alGetSourcefv(source, AL_VELOCITY, (float*)&v);
	return v;
}

void Source::setDirection(const cocos2d::Vec3& v)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcefv(source, AL_DIRECTION, (float*)&v);
	else
		direction = v;
}

cocos2d::Vec3 Source::getDirection()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return {};
	}

	auto v = position;
	if (valid)
		alGetSourcefv(source, AL_DIRECTION, (float*)&v);
	return v;
}

void Source::setCone(float innerAngle, float outerAngle, float outerVolume, float outerHighGain)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	cone.innerAngle = (int)TODEG(innerAngle);
	cone.outerAngle = (int)TODEG(outerAngle);
	cone.outerVolume = outerVolume;
	cone.outerHighGain = outerHighGain;

	if (valid)
	{
		alSourcei(source, AL_CONE_INNER_ANGLE, cone.innerAngle);
		alSourcei(source, AL_CONE_OUTER_ANGLE, cone.outerAngle);
		alSourcef(source, AL_CONE_OUTER_GAIN, cone.outerVolume);
#ifdef ALC_EXT_EFX
		alSourcef(source, AL_CONE_OUTER_GAINHF, cone.outerHighGain);
#endif
	}
}

void Source::setCone(const std::array<float, 4>& param)
{
	setCone(param[0], param[1], param[2], param[3]);
}

std::array<float, 4> Source::getCone()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return {};
	}
	return {
		CC_DEGREES_TO_RADIANS(cone.innerAngle),
		CC_DEGREES_TO_RADIANS(cone.outerAngle),
		cone.outerVolume,
		cone.outerHighGain };
}

void Source::setRelative(bool enable)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcei(source, AL_SOURCE_RELATIVE, enable ? AL_TRUE : AL_FALSE);

	relative = enable;
}

bool Source::isRelative()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return false;
	}

	return relative;
}

void Source::setLooping(bool enable)
{
	if (sourceType == Type::QUEUE)
	{
		QueueLoopingException();
		return;
	}

	if (valid && sourceType == Type::STATIC)
		alSourcei(source, AL_LOOPING, enable ? AL_TRUE : AL_FALSE);

	looping = enable;
}

bool Source::isLooping() const
{
	return looping;
}

void Source::setLoopingPoint(double tStart, double tEnd)
{
	if (sourceType == Type::STREAM)
		decoder->setLoopingPoint(tStart, tEnd);
}

bool Source::isSupportLoopingPoint() const
{
	return sourceType == Type::STREAM;
}

double Source::getLoopingStart() const
{
	if (sourceType == Type::STREAM)
		return decoder->getLoopingStart();
	return 0.0;
}

double Source::getLoopingEnd() const
{
	if (sourceType == Type::STREAM)
		return decoder->getLoopingEnd();
	return 0.0;
}

bool Source::queueData(void *data, size_t length, int dataSampleRate, int dataBitDepth, int dataChannels)
{
	auto l = pool->lock();

	if (sourceType != Type::QUEUE)
	{
		QueueTypeMismatchException();
		return false;
	}

	if (dataSampleRate != sampleRate || dataBitDepth != bitDepth || dataChannels != channels)
	{
		QueueFormatMismatchException();
		return false;
	}

	if (length % (bitDepth / 8 * channels) != 0)
	{
		QueueMalformedLengthException(bitDepth / 8 * channels);
		return false;
	}

	if (length == 0)
		return true;

	if (unusedBuffers.empty())
		return false;

	auto buffer = unusedBuffers.top();
	unusedBuffers.pop();
	alBufferData(buffer, Engine::getFormat(bitDepth, channels), data, length, sampleRate);
	bufferedBytes += length;

	if (valid)
		alSourceQueueBuffers(source, 1, &buffer);
	else
		streamBuffers.push(buffer);

	return true;
}

bool Source::queue(SoundData* data, ssize_t offset, ssize_t length)
{
	if (offset < 0)
		offset = 0;
	const auto r = (ssize_t)data->getSize() - offset;
	if (length < 0 || length > r)
		length = r;
	return queueData((unsigned char*)data->getData() + offset, length,
		data->getSampleRate(), data->getBitDepth(), data->getChannelCount());
}

int Source::getFreeBufferCount() const
{
	switch (sourceType) //why not :^)
	{
	case Type::STATIC:
		return 0;
	case Type::STREAM:
		return unusedBuffers.size();
	case Type::QUEUE:
		return unusedBuffers.size();
	case Type::MAX_ENUM:
		return 0;
	}
	return 0;
}

void Source::prepareAtomic()
{
	// This Source may now be associated with an OpenAL source that still has
	// the properties of another love Source. Let's reset it to the settings
	// of the new one.
	reset();

	switch (sourceType)
	{
	case Type::STATIC:
		alSourcei(source, AL_BUFFER, staticBuffer->getBuffer());
		break;
	case Type::STREAM:
		while (!unusedBuffers.empty())
		{
			auto b = unusedBuffers.top();
			if (streamAtomic(b, decoder) == 0)
				break;

			alSourceQueueBuffers(source, 1, &b);
			unusedBuffers.pop();

			if (decoder->isFinished())
				break;
		}
		break;
	case Type::QUEUE:
	{
		while (!streamBuffers.empty())
		{
			alSourceQueueBuffers(source, 1, &streamBuffers.front());
			streamBuffers.pop();
		}
		break;
	}
	case Type::MAX_ENUM:
		break;
	}
	// Seek to the current/pending offset.
	alSourcei(source, AL_SAMPLE_OFFSET, offsetSamples);
}

void Source::teardownAtomic()
{
	switch (sourceType)
	{
	case Type::STATIC:
		break;
	case Type::STREAM:
	{
/*
		ALint queued;
		ALuint buffer;
		decoder->seek(0);
		// drain buffers
		//since we only unqueue 1 buffer, it's OK to use singular variable pointer instead of array
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		for (unsigned int i = 0; i < (unsigned int)queued; i++)
		{
			alSourceUnqueueBuffers(source, 1, &buffer);
			unusedBuffers.push(buffer);
		}
*/
		ALint queued = 0;
		ALuint buffers[MAX_BUFFERS];
		decoder->seek(0);
		// Drain buffers.
		// NOTE: The Apple implementation of OpenAL on iOS doesn't return
		// correct buffer ids for single alSourceUnqueueBuffers calls past the
		// first queued buffer, so we must unqueue them all at once.
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		alSourceUnqueueBuffers(source, queued, buffers);
		for (int i = 0; i < queued; i++)
			unusedBuffers.push(buffers[i]);
		break;
	}
	case Type::QUEUE:
	{
/*
		ALint queued;
		ALuint buffer;
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		for (auto i = queued; i > 0; i--)
		{
			alSourceUnqueueBuffers(source, 1, &buffer);
			unusedBuffers.push(buffer);
		}
*/
		ALint queued;
		ALuint buffers[MAX_BUFFERS];
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		alSourceUnqueueBuffers(source, queued, buffers);
		for (int i = 0; i < queued; i++)
			unusedBuffers.push(buffers[i]);
		break;
	}
	case Type::MAX_ENUM:
		break;
	}

	alSourcei(source, AL_BUFFER, AL_NONE);

	toLoop = 0;
	valid = false;
	offsetSamples = 0;
}

bool Source::playAtomic(ALuint source)
{
	this->source = source;
	prepareAtomic();

	// Clear errors.
	alGetError();

	alSourcePlay(source);

	bool success = alGetError() == AL_NO_ERROR;

	if (sourceType == Type::STREAM)
	{
		valid = true; //isPlaying() needs source to be valid
		if (!isPlaying())
			success = false;
	}
	//else if (success)
	//{
	//	alSourcei(source, AL_SAMPLE_OFFSET, offsetSamples);
	//	success = alGetError() == AL_NO_ERROR;
	//}

	if (!success)
	{
		//valid = true; //stop() needs source to be valid
		releaseSource();
	}
	// Static sources: reset the pending offset since it's not valid anymore.
	if (sourceType != Type::STREAM)
		offsetSamples = 0;

	return success;
}

void Source::stopAtomic()
{
	if (!valid)
		return;
	alSourceStop(source);
	teardownAtomic();
}

void Source::pauseAtomic()
{
	if (valid)
		alSourcePause(source);
}

void Source::resumeAtomic()
{
	if (valid && !isPlaying())
	{
		alSourcePlay(source);

		//failed to play or nothing to play
		if (alGetError() == AL_INVALID_VALUE || sourceType == Type::STREAM && (int)unusedBuffers.size() == buffers)
			releaseSource();
	}
}

size_t Source::copyBuffer(char* dst, size_t size, size_t offset)
{
	auto l = pool->lock();
	switch (sourceType)
	{
	case Type::STATIC: //TODO:
		break;
	case Type::STREAM:
	{			
		const auto bufferSize = (size_t)decoder->getBufferSize();
		// note: avoid bufferSize - offset underflow
		offset = std::min(offset, bufferSize);
		size = std::min(size, bufferSize - offset);
		if (size <= 0)return 0;
		memcpy(dst, decoder->getBuffer() + offset, size);
		return size;
	}
	case Type::QUEUE:
		break;
	case Type::MAX_ENUM:
		break;
	}
	return 0;
}

int64_t Source::getBufferOffset()
{
	auto l = pool->lock();
	switch (sourceType)
	{
	case Type::STATIC: //TODO:
		break;
	case Type::STREAM:
	{
		return decoder->getBufferOffset();
	}
	case Type::QUEUE:
		break;
	case Type::MAX_ENUM:
		break;
	}
	return 0;
}

bool Source::playBatch(const std::vector<Source*> &sources)
{
	if (sources.empty())
		return true;
	auto pool = Pool::getInstance();
	if (!pool)
		return false;
	auto l = pool->lock();

	// NOTE: not bool, because std::vector<bool> is implemented as a bitvector
	// which means no bool references can be created.
	std::vector<char> wasPlaying(sources.size());
	std::vector<ALuint> ids(sources.size());

	for (size_t i = 0; i < sources.size(); i++)
	{
		if (!pool->assignSource(sources[i], ids[i], wasPlaying[i]))
		{
			for (size_t j = 0; j < i; j++)
				if (!wasPlaying[j])
					sources[j]->releaseSource(false);
			return false;
		}
	}

	std::vector<ALuint> toPlay;
	toPlay.reserve(sources.size());
	for (size_t i = 0; i < sources.size(); i++)
	{
		// If the source was paused, wasPlaying[i] will be true but we still
		// want to resume it. We don't want to call alSourcePlay on sources
		// that are actually playing though.
		if (wasPlaying[i] && sources[i]->isPlaying())
			continue;

		if (!wasPlaying[i])
		{
			auto source = sources[i];
			source->source = ids[i];
			source->prepareAtomic();
		}

		toPlay.push_back(ids[i]);
	}

	alGetError();
	alSourcePlayv((ALsizei)toPlay.size(), &toPlay[0]);
	const bool success = alGetError() == AL_NO_ERROR;

	for (auto& source : sources)
	{
		source->valid = source->valid || success;
		if (success && source->sourceType != Type::STREAM)
			source->offsetSamples = 0;
	}

	return success;
}

void Source::stopBatch(const std::vector<Source*> &sources)
{
	if (sources.empty())
		return;
	auto pool = Pool::getInstance();
	if (!pool)
		return;
	auto l = pool->lock();

	std::vector<ALuint> sourceIds;
	sourceIds.reserve(sources.size());
	for (auto& source : sources)
	{
		if (source->valid)
			sourceIds.push_back(source->source);
	}

	alSourceStopv((ALsizei)sourceIds.size(), &sourceIds[0]);

	for (auto& source : sources)
	{
		if (source->valid)
			source->teardownAtomic();
		source->releaseSource(false);
	}
}

void Source::pauseBatch(const std::vector<Source*> &sources)
{
	if (sources.empty())
		return;
	auto pool = Pool::getInstance();
	if (!pool)
		return;
	auto l = pool->lock();

	std::vector<ALuint> sourceIds;
	sourceIds.reserve(sources.size());
	for (auto& source : sources)
	{
		if (source->valid)
			sourceIds.push_back(source->source);
	}

	alSourcePausev((ALsizei)sourceIds.size(), &sourceIds[0]);
}

std::vector<Source*> Source::pauseAll()
{
	auto pool = Pool::getInstance();
	if (!pool)
		return {};
	std::vector<Source*> sources;
	{
		auto l = pool->lock();
		sources = pool->getPlayingSources();
	}

	const auto newend = std::remove_if(sources.begin(), sources.end(), [](Source* s) {
		return !s->isPlaying();
	});
	sources.erase(newend, sources.end());

	pauseBatch(sources);
	return sources;
}

void Source::stopAll()
{
	auto pool = Pool::getInstance();
	if (!pool)
		return;
	std::vector<Source*> sources;
	{
		auto l = pool->lock();
		sources = pool->getPlayingSources();
	}
	stopBatch(sources);
}

bool Source::releaseSource(bool stop)
{
	return pool->releaseSource(this, stop);
}

void Source::reset()
{
	alSourcei(source, AL_BUFFER, AL_NONE);
	alSourcefv(source, AL_POSITION, (float*)&position);
	alSourcefv(source, AL_VELOCITY, (float*)&velocity);
	alSourcefv(source, AL_DIRECTION, (float*)&direction);
	alSourcef(source, AL_PITCH, pitch);
	alSourcef(source, AL_GAIN, volume);
	alSourcef(source, AL_MIN_GAIN, minVolume);
	alSourcef(source, AL_MAX_GAIN, maxVolume);
	alSourcef(source, AL_REFERENCE_DISTANCE, referenceDistance);
	alSourcef(source, AL_ROLLOFF_FACTOR, rolloffFactor);
	alSourcef(source, AL_MAX_DISTANCE, maxDistance);
	alSourcei(source, AL_LOOPING, sourceType == Type::STATIC && isLooping() ? AL_TRUE : AL_FALSE);
	alSourcei(source, AL_SOURCE_RELATIVE, relative ? AL_TRUE : AL_FALSE);
	alSourcei(source, AL_CONE_INNER_ANGLE, cone.innerAngle);
	alSourcei(source, AL_CONE_OUTER_ANGLE, cone.outerAngle);
	alSourcef(source, AL_CONE_OUTER_GAIN, cone.outerVolume);
#ifdef ALC_EXT_EFX
	alSourcef(source, AL_AIR_ABSORPTION_FACTOR, absorptionFactor);
	alSourcef(source, AL_CONE_OUTER_GAINHF, cone.outerHighGain);
	alSourcef(source, AL_ROOM_ROLLOFF_FACTOR, rolloffFactor); //reverb-specific rolloff
	alSourcei(source, AL_DIRECT_FILTER, directfilter ? directfilter->getFilter() : AL_FILTER_NULL);
	// clear all send slots, then re-enable applied ones
	for (int i = 0; i < Engine::getMaxSourceEffectCount(); i++)
		alSource3i(source, AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, i, AL_FILTER_NULL);
	for (auto& i : effectmap)
		alSource3i(source, AL_AUXILIARY_SEND_FILTER,
			i.second.target,
			i.second.slot,
			i.second.filter ? i.second.filter->getFilter() : AL_FILTER_NULL);
	//alGetError();
#endif
}

int Source::streamAtomic(ALuint buffer, Decoder* d)
{
	if (!d) return 0;
	// Get more sound data.
	int decoded = std::max(d->decode(), 0LL);

	// OpenAL implementations are allowed to ignore 0-size alBufferData calls.
	if (decoded > 0)
	{
		const auto fmt = Engine::getFormat(d->getBitDepth(), d->getChannelCount());

		if (fmt != AL_NONE)
			alBufferData(buffer, fmt, d->getBuffer(), decoded, d->getSampleRate());
		else
			decoded = 0;
	}

	if (decoder->isFinished() && isLooping())
	{
		ALint queued, processed;
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
		if (queued > processed)
			toLoop = queued - processed;
		else
			toLoop = buffers - processed;
		d->rewind();
	}

	if (toLoop > 0)
	{
		if (--toLoop == 0)
		{
			//offsetSamples = 0;
			offsetSamples = d->tell();
		}
	}

	return decoded;
}

void Source::setMinVolume(float v)
{
	v = std::max(0.f, v);
	if (valid)
		alSourcef(source, AL_MIN_GAIN, v);
	minVolume = v;
}

float Source::getMinVolume() const
{
	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_MIN_GAIN, &f);
		return f;
	}
	// In case the Source isn't playing.
	return this->minVolume;
}

void Source::setMaxVolume(float v)
{
	v = std::max(0.f, v);
	if (valid)
		alSourcef(source, AL_MAX_GAIN, v);
	maxVolume = v;
}

float Source::getMaxVolume() const
{
	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_MAX_GAIN, &f);
		return f;
	}
	// In case the Source isn't playing.
	return maxVolume;
}

void Source::setRolloffFactor(float value)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcef(source, AL_ROLLOFF_FACTOR, value);

	rolloffFactor = value;
}

float Source::getRolloffFactor()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return 0;
	}

	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_ROLLOFF_FACTOR, &f);
		return f;
	}

	// In case the Source isn't playing.
	return rolloffFactor;
}

void Source::setReferenceDistance(float value)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcef(source, AL_REFERENCE_DISTANCE, value);

	referenceDistance = value;
}

float Source::getReferenceDistance()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return 0;
	}

	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_REFERENCE_DISTANCE, &f);
		return f;
	}

	// In case the Source isn't playing.
	return referenceDistance;
}

void Source::setMaxDistance(float value)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	value = std::min(value, MAX_ATTENUATION_DISTANCE);

	if (valid)
		alSourcef(source, AL_MAX_DISTANCE, value);

	maxDistance = value;
}

float Source::getMaxDistance()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return 0;
	}

	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_MAX_DISTANCE, &f);
		return f;
	}

	// In case the Source isn't playing.
	return maxDistance;
}

void Source::setAirAbsorptionFactor(float value)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	absorptionFactor = value;
#ifdef ALC_EXT_EFX
	if (valid)
	{
		alSourcef(source, AL_AIR_ABSORPTION_FACTOR, absorptionFactor);
		//alGetError();
	}
#endif
}

float Source::getAirAbsorptionFactor()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return 0;
	}

	return absorptionFactor;
}

int Source::getChannelCount() const
{
	return channels;
}

int Source::getSampleRate() const
{
	return sampleRate;
}

int Source::getBitDepth() const
{
	return bitDepth;
}

int Source::getBytesPerFrame() const
{
	return channels * bitDepth / 8;
}

bool Source::setFilter(const Filter::ParamMap& params)
{
	if (!directfilter)
		directfilter = new Filter();

	bool result = directfilter->setParams(params);

#ifdef ALC_EXT_EFX
	if (valid)
	{
		//in case of failure contains AL_FILTER_NULL, a valid non-filter
		alSourcei(source, AL_DIRECT_FILTER, directfilter->getFilter());
		//alGetError();
	}
#endif

	return result;
}

bool Source::removeFilter()
{
	delete directfilter;
	directfilter = nullptr;

#ifdef ALC_EXT_EFX
	if (valid)
	{
		alSourcei(source, AL_DIRECT_FILTER, AL_FILTER_NULL);
		//alGetError();
	}
#endif

	return true;
}

Filter::ParamMap Source::getFilter()
{
	if (!directfilter)
		return {};
	Filter::ParamMap params = directfilter->getParams();
	return params;
}

bool Source::setEffect(const std::string& name)
{
	ALuint slot, target;
	Filter *filter;

	// effect with this name doesn't exist
	if (!Engine::getEffectID(name, target))
		return false;

	auto iter = effectmap.find(name);
	if (iter == effectmap.end())
	{
		// new send target needed but no more room
		if (slotlist.empty())
			return false;

		slot = slotlist.top();
		slotlist.pop();
	}
	else
	{
		slot = iter->second.slot;
		filter = iter->second.filter;
		delete filter;
	}
	effectmap[name] = { nullptr, slot, target };

#ifdef ALC_EXT_EFX
	if (valid)
	{
		alSource3i(source, AL_AUXILIARY_SEND_FILTER, target, slot, AL_FILTER_NULL);
		//alGetError();
	}
#endif

	return true;
}

bool Source::setEffect(const std::string& name, const Filter::ParamMap& filterParams)
{
	ALuint slot, target;
	Filter *filter = nullptr;

	// effect with this name doesn't exist
	if (!Engine::getEffectID(name, target))
		return false;

	auto iter = effectmap.find(name);
	if (iter == effectmap.end())
	{
		// new send target needed but no more room
		if (slotlist.empty())
			return false;

		slot = slotlist.top();
		slotlist.pop();
	}
	else
	{
		slot = iter->second.slot;
		filter = iter->second.filter;
	}
	if (!filter)
		filter = new Filter();

	effectmap[name] = { filter, slot, target };

	filter->setParams(filterParams);

#ifdef ALC_EXT_EFX
	if (valid)
	{
		//in case of failure contains AL_FILTER_NULL, a valid non-filter
		alSource3i(source, AL_AUXILIARY_SEND_FILTER, target, slot, filter->getFilter());
		//alGetError();
	}
#endif
	return true;
}

bool Source::removeEffect(const std::string& name)
{
	const auto iter = effectmap.find(name);
	if (iter == effectmap.end())
		return false;

	const ALuint slot = iter->second.slot;
	Filter *filter = iter->second.filter;

	delete filter;

#ifdef ALC_EXT_EFX
	if (valid)
	{
		alSource3i(source, AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, slot, AL_FILTER_NULL);
		//alGetError();
	}
#endif
	effectmap.erase(iter);
	slotlist.push(slot);
	return true;
}

Filter::ParamMap Source::getEffect(const std::string& name)
{
	auto iter = effectmap.find(name);
	if (iter == effectmap.end())
		return {};
	Filter::ParamMap params;
	if (iter->second.filter)
		params = iter->second.filter->getParams();
	return params;
}

std::vector<std::string> Source::getActiveEffects() const
{
	if (effectmap.empty())
		return {};
	std::vector<std::string> list;
	list.reserve(effectmap.size());
	for (auto& i : effectmap)
		list.push_back(i.first);
	return list;
}

void Source::InvalidFormatException(int channelCount, int bitDepth)
{
	lastError = string_format("invalid format: channelCount=%d, bitDepth=%d" , channelCount, bitDepth);
}

void Source::SpatialSupportException()
{
	lastError = "invalid spatial operation on this source";
}

void Source::QueueLoopingException()
{
	lastError = "this source dose not support looping";
}

void Source::QueueTypeMismatchException()
{
	lastError = "this source dose not support queue";
}

void Source::QueueFormatMismatchException()
{
	lastError = "queue format mismatch";
}

void Source::QueueMalformedLengthException(int bytesPerSample)
{
	lastError = string_format("invalid queue buffer length, should be multiple of %d", bytesPerSample);
}
