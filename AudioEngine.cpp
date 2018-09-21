#include "AudioEngine.h"
#include "AudioEngineImpl.h"
#include <queue>
#include "platform/CCFileUtils.h"
#include "base/ccUtils.h"

#define TIME_DELAY_PRECISION 0.0001
#ifdef ERROR
#undef ERROR
#endif // ERROR

using namespace xAudio;
using namespace cocos2d;
using namespace std;

const int AudioEngine::INVALID_AUDIO_ID = -1;
const float AudioEngine::TIME_UNKNOWN = -1.0f;
vector<int> AudioEngine::tempPaused;

//audio file path,audio IDs
unordered_map<string, list<int>> AudioEngine::_audioPathIDMap;
//profileName,ProfileHelper
unordered_map<string, AudioEngine::ProfileHelper> AudioEngine::_audioPathProfileHelperMap;
unsigned int AudioEngine::_maxInstances = MAX_AUDIOINSTANCES;
AudioEngine::ProfileHelper* AudioEngine::_defaultProfileHelper = nullptr;
unordered_map<int, AudioEngine::AudioInfo> AudioEngine::_audioIDInfoMap;
AudioEngineImpl* AudioEngine::_audioEngineImpl = nullptr;

AudioEngine::AudioEngineThreadPool* AudioEngine::s_threadPool = nullptr;
bool AudioEngine::_isEnabled = true;

class AudioEngine::AudioEngineThreadPool
{
public:
	AudioEngineThreadPool(int threads = 4)
		: _stop(false)
	{
		for (int index = 0; index < threads; ++index)
		{
			_workers.emplace_back(thread(std::bind(&AudioEngineThreadPool::threadFunc, this)));
		}
	}

	void addTask(const function<void()> &task) {
		unique_lock<mutex> lk(_queueMutex);
		_taskQueue.emplace(task);
		_taskCondition.notify_one();
	}

	~AudioEngineThreadPool()
	{
		{
			unique_lock<mutex> lk(_queueMutex);
			_stop = true;
			_taskCondition.notify_all();
		}

		for (auto&& worker : _workers) {
			worker.join();
		}
	}

private:
	void threadFunc()
	{
		while (true) {
			function<void()> task = nullptr;
			{
				unique_lock<mutex> lk(_queueMutex);
				if (_stop)
				{
					break;
				}
				if (!_taskQueue.empty())
				{
					task = move(_taskQueue.front());
					_taskQueue.pop();
				}
				else
				{
					_taskCondition.wait(lk);
					continue;
				}
			}

			task();
		}
	}

	vector<thread>  _workers;
	queue< function<void()> > _taskQueue;

	mutex _queueMutex;
	condition_variable _taskCondition;
	bool _stop;
};

void AudioEngine::end()
{
	if (s_threadPool)
	{
		delete s_threadPool;
		s_threadPool = nullptr;
	}

	delete _audioEngineImpl;
	_audioEngineImpl = nullptr;

	delete _defaultProfileHelper;
	_defaultProfileHelper = nullptr;
}

bool AudioEngine::lazyInit()
{
	if (_audioEngineImpl == nullptr)
	{
		_audioEngineImpl = new (nothrow) AudioEngineImpl();
		if (!_audioEngineImpl || !_audioEngineImpl->init()) {
			delete _audioEngineImpl;
			_audioEngineImpl = nullptr;
			return false;
		}
	}

//#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	if (_audioEngineImpl && s_threadPool == nullptr)
	{
		s_threadPool = new (nothrow) AudioEngineThreadPool();
	}
//#endif
	return true;
}

int AudioEngine::play2d(const string& filePath, bool loop, float volume, bool block, const cocos2d::experimental::AudioProfile *profile)
{
	SourceParam param;
	param.loop = loop;
	param.volume = volume;
	return play2d(filePath, &param, block, profile);
}

