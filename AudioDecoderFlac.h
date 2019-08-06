#pragma once
#include "AudioDecoder.h"
#include "cocos2d.h"
#if CC_64BITS
#define DRFLAC_64BIT
#endif
#include "dr_flac.h"

namespace audio
{
	class DecoderFlac : public Decoder
	{
		DecoderFlac(size_t bufferSize);
		virtual ~DecoderFlac();
		bool init(Stream* src);
	public:
		static DecoderFlac* create(Stream* src, size_t bufferSize);

		int64_t decode(char* dst, uint64_t bytesToRead) override;
		bool seek(int64_t frameOffset) override;
		int64_t tell() override;
		bool isSeekable() override;
	private:
		drflac* flac = nullptr;
	};	
}
