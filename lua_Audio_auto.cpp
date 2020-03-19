#include "lua_audio_auto.hpp"
#include "AudioEngine.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_x_Audio_Source_getVolume(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getVolume'", nullptr);
            return 0;
        }
        double ret = cobj->getVolume();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getVolume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getTime(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getTime'", nullptr);
            return 0;
        }
        double ret = cobj->getTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getTime'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_isRelative(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_isRelative'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_isRelative'", nullptr);
            return 0;
        }
        bool ret = cobj->isRelative();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:isRelative",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_isRelative'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getBitDepth(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getBitDepth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getBitDepth'", nullptr);
            return 0;
        }
        int ret = cobj->getBitDepth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getBitDepth",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getBitDepth'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getRolloffFactor(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getRolloffFactor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getRolloffFactor'", nullptr);
            return 0;
        }
        double ret = cobj->getRolloffFactor();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getRolloffFactor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getRolloffFactor'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getActiveEffects(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getActiveEffects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getActiveEffects'", nullptr);
            return 0;
        }
        std::vector<std::string> ret = cobj->getActiveEffects();
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getActiveEffects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getActiveEffects'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getDirection(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getDirection'", nullptr);
            return 0;
        }
        cocos2d::Vec3 ret = cobj->getDirection();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getDirection",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getBytesPerFrame(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getBytesPerFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getBytesPerFrame'", nullptr);
            return 0;
        }
        int ret = cobj->getBytesPerFrame();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getBytesPerFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getBytesPerFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_seek(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_seek'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        long long arg0;

        ok &= luaval_to_long_long(tolua_S, 2,&arg0, "audio.Source:seek");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_seek'", nullptr);
            return 0;
        }
        cobj->seek(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:seek",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_seek'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setVelocity(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "audio.Source:setVelocity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setVelocity'", nullptr);
            return 0;
        }
        cobj->setVelocity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setVelocity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getPitch(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getPitch'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getPitch'", nullptr);
            return 0;
        }
        double ret = cobj->getPitch();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getPitch",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getPitch'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setEffect(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setEffect'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Source:setEffect");

            if (!ok) { break; }
            std::map<audio::Filter::Parameter, float> arg1;
            ok &= audio::lua::luaval_to_native(tolua_S, 3, &arg1, "audio.Source:setEffect");

            if (!ok) { break; }
            bool ret = cobj->setEffect(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Source:setEffect");

            if (!ok) { break; }
            bool ret = cobj->setEffect(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "audio.Source:setEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_pause(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_pause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_pause'", nullptr);
            return 0;
        }
        cobj->pause();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:pause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_pause'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getVelocity(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getVelocity'", nullptr);
            return 0;
        }
        cocos2d::Vec3 ret = cobj->getVelocity();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getVelocity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setDirection(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "audio.Source:setDirection");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setDirection'", nullptr);
            return 0;
        }
        cobj->setDirection(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setDirection",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getCone(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getCone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getCone'", nullptr);
            return 0;
        }
        std::array<float, 4> ret = cobj->getCone();
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getCone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getCone'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setRolloffFactor(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setRolloffFactor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setRolloffFactor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setRolloffFactor'", nullptr);
            return 0;
        }
        cobj->setRolloffFactor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setRolloffFactor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setRolloffFactor'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_removeFilter(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_removeFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_removeFilter'", nullptr);
            return 0;
        }
        bool ret = cobj->removeFilter();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:removeFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_removeFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getReferenceDistance(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getReferenceDistance'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getReferenceDistance'", nullptr);
            return 0;
        }
        double ret = cobj->getReferenceDistance();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getReferenceDistance",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getReferenceDistance'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getTotalTime(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getTotalTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getTotalTime'", nullptr);
            return 0;
        }
        double ret = cobj->getTotalTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getTotalTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getTotalTime'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getLoopingEnd(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getLoopingEnd'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getLoopingEnd'", nullptr);
            return 0;
        }
        double ret = cobj->getLoopingEnd();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getLoopingEnd",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getLoopingEnd'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getLoopingStart(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getLoopingStart'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getLoopingStart'", nullptr);
            return 0;
        }
        double ret = cobj->getLoopingStart();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getLoopingStart",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getLoopingStart'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setLoopingPoint(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setLoopingPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setLoopingPoint");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "audio.Source:setLoopingPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setLoopingPoint'", nullptr);
            return 0;
        }
        cobj->setLoopingPoint(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setLoopingPoint",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setLoopingPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setAirAbsorptionFactor(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setAirAbsorptionFactor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setAirAbsorptionFactor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setAirAbsorptionFactor'", nullptr);
            return 0;
        }
        cobj->setAirAbsorptionFactor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setAirAbsorptionFactor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setAirAbsorptionFactor'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_tell(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_tell'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_tell'", nullptr);
            return 0;
        }
        long long ret = cobj->tell();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:tell",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_tell'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getMinVolume(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getMinVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getMinVolume'", nullptr);
            return 0;
        }
        double ret = cobj->getMinVolume();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getMinVolume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getMinVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setVolume(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setVolume");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setVolume'", nullptr);
            return 0;
        }
        cobj->setVolume(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setVolume",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_play(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_play'", nullptr);
            return 0;
        }
        bool ret = cobj->play();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:play",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_play'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getFilter(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getFilter'", nullptr);
            return 0;
        }
        std::map<audio::Filter::Parameter, float> ret = cobj->getFilter();
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setMinVolume(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setMinVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setMinVolume");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setMinVolume'", nullptr);
            return 0;
        }
        cobj->setMinVolume(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setMinVolume",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setMinVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_isFinished(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_isFinished'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_isFinished'", nullptr);
            return 0;
        }
        bool ret = cobj->isFinished();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:isFinished",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_isFinished'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_clone(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_clone'", nullptr);
            return 0;
        }
        audio::Source* ret = cobj->clone();
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_stop(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_stop'", nullptr);
            return 0;
        }
        cobj->stop();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:stop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getChannelCount(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getChannelCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getChannelCount'", nullptr);
            return 0;
        }
        int ret = cobj->getChannelCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getChannelCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getChannelCount'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getTotalFrames(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getTotalFrames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getTotalFrames'", nullptr);
            return 0;
        }
        long long ret = cobj->getTotalFrames();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getTotalFrames",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getTotalFrames'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setTime(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setTime'", nullptr);
            return 0;
        }
        cobj->setTime(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setTime'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_isLooping(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_isLooping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_isLooping'", nullptr);
            return 0;
        }
        bool ret = cobj->isLooping();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:isLooping",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_isLooping'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "audio.Source:setPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setPosition'", nullptr);
            return 0;
        }
        cobj->setPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setPosition",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_isPlaying(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_isPlaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_isPlaying'", nullptr);
            return 0;
        }
        bool ret = cobj->isPlaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:isPlaying",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_isPlaying'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getEffect(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Source:getEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getEffect'", nullptr);
            return 0;
        }
        std::map<audio::Filter::Parameter, float> ret = cobj->getEffect(arg0);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setReferenceDistance(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setReferenceDistance'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setReferenceDistance");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setReferenceDistance'", nullptr);
            return 0;
        }
        cobj->setReferenceDistance(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setReferenceDistance",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setReferenceDistance'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getPosition'", nullptr);
            return 0;
        }
        cocos2d::Vec3 ret = cobj->getPosition();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setFilter(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::map<audio::Filter::Parameter, float> arg0;

        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Source:setFilter");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setFilter'", nullptr);
            return 0;
        }
        bool ret = cobj->setFilter(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setFilter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getFreeBufferCount(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getFreeBufferCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getFreeBufferCount'", nullptr);
            return 0;
        }
        int ret = cobj->getFreeBufferCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getFreeBufferCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getFreeBufferCount'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_isSupportLoopingPoint(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_isSupportLoopingPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_isSupportLoopingPoint'", nullptr);
            return 0;
        }
        bool ret = cobj->isSupportLoopingPoint();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:isSupportLoopingPoint",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_isSupportLoopingPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getMaxDistance(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getMaxDistance'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getMaxDistance'", nullptr);
            return 0;
        }
        double ret = cobj->getMaxDistance();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getMaxDistance",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getMaxDistance'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getAirAbsorptionFactor(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getAirAbsorptionFactor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getAirAbsorptionFactor'", nullptr);
            return 0;
        }
        double ret = cobj->getAirAbsorptionFactor();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getAirAbsorptionFactor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getAirAbsorptionFactor'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setMaxVolume(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setMaxVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setMaxVolume");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setMaxVolume'", nullptr);
            return 0;
        }
        cobj->setMaxVolume(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setMaxVolume",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setMaxVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getLastError(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getLastError'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getLastError'", nullptr);
            return 0;
        }
        std::string ret = cobj->getLastError();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getLastError",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getLastError'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_queue(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_queue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        audio::SoundData* arg0;

        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Source:queue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_queue'", nullptr);
            return 0;
        }
        bool ret = cobj->queue(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        audio::SoundData* arg0;
        ssize_t arg1;

        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Source:queue");

        ok &= luaval_to_ssize(tolua_S, 3, &arg1, "audio.Source:queue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_queue'", nullptr);
            return 0;
        }
        bool ret = cobj->queue(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 3) 
    {
        audio::SoundData* arg0;
        ssize_t arg1;
        ssize_t arg2;

        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Source:queue");

        ok &= luaval_to_ssize(tolua_S, 3, &arg1, "audio.Source:queue");

        ok &= luaval_to_ssize(tolua_S, 4, &arg2, "audio.Source:queue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_queue'", nullptr);
            return 0;
        }
        bool ret = cobj->queue(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:queue",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_queue'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getSampleRate(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getSampleRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getSampleRate'", nullptr);
            return 0;
        }
        int ret = cobj->getSampleRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getSampleRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getSampleRate'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setRelative(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setRelative'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "audio.Source:setRelative");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setRelative'", nullptr);
            return 0;
        }
        cobj->setRelative(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setRelative",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setRelative'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setCone(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setCone'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::array<float, 4> arg0;
            ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "setCone");

            if (!ok) { break; }
            cobj->setCone(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setCone");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "audio.Source:setCone");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "audio.Source:setCone");

            if (!ok) { break; }
            double arg3;
            ok &= luaval_to_number(tolua_S, 5,&arg3, "audio.Source:setCone");

            if (!ok) { break; }
            cobj->setCone(arg0, arg1, arg2, arg3);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "audio.Source:setCone",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setCone'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_getMaxVolume(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_getMaxVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_getMaxVolume'", nullptr);
            return 0;
        }
        double ret = cobj->getMaxVolume();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:getMaxVolume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_getMaxVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setMaxDistance(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setMaxDistance'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setMaxDistance");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setMaxDistance'", nullptr);
            return 0;
        }
        cobj->setMaxDistance(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setMaxDistance",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setMaxDistance'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setPitch(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setPitch'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Source:setPitch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setPitch'", nullptr);
            return 0;
        }
        cobj->setPitch(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setPitch",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setPitch'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_setLooping(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_setLooping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "audio.Source:setLooping");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_setLooping'", nullptr);
            return 0;
        }
        cobj->setLooping(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:setLooping",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_setLooping'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_removeEffect(lua_State* tolua_S)
{
    int argc = 0;
    audio::Source* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Source*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Source_removeEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Source:removeEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_removeEffect'", nullptr);
            return 0;
        }
        bool ret = cobj->removeEffect(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Source:removeEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_removeEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Source_pauseBatch(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::vector<audio::Source *> arg0;
        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Source:pauseBatch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_pauseBatch'", nullptr);
            return 0;
        }
        audio::Source::pauseBatch(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Source:pauseBatch",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_pauseBatch'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Source_playBatch(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::vector<audio::Source *> arg0;
        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Source:playBatch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_playBatch'", nullptr);
            return 0;
        }
        bool ret = audio::Source::playBatch(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Source:playBatch",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_playBatch'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Source_createFromDecoder(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        audio::Decoder* arg0;
        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Source:createFromDecoder");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_createFromDecoder'", nullptr);
            return 0;
        }
        audio::Source* ret = audio::Source::createFromDecoder(arg0);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Source:createFromDecoder",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_createFromDecoder'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Source_createFromSoundData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        audio::SoundData* arg0;
        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Source:createFromSoundData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_createFromSoundData'", nullptr);
            return 0;
        }
        audio::Source* ret = audio::Source::createFromSoundData(arg0);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Source:createFromSoundData",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_createFromSoundData'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Source_stopBatch(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::vector<audio::Source *> arg0;
        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Source:stopBatch");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_stopBatch'", nullptr);
            return 0;
        }
        audio::Source::stopBatch(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Source:stopBatch",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_stopBatch'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Source_pauseAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_pauseAll'", nullptr);
            return 0;
        }
        std::vector<audio::Source *> ret = audio::Source::pauseAll();
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Source:pauseAll",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_pauseAll'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Source_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "audio.Source:create");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "audio.Source:create");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "audio.Source:create");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "audio.Source:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_create'", nullptr);
            return 0;
        }
        audio::Source* ret = audio::Source::create(arg0, arg1, arg2, arg3);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Source:create",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_create'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Source_stopAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Source",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Source_stopAll'", nullptr);
            return 0;
        }
        audio::Source::stopAll();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Source:stopAll",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Source_stopAll'.",&tolua_err);