int AudioEngine::play2d(const string& filePath, SourceParam* param, bool block, const cocos2d::experimental::AudioProfile* profile)
{
	int ret = INVALID_AUDIO_ID;

	do {
		if (!isEnabled())
		{
			ALOGD("[AudioEngine::play2d] not enabled!");
			break;
		}

		if (!lazyInit()) {
			ALOGE("[AudioEngine::play2d] lazyInit failed!");
			break;
		}

		// fail on linux
		/*
		if (!FileUtils::getInstance()->isFileExist(filePath)) {
			ALOGE("[AudioEngine::play2d] can't find file %s", filePath.c_str());
			break;
		}
		*/
		
		auto profileHelper = _defaultProfileHelper;
		if (profile && profile != &profileHelper->profile) {
			CC_ASSERT(!profile->name.empty());
			profileHelper = &_audioPathProfileHelperMap[profile->name];
			profileHelper->profile = *profile;
		}

		if (_audioIDInfoMap.size() >= _maxInstances) {
			log("Fail to play %s cause by limited max instance of AudioEngine", filePath.c_str());
			break;
		}
		if (profileHelper)
		{
			if (profileHelper->profile.maxInstances != 0 &&
				profileHelper->audioIDs.size() >= profileHelper->profile.maxInstances) {
				log("Fail to play %s cause by limited max instance of AudioProfile", filePath.c_str());
				break;
			}
			if (profileHelper->profile.minDelay > TIME_DELAY_PRECISION) {
				auto currTime = utils::gettime();
				if (profileHelper->lastPlayTime > TIME_DELAY_PRECISION &&
					currTime - profileHelper->lastPlayTime <= profileHelper->profile.minDelay) {
					log("Fail to play %s cause by limited minimum delay", filePath.c_str());
					break;
				}
			}
		}

		param->volume = max(0.f, min(param->volume, 1.f));
		param->pitch = max(0.5f, min(param->pitch, 2.f));

		ret = _audioEngineImpl->play2d(filePath, param);
		if (ret != INVALID_AUDIO_ID)
		{
			_audioPathIDMap[filePath].push_back(ret);
			auto it = _audioPathIDMap.find(filePath);

			auto& audioRef = _audioIDInfoMap[ret];
			audioRef.volume = param->volume;
			audioRef.loop = param->loop;
			audioRef.filePath = &it->first;

			if (profileHelper) {
				profileHelper->lastPlayTime = utils::gettime();
				profileHelper->audioIDs.push_back(ret);
			}
			audioRef.profileHelper = profileHelper;

			if (block)
			{
				auto player = _audioEngineImpl->getPlayer(ret);
				if (!player)
					ALOGD("[AudioEngine::play2d] player still not ready!");
				else
					audioRef.state = AudioState::PLAYING;
			}
		}
	} while (false);

	return ret;
}

void AudioEngine::setLoop(int audioID, bool loop)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end() && it->second.loop != loop) {
		_audioEngineImpl->setLoop(audioID, loop);
		it->second.loop = loop;
	}
}

void AudioEngine::setVolume(int audioID, float volume)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end()) {
		if (volume < 0.0f)
			volume = 0.0f;
		else if (volume > 1.0f)
			volume = 1.0f;

		if (it->second.volume != volume) {
			_audioEngineImpl->setVolume(audioID, volume);
			it->second.volume = volume;
		}
	}
}

void AudioEngine::pause(int audioID)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end() && it->second.state == AudioState::PLAYING) {
		_audioEngineImpl->pause(audioID);
		it->second.state = AudioState::PAUSED;
	}
}

void AudioEngine::pauseAll()
{
	auto itEnd = _audioIDInfoMap.end();
	for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it)
	{
		if (it->second.state == AudioState::PLAYING)
		{
			_audioEngineImpl->pause(it->first);
			it->second.state = AudioState::PAUSED;
		}
	}
}

void AudioEngine::pauseTemp()
{
	auto itEnd = _audioIDInfoMap.end();
	for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it)
	{
		if (it->second.state == AudioState::PLAYING)
		{
			_audioEngineImpl->pause(it->first);
			it->second.state = AudioState::PAUSED;
			tempPaused.push_back(it->first);
		}
	}
}

void AudioEngine::resume(int audioID)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end() && it->second.state == AudioState::PAUSED) {
		_audioEngineImpl->resume(audioID);
		it->second.state = AudioState::PLAYING;
	}
}

