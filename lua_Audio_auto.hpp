#pragma once
#include "base/ccConfig.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_all_x_Audio(lua_State* tolua_S);