#endif
    return 0;
}
static int lua_x_Audio_Source_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Source)");
    return 0;
}

int lua_register_x_Audio_Source(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"audio.Source");
    tolua_cclass(tolua_S,"Source","audio.Source","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Source");
        tolua_function(tolua_S,"getVolume",lua_x_Audio_Source_getVolume);
        tolua_function(tolua_S,"getTime",lua_x_Audio_Source_getTime);
        tolua_function(tolua_S,"isRelative",lua_x_Audio_Source_isRelative);
        tolua_function(tolua_S,"getBitDepth",lua_x_Audio_Source_getBitDepth);
        tolua_function(tolua_S,"getRolloffFactor",lua_x_Audio_Source_getRolloffFactor);
        tolua_function(tolua_S,"getActiveEffects",lua_x_Audio_Source_getActiveEffects);
        tolua_function(tolua_S,"getDirection",lua_x_Audio_Source_getDirection);
        tolua_function(tolua_S,"getBytesPerFrame",lua_x_Audio_Source_getBytesPerFrame);
        tolua_function(tolua_S,"seek",lua_x_Audio_Source_seek);
        tolua_function(tolua_S,"setVelocity",lua_x_Audio_Source_setVelocity);
        tolua_function(tolua_S,"getPitch",lua_x_Audio_Source_getPitch);
        tolua_function(tolua_S,"setEffect",lua_x_Audio_Source_setEffect);
        tolua_function(tolua_S,"pause",lua_x_Audio_Source_pause);
        tolua_function(tolua_S,"getVelocity",lua_x_Audio_Source_getVelocity);
        tolua_function(tolua_S,"setDirection",lua_x_Audio_Source_setDirection);
        tolua_function(tolua_S,"getCone",lua_x_Audio_Source_getCone);
        tolua_function(tolua_S,"setRolloffFactor",lua_x_Audio_Source_setRolloffFactor);
        tolua_function(tolua_S,"removeFilter",lua_x_Audio_Source_removeFilter);
        tolua_function(tolua_S,"getReferenceDistance",lua_x_Audio_Source_getReferenceDistance);
        tolua_function(tolua_S,"getTotalTime",lua_x_Audio_Source_getTotalTime);
        tolua_function(tolua_S,"getLoopingEnd",lua_x_Audio_Source_getLoopingEnd);
        tolua_function(tolua_S,"getLoopingStart",lua_x_Audio_Source_getLoopingStart);
        tolua_function(tolua_S,"setLoopingPoint",lua_x_Audio_Source_setLoopingPoint);
        tolua_function(tolua_S,"setAirAbsorptionFactor",lua_x_Audio_Source_setAirAbsorptionFactor);
        tolua_function(tolua_S,"tell",lua_x_Audio_Source_tell);
        tolua_function(tolua_S,"getMinVolume",lua_x_Audio_Source_getMinVolume);
        tolua_function(tolua_S,"setVolume",lua_x_Audio_Source_setVolume);
        tolua_function(tolua_S,"play",lua_x_Audio_Source_play);
        tolua_function(tolua_S,"getFilter",lua_x_Audio_Source_getFilter);
        tolua_function(tolua_S,"setMinVolume",lua_x_Audio_Source_setMinVolume);
        tolua_function(tolua_S,"isFinished",lua_x_Audio_Source_isFinished);
        tolua_function(tolua_S,"clone",lua_x_Audio_Source_clone);
        tolua_function(tolua_S,"stop",lua_x_Audio_Source_stop);
        tolua_function(tolua_S,"getChannelCount",lua_x_Audio_Source_getChannelCount);
        tolua_function(tolua_S,"getTotalFrames",lua_x_Audio_Source_getTotalFrames);
        tolua_function(tolua_S,"setTime",lua_x_Audio_Source_setTime);
        tolua_function(tolua_S,"isLooping",lua_x_Audio_Source_isLooping);
        tolua_function(tolua_S,"setPosition",lua_x_Audio_Source_setPosition);
        tolua_function(tolua_S,"isPlaying",lua_x_Audio_Source_isPlaying);
        tolua_function(tolua_S,"getEffect",lua_x_Audio_Source_getEffect);
        tolua_function(tolua_S,"setReferenceDistance",lua_x_Audio_Source_setReferenceDistance);
        tolua_function(tolua_S,"getPosition",lua_x_Audio_Source_getPosition);
        tolua_function(tolua_S,"setFilter",lua_x_Audio_Source_setFilter);
        tolua_function(tolua_S,"getFreeBufferCount",lua_x_Audio_Source_getFreeBufferCount);
        tolua_function(tolua_S,"isSupportLoopingPoint",lua_x_Audio_Source_isSupportLoopingPoint);
        tolua_function(tolua_S,"getMaxDistance",lua_x_Audio_Source_getMaxDistance);
        tolua_function(tolua_S,"getAirAbsorptionFactor",lua_x_Audio_Source_getAirAbsorptionFactor);
        tolua_function(tolua_S,"setMaxVolume",lua_x_Audio_Source_setMaxVolume);
        tolua_function(tolua_S,"getLastError",lua_x_Audio_Source_getLastError);
        tolua_function(tolua_S,"queue",lua_x_Audio_Source_queue);
        tolua_function(tolua_S,"getSampleRate",lua_x_Audio_Source_getSampleRate);
        tolua_function(tolua_S,"setRelative",lua_x_Audio_Source_setRelative);
        tolua_function(tolua_S,"setCone",lua_x_Audio_Source_setCone);
        tolua_function(tolua_S,"getMaxVolume",lua_x_Audio_Source_getMaxVolume);
        tolua_function(tolua_S,"setMaxDistance",lua_x_Audio_Source_setMaxDistance);
        tolua_function(tolua_S,"setPitch",lua_x_Audio_Source_setPitch);
        tolua_function(tolua_S,"setLooping",lua_x_Audio_Source_setLooping);
        tolua_function(tolua_S,"removeEffect",lua_x_Audio_Source_removeEffect);
        tolua_function(tolua_S,"pauseBatch", lua_x_Audio_Source_pauseBatch);
        tolua_function(tolua_S,"playBatch", lua_x_Audio_Source_playBatch);
        tolua_function(tolua_S,"createFromDecoder", lua_x_Audio_Source_createFromDecoder);
        tolua_function(tolua_S,"createFromSoundData", lua_x_Audio_Source_createFromSoundData);
        tolua_function(tolua_S,"stopBatch", lua_x_Audio_Source_stopBatch);
        tolua_function(tolua_S,"pauseAll", lua_x_Audio_Source_pauseAll);
        tolua_function(tolua_S,"create", lua_x_Audio_Source_create);
        tolua_function(tolua_S,"stopAll", lua_x_Audio_Source_stopAll);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(audio::Source).name();
    g_luaType[typeName] = "audio.Source";
    g_typeCast["Source"] = "audio.Source";
    return 1;
}

