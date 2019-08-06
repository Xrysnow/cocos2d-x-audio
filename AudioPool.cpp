#include "AudioPool.h"
#include "AudioSource.h"

using namespace audio;

Pool* Pool::instance = nullptr;

Pool::Pool()
	: sources()
	, totalSources(0)
{
}

Pool::~Pool()
{
}

bool Pool::init()
{
	// Clear errors.
	alGetError();

	// Generate sources.
	for (int i = 0; i < MAX_SOURCES; i++)
	{
		alGenSources(1, &sources[i]);

		// We might hit an implementation-dependent limit on the total number
		// of sources before reaching MAX_SOURCES.
		if (alGetError() != AL_NO_ERROR)
			break;

		totalSources++;
	}

	if (totalSources < 4)
	{
		AINFO("can not generate enough sources, got %d", totalSources);
		return false;
	}

#ifdef AL_SOFT_direct_channels
	ALboolean hasext = alIsExtensionPresent("AL_SOFT_direct_channels");
#endif

	// Make all sources available initially.
	for (int i = 0; i < totalSources; i++)
	{
#ifdef AL_SOFT_direct_channels
		if (hasext)
		{
			// Bypass virtualization of speakers for multi-channel sources in OpenAL Soft.
			alSourcei(sources[i], AL_DIRECT_CHANNELS_SOFT, AL_TRUE);
		}
#endif

		available.push(sources[i]);
	}
	return true;
}

void Pool::end()
{
	Source::stopAll();
	// Free all sources.
	alDeleteSources(totalSources, sources);
}

Pool* Pool::getInstance()
{
	if (!instance)
	{
		instance = new (std::nothrow) Pool();
		if (!instance || !instance->init())
		{
			delete instance;
			instance = nullptr;
		}
	}
	return instance;
}

void Pool::destroyInstance()
{
	if (instance)
		instance->end();
	delete instance;
	instance = nullptr;
}

bool Pool::isAvailable()
{
	bool has = false;
	{
		auto lk = lock();
		has = !available.empty();
	}
	return has;
}

bool Pool::isPlaying(Source *s)
{
	bool p = false;
	{
		auto lk = lock();
		p = (playing.find(s) != playing.end());
	}
	return p;
}

void Pool::update()
{
	auto lk = lock();

	std::vector<Source*> torelease;

	for (const auto &i : playing)
	{
		// finished source will be released
		if (!i.first->update())
			torelease.push_back(i.first);
	}

	for (auto& s : torelease)
		releaseSource(s);
}

int Pool::getActiveSourceCount() const
{
	return (int)playing.size();
}

int Pool::getMaxSources() const
{
	return totalSources;
}

std::unique_lock<std::mutex> Pool::lock()
{
	return std::unique_lock<std::mutex>{mutex};
}

bool Pool::assignSource(Source *source, ALuint &out, char &wasPlaying)
{
	out = 0;

	if (findSource(source, out))
		return wasPlaying = true;

	wasPlaying = false;

	if (available.empty())
		return false;

	out = available.front();
	available.pop();

	playing.insert(std::make_pair(source, out));
	source->retain();
	return true;
}

bool Pool::releaseSource(Source *source, bool stop)
{
	ALuint s;

	if (findSource(source, s))
	{
		if (stop)
			source->stopAtomic();
		source->release();//TODO: ???
		available.push(s);
		playing.erase(source);
		return true;
	}

	return false;
}

bool Pool::findSource(Source *source, ALuint &out)
{
	const auto i = playing.find(source);

	if (i == playing.end())
		return false;

	out = i->second;
	return true;
}

std::vector<Source*> Pool::getPlayingSources()
{
	std::vector<Source*> sources;
	sources.reserve(playing.size());
	for (auto &i : playing)
		sources.push_back(i.first);
	return sources;
}

