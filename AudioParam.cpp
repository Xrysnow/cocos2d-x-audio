#include "AudioParam.h"
#include "AudioMacros.h"

using namespace xAudio;

const SourceParam SourceParam::DEFAULT;
const ListenerParam ListenerParam::DEFAULT;

lstg::LogSystem& AudioLogger()
{
	static lstg::LogSystem ALogger{ "audio_log.txt" };
	return ALogger;
}
