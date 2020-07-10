#pragma once
#include "platform/CCPlatformConfig.h"
#include <functional>
#include <string>

namespace audio
{
	void setLoggingFunction(const std::function<void(const std::string&)>& callback);
	void logging(const char* format, ...);
	const char* getErrorString(int errorCode);

	void setOnRequestRecordPermission(const std::function<bool()>& callback);
	bool requestRecordAudioPermission();
}

#define AINFO(_str, ...) audio::logging("[AINFO] [%s] " _str, __FUNCTION__, ##__VA_ARGS__)
#define AWARN(_str,...) audio::logging("[AWARN] [%s] " _str, __FUNCTION__, ##__VA_ARGS__)
#define AERRO(_str, ...) audio::logging("[AERRO] [%s] " _str, __FUNCTION__, ##__VA_ARGS__)

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)||(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenAL/alext.h>
#else
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
//#include "AL/efx.h"
//#include "AL/efx-presets.h"
#endif
