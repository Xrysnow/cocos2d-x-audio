#include "lua_audio_auto.hpp"
#include "AudioEngine.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
using audio::lua::luaval_to_native;
using audio::lua::native_to_luaval;

#ifndef LUA_CHECK_COBJ_TYPE
	#ifdef LUA_DEBUG
		#define LUA_CHECK_COBJ_TYPE(L, TYPE, NAME) if(!tolua_isusertype((L), 1, (TYPE), 0, nullptr)) { return luaL_error((L), "invalid 'cobj' in '%s': '%s', expects '%s'", NAME, tolua_typename((L), 1), (TYPE)); }
	#else
		#define LUA_CHECK_COBJ_TYPE(L, TYPE, NAME) (void)(TYPE);
	#endif
#endif
#ifndef LUA_CHECK_COBJ
	#ifdef LUA_DEBUG
		#define LUA_CHECK_COBJ(L, COBJ, NAME) if(!(COBJ)) { return luaL_error((L), "invalid 'cobj' in '%s'", NAME); }
	#else
		#define LUA_CHECK_COBJ(L, COBJ, NAME)
	#endif
#endif
#ifndef LUA_CHECK_PARAMETER
	#define LUA_CHECK_PARAMETER(L, OK, NAME) if(!(OK)) { return luaL_error((L), "invalid arguments in '%s'", NAME); }
#endif
#ifndef LUA_PARAMETER_ERROR
	#define LUA_PARAMETER_ERROR(L, NAME, ARGC, EXPECT) return luaL_error((L), "wrong number of arguments in '%s': %d, expects %s", NAME, (ARGC), EXPECT);
#endif

