#include "AudioCommon.h"
#include <cstdarg>
#include <cassert>

using namespace audio;

namespace
{
	std::function<void(const std::string&)> AudioLoggingFunction;
	std::function<bool()> AudioRequestRecordPermissionFunction;
	enum class RecordPermissionState { UNKNOWN, GRANTED, DENIED };
	RecordPermissionState AudioRecordPermissionState = RecordPermissionState::UNKNOWN;
}

std::string audio::string_format(const char* format, ...)
{
	constexpr auto BUFFER_LENGTH = 512;
	va_list args;
	std::string buffer(BUFFER_LENGTH, '\0');

	va_start(args, format);
	int nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
	va_end(args);

	if (nret >= 0) {
		if ((unsigned int)nret < buffer.length()) {
			buffer.resize(nret);
		}
		else if ((unsigned int)nret > buffer.length()) { // VS2015/2017 or later Visual Studio Version
			buffer.resize(nret);

			va_start(args, format);
			nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
			va_end(args);

			assert(nret == buffer.length());
		}
		// else equals, do nothing.
	}
	else { // less or equal VS2013 and Unix System glibc implement.
		do {
			buffer.resize(buffer.length() * 3 / 2);

			va_start(args, format);
			nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
			va_end(args);

		} while (nret < 0);

		buffer.resize(nret);
	}

	return buffer;
}

void audio::setLoggingFunction(const std::function<void(const std::string&)>& callback)
{
	AudioLoggingFunction = callback;
}

void audio::logging(const char* format, ...)
{
	if (!AudioLoggingFunction)
		return;
	constexpr auto BUFFER_LENGTH = 512;
	va_list args;
	std::string buffer(BUFFER_LENGTH, '\0');

	va_start(args, format);
	int nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
	va_end(args);

	if (nret >= 0) {
		if ((unsigned int)nret < buffer.length()) {
			buffer.resize(nret);
		}
		else if ((unsigned int)nret > buffer.length()) { // VS2015/2017 or later Visual Studio Version
			buffer.resize(nret);

			va_start(args, format);
			nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
			va_end(args);

			assert(nret == buffer.length());
		}
		// else equals, do nothing.
	}
	else { // less or equal VS2013 and Unix System glibc implement.
		do {
			buffer.resize(buffer.length() * 3 / 2);

			va_start(args, format);
			nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
			va_end(args);

		} while (nret < 0);

		buffer.resize(nret);
	}
	AudioLoggingFunction(buffer);
}

const char* audio::getErrorString(int errorCode)
{
	switch (errorCode)
	{
	case AL_NO_ERROR: return "no error";
	case AL_INVALID_NAME: return "invalid name";
	case AL_INVALID_ENUM: return "invalid enum";
	case AL_INVALID_VALUE: return "invalid value";
	case AL_INVALID_OPERATION: return "invalid operation";
	case AL_OUT_OF_MEMORY: return "out of memory";
	default: return "unknown error";
	}
}

void audio::setOnRequestRecordPermission(const std::function<bool()>& callback)
{
	AudioRequestRecordPermissionFunction = callback;
}

bool audio::requestRecordAudioPermission()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	if (AudioRecordPermissionState != RecordPermissionState::UNKNOWN)
		return AudioRecordPermissionState == RecordPermissionState::GRANTED;
	if (AudioRequestRecordPermissionFunction)
	{
		const auto ret = AudioRequestRecordPermissionFunction();
		AudioRecordPermissionState = ret ? RecordPermissionState::GRANTED : RecordPermissionState::DENIED;
		return ret;
	}
#endif
	return true;
}
