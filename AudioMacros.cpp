#include "AudioMacros.h"

lstg::LogSystem& AudioLogger()
{
	static lstg::LogSystem ALogger{ "audio_log.txt" };
	return ALogger;
}