int lua_x_Audio_Stream_lock(lua_State* tolua_S)
{
    int argc = 0;
    audio::Stream* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Stream",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Stream*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Stream_lock'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Stream_lock'", nullptr);
            return 0;
        }
        cobj->lock();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Stream:lock",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Stream_lock'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Stream_unlock(lua_State* tolua_S)
{
    int argc = 0;
    audio::Stream* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Stream",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Stream*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Stream_unlock'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Stream_unlock'", nullptr);
            return 0;
        }
        cobj->unlock();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Stream:unlock",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Stream_unlock'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Stream_seek(lua_State* tolua_S)
{
    int argc = 0;
    audio::Stream* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Stream",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Stream*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Stream_seek'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        audio::Stream::SeekOrigin arg0;
        long long arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "audio.Stream:seek");

        ok &= luaval_to_long_long(tolua_S, 3,&arg1, "audio.Stream:seek");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Stream_seek'", nullptr);
            return 0;
        }
        bool ret = cobj->seek(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Stream:seek",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Stream_seek'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Stream_tell(lua_State* tolua_S)
{
    int argc = 0;
    audio::Stream* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Stream",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Stream*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Stream_tell'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Stream_tell'", nullptr);
            return 0;
        }
        unsigned long long ret = cobj->tell();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Stream:tell",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Stream_tell'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Stream_size(lua_State* tolua_S)
{
    int argc = 0;
    audio::Stream* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Stream",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Stream*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Stream_size'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Stream_size'", nullptr);
            return 0;
        }
        unsigned long long ret = cobj->size();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Stream:size",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Stream_size'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Stream_createFromFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Stream",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Stream:createFromFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Stream_createFromFile'", nullptr);
            return 0;
        }
        audio::Stream* ret = audio::Stream::createFromFile(arg0);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Stream:createFromFile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Stream_createFromFile'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Stream_createFromLocalFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Stream",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Stream:createFromLocalFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Stream_createFromLocalFile'", nullptr);
            return 0;
        }
        audio::Stream* ret = audio::Stream::createFromLocalFile(arg0);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Stream:createFromLocalFile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Stream_createFromLocalFile'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Stream_createFromSoundData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Stream",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        audio::SoundData* arg0;
        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Stream:createFromSoundData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Stream_createFromSoundData'", nullptr);
            return 0;
        }
        audio::Stream* ret = audio::Stream::createFromSoundData(arg0);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Stream:createFromSoundData",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Stream_createFromSoundData'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Stream_createFromStringData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Stream",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Stream:createFromStringData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Stream_createFromStringData'", nullptr);
            return 0;
        }
        audio::Stream* ret = audio::Stream::createFromStringData(arg0);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Stream:createFromStringData",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Stream_createFromStringData'.",&tolua_err);
