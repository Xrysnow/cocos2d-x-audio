#include "AudioEngineImpl.h"

#include "AudioEngine.h"
#include "AudioDecoderManager.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"
#include AL_HEADER
#include ALC_HEADER
#include "ALSupport.h"

using namespace xAudio;

static ALCdevice *s_ALDevice = nullptr;
static ALCcontext *s_ALContext = nullptr;

AudioEngineImpl::AudioEngineImpl()
	: _lazyInitLoop(true)
	, _currentAudioID(0)
	, _scheduler(nullptr)
{

}

AudioEngineImpl::~AudioEngineImpl()
{
	if (_scheduler != nullptr)
	{
		_scheduler->unschedule(CC_SCHEDULE_SELECTOR(AudioEngineImpl::update), this);
	}

	if (s_ALContext) {
		alDeleteSources(MAX_AUDIOINSTANCES, _alSources);

		_audioCaches.clear();

		alcMakeContextCurrent(nullptr);
		alcDestroyContext(s_ALContext);
		s_ALContext = nullptr;
	}

	if (s_ALDevice) {
		alcCloseDevice(s_ALDevice);
		s_ALDevice = nullptr;
	}

	AudioDecoderManager::destroy();
}

bool AudioEngineImpl::init()
{
	bool ret = false;
	do {
		s_ALDevice = alcOpenDevice(nullptr);

		if (s_ALDevice) {
			//TODO: use ALC Queries to get some info
			alGetError();
			// TODO: attrList?
			s_ALContext = alcCreateContext(s_ALDevice, nullptr);
			alcMakeContextCurrent(s_ALContext);

			alGenSources(MAX_AUDIOINSTANCES, _alSources);
			auto alError = alGetError();
			if (alError != AL_NO_ERROR)
			{
				ALOGE("%s:generating sources failed! error = %x\n", __FUNCTION__, alError);
				break;
			}

			for (int i = 0; i < MAX_AUDIOINSTANCES; ++i) {
				_alSourceUsed[_alSources[i]] = false;
			}

			_scheduler = cocos2d::Director::getInstance()->getScheduler();
			ret = AudioDecoderManager::init();
			ALOGI("OpenAL was initialized successfully!");
		}
	} while (false);
	ALOGI("\n%s", ALSupport::getReadableInfo().c_str());

	return ret;
}

AudioCache* AudioEngineImpl::preload(const std::string& filePath, fcyStream* stream,
	std::function<void(bool)> callback)
{
	return preload(filePath, stream, 0.0, -1.0, callback);
}

AudioCache* AudioEngineImpl::preload(const std::string& filePath, fcyStream* stream,
	double loopA, double loopB, std::function<void(bool)> callback)
{
	AudioCache* audioCache = nullptr;

	auto it = _audioCaches.find(filePath);
	if (it == _audioCaches.end()) {
		// here assumes AudioCache always construct rightly
		audioCache = &_audioCaches[filePath];
		if (stream)
		{
			audioCache->_fileFullPath = filePath;
			audioCache->_stream = stream;
			audioCache->_loopA = loopA;
			audioCache->_loopB = loopB;
		}
		else
			audioCache->_fileFullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(filePath);
		unsigned int cacheId = audioCache->_id;
		auto isCacheDestroyed = audioCache->_isDestroyed;
		AudioEngine::addTask([audioCache, cacheId, isCacheDestroyed]() {
			if (*isCacheDestroyed)
			{
				ALOGV("AudioCache (id=%u) was destroyed, no need to launch readDataTask.", cacheId);
				audioCache->setSkipReadDataTask(true);
				return;
			}
			audioCache->readDataTask(cacheId);
		});
	}
	else {
		audioCache = &it->second;
	}

	if (audioCache && callback)
	{
		audioCache->addLoadCallback(callback);
	}
	return audioCache;
}

