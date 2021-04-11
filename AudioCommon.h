#pragma once
#include "platform/CCPlatformConfig.h"
#include <functional>
#include <string>

namespace audio
{
	std::string string_format(const char* format, ...);
	void setLoggingFunction(const std::function<void(const std::string&)>& callback);
	void logging(const char* format, ...);
	const char* getErrorString(int errorCode);

	void setOnRequestRecordPermission(const std::function<bool()>& callback);
	bool requestRecordAudioPermission();
}

#define AINFO(_str, ...) audio::logging("[AINFO] [%s] " _str, __FUNCTION__, ##__VA_ARGS__)
#define AWARN(_str,...) audio::logging("[AWARN] [%s] " _str, __FUNCTION__, ##__VA_ARGS__)
#define AERRO(_str, ...) audio::logging("[AERRO] [%s] " _str, __FUNCTION__, ##__VA_ARGS__)

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
//#include "AL/efx.h"
//#include "AL/efx-presets.h"
