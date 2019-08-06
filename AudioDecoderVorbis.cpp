﻿#include "AudioDecoderVorbis.h"
#include <string>

using namespace audio;

static int vorbisClose(void *	/* ptr to the data that the vorbis files need*/)
{
	// Does nothing (handled elsewhere)
	return 0;
}

static size_t vorbisRead(
	void *ptr			/* ptr to the data that the vorbis files need*/,
	size_t size			/* how big a byte is*/,
	size_t nmemb		/* How much we can read*/,
	void *datasource	/* this is a pointer to the data we passed into ov_open_callbacks (our SOggFile struct*/)
{
	auto src = (Stream*)datasource;
	size_t toRead = (src->size() - src->tell()) / size;
	if (toRead > nmemb)
		toRead = nmemb;
	uint64_t read = 0;
	src->read((uint8_t*)ptr, toRead * size, &read);
	return read;
}

static int vorbisSeek(
	void *datasource	/* ptr to the data that the vorbis files need*/,
	ogg_int64_t offset	/*offset from the point we wish to seek to*/,
	int whence			/*where we want to seek to*/)
{
	auto tOrigin = Stream::SeekOrigin::BEGINNING;
	switch (whence)
	{
	case 0:
		tOrigin = Stream::SeekOrigin::BEGINNING;
		break;
	case 1:
		tOrigin = Stream::SeekOrigin::CURRENT;
		break;
	case 2:
		tOrigin = Stream::SeekOrigin::END;
		break;
	default:;
	}
	if (!((Stream*)datasource)->seek(tOrigin, offset))
		return -1;
	return 0;
}

static long vorbisTell(void *datasource	/* ptr to the data that the vorbis files need*/)
{
	return (long)((Stream*)datasource)->tell();
}

DecoderVorbis::DecoderVorbis(size_t bufferSize)
	: Decoder(bufferSize, DecoderType::VORBIS),
	vorbisCallbacks(),
	handle()
{
}

DecoderVorbis::~DecoderVorbis()
{
	ov_clear(&handle);
	if (stream)
	{
		stream->seek(Stream::SeekOrigin::BEGINNING, 0);
		stream->release();
		stream = nullptr;
	}
}

bool DecoderVorbis::init(Stream* src)
{
	stream = src;
	if (!stream)
		return false;
	// Initialize callbacks
	vorbisCallbacks.close_func = vorbisClose;
	vorbisCallbacks.seek_func = vorbisSeek;
	vorbisCallbacks.read_func = vorbisRead;
	vorbisCallbacks.tell_func = vorbisTell;
	// Check endianness
//if (CC_HOST_IS_BIG_ENDIAN)
//	endian = 1;
//else
//	endian = 0;
	endian = 0;

	stream->lock();
	stream->seek(Stream::SeekOrigin::BEGINNING, 0);
	// Open Vorbis handle
	const auto ret = ov_open_callbacks(stream, &handle, nullptr, 0, vorbisCallbacks);
	stream->unlock();
	if (ret != 0)
		return false;
	// Get info and comments
	vorbisInfo = ov_info(&handle, -1);
	vorbisComment = ov_comment(&handle, -1);

	audioInfo.totalFrames = ov_pcm_total(&handle, -1);
	audioInfo.channelCount = vorbisInfo->channels;
	audioInfo.sampleRate = vorbisInfo->rate;
	audioInfo.bytesPerFrame = vorbisInfo->channels * 2; // 16bit

	stream->retain();
	return true;
}

DecoderVorbis* DecoderVorbis::create(Stream* src, size_t bufferSize)
{
	auto ret = new (std::nothrow) DecoderVorbis(bufferSize);
	if (ret&&ret->init(src))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

int64_t DecoderVorbis::decode(char* dst, uint64_t bytesToRead)
{
	uint64_t size = 0;
	while (size < bytesToRead)
	{
		stream->lock();
		const auto result = ov_read(&handle, dst + size, int(bytesToRead - size),
			endian, (getBitDepth() == 16 ? 2 : 1), 1, nullptr);
		stream->unlock();
		if (result == OV_HOLE)
			continue;
		else if (result <= OV_EREAD)
			return -1;
		else if (result == 0)
		{
			eof = true;
			break;
		}
		else if (result > 0)
			size += result;
	}
	return size;
}

bool DecoderVorbis::seek(int64_t frameOffset)
{
	if (frameOffset >= getTotalFrames())
		return false;
	int result;
	stream->lock();
	// Avoid ov_pcm_seek when seeking to 0, to avoid
	// a bug in libvorbis <= 1.3.4 when seeking to PCM 0 in multiplexed streams.
	if (frameOffset == 0)
		result = ov_raw_seek(&handle, 0);
	else
		result = ov_pcm_seek(&handle, frameOffset);
	stream->unlock();

	if (result == 0)
	{
		eof = false;
		return true;
	}
	return false;
}

int64_t DecoderVorbis::tell()
{
	return int64_t(ov_pcm_tell(&handle));
}

bool DecoderVorbis::isSeekable()
{
	return ov_seekable(&handle) != 0;
}
