#include "AudioDecoderManager.h"
//#include "AudioDecoderMp3.h"
#include "AudioMacros.h"
#include "platform/CCFileUtils.h"
//#include "base/CCConsole.h"
#include "AudioDecoderWav.h"
#include "AudioDecoderOgg.h"

#define LOG_TAG "AudioDecoderManager"
using namespace xAudio;

bool AudioDecoderManager::init()
{
	return true;
}

void AudioDecoderManager::destroy()
{
	//AudioDecoderMp3::destroy();
}

AudioDecoder* AudioDecoderManager::createDecoder(const char* path)
{
	std::string suffix = cocos2d::FileUtils::getInstance()->getFileExtension(path);
	if (suffix == ".ogg")
	{
		return new (std::nothrow) AudioDecoderOgg();
	}
	if (suffix == ".wav")
	{
		return new (std::nothrow) AudioDecoderWav();
	}

	return nullptr;
}

void AudioDecoderManager::destroyDecoder(AudioDecoder* decoder)
{
	if(decoder)
	{
		if (decoder->isOpened())
		{
			decoder->seek(0);
			decoder->close();			
		}
		delete decoder;
	}
}

