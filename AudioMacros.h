#pragma once

#include "../LSTG/LogSystem.h"
lstg::LogSystem& AudioLogger();

#define ALOGGER AudioLogger()
#define AERROR(info, ...) ALOGGER.Log(lstg::LogType::Error, info, ##__VA_ARGS__)
#define AWARNING(info, ...) ALOGGER.Log(lstg::LogType::Warning, info, ##__VA_ARGS__)
#define AINFO(info, ...) ALOGGER.Log(lstg::LogType::Information, info, ##__VA_ARGS__)

#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)

//#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
//#define ALOGV(fmt, ...) audioLog("V/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "", ##__VA_ARGS__)
#define ALOGV AINFO
//#else
//#define ALOGV(fmt, ...) do {} while(false)
//#endif
//#define ALOGD(fmt, ...) audioLog("D/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "", ##__VA_ARGS__)
//#define ALOGI(fmt, ...) audioLog("I/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "", ##__VA_ARGS__)
//#define ALOGW(fmt, ...) audioLog("W/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "", ##__VA_ARGS__)
//#define ALOGE(fmt, ...) audioLog("E/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "", ##__VA_ARGS__)

#define ALOGD ALOGV
#define ALOGI ALOGV
#define ALOGW ALOGV
#define ALOGE ALOGV

#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
#define CHECK_AL_ERROR_DEBUG() \
do { \
    ALenum __error = alGetError(); \
    if (__error) { \
        ALOGE("OpenAL error %d in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
    } \
} while (false)
        //ALOGE("OpenAL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__);
#else
#define CHECK_AL_ERROR_DEBUG()
#endif

#define BREAK_IF(condition) \
    if (!!(condition)) { \
        break; \
    }

#define BREAK_IF_ERR_LOG(condition, fmt, ...) \
    if (!!(condition)) { \
        ALOGE("(" QUOTEME(condition) ") failed, message: " fmt, ##__VA_ARGS__); \
        break; \
    }
