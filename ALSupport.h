#pragma once
#include "AudioCommon.h"
#include <string>
#include <vector>

namespace audio
{
	class ALSupport
	{
		static void init();
	public:

		static std::string getReadableInfo();

		static std::string getDeviceName();
		static std::string getCaptureDeviceName();
		static std::vector<std::string> getDeviceNames();
		static std::vector<std::string> getCaptureDeviceNames();

		static ALenum getBufferFormat(const std::string& name);
		static bool hasALEXT(const std::string& name);
		static bool hasALCEXT(const std::string& name);
	};
}
