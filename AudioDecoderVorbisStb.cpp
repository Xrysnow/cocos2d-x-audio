#include "AudioDecoderVorbisStb.h"
#include "AudioCommon.h"
#include <string>

using namespace audio;

static int stbVorbisRead(void* cookie, char* buf, unsigned int size)
{
	const auto p = (Stream*)cookie;
	// skip if not enough
	if (p->size() - p->tell() < size)
		return 0;
	uint64_t read = 0;
	if (!p->read((uint8_t*)buf, size, &read))
		return 0;
	return (int)read;
}
static int stbVorbisSeek(void* cookie, int* pos, int whence)
{
	const auto p = (Stream*)cookie;
	Stream::SeekOrigin origin = Stream::SeekOrigin::BEGINNING;
	if (whence == SEEK_CUR)
		origin = Stream::SeekOrigin::CURRENT;
	else if (whence == SEEK_END)
		origin = Stream::SeekOrigin::END;
	const bool ok = p->seek(origin, *pos);
	*pos = (int)p->tell();
	return ok ? 0 : -1;
}
static int stbVorbisTell(void* cookie)
{
	const auto p = (Stream*)cookie;
	return (int)p->tell();
}
static int stbVorbisClose(void* cookie)
{
	return 0;
}

DecoderStbVorbis::DecoderStbVorbis(size_t bufferSize)
	: Decoder(bufferSize, DecoderType::VORBIS)
{
}

DecoderStbVorbis::~DecoderStbVorbis()
{
	stb_vorbis_close(handle);
	if (stream)
	{
		stream->seek(Stream::SeekOrigin::BEGINNING, 0);
		stream->release();
		stream = nullptr;
	}
}

bool DecoderStbVorbis::init(Stream* src)
{
	stream = src;
	if (!stream)
		return false;
	stream->lock();
	stream->seek(Stream::SeekOrigin::BEGINNING, 0);
	stb_vorbis_cookie cookie;
	cookie.cookie = stream;
	cookie.reader = stbVorbisRead;
	cookie.seeker = stbVorbisSeek;
	cookie.teller = stbVorbisTell;
	cookie.closer = stbVorbisClose;
	int error;
	handle = stb_vorbis_open_cookie(cookie, &error, nullptr, (unsigned)stream->size());
	stream->unlock();
	if (!handle)
	{
		AINFO("can't open vorbis stream: %d", error);
		return false;
	}
	vorbisInfo = stb_vorbis_get_info(handle);
	vorbisComment = stb_vorbis_get_comment(handle);
	audioInfo.totalFrames = stb_vorbis_stream_length_in_samples(handle) / vorbisInfo.channels; // can be 0 if not given
	audioInfo.channelCount = vorbisInfo.channels;
	audioInfo.sampleRate = vorbisInfo.sample_rate;
	audioInfo.bytesPerFrame = vorbisInfo.channels * 2; // 16bit

	stream->retain();
	return true;
}

DecoderStbVorbis* DecoderStbVorbis::create(Stream* src, size_t bufferSize)
{
	auto ret = new (std::nothrow) DecoderStbVorbis(bufferSize);
	if (ret && ret->init(src))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

int64_t DecoderStbVorbis::decode(char* dst, uint64_t bytesToRead)
{
	stream->lock();
	const auto nFrame = stb_vorbis_get_samples_short_interleaved(handle, vorbisInfo.channels, (short*)dst, bytesToRead / 2);
	stream->unlock();
	if (nFrame == 0)
		eof = true;
	lastSeek = -1;
	return int64_t(nFrame) * vorbisInfo.channels * 2;
}

bool DecoderStbVorbis::seek(int64_t frameOffset)
{
	stream->lock();
	const auto ret = stb_vorbis_seek(handle, frameOffset * vorbisInfo.channels);
	stream->unlock();
	const auto ok = ret == 1;
	if (ok)
	{
		lastSeek = frameOffset;
		eof = false;
	}
	return ok;
}

int64_t DecoderStbVorbis::tell()
{
	if (lastSeek >= 0)
		return lastSeek;
	// NOT WORKING YET after a seek with PULLDATA API
	return stb_vorbis_get_sample_offset(handle) / vorbisInfo.channels;
}

bool DecoderStbVorbis::isSeekable()
{
	return true;
}