#endif
    return 0;
}
static int lua_x_Audio_Stream_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Stream)");
    return 0;
}

int lua_register_x_Audio_Stream(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"audio.Stream");
    tolua_cclass(tolua_S,"Stream","audio.Stream","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Stream");
        tolua_function(tolua_S,"lock",lua_x_Audio_Stream_lock);
        tolua_function(tolua_S,"unlock",lua_x_Audio_Stream_unlock);
        tolua_function(tolua_S,"seek",lua_x_Audio_Stream_seek);
        tolua_function(tolua_S,"tell",lua_x_Audio_Stream_tell);
        tolua_function(tolua_S,"size",lua_x_Audio_Stream_size);
        tolua_function(tolua_S,"createFromFile", lua_x_Audio_Stream_createFromFile);
        tolua_function(tolua_S,"createFromLocalFile", lua_x_Audio_Stream_createFromLocalFile);
        tolua_function(tolua_S,"createFromSoundData", lua_x_Audio_Stream_createFromSoundData);
        tolua_function(tolua_S,"createFromStringData", lua_x_Audio_Stream_createFromStringData);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(audio::Stream).name();
    g_luaType[typeName] = "audio.Stream";
    g_typeCast["Stream"] = "audio.Stream";
    return 1;
}

int lua_x_Audio_Decoder_getBufferSize(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_getBufferSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_getBufferSize'", nullptr);
            return 0;
        }
        int ret = cobj->getBufferSize();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:getBufferSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_getBufferSize'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_seekTime(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_seekTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Decoder:seekTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_seekTime'", nullptr);
            return 0;
        }
        bool ret = cobj->seekTime(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:seekTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_seekTime'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_isFinished(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_isFinished'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_isFinished'", nullptr);
            return 0;
        }
        bool ret = cobj->isFinished();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:isFinished",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_isFinished'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_clone(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_clone'", nullptr);
            return 0;
        }
        audio::Decoder* ret = cobj->clone();
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_getBitDepth(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_getBitDepth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_getBitDepth'", nullptr);
            return 0;
        }
        long long ret = cobj->getBitDepth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:getBitDepth",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_getBitDepth'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_getTotalFrames(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_getTotalFrames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_getTotalFrames'", nullptr);
            return 0;
        }
        long long ret = cobj->getTotalFrames();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:getTotalFrames",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_getTotalFrames'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_getChannelCount(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_getChannelCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_getChannelCount'", nullptr);
            return 0;
        }
        long long ret = cobj->getChannelCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:getChannelCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_getChannelCount'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_getSampleRate(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_getSampleRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_getSampleRate'", nullptr);
            return 0;
        }
        long long ret = cobj->getSampleRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:getSampleRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_getSampleRate'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_isSeekable(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_isSeekable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_isSeekable'", nullptr);
            return 0;
        }
        bool ret = cobj->isSeekable();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:isSeekable",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_isSeekable'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_getLoopingEnd(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_getLoopingEnd'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_getLoopingEnd'", nullptr);
            return 0;
        }
        double ret = cobj->getLoopingEnd();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:getLoopingEnd",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_getLoopingEnd'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_getBytesPerFrame(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_getBytesPerFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_getBytesPerFrame'", nullptr);
            return 0;
        }
        long long ret = cobj->getBytesPerFrame();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:getBytesPerFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_getBytesPerFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_rewind(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_rewind'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_rewind'", nullptr);
            return 0;
        }
        bool ret = cobj->rewind();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:rewind",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_rewind'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_seek(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_seek'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        long long arg0;

        ok &= luaval_to_long_long(tolua_S, 2,&arg0, "audio.Decoder:seek");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_seek'", nullptr);
            return 0;
        }
        bool ret = cobj->seek(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:seek",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_seek'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_tell(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_tell'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_tell'", nullptr);
            return 0;
        }
        long long ret = cobj->tell();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:tell",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_tell'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_getDuration(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_getDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_getDuration'", nullptr);
            return 0;
        }
        double ret = cobj->getDuration();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:getDuration",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_getDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_getLoopingStart(lua_State* tolua_S)
{
    int argc = 0;
    audio::Decoder* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::Decoder*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_Decoder_getLoopingStart'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_getLoopingStart'", nullptr);
            return 0;
        }
        double ret = cobj->getLoopingStart();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.Decoder:getLoopingStart",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_getLoopingStart'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_Decoder_createFromFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        unsigned int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Decoder:createFromFile");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "audio.Decoder:createFromFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_createFromFile'", nullptr);
            return 0;
        }
        audio::Decoder* ret = audio::Decoder::createFromFile(arg0, arg1);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    if (argc == 3)
    {
        std::string arg0;
        unsigned int arg1;
        audio::Decoder::DecoderType arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Decoder:createFromFile");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "audio.Decoder:createFromFile");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "audio.Decoder:createFromFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_createFromFile'", nullptr);
            return 0;
        }
        audio::Decoder* ret = audio::Decoder::createFromFile(arg0, arg1, arg2);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Decoder:createFromFile",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_createFromFile'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Decoder_createFromSoundData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        audio::SoundData* arg0;
        unsigned int arg1;
        audio::Decoder::DecoderType arg2;
        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Decoder:createFromSoundData");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "audio.Decoder:createFromSoundData");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "audio.Decoder:createFromSoundData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_createFromSoundData'", nullptr);
            return 0;
        }
        audio::Decoder* ret = audio::Decoder::createFromSoundData(arg0, arg1, arg2);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Decoder:createFromSoundData",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_createFromSoundData'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Decoder_createFromStringData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        unsigned int arg1;
        audio::Decoder::DecoderType arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Decoder:createFromStringData");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "audio.Decoder:createFromStringData");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "audio.Decoder:createFromStringData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_createFromStringData'", nullptr);
            return 0;
        }
        audio::Decoder* ret = audio::Decoder::createFromStringData(arg0, arg1, arg2);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Decoder:createFromStringData",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_createFromStringData'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Decoder_getDecoderTypeFromPath(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Decoder:getDecoderTypeFromPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_getDecoderTypeFromPath'", nullptr);
            return 0;
        }
        int ret = (int)audio::Decoder::getDecoderTypeFromPath(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Decoder:getDecoderTypeFromPath",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_getDecoderTypeFromPath'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Decoder_createFromLocalFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        unsigned int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Decoder:createFromLocalFile");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "audio.Decoder:createFromLocalFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_createFromLocalFile'", nullptr);
            return 0;
        }
        audio::Decoder* ret = audio::Decoder::createFromLocalFile(arg0, arg1);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    if (argc == 3)
    {
        std::string arg0;
        unsigned int arg1;
        audio::Decoder::DecoderType arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Decoder:createFromLocalFile");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "audio.Decoder:createFromLocalFile");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "audio.Decoder:createFromLocalFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_createFromLocalFile'", nullptr);
            return 0;
        }
        audio::Decoder* ret = audio::Decoder::createFromLocalFile(arg0, arg1, arg2);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Decoder:createFromLocalFile",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_createFromLocalFile'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Decoder_createFromStream(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Decoder",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        audio::Stream* arg0;
        unsigned int arg1;
        audio::Decoder::DecoderType arg2;
        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Decoder:createFromStream");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "audio.Decoder:createFromStream");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "audio.Decoder:createFromStream");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Decoder_createFromStream'", nullptr);
            return 0;
        }
        audio::Decoder* ret = audio::Decoder::createFromStream(arg0, arg1, arg2);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Decoder:createFromStream",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Decoder_createFromStream'.",&tolua_err);
