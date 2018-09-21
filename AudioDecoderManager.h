#pragma once

namespace xAudio {

class AudioDecoder;

class AudioDecoderManager
{
public:
    static bool init();
    static void destroy();
    static AudioDecoder* createDecoder(const char* path);
    static void destroyDecoder(AudioDecoder* decoder);
};

}
