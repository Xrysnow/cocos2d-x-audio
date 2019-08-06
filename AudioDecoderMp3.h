#pragma once
#include "AudioDecoder.h"
#include "dr_mp3.h"

namespace audio
{
	class DecoderMp3 : public Decoder
	{
		DecoderMp3(size_t bufferSize);
		virtual ~DecoderMp3();
		bool init(Stream* src);
	public:
		static DecoderMp3* create(Stream* src, size_t bufferSize);

		int64_t decode(char* dst, uint64_t bytesToRead) override;
		bool seek(int64_t frameOffset) override;
		int64_t tell() override;
		bool isSeekable() override;
	private:
		drmp3* mp3 = nullptr;
	};	
}
