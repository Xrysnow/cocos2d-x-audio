#pragma once
#include "AudioDecoder.h"

namespace audio
{
	class DecoderWav : public Decoder
	{
		DecoderWav(size_t bufferSize);
		virtual ~DecoderWav();
		bool init(Stream* src);
	public:

		static DecoderWav* create(Stream* src, size_t bufferSize);

		int64_t decode(char* dst, uint64_t bytesToRead) override;
		bool seek(int64_t frameOffset) override;
		int64_t tell() override;
		bool isSeekable() override;

	protected:
		uint64_t data_offset = 0;
	};	
}
