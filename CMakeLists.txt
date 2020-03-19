set(LIB_NAME cc_audio)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${COCOS2DX_ROOT_PATH}/cocos
    ${COCOS2DX_ROOT_PATH}/cocos/base
    ${COCOS2DX_ROOT_PATH}/cocos/platform
    ${COCOS2DX_ROOT_PATH}/external
    ${COCOS2DX_ROOT_PATH}/external/glfw3/include/win32
)

if(WINDOWS)
    include_directories(${COCOS2DX_ROOT_PATH}/external/win32-specific/gles/include/OGLES)
endif()

set(HEADER
    ALSupport.h
    AudioCommon.h
    AudioDecoder.h
    AudioDecoderFlac.h
    AudioDecoderMp3.h
    AudioDecoderVorbis.h
    AudioDecoderWav.h
    AudioEffect.h
    AudioEngine.h
    AudioFilter.h
    AudioPool.h
    AudioRecordingDevice.h
    AudioSoundData.h
    AudioSource.h
    AudioStream.h
    dr_flac.h
    dr_mp3.h
    NqrCommon.h
    NqrDither.h
    NqrRiffUtils.h
)

set(SOURCE
    ALSupport.cpp
    AudioCommon.cpp
    AudioDecoder.cpp
    AudioDecoderFlac.cpp
    AudioDecoderMp3.cpp
    AudioDecoderVorbis.cpp
    AudioDecoderWav.cpp
    AudioEffect.cpp
    AudioEngine.cpp
    AudioFilter.cpp
    AudioPool.cpp
    AudioRecordingDevice.cpp
    AudioSoundData.cpp
    AudioSource.cpp
    NqrCommon.cpp
    NqrRiffUtils.cpp
)

if(BUILD_LUA_LIBS)
    include_directories(
        ${COCOS2DX_ROOT_PATH}/external/lua/luajit/include
        ${COCOS2DX_ROOT_PATH}/external/lua/tolua
    )
    list(APPEND HEADER
        lua_audio_auto.hpp
    )
    list(APPEND SOURCE
        lua_audio_auto.cpp
    )
endif()

add_library(${LIB_NAME} STATIC ${SOURCE} ${HEADER})
add_dependencies(${LIB_NAME} cocos2d)
use_cocos2dx_compile_define(${LIB_NAME})
use_cocos2dx_compile_options(${LIB_NAME})

if(CC_AUDIO_DEPEND_LIBS)
    target_link_libraries(${LIB_NAME} ${CC_AUDIO_DEPEND_LIBS})
endif()

if(BUILD_LUA_LIBS)
    target_compile_definitions(${LIB_NAME} PUBLIC _USRLUASTATIC)
endif()

set_target_properties(${LIB_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}
)

if(XCODE OR VS)
    cocos_mark_code_files(${LIB_NAME})
endif()
