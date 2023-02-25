#pragma once
#include "base/ccConfig.h"
#include "lua_conversion.hpp"

extern int luaReg_audio_audioSource(lua_State* lua_S);
extern int luaReg_audio_audioStream(lua_State* lua_S);
extern int luaReg_audio_audioDecoder(lua_State* lua_S);
extern int luaReg_audio_audioSoundData(lua_State* lua_S);
extern int luaReg_audio_audioRecordingDevice(lua_State* lua_S);
extern int luaReg_audio_audioEngine(lua_State* lua_S);

inline int register_all_cc_audio(lua_State* lua_S)
{
	luaReg_audio_audioSource(lua_S);
	luaReg_audio_audioStream(lua_S);
	luaReg_audio_audioDecoder(lua_S);
	luaReg_audio_audioSoundData(lua_S);
	luaReg_audio_audioRecordingDevice(lua_S);
	luaReg_audio_audioEngine(lua_S);
	return 0;
}