#endif
    return 0;
}
static int lua_x_Audio_Decoder_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Decoder)");
    return 0;
}

int lua_register_x_Audio_Decoder(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"audio.Decoder");
    tolua_cclass(tolua_S,"Decoder","audio.Decoder","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Decoder");
        tolua_function(tolua_S,"getBufferSize",lua_x_Audio_Decoder_getBufferSize);
        tolua_function(tolua_S,"seekTime",lua_x_Audio_Decoder_seekTime);
        tolua_function(tolua_S,"isFinished",lua_x_Audio_Decoder_isFinished);
        tolua_function(tolua_S,"clone",lua_x_Audio_Decoder_clone);
        tolua_function(tolua_S,"getBitDepth",lua_x_Audio_Decoder_getBitDepth);
        tolua_function(tolua_S,"getTotalFrames",lua_x_Audio_Decoder_getTotalFrames);
        tolua_function(tolua_S,"getChannelCount",lua_x_Audio_Decoder_getChannelCount);
        tolua_function(tolua_S,"getSampleRate",lua_x_Audio_Decoder_getSampleRate);
        tolua_function(tolua_S,"isSeekable",lua_x_Audio_Decoder_isSeekable);
        tolua_function(tolua_S,"getLoopingEnd",lua_x_Audio_Decoder_getLoopingEnd);
        tolua_function(tolua_S,"getBytesPerFrame",lua_x_Audio_Decoder_getBytesPerFrame);
        tolua_function(tolua_S,"rewind",lua_x_Audio_Decoder_rewind);
        tolua_function(tolua_S,"seek",lua_x_Audio_Decoder_seek);
        tolua_function(tolua_S,"tell",lua_x_Audio_Decoder_tell);
        tolua_function(tolua_S,"getDuration",lua_x_Audio_Decoder_getDuration);
        tolua_function(tolua_S,"getLoopingStart",lua_x_Audio_Decoder_getLoopingStart);
        tolua_function(tolua_S,"createFromFile", lua_x_Audio_Decoder_createFromFile);
        tolua_function(tolua_S,"createFromSoundData", lua_x_Audio_Decoder_createFromSoundData);
        tolua_function(tolua_S,"createFromStringData", lua_x_Audio_Decoder_createFromStringData);
        tolua_function(tolua_S,"getDecoderTypeFromPath", lua_x_Audio_Decoder_getDecoderTypeFromPath);
        tolua_function(tolua_S,"createFromLocalFile", lua_x_Audio_Decoder_createFromLocalFile);
        tolua_function(tolua_S,"createFromStream", lua_x_Audio_Decoder_createFromStream);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(audio::Decoder).name();
    g_luaType[typeName] = "audio.Decoder";
    g_typeCast["Decoder"] = "audio.Decoder";
    return 1;
}

