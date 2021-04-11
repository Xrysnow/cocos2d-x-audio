#include "AudioDecoder.h"
#include "AudioStream.h"
#include "AudioDecoderWav.h"
#include "AudioDecoderVorbis.h"
#include "AudioDecoderFlac.h"
#include "AudioDecoderMp3.h"
#include "AudioCommon.h"
#include "cocos2d.h"
#include <algorithm>
#include <cctype>

using namespace audio;

static std::unordered_map<std::string, Decoder::DecoderType> DecoderTypeMap = {
	{"wav", Decoder::DecoderType::WAV},
	{"ogg", Decoder::DecoderType::VORBIS},
	{"flac", Decoder::DecoderType::FLAC},
	{"mp3", Decoder::DecoderType::MP3},
};

std::string Decoder::AudioInfo::toString()
{
	return string_format("Frame: %d, Freq: %d, Time: %.3f, Channel: %d, BitDepth: %d",
		(int)totalFrames, (int)sampleRate, (float)getTotalTime(),
		(int)channelCount, (int)getBitDepth());
}

Decoder::Decoder(size_t bufferSize, DecoderType type)
	: decoderType(type)
	, bufferSize(bufferSize)
{
	buffer = new int8_t[bufferSize];
}

Decoder::~Decoder()
{
	delete[] buffer;
}

Decoder::DecoderType Decoder::getDecoderTypeFromPath(const std::string& path)
{
	// get ext in lower case
	auto ext = cocos2d::FileUtils::getInstance()->getFileExtension(path);
	// remove dot
	if (!ext.empty())
		ext = ext.substr(1);
	const auto it = DecoderTypeMap.find(ext);
	if (it != DecoderTypeMap.end())
		return it->second;
	return Decoder::DecoderType::UNKNOWN;
}

Decoder* Decoder::createFromStream(Stream* s, size_t bufferSize, DecoderType type)
{
	if (!s)
		return nullptr;
	switch (type)
	{
	case Decoder::DecoderType::WAV:
		return DecoderWav::create(s, bufferSize);
	case Decoder::DecoderType::VORBIS:
		return DecoderVorbis::create(s, bufferSize);
	case Decoder::DecoderType::FLAC:
		return DecoderFlac::create(s, bufferSize);
	case Decoder::DecoderType::MP3:
		return DecoderMp3::create(s, bufferSize);
	case Decoder::DecoderType::UNKNOWN:
	default:;
	}
	return nullptr;
}

Decoder* Decoder::createFromFile(const std::string& path, size_t bufferSize, DecoderType type)
{
	if (type == DecoderType::UNKNOWN)
		type = getDecoderTypeFromPath(path);
	return createFromStream(Stream::createFromFile(path), bufferSize, type);
}

Decoder* Decoder::createFromLocalFile(const std::string& path, size_t bufferSize, DecoderType type)
{
	if (type == DecoderType::UNKNOWN)
		type = getDecoderTypeFromPath(path);
	return createFromStream(Stream::createFromLocalFile(path), bufferSize, type);
}

Decoder* Decoder::createFromStringData(const std::string& str, size_t bufferSize, DecoderType type)
{
	return createFromStream(Stream::createFromStringData(str), bufferSize, type);
}

Decoder* Decoder::createFromSoundData(SoundData* soundData, size_t bufferSize, DecoderType type)
{
	return createFromStream(Stream::createFromSoundData(soundData), bufferSize, type);
}

int8_t* Decoder::getBuffer() const
{
	return buffer;
}

bool Decoder::seekTime(double seconds)
{
	return seek(seconds*getSampleRate());
}

Decoder* Decoder::clone()
{
	//BUG: current implementation dose not support play from the same stream
	return createFromStream(stream, bufferSize, decoderType);
}

int64_t Decoder::decode()
{
	int64_t toReadSize = bufferSize;
	const int64_t tCurSample = tell();
	const int64_t tSampleToRead = bufferSize / getBytesPerFrame();
	const int64_t exceed = tCurSample + tSampleToRead - getLoopEnd();
	if (exceed > 0)
		toReadSize -= exceed * getBytesPerFrame();
	toReadSize = std::max(toReadSize, 0LL);
	const int64_t size = decode((char*)buffer, toReadSize);
	if (size > 0)
		bufferPosition = tCurSample;
	if (exceed > 0 && size == toReadSize)
		eof = true;
	return size;
}

int Decoder::getBufferSize() const
{
	return bufferSize;
}

void Decoder::setLoopingPoint(double tStart, double tEnd)
{
	if (tStart >= 0.0 && tEnd > 0.0 && tStart < tEnd)
	{
		const auto sampleRate = getSampleRate();
		const auto totalFrames = getTotalFrames();
		const auto start = std::min(int64_t(sampleRate * tStart), totalFrames);
		const auto end = std::min(int64_t(sampleRate * tEnd), totalFrames);
		if (start < end)
		{
			loopStart = start;
			loopEnd = end;
		}
	}
}

double Decoder::getLoopingStart()
{
	return (double)getLoopStart() / getSampleRate();
}

double Decoder::getLoopingEnd()
{
	return (double)getLoopEnd() / getSampleRate();
}

int64_t Decoder::getLoopStart() const
{
	return loopStart;
}

int64_t Decoder::getLoopEnd() const
{
	return loopEnd == 0 ? getTotalFrames() : loopEnd;
}

bool Decoder::rewind()
{
	return seek(getLoopStart());
}

bool Decoder::isFinished()
{
	return eof;
}