int lua_x_Audio_Source_clone(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:clone";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->clone();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_create(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:create";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 4) {
		int arg0;
		int arg1;
		int arg2;
		int arg3;
		ok &= luaval_to_int32(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_int32(tolua_S, 3, &arg1, LUA_FNAME);
		ok &= luaval_to_int32(tolua_S, 4, &arg2, LUA_FNAME);
		ok &= luaval_to_int32(tolua_S, 5, &arg3, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Source::create(arg0, arg1, arg2, arg3);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "4");
}
int lua_x_Audio_Source_createFromDecoder(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:createFromDecoder";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		audio::Decoder* arg0;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Source::createFromDecoder(arg0);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_createFromSoundData(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:createFromSoundData";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		audio::SoundData* arg0;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Source::createFromSoundData(arg0);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_getActiveEffects(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getActiveEffects";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getActiveEffects();
		ccvector_std_string_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getAirAbsorptionFactor(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getAirAbsorptionFactor";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getAirAbsorptionFactor();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getBitDepth(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getBitDepth";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getBitDepth();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getBytesPerFrame(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getBytesPerFrame";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getBytesPerFrame();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getChannelCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getChannelCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getChannelCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getCone(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getCone";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getCone();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getDirection(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getDirection";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getDirection();
		vec3_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getEffect(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getEffect";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getEffect(arg0);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_getFilter(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getFilter";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getFilter();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getFreeBufferCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getFreeBufferCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getFreeBufferCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getLastError(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getLastError";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getLastError();
		lua_pushlstring(tolua_S, ret.c_str(), ret.length());
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getLoopingEnd(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getLoopingEnd";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getLoopingEnd();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getLoopingStart(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getLoopingStart";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getLoopingStart();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getMaxDistance(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getMaxDistance";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getMaxDistance();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getMaxVolume(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getMaxVolume";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getMaxVolume();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getMinVolume(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getMinVolume";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getMinVolume();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getPitch(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getPitch";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getPitch();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getPosition(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getPosition";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getPosition();
		vec3_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getReferenceDistance(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getReferenceDistance";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getReferenceDistance();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getRolloffFactor(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getRolloffFactor";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getRolloffFactor();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getSampleRate(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getSampleRate";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getSampleRate();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getTime(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getTime";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getTime();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getTotalFrames(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getTotalFrames";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getTotalFrames();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getTotalTime(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getTotalTime";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getTotalTime();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getType(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getType";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getType();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getVelocity(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getVelocity";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getVelocity();
		vec3_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_getVolume(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:getVolume";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getVolume();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_isFinished(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:isFinished";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->isFinished();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_isLooping(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:isLooping";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->isLooping();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_isPlaying(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:isPlaying";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->isPlaying();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_isRelative(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:isRelative";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->isRelative();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_isSupportLoopingPoint(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:isSupportLoopingPoint";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->isSupportLoopingPoint();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_pause(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:pause";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->pause();
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_pauseAll(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:pauseAll";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Source::pauseAll();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_pauseBatch(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:pauseBatch";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::vector<audio::Source *> arg0;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Source::pauseBatch(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_play(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:play";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->play();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_playBatch(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:playBatch";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::vector<audio::Source *> arg0;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Source::playBatch(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_queue(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:queue";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		audio::SoundData* arg0;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->queue(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	if (argc == 2) {
		audio::SoundData* arg0;
		ssize_t arg1;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_ssize(tolua_S, 3, &arg1, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->queue(arg0, arg1);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	if (argc == 3) {
		audio::SoundData* arg0;
		ssize_t arg1;
		ssize_t arg2;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_ssize(tolua_S, 3, &arg1, LUA_FNAME);
		ok &= luaval_to_ssize(tolua_S, 4, &arg2, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->queue(arg0, arg1, arg2);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1 to 3");
}
int lua_x_Audio_Source_removeEffect(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:removeEffect";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->removeEffect(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_removeFilter(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:removeFilter";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->removeFilter();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_seek(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:seek";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		long long arg0;
		ok &= luaval_to_long_long(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->seek(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setAirAbsorptionFactor(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setAirAbsorptionFactor";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setAirAbsorptionFactor(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setCone(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setCone";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	do {
		if (argc == 1) {
			std::array<float, 4> arg0;
			ok &= luaval_to_native(tolua_S, 2, &arg0, "LUA_FNAME");
			if (!ok) { break; }
			cobj->setCone(arg0);
			lua_settop(tolua_S, 1);
			return 1;
		}
	} while (false);
	ok = true;
	do {
		if (argc == 4) {
			double arg0;
			ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
			if (!ok) { break; }
			double arg1;
			ok &= luaval_to_number(tolua_S, 3, &arg1, LUA_FNAME);
			if (!ok) { break; }
			double arg2;
			ok &= luaval_to_number(tolua_S, 4, &arg2, LUA_FNAME);
			if (!ok) { break; }
			double arg3;
			ok &= luaval_to_number(tolua_S, 5, &arg3, LUA_FNAME);
			if (!ok) { break; }
			cobj->setCone(arg0, arg1, arg2, arg3);
			lua_settop(tolua_S, 1);
			return 1;
		}
	} while (false);
	ok = true;
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "4");
}
int lua_x_Audio_Source_setDirection(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setDirection";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		cocos2d::Vec3 arg0;
		ok &= luaval_to_vec3(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setDirection(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setEffect(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setEffect";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	do {
		if (argc == 2) {
			std::string arg0;
			ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
			if (!ok) { break; }
			std::map<audio::Filter::Parameter, float> arg1;
			ok &= luaval_to_native(tolua_S, 3, &arg1, LUA_FNAME);
			if (!ok) { break; }
			auto ret = cobj->setEffect(arg0, arg1);
			tolua_pushboolean(tolua_S, (bool)ret);
			return 1;
		}
	} while (false);
	ok = true;
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
			if (!ok) { break; }
			auto ret = cobj->setEffect(arg0);
			tolua_pushboolean(tolua_S, (bool)ret);
			return 1;
		}
	} while (false);
	ok = true;
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setFilter(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setFilter";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::map<audio::Filter::Parameter, float> arg0;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->setFilter(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setLooping(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setLooping";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setLooping(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setLoopingPoint(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setLoopingPoint";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 2) {
		double arg0;
		double arg1;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_number(tolua_S, 3, &arg1, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setLoopingPoint(arg0, arg1);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "2");
}
int lua_x_Audio_Source_setMaxDistance(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setMaxDistance";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setMaxDistance(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setMaxVolume(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setMaxVolume";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setMaxVolume(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setMinVolume(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setMinVolume";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setMinVolume(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setPitch(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setPitch";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setPitch(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setPosition(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setPosition";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		cocos2d::Vec3 arg0;
		ok &= luaval_to_vec3(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setPosition(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setReferenceDistance(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setReferenceDistance";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setReferenceDistance(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setRelative(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setRelative";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setRelative(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setRolloffFactor(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setRolloffFactor";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setRolloffFactor(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setTime(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setTime";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setTime(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setVelocity(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setVelocity";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		cocos2d::Vec3 arg0;
		ok &= luaval_to_vec3(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setVelocity(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_setVolume(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:setVolume";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->setVolume(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_stop(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:stop";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->stop();
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_stopAll(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:stopAll";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Source::stopAll();
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Source_stopBatch(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:stopBatch";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::vector<audio::Source *> arg0;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Source::stopBatch(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Source_tell(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Source";
	constexpr auto LUA_FNAME = "audio.Source:tell";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Source*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->tell();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
static int lua_x_Audio_Source_finalize(lua_State* tolua_S)
{
	return 0;
}

int lua_register_x_Audio_Source(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "audio.Source");
	tolua_cclass(tolua_S, "Source", "audio.Source", "cc.Ref", nullptr);

	tolua_beginmodule(tolua_S, "Source");
		tolua_function(tolua_S, "clone", lua_x_Audio_Source_clone);
		tolua_function(tolua_S, "getActiveEffects", lua_x_Audio_Source_getActiveEffects);
		tolua_function(tolua_S, "getAirAbsorptionFactor", lua_x_Audio_Source_getAirAbsorptionFactor);
		tolua_function(tolua_S, "getBitDepth", lua_x_Audio_Source_getBitDepth);
		tolua_function(tolua_S, "getBytesPerFrame", lua_x_Audio_Source_getBytesPerFrame);
		tolua_function(tolua_S, "getChannelCount", lua_x_Audio_Source_getChannelCount);
		tolua_function(tolua_S, "getCone", lua_x_Audio_Source_getCone);
		tolua_function(tolua_S, "getDirection", lua_x_Audio_Source_getDirection);
		tolua_function(tolua_S, "getEffect", lua_x_Audio_Source_getEffect);
		tolua_function(tolua_S, "getFilter", lua_x_Audio_Source_getFilter);
		tolua_function(tolua_S, "getFreeBufferCount", lua_x_Audio_Source_getFreeBufferCount);
		tolua_function(tolua_S, "getLastError", lua_x_Audio_Source_getLastError);
		tolua_function(tolua_S, "getLoopingEnd", lua_x_Audio_Source_getLoopingEnd);
		tolua_function(tolua_S, "getLoopingStart", lua_x_Audio_Source_getLoopingStart);
		tolua_function(tolua_S, "getMaxDistance", lua_x_Audio_Source_getMaxDistance);
		tolua_function(tolua_S, "getMaxVolume", lua_x_Audio_Source_getMaxVolume);
		tolua_function(tolua_S, "getMinVolume", lua_x_Audio_Source_getMinVolume);
		tolua_function(tolua_S, "getPitch", lua_x_Audio_Source_getPitch);
		tolua_function(tolua_S, "getPosition", lua_x_Audio_Source_getPosition);
		tolua_function(tolua_S, "getReferenceDistance", lua_x_Audio_Source_getReferenceDistance);
		tolua_function(tolua_S, "getRolloffFactor", lua_x_Audio_Source_getRolloffFactor);
		tolua_function(tolua_S, "getSampleRate", lua_x_Audio_Source_getSampleRate);
		tolua_function(tolua_S, "getTime", lua_x_Audio_Source_getTime);
		tolua_function(tolua_S, "getTotalFrames", lua_x_Audio_Source_getTotalFrames);
		tolua_function(tolua_S, "getTotalTime", lua_x_Audio_Source_getTotalTime);
		tolua_function(tolua_S, "getType", lua_x_Audio_Source_getType);
		tolua_function(tolua_S, "getVelocity", lua_x_Audio_Source_getVelocity);
		tolua_function(tolua_S, "getVolume", lua_x_Audio_Source_getVolume);
		tolua_function(tolua_S, "isFinished", lua_x_Audio_Source_isFinished);
		tolua_function(tolua_S, "isLooping", lua_x_Audio_Source_isLooping);
		tolua_function(tolua_S, "isPlaying", lua_x_Audio_Source_isPlaying);
		tolua_function(tolua_S, "isRelative", lua_x_Audio_Source_isRelative);
		tolua_function(tolua_S, "isSupportLoopingPoint", lua_x_Audio_Source_isSupportLoopingPoint);
		tolua_function(tolua_S, "pause", lua_x_Audio_Source_pause);
		tolua_function(tolua_S, "play", lua_x_Audio_Source_play);
		tolua_function(tolua_S, "queue", lua_x_Audio_Source_queue);
		tolua_function(tolua_S, "removeEffect", lua_x_Audio_Source_removeEffect);
		tolua_function(tolua_S, "removeFilter", lua_x_Audio_Source_removeFilter);
		tolua_function(tolua_S, "seek", lua_x_Audio_Source_seek);
		tolua_function(tolua_S, "setAirAbsorptionFactor", lua_x_Audio_Source_setAirAbsorptionFactor);
		tolua_function(tolua_S, "setCone", lua_x_Audio_Source_setCone);
		tolua_function(tolua_S, "setDirection", lua_x_Audio_Source_setDirection);
		tolua_function(tolua_S, "setEffect", lua_x_Audio_Source_setEffect);
		tolua_function(tolua_S, "setFilter", lua_x_Audio_Source_setFilter);
		tolua_function(tolua_S, "setLooping", lua_x_Audio_Source_setLooping);
		tolua_function(tolua_S, "setLoopingPoint", lua_x_Audio_Source_setLoopingPoint);
		tolua_function(tolua_S, "setMaxDistance", lua_x_Audio_Source_setMaxDistance);
		tolua_function(tolua_S, "setMaxVolume", lua_x_Audio_Source_setMaxVolume);
		tolua_function(tolua_S, "setMinVolume", lua_x_Audio_Source_setMinVolume);
		tolua_function(tolua_S, "setPitch", lua_x_Audio_Source_setPitch);
		tolua_function(tolua_S, "setPosition", lua_x_Audio_Source_setPosition);
		tolua_function(tolua_S, "setReferenceDistance", lua_x_Audio_Source_setReferenceDistance);
		tolua_function(tolua_S, "setRelative", lua_x_Audio_Source_setRelative);
		tolua_function(tolua_S, "setRolloffFactor", lua_x_Audio_Source_setRolloffFactor);
		tolua_function(tolua_S, "setTime", lua_x_Audio_Source_setTime);
		tolua_function(tolua_S, "setVelocity", lua_x_Audio_Source_setVelocity);
		tolua_function(tolua_S, "setVolume", lua_x_Audio_Source_setVolume);
		tolua_function(tolua_S, "stop", lua_x_Audio_Source_stop);
		tolua_function(tolua_S, "tell", lua_x_Audio_Source_tell);
		tolua_function(tolua_S, "create", lua_x_Audio_Source_create);
		tolua_function(tolua_S, "createFromDecoder", lua_x_Audio_Source_createFromDecoder);
		tolua_function(tolua_S, "createFromSoundData", lua_x_Audio_Source_createFromSoundData);
		tolua_function(tolua_S, "pauseAll", lua_x_Audio_Source_pauseAll);
		tolua_function(tolua_S, "pauseBatch", lua_x_Audio_Source_pauseBatch);
		tolua_function(tolua_S, "playBatch", lua_x_Audio_Source_playBatch);
		tolua_function(tolua_S, "stopAll", lua_x_Audio_Source_stopAll);
		tolua_function(tolua_S, "stopBatch", lua_x_Audio_Source_stopBatch);
		{
			tolua_module(tolua_S, "Type", 0);
			tolua_beginmodule(tolua_S, "Type");
			{
				tolua_constant(tolua_S, "STATIC", (lua_Number)audio::Source::Type::STATIC);
				tolua_constant(tolua_S, "STREAM", (lua_Number)audio::Source::Type::STREAM);
				tolua_constant(tolua_S, "QUEUE", (lua_Number)audio::Source::Type::QUEUE);
				tolua_constant(tolua_S, "MAX_ENUM", (lua_Number)audio::Source::Type::MAX_ENUM);
			}
			tolua_endmodule(tolua_S);
		}
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(audio::Source).name();
	g_luaType[typeName] = "audio.Source";
	g_typeCast["Source"] = "audio.Source";
	return 1;
}

int lua_x_Audio_Stream_createFromFile(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Stream";
	constexpr auto LUA_FNAME = "audio.Stream:createFromFile";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Stream::createFromFile(arg0);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Stream_createFromLocalFile(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Stream";
	constexpr auto LUA_FNAME = "audio.Stream:createFromLocalFile";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Stream::createFromLocalFile(arg0);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Stream_createFromSoundData(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Stream";
	constexpr auto LUA_FNAME = "audio.Stream:createFromSoundData";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		audio::SoundData* arg0;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Stream::createFromSoundData(arg0);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Stream_createFromStringData(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Stream";
	constexpr auto LUA_FNAME = "audio.Stream:createFromStringData";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Stream::createFromStringData(arg0);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Stream_lock(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Stream";
	constexpr auto LUA_FNAME = "audio.Stream:lock";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Stream*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->lock();
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Stream_seek(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Stream";
	constexpr auto LUA_FNAME = "audio.Stream:seek";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Stream*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 2) {
		audio::Stream::SeekOrigin arg0;
		long long arg1;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_long_long(tolua_S, 3, &arg1, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->seek(arg0, arg1);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "2");
}
int lua_x_Audio_Stream_size(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Stream";
	constexpr auto LUA_FNAME = "audio.Stream:size";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Stream*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->size();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Stream_tell(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Stream";
	constexpr auto LUA_FNAME = "audio.Stream:tell";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Stream*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->tell();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Stream_unlock(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Stream";
	constexpr auto LUA_FNAME = "audio.Stream:unlock";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Stream*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->unlock();
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
static int lua_x_Audio_Stream_finalize(lua_State* tolua_S)
{
	return 0;
}

int lua_register_x_Audio_Stream(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "audio.Stream");
	tolua_cclass(tolua_S, "Stream", "audio.Stream", "cc.Ref", nullptr);

	tolua_beginmodule(tolua_S, "Stream");
		tolua_function(tolua_S, "lock", lua_x_Audio_Stream_lock);
		tolua_function(tolua_S, "seek", lua_x_Audio_Stream_seek);
		tolua_function(tolua_S, "size", lua_x_Audio_Stream_size);
		tolua_function(tolua_S, "tell", lua_x_Audio_Stream_tell);
		tolua_function(tolua_S, "unlock", lua_x_Audio_Stream_unlock);
		tolua_function(tolua_S, "createFromFile", lua_x_Audio_Stream_createFromFile);
		tolua_function(tolua_S, "createFromLocalFile", lua_x_Audio_Stream_createFromLocalFile);
		tolua_function(tolua_S, "createFromSoundData", lua_x_Audio_Stream_createFromSoundData);
		tolua_function(tolua_S, "createFromStringData", lua_x_Audio_Stream_createFromStringData);
		{
			tolua_module(tolua_S, "SeekOrigin", 0);
			tolua_beginmodule(tolua_S, "SeekOrigin");
			{
				tolua_constant(tolua_S, "BEGINNING", (lua_Number)audio::Stream::SeekOrigin::BEGINNING);
				tolua_constant(tolua_S, "CURRENT", (lua_Number)audio::Stream::SeekOrigin::CURRENT);
				tolua_constant(tolua_S, "END", (lua_Number)audio::Stream::SeekOrigin::END);
			}
			tolua_endmodule(tolua_S);
		}
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(audio::Stream).name();
	g_luaType[typeName] = "audio.Stream";
	g_typeCast["Stream"] = "audio.Stream";
	return 1;
}

int lua_x_Audio_Decoder_clone(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:clone";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->clone();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_createFromFile(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:createFromFile";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 2) {
		std::string arg0;
		unsigned int arg1;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_uint32(tolua_S, 3, &arg1, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Decoder::createFromFile(arg0, arg1);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	if (argc == 3) {
		std::string arg0;
		unsigned int arg1;
		audio::Decoder::DecoderType arg2;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_uint32(tolua_S, 3, &arg1, LUA_FNAME);
		ok &= luaval_to_native(tolua_S, 4, &arg2, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Decoder::createFromFile(arg0, arg1, arg2);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "2 to 3");
}
int lua_x_Audio_Decoder_createFromLocalFile(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:createFromLocalFile";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 2) {
		std::string arg0;
		unsigned int arg1;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_uint32(tolua_S, 3, &arg1, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Decoder::createFromLocalFile(arg0, arg1);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	if (argc == 3) {
		std::string arg0;
		unsigned int arg1;
		audio::Decoder::DecoderType arg2;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_uint32(tolua_S, 3, &arg1, LUA_FNAME);
		ok &= luaval_to_native(tolua_S, 4, &arg2, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Decoder::createFromLocalFile(arg0, arg1, arg2);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "2 to 3");
}
int lua_x_Audio_Decoder_createFromSoundData(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:createFromSoundData";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 3) {
		audio::SoundData* arg0;
		unsigned int arg1;
		audio::Decoder::DecoderType arg2;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_uint32(tolua_S, 3, &arg1, LUA_FNAME);
		ok &= luaval_to_native(tolua_S, 4, &arg2, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Decoder::createFromSoundData(arg0, arg1, arg2);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "3");
}
int lua_x_Audio_Decoder_createFromStream(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:createFromStream";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 3) {
		audio::Stream* arg0;
		unsigned int arg1;
		audio::Decoder::DecoderType arg2;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_uint32(tolua_S, 3, &arg1, LUA_FNAME);
		ok &= luaval_to_native(tolua_S, 4, &arg2, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Decoder::createFromStream(arg0, arg1, arg2);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "3");
}
int lua_x_Audio_Decoder_createFromStringData(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:createFromStringData";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 3) {
		std::string arg0;
		unsigned int arg1;
		audio::Decoder::DecoderType arg2;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_uint32(tolua_S, 3, &arg1, LUA_FNAME);
		ok &= luaval_to_native(tolua_S, 4, &arg2, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Decoder::createFromStringData(arg0, arg1, arg2);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "3");
}
int lua_x_Audio_Decoder_getBitDepth(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:getBitDepth";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getBitDepth();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_getBufferSize(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:getBufferSize";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getBufferSize();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_getBytesPerFrame(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:getBytesPerFrame";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getBytesPerFrame();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_getChannelCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:getChannelCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getChannelCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_getDecoderTypeFromPath(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:getDecoderTypeFromPath";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Decoder::getDecoderTypeFromPath(arg0);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Decoder_getDuration(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:getDuration";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getDuration();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_getLoopingEnd(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:getLoopingEnd";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getLoopingEnd();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_getLoopingStart(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:getLoopingStart";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getLoopingStart();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_getSampleRate(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:getSampleRate";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getSampleRate();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_getTotalFrames(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:getTotalFrames";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getTotalFrames();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_isFinished(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:isFinished";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->isFinished();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_isSeekable(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:isSeekable";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->isSeekable();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_rewind(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:rewind";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->rewind();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Decoder_seek(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:seek";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		long long arg0;
		ok &= luaval_to_long_long(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->seek(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Decoder_seekTime(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:seekTime";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->seekTime(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Decoder_tell(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Decoder";
	constexpr auto LUA_FNAME = "audio.Decoder:tell";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::Decoder*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->tell();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
static int lua_x_Audio_Decoder_finalize(lua_State* tolua_S)
{
	return 0;
}

int lua_register_x_Audio_Decoder(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "audio.Decoder");
	tolua_cclass(tolua_S, "Decoder", "audio.Decoder", "cc.Ref", nullptr);

	tolua_beginmodule(tolua_S, "Decoder");
		tolua_function(tolua_S, "clone", lua_x_Audio_Decoder_clone);
		tolua_function(tolua_S, "getBitDepth", lua_x_Audio_Decoder_getBitDepth);
		tolua_function(tolua_S, "getBufferSize", lua_x_Audio_Decoder_getBufferSize);
		tolua_function(tolua_S, "getBytesPerFrame", lua_x_Audio_Decoder_getBytesPerFrame);
		tolua_function(tolua_S, "getChannelCount", lua_x_Audio_Decoder_getChannelCount);
		tolua_function(tolua_S, "getDuration", lua_x_Audio_Decoder_getDuration);
		tolua_function(tolua_S, "getLoopingEnd", lua_x_Audio_Decoder_getLoopingEnd);
		tolua_function(tolua_S, "getLoopingStart", lua_x_Audio_Decoder_getLoopingStart);
		tolua_function(tolua_S, "getSampleRate", lua_x_Audio_Decoder_getSampleRate);
		tolua_function(tolua_S, "getTotalFrames", lua_x_Audio_Decoder_getTotalFrames);
		tolua_function(tolua_S, "isFinished", lua_x_Audio_Decoder_isFinished);
		tolua_function(tolua_S, "isSeekable", lua_x_Audio_Decoder_isSeekable);
		tolua_function(tolua_S, "rewind", lua_x_Audio_Decoder_rewind);
		tolua_function(tolua_S, "seek", lua_x_Audio_Decoder_seek);
		tolua_function(tolua_S, "seekTime", lua_x_Audio_Decoder_seekTime);
		tolua_function(tolua_S, "tell", lua_x_Audio_Decoder_tell);
		tolua_function(tolua_S, "createFromFile", lua_x_Audio_Decoder_createFromFile);
		tolua_function(tolua_S, "createFromLocalFile", lua_x_Audio_Decoder_createFromLocalFile);
		tolua_function(tolua_S, "createFromSoundData", lua_x_Audio_Decoder_createFromSoundData);
		tolua_function(tolua_S, "createFromStream", lua_x_Audio_Decoder_createFromStream);
		tolua_function(tolua_S, "createFromStringData", lua_x_Audio_Decoder_createFromStringData);
		tolua_function(tolua_S, "getDecoderTypeFromPath", lua_x_Audio_Decoder_getDecoderTypeFromPath);
		{
			tolua_module(tolua_S, "DecoderType", 0);
			tolua_beginmodule(tolua_S, "DecoderType");
			{
				tolua_constant(tolua_S, "UNKNOWN", (lua_Number)audio::Decoder::DecoderType::UNKNOWN);
				tolua_constant(tolua_S, "WAV", (lua_Number)audio::Decoder::DecoderType::WAV);
				tolua_constant(tolua_S, "VORBIS", (lua_Number)audio::Decoder::DecoderType::VORBIS);
				tolua_constant(tolua_S, "FLAC", (lua_Number)audio::Decoder::DecoderType::FLAC);
				tolua_constant(tolua_S, "MP3", (lua_Number)audio::Decoder::DecoderType::MP3);
			}
			tolua_endmodule(tolua_S);
		}
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(audio::Decoder).name();
	g_luaType[typeName] = "audio.Decoder";
	g_typeCast["Decoder"] = "audio.Decoder";
	return 1;
}

int lua_x_Audio_SoundData_clone(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.SoundData";
	constexpr auto LUA_FNAME = "audio.SoundData:clone";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::SoundData*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->clone();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_SoundData_getBitDepth(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.SoundData";
	constexpr auto LUA_FNAME = "audio.SoundData:getBitDepth";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::SoundData*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getBitDepth();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_SoundData_getChannelCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.SoundData";
	constexpr auto LUA_FNAME = "audio.SoundData:getChannelCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::SoundData*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getChannelCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_SoundData_getDuration(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.SoundData";
	constexpr auto LUA_FNAME = "audio.SoundData:getDuration";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::SoundData*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getDuration();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_SoundData_getLastError(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.SoundData";
	constexpr auto LUA_FNAME = "audio.SoundData:getLastError";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::SoundData*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getLastError();
		lua_pushlstring(tolua_S, ret.c_str(), ret.length());
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_SoundData_getSample(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.SoundData";
	constexpr auto LUA_FNAME = "audio.SoundData:getSample";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::SoundData*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	do {
		if (argc == 2) {
			int arg0;
			ok &= luaval_to_int32(tolua_S, 2, &arg0, LUA_FNAME);
			if (!ok) { break; }
			int arg1;
			ok &= luaval_to_int32(tolua_S, 3, &arg1, LUA_FNAME);
			if (!ok) { break; }
			auto ret = cobj->getSample(arg0, arg1);
			tolua_pushnumber(tolua_S, (lua_Number)ret);
			return 1;
		}
	} while (false);
	ok = true;
	do {
		if (argc == 1) {
			int arg0;
			ok &= luaval_to_int32(tolua_S, 2, &arg0, LUA_FNAME);
			if (!ok) { break; }
			auto ret = cobj->getSample(arg0);
			tolua_pushnumber(tolua_S, (lua_Number)ret);
			return 1;
		}
	} while (false);
	ok = true;
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_SoundData_getSampleCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.SoundData";
	constexpr auto LUA_FNAME = "audio.SoundData:getSampleCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::SoundData*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getSampleCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_SoundData_getSampleRate(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.SoundData";
	constexpr auto LUA_FNAME = "audio.SoundData:getSampleRate";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::SoundData*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getSampleRate();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_SoundData_getSize(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.SoundData";
	constexpr auto LUA_FNAME = "audio.SoundData:getSize";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::SoundData*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getSize();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_SoundData_setSample(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.SoundData";
	constexpr auto LUA_FNAME = "audio.SoundData:setSample";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::SoundData*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	do {
		if (argc == 3) {
			int arg0;
			ok &= luaval_to_int32(tolua_S, 2, &arg0, LUA_FNAME);
			if (!ok) { break; }
			int arg1;
			ok &= luaval_to_int32(tolua_S, 3, &arg1, LUA_FNAME);
			if (!ok) { break; }
			double arg2;
			ok &= luaval_to_number(tolua_S, 4, &arg2, LUA_FNAME);
			if (!ok) { break; }
			cobj->setSample(arg0, arg1, arg2);
			lua_settop(tolua_S, 1);
			return 1;
		}
	} while (false);
	ok = true;
	do {
		if (argc == 2) {
			int arg0;
			ok &= luaval_to_int32(tolua_S, 2, &arg0, LUA_FNAME);
			if (!ok) { break; }
			double arg1;
			ok &= luaval_to_number(tolua_S, 3, &arg1, LUA_FNAME);
			if (!ok) { break; }
			cobj->setSample(arg0, arg1);
			lua_settop(tolua_S, 1);
			return 1;
		}
	} while (false);
	ok = true;
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "2");
}
static int lua_x_Audio_SoundData_finalize(lua_State* tolua_S)
{
	return 0;
}

int lua_register_x_Audio_SoundData(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "audio.SoundData");
	tolua_cclass(tolua_S, "SoundData", "audio.SoundData", "", nullptr);

	tolua_beginmodule(tolua_S, "SoundData");
		tolua_function(tolua_S, "clone", lua_x_Audio_SoundData_clone);
		tolua_function(tolua_S, "getBitDepth", lua_x_Audio_SoundData_getBitDepth);
		tolua_function(tolua_S, "getChannelCount", lua_x_Audio_SoundData_getChannelCount);
		tolua_function(tolua_S, "getDuration", lua_x_Audio_SoundData_getDuration);
		tolua_function(tolua_S, "getLastError", lua_x_Audio_SoundData_getLastError);
		tolua_function(tolua_S, "getSample", lua_x_Audio_SoundData_getSample);
		tolua_function(tolua_S, "getSampleCount", lua_x_Audio_SoundData_getSampleCount);
		tolua_function(tolua_S, "getSampleRate", lua_x_Audio_SoundData_getSampleRate);
		tolua_function(tolua_S, "getSize", lua_x_Audio_SoundData_getSize);
		tolua_function(tolua_S, "setSample", lua_x_Audio_SoundData_setSample);
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(audio::SoundData).name();
	g_luaType[typeName] = "audio.SoundData";
	g_typeCast["SoundData"] = "audio.SoundData";
	return 1;
}

int lua_x_Audio_RecordingDevice_getBitDepth(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.RecordingDevice";
	constexpr auto LUA_FNAME = "audio.RecordingDevice:getBitDepth";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getBitDepth();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_RecordingDevice_getChannelCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.RecordingDevice";
	constexpr auto LUA_FNAME = "audio.RecordingDevice:getChannelCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getChannelCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_RecordingDevice_getData(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.RecordingDevice";
	constexpr auto LUA_FNAME = "audio.RecordingDevice:getData";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getData();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_RecordingDevice_getMaxSamples(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.RecordingDevice";
	constexpr auto LUA_FNAME = "audio.RecordingDevice:getMaxSamples";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getMaxSamples();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_RecordingDevice_getName(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.RecordingDevice";
	constexpr auto LUA_FNAME = "audio.RecordingDevice:getName";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getName();
		lua_pushlstring(tolua_S, ret.c_str(), ret.length());
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_RecordingDevice_getSampleCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.RecordingDevice";
	constexpr auto LUA_FNAME = "audio.RecordingDevice:getSampleCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getSampleCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_RecordingDevice_getSampleRate(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.RecordingDevice";
	constexpr auto LUA_FNAME = "audio.RecordingDevice:getSampleRate";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->getSampleRate();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_RecordingDevice_isRecording(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.RecordingDevice";
	constexpr auto LUA_FNAME = "audio.RecordingDevice:isRecording";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->isRecording();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_RecordingDevice_start(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.RecordingDevice";
	constexpr auto LUA_FNAME = "audio.RecordingDevice:start";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 4) {
		int arg0;
		int arg1;
		int arg2;
		int arg3;
		ok &= luaval_to_int32(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_int32(tolua_S, 3, &arg1, LUA_FNAME);
		ok &= luaval_to_int32(tolua_S, 4, &arg2, LUA_FNAME);
		ok &= luaval_to_int32(tolua_S, 5, &arg3, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = cobj->start(arg0, arg1, arg2, arg3);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "4");
}
int lua_x_Audio_RecordingDevice_stop(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.RecordingDevice";
	constexpr auto LUA_FNAME = "audio.RecordingDevice:stop";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	auto cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S, 1, nullptr);
	LUA_CHECK_COBJ(tolua_S, cobj, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		cobj->stop();
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
static int lua_x_Audio_RecordingDevice_finalize(lua_State* tolua_S)
{
	return 0;
}

int lua_register_x_Audio_RecordingDevice(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "audio.RecordingDevice");
	tolua_cclass(tolua_S, "RecordingDevice", "audio.RecordingDevice", "cc.Ref", nullptr);

	tolua_beginmodule(tolua_S, "RecordingDevice");
		tolua_function(tolua_S, "getBitDepth", lua_x_Audio_RecordingDevice_getBitDepth);
		tolua_function(tolua_S, "getChannelCount", lua_x_Audio_RecordingDevice_getChannelCount);
		tolua_function(tolua_S, "getData", lua_x_Audio_RecordingDevice_getData);
		tolua_function(tolua_S, "getMaxSamples", lua_x_Audio_RecordingDevice_getMaxSamples);
		tolua_function(tolua_S, "getName", lua_x_Audio_RecordingDevice_getName);
		tolua_function(tolua_S, "getSampleCount", lua_x_Audio_RecordingDevice_getSampleCount);
		tolua_function(tolua_S, "getSampleRate", lua_x_Audio_RecordingDevice_getSampleRate);
		tolua_function(tolua_S, "isRecording", lua_x_Audio_RecordingDevice_isRecording);
		tolua_function(tolua_S, "start", lua_x_Audio_RecordingDevice_start);
		tolua_function(tolua_S, "stop", lua_x_Audio_RecordingDevice_stop);
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(audio::RecordingDevice).name();
	g_luaType[typeName] = "audio.RecordingDevice";
	g_typeCast["RecordingDevice"] = "audio.RecordingDevice";
	return 1;
}

int lua_x_Audio_Engine_getActiveEffects(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getActiveEffects";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getActiveEffects();
		ccvector_std_string_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getActiveSourceCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getActiveSourceCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getActiveSourceCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getDistanceModel(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getDistanceModel";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getDistanceModel();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getDopplerScale(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getDopplerScale";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getDopplerScale();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getEffect(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getEffect";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getEffect(arg0);
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Engine_getEffectID(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getEffectID";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 2) {
		std::string arg0;
		unsigned int arg1;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_uint32(tolua_S, 3, &arg1, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getEffectID(arg0, arg1);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "2");
}
int lua_x_Audio_Engine_getFormat(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getFormat";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 2) {
		int arg0;
		int arg1;
		ok &= luaval_to_int32(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_int32(tolua_S, 3, &arg1, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getFormat(arg0, arg1);
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "2");
}
int lua_x_Audio_Engine_getLastError(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getLastError";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getLastError();
		lua_pushlstring(tolua_S, ret.c_str(), ret.length());
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getMaxEffectCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getMaxEffectCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getMaxEffectCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getMaxSourceCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getMaxSourceCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getMaxSourceCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getMaxSourceEffectCount(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getMaxSourceEffectCount";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getMaxSourceEffectCount();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getOrientation(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getOrientation";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getOrientation();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getPosition(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getPosition";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getPosition();
		vec3_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getRecordingDevices(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getRecordingDevices";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getRecordingDevices();
		native_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getVelocity(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getVelocity";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getVelocity();
		vec3_to_luaval(tolua_S, ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_getVolume(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:getVolume";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::getVolume();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_isEffectSupported(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:isEffectSupported";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::isEffectSupported();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_isValid(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:isValid";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::isValid();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_onEnterBackground(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:onEnterBackground";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Engine::onEnterBackground();
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_onEnterForeground(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:onEnterForeground";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 0) {
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Engine::onEnterForeground();
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "0");
}
int lua_x_Audio_Engine_pause(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:pause";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	do {
		if (argc == 0) {
			auto ret = audio::Engine::pause();
			native_to_luaval(tolua_S, ret);
			return 1;
		}
	} while (0);
	ok = true;
	do {
		if (argc == 1) {
			std::vector<audio::Source *> arg0;
			ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
			if (!ok) { break; }
			audio::Engine::pause(arg0);
			lua_settop(tolua_S, 1);
			return 1;
		}
	} while (0);
	ok = true;
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Engine_play(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:play";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::vector<audio::Source *> arg0;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::play(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Engine_removeEffect(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:removeEffect";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::removeEffect(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Engine_setDistanceModel(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:setDistanceModel";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		audio::Engine::DistanceModel arg0;
		ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Engine::setDistanceModel(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Engine_setDopplerScale(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:setDopplerScale";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Engine::setDopplerScale(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Engine_setEffect(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:setEffect";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 2) {
		std::string arg0;
		std::map<audio::Effect::Parameter, float> arg1;
		ok &= luaval_to_std_string(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_native(tolua_S, 3, &arg1, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		auto ret = audio::Engine::setEffect(arg0, arg1);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "2");
}
int lua_x_Audio_Engine_setOrientation(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:setOrientation";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 2) {
		cocos2d::Vec3 arg0;
		cocos2d::Vec3 arg1;
		ok &= luaval_to_vec3(tolua_S, 2, &arg0, LUA_FNAME);
		ok &= luaval_to_vec3(tolua_S, 3, &arg1, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Engine::setOrientation(arg0, arg1);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "2");
}
int lua_x_Audio_Engine_setPosition(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:setPosition";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		cocos2d::Vec3 arg0;
		ok &= luaval_to_vec3(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Engine::setPosition(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Engine_setVelocity(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:setVelocity";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		cocos2d::Vec3 arg0;
		ok &= luaval_to_vec3(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Engine::setVelocity(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Engine_setVolume(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:setVolume";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2, &arg0, LUA_FNAME);
		LUA_CHECK_PARAMETER(tolua_S, ok, LUA_FNAME);
		audio::Engine::setVolume(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
int lua_x_Audio_Engine_stop(lua_State* tolua_S)
{
	bool ok = true;
	constexpr auto LUA_OBJ_TYPE = "audio.Engine";
	constexpr auto LUA_FNAME = "audio.Engine:stop";
	LUA_CHECK_COBJ_TYPE(tolua_S, LUA_OBJ_TYPE, LUA_FNAME);
	const int argc = lua_gettop(tolua_S) - 1;
	do {
		if (argc == 0) {
			audio::Engine::stop();
			lua_settop(tolua_S, 1);
			return 1;
		}
	} while (0);
	ok = true;
	do {
		if (argc == 1) {
			std::vector<audio::Source *> arg0;
			ok &= luaval_to_native(tolua_S, 2, &arg0, LUA_FNAME);
			if (!ok) { break; }
			audio::Engine::stop(arg0);
			lua_settop(tolua_S, 1);
			return 1;
		}
	} while (0);
	ok = true;
	LUA_PARAMETER_ERROR(tolua_S, LUA_FNAME, argc, "1");
}
static int lua_x_Audio_Engine_finalize(lua_State* tolua_S)
{
	return 0;
}

int lua_register_x_Audio_Engine(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "audio.Engine");
	tolua_cclass(tolua_S, "Engine", "audio.Engine", "", nullptr);

	tolua_beginmodule(tolua_S, "Engine");
		tolua_function(tolua_S, "getActiveEffects", lua_x_Audio_Engine_getActiveEffects);
		tolua_function(tolua_S, "getActiveSourceCount", lua_x_Audio_Engine_getActiveSourceCount);
		tolua_function(tolua_S, "getDistanceModel", lua_x_Audio_Engine_getDistanceModel);
		tolua_function(tolua_S, "getDopplerScale", lua_x_Audio_Engine_getDopplerScale);
		tolua_function(tolua_S, "getEffect", lua_x_Audio_Engine_getEffect);
		tolua_function(tolua_S, "getEffectID", lua_x_Audio_Engine_getEffectID);
		tolua_function(tolua_S, "getFormat", lua_x_Audio_Engine_getFormat);
		tolua_function(tolua_S, "getLastError", lua_x_Audio_Engine_getLastError);
		tolua_function(tolua_S, "getMaxEffectCount", lua_x_Audio_Engine_getMaxEffectCount);
		tolua_function(tolua_S, "getMaxSourceCount", lua_x_Audio_Engine_getMaxSourceCount);
		tolua_function(tolua_S, "getMaxSourceEffectCount", lua_x_Audio_Engine_getMaxSourceEffectCount);
		tolua_function(tolua_S, "getOrientation", lua_x_Audio_Engine_getOrientation);
		tolua_function(tolua_S, "getPosition", lua_x_Audio_Engine_getPosition);
		tolua_function(tolua_S, "getRecordingDevices", lua_x_Audio_Engine_getRecordingDevices);
		tolua_function(tolua_S, "getVelocity", lua_x_Audio_Engine_getVelocity);
		tolua_function(tolua_S, "getVolume", lua_x_Audio_Engine_getVolume);
		tolua_function(tolua_S, "isEffectSupported", lua_x_Audio_Engine_isEffectSupported);
		tolua_function(tolua_S, "isValid", lua_x_Audio_Engine_isValid);
		tolua_function(tolua_S, "onEnterBackground", lua_x_Audio_Engine_onEnterBackground);
		tolua_function(tolua_S, "onEnterForeground", lua_x_Audio_Engine_onEnterForeground);
		tolua_function(tolua_S, "pause", lua_x_Audio_Engine_pause);
		tolua_function(tolua_S, "play", lua_x_Audio_Engine_play);
		tolua_function(tolua_S, "removeEffect", lua_x_Audio_Engine_removeEffect);
		tolua_function(tolua_S, "setDistanceModel", lua_x_Audio_Engine_setDistanceModel);
		tolua_function(tolua_S, "setDopplerScale", lua_x_Audio_Engine_setDopplerScale);
		tolua_function(tolua_S, "setEffect", lua_x_Audio_Engine_setEffect);
		tolua_function(tolua_S, "setOrientation", lua_x_Audio_Engine_setOrientation);
		tolua_function(tolua_S, "setPosition", lua_x_Audio_Engine_setPosition);
		tolua_function(tolua_S, "setVelocity", lua_x_Audio_Engine_setVelocity);
		tolua_function(tolua_S, "setVolume", lua_x_Audio_Engine_setVolume);
		tolua_function(tolua_S, "stop", lua_x_Audio_Engine_stop);
		{
			tolua_module(tolua_S, "DistanceModel", 0);
			tolua_beginmodule(tolua_S, "DistanceModel");
			{
				tolua_constant(tolua_S, "NONE", (lua_Number)audio::Engine::DistanceModel::NONE);
				tolua_constant(tolua_S, "INVERSE", (lua_Number)audio::Engine::DistanceModel::INVERSE);
				tolua_constant(tolua_S, "INVERSE_CLAMPED", (lua_Number)audio::Engine::DistanceModel::INVERSE_CLAMPED);
				tolua_constant(tolua_S, "LINEAR", (lua_Number)audio::Engine::DistanceModel::LINEAR);
				tolua_constant(tolua_S, "LINEAR_CLAMPED", (lua_Number)audio::Engine::DistanceModel::LINEAR_CLAMPED);
				tolua_constant(tolua_S, "EXPONENT", (lua_Number)audio::Engine::DistanceModel::EXPONENT);
				tolua_constant(tolua_S, "EXPONENT_CLAMPED", (lua_Number)audio::Engine::DistanceModel::EXPONENT_CLAMPED);
				tolua_constant(tolua_S, "MAX_ENUM", (lua_Number)audio::Engine::DistanceModel::MAX_ENUM);
			}
			tolua_endmodule(tolua_S);
		}
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(audio::Engine).name();
	g_luaType[typeName] = "audio.Engine";
	g_typeCast["Engine"] = "audio.Engine";
	return 1;
}

int register_all_cc_audio(lua_State* tolua_S)
{
	tolua_open(tolua_S);

	tolua_module(tolua_S, "audio", 0);
	tolua_beginmodule(tolua_S, "audio");

	lua_register_x_Audio_Engine(tolua_S);
	lua_register_x_Audio_Stream(tolua_S);
	lua_register_x_Audio_Source(tolua_S);
	lua_register_x_Audio_RecordingDevice(tolua_S);
	lua_register_x_Audio_Decoder(tolua_S);
	lua_register_x_Audio_SoundData(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