int lua_x_Audio_SoundData_getLastError(lua_State* tolua_S)
{
    int argc = 0;
    audio::SoundData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.SoundData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::SoundData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_SoundData_getLastError'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_SoundData_getLastError'", nullptr);
            return 0;
        }
        std::string ret = cobj->getLastError();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.SoundData:getLastError",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_SoundData_getLastError'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_SoundData_getSample(lua_State* tolua_S)
{
    int argc = 0;
    audio::SoundData* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.SoundData",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (audio::SoundData*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_SoundData_getSample'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "audio.SoundData:getSample");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "audio.SoundData:getSample");

            if (!ok) { break; }
            double ret = cobj->getSample(arg0, arg1);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "audio.SoundData:getSample");

            if (!ok) { break; }
            double ret = cobj->getSample(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "audio.SoundData:getSample",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_SoundData_getSample'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_SoundData_clone(lua_State* tolua_S)
{
    int argc = 0;
    audio::SoundData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.SoundData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::SoundData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_SoundData_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_SoundData_clone'", nullptr);
            return 0;
        }
        audio::SoundData* ret = cobj->clone();
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.SoundData:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_SoundData_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_SoundData_getBitDepth(lua_State* tolua_S)
{
    int argc = 0;
    audio::SoundData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.SoundData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::SoundData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_SoundData_getBitDepth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_SoundData_getBitDepth'", nullptr);
            return 0;
        }
        int ret = cobj->getBitDepth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.SoundData:getBitDepth",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_SoundData_getBitDepth'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_SoundData_getChannelCount(lua_State* tolua_S)
{
    int argc = 0;
    audio::SoundData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.SoundData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::SoundData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_SoundData_getChannelCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_SoundData_getChannelCount'", nullptr);
            return 0;
        }
        int ret = cobj->getChannelCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.SoundData:getChannelCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_SoundData_getChannelCount'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_SoundData_getSize(lua_State* tolua_S)
{
    int argc = 0;
    audio::SoundData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.SoundData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::SoundData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_SoundData_getSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_SoundData_getSize'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getSize();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.SoundData:getSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_SoundData_getSize'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_SoundData_getSampleRate(lua_State* tolua_S)
{
    int argc = 0;
    audio::SoundData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.SoundData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::SoundData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_SoundData_getSampleRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_SoundData_getSampleRate'", nullptr);
            return 0;
        }
        int ret = cobj->getSampleRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.SoundData:getSampleRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_SoundData_getSampleRate'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_SoundData_getDuration(lua_State* tolua_S)
{
    int argc = 0;
    audio::SoundData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.SoundData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::SoundData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_SoundData_getDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_SoundData_getDuration'", nullptr);
            return 0;
        }
        double ret = cobj->getDuration();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.SoundData:getDuration",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_SoundData_getDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_SoundData_getSampleCount(lua_State* tolua_S)
{
    int argc = 0;
    audio::SoundData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.SoundData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::SoundData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_SoundData_getSampleCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_SoundData_getSampleCount'", nullptr);
            return 0;
        }
        int ret = cobj->getSampleCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.SoundData:getSampleCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_SoundData_getSampleCount'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_SoundData_setSample(lua_State* tolua_S)
{
    int argc = 0;
    audio::SoundData* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.SoundData",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (audio::SoundData*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_SoundData_setSample'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "audio.SoundData:setSample");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "audio.SoundData:setSample");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "audio.SoundData:setSample");

            if (!ok) { break; }
            cobj->setSample(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "audio.SoundData:setSample");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "audio.SoundData:setSample");

            if (!ok) { break; }
            cobj->setSample(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "audio.SoundData:setSample",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_SoundData_setSample'.",&tolua_err);
#endif

    return 0;
}
static int lua_x_Audio_SoundData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SoundData)");
    return 0;
}

int lua_register_x_Audio_SoundData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"audio.SoundData");
    tolua_cclass(tolua_S,"SoundData","audio.SoundData","",nullptr);

    tolua_beginmodule(tolua_S,"SoundData");
        tolua_function(tolua_S,"getLastError",lua_x_Audio_SoundData_getLastError);
        tolua_function(tolua_S,"getSample",lua_x_Audio_SoundData_getSample);
        tolua_function(tolua_S,"clone",lua_x_Audio_SoundData_clone);
        tolua_function(tolua_S,"getBitDepth",lua_x_Audio_SoundData_getBitDepth);
        tolua_function(tolua_S,"getChannelCount",lua_x_Audio_SoundData_getChannelCount);
        tolua_function(tolua_S,"getSize",lua_x_Audio_SoundData_getSize);
        tolua_function(tolua_S,"getSampleRate",lua_x_Audio_SoundData_getSampleRate);
        tolua_function(tolua_S,"getDuration",lua_x_Audio_SoundData_getDuration);
        tolua_function(tolua_S,"getSampleCount",lua_x_Audio_SoundData_getSampleCount);
        tolua_function(tolua_S,"setSample",lua_x_Audio_SoundData_setSample);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(audio::SoundData).name();
    g_luaType[typeName] = "audio.SoundData";
    g_typeCast["SoundData"] = "audio.SoundData";
    return 1;
}

int lua_x_Audio_RecordingDevice_getSampleRate(lua_State* tolua_S)
{
    int argc = 0;
    audio::RecordingDevice* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.RecordingDevice",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_RecordingDevice_getSampleRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_RecordingDevice_getSampleRate'", nullptr);
            return 0;
        }
        int ret = cobj->getSampleRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.RecordingDevice:getSampleRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_RecordingDevice_getSampleRate'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_RecordingDevice_getName(lua_State* tolua_S)
{
    int argc = 0;
    audio::RecordingDevice* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.RecordingDevice",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_RecordingDevice_getName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_RecordingDevice_getName'", nullptr);
            return 0;
        }
        std::string ret = cobj->getName();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.RecordingDevice:getName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_RecordingDevice_getName'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_RecordingDevice_getBitDepth(lua_State* tolua_S)
{
    int argc = 0;
    audio::RecordingDevice* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.RecordingDevice",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_RecordingDevice_getBitDepth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_RecordingDevice_getBitDepth'", nullptr);
            return 0;
        }
        int ret = cobj->getBitDepth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.RecordingDevice:getBitDepth",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_RecordingDevice_getBitDepth'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_RecordingDevice_stop(lua_State* tolua_S)
{
    int argc = 0;
    audio::RecordingDevice* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.RecordingDevice",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_RecordingDevice_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_RecordingDevice_stop'", nullptr);
            return 0;
        }
        cobj->stop();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.RecordingDevice:stop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_RecordingDevice_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_RecordingDevice_getChannelCount(lua_State* tolua_S)
{
    int argc = 0;
    audio::RecordingDevice* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.RecordingDevice",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_RecordingDevice_getChannelCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_RecordingDevice_getChannelCount'", nullptr);
            return 0;
        }
        int ret = cobj->getChannelCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.RecordingDevice:getChannelCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_RecordingDevice_getChannelCount'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_RecordingDevice_getMaxSamples(lua_State* tolua_S)
{
    int argc = 0;
    audio::RecordingDevice* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.RecordingDevice",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_RecordingDevice_getMaxSamples'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_RecordingDevice_getMaxSamples'", nullptr);
            return 0;
        }
        int ret = cobj->getMaxSamples();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.RecordingDevice:getMaxSamples",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_RecordingDevice_getMaxSamples'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_RecordingDevice_start(lua_State* tolua_S)
{
    int argc = 0;
    audio::RecordingDevice* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.RecordingDevice",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_RecordingDevice_start'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "audio.RecordingDevice:start");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "audio.RecordingDevice:start");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "audio.RecordingDevice:start");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "audio.RecordingDevice:start");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_RecordingDevice_start'", nullptr);
            return 0;
        }
        bool ret = cobj->start(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.RecordingDevice:start",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_RecordingDevice_start'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_RecordingDevice_getSampleCount(lua_State* tolua_S)
{
    int argc = 0;
    audio::RecordingDevice* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.RecordingDevice",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_RecordingDevice_getSampleCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_RecordingDevice_getSampleCount'", nullptr);
            return 0;
        }
        int ret = cobj->getSampleCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.RecordingDevice:getSampleCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_RecordingDevice_getSampleCount'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_RecordingDevice_getData(lua_State* tolua_S)
{
    int argc = 0;
    audio::RecordingDevice* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.RecordingDevice",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_RecordingDevice_getData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_RecordingDevice_getData'", nullptr);
            return 0;
        }
        audio::SoundData* ret = cobj->getData();
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.RecordingDevice:getData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_RecordingDevice_getData'.",&tolua_err);
#endif

    return 0;
}
int lua_x_Audio_RecordingDevice_isRecording(lua_State* tolua_S)
{
    int argc = 0;
    audio::RecordingDevice* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"audio.RecordingDevice",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (audio::RecordingDevice*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_x_Audio_RecordingDevice_isRecording'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_RecordingDevice_isRecording'", nullptr);
            return 0;
        }
        bool ret = cobj->isRecording();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "audio.RecordingDevice:isRecording",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_RecordingDevice_isRecording'.",&tolua_err);
#endif

    return 0;
}
static int lua_x_Audio_RecordingDevice_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RecordingDevice)");
    return 0;
}

