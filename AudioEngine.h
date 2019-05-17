#pragma once
#include "audio/include/AudioEngine.h"
#include "AudioParam.h"
#include "AudioEngineImpl.h"
#include "AudioStream.h"
#include "base/CCData.h"
#ifdef ERROR
#undef ERROR
#endif // ERROR

namespace xAudio
{
	
	class AudioEngine// : public cocos2d::experimental::AudioEngine
	{
	public:
		/** AudioState enum,all possible states of an audio instance.*/
		enum class AudioState
		{
			ERROR = -1,
			INITIALIZING,
			PLAYING,
			PAUSED
		};
		static const int INVALID_AUDIO_ID;
		static const float TIME_UNKNOWN;
		static std::vector<int> tempPaused;

		static bool lazyInit();
		static void end();
		static cocos2d::experimental::AudioProfile* getDefaultProfile();
		static int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f, bool block = false,
			const cocos2d::experimental::AudioProfile *profile = nullptr);
		static int play2d(const std::string& filePath, SourceParam* param, bool block = false,
			const cocos2d::experimental::AudioProfile *profile = nullptr);
		static void setLoop(int audioID, bool loop);
		static bool isLoop(int audioID);
		static void setVolume(int audioID, float volume);
		static float getVolume(int audioID);
		static void pause(int audioID);
		static void pauseAll();
		static void pauseTemp();
		static void resume(int audioID);
		static void resumeAll();
		static void resumeTemp();
		static void stop(int audioID);
		static void stopAll();
		static bool setCurrentTime(int audioID, float sec);
		static float getCurrentTime(int audioID);
		static float getDuration(int audioID);
		static AudioState getState(int audioID);
		static void setFinishCallback(int audioID, const std::function<void(int, const std::string&)>& callback);
		static int getMaxAudioInstance() { return _maxInstances; }
		static bool setMaxAudioInstance(int maxInstances);
		static void uncache(const std::string& filePath);
		static void uncacheAll();
		static cocos2d::experimental::AudioProfile* getProfile(int audioID);
		static cocos2d::experimental::AudioProfile* getProfile(const std::string &profileName);
		static void preload(const std::string& filePath) { preload(filePath, nullptr); }
		static void preload(const std::string& filePath,
			std::function<void(bool isSuccess)> callback);
		static bool preload(const std::string& filePath,
			AudioStream* stream,
			std::function<void(bool isSuccess)> callback,
			AudioCache** cache = nullptr);
		static bool preload(const std::string& filePath,
			AudioStream* stream,
			double loopA,
			double loopB,
		    const std::function<void(bool isSuccess)>& callback,
			AudioCache** cache = nullptr);
		static int getPlayingAudioCount();
		static void setEnabled(bool isEnabled);
		static bool isEnabled();

		static bool setSourceParam(int audioID, const SourceParam& param);
		static const SourceParam* getSourceParam(int audioID);
		static bool setListenerParam(const ListenerParam& param);
		static const ListenerParam* getListenerParam();
		
		static AudioPlayer* getPlayer(int audioID);
	protected:
		static void addTask(const std::function<void()>& task);
		static void remove(int audioID);
	private:
		struct ProfileHelper
		{
			cocos2d::experimental::AudioProfile profile;

			std::list<int> audioIDs;

			double lastPlayTime;

			ProfileHelper()
				: lastPlayTime(0.0)
			{

			}
		};

		struct AudioInfo
		{
			const std::string* filePath;
			ProfileHelper* profileHelper;

			float volume;
			bool loop;
			float duration;
			AudioState state;

			AudioInfo();
			~AudioInfo();
			AudioInfo(const AudioInfo& info) = delete;
			AudioInfo(AudioInfo&& info) = delete;
			AudioInfo& operator=(const AudioInfo& info) = delete;
			AudioInfo& operator=(AudioInfo&& info) = delete;
		};

		//audioID,audioAttribute
		static std::unordered_map<int, AudioInfo> _audioIDInfoMap;

		//audio file path,audio IDs
		static std::unordered_map<std::string, std::list<int>> _audioPathIDMap;

		//profileName,ProfileHelper
		static std::unordered_map<std::string, ProfileHelper> _audioPathProfileHelperMap;

		static unsigned int _maxInstances;

		static ProfileHelper* _defaultProfileHelper;

		static AudioEngineImpl* _audioEngineImpl;

		class AudioEngineThreadPool;
		static AudioEngineThreadPool* s_threadPool;

		static bool _isEnabled;

		friend class AudioEngineImpl;
	};	
}

using XAudioEngine = xAudio::AudioEngine;
