#pragma once
#include "base/CCRef.h"
#include "base/CCScheduler.h"
#include "AudioCache.h"
#include "AudioPlayer.h"
#include "AudioEngine.h"
#include <unordered_map>

#define MAX_AUDIOINSTANCES 32

namespace xAudio
{
	class AudioEngineImpl : public cocos2d::Ref
	{
	public:
		AudioEngineImpl();
		~AudioEngineImpl();

		bool init();
		AudioCache* preload(const std::string& filePath,
			AudioStream* stream = nullptr, std::function<void(bool)> callback = nullptr);
		AudioCache* preload(const std::string& filePath,
			AudioStream* stream, double loopA, double loopB, std::function<void(bool)> callback = nullptr);
		int play2d(const std::string &fileFullPath, SourceParam* param = nullptr, bool sync = false);
		void setVolume(int audioID, float volume);
		void setLoop(int audioID, bool loop);
		bool pause(int audioID);
		bool resume(int audioID);
		void stop(int audioID);
		void stopAll();
		float getDuration(int audioID);
		float getCurrentTime(int audioID);
		bool setCurrentTime(int audioID, float time);
		void setFinishCallback(int audioID, const std::function<void(int, const std::string &)> &callback);

		bool setSourceParam(int audioID, const SourceParam& param);
		const SourceParam* getSourceParam(int audioID);
		bool setListenerParam(const ListenerParam& param);
		const ListenerParam* getListenerParam() const;

		void uncache(const std::string& filePath);
		void uncacheAll();
		
		void update(float dt);

		AudioPlayer* getPlayer(int audioID);
		void waitSubThread();
	protected:
		void _play2d(AudioCache *cache, int audioID, bool block);

		ListenerParam _lparam;

		ALuint _alSources[MAX_AUDIOINSTANCES];

		//source,used
		std::unordered_map<ALuint, bool> _alSourceUsed;

		//filePath,bufferInfo
		std::unordered_map<std::string, AudioCache> _audioCaches;

		//audioID,AudioInfo
		std::unordered_map<int, AudioPlayer*>  _audioPlayers;
		std::mutex _threadMutex;

		bool _lazyInitLoop;

		int _currentAudioID;
		cocos2d::Scheduler* _scheduler;

	};	
}
