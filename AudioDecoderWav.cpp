#include "AudioDecoderWav.h"
#include "RiffUtils.h"
#include "IMA4Util.h"
#include "AudioMacros.h"

#define LOG_TAG "AudioDecoderWav"

using namespace std;
using namespace xAudio;
using namespace nqr;

const uint32_t CKC_RIFF = GenerateChunkCode('R', 'I', 'F', 'F');
const uint32_t CKC_RIFX = GenerateChunkCode('R', 'I', 'F', 'X');
const uint32_t CKC_FFIR = GenerateChunkCode('F', 'F', 'I', 'R');
const uint32_t CKC_WAVE = GenerateChunkCode('W', 'A', 'V', 'E');
const uint32_t CKC_fmt_ = GenerateChunkCode('f', 'm', 't', ' ');
const uint32_t CKC_fact = GenerateChunkCode('f', 'a', 'c', 't');
const uint32_t CKC_bext = GenerateChunkCode('b', 'e', 'x', 't');
const uint32_t CKC_data = GenerateChunkCode('d', 'a', 't', 'a');

bool AudioDecoderWav::open(AudioStream* src, double loopA, double loopB)
{
	if (_isOpened || !src)
		return false;
	stream = src;
	string msg;
	uint8_t* tempBuffer = nullptr;
	bool ret = false;
	stream->lock();
	do
	{
		stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
		auto size = stream->size();

		// Read RIFF Header
		RiffChunkHeader riffHeader = {};
		stream->read((uint8_t*)&riffHeader, 12);
		// Check RIFF
		if (riffHeader.id_riff != CKC_RIFF){
			if (riffHeader.id_riff == CKC_RIFX || riffHeader.id_riff == CKC_FFIR){
				msg = "doesn't support big endian file"; break;
			}
			msg = "bad RIFF/RIFX/FFIR file header"; break;
		}

		if (riffHeader.id_wave != CKC_WAVE){
			msg = "bad WAVE header"; break;
		}
		auto expectedSize = size - riffHeader.file_size;
		if (expectedSize != sizeof(uint32_t) * 2){
			msg = "declared size of file dosn't match real size"; break;
		}
		// note: assume that header is smaller than 256B
		tempBuffer = (uint8_t*)malloc(256);
		uint64_t bufferLength;
		stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
		stream->read(tempBuffer, 256, &bufferLength);

		// Read WAVE Header
		auto WaveChunkInfo = ScanForChunk(tempBuffer, bufferLength, CKC_fmt_);
		if (WaveChunkInfo.offset == 0) {
			msg = "couldn't find fmt chunk"; break;
		}
		CC_ASSERT(WaveChunkInfo.size == 16 || WaveChunkInfo.size == 18 ||
			WaveChunkInfo.size == 20 || WaveChunkInfo.size == 40);
		WaveChunkHeader wavHeader = {};
		memcpy(&wavHeader, tempBuffer + WaveChunkInfo.offset, sizeof(WaveChunkHeader));

		if (wavHeader.chunk_size < 16) {
			msg = "format chunk too small"; break;
		}
		//@todo validate wav header (sane sample rate, bit depth, etc)

		sourceInfo.channelCount = wavHeader.channel_count;
		sourceInfo.sampleRate = wavHeader.sample_rate;
		sourceInfo.bytesPerFrame = wavHeader.frame_size;
		auto bit_depth = wavHeader.bit_depth;
		CC_ASSERT(sourceInfo.channelCount*bit_depth/8 == wavHeader.frame_size);
		if (bit_depth != 16) {
			// todo: not implemented
			msg = "only support 16bit format, got " + to_string(bit_depth) + "bit"; break;
		}

		bool scanForFact = false;
		bool grabExtensibleData = false;
		//bool adpcmEncoded = false;
		if (wavHeader.format == FORMAT_PCM)
		{
		}
		else if (wavHeader.format == FORMAT_IEEE)
		{
			scanForFact = true;
		}
		else if (wavHeader.format == FORMAT_IMA_ADPCM)
		{
			//adpcmEncoded = true;
			//scanForFact = true;
			// todo: not implemented
			msg = "not support ADPCM format"; break;
		}
		else if (wavHeader.format == FORMAT_EXT)
		{
			// Used when (1) PCM data has more than 16 bits; (2) channels > 2;
			// (3) bits/sample !== container size; (4) channel/speaker mapping specified
			//std::cout << "[format id] extended" << std::endl;
			scanForFact = true;
			grabExtensibleData = true;
		}
		else if (wavHeader.format == FORMAT_UNKNOWN) {
			msg = "unknown wave format"; break;
		}

		// Read Additional Chunks
		FactChunk factChunk;
		if (scanForFact)
		{
			auto FactChunkInfo = ScanForChunk(tempBuffer, bufferLength, CKC_fact);
			if (FactChunkInfo.size)
				memcpy(&factChunk, tempBuffer + FactChunkInfo.offset, sizeof(FactChunk));
		}
		if (grabExtensibleData)
		{
			ExtensibleData extData = {};
			memcpy(&extData, tempBuffer + WaveChunkInfo.offset + sizeof(WaveChunkHeader), sizeof(ExtensibleData));
			// extData can be compared against the multi-channel masks defined in the header
			// eg. extData.channel_mask == SPEAKER_5POINT1
		}

		// Read Bext Chunk
		auto BextChunkInfo = ScanForChunk(tempBuffer, bufferLength, CKC_bext);
		BextChunk bextChunk = {};
		if (BextChunkInfo.size)
			memcpy(&bextChunk, tempBuffer + BextChunkInfo.offset, sizeof(BextChunk));

		// Read DATA Chunk
		auto DataChunkInfo = ScanForChunk(tempBuffer, bufferLength, CKC_data);
		if (DataChunkInfo.offset == 0) {
			msg = "couldn't find data chunk |size=" + to_string(stream->size()) +
				"|temp buf size=" + to_string(bufferLength); break;
		}
		uint32_t data_size;
		memcpy(&data_size, tempBuffer + DataChunkInfo.offset + sizeof(uint32_t), sizeof(uint32_t));
		data_offset = DataChunkInfo.offset + 2 * sizeof(uint32_t);// skip the header and size fields
		// note: there may be some info at file tail, only use data_size
		if (data_size != stream->size() - data_offset)
		{
			msg = "data size mismatch. expect " + to_string(data_size) +
				", got " + to_string(stream->size() - data_offset);
			data_size = min(data_size, uint32_t(stream->size() - data_offset));
		}
		//if (adpcmEncoded){}
		sourceInfo.totalFrames = data_size / wavHeader.frame_size;
		stream->seek(AudioStream::SeekOrigin::BEGINNING, data_offset);
		stream->retain();
		calcLoopAB(loopA, loopB);
		_isOpened = true;
		ret = true;
	}
	while (false);
	stream->unlock();
	if (tempBuffer)free(tempBuffer);
	if (!msg.empty())
	{
		ALOGV("[AudioDecoderWav::open] %s", msg.c_str());
	}
	return ret;
}