int AudioEngineImpl::play2d(const std::string& fileFullPath, SourceParam* param, bool sync)
{
	if (s_ALDevice == nullptr) {
		ALOGE("[AudioEngineImpl::play2d] OpenAL device was not initialized!");
		return AudioEngine::INVALID_AUDIO_ID;
	}

	bool sourceFlag = false;
	ALuint alSource = 0;
	// search for an unused alSource
	for (int i = 0; i < MAX_AUDIOINSTANCES; ++i) {
		alSource = _alSources[i];

		if (!_alSourceUsed[alSource]) {
			sourceFlag = true;
			break;
		}
	}
	if (!sourceFlag) {
		ALOGD("[AudioEngineImpl::play2d] no enough source");
		return AudioEngine::INVALID_AUDIO_ID;
	}
	// the max number of AudioPlayer is MAX_AUDIOINSTANCES
	auto player = new (std::nothrow) AudioPlayer;
	if (player == nullptr) {
		ALOGE("[AudioEngineImpl::play2d] new AudioPlayer failed");
		return AudioEngine::INVALID_AUDIO_ID;
	}
	player->_alSource = alSource;
	player->_param = param ? *param : SourceParam::DEFAULT;
	// audioCache one-to-one matches fileFullPath
	auto audioCache = preload(fileFullPath, nullptr);
	if (audioCache == nullptr) {
		delete player;
		ALOGE("[AudioEngineImpl::play2d] preload cache failed");
		return AudioEngine::INVALID_AUDIO_ID;
	}

	player->setCache(audioCache);
	_threadMutex.lock();
	_audioPlayers[_currentAudioID] = player;
	_threadMutex.unlock();

	_alSourceUsed[alSource] = true;

	if (sync)
	{
		audioCache->blockToReady();
		_play2d(audioCache, _currentAudioID, true);
	}
	else
		audioCache->addPlayCallback(std::bind(&AudioEngineImpl::_play2d,
			this, audioCache, _currentAudioID, false));

	if (_lazyInitLoop) {
		_lazyInitLoop = false;
		_scheduler->schedule(CC_SCHEDULE_SELECTOR(AudioEngineImpl::update), this, 0.05f, false);
	}
	// return value is _currentAudioID
	return _currentAudioID++;
}

void AudioEngineImpl::_play2d(AudioCache *cache, int audioID, bool block)
{
	//Note: It may bn in sub thread or main thread :(
	if (!*cache->_isDestroyed && cache->_state == AudioCache::State::READY)
	{
		_threadMutex.lock();
		auto playerIt = _audioPlayers.find(audioID);
		if (playerIt != _audioPlayers.end() && playerIt->second->play2d()) {
			if(!block)
				_scheduler->performFunctionInCocosThread([audioID]() {
					if (AudioEngine::_audioIDInfoMap.find(audioID) != AudioEngine::_audioIDInfoMap.end()) {
						AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PLAYING;
					}
				});
		}
		_threadMutex.unlock();
	}
	else
	{
		ALOGD("AudioEngineImpl::_play2d, cache was destroyed or not ready!");
		auto iter = _audioPlayers.find(audioID);
		if (iter != _audioPlayers.end())
		{
			iter->second->_removeByAudioEngine = true;
		}
	}
}

void AudioEngineImpl::setVolume(int audioID, float volume)
{
	auto player = _audioPlayers[audioID];
	if (!player) return;
	player->_param.volume = volume;
	player->updateVolume();
}

void AudioEngineImpl::setLoop(int audioID, bool loop)
{
	auto player = _audioPlayers[audioID];
	if (!player) return;

	if (player->_ready) {
		if (player->_streamingSource) {
			player->setLoop(loop);
		}
		else {
			if (loop) {
				alSourcei(player->_alSource, AL_LOOPING, AL_TRUE);
			}
			else {
				alSourcei(player->_alSource, AL_LOOPING, AL_FALSE);
			}

			auto error = alGetError();
			if (error != AL_NO_ERROR) {
				ALOGE("%s: audio id = %d, error = %x", __FUNCTION__, audioID, error);
			}
		}
	}
	else {
		player->_param.loop = loop;
	}
}