void AudioEngine::resumeAll()
{
	auto itEnd = _audioIDInfoMap.end();
	for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it)
	{
		if (it->second.state == AudioState::PAUSED)
		{
			_audioEngineImpl->resume(it->first);
			it->second.state = AudioState::PLAYING;
		}
	}
}

void AudioEngine::resumeTemp()
{
	for(auto id : tempPaused)
	{
		resume(id);
	}
	tempPaused.clear();
}

void AudioEngine::stop(int audioID)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end()) {
		_audioEngineImpl->stop(audioID);

		remove(audioID);
	}
}

void AudioEngine::remove(int audioID)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end()) {
		if (it->second.profileHelper) {
			it->second.profileHelper->audioIDs.remove(audioID);
		}
		_audioPathIDMap[*it->second.filePath].remove(audioID);
		_audioIDInfoMap.erase(audioID);
	}
}

void AudioEngine::stopAll()
{
	if (!_audioEngineImpl) {
		return;
	}
	_audioEngineImpl->stopAll();
	auto itEnd = _audioIDInfoMap.end();
	for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it)
	{
		if (it->second.profileHelper) {
			it->second.profileHelper->audioIDs.remove(it->first);
		}
	}
	_audioPathIDMap.clear();
	_audioIDInfoMap.clear();
}

void AudioEngine::uncache(const string &filePath)
{
	auto audioIDsIter = _audioPathIDMap.find(filePath);
	if (audioIDsIter != _audioPathIDMap.end())
	{
		//@Note: For safely iterating elements from the audioID list, we need to copy the list
		// since 'AudioEngine::remove' may be invoked in '_audioEngineImpl->stop' synchronously.
		// If this happens, it will break the iteration, and crash will appear on some devices.
		list<int> copiedIDs(audioIDsIter->second);

		for (int audioID : copiedIDs)
		{
			_audioEngineImpl->stop(audioID);

			auto itInfo = _audioIDInfoMap.find(audioID);
			if (itInfo != _audioIDInfoMap.end())
			{
				if (itInfo->second.profileHelper)
				{
					itInfo->second.profileHelper->audioIDs.remove(audioID);
				}
				_audioIDInfoMap.erase(audioID);
			}
		}
		_audioPathIDMap.erase(filePath);
	}

	if (_audioEngineImpl)
	{
		_audioEngineImpl->uncache(filePath);
	}
}

void AudioEngine::uncacheAll()
{
	if (!_audioEngineImpl) {
		return;
	}
	stopAll();
	_audioEngineImpl->uncacheAll();
}

float AudioEngine::getDuration(int audioID)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end() && it->second.state != AudioState::INITIALIZING)
	{
		if (it->second.duration == TIME_UNKNOWN)
		{
			it->second.duration = _audioEngineImpl->getDuration(audioID);
		}
		return it->second.duration;
	}

	return TIME_UNKNOWN;
}

bool AudioEngine::setCurrentTime(int audioID, float time)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end() && it->second.state != AudioState::INITIALIZING) {
		return _audioEngineImpl->setCurrentTime(audioID, time);
	}

	return false;
}

float AudioEngine::getCurrentTime(int audioID)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end() && it->second.state != AudioState::INITIALIZING) {
		return _audioEngineImpl->getCurrentTime(audioID);
	}
	return 0.0f;
}

void AudioEngine::setFinishCallback(int audioID, const function<void(int, const string &)> &callback)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end()) {
		_audioEngineImpl->setFinishCallback(audioID, callback);
	}
}

bool AudioEngine::setMaxAudioInstance(int maxInstances)
{
	if (maxInstances > 0 && maxInstances <= MAX_AUDIOINSTANCES) {
		_maxInstances = maxInstances;
		return true;
	}

	return false;
}

bool AudioEngine::isLoop(int audioID)
{
	auto tmpIterator = _audioIDInfoMap.find(audioID);
	if (tmpIterator != _audioIDInfoMap.end())
	{
		return tmpIterator->second.loop;
	}

	log("AudioEngine::isLoop-->The audio instance %d is non-existent", audioID);
	return false;
}