void AudioDecoderWav::close()
{
	if (_isOpened)
	{
		_isOpened = false;
		if (stream)
		{
			stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
			stream->release();
			stream = nullptr;
		}
	}
}

uint32_t AudioDecoderWav::read(uint32_t framesToRead, char* pcmBuf)
{
	uint32_t ret = 0;
	uint32_t bytesToRead = framesToRead * sourceInfo.bytesPerFrame;
	if (_isABLoop && !in_read_loop)
	{
		ret = read_loop(framesToRead, pcmBuf);
	}
	else if (stream)
	{
		stream->lock(); // 锁定流

		uint32_t tSizeRead = 0;
		auto tBuffer = (uint8_t*)pcmBuf;
		while (tSizeRead < bytesToRead)
		{
			uint64_t tRet;
			stream->read(tBuffer, bytesToRead - tSizeRead, &tRet);
			if (tRet == 0)  // 到尾部
				break;
			tSizeRead += tRet;
			tBuffer += tRet;
		}

		stream->unlock();
		ret = tSizeRead / sourceInfo.bytesPerFrame;
	}

	return ret;
}

bool AudioDecoderWav::seek(uint32_t frameOffset)
{
	if (frameOffset >= sourceInfo.totalFrames)
		return false;
	//ALOGV("[AudioDecoderWav::seek] Seek %u.", frameOffset);
	return stream->seek(AudioStream::SeekOrigin::BEGINNING, data_offset + frameOffset * sourceInfo.bytesPerFrame);
}

uint32_t AudioDecoderWav::tell() const
{
	int32_t p = stream->tell() - data_offset;
	return max(0, p) / sourceInfo.bytesPerFrame;
}

uint32_t AudioDecoderWav::fixLength(vector<uint8_t>* buffer)
{
	// do not fix length
	if (buffer)buffer->clear();
	return 0;
}

AudioDecoderWav::AudioDecoderWav()
{
}

AudioDecoderWav::~AudioDecoderWav()
{
	AudioDecoderWav::close();
}
