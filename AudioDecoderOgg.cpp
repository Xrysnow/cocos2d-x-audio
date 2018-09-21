#include "AudioDecoderOgg.h"
#include "AudioMacros.h"
#include "platform/CCFileUtils.h"
#include <algorithm>

#define LOG_TAG "AudioDecoderOgg"

using namespace xAudio;

AudioDecoderOgg::AudioDecoderOgg()
{
}

AudioDecoderOgg::~AudioDecoderOgg()
{
	AudioDecoderOgg::close();
}

bool AudioDecoderOgg::open(const char* path)
{
	if (_isOpened)
		return false;
	auto fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(path);
    if (0 == ov_fopen(cocos2d::FileUtils::getInstance()->getSuitableFOpen(fullPath).c_str(), &_vf))
    {
		vInfo = ov_info(&_vf, -1);
        sourceInfo.sampleRate = static_cast<uint32_t>(vInfo->rate);
        sourceInfo.channelCount = vInfo->channels;
		// 16-bit pre channel, set by ov_read
        sourceInfo.bytesPerFrame = vInfo->channels * sizeof(short);
        sourceInfo.totalFrames = static_cast<uint32_t>(ov_pcm_total(&_vf, -1));
        _isOpened = true;
        return true;
    }
    return false;
}

bool AudioDecoderOgg::open(fcyStream* src, double tA, double tB)
{
	if (_isOpened || !src)
		return false;
	ov_callbacks tCallbacks =
	{
		/*(size_t(*)(void *, size_t, size_t, void *))*/  streamReadFunc,
		/*(int(*)(void *, ogg_int64_t, int))*/           streamSeekFunc,
		/*(int(*)(void *))*/                             streamCloseFunc,
		/*(long(*)(void *))*/                            streamTellFunc
	};
	stream = src;
	stream->retain();
	stream->Lock();
	stream->SetPosition(BEG, 0);
	auto tRet = ov_open_callbacks(stream, &_vf, nullptr, 0, tCallbacks);
	// fcyStream::GetPosition is designed to be atomic,
	// so it's not necessary to save position
	//streamPos = stream->GetPosition();
	stream->Unlock();

	_isOpened = true;
	if (tRet != 0)
	{
		close();
		return false;
	}
	vInfo = ov_info(&_vf, -1);
	sourceInfo.sampleRate = static_cast<uint32_t>(vInfo->rate);
	sourceInfo.channelCount = vInfo->channels;
	sourceInfo.bytesPerFrame = vInfo->channels * sizeof(short);
	sourceInfo.totalFrames = static_cast<uint32_t>(ov_pcm_total(&_vf, -1));

	calcLoopAB(tA, tB);
	//ALOGV("AudioDecoderOgg::open finished");
	return true;
}

void AudioDecoderOgg::close()
{
    if (_isOpened)
    {
        ov_clear(&_vf);
        _isOpened = false;
	    if (stream)
	    {
			ALOGV("[AudioDecoderOgg::close] Ref=%d", stream->getReferenceCount());
			stream->SetPosition(BEG, 0);
		    stream->release();
			stream = nullptr;
	    }
    }
}

uint32_t AudioDecoderOgg::read(uint32_t framesToRead, char* pcmBuf)
{
	uint32_t ret = 0;
	uint32_t bytesToRead = framesToRead * sourceInfo.bytesPerFrame;
	if (_isABLoop && !in_read_loop)
	{
		ret = read_loop(framesToRead, pcmBuf);
	}
	else if (stream)
	{
		stream->Lock(); // 锁定流

		uint32_t tSizeRead = 0;
		char* tBuffer = pcmBuf;
		while (tSizeRead < bytesToRead)
		{
			// PCM format: signed 16-bit little-endian
			// note that tRet is not constant, most possible values are 512,2304,4096
			auto tRet = ov_read(&_vf, tBuffer, bytesToRead - tSizeRead, 0, 2, 1, &currentSec);
			if (tRet < 0)     // 错误
			{
				break;
			}
			if (tRet == 0)  // 到尾部
				break;
			tSizeRead += tRet;
			tBuffer += tRet;
		}

		stream->Unlock();
		ret = tSizeRead / sourceInfo.bytesPerFrame;
	}
	else
	{
		auto bytesRead = ov_read(&_vf, pcmBuf, bytesToRead, 0, 2, 1, &currentSec);
		if (bytesRead < 0)
			ret = 0;
		else
			ret = static_cast<uint32_t>(bytesRead / sourceInfo.bytesPerFrame);
	}

    return ret;
}

bool AudioDecoderOgg::seek(uint32_t frameOffset)
{
	if (frameOffset >= sourceInfo.totalFrames)
		return false;
	int ret;
	if (stream)
	{
		ALOGV("[AudioDecoderOgg::seek] Seek %u.", frameOffset);
		// 进行Seek操作
		currentSec = 0;
		//currentSec seems always equals to 0

		stream->Lock();  // 锁定流

		ret = ov_pcm_seek(&_vf, frameOffset);

		stream->Unlock();
	} else {
		ret = ov_pcm_seek(&_vf, frameOffset);
	}
    return 0 == ret;
}

uint32_t AudioDecoderOgg::tell() const
{
    return static_cast<uint32_t>(ov_pcm_tell(const_cast<OggVorbis_File*>(&_vf)));
}

size_t AudioDecoderOgg::streamReadFunc(void *ptr, size_t size, size_t nmemb, void *datasource)
{
	auto src = (fcyStream*)datasource;
	uint32_t tCountToRead = (src->GetLength() - src->GetPosition()) / size;
	if (tCountToRead > nmemb)
		tCountToRead = nmemb;

	src->ReadBytes((uint8_t*)ptr, tCountToRead * size, nullptr);

	return tCountToRead;
}

int AudioDecoderOgg::streamSeekFunc(void *datasource, ogg_int64_t offset, int whence)
{
	FCYSEEKORIGIN tOrigin = BEG;
	switch (whence)
	{
	case 0:
		tOrigin = BEG;
		break;
	case 1:
		tOrigin = CUR;
		break;
	case 2:
		tOrigin = END;
		break;
	default: ;
	}
	if (FCYFAILED(((fcyStream*)datasource)->SetPosition(tOrigin, offset)))
		return -1;
	return 0;
}

int AudioDecoderOgg::streamCloseFunc(void *datasource)
{
	return 0;
}

long AudioDecoderOgg::streamTellFunc(void *datasource)
{
	return (long)((fcyStream*)datasource)->GetPosition();
}
