#include "platform/CCPlatformConfig.h"

#include "AudioCache.h"
#include <thread>
#include "base/CCDirector.h"
#include "base/CCScheduler.h"

#include "AudioDecoderManager.h"
#include "AudioDecoder.h"

#define LOG_TAG "AudioCache"
//#define VERY_VERY_VERBOSE_LOGGING
#ifdef VERY_VERY_VERBOSE_LOGGING
#define ALOGVV ALOGV
#else
#define ALOGVV(...) do{} while(false)
#endif

namespace {
unsigned int __idIndex = 0;
}

#define INVALID_AL_BUFFER_ID 0xFFFFFFFF
#define PCMDATA_CACHEMAXSIZE 1048576

using namespace xAudio;

AudioCache::AudioCache():
_format(-1),
_duration(0.0f),
_framesRead(0),
_alBufferId(INVALID_AL_BUFFER_ID),
_pcmData(nullptr),
_queBufferFrames(0),
_state(State::INITIAL),
_isDestroyed(std::make_shared<bool>(false)),
_id(++__idIndex),
_isLoadingFinished(false),
_isSkipReadDataTask(false),
_stream(nullptr),
_loopA(0),
_loopB(-1),
_forceLoad(false)
{
	ALOGVV("AudioCache() %p, id=%u", this, _id);
	for (int i = 0; i < QUEUEBUFFER_NUM; ++i)
	{
		_queBuffers[i] = nullptr;
		_queBufferSize[i] = 0;
	}
}

