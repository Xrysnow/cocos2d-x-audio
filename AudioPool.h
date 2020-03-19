#pragma once
#include "AudioCommon.h"
#include <vector>
#include <mutex>
#include <queue>
#include <map>

namespace audio
{
	class Source;

	class Pool
	{
		friend class Engine;
		friend class Source;
		Pool();
		virtual ~Pool();
		bool init();
		void end();
	public:

		static Pool* getInstance();
		static void destroyInstance();

		/**
		 * Checks whether an OpenAL source is available.
		 * @return True if at least one is available, false otherwise.
		 **/
		bool isAvailable();

		/**
		 * Checks whether a Source is currently in the playing list.
		 **/
		bool isPlaying(Source *s);

		void update();

		int getActiveSourceCount() const;
		int getMaxSources() const;

	private:

		std::unique_lock<std::mutex> lock();
		std::vector<Source*> getPlayingSources();

		/**
		 * Makes the specified OpenAL source available for use.
		 * @param source The OpenAL source.
		 **/
		bool releaseSource(Source *source, bool stop = true);

		bool assignSource(Source *source, ALuint &out, char &wasPlaying);
		bool findSource(Source *source, ALuint &out);

		static Pool* instance;

		// Maximum possible number of OpenAL sources the pool attempts to generate.
		static const int MAX_SOURCES = 64;

		// OpenAL sources
		ALuint sources[MAX_SOURCES];

		// Total number of created sources in the pool.
		int totalSources;

		// A queue of available sources.
		std::queue<ALuint> available;

		// A map of playing sources.
		std::map<Source*, ALuint> playing;

		// Only one thread can access this object at the same time. This mutex will
		// make sure of that.
		std::mutex mutex;
	};	
}