bool AudioEngineImpl::pause(int audioID)
{
	auto player = _audioPlayers[audioID];
	if (!player) return false;
	bool ret = true;
	alSourcePause(player->_alSource);

	auto error = alGetError();
	if (error != AL_NO_ERROR) {
		ret = false;
		ALOGE("%s: audio id = %d, error = %x\n", __FUNCTION__, audioID, error);
	}

	return ret;
}

bool AudioEngineImpl::resume(int audioID)
{
	auto player = _audioPlayers[audioID];
	if (!player) return false;
	bool ret = true;
	alSourcePlay(player->_alSource);
	auto error = alGetError();
	if (error != AL_NO_ERROR) {
		ret = false;
		ALOGE("%s: audio id = %d, error = %x\n", __FUNCTION__, audioID, error);
	}
	return ret;
}

void AudioEngineImpl::stop(int audioID)
{
	auto player = _audioPlayers[audioID];
	if (!player) return;
	alSourceStop(player->_alSource); CHECK_AL_ERROR_DEBUG();
	player->destroy();
	//Note: Don't set the flag to false here, it should be set in 'update' function.
	// Otherwise, the state got from alSourceState may be wrong
	//    _alSourceUsed[player->_alSource] = false;

	// Call 'update' method to cleanup immediately since the schedule may be cancelled without any notification.
	update(0.0f);
}

void AudioEngineImpl::stopAll()
{
	for (auto&& player : _audioPlayers)
	{
		alSourceStop(player.second->_alSource); CHECK_AL_ERROR_DEBUG();
		player.second->destroy();
	}
	//Note: Don't set the flag to false here, it should be set in 'update' function.
	// Otherwise, the state got from alSourceState may be wrong
	//    for(int index = 0; index < MAX_AUDIOINSTANCES; ++index)
	//    {
	//        _alSourceUsed[_alSources[index]] = false;
	//    }

	// Call 'update' method to cleanup immediately since the schedule may be cancelled without any notification.
	update(0.0f);
}

float AudioEngineImpl::getDuration(int audioID)
{
	auto player = _audioPlayers[audioID];
	if (player && player->_ready) {
		return player->_audioCache->_duration;
	}
	else {
		return AudioEngine::TIME_UNKNOWN;
	}
}

float AudioEngineImpl::getCurrentTime(int audioID)
{
	float ret = 0.0f;
	auto player = _audioPlayers[audioID];
	if (player && player->_ready) {
		if (player->_streamingSource) {
			ret = player->getTime();
		}
		else {
			// this value is not right when use AB loop
			alGetSourcef(player->_alSource, AL_SEC_OFFSET, &ret);

			auto error = alGetError();
			if (error != AL_NO_ERROR) {
				ALOGE("%s, audio id:%d,error code:%x", __FUNCTION__, audioID, error);
			}
		}
	}

	return ret;
}

bool AudioEngineImpl::setCurrentTime(int audioID, float time)
{
	bool ret = false;
	auto player = _audioPlayers[audioID];

	do {
		if (!player || !player->_ready)
			break;

		if (player->_streamingSource) {
			ret = player->setTime(time);
			break;
		} else {
			if (player->_audioCache->_framesRead != player->_audioCache->_sourceInfo.totalFrames &&
				(time * player->_audioCache->_sourceInfo.sampleRate) > player->_audioCache->_framesRead) {
				ALOGE("%s: audio id = %d", __FUNCTION__, audioID);
				break;
			}

			alSourcef(player->_alSource, AL_SEC_OFFSET, time);

			auto error = alGetError();
			if (error != AL_NO_ERROR) {
				ALOGE("%s: audio id = %d, error = %x", __FUNCTION__, audioID, error);
			}
			ret = true;
		}
	} while (false);

	return ret;
}

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void(int, const std::string &)> &callback)
{
	auto player = _audioPlayers[audioID];
	if(player)
		player->_finishCallbak = callback;
}

