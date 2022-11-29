#pragma once
#include "AudioDecoder.h"
#include "AudioStream.h"
#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"
#include <cstdint>

namespace audio
{
	class DecoderStbVorbis : public Decoder
	{
		DecoderStbVorbis(size_t bufferSize);
		virtual ~DecoderStbVorbis();
		bool init(Stream* src);
	public:

		static DecoderStbVorbis* create(Stream* src, size_t bufferSize);

		int64_t decode(char* dst, uint64_t bytesToRead) override;
		bool seek(int64_t frameOffset) override;
		int64_t tell() override;
		bool isSeekable() override;

	private:
		stb_vorbis* handle = nullptr;
		stb_vorbis_info vorbisInfo;
		stb_vorbis_comment vorbisComment;
		int64_t lastSeek = -1;
	};
}
