#include "AudioStream.h"
#include "AudioSoundData.h"
#include "../Classes/XStream.h"
#include "../LSTG/ResourceMgr.h"

using namespace audio;
using lstg::XAudioStream;

// note: this implementation depends on LuaSTG-x

Stream* Stream::createFromFile(const std::string& path)
{
	const auto buffer = LRES.getBufferFromFile(path);
	if (!buffer)
		return nullptr;
	return XAudioStream::create(lstg::StreamMemory::create(buffer));
}

Stream* Stream::createFromLocalFile(const std::string& path)
{
	return XAudioStream::create(lstg::StreamFile::create(path, false));
}

Stream* Stream::createFromStringData(const std::string& str)
{
	const auto buffer = lstg::Buffer::createFromString(str);
	if (!buffer)
		return nullptr;
	return XAudioStream::create(lstg::StreamMemory::create(buffer));
}

Stream* Stream::createFromSoundData(SoundData* soundData)
{
	if(!soundData)
		return nullptr;
	const auto s = lstg::StreamMemory::create();
	if (!s)
		return nullptr;
	if (!s->resize(soundData->getSize()))
		return nullptr;
	// copy data
	if (!s->write((const uint8_t*)soundData->getData(), soundData->getSize(), nullptr))
		return nullptr;
	return XAudioStream::create(s);
}
