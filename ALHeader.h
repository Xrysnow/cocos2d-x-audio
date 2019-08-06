#pragma once
#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)||(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenAL/alext.h>
#else
#include "../../external/OpenalSoft/include/AL/al.h"
#include "../../external/OpenalSoft/include/AL/alc.h"
#include "../../external/OpenalSoft/include/AL/alext.h"
//#include "../../external/OpenalSoft/include/AL/efx.h"
//#include "../../external/OpenalSoft/include/AL/efx-presets.h"
#endif
