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

bool AudioDecoderOgg::open(AudioStream* src, double tA, double tB)
{
	if (_isOpened || !src)
		return false;
	const ov_callbacks tCallbacks =
	{
		/*(size_t(*)(void *, size_t, size_t, void *))*/	streamReadFunc,
		/*(int(*)(void *, ogg_int64_t, int))*/			streamSeekFunc,
		/*(int(*)(void *))*/							streamCloseFunc,
		/*(long(*)(void *))*/							streamTellFunc
	};
	stream = src;
	stream->lock();
	stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
	const auto ret = ov_open_callbacks(stream, &_vf, nullptr, 0, tCallbacks);
	// it's not necessary to save position
	//streamPos = stream->tell();
	stream->unlock();

	_isOpened = true;
	if (ret != 0)
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
	stream->retain();
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
			//ALOGV("[AudioDecoderOgg::close] Ref=%d", stream->getReferenceCount());
			stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
			stream->release();
			stream = nullptr;
		}
	}
}

uint32_t AudioDecoderOgg::read(uint32_t framesToRead, char* pcmBuf)
{
	uint32_t ret = 0;
	const auto bytesToRead = framesToRead * sourceInfo.bytesPerFrame;
	if (_isABLoop && !in_read_loop)
	{
		ret = read_loop(framesToRead, pcmBuf);
	}
	else if (stream)
	{
		stream->lock();

		uint32_t size_read = 0;
		char* buffer = pcmBuf;
		while (size_read < bytesToRead)
		{
			// PCM format: signed 16-bit little-endian
			// note that tRet is not constant, most possible values are 512,2304,4096
			const auto read = ov_read(&_vf, buffer, bytesToRead - size_read, 0, 2, 1, &currentSec);
			if (read < 0)	 // error
			{
				break;
			}
			if (read == 0)  // end
				break;
			size_read += read;
			buffer += read;
		}

		stream->unlock();
		ret = size_read / sourceInfo.bytesPerFrame;
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
		// seek
		currentSec = 0;
		//currentSec seems always be 0

		stream->lock();

		ret = ov_pcm_seek(&_vf, frameOffset);

		stream->unlock();
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
	auto src = (AudioStream*)datasource;
	uint32_t tCountToRead = (src->size() - src->tell()) / size;
	if (tCountToRead > nmemb)
		tCountToRead = nmemb;

	src->read((uint8_t*)ptr, tCountToRead * size, nullptr);

	return tCountToRead;
}

int AudioDecoderOgg::streamSeekFunc(void *datasource, ogg_int64_t offset, int whence)
{
	auto tOrigin = AudioStream::SeekOrigin::BEGINNING;
	switch (whence)
	{
	case 0:
		tOrigin = AudioStream::SeekOrigin::BEGINNING;
		break;
	case 1:
		tOrigin = AudioStream::SeekOrigin::CURRENT;
		break;
	case 2:
		tOrigin = AudioStream::SeekOrigin::END;
		break;
	default: ;
	}
	if (!((AudioStream*)datasource)->seek(tOrigin, offset))
		return -1;
	return 0;
}

int AudioDecoderOgg::streamCloseFunc(void *datasource)
{
	return 0;
}

long AudioDecoderOgg::streamTellFunc(void *datasource)
{
	return (long)((AudioStream*)datasource)->tell();
}
