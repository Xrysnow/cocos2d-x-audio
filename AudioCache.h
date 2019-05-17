#pragma once

#include "platform/CCPlatformConfig.h"

#include "AudioMacros.h"
#include "AudioParam.h"
#include AL_HEADER
#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include "AudioStream.h"

namespace xAudio{

class AudioEngineImpl;
class AudioPlayer;

class AudioCache
{
public:

	enum class State
	{
		INITIAL,
		LOADING,
		READY,
		FAILED
	};

	AudioCache();
	~AudioCache();
	// Called when READY or FAILED.
	// Will be called in sub thread.
	void addPlayCallback(const std::function<void()>& callback);
	// Called when READY or FAILED, param means READY.
	// Will be called in cocos thread.
	void addLoadCallback(const std::function<void(bool)>& callback);

	ALenum getFormat() const;
	uint32_t getSampleRate() const;
	double getDuration() const;
	uint32_t getTotalFrames() const;
	uint32_t getBytesPerFrame() const;
	uint32_t getChannelCount() const;

	SourceInfo* getSourceInfo();

	bool blockToReady();
	AudioStream* getStream() const { return _stream; }
	bool isLoopAB() const { return _isLoopAB; }
	void getLoopAB(double& loopA, double& loopB) const{ loopA = _loopA; loopB = _loopB; }
	bool isQueueBuffer() const { return _queBufferFrames != 0; }
protected:
	void setSkipReadDataTask(bool isSkip) { _isSkipReadDataTask = isSkip; }
	void readDataTask(unsigned int selfId);

	void invokingPlayCallbacks();

	void invokingLoadCallbacks();

	//pcm data related stuff

	ALenum _format;         //format of _pcmData, AL_FORMAT_MONO16 or AL_FORMAT_STEREO16
	double _duration;
	SourceInfo _sourceInfo;

	uint32_t _framesRead;

    /*Cache related stuff;
     * Cache pcm data when sizeInBytes less than PCMDATA_CACHEMAXSIZE
     */
    ALuint _alBufferId;
    char* _pcmData;
	size_t _pcmDataSize = 0;

    /*Queue buffer related stuff
     *  Streaming in OpenAL when sizeInBytes greater then PCMDATA_CACHEMAXSIZE
     */
    char* _queBuffers[QUEUEBUFFER_NUM];
    ALsizei _queBufferSize[QUEUEBUFFER_NUM];
    // Number of frames of each queBuffer, it indicates if buffer is used.
	uint32_t _queBufferFrames;

    std::mutex _playCallbackMutex;
    std::vector< std::function<void()> > _playCallbacks;

    // loadCallbacks doesn't need mutex since it's invoked only in Cocos thread.
    std::vector< std::function<void(bool)> > _loadCallbacks;

    std::mutex _readDataTaskMutex;

    State _state;

    std::shared_ptr<bool> _isDestroyed;
    unsigned int _id;
    bool _isLoadingFinished;
    bool _isSkipReadDataTask;

	// set external:

    std::string _fileFullPath;
	AudioStream* _stream;
	double _loopA;
	double _loopB;
	// Force decode all data in 'readDataTask', this will disable AB loop.
	// Used for SE larger than 1MB.
	bool _forceLoad;

	bool _isLoopAB = false;

    friend class AudioEngineImpl;
    friend class AudioPlayer;
    friend class AudioDecoder;
};

}
