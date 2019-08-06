#pragma once
#include "AudioDecoder.h"
#include "AudioStream.h"
#define OV_EXCLUDE_STATIC_CALLBACKS
#include "../../external/OggDecoder/include/vorbis/codec.h"
#include "../../external/OggDecoder/include/vorbis/vorbisfile.h"
#include <cstdint>

namespace audio
{
	// Struct for handling data
	struct SOggFile
	{
		const char *dataPtr;	// Pointer to the data in memory
		int64_t dataSize;	// Size of the data
		int64_t dataRead;	// How much we've read so far
	};

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
		//SOggFile oggFile;				// (see struct)
		ov_callbacks vorbisCallbacks;	// Callbacks used to read the file from mem
		OggVorbis_File handle;			// Handle to the file
		vorbis_info* vorbisInfo = nullptr;		// Info
		vorbis_comment* vorbisComment = nullptr;	// Comments
		int endian = 0;						// Endianness
	};
}