bool AudioEngineImpl::setSourceParam(int audioID, const SourceParam& param)
{
	auto player = _audioPlayers[audioID];
	if (!player)
		return false;
	player->_param = param;
	player->updateParam();
	return true;
}

const SourceParam* AudioEngineImpl::getSourceParam(int audioID)
{
	auto player = _audioPlayers[audioID];
	return player ? &player->_param : nullptr;
}

bool AudioEngineImpl::setListenerParam(const ListenerParam& param)
{
	bool ret = true;
	if (_lparam.position != param.position)
	{
		float pos[3] = { param.position.x,param.position.y,param.position.z };
		alListenerfv(AL_POSITION, pos);
		if (alGetError() != AL_NO_ERROR) { ret = false; }
	}
	if (_lparam.velocity != param.velocity)
	{
		float vel[3] = { param.velocity.x,param.velocity.y,param.velocity.z };
		alListenerfv(AL_VELOCITY, vel);
		if (alGetError() != AL_NO_ERROR) { ret = false; }
	}
	if (_lparam.ori_at != param.ori_at || _lparam.ori_up != param.ori_up)
	{
		float ori[6] = { param.ori_at.x,param.ori_at.y,param.ori_at.z,
			param.ori_up.x,param.ori_up.y,param.ori_up.z };
		alListenerfv(AL_ORIENTATION, ori);
		if (alGetError() != AL_NO_ERROR) { ret = false; }
	}
	_lparam = param;
	return ret;
}

const ListenerParam* AudioEngineImpl::getListenerParam() const
{
	return &_lparam;
}

void AudioEngineImpl::uncache(const std::string &filePath)
{
	_audioCaches.erase(filePath);
}

void AudioEngineImpl::uncacheAll()
{
	_audioCaches.clear();
}

void AudioEngineImpl::update(float dt)
{
	// check stopped players every 50ms and remove them

	ALint sourceState;
	int audioID;
	AudioPlayer* player;
	ALuint alSource;

	//    ALOGV("AudioPlayer count: %d", (int)_audioPlayers.size());

	for (auto it = _audioPlayers.begin(); it != _audioPlayers.end(); ) {
		audioID = it->first;
		player = it->second;
		alSource = player->_alSource;
		alGetSourcei(alSource, AL_SOURCE_STATE, &sourceState);

		if(player->_skipRemove){
			++it;
		}
		else if (player->_removeByAudioEngine)
		{
			AudioEngine::remove(audioID);
			_threadMutex.lock();
			it = _audioPlayers.erase(it);
			_threadMutex.unlock();
			delete player;
			_alSourceUsed[alSource] = false;
		}
		else if (player->_ready && sourceState == AL_STOPPED) {

			std::string filePath;
			if (player->_finishCallbak) {
				auto& audioInfo = AudioEngine::_audioIDInfoMap[audioID];
				filePath = *audioInfo.filePath;
			}

			AudioEngine::remove(audioID);

			_threadMutex.lock();
			it = _audioPlayers.erase(it);
			_threadMutex.unlock();

			if (player->_finishCallbak) {
				player->_finishCallbak(audioID, filePath); //FIXME: callback will delay 50ms
			}
			delete player;
			_alSourceUsed[alSource] = false;
		}
		else {
			++it;
		}
	}

	if (_audioPlayers.empty()) {
		_lazyInitLoop = true;
		_scheduler->unschedule(CC_SCHEDULE_SELECTOR(AudioEngineImpl::update), this);
	}
}

void AudioEngineImpl::waitSubThread()
{
	_threadMutex.lock();
	_threadMutex.unlock();
}

AudioPlayer* AudioEngineImpl::getPlayer(int audioID)
{
	_threadMutex.lock();
	AudioPlayer* ret = nullptr;
	auto it = _audioPlayers.find(audioID);
	if (it != _audioPlayers.end())
		ret = it->second;
	_threadMutex.unlock();
	return ret;
}