float AudioEngine::getVolume(int audioID)
{
	auto tmpIterator = _audioIDInfoMap.find(audioID);
	if (tmpIterator != _audioIDInfoMap.end())
	{
		return tmpIterator->second.volume;
	}

	log("AudioEngine::getVolume-->The audio instance %d is non-existent", audioID);
	return 0.0f;
}

AudioEngine::AudioState AudioEngine::getState(int audioID)
{
	auto tmpIterator = _audioIDInfoMap.find(audioID);
	if (tmpIterator != _audioIDInfoMap.end())
	{
		return tmpIterator->second.state;
	}

	return AudioState::ERROR;
}

cocos2d::experimental::AudioProfile* AudioEngine::getProfile(int audioID)
{
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end())
	{
		return &it->second.profileHelper->profile;
	}

	return nullptr;
}

cocos2d::experimental::AudioProfile* AudioEngine::getDefaultProfile()
{
	if (_defaultProfileHelper == nullptr)
	{
		_defaultProfileHelper = new (nothrow) ProfileHelper();
	}

	return &_defaultProfileHelper->profile;
}

cocos2d::experimental::AudioProfile* AudioEngine::getProfile(const string& name)
{
	auto it = _audioPathProfileHelperMap.find(name);
	if (it != _audioPathProfileHelperMap.end()) {
		return &it->second.profile;
	}
	else {
		return nullptr;
	}
}

void AudioEngine::preload(const string& filePath, function<void(bool isSuccess)> callback)
{
	preload(filePath, nullptr, callback, nullptr);
}

bool AudioEngine::preload(const string& filePath, fcyStream* stream
	, function<void(bool isSuccess)> callback, AudioCache** cache)
{
	return preload(filePath, stream, 0.0, -1.0, callback, cache);
}

bool AudioEngine::preload(const string& filePath, fcyStream* stream, double loopA, double loopB,
	const function<void(bool isSuccess)>& callback, AudioCache** cache)
{
	if (!isEnabled())
	{
		callback(false);
		return false;
	}
	if (!lazyInit())
		return false;
	if (!_audioEngineImpl)
		return false;

	if (!stream && !FileUtils::getInstance()->isFileExist(filePath)) {
		if (callback)
			callback(false);
		return false;
	}

	auto c = _audioEngineImpl->preload(filePath, stream, loopA, loopB, callback);
	if (cache)
		*cache = c;
	return !!c;
}

void AudioEngine::addTask(const function<void()>& task)
{
	lazyInit();

	if (_audioEngineImpl && s_threadPool)
	{
		s_threadPool->addTask(task);
	}
}

int AudioEngine::getPlayingAudioCount()
{
	return static_cast<int>(_audioIDInfoMap.size());
}

void AudioEngine::setEnabled(bool isEnabled)
{
	if (_isEnabled != isEnabled)
	{
		_isEnabled = isEnabled;

		if (!_isEnabled)
		{
			stopAll();
		}
	}
}

bool AudioEngine::isEnabled()
{
	return _isEnabled;
}

bool AudioEngine::setSourceParam(int audioID, const SourceParam& param)
{
	return _audioEngineImpl->setSourceParam(audioID, param);
}

const SourceParam* AudioEngine::getSourceParam(int audioID)
{
	return _audioEngineImpl->getSourceParam(audioID);
}

bool AudioEngine::setListenerParam(const ListenerParam& param)
{
	return _audioEngineImpl->setListenerParam(param);
}

const ListenerParam* AudioEngine::getListenerParam()
{
	return _audioEngineImpl->getListenerParam();
}

AudioPlayer* AudioEngine::getPlayer(int audioID)
{
	AudioPlayer* ret = nullptr;
	auto it = _audioIDInfoMap.find(audioID);
	if (it != _audioIDInfoMap.end()) {
		ret = _audioEngineImpl->getPlayer(audioID);
	}
	return ret;
}

AudioEngine::AudioInfo::AudioInfo():
filePath(nullptr),
profileHelper(nullptr),
volume(1.0f),
loop(false),
duration(TIME_UNKNOWN),
state(AudioState::INITIALIZING)
{

}

AudioEngine::AudioInfo::~AudioInfo()
{
}