int lua_register_x_Audio_RecordingDevice(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"audio.RecordingDevice");
    tolua_cclass(tolua_S,"RecordingDevice","audio.RecordingDevice","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"RecordingDevice");
        tolua_function(tolua_S,"getSampleRate",lua_x_Audio_RecordingDevice_getSampleRate);
        tolua_function(tolua_S,"getName",lua_x_Audio_RecordingDevice_getName);
        tolua_function(tolua_S,"getBitDepth",lua_x_Audio_RecordingDevice_getBitDepth);
        tolua_function(tolua_S,"stop",lua_x_Audio_RecordingDevice_stop);
        tolua_function(tolua_S,"getChannelCount",lua_x_Audio_RecordingDevice_getChannelCount);
        tolua_function(tolua_S,"getMaxSamples",lua_x_Audio_RecordingDevice_getMaxSamples);
        tolua_function(tolua_S,"start",lua_x_Audio_RecordingDevice_start);
        tolua_function(tolua_S,"getSampleCount",lua_x_Audio_RecordingDevice_getSampleCount);
        tolua_function(tolua_S,"getData",lua_x_Audio_RecordingDevice_getData);
        tolua_function(tolua_S,"isRecording",lua_x_Audio_RecordingDevice_isRecording);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(audio::RecordingDevice).name();
    g_luaType[typeName] = "audio.RecordingDevice";
    g_typeCast["RecordingDevice"] = "audio.RecordingDevice";
    return 1;
}

int lua_x_Audio_Engine_isValid(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_isValid'", nullptr);
            return 0;
        }
        bool ret = audio::Engine::isValid();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:isValid",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_isValid'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getVolume(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getVolume'", nullptr);
            return 0;
        }
        double ret = audio::Engine::getVolume();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getVolume",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getVolume'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getOrientation(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getOrientation'", nullptr);
            return 0;
        }
        std::array<cocos2d::Vec3, 2> ret = audio::Engine::getOrientation();
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getOrientation",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getOrientation'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getActiveEffects(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getActiveEffects'", nullptr);
            return 0;
        }
        std::vector<std::string> ret = audio::Engine::getActiveEffects();
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getActiveEffects",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getActiveEffects'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getMaxEffectCount(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getMaxEffectCount'", nullptr);
            return 0;
        }
        int ret = audio::Engine::getMaxEffectCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getMaxEffectCount",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getMaxEffectCount'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_setVelocity(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Vec3 arg0;
        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "audio.Engine:setVelocity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_setVelocity'", nullptr);
            return 0;
        }
        audio::Engine::setVelocity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:setVelocity",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_setVelocity'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_setEffect(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::map<audio::Effect::Parameter, float> arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Engine:setEffect");
        ok &= audio::lua::luaval_to_native(tolua_S, 3, &arg1, "audio.Engine:setEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_setEffect'", nullptr);
            return 0;
        }
        bool ret = audio::Engine::setEffect(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:setEffect",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_setEffect'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_pause(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 0)
        {
            std::vector<audio::Source *> ret = audio::Engine::pause();
            audio::lua::native_to_luaval(tolua_S, ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            std::vector<audio::Source *> arg0;
            ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Engine:pause");
            if (!ok) { break; }
            audio::Engine::pause(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "audio.Engine:pause",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_pause'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getVelocity(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getVelocity'", nullptr);
            return 0;
        }
        cocos2d::Vec3 ret = audio::Engine::getVelocity();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getVelocity",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getVelocity'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getMaxSourceCount(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getMaxSourceCount'", nullptr);
            return 0;
        }
        int ret = audio::Engine::getMaxSourceCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getMaxSourceCount",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getMaxSourceCount'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_onEnterForeground(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_onEnterForeground'", nullptr);
            return 0;
        }
        audio::Engine::onEnterForeground();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:onEnterForeground",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_onEnterForeground'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getPosition'", nullptr);
            return 0;
        }
        cocos2d::Vec3 ret = audio::Engine::getPosition();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getPosition",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getPosition'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getDopplerScale(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getDopplerScale'", nullptr);
            return 0;
        }
        double ret = audio::Engine::getDopplerScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getDopplerScale",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getDopplerScale'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_setVolume(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Engine:setVolume");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_setVolume'", nullptr);
            return 0;
        }
        audio::Engine::setVolume(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:setVolume",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_setVolume'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_play(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::vector<audio::Source *> arg0;
        ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Engine:play");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_play'", nullptr);
            return 0;
        }
        bool ret = audio::Engine::play(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:play",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_play'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getMaxSourceEffectCount(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getMaxSourceEffectCount'", nullptr);
            return 0;
        }
        int ret = audio::Engine::getMaxSourceEffectCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getMaxSourceEffectCount",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getMaxSourceEffectCount'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getDistanceModel(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getDistanceModel'", nullptr);
            return 0;
        }
        int ret = (int)audio::Engine::getDistanceModel();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getDistanceModel",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getDistanceModel'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_stop(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 0)
        {
            audio::Engine::stop();
            lua_settop(tolua_S, 1);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            std::vector<audio::Source *> arg0;
            ok &= audio::lua::luaval_to_native(tolua_S, 2, &arg0, "audio.Engine:stop");
            if (!ok) { break; }
            audio::Engine::stop(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "audio.Engine:stop",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_stop'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getLastError(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getLastError'", nullptr);
            return 0;
        }
        std::string ret = audio::Engine::getLastError();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getLastError",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getLastError'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_isEffectSupported(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_isEffectSupported'", nullptr);
            return 0;
        }
        bool ret = audio::Engine::isEffectSupported();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:isEffectSupported",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_isEffectSupported'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getActiveSourceCount(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getActiveSourceCount'", nullptr);
            return 0;
        }
        int ret = audio::Engine::getActiveSourceCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getActiveSourceCount",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getActiveSourceCount'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_setDistanceModel(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        audio::Engine::DistanceModel arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "audio.Engine:setDistanceModel");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_setDistanceModel'", nullptr);
            return 0;
        }
        audio::Engine::setDistanceModel(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:setDistanceModel",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_setDistanceModel'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Vec3 arg0;
        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "audio.Engine:setPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_setPosition'", nullptr);
            return 0;
        }
        audio::Engine::setPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:setPosition",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_setPosition'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getFormat(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "audio.Engine:getFormat");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "audio.Engine:getFormat");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getFormat'", nullptr);
            return 0;
        }
        int ret = audio::Engine::getFormat(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getFormat",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getFormat'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getRecordingDevices(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getRecordingDevices'", nullptr);
            return 0;
        }
        std::vector<audio::RecordingDevice *> ret = audio::Engine::getRecordingDevices();
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getRecordingDevices",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getRecordingDevices'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getEffect(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Engine:getEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getEffect'", nullptr);
            return 0;
        }
        std::map<audio::Effect::Parameter, float> ret = audio::Engine::getEffect(arg0);
        audio::lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getEffect",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getEffect'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_setOrientation(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "audio.Engine:setOrientation");
        ok &= luaval_to_vec3(tolua_S, 3, &arg1, "audio.Engine:setOrientation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_setOrientation'", nullptr);
            return 0;
        }
        audio::Engine::setOrientation(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:setOrientation",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_setOrientation'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_getEffectID(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        unsigned int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Engine:getEffectID");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "audio.Engine:getEffectID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_getEffectID'", nullptr);
            return 0;
        }
        bool ret = audio::Engine::getEffectID(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:getEffectID",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_getEffectID'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_onEnterBackground(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_onEnterBackground'", nullptr);
            return 0;
        }
        audio::Engine::onEnterBackground();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:onEnterBackground",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_onEnterBackground'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_setDopplerScale(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "audio.Engine:setDopplerScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_setDopplerScale'", nullptr);
            return 0;
        }
        audio::Engine::setDopplerScale(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:setDopplerScale",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_setDopplerScale'.",&tolua_err);