AudioCache::~AudioCache()
{
	ALOGVV("~AudioCache() %p, id=%u, begin", this, _id);
	// When call "delete this" and 'readDataTask' is running,
	// this will make 'readDataTask' quit properly and as soon as possible.
	*_isDestroyed = true;
	while (!_isLoadingFinished)
	{
		if (_isSkipReadDataTask)
		{
			ALOGV("id=%u, Skip read data task, don't continue to wait!", _id);
			break;
		}
		ALOGVV("id=%u, waiting readData thread to finish ...", _id);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	// Wait for the 'readDataTask' task to exit.
	// This will not waste time because in 'readDataTask',
	// '_isLoadingFinished' is near '_readDataTaskMutex.unlock'.
	_readDataTaskMutex.lock();
	_readDataTaskMutex.unlock();

	if (_pcmData)
	{
		if (_state == State::READY)
		{
			if (_alBufferId != INVALID_AL_BUFFER_ID && alIsBuffer(_alBufferId))
			{
				ALOGVV("~AudioCache(id=%u), delete buffer: %u", _id, _alBufferId);
				alDeleteBuffers(1, &_alBufferId);
				_alBufferId = INVALID_AL_BUFFER_ID;
			}
		}
		else
		{
			ALOGW("AudioCache (%p), id=%u, buffer isn't ready, state=%d", this, _id, _state);
		}

		free(_pcmData);
	}

	if (_queBufferFrames > 0)
	{
		for (int index = 0; index < QUEUEBUFFER_NUM; ++index)
			free(_queBuffers[index]);
	}
	ALOGVV("~AudioCache() %p, id=%u, end", this, _id);
}

void AudioCache::readDataTask(unsigned int selfId)
{
	//Note: It's in sub thread
	//ALOGVV("readDataTask begin, cache id=%u", selfId);

	_readDataTaskMutex.lock();
	_state = State::LOADING;

	AudioDecoder* decoder = AudioDecoderManager::createDecoder(_fileFullPath.c_str());
	do
	{
		if (decoder == nullptr ||
			(_stream ? !decoder->open(_stream, _loopA, _loopB) : !decoder->open(_fileFullPath.c_str())))
			break;
		_isLoopAB = decoder->isABLoop();

		_sourceInfo.channelCount = decoder->getChannelCount();
		_format = _sourceInfo.channelCount > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		_sourceInfo.sampleRate = (ALsizei)decoder->getSampleRate();
		_sourceInfo.bytesPerFrame = decoder->getBytesPerFrame();
		_sourceInfo.totalFrames = decoder->getTotalFrames();
		_duration = 1.0 * _sourceInfo.totalFrames / _sourceInfo.sampleRate;

		const uint32_t originalTotalFrames = _sourceInfo.totalFrames;
		uint32_t totalFrames = originalTotalFrames;
		uint32_t dataSize = totalFrames * _sourceInfo.bytesPerFrame;
		uint32_t remainingFrames = totalFrames;
		uint32_t adjustFrames = 0;
		// if AB loop is enabled, we should use queue buffer
		if ((dataSize <= PCMDATA_CACHEMAXSIZE || _forceLoad) && !decoder->isABLoop())
		{
			const uint32_t framesToReadOnce = std::min(totalFrames,
				static_cast<uint32_t>(_sourceInfo.sampleRate * QUEUEBUFFER_TIME_STEP * QUEUEBUFFER_NUM));

			std::vector<uint8_t> adjustFrameBuf;

			if (decoder->seek(totalFrames))
			{
				adjustFrames = decoder->fixLength(&adjustFrameBuf);
				if (adjustFrames > 0)
				{
					dataSize = decoder->getTotalFrames() * _sourceInfo.bytesPerFrame;
					_sourceInfo.totalFrames = decoder->getTotalFrames();
					_duration = 1.0 * _sourceInfo.totalFrames / _sourceInfo.sampleRate;
					// decoder dose not use AB loop
					//decoder->calcLoopAB(_loopA, _loopB);
				}
			}
			// Reset to frame 0
			BREAK_IF_ERR_LOG(!decoder->seek(0), "AudioDecoder::seek(0) failed!");

			_pcmData = (char*)malloc(dataSize);
			if (!_pcmData)
				break;
			memset(_pcmData, 0x00, dataSize);
			_pcmDataSize = dataSize;

			// copy extra part
			if (adjustFrames > 0)
			{
				memcpy(_pcmData + (dataSize - adjustFrameBuf.size()), adjustFrameBuf.data(), adjustFrameBuf.size());
			}

			alGenBuffers(1, &_alBufferId);
			auto alError = alGetError();
			if (alError != AL_NO_ERROR) {
				ALOGE("%s: attaching audio to buffer fail: %x", __FUNCTION__, alError);
				break;
			}

			if (*_isDestroyed) break;

			// here '_framesRead' should be 0?
			uint32_t framesRead = decoder->readFixedFrames(
				std::min(framesToReadOnce, remainingFrames),
				_pcmData + _framesRead * _sourceInfo.bytesPerFrame);
			_framesRead += framesRead;
			remainingFrames -= framesRead;

			if (*_isDestroyed) break;

			uint32_t frames = 0;
			// read step by step in order to quit fastly when needed.
			while (!*_isDestroyed && _framesRead < originalTotalFrames)
			{
				frames = std::min(framesToReadOnce, remainingFrames);
				if (_framesRead + frames > originalTotalFrames)
				{
					frames = originalTotalFrames - _framesRead;
				}
				framesRead = decoder->read(frames, _pcmData + _framesRead * _sourceInfo.bytesPerFrame);
				if (framesRead == 0)
					break;
				_framesRead += framesRead;
				remainingFrames -= framesRead;
			}

			if (*_isDestroyed) break;

			if (_framesRead < originalTotalFrames)
			{
				memset(_pcmData + _framesRead * _sourceInfo.bytesPerFrame, 0x00, (totalFrames - _framesRead) * _sourceInfo.bytesPerFrame);
			}
			ALOGVV("[AudioCache::readDataTask] pcm buffer loaded, total frames: %u, total read: %u, adjust: %u, remaining: %u",
				totalFrames, _framesRead, adjustFrames, remainingFrames);

			_framesRead += adjustFrames;

			alBufferData(_alBufferId, _format, _pcmData, (ALsizei)dataSize, (ALsizei)_sourceInfo.sampleRate);

			_state = State::READY;
		}
		else
		{
			_queBufferFrames = _sourceInfo.sampleRate * QUEUEBUFFER_TIME_STEP;
			BREAK_IF_ERR_LOG(_queBufferFrames == 0, "_queBufferFrames == 0");

			const uint32_t queBufferBytes = _queBufferFrames * _sourceInfo.bytesPerFrame;

			for (int index = 0; index < QUEUEBUFFER_NUM; ++index)
			{
				_queBuffers[index] = (char*)malloc(queBufferBytes);
				_queBufferSize[index] = queBufferBytes;
				//get 0x00 if source don't have enough bytes
				decoder->readFixedFrames(_queBufferFrames, _queBuffers[index]);
			}

			_state = State::READY;
		}

	} while (false);

	AudioDecoderManager::destroyDecoder(decoder);

	if (_state != State::READY)
	{
		_state = State::FAILED;
		if (_alBufferId != INVALID_AL_BUFFER_ID && alIsBuffer(_alBufferId))
		{
			ALOGV("readDataTask failed, delete buffer: %u", _alBufferId);
			alDeleteBuffers(1, &_alBufferId);
			_alBufferId = INVALID_AL_BUFFER_ID;
		}
	}

	//FIXME: Why to invoke play callback first? Should it be after 'load' callback?
	invokingPlayCallbacks();
	invokingLoadCallbacks();

	_isLoadingFinished = true;
	_readDataTaskMutex.unlock();
	//ALOGVV("readDataTask end, cache id=%u", selfId);
}

void AudioCache::addPlayCallback(const std::function<void()>& callback)
{
	std::lock_guard<std::mutex> lk(_playCallbackMutex);
	switch (_state)
	{
		case State::INITIAL:
		case State::LOADING:
			_playCallbacks.push_back(callback);
			break;

		case State::READY:
		// If state is failure, we still need to invoke the callback
		// since the callback will set the 'AudioPlayer::_removeByAudioEngine' flag to true.
		case State::FAILED:
			callback();
			break;

		default:
			ALOGE("Invalid state: %d", _state);
			break;
	}
}

void AudioCache::invokingPlayCallbacks()
{
	std::lock_guard<std::mutex> lk(_playCallbackMutex);

	for (auto&& cb : _playCallbacks)
	{
		cb();
	}

	_playCallbacks.clear();
}

void AudioCache::addLoadCallback(const std::function<void(bool)>& callback)
{
	switch (_state)
	{
		case State::INITIAL:
		case State::LOADING:
			_loadCallbacks.push_back(callback);
			break;

		case State::READY:
			callback(true);
			break;
		case State::FAILED:
			callback(false);
			break;

		default:
			ALOGE("Invalid state: %d", _state);
			break;
	}
}

void AudioCache::invokingLoadCallbacks()
{
	if (*_isDestroyed)
	{
		ALOGV("AudioCache (%p) was destroyed, don't invoke preload callback ...", this);
		return;
	}

	auto isDestroyed = _isDestroyed;
	auto scheduler = cocos2d::Director::getInstance()->getScheduler();
	scheduler->performFunctionInCocosThread([&, isDestroyed](){
		if (*isDestroyed)
		{
			ALOGV("invokingLoadCallbacks perform in cocos thread, AudioCache (%p) was destroyed!", this);
			return;
		}

		for (auto&& cb : _loadCallbacks)
		{
			cb(_state == State::READY);
		}

		_loadCallbacks.clear();
	});
}

ALenum AudioCache::getFormat() const
{
	return _state == State::READY ? _format : AL_INVALID;
}

uint32_t AudioCache::getSampleRate() const
{
	return _state == State::READY ? _sourceInfo.sampleRate : 0;
}

double AudioCache::getDuration() const
{
	return _state == State::READY ? _duration : -1;
}

uint32_t AudioCache::getTotalFrames() const
{
	return _state == State::READY ? _sourceInfo.totalFrames : 0;
}

uint32_t AudioCache::getBytesPerFrame() const
{
	return _state == State::READY ? _sourceInfo.bytesPerFrame : 0;
}

uint32_t AudioCache::getChannelCount() const
{
	return _state == State::READY ? _sourceInfo.channelCount : 0;
}

SourceInfo* AudioCache::getSourceInfo()
{
	return _state == State::READY ? &_sourceInfo : nullptr;
}

bool AudioCache::blockToReady()
{
	if (_state == State::FAILED)
		return false;
	_readDataTaskMutex.lock();
	_readDataTaskMutex.unlock();
	return _state == State::READY;
}

