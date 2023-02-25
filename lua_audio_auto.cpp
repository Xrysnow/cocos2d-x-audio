#include "lua_audio_auto.hpp"
#include "AudioEngine.h"

int lua_audio_Source_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:clone");
	LUA_TRY_INVOKE_R(0, &audio::Source::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getActiveEffects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getActiveEffects");
	LUA_TRY_INVOKE_R(0, &audio::Source::getActiveEffects);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getAirAbsorptionFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getAirAbsorptionFactor");
	LUA_TRY_INVOKE_R(0, &audio::Source::getAirAbsorptionFactor);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getBitDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getBitDepth");
	LUA_TRY_INVOKE_R(0, &audio::Source::getBitDepth);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getBytesPerFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getBytesPerFrame");
	LUA_TRY_INVOKE_R(0, &audio::Source::getBytesPerFrame);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getChannelCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getChannelCount");
	LUA_TRY_INVOKE_R(0, &audio::Source::getChannelCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getCone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getCone");
	LUA_TRY_INVOKE_R(0, &audio::Source::getCone);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getDirection");
	LUA_TRY_INVOKE_R(0, &audio::Source::getDirection);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getEffect");
	LUA_TRY_INVOKE_R(1, &audio::Source::getEffect);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_getFilter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getFilter");
	LUA_TRY_INVOKE_R(0, &audio::Source::getFilter);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getFreeBufferCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getFreeBufferCount");
	LUA_TRY_INVOKE_R(0, &audio::Source::getFreeBufferCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getLastError(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getLastError");
	LUA_TRY_INVOKE_R(0, &audio::Source::getLastError);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getLoopingEnd(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getLoopingEnd");
	LUA_TRY_INVOKE_R(0, &audio::Source::getLoopingEnd);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getLoopingStart(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getLoopingStart");
	LUA_TRY_INVOKE_R(0, &audio::Source::getLoopingStart);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getMaxDistance(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getMaxDistance");
	LUA_TRY_INVOKE_R(0, &audio::Source::getMaxDistance);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getMaxVolume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getMaxVolume");
	LUA_TRY_INVOKE_R(0, &audio::Source::getMaxVolume);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getMinVolume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getMinVolume");
	LUA_TRY_INVOKE_R(0, &audio::Source::getMinVolume);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getPitch(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getPitch");
	LUA_TRY_INVOKE_R(0, &audio::Source::getPitch);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getPosition");
	LUA_TRY_INVOKE_R(0, &audio::Source::getPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getReferenceDistance(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getReferenceDistance");
	LUA_TRY_INVOKE_R(0, &audio::Source::getReferenceDistance);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getRolloffFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getRolloffFactor");
	LUA_TRY_INVOKE_R(0, &audio::Source::getRolloffFactor);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getSampleRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getSampleRate");
	LUA_TRY_INVOKE_R(0, &audio::Source::getSampleRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getTime");
	LUA_TRY_INVOKE_R(0, &audio::Source::getTime);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getTotalFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getTotalFrames");
	LUA_TRY_INVOKE_R(0, &audio::Source::getTotalFrames);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getTotalTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getTotalTime");
	LUA_TRY_INVOKE_R(0, &audio::Source::getTotalTime);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getType");
	LUA_TRY_INVOKE_R(0, &audio::Source::getType);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getVelocity");
	LUA_TRY_INVOKE_R(0, &audio::Source::getVelocity);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_getVolume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:getVolume");
	LUA_TRY_INVOKE_R(0, &audio::Source::getVolume);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_isFinished(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:isFinished");
	LUA_TRY_INVOKE_R(0, &audio::Source::isFinished);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_isLooping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:isLooping");
	LUA_TRY_INVOKE_R(0, &audio::Source::isLooping);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_isPlaying(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:isPlaying");
	LUA_TRY_INVOKE_R(0, &audio::Source::isPlaying);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_isRelative(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:isRelative");
	LUA_TRY_INVOKE_R(0, &audio::Source::isRelative);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_isSupportLoopingPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:isSupportLoopingPoint");
	LUA_TRY_INVOKE_R(0, &audio::Source::isSupportLoopingPoint);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:pause");
	LUA_TRY_INVOKE(0, &audio::Source::pause);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_play(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:play");
	LUA_TRY_INVOKE_R(0, &audio::Source::play);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_queue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:queue");
	LUA_TRY_INVOKE_R(3, static_cast<bool(audio::Source::*)(audio::SoundData*, ssize_t, ssize_t)>(&audio::Source::queue));
	LUA_TRY_INVOKE_R(2, [](audio::Source* obj, audio::SoundData* arg0,ssize_t arg1){{return obj->queue(std::move(arg0),std::move(arg1));}});
	LUA_TRY_INVOKE_R(1, [](audio::Source* obj, audio::SoundData* arg0){{return obj->queue(arg0);}});
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_audio_Source_removeEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:removeEffect");
	LUA_TRY_INVOKE_R(1, &audio::Source::removeEffect);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_removeFilter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:removeFilter");
	LUA_TRY_INVOKE_R(0, &audio::Source::removeFilter);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_seek(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:seek");
	LUA_TRY_INVOKE(1, &audio::Source::seek);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setAirAbsorptionFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setAirAbsorptionFactor");
	LUA_TRY_INVOKE(1, &audio::Source::setAirAbsorptionFactor);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setCone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setCone");
	LUA_TRY_INVOKE(4, static_cast<void(audio::Source::*)(float, float, float, float)>(&audio::Source::setCone));
	LUA_TRY_INVOKE(1, static_cast<void(audio::Source::*)(const std::array<float, 4>&)>(&audio::Source::setCone));
	LUA_INVOKE_FOOTER("1,4");
}
int lua_audio_Source_setDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setDirection");
	LUA_TRY_INVOKE(1, &audio::Source::setDirection);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setEffect");
	LUA_TRY_INVOKE_R(2, static_cast<bool(audio::Source::*)(const std::string&, const audio::Filter::ParamMap&)>(&audio::Source::setEffect));
	LUA_TRY_INVOKE_R(1, static_cast<bool(audio::Source::*)(const std::string&)>(&audio::Source::setEffect));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_audio_Source_setFilter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setFilter");
	LUA_TRY_INVOKE_R(1, &audio::Source::setFilter);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setLooping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setLooping");
	LUA_TRY_INVOKE(1, &audio::Source::setLooping);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setLoopingPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setLoopingPoint");
	LUA_TRY_INVOKE(2, &audio::Source::setLoopingPoint);
	LUA_INVOKE_FOOTER("2");
}
int lua_audio_Source_setMaxDistance(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setMaxDistance");
	LUA_TRY_INVOKE(1, &audio::Source::setMaxDistance);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setMaxVolume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setMaxVolume");
	LUA_TRY_INVOKE(1, &audio::Source::setMaxVolume);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setMinVolume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setMinVolume");
	LUA_TRY_INVOKE(1, &audio::Source::setMinVolume);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setPitch(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setPitch");
	LUA_TRY_INVOKE(1, &audio::Source::setPitch);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setPosition");
	LUA_TRY_INVOKE(1, &audio::Source::setPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setReferenceDistance(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setReferenceDistance");
	LUA_TRY_INVOKE(1, &audio::Source::setReferenceDistance);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setRelative(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setRelative");
	LUA_TRY_INVOKE(1, &audio::Source::setRelative);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setRolloffFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setRolloffFactor");
	LUA_TRY_INVOKE(1, &audio::Source::setRolloffFactor);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setTime");
	LUA_TRY_INVOKE(1, &audio::Source::setTime);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setVelocity");
	LUA_TRY_INVOKE(1, &audio::Source::setVelocity);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_setVolume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:setVolume");
	LUA_TRY_INVOKE(1, &audio::Source::setVolume);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Source_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:stop");
	LUA_TRY_INVOKE(0, &audio::Source::stop);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_tell(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Source", "audio.Source:tell");
	LUA_TRY_INVOKE_R(0, &audio::Source::tell);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Source_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Source", "audio.Source:create");
	LUA_TRY_INVOKE_R(4, &audio::Source::create);
	LUA_SINVOKE_FOOTER("4");
}
int lua_audio_Source_createFromDecoder(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Source", "audio.Source:createFromDecoder");
	LUA_TRY_INVOKE_R(1, &audio::Source::createFromDecoder);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Source_createFromSoundData(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Source", "audio.Source:createFromSoundData");
	LUA_TRY_INVOKE_R(1, &audio::Source::createFromSoundData);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Source_pauseAll(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Source", "audio.Source:pauseAll");
	LUA_TRY_INVOKE_R(0, &audio::Source::pauseAll);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Source_pauseBatch(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Source", "audio.Source:pauseBatch");
	LUA_TRY_INVOKE(1, &audio::Source::pauseBatch);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Source_playBatch(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Source", "audio.Source:playBatch");
	LUA_TRY_INVOKE_R(1, &audio::Source::playBatch);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Source_stopAll(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Source", "audio.Source:stopAll");
	LUA_TRY_INVOKE(0, &audio::Source::stopAll);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Source_stopBatch(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Source", "audio.Source:stopBatch");
	LUA_TRY_INVOKE(1, &audio::Source::stopBatch);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_audio_audioSource(lua_State* lua_S)
{
	LUA_ENTRY("audio");
	LUA_CLS_DEF_BASE(audio::Source, "Source", "audio.Source",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_audio_Source_clone);
	LUA_METHOD("getActiveEffects", lua_audio_Source_getActiveEffects);
	LUA_METHOD("getAirAbsorptionFactor", lua_audio_Source_getAirAbsorptionFactor);
	LUA_METHOD("getBitDepth", lua_audio_Source_getBitDepth);
	LUA_METHOD("getBytesPerFrame", lua_audio_Source_getBytesPerFrame);
	LUA_METHOD("getChannelCount", lua_audio_Source_getChannelCount);
	LUA_METHOD("getCone", lua_audio_Source_getCone);
	LUA_METHOD("getDirection", lua_audio_Source_getDirection);
	LUA_METHOD("getEffect", lua_audio_Source_getEffect);
	LUA_METHOD("getFilter", lua_audio_Source_getFilter);
	LUA_METHOD("getFreeBufferCount", lua_audio_Source_getFreeBufferCount);
	LUA_METHOD("getLastError", lua_audio_Source_getLastError);
	LUA_METHOD("getLoopingEnd", lua_audio_Source_getLoopingEnd);
	LUA_METHOD("getLoopingStart", lua_audio_Source_getLoopingStart);
	LUA_METHOD("getMaxDistance", lua_audio_Source_getMaxDistance);
	LUA_METHOD("getMaxVolume", lua_audio_Source_getMaxVolume);
	LUA_METHOD("getMinVolume", lua_audio_Source_getMinVolume);
	LUA_METHOD("getPitch", lua_audio_Source_getPitch);
	LUA_METHOD("getPosition", lua_audio_Source_getPosition);
	LUA_METHOD("getReferenceDistance", lua_audio_Source_getReferenceDistance);
	LUA_METHOD("getRolloffFactor", lua_audio_Source_getRolloffFactor);
	LUA_METHOD("getSampleRate", lua_audio_Source_getSampleRate);
	LUA_METHOD("getTime", lua_audio_Source_getTime);
	LUA_METHOD("getTotalFrames", lua_audio_Source_getTotalFrames);
	LUA_METHOD("getTotalTime", lua_audio_Source_getTotalTime);
	LUA_METHOD("getType", lua_audio_Source_getType);
	LUA_METHOD("getVelocity", lua_audio_Source_getVelocity);
	LUA_METHOD("getVolume", lua_audio_Source_getVolume);
	LUA_METHOD("isFinished", lua_audio_Source_isFinished);
	LUA_METHOD("isLooping", lua_audio_Source_isLooping);
	LUA_METHOD("isPlaying", lua_audio_Source_isPlaying);
	LUA_METHOD("isRelative", lua_audio_Source_isRelative);
	LUA_METHOD("isSupportLoopingPoint", lua_audio_Source_isSupportLoopingPoint);
	LUA_METHOD("pause", lua_audio_Source_pause);
	LUA_METHOD("play", lua_audio_Source_play);
	LUA_METHOD("queue", lua_audio_Source_queue);
	LUA_METHOD("removeEffect", lua_audio_Source_removeEffect);
	LUA_METHOD("removeFilter", lua_audio_Source_removeFilter);
	LUA_METHOD("seek", lua_audio_Source_seek);
	LUA_METHOD("setAirAbsorptionFactor", lua_audio_Source_setAirAbsorptionFactor);
	LUA_METHOD("setCone", lua_audio_Source_setCone);
	LUA_METHOD("setDirection", lua_audio_Source_setDirection);
	LUA_METHOD("setEffect", lua_audio_Source_setEffect);
	LUA_METHOD("setFilter", lua_audio_Source_setFilter);
	LUA_METHOD("setLooping", lua_audio_Source_setLooping);
	LUA_METHOD("setLoopingPoint", lua_audio_Source_setLoopingPoint);
	LUA_METHOD("setMaxDistance", lua_audio_Source_setMaxDistance);
	LUA_METHOD("setMaxVolume", lua_audio_Source_setMaxVolume);
	LUA_METHOD("setMinVolume", lua_audio_Source_setMinVolume);
	LUA_METHOD("setPitch", lua_audio_Source_setPitch);
	LUA_METHOD("setPosition", lua_audio_Source_setPosition);
	LUA_METHOD("setReferenceDistance", lua_audio_Source_setReferenceDistance);
	LUA_METHOD("setRelative", lua_audio_Source_setRelative);
	LUA_METHOD("setRolloffFactor", lua_audio_Source_setRolloffFactor);
	LUA_METHOD("setTime", lua_audio_Source_setTime);
	LUA_METHOD("setVelocity", lua_audio_Source_setVelocity);
	LUA_METHOD("setVolume", lua_audio_Source_setVolume);
	LUA_METHOD("stop", lua_audio_Source_stop);
	LUA_METHOD("tell", lua_audio_Source_tell);
	LUA_METHOD("create", lua_audio_Source_create);
	LUA_METHOD("createFromDecoder", lua_audio_Source_createFromDecoder);
	LUA_METHOD("createFromSoundData", lua_audio_Source_createFromSoundData);
	LUA_METHOD("pauseAll", lua_audio_Source_pauseAll);
	LUA_METHOD("pauseBatch", lua_audio_Source_pauseBatch);
	LUA_METHOD("playBatch", lua_audio_Source_playBatch);
	LUA_METHOD("stopAll", lua_audio_Source_stopAll);
	LUA_METHOD("stopBatch", lua_audio_Source_stopBatch);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_audio_Stream_lock(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Stream", "audio.Stream:lock");
	LUA_TRY_INVOKE(0, &audio::Stream::lock);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Stream_seek(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Stream", "audio.Stream:seek");
	LUA_TRY_INVOKE_R(2, &audio::Stream::seek);
	LUA_INVOKE_FOOTER("2");
}
int lua_audio_Stream_size(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Stream", "audio.Stream:size");
	LUA_TRY_INVOKE_R(0, &audio::Stream::size);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Stream_tell(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Stream", "audio.Stream:tell");
	LUA_TRY_INVOKE_R(0, &audio::Stream::tell);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Stream_unlock(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Stream", "audio.Stream:unlock");
	LUA_TRY_INVOKE(0, &audio::Stream::unlock);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Stream_createFromFile(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Stream", "audio.Stream:createFromFile");
	LUA_TRY_INVOKE_R(1, &audio::Stream::createFromFile);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Stream_createFromLocalFile(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Stream", "audio.Stream:createFromLocalFile");
	LUA_TRY_INVOKE_R(1, &audio::Stream::createFromLocalFile);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Stream_createFromSoundData(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Stream", "audio.Stream:createFromSoundData");
	LUA_TRY_INVOKE_R(1, &audio::Stream::createFromSoundData);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Stream_createFromStringData(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Stream", "audio.Stream:createFromStringData");
	LUA_TRY_INVOKE_R(1, &audio::Stream::createFromStringData);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_audio_audioStream(lua_State* lua_S)
{
	LUA_ENTRY("audio");
	LUA_CLS_DEF_BASE(audio::Stream, "Stream", "audio.Stream",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("lock", lua_audio_Stream_lock);
	LUA_METHOD("seek", lua_audio_Stream_seek);
	LUA_METHOD("size", lua_audio_Stream_size);
	LUA_METHOD("tell", lua_audio_Stream_tell);
	LUA_METHOD("unlock", lua_audio_Stream_unlock);
	LUA_METHOD("createFromFile", lua_audio_Stream_createFromFile);
	LUA_METHOD("createFromLocalFile", lua_audio_Stream_createFromLocalFile);
	LUA_METHOD("createFromSoundData", lua_audio_Stream_createFromSoundData);
	LUA_METHOD("createFromStringData", lua_audio_Stream_createFromStringData);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_audio_Decoder_DEFAULT_BIT_DEPTH_getter(lua_State* lua_S)
{
	LUA_CUR_FNAME("audio.Decoder.DEFAULT_BIT_DEPTH/getter");
	LUA_PUSH_NATIVE(audio::Decoder::DEFAULT_BIT_DEPTH);
	return 1;
}
int lua_audio_Decoder_DEFAULT_BUFFER_SIZE_getter(lua_State* lua_S)
{
	LUA_CUR_FNAME("audio.Decoder.DEFAULT_BUFFER_SIZE/getter");
	LUA_PUSH_NATIVE(audio::Decoder::DEFAULT_BUFFER_SIZE);
	return 1;
}
int lua_audio_Decoder_DEFAULT_CHANNELS_getter(lua_State* lua_S)
{
	LUA_CUR_FNAME("audio.Decoder.DEFAULT_CHANNELS/getter");
	LUA_PUSH_NATIVE(audio::Decoder::DEFAULT_CHANNELS);
	return 1;
}
int lua_audio_Decoder_DEFAULT_SAMPLE_RATE_getter(lua_State* lua_S)
{
	LUA_CUR_FNAME("audio.Decoder.DEFAULT_SAMPLE_RATE/getter");
	LUA_PUSH_NATIVE(audio::Decoder::DEFAULT_SAMPLE_RATE);
	return 1;
}
int lua_audio_Decoder_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:clone");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_getBitDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:getBitDepth");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::getBitDepth);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_getBufferSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:getBufferSize");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::getBufferSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_getBytesPerFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:getBytesPerFrame");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::getBytesPerFrame);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_getChannelCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:getChannelCount");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::getChannelCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:getDuration");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::getDuration);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_getLoopingEnd(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:getLoopingEnd");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::getLoopingEnd);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_getLoopingStart(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:getLoopingStart");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::getLoopingStart);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_getSampleRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:getSampleRate");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::getSampleRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_getTotalFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:getTotalFrames");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::getTotalFrames);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_isFinished(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:isFinished");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::isFinished);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_isSeekable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:isSeekable");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::isSeekable);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_rewind(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:rewind");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::rewind);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_seek(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:seek");
	LUA_TRY_INVOKE_R(1, &audio::Decoder::seek);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Decoder_seekTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:seekTime");
	LUA_TRY_INVOKE_R(1, &audio::Decoder::seekTime);
	LUA_INVOKE_FOOTER("1");
}
int lua_audio_Decoder_tell(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.Decoder", "audio.Decoder:tell");
	LUA_TRY_INVOKE_R(0, &audio::Decoder::tell);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_Decoder_createFromFile(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Decoder", "audio.Decoder:createFromFile");
	LUA_TRY_INVOKE_R(3, static_cast<audio::Decoder*(*)(const std::string&, size_t, audio::Decoder::DecoderType)>(&audio::Decoder::createFromFile));
	LUA_TRY_INVOKE_R(2, [](const std::string& arg0,size_t arg1){{return audio::Decoder::createFromFile(arg0,std::move(arg1));}});
	LUA_SINVOKE_FOOTER("2,3");
}
int lua_audio_Decoder_createFromLocalFile(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Decoder", "audio.Decoder:createFromLocalFile");
	LUA_TRY_INVOKE_R(3, static_cast<audio::Decoder*(*)(const std::string&, size_t, audio::Decoder::DecoderType)>(&audio::Decoder::createFromLocalFile));
	LUA_TRY_INVOKE_R(2, [](const std::string& arg0,size_t arg1){{return audio::Decoder::createFromLocalFile(arg0,std::move(arg1));}});
	LUA_SINVOKE_FOOTER("2,3");
}
int lua_audio_Decoder_createFromSoundData(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Decoder", "audio.Decoder:createFromSoundData");
	LUA_TRY_INVOKE_R(3, &audio::Decoder::createFromSoundData);
	LUA_SINVOKE_FOOTER("3");
}
int lua_audio_Decoder_createFromStream(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Decoder", "audio.Decoder:createFromStream");
	LUA_TRY_INVOKE_R(3, &audio::Decoder::createFromStream);
	LUA_SINVOKE_FOOTER("3");
}
int lua_audio_Decoder_createFromStringData(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Decoder", "audio.Decoder:createFromStringData");
	LUA_TRY_INVOKE_R(3, &audio::Decoder::createFromStringData);
	LUA_SINVOKE_FOOTER("3");
}
int lua_audio_Decoder_getDecoderTypeFromPath(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Decoder", "audio.Decoder:getDecoderTypeFromPath");
	LUA_TRY_INVOKE_R(1, &audio::Decoder::getDecoderTypeFromPath);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_audio_audioDecoder(lua_State* lua_S)
{
	LUA_ENTRY("audio");
	LUA_CLS_DEF_BASE(audio::Decoder, "Decoder", "audio.Decoder",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_SFIELD("DEFAULT_BIT_DEPTH", lua_audio_Decoder_DEFAULT_BIT_DEPTH_getter, nullptr);
	LUA_SFIELD("DEFAULT_BUFFER_SIZE", lua_audio_Decoder_DEFAULT_BUFFER_SIZE_getter, nullptr);
	LUA_SFIELD("DEFAULT_CHANNELS", lua_audio_Decoder_DEFAULT_CHANNELS_getter, nullptr);
	LUA_SFIELD("DEFAULT_SAMPLE_RATE", lua_audio_Decoder_DEFAULT_SAMPLE_RATE_getter, nullptr);
	LUA_METHOD("clone", lua_audio_Decoder_clone);
	LUA_METHOD("getBitDepth", lua_audio_Decoder_getBitDepth);
	LUA_METHOD("getBufferSize", lua_audio_Decoder_getBufferSize);
	LUA_METHOD("getBytesPerFrame", lua_audio_Decoder_getBytesPerFrame);
	LUA_METHOD("getChannelCount", lua_audio_Decoder_getChannelCount);
	LUA_METHOD("getDuration", lua_audio_Decoder_getDuration);
	LUA_METHOD("getLoopingEnd", lua_audio_Decoder_getLoopingEnd);
	LUA_METHOD("getLoopingStart", lua_audio_Decoder_getLoopingStart);
	LUA_METHOD("getSampleRate", lua_audio_Decoder_getSampleRate);
	LUA_METHOD("getTotalFrames", lua_audio_Decoder_getTotalFrames);
	LUA_METHOD("isFinished", lua_audio_Decoder_isFinished);
	LUA_METHOD("isSeekable", lua_audio_Decoder_isSeekable);
	LUA_METHOD("rewind", lua_audio_Decoder_rewind);
	LUA_METHOD("seek", lua_audio_Decoder_seek);
	LUA_METHOD("seekTime", lua_audio_Decoder_seekTime);
	LUA_METHOD("tell", lua_audio_Decoder_tell);
	LUA_METHOD("createFromFile", lua_audio_Decoder_createFromFile);
	LUA_METHOD("createFromLocalFile", lua_audio_Decoder_createFromLocalFile);
	LUA_METHOD("createFromSoundData", lua_audio_Decoder_createFromSoundData);
	LUA_METHOD("createFromStream", lua_audio_Decoder_createFromStream);
	LUA_METHOD("createFromStringData", lua_audio_Decoder_createFromStringData);
	LUA_METHOD("getDecoderTypeFromPath", lua_audio_Decoder_getDecoderTypeFromPath);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_audio_SoundData_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.SoundData", "audio.SoundData:clone");
	LUA_TRY_INVOKE_R(0, &audio::SoundData::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_SoundData_getBitDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.SoundData", "audio.SoundData:getBitDepth");
	LUA_TRY_INVOKE_R(0, &audio::SoundData::getBitDepth);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_SoundData_getChannelCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.SoundData", "audio.SoundData:getChannelCount");
	LUA_TRY_INVOKE_R(0, &audio::SoundData::getChannelCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_SoundData_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.SoundData", "audio.SoundData:getDuration");
	LUA_TRY_INVOKE_R(0, &audio::SoundData::getDuration);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_SoundData_getLastError(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.SoundData", "audio.SoundData:getLastError");
	LUA_TRY_INVOKE_R(0, &audio::SoundData::getLastError);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_SoundData_getSample(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.SoundData", "audio.SoundData:getSample");
	LUA_TRY_INVOKE_R(2, static_cast<float(audio::SoundData::*)(int, int)>(&audio::SoundData::getSample));
	LUA_TRY_INVOKE_R(1, static_cast<float(audio::SoundData::*)(int)>(&audio::SoundData::getSample));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_audio_SoundData_getSampleCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.SoundData", "audio.SoundData:getSampleCount");
	LUA_TRY_INVOKE_R(0, &audio::SoundData::getSampleCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_SoundData_getSampleRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.SoundData", "audio.SoundData:getSampleRate");
	LUA_TRY_INVOKE_R(0, &audio::SoundData::getSampleRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_SoundData_getSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.SoundData", "audio.SoundData:getSize");
	LUA_TRY_INVOKE_R(0, &audio::SoundData::getSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_SoundData_setSample(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.SoundData", "audio.SoundData:setSample");
	LUA_TRY_INVOKE(3, static_cast<void(audio::SoundData::*)(int, int, float)>(&audio::SoundData::setSample));
	LUA_TRY_INVOKE(2, static_cast<void(audio::SoundData::*)(int, float)>(&audio::SoundData::setSample));
	LUA_INVOKE_FOOTER("2,3");
}
int luaReg_audio_audioSoundData(lua_State* lua_S)
{
	LUA_ENTRY("audio");
	LUA_CLS_DEF(audio::SoundData, "SoundData", "audio.SoundData",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_audio_SoundData_clone);
	LUA_METHOD("getBitDepth", lua_audio_SoundData_getBitDepth);
	LUA_METHOD("getChannelCount", lua_audio_SoundData_getChannelCount);
	LUA_METHOD("getDuration", lua_audio_SoundData_getDuration);
	LUA_METHOD("getLastError", lua_audio_SoundData_getLastError);
	LUA_METHOD("getSample", lua_audio_SoundData_getSample);
	LUA_METHOD("getSampleCount", lua_audio_SoundData_getSampleCount);
	LUA_METHOD("getSampleRate", lua_audio_SoundData_getSampleRate);
	LUA_METHOD("getSize", lua_audio_SoundData_getSize);
	LUA_METHOD("setSample", lua_audio_SoundData_setSample);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_audio_RecordingDevice_DEFAULT_BIT_DEPTH_getter(lua_State* lua_S)
{
	LUA_CUR_FNAME("audio.RecordingDevice.DEFAULT_BIT_DEPTH/getter");
	LUA_PUSH_NATIVE(audio::RecordingDevice::DEFAULT_BIT_DEPTH);
	return 1;
}
int lua_audio_RecordingDevice_DEFAULT_CHANNELS_getter(lua_State* lua_S)
{
	LUA_CUR_FNAME("audio.RecordingDevice.DEFAULT_CHANNELS/getter");
	LUA_PUSH_NATIVE(audio::RecordingDevice::DEFAULT_CHANNELS);
	return 1;
}
int lua_audio_RecordingDevice_DEFAULT_SAMPLES_getter(lua_State* lua_S)
{
	LUA_CUR_FNAME("audio.RecordingDevice.DEFAULT_SAMPLES/getter");
	LUA_PUSH_NATIVE(audio::RecordingDevice::DEFAULT_SAMPLES);
	return 1;
}
int lua_audio_RecordingDevice_DEFAULT_SAMPLE_RATE_getter(lua_State* lua_S)
{
	LUA_CUR_FNAME("audio.RecordingDevice.DEFAULT_SAMPLE_RATE/getter");
	LUA_PUSH_NATIVE(audio::RecordingDevice::DEFAULT_SAMPLE_RATE);
	return 1;
}
int lua_audio_RecordingDevice_getBitDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.RecordingDevice", "audio.RecordingDevice:getBitDepth");
	LUA_TRY_INVOKE_R(0, &audio::RecordingDevice::getBitDepth);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_RecordingDevice_getChannelCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.RecordingDevice", "audio.RecordingDevice:getChannelCount");
	LUA_TRY_INVOKE_R(0, &audio::RecordingDevice::getChannelCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_RecordingDevice_getData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.RecordingDevice", "audio.RecordingDevice:getData");
	LUA_TRY_INVOKE_R(0, &audio::RecordingDevice::getData);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_RecordingDevice_getMaxSamples(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.RecordingDevice", "audio.RecordingDevice:getMaxSamples");
	LUA_TRY_INVOKE_R(0, &audio::RecordingDevice::getMaxSamples);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_RecordingDevice_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.RecordingDevice", "audio.RecordingDevice:getName");
	LUA_TRY_INVOKE_R(0, &audio::RecordingDevice::getName);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_RecordingDevice_getSampleCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.RecordingDevice", "audio.RecordingDevice:getSampleCount");
	LUA_TRY_INVOKE_R(0, &audio::RecordingDevice::getSampleCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_RecordingDevice_getSampleRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.RecordingDevice", "audio.RecordingDevice:getSampleRate");
	LUA_TRY_INVOKE_R(0, &audio::RecordingDevice::getSampleRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_RecordingDevice_isRecording(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.RecordingDevice", "audio.RecordingDevice:isRecording");
	LUA_TRY_INVOKE_R(0, &audio::RecordingDevice::isRecording);
	LUA_INVOKE_FOOTER("0");
}
int lua_audio_RecordingDevice_start(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.RecordingDevice", "audio.RecordingDevice:start");
	LUA_TRY_INVOKE_R(4, &audio::RecordingDevice::start);
	LUA_INVOKE_FOOTER("4");
}
int lua_audio_RecordingDevice_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("audio.RecordingDevice", "audio.RecordingDevice:stop");
	LUA_TRY_INVOKE(0, &audio::RecordingDevice::stop);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_audio_audioRecordingDevice(lua_State* lua_S)
{
	LUA_ENTRY("audio");
	LUA_CLS_DEF_BASE(audio::RecordingDevice, "RecordingDevice", "audio.RecordingDevice",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_SFIELD("DEFAULT_BIT_DEPTH", lua_audio_RecordingDevice_DEFAULT_BIT_DEPTH_getter, nullptr);
	LUA_SFIELD("DEFAULT_CHANNELS", lua_audio_RecordingDevice_DEFAULT_CHANNELS_getter, nullptr);
	LUA_SFIELD("DEFAULT_SAMPLES", lua_audio_RecordingDevice_DEFAULT_SAMPLES_getter, nullptr);
	LUA_SFIELD("DEFAULT_SAMPLE_RATE", lua_audio_RecordingDevice_DEFAULT_SAMPLE_RATE_getter, nullptr);
	LUA_METHOD("getBitDepth", lua_audio_RecordingDevice_getBitDepth);
	LUA_METHOD("getChannelCount", lua_audio_RecordingDevice_getChannelCount);
	LUA_METHOD("getData", lua_audio_RecordingDevice_getData);
	LUA_METHOD("getMaxSamples", lua_audio_RecordingDevice_getMaxSamples);
	LUA_METHOD("getName", lua_audio_RecordingDevice_getName);
	LUA_METHOD("getSampleCount", lua_audio_RecordingDevice_getSampleCount);
	LUA_METHOD("getSampleRate", lua_audio_RecordingDevice_getSampleRate);
	LUA_METHOD("isRecording", lua_audio_RecordingDevice_isRecording);
	LUA_METHOD("start", lua_audio_RecordingDevice_start);
	LUA_METHOD("stop", lua_audio_RecordingDevice_stop);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_audio_Engine_getActiveEffects(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getActiveEffects");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getActiveEffects);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getActiveSourceCount(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getActiveSourceCount");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getActiveSourceCount);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getDistanceModel(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getDistanceModel");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getDistanceModel);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getDopplerScale(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getDopplerScale");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getDopplerScale);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getEffect(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getEffect");
	LUA_TRY_INVOKE_R(1, &audio::Engine::getEffect);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Engine_getEffectID(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getEffectID");
	LUA_TRY_INVOKE_R(2, &audio::Engine::getEffectID);
	LUA_SINVOKE_FOOTER("2");
}
int lua_audio_Engine_getFormat(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getFormat");
	LUA_TRY_INVOKE_R(2, &audio::Engine::getFormat);
	LUA_SINVOKE_FOOTER("2");
}
int lua_audio_Engine_getLastError(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getLastError");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getLastError);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getMaxEffectCount(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getMaxEffectCount");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getMaxEffectCount);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getMaxSourceCount(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getMaxSourceCount");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getMaxSourceCount);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getMaxSourceEffectCount(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getMaxSourceEffectCount");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getMaxSourceEffectCount);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getOrientation(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getOrientation");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getOrientation);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getPosition(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getPosition");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getPosition);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getRecordingDevices(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getRecordingDevices");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getRecordingDevices);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getVelocity(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getVelocity");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getVelocity);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_getVolume(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:getVolume");
	LUA_TRY_INVOKE_R(0, &audio::Engine::getVolume);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_isEffectSupported(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:isEffectSupported");
	LUA_TRY_INVOKE_R(0, &audio::Engine::isEffectSupported);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_isValid(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:isValid");
	LUA_TRY_INVOKE_R(0, &audio::Engine::isValid);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_onEnterBackground(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:onEnterBackground");
	LUA_TRY_INVOKE(0, &audio::Engine::onEnterBackground);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_onEnterForeground(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:onEnterForeground");
	LUA_TRY_INVOKE(0, &audio::Engine::onEnterForeground);
	LUA_SINVOKE_FOOTER("0");
}
int lua_audio_Engine_pause(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:pause");
	LUA_TRY_INVOKE(1, static_cast<void(*)(const std::vector<audio::Source *>&)>(&audio::Engine::pause));
	LUA_TRY_INVOKE_R(0, static_cast<std::vector<audio::Source *>(*)()>(&audio::Engine::pause));
	LUA_SINVOKE_FOOTER("0,1");
}
int lua_audio_Engine_play(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:play");
	LUA_TRY_INVOKE_R(1, &audio::Engine::play);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Engine_removeEffect(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:removeEffect");
	LUA_TRY_INVOKE_R(1, &audio::Engine::removeEffect);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Engine_setDistanceModel(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:setDistanceModel");
	LUA_TRY_INVOKE(1, &audio::Engine::setDistanceModel);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Engine_setDopplerScale(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:setDopplerScale");
	LUA_TRY_INVOKE(1, &audio::Engine::setDopplerScale);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Engine_setEffect(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:setEffect");
	LUA_TRY_INVOKE_R(2, &audio::Engine::setEffect);
	LUA_SINVOKE_FOOTER("2");
}
int lua_audio_Engine_setOrientation(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:setOrientation");
	LUA_TRY_INVOKE(2, &audio::Engine::setOrientation);
	LUA_SINVOKE_FOOTER("2");
}
int lua_audio_Engine_setPosition(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:setPosition");
	LUA_TRY_INVOKE(1, &audio::Engine::setPosition);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Engine_setVelocity(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:setVelocity");
	LUA_TRY_INVOKE(1, &audio::Engine::setVelocity);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Engine_setVolume(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:setVolume");
	LUA_TRY_INVOKE(1, &audio::Engine::setVolume);
	LUA_SINVOKE_FOOTER("1");
}
int lua_audio_Engine_stop(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("audio.Engine", "audio.Engine:stop");
	LUA_TRY_INVOKE(1, static_cast<void(*)(const std::vector<audio::Source *>&)>(&audio::Engine::stop));
	LUA_TRY_INVOKE(0, static_cast<void(*)()>(&audio::Engine::stop));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_audio_audioEngine(lua_State* lua_S)
{
	LUA_ENTRY("audio");
	LUA_CLS_DEF(audio::Engine, "Engine", "audio.Engine",
		nullptr, nullptr);
	LUA_METHOD("getActiveEffects", lua_audio_Engine_getActiveEffects);
	LUA_METHOD("getActiveSourceCount", lua_audio_Engine_getActiveSourceCount);
	LUA_METHOD("getDistanceModel", lua_audio_Engine_getDistanceModel);
	LUA_METHOD("getDopplerScale", lua_audio_Engine_getDopplerScale);
	LUA_METHOD("getEffect", lua_audio_Engine_getEffect);
	LUA_METHOD("getEffectID", lua_audio_Engine_getEffectID);
	LUA_METHOD("getFormat", lua_audio_Engine_getFormat);
	LUA_METHOD("getLastError", lua_audio_Engine_getLastError);
	LUA_METHOD("getMaxEffectCount", lua_audio_Engine_getMaxEffectCount);
	LUA_METHOD("getMaxSourceCount", lua_audio_Engine_getMaxSourceCount);
	LUA_METHOD("getMaxSourceEffectCount", lua_audio_Engine_getMaxSourceEffectCount);
	LUA_METHOD("getOrientation", lua_audio_Engine_getOrientation);
	LUA_METHOD("getPosition", lua_audio_Engine_getPosition);
	LUA_METHOD("getRecordingDevices", lua_audio_Engine_getRecordingDevices);
	LUA_METHOD("getVelocity", lua_audio_Engine_getVelocity);
	LUA_METHOD("getVolume", lua_audio_Engine_getVolume);
	LUA_METHOD("isEffectSupported", lua_audio_Engine_isEffectSupported);
	LUA_METHOD("isValid", lua_audio_Engine_isValid);
	LUA_METHOD("onEnterBackground", lua_audio_Engine_onEnterBackground);
	LUA_METHOD("onEnterForeground", lua_audio_Engine_onEnterForeground);
	LUA_METHOD("pause", lua_audio_Engine_pause);
	LUA_METHOD("play", lua_audio_Engine_play);
	LUA_METHOD("removeEffect", lua_audio_Engine_removeEffect);
	LUA_METHOD("setDistanceModel", lua_audio_Engine_setDistanceModel);
	LUA_METHOD("setDopplerScale", lua_audio_Engine_setDopplerScale);
	LUA_METHOD("setEffect", lua_audio_Engine_setEffect);
	LUA_METHOD("setOrientation", lua_audio_Engine_setOrientation);
	LUA_METHOD("setPosition", lua_audio_Engine_setPosition);
	LUA_METHOD("setVelocity", lua_audio_Engine_setVelocity);
	LUA_METHOD("setVolume", lua_audio_Engine_setVolume);
	LUA_METHOD("stop", lua_audio_Engine_stop);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