#endif
    return 0;
}
int lua_x_Audio_Engine_removeEffect(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"audio.Engine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "audio.Engine:removeEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_x_Audio_Engine_removeEffect'", nullptr);
            return 0;
        }
        bool ret = audio::Engine::removeEffect(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "audio.Engine:removeEffect",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_x_Audio_Engine_removeEffect'.",&tolua_err);
#endif
    return 0;
}
static int lua_x_Audio_Engine_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Engine)");
    return 0;
}

int lua_register_x_Audio_Engine(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"audio.Engine");
    tolua_cclass(tolua_S,"Engine","audio.Engine","",nullptr);

    tolua_beginmodule(tolua_S,"Engine");
        tolua_function(tolua_S,"isValid", lua_x_Audio_Engine_isValid);
        tolua_function(tolua_S,"getVolume", lua_x_Audio_Engine_getVolume);
        tolua_function(tolua_S,"getOrientation", lua_x_Audio_Engine_getOrientation);
        tolua_function(tolua_S,"getActiveEffects", lua_x_Audio_Engine_getActiveEffects);
        tolua_function(tolua_S,"getMaxEffectCount", lua_x_Audio_Engine_getMaxEffectCount);
        tolua_function(tolua_S,"setVelocity", lua_x_Audio_Engine_setVelocity);
        tolua_function(tolua_S,"setEffect", lua_x_Audio_Engine_setEffect);
        tolua_function(tolua_S,"pause", lua_x_Audio_Engine_pause);
        tolua_function(tolua_S,"getVelocity", lua_x_Audio_Engine_getVelocity);
        tolua_function(tolua_S,"getMaxSourceCount", lua_x_Audio_Engine_getMaxSourceCount);
        tolua_function(tolua_S,"onEnterForeground", lua_x_Audio_Engine_onEnterForeground);
        tolua_function(tolua_S,"getPosition", lua_x_Audio_Engine_getPosition);
        tolua_function(tolua_S,"getDopplerScale", lua_x_Audio_Engine_getDopplerScale);
        tolua_function(tolua_S,"setVolume", lua_x_Audio_Engine_setVolume);
        tolua_function(tolua_S,"play", lua_x_Audio_Engine_play);
        tolua_function(tolua_S,"getMaxSourceEffectCount", lua_x_Audio_Engine_getMaxSourceEffectCount);
        tolua_function(tolua_S,"getDistanceModel", lua_x_Audio_Engine_getDistanceModel);
        tolua_function(tolua_S,"stop", lua_x_Audio_Engine_stop);
        tolua_function(tolua_S,"getLastError", lua_x_Audio_Engine_getLastError);
        tolua_function(tolua_S,"isEffectSupported", lua_x_Audio_Engine_isEffectSupported);
        tolua_function(tolua_S,"getActiveSourceCount", lua_x_Audio_Engine_getActiveSourceCount);
        tolua_function(tolua_S,"setDistanceModel", lua_x_Audio_Engine_setDistanceModel);
        tolua_function(tolua_S,"setPosition", lua_x_Audio_Engine_setPosition);
        tolua_function(tolua_S,"getFormat", lua_x_Audio_Engine_getFormat);
        tolua_function(tolua_S,"getRecordingDevices", lua_x_Audio_Engine_getRecordingDevices);
        tolua_function(tolua_S,"getEffect", lua_x_Audio_Engine_getEffect);
        tolua_function(tolua_S,"setOrientation", lua_x_Audio_Engine_setOrientation);
        tolua_function(tolua_S,"getEffectID", lua_x_Audio_Engine_getEffectID);
        tolua_function(tolua_S,"onEnterBackground", lua_x_Audio_Engine_onEnterBackground);
        tolua_function(tolua_S,"setDopplerScale", lua_x_Audio_Engine_setDopplerScale);
        tolua_function(tolua_S,"removeEffect", lua_x_Audio_Engine_removeEffect);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(audio::Engine).name();
    g_luaType[typeName] = "audio.Engine";
    g_typeCast["Engine"] = "audio.Engine";
    return 1;
}
TOLUA_API int register_all_cc_audio(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"audio",0);
	tolua_beginmodule(tolua_S,"audio");

	lua_register_x_Audio_Engine(tolua_S);
	lua_register_x_Audio_Stream(tolua_S);
	lua_register_x_Audio_Source(tolua_S);
	lua_register_x_Audio_RecordingDevice(tolua_S);
	lua_register_x_Audio_Decoder(tolua_S);
	lua_register_x_Audio_SoundData(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

