#pragma once

#include "AudioDecoder.h"

namespace nqr {
	struct AudioData;
}

namespace xAudio
{
	class AudioDecoderWav
		: public AudioDecoder
	{
	public:
	public:
		bool open(const char* path) override;
		bool open(fcyStream* stream, double loopA = 0, double loopB = -1) override;
		void close() override;
		uint32_t read(uint32_t framesToRead, char* pcmBuf) override;
		bool seek(uint32_t frameOffset) override;
		uint32_t tell() const override;
		uint32_t fixLength(std::vector<uint8_t>* buffer = nullptr) override;

	private:
		uint64_t data_offset = 0;
	protected:
		AudioDecoderWav();
		~AudioDecoderWav();

		friend class AudioDecoderManager;
	};	
}
