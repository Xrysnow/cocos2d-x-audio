#include "platform/CCPlatformConfig.h"

#include "AudioPlayer.h"
#include "AudioCache.h"
#include "platform/CCFileUtils.h"
#include "AudioDecoderManager.h"
#include "AudioDecoder.h"
#include "../fcyLib/fcyMisc/fcyStopWatch.h"

#define LOG_TAG "AudioPlayer"
//#define VERY_VERY_VERBOSE_LOGGING
#ifdef VERY_VERY_VERBOSE_LOGGING
#define ALOGVV ALOGV
#else
#define ALOGVV(...) do{} while(false)
#endif

using namespace xAudio;
static fcyStopWatch AudioPlayerWatch;

namespace {
unsigned int __idIndex = 0;
}

AudioPlayer::AudioPlayer():
_audioCache(nullptr),
_finishCallbak(nullptr),
_alSource(0),
_ready(false),
_isDestroyed(false),
_removeByAudioEngine(false),
_skipRemove(false),
_currTime(0.0f),
_streamingSource(false),
_rotateBufferThread(nullptr),
_timeDirty(false),
_isRotateThreadExited(false),
_id(++__idIndex)
{
	memset(_bufferIds, 0, sizeof(_bufferIds));
}

AudioPlayer::~AudioPlayer()
{
    ALOGVV("~AudioPlayer() (%p), id=%u", this, _id);
    destroy();

    if (_streamingSource)
    {
        alDeleteBuffers(3, _bufferIds);
    }
	if (decoder)
	{
		decoder->close();
		AudioDecoderManager::destroyDecoder(decoder);
	}
	if(tmpBuffer)
		free(tmpBuffer);
}

