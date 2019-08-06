#define DR_MP3_IMPLEMENTATION
#include "AudioDecoderMp3.h"

using namespace audio;

/*
Callback for when data is read. Return value is the number of bytes actually read.

pUserData   [in]  The user data that was passed to drmp3_init(), drmp3_open() and family.
pBufferOut  [out] The output buffer.
bytesToRead [in]  The number of bytes to read.

Returns the number of bytes actually read.

A return value of less than bytesToRead indicates the end of the stream. Do _not_ return from this callback until
either the entire bytesToRead is filled or you have reached the end of the stream.
*/
static size_t mp3Read(void* pUserData, void* pBufferOut, size_t bytesToRead)
{
	auto src = (Stream*)pUserData;
	size_t toRead = src->size() - src->tell();
	if (toRead > bytesToRead)
		toRead = bytesToRead;
	uint64_t read = 0;
	src->read((uint8_t*)pBufferOut, toRead, &read);
	return read;
}
/*
Callback for when data needs to be seeked.

pUserData [in] The user data that was passed to drmp3_init(), drmp3_open() and family.
offset    [in] The number of bytes to move, relative to the origin. Will never be negative.
origin    [in] The origin of the seek - the current position or the start of the stream.

Returns whether or not the seek was successful.

Whether or not it is relative to the beginning or current position is determined by the "origin" parameter which
will be either drmp3_seek_origin_start or drmp3_seek_origin_current.
*/
static drmp3_bool32 mp3Seek(void* pUserData, int offset, drmp3_seek_origin origin)
{
	auto src = (Stream*)pUserData;
	bool ret = false;
	switch (origin) {
	case drmp3_seek_origin_start:
		ret = src->seek(Stream::SeekOrigin::BEGINNING, offset);
		break;
	case drmp3_seek_origin_current:
		ret = src->seek(Stream::SeekOrigin::CURRENT, offset);
		break;
	default:;
	}
	return ret;
}

DecoderMp3::DecoderMp3(size_t bufferSize)
	: Decoder(bufferSize, DecoderType::MP3)
{
}

DecoderMp3::~DecoderMp3()
{
	if (mp3)
		drmp3_uninit(mp3);
	delete mp3;
	if (stream)
	{
		stream->seek(Stream::SeekOrigin::BEGINNING, 0);
		stream->release();
		stream = nullptr;
	}
}

bool DecoderMp3::init(Stream* src)
{
	stream = src;
	if (!stream)
		return false;
	mp3 = new drmp3{};
	stream->lock();
	stream->seek(Stream::SeekOrigin::BEGINNING, 0);
	const auto ok = drmp3_init(mp3, mp3Read, mp3Seek, stream, nullptr);
	stream->unlock();
	if(!ok)
		return false;
	audioInfo.sampleRate = mp3->sampleRate;
	//audioInfo.bytesPerFrame = flac->bitsPerSample / 8;
	audioInfo.bytesPerFrame = 2 * mp3->channels;
	audioInfo.channelCount = mp3->channels;
	audioInfo.totalFrames = drmp3_get_pcm_frame_count(mp3);
	stream->retain();
	return true;
}

DecoderMp3* DecoderMp3::create(Stream* src, size_t bufferSize)
{
	auto ret = new (std::nothrow) DecoderMp3(bufferSize);
	if (ret&&ret->init(src))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

int64_t DecoderMp3::decode(char* dst, uint64_t bytesToRead)
{
	stream->lock();
	const auto framesRead = drmp3_read_pcm_frames_s16(mp3, bytesToRead / audioInfo.bytesPerFrame, (drmp3_int16*)dst);
	stream->unlock();
	const auto bytesRead = framesRead * 2 * audioInfo.channelCount;
	if (bytesRead < bytesToRead)
		eof = true;
	return bytesRead;
}

bool DecoderMp3::seek(int64_t frameOffset)
{
	stream->lock();
	const drmp3_bool32 result = drmp3_seek_to_pcm_frame(mp3, (drmp3_uint64)frameOffset);
	stream->unlock();
	if (result)
		eof = false;
	return result;
}

int64_t DecoderMp3::tell()
{
	return mp3->currentPCMFrame;
}

bool DecoderMp3::isSeekable()
{
	return true;
}
