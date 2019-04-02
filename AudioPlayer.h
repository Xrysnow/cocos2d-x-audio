#pragma once

#include "platform/CCPlatformConfig.h"

#include "AudioEngine.h"
#include "AudioDecoder.h"
#include <string>
#include <condition_variable>
#include <mutex>
#include <thread>
#include AL_HEADER

namespace xAudio{

class AudioCache;
class AudioEngineImpl;

class AudioPlayer
{
public:
    AudioPlayer();
    ~AudioPlayer();

    void destroy();

    //queue buffer related stuff

	// Not accurate, precision is QUEUEBUFFER_TIME_STEP.
	// No effect if not use queue buffers.
    bool setTime(float time);
	// Not accurate, precision is QUEUEBUFFER_TIME_STEP.
	// No effect if not use queue buffers.
    float getTime() { return _currTime;}
    bool setLoop(bool loop);

	SourceInfo* getSourceInfo();
	bool isStreamingSource() const { return _streamingSource; }

//protected:
    void setCache(AudioCache* cache);
	AudioCache* getCache() { return _audioCache; }
    void rotateBufferThread(int offsetFrame);
	// Will be called only once since AudioEngine::play2d always creates a new AudioPlayer
    bool play2d();
	void updateParam(bool force = false);
	void updateVolume(bool force = false);
	void updatePitch(bool force = false);
	void updatePosition(bool force = false);
	void updateVelocity(bool force = false);

	void getBuffer(char** buf, uint32_t* size, uint32_t* frames);
	uint32_t copyBuffer(char* dst, uint32_t size);
	uint32_t copyBuffer(char* dst, uint32_t size, uint32_t offset);
protected:
    AudioCache* _audioCache;
	SourceParam _param;

    std::function<void (int, const std::string &)> _finishCallbak;

    ALuint _alSource;
    bool _ready;
    bool _isDestroyed;
    bool _removeByAudioEngine;
	bool _skipRemove;

    //play by circular buffer

    float _currTime;
    bool _streamingSource;
    ALuint _bufferIds[3];
    std::thread* _rotateBufferThread;
    std::condition_variable _sleepCondition;
    std::mutex _sleepMutex;
    bool _timeDirty;
    bool _isRotateThreadExited;

    std::mutex _play2dMutex;

    unsigned int _id;
	char* tmpBuffer = nullptr;
	size_t tmpBufferSize = 0;
	std::mutex tmpBufferMutex;
	AudioDecoder* decoder = nullptr;
private:
	SourceParam lastParam;

    friend class AudioEngineImpl;
};

}