void AudioPlayer::destroy()
{
    if (_isDestroyed)
        return;

    ALOGVV("AudioPlayer::destroy begin, id=%u", _id);

    _isDestroyed = true;

    do
    {
        if (_audioCache != nullptr)
        {
            if (_audioCache->_state == AudioCache::State::INITIAL)
            {
                ALOGV("AudioPlayer::destroy, id=%u, cache isn't ready!", _id);
                break;
            }

            while (!_audioCache->_isLoadingFinished)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        // Wait for play2d to be finished.
        _play2dMutex.lock();
        _play2dMutex.unlock();

        if (_streamingSource)
        {
            if (_rotateBufferThread != nullptr)
            {
                while (!_isRotateThreadExited)
                {
                    _sleepCondition.notify_one();
                    //std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }

                if (_rotateBufferThread->joinable()) {
                    _rotateBufferThread->join();
                }

                delete _rotateBufferThread;
                _rotateBufferThread = nullptr;
                ALOGV("rotateBufferThread exited!");
            }
        }
    } while(false);

    alSourceStop(_alSource); CHECK_AL_ERROR_DEBUG();
    alSourcei(_alSource, AL_BUFFER, 0); CHECK_AL_ERROR_DEBUG();

    _removeByAudioEngine = true;

    _ready = false;
    ALOGVV("AudioPlayer::destroy end, id=%u", _id);
}

void AudioPlayer::setCache(AudioCache* cache)
{
    _audioCache = cache;
}

bool AudioPlayer::play2d()
{
    _play2dMutex.lock();
    ALOGVV("[AudioPlayer::play2d] _alSource: %u, player id=%u", _alSource, _id);
	//ALOGV("[AudioPlayer::play2d] start at %fms", AudioPlayerWatch.GetElapsed() * 1000);

    /*********************************************************************/
    /*       Note that it may be in sub thread or in main thread.       **/
    /*********************************************************************/
    bool ret = false;
    do
    {
        if (!_audioCache || _audioCache->_state != AudioCache::State::READY)
        {
            ALOGE("alBuffer isn't ready for play!");
            break;
        }

        alSourcei(_alSource, AL_BUFFER, 0);CHECK_AL_ERROR_DEBUG();
        alSourcef(_alSource, AL_PITCH, _param.pitch);CHECK_AL_ERROR_DEBUG();
        alSourcef(_alSource, AL_GAIN, _param.volume);CHECK_AL_ERROR_DEBUG();
        alSourcei(_alSource, AL_LOOPING, AL_FALSE);CHECK_AL_ERROR_DEBUG();
		updateParam(true);
		uint32_t offset = 0;

        if (_audioCache->_queBufferFrames == 0)
        {
            if (_param.loop) {
                alSourcei(_alSource, AL_LOOPING, AL_TRUE);
                CHECK_AL_ERROR_DEBUG();
            }
        }
        else
        {
			if(!decoder)
				decoder = AudioDecoderManager::createDecoder(_audioCache->_fileFullPath.c_str());
			if (!decoder)
				break;
	        if (!decoder->isOpened())
	        {
				if (_audioCache->_stream ?
					!decoder->open(_audioCache->_stream, _audioCache->_loopA, _audioCache->_loopB) :
					!decoder->open(_audioCache->_fileFullPath.c_str()))
					break;
	        }
			const uint32_t framesToRead = _audioCache->_queBufferFrames;
			const uint32_t bufferSize = framesToRead * decoder->getBytesPerFrame();
			if(!tmpBuffer)
			{
				tmpBuffer = (char*)malloc(bufferSize);
	        }
	        if (!tmpBuffer)
				break;
			memset(tmpBuffer, 0, bufferSize);

            alGenBuffers(3, _bufferIds);

            auto alError = alGetError();
            if (alError == AL_NO_ERROR)
            {
				if(_currTime > 0.0f)
				{
					_currTime = std::min(_currTime, (float)_audioCache->_duration);
					auto curOffset = _currTime*decoder->getSampleRate();
					ALOGV("[AudioPlayer::play2d] currTime=%f, offset=%d.", _currTime, curOffset);
					if (!decoder->seek(curOffset))break;
					// reload
					for (int index = 0; index < QUEUEBUFFER_NUM; ++index)
					{
						decoder->readFixedFrames(_audioCache->_queBufferFrames, _audioCache->_queBuffers[index]);
					}
					offset = curOffset + _audioCache->_queBufferFrames * QUEUEBUFFER_NUM + 1;
				} else {
					offset = _audioCache->_queBufferFrames * QUEUEBUFFER_NUM + 1;
				}
				// fill
				for (int index = 0; index < QUEUEBUFFER_NUM; ++index)
				{
					alBufferData(_bufferIds[index], _audioCache->_format, _audioCache->_queBuffers[index],
						_audioCache->_queBufferSize[index], _audioCache->_sourceInfo.sampleRate);
				}
                CHECK_AL_ERROR_DEBUG();
            }
            else
            {
                ALOGE("%s:alGenBuffers error code:%d", __FUNCTION__,alError);
                break;
            }
            _streamingSource = true;
        }

        {
            std::unique_lock<std::mutex> lk(_sleepMutex);
            if (_isDestroyed)
                break;

            if (_streamingSource)
            {
                alSourceQueueBuffers(_alSource, QUEUEBUFFER_NUM, _bufferIds);
                CHECK_AL_ERROR_DEBUG();
                _rotateBufferThread = new std::thread(&AudioPlayer::rotateBufferThread, this, offset);
            }
            else
            {
                alSourcei(_alSource, AL_BUFFER, _audioCache->_alBufferId);
                CHECK_AL_ERROR_DEBUG();
            }

            alSourcePlay(_alSource);
        }

        auto alError = alGetError();
        if (alError != AL_NO_ERROR)
        {
            ALOGE("%s:alSourcePlay error code:%d", __FUNCTION__,alError);
            break;
        }

        ALint state;
        alGetSourcei(_alSource, AL_SOURCE_STATE, &state);
		alError = alGetError();
		if (alError)
		{
			ALOGE("[AudioPlayer::play2d] OpenAL error %d\n", alError);
			break;
		}
        if (state != AL_PLAYING)
        {
            ALOGE("state isn't playing, %d, %s, cache id=%u, player id=%u",
				state, _audioCache->_fileFullPath.c_str(), _audioCache->_id, _id);
			break;
		}
		// note: if device is disconnected, assert will fail
        //assert(state == AL_PLAYING);
        _ready = true;
        ret = true;
    } while (false);

	_removeByAudioEngine = !ret;

	_play2dMutex.unlock();
    return ret;
}

void AudioPlayer::rotateBufferThread(int offsetFrame)
{
    do
    {
		if (!decoder || !decoder->isOpened())
		{
			ALOGE("[AudioPlayer::rotateBufferThread] decoder not set!");
			break;
	    }
	    uint32_t framesRead = 0;
        const uint32_t framesToRead = _audioCache->_queBufferFrames;
        const uint32_t bufferSize = framesToRead * decoder->getBytesPerFrame();
	    if (!tmpBuffer)
	    {
			ALOGE("[AudioPlayer::rotateBufferThread] no tmpBuffer!");
		    break;
	    }
	    memset(tmpBuffer, 0, bufferSize);
		tmpBufferSize = bufferSize;

        if (offsetFrame != 0) {
            decoder->seek(offsetFrame);
        }

        ALint sourceState;
        ALint bufferProcessed = 0;
        bool needToExitThread = false;

		ALOGV("[AudioPlayer::rotateBufferThread] started. offset=%d, que length=%u, buffer size=%u",
			offsetFrame, framesToRead, bufferSize);
		ALOGV("[AudioPlayer::rotateBufferThread] started at %fms", AudioPlayerWatch.GetElapsed() * 1000);
		fcyStopWatch sw;

        while (!_isDestroyed) {
            alGetSourcei(_alSource, AL_SOURCE_STATE, &sourceState);
	        auto __error = alGetError();
			if (__error)
			{
				ALOGE("[AudioPlayer::rotateBufferThread] OpenAL error %d, exit.\n", __error);
				needToExitThread = true;
			}
            if (sourceState == AL_PLAYING) {
                alGetSourcei(_alSource, AL_BUFFERS_PROCESSED, &bufferProcessed);
				CHECK_AL_ERROR_DEBUG();
				auto processed = bufferProcessed; sw.Reset();
                while (bufferProcessed > 0) {
                    bufferProcessed--;
      //              if (_timeDirty) {
      //                  _timeDirty = false;
      //                  offsetFrame = _currTime * decoder->getSampleRate();
						//ALOGV("[AudioPlayer::rotateBufferThread] Set time to %f.", _currTime);
	     //               if (!decoder->seek(offsetFrame))
		    //                decoder->seek(0);
      //              }
      //              else
					{
                        _currTime += QUEUEBUFFER_TIME_STEP;
                        if (_currTime > _audioCache->_duration) {
							if (_param.loop) {
                                _currTime = 0.0f;
                            } else {
                                _currTime = _audioCache->_duration;
                            }
                        }
                    }

					tmpBufferMutex.lock();
					framesRead = decoder->readFixedFrames(framesToRead, tmpBuffer);
					tmpBufferMutex.unlock();
					ALOGVV("[AudioPlayer::rotateBufferThread] read %u B", framesRead);
					CC_ASSERT(decoder->isABLoop() ? (framesRead == framesToRead) : true);

                    if (framesRead == 0) {
                        if (_param.loop) {
                            decoder->seek(0);
							tmpBufferMutex.lock();
                            framesRead = decoder->readFixedFrames(framesToRead, tmpBuffer);
							tmpBufferMutex.unlock();
						} else {
                            needToExitThread = true;
                            break;
                        }
                    }

					tmpBufferMutex.lock();
					// fill buffer is very fast
                    ALuint bid;
                    alSourceUnqueueBuffers(_alSource, 1, &bid);
					alBufferData(bid, _audioCache->_format, tmpBuffer,
						framesRead * decoder->getBytesPerFrame(), decoder->getSampleRate());
					alSourceQueueBuffers(_alSource, 1, &bid);
					tmpBufferMutex.unlock();
                }
				if (processed != 0){
					ALOGVV("[AudioPlayer::rotateBufferThread] %d buffers processed in %fms.",
						processed, sw.GetElapsed() * 1000); sw.Reset();
				}
            }

            std::unique_lock<std::mutex> lk(_sleepMutex);
            if (_isDestroyed || needToExitThread) {
                break;
            }
			// unlock 'lk', block until destroyed or 75ms is reached
            _sleepCondition.wait_for(lk,std::chrono::milliseconds(75));
		}

    } while(false);

    //ALOGV("_isDestroyed=%b", _isDestroyed);
    //ALOGV("Exit rotate buffer thread ...");

    _isRotateThreadExited = true;
	ALOGV("[AudioPlayer::rotateBufferThread] exite at %fms", AudioPlayerWatch.GetElapsed() * 1000);
    ALOGV("[AudioPlayer::rotateBufferThread] exited.\n");
}

bool AudioPlayer::setLoop(bool loop)
{
    if (!_isDestroyed ) {
		_param.loop = loop;
        return true;
    }

    return false;
}

bool AudioPlayer::setTime(float time)
{
	// not accurate, need an improvement
    if (!_isDestroyed && time >= 0.0f && time < _audioCache->_duration) {

		//ALOGV("[AudioPlayer::setTime] start at %fms", AudioPlayerWatch.GetElapsed() * 1000);
		_currTime = time;
        _timeDirty = true;
		fcyStopWatch sw;
		//TODO: check this
	    if (_ready)
	    {
			ALenum __error;

			_skipRemove = true;
			alSourceStop(_alSource);
			_sleepCondition.notify_one();
			destroy();
			ALint bufferInQueue = 0;
			alGetSourcei(_alSource, AL_BUFFERS_QUEUED, &bufferInQueue);
			//ALOGV("[AudioPlayer::setTime] buffer in queue: %d", bufferInQueue);
			for (int i = 0; i < bufferInQueue; ++i)
			{
				ALuint bid;
				alSourceUnqueueBuffers(_alSource, 1, &bid);				
			}

			alDeleteBuffers(3, _bufferIds);
			//memset(_bufferIds, 0, sizeof(_bufferIds));
			_removeByAudioEngine = false;
		    _isDestroyed = false;
			play2d();

			//alGetSourcei(_alSource, AL_BUFFERS_QUEUED, &bufferInQueue);
			//ALOGV("[AudioPlayer::setTime] buffer in queue: %d", bufferInQueue);

			__error = alGetError();
			if (__error) {
				ALOGE("[AudioPlayer::setTime] last error %d", __error);
			}

			_skipRemove = false;
	    }
		ALOGV("[AudioPlayer::setTime] cost %fms", sw.GetElapsed() * 1000);

        return true;
    }
    return false;
}

SourceInfo* AudioPlayer::getSourceInfo()
{
	return _audioCache ? _audioCache->getSourceInfo() : nullptr;
}

void AudioPlayer::updateParam(bool force)
{
	updateVolume(force);
	updatePitch(force);
	updatePosition(force);
	updateVelocity(force);
	lastParam = _param;
}

void AudioPlayer::updateVolume(bool force)
{
	if (!_ready && !force) return;
	if (_param.volume != lastParam.volume) {
		alSourcef(_alSource, AL_GAIN, _param.volume); CHECK_AL_ERROR_DEBUG();
		lastParam.volume = _param.volume;
	}
}

void AudioPlayer::updatePitch(bool force)
{
	if (!_ready && !force) return;
	if (_param.pitch != lastParam.pitch) {
		alSourcef(_alSource, AL_PITCH, _param.pitch); CHECK_AL_ERROR_DEBUG();
		lastParam.pitch = _param.pitch;
	}
}

void AudioPlayer::updatePosition(bool force)
{
	if (!_ready && !force) return;
	if (_param.position != lastParam.position)
	{
		float pos[3] = { _param.position.x,_param.position.y,_param.position.z };
		alSourcefv(_alSource, AL_POSITION, pos); CHECK_AL_ERROR_DEBUG();
		lastParam.position = _param.position;
	}
}

void AudioPlayer::updateVelocity(bool force)
{
	if (!_ready && !force) return;
	if (_param.velocity != lastParam.velocity)
	{
		float vel[3] = { _param.velocity.x,_param.velocity.y,_param.velocity.z };
		alSourcefv(_alSource, AL_VELOCITY, vel); CHECK_AL_ERROR_DEBUG();
		lastParam.velocity = _param.velocity;
	}
}

void AudioPlayer::getBuffer(char** buf, uint32_t* size, uint32_t* frames)
{
	if (_audioCache&&tmpBuffer)
	{
		*buf = tmpBuffer;
		*size = _audioCache->_queBufferFrames*decoder->getBytesPerFrame();
		*frames = _audioCache->_queBufferFrames;
	}
	else if (_audioCache&&_audioCache->_pcmData)
	{
		*buf = _audioCache->_pcmData;
		*size = _audioCache->_sourceInfo.totalFrames*decoder->getBytesPerFrame();
		*frames = _audioCache->_sourceInfo.totalFrames;
	}
	else
	{
		*buf = nullptr;
		*size = 0;
		*frames = 0;
	}
}

uint32_t AudioPlayer::copyBuffer(char* dst, uint32_t size)
{
	return copyBuffer(dst, size, 0);
}

uint32_t AudioPlayer::copyBuffer(char* dst, uint32_t size, uint32_t offset)
{
	if (_audioCache)
	{
		std::lock_guard<std::mutex> lg(tmpBufferMutex);
		if (tmpBuffer)
		{
			// note: important, avoid tmpBufferSize - offset underflow
			offset = std::min(offset, tmpBufferSize);
			size = std::min(size, tmpBufferSize - offset);
			if (size <= 0)return 0;
			memcpy(dst, tmpBuffer + offset, size);
			return size;
		}
	}
	if (_audioCache&&_audioCache->_pcmData)
	{
		offset = std::min(offset, _audioCache->_pcmDataSize);
		size = std::min(size, _audioCache->_pcmDataSize - offset);
		if (size <= 0)return 0;
		memcpy(dst, _audioCache->_pcmData + offset, size);
		return size;
	}
	return 0;
}

