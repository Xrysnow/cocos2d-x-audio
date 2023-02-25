#pragma once
#include "AudioDecoder.h"
#include "AudioStream.h"
#define OV_EXCLUDE_STATIC_CALLBACKS
#ifdef CC_VERSION
#include "../../external/ogg/include/vorbis/codec.h"
#include "../../external/ogg/include/vorbis/vorbisfile.h"
#else
#include "../../external/OggDecoder/include/vorbis/codec.h"
#include "../../external/OggDecoder/include/vorbis/vorbisfile.h"
#endif // CC_VERSION
#include <cstdint>

namespace audio
{
	class DecoderVorbis : public Decoder
	{
		DecoderVorbis(size_t bufferSize);
		virtual ~DecoderVorbis();
		bool init(Stream* src);
	public:

		static DecoderVorbis* create(Stream* src, size_t bufferSize);

		int64_t decode(char* dst, uint64_t bytesToRead) override;
		bool seek(int64_t frameOffset) override;
		int64_t tell() override;
		bool isSeekable() override;

	private:
		ov_callbacks vorbisCallbacks;	// Callbacks used to read the file from mem
		OggVorbis_File handle;			// Handle to the file
		vorbis_info* vorbisInfo = nullptr;
		vorbis_comment* vorbisComment = nullptr;
		int endian = 0;
	};
}
