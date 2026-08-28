#include "AudioEngine.h"
#include "ALSupport.h"
#include <atomic>
#include <chrono>
#include <algorithm>
#include <functional>

using namespace std;
using namespace audio;

namespace
{
#ifdef ALC_SOFT_system_events
	LPALCEVENTCALLBACKSOFT sEventCallbackSOFT = nullptr;
	LPALCEVENTCONTROLSOFT  sEventControlSOFT  = nullptr;
#endif

	std::atomic<bool> sDeviceEventPending{ false };
	const std::chrono::milliseconds sDeviceCheckInterval{ 200 };
	const std::chrono::milliseconds sReopenThrottle{ 500 };
	std::chrono::steady_clock::time_point sLastDeviceCheck{
		std::chrono::steady_clock::now() - sDeviceCheckInterval };
	std::chrono::steady_clock::time_point sLastReopen{
		std::chrono::steady_clock::now() - sReopenThrottle };
	int sRecoveryFailures = 0;

	// "Device generation": incremented whenever the OpenAL context is
	// (re)created/destroyed; Sources use it to detect stale AL ids after a
	// context swap.
	std::atomic<int> sDeviceGeneration{ 0 };
}

static std::string getDefaultDeviceName()
{
	const ALCchar* name = nullptr;
	// query the real endpoint name
	if (alcIsExtensionPresent(NULL, "ALC_ENUMERATE_ALL_EXT") == ALC_TRUE)
		name = alcGetString(NULL, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
	// fallback
	if (!name || name[0] == '\0')
		name = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	return name ? std::string(name) : std::string();
}

#ifdef ALC_SOFT_system_events
static void ALC_APIENTRY audioDeviceEventCallback(
	ALCenum eventType, ALCenum /*deviceType*/, ALCdevice* /*device*/,
	ALCsizei /*length*/, const ALCchar* /*message*/, void* /*userParam*/) noexcept
{
	switch (eventType)
	{
	case ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT:
	case ALC_EVENT_TYPE_DEVICE_REMOVED_SOFT:
		sDeviceEventPending.store(true, std::memory_order_release);
		break;
	default:
		break;
	}
}
#endif // ALC_SOFT_system_events

class PoolThread
{
protected:
	using _lock = std::unique_lock<std::mutex>;
	Pool *pool;
	// Set this to true when the thread should finish.
	// Main thread will write to this value, and PoolThread
	// will read from it.
	volatile bool finish;
	// finish lock
	std::mutex mutex;
	std::thread* worker = nullptr;
public:
	static PoolThread* Instance;

	void threadFunction()
	{
		// Device checks every 40 ticks (~200ms); checkDeviceChange() also
		// throttles internally.
		int deviceCheckTick = 0;
		while (true)
		{
			{
				_lock lock(mutex);
				if (finish)
					return;
			}

			if (++deviceCheckTick >= 40)
			{
				deviceCheckTick = 0;
				Engine::checkDeviceChange();
			}

			pool->update();
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}
	void setFinish()
	{
		_lock lock(mutex);
		finish = true;
	}
	PoolThread(Pool *pool)
		: pool(pool)
		, finish(false)
	{
		worker = new std::thread([this] { threadFunction(); });
	}
	~PoolThread()
	{
		//setFinish();
		worker->join();
		delete worker;
	}
};
PoolThread* PoolThread::Instance = nullptr;

bool Engine::valid = false;
ALCdevice* Engine::device = nullptr;
ALCcontext* Engine::context = nullptr;
Pool* Engine::pool = nullptr;
cocos2d::Vector<RecordingDevice*> Engine::capture{};
cocos2d::Vector<Source*> Engine::tempSources{};
Engine::DistanceModel Engine::distanceModel = DistanceModel::INVERSE_CLAMPED;

std::map<std::string, struct Engine::EffectMapStorage> Engine::effectmap{};
std::stack<ALuint> Engine::slotlist{};

int Engine::MAX_SCENE_EFFECTS = 64;
int Engine::MAX_SOURCE_EFFECTS = 64;
std::string Engine::lastError{};

LPALCREOPENDEVICESOFT Engine::alcReopenDeviceSoft = nullptr;
ALint Engine::initAttribs[4] = { 0, 0, 0, 0 };
bool Engine::hasInitAttribs = false;
std::string Engine::lastAppliedDevice;
std::string Engine::lastDefaultName;
bool Engine::devicePinned = false;

ALenum Engine::getFormat(int bitDepth, int channels)
{
	if (bitDepth != 8 && bitDepth != 16)
		return AL_NONE;

	if (channels == 1)
		return bitDepth == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
	else if (channels == 2)
		return bitDepth == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
#ifdef AL_EXT_MCFORMATS
	else if (alIsExtensionPresent("AL_EXT_MCFORMATS"))
	{
		if (channels == 6)
			return bitDepth == 8 ? AL_FORMAT_51CHN8 : AL_FORMAT_51CHN16;
		else if (channels == 8)
			return bitDepth == 8 ? AL_FORMAT_71CHN8 : AL_FORMAT_71CHN16;
	}
#endif
	return AL_NONE;
}

int Engine::getActiveSourceCount()
{
	return pool ? pool->getActiveSourceCount() : 0;
}

int Engine::getMaxSourceCount()
{
	return pool ? pool->getMaxSources() : 0;
}

int Engine::getDeviceGeneration()
{
	return sDeviceGeneration.load(std::memory_order_acquire);
}

bool Engine::play(const std::vector<Source*> &sources)
{
	return Source::playBatch(sources);
}

void Engine::stop(const std::vector<Source*> &sources)
{
	return Source::stopBatch(sources);
}

void Engine::stop()
{
	Source::stopAll();
}

void Engine::pause(const std::vector<Source*> &sources)
{
	return Source::pauseBatch(sources);
}

std::vector<Source*> Engine::pause()
{
	return Source::pauseAll();
}

void Engine::setVolume(float volume)
{
	volume = std::max(0.f, std::min(volume, 1.f));
	alListenerf(AL_GAIN, volume);
}

float Engine::getVolume()
{
	ALfloat volume;
	alGetListenerf(AL_GAIN, &volume);
	return volume;
}

cocos2d::Vec3 Engine::getPosition()
{
	cocos2d::Vec3 v;
	alGetListenerfv(AL_POSITION, (float*)&v);
	return v;
}

void Engine::setPosition(const cocos2d::Vec3& v)
{
	alListenerfv(AL_POSITION, (float*)&v);
}

std::array<cocos2d::Vec3, 2> Engine::getOrientation()
{
	std::array<cocos2d::Vec3, 2> v;
	alGetListenerfv(AL_ORIENTATION, (float*)v.data());
	return v;
}

void Engine::setOrientation(const cocos2d::Vec3& forward, const cocos2d::Vec3& up)
{
	cocos2d::Vec3 v[2] = { forward, up };
	alListenerfv(AL_ORIENTATION, (float*)v);
}

cocos2d::Vec3 Engine::getVelocity()
{
	cocos2d::Vec3 v;
	alGetListenerfv(AL_VELOCITY, (float*)&v);
	return v;
}

void Engine::setVelocity(const cocos2d::Vec3& v)
{
	alListenerfv(AL_VELOCITY, (float*)&v);
}

void Engine::setDopplerScale(float scale)
{
	scale = std::max(0.f, scale);
	alDopplerFactor(scale);
}

float Engine::getDopplerScale()
{
	return alGetFloat(AL_DOPPLER_FACTOR);
}
/*
void Engine::setMeter(float scale)
{
	if (scale >= 0.0f)
	{
		metersPerUnit = scale;
#ifdef ALC_EXT_EFX
		alListenerf(AL_METERS_PER_UNIT, scale);
#endif
	}
}

float Engine::getMeter() const
{
	return metersPerUnit;
}
*/
Engine::DistanceModel Engine::getDistanceModel()
{
	return distanceModel;
}

void Engine::setDistanceModel(DistanceModel distanceModel_)
{
	distanceModel = distanceModel_;

	switch (distanceModel)
	{
	case DistanceModel::NONE:
		alDistanceModel(AL_NONE);
		break;

	case DistanceModel::INVERSE:
		alDistanceModel(AL_INVERSE_DISTANCE);
		break;

	case DistanceModel::INVERSE_CLAMPED:
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
		break;

	case DistanceModel::LINEAR:
		alDistanceModel(AL_LINEAR_DISTANCE);
		break;

	case DistanceModel::LINEAR_CLAMPED:
		alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
		break;

	case DistanceModel::EXPONENT:
		alDistanceModel(AL_EXPONENT_DISTANCE);
		break;

	case DistanceModel::EXPONENT_CLAMPED:
		alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
		break;

	default:
		break;
	}
}

std::vector<RecordingDevice*> Engine::getRecordingDevices()
{
	if (!requestRecordAudioPermission())
		return {};
	
	std::vector<std::string> devnames;
	cocos2d::Vector<RecordingDevice*> devices;

	auto _defaultname = alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
	std::string defaultname;
	if (_defaultname)
		defaultname = _defaultname;

	//no device name obtained from AL, fallback to reading from device
	if (defaultname.empty())
	{
		//use some safe basic parameters - 8 kHz, 8 bits, 1 channel
		ALCdevice *defaultdevice = alcCaptureOpenDevice(NULL, 8000, AL_FORMAT_MONO8, 1024);
		if (alGetError() == AL_NO_ERROR)
		{
			defaultname = alcGetString(defaultdevice, ALC_CAPTURE_DEVICE_SPECIFIER);
			alcCaptureCloseDevice(defaultdevice);
		}
		else
		{
			//failed to open default recording device - bail, return empty list
			capture.clear();
			return {};
		}
	}

	devnames.reserve(capture.size());
	devnames.push_back(defaultname);

	//find devices name list
	const ALCchar *devstr = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
	if (!devstr)
		return {};
	size_t offset = 0;
	while (true)
	{
		if (devstr[offset] == '\0')
			break;
		std::string str(&devstr[offset]);
		if (str != defaultname)
			devnames.push_back(str);
		offset += str.length() + 1;
	}

	devices.reserve(devnames.size());
	//build ordered list of devices
	for (auto& devname : devnames)
	{
		bool needCreate = true;
		for (auto&& c : capture)
		{
			if (devname == c->getName())
			{
				devices.pushBack(c);
				needCreate = false;
				break;
			}
		}
		if (needCreate)
		{
			auto dev = new RecordingDevice(devname.c_str());
			dev->autorelease();
			devices.pushBack(dev);
		}
	}

	capture.clear();
	capture = devices;

	std::vector<RecordingDevice*> ret;
	for (ssize_t i = 0; i < capture.size(); i++)
		ret.push_back(capture.at(i));
	return ret;
}

bool Engine::setEffect(const std::string& name, const Effect::ParamMap& params)
{
	Effect *effect;
	ALuint slot;

	const auto iter = effectmap.find(name);
	if (iter == effectmap.end())
	{
		//new effect needed but no more slots
		if (effectmap.size() >= (unsigned int)MAX_SCENE_EFFECTS)
			return false;

		effect = new Effect();
		slot = slotlist.top();
		slotlist.pop();

		effectmap[name] = { effect, slot };
	}
	else
	{
		effect = iter->second.effect;
		slot = iter->second.slot;
	}

	const bool result = effect->setParams(params);

#ifdef ALC_EXT_EFX
	if (alAuxiliaryEffectSloti)
	{
		if (result)
		{
			auto it = params.find(Effect::Parameter::VOLUME);
			if (it != params.end())
				alAuxiliaryEffectSlotf(slot, AL_EFFECTSLOT_GAIN, it->second);
			alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, effect->getEffect());
		}
		else
			alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
		alGetError();
	}
#endif

	return result;
}

bool Engine::removeEffect(const std::string& name)
{
	auto iter = effectmap.find(name);
	if (iter == effectmap.end())
		return false;

	Effect *effect = iter->second.effect;
	ALuint slot = iter->second.slot;

#ifdef ALC_EXT_EFX
	if (alAuxiliaryEffectSloti)
		alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
#endif

	delete effect;
	effectmap.erase(iter);
	slotlist.push(slot);
	return true;
}

Effect::ParamMap Engine::getEffect(const std::string& name)
{
	const auto iter = effectmap.find(name);
	if (iter == effectmap.end())
		return {};
	return iter->second.effect->getParams();
}

std::vector<std::string> Engine::getActiveEffects()
{
	if (effectmap.empty())
		return {};
	std::vector<std::string> list;
	list.reserve(effectmap.size());
	for (auto& i : effectmap)
		list.push_back(i.first);
	return list;
}

int Engine::getMaxEffectCount()
{
	return MAX_SCENE_EFFECTS;
}

int Engine::getMaxSourceEffectCount()
{
	return MAX_SOURCE_EFFECTS;
}

bool Engine::isEffectSupported()
{
#ifdef ALC_EXT_EFX
	return (alGenEffects != nullptr);
#else
	return false;
#endif
}

bool Engine::getEffectID(const std::string& name, ALuint &id)
{
	const auto iter = effectmap.find(name);
	if (iter == effectmap.end())
		return false;

	id = iter->second.slot;
	return true;
}

void Engine::onEnterBackground()
{
	tempSources.clear();
	auto sources = Source::pauseAll();
	for (auto& s : sources)
		tempSources.pushBack(s);
}

void Engine::onEnterForeground()
{
	std::vector<Source*> sources;
	for (auto& s : tempSources)
		sources.push_back(s);
	Source::playBatch(sources);
	tempSources.clear();
}

bool Engine::init()
{
	// Check permission before opening new device
	requestRecordAudioPermission();

	// Passing null for default device.
	device = alcOpenDevice(nullptr);

	if (device == nullptr)
	{
		lastError = "Could not open device.";
		return false;
	}

	// Load the entry point
	if (alcIsExtensionPresent(device, "ALC_SOFT_reopen_device") == ALC_TRUE)
		alcReopenDeviceSoft = (LPALCREOPENDEVICESOFT)alcGetProcAddress(device, "alcReopenDeviceSOFT");
	else
		alcReopenDeviceSoft = nullptr;

#ifdef ALC_EXT_EFX
	ALint attribs[4] = { ALC_MAX_AUXILIARY_SENDS, MAX_SOURCE_EFFECTS, 0, 0 };
	// Remember attribute list for reopening
	hasInitAttribs = true;
	std::copy_n(attribs, 4, initAttribs);
#else
	hasInitAttribs = false;
	ALint *attribs = nullptr;
#endif

	context = alcCreateContext(device, attribs);

	if (context == nullptr)
	{
		lastError = "Could not create context.";
		return false;
	}

	if (!alcMakeContextCurrent(context) || alcGetError(device) != ALC_NO_ERROR)
	{
		lastError = "Could not make context current.";
		return false;
	}

	// New context => new AL object namespace: bump the device generation
	// (Sources detect stale ids via it, see overview in AudioEngine.h).
	++sDeviceGeneration;

#ifdef ALC_EXT_EFX
	initializeEFX();
#endif

	// EFX aux slots are context objects - allocate them once per context.
	createEffectSlots();

	pool = Pool::getInstance();
	if (!pool)
	{
		capture.clear();

#ifdef ALC_EXT_EFX
		if (alDeleteAuxiliaryEffectSlots)
		{
			while (!slotlist.empty())
			{
				alDeleteAuxiliaryEffectSlots(1, &slotlist.top());
				slotlist.pop();
			}
		}
#endif

		alcMakeContextCurrent(nullptr);
		if (context)
			alcDestroyContext(context);
		if (device)
			alcCloseDevice(device);
		lastError = "Could not initialize source pool.";
		return false;
	}

	// Rebuild the pool's OpenAL sources for THIS context.
	pool->init();

	PoolThread::Instance = new PoolThread(pool);

	initializeDeviceEvents();

	lastDefaultName = getDefaultDeviceName();
	lastAppliedDevice = lastDefaultName;

	valid = true;
	return true;
}

void Engine::end()
{
	valid = false;
	if (PoolThread::Instance)
	{
		PoolThread::Instance->setFinish();
		delete PoolThread::Instance;
		PoolThread::Instance = nullptr;
	}

	// Drain the pool while the OpenAL context is still current (valid AL
	// calls): stops all playing Sources and frees the pool's OpenAL sources.
	// The Pool OBJECT is deliberately NOT destroyed here - Source objects
	// hold a raw Pool* and their destructors call Pool::stop()/lock() (e.g.
	// when Lua refcounts drop after end()); destroying it would be a
	// use-after-free. The pool is a process-lifetime singleton and its
	// drained state is re-initialized by the next Engine::init().
	if (pool)
		pool->end();

	tempSources.clear(); // release the retained paused Sources (refcounted)

	capture.clear();

#ifdef ALC_EXT_EFX
	for (auto& e : effectmap)
	{
		delete e.second.effect;
		slotlist.push(e.second.slot);
	}

	if (alDeleteAuxiliaryEffectSlots)
	{
		while (!slotlist.empty())
		{
			alDeleteAuxiliaryEffectSlots(1, &slotlist.top());
			slotlist.pop();
		}
	}
#endif
	// Drop the effect registry itself (the Effect objects and slots were
	// deleted above); without this a re-init would leave dangling entries in
	// the static map (Engine::setEffect would return a freed pointer).
	effectmap.clear();

	alcMakeContextCurrent(nullptr);
	if (context)
	{
		alcDestroyContext(context);
		context = nullptr; // avoid double-free
	}
	if (device)
	{
		alcCloseDevice(device);
		device = nullptr;
	}

	// Bump the generation so destructors of still-alive Sources skip AL
	// deletes against the now-destroyed context (the ids died with it and
	// could collide with objects of a future context).
	++sDeviceGeneration;

	// Reset the device-tracking state
	sDeviceEventPending.store(false, std::memory_order_release);
	lastAppliedDevice.clear();
	lastDefaultName.clear();
	devicePinned = false;
}

void Engine::createEffectSlots()
{
	while (!slotlist.empty())
		slotlist.pop();

#ifdef ALC_EXT_EFX
	alcGetIntegerv(device, ALC_MAX_AUXILIARY_SENDS, 1, &MAX_SOURCE_EFFECTS);

	alGetError();
	if (alGenAuxiliaryEffectSlots)
	{
		// get real number of scene effects
		for (int i = 0; i < MAX_SCENE_EFFECTS; i++)
		{
			ALuint slot;
			alGenAuxiliaryEffectSlots(1, &slot);
			if (alGetError() == AL_NO_ERROR)
				slotlist.push(slot);
			else
			{
				MAX_SCENE_EFFECTS = i;
				break;
			}
		}
	}
	else
		MAX_SCENE_EFFECTS = MAX_SOURCE_EFFECTS = 0;
#else
	MAX_SCENE_EFFECTS = MAX_SOURCE_EFFECTS = 0;
#endif
}

void Engine::initializeDeviceEvents()
{
#ifdef ALC_SOFT_system_events
	// Push notifications for default-device changes / device removals; the
	// polling path in checkDeviceChange() remains as a fallback. A missing
	// extension just leaves the polling path active.
	if (alcIsExtensionPresent(device, "ALC_SOFT_system_events") != ALC_TRUE)
	{
		AWARN("ALC_SOFT_system_events not available");
		return;
	}
	sEventCallbackSOFT = (LPALCEVENTCALLBACKSOFT)alcGetProcAddress(NULL, "alcEventCallbackSOFT");
	sEventControlSOFT = (LPALCEVENTCONTROLSOFT)alcGetProcAddress(NULL, "alcEventControlSOFT");
	if (!sEventCallbackSOFT || !sEventControlSOFT)
	{
		AWARN("ALC_SOFT_system_events entry points not found");
		return;
	}

	sEventCallbackSOFT(audioDeviceEventCallback, nullptr);
	constexpr ALCenum events[2] = {
		ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT,
		ALC_EVENT_TYPE_DEVICE_REMOVED_SOFT
	};
	sEventControlSOFT(2, events, ALC_TRUE);
#else
	AINFO("ALC_SOFT_system_events not declared by the AL headers");
#endif
}

void Engine::checkDeviceChange()
{
	if (!valid || !device)
		return;

	// Throttle (also safe when called from other places than the PoolThread).
	const auto now = std::chrono::steady_clock::now();
	if (now - sLastDeviceCheck < sDeviceCheckInterval)
		return;
	sLastDeviceCheck = now;

	bool changed = false;
	bool disconnected = false;

	// Default device name observed in this check; lastDefaultName is only
	// advanced after the change was handled, so failures are retried.
	std::string observedDefault = lastDefaultName;

	// 1) Fast path: system-events notification (flag set by the callback).
	if (sDeviceEventPending.exchange(false, std::memory_order_acq_rel))
		changed = true;

	// 2) Polling: default device name differs (on Windows the old endpoint
	//    stays "connected", so this is what catches plain default switches).
	{
		const std::string defaultName = getDefaultDeviceName();
		if (defaultName != lastDefaultName)
		{
			changed = true;
			observedDefault = defaultName;
		}
	}

	// 3) Unplug: the currently open device reports ALC_CONNECTED == ALC_FALSE
	//    (leads to the recreation path; see the overview in AudioEngine.h).
#ifdef ALC_EXT_disconnect
	{
		ALint connected = ALC_TRUE;
		alcGetIntegerv(device, ALC_CONNECTED, 1, &connected);
		// Clear the error: without ALC_EXT_disconnect this is an invalid enum.
		alcGetError(device);
		if (connected == ALC_FALSE)
		{
			changed = true;
			disconnected = true;
		}
	}
#endif

	if (!changed)
		return;

	if (devicePinned && !disconnected)
	{
		// A fixed device was requested - don't hijack it on default changes
		// (still note the new default name so the check does not re-trigger).
		lastDefaultName = observedDefault;
		AINFO("audio device pinned to \"%s\", ignoring default device change",
			lastAppliedDevice.c_str());
		return;
	}

	// Windows emits several notifications for one user action.
	if (now - sLastReopen < sReopenThrottle)
	{
		//AINFO("audio device switch suppressed");
		return;
	}

	if (disconnected)
	{
		// The opened device is physically gone - in-place reopening cannot
		// revive it (see the overview in AudioEngine.h), so the recreation
		// path is used. It keeps retrying (~1/s) until some device exists.
		AINFO("device disconnected (detected default: \"%s\"), recreating it",
			observedDefault.c_str());
		sLastReopen = now;
		if (recoverDisconnectedDevice())
			sRecoveryFailures = 0; // tracking state was re-based inside
		else
		{
			++sRecoveryFailures;
			// Log the first failure, then every 10th attempt (no log flood).
			if (sRecoveryFailures == 1 || sRecoveryFailures % 10 == 0)
				AWARN("device recovery failed (%d consecutive attempts); retrying automatically",
					sRecoveryFailures);
		}
		return;
	}

	// Note: "observedDefault" may still be the cached pre-change name on
	// Windows; the authoritative endpoint is logged by reopenDevice() after
	// it succeeded. This branch is only reached while the device is connected.
	AINFO("switching to current default device: \"%s\"",
		observedDefault.c_str());
	if (reopenDevice(std::string())) // empty -> follow current default (NULL deviceName)
	{
		lastDefaultName = getDefaultDeviceName();
	}
	else
	{
		// Accept the change as "handled but not applied" so we do not
		// retry-spin; the next change triggers a new attempt.
		lastDefaultName = observedDefault;
		AWARN("audio device change not applied (%s); keeping the current audio device",
			alcReopenDeviceSoft ? "reopen failed" : "ALC_SOFT_reopen_device not supported");
	}
}

bool Engine::reopenDevice(const std::string& name)
{
	if (!valid || !device)
	{
		AERRO("reopenDevice: engine not initialized");
		return false;
	}

	// Record the attempt before calling so checkDeviceChange()'s throttle also
	// backs off repeating failures.
	sLastReopen = std::chrono::steady_clock::now();

	if (!alcReopenDeviceSoft)
	{
		// Extension unavailable: keep the originally opened device.
		AWARN("ALC_SOFT_reopen_device not supported; cannot switch the audio device");
		return false;
	}

	if (name.empty())
	{
		// Follow the current default: pass deviceName = NULL so the
		// implementation re-resolves it at call time. NEVER pre-resolve via
		// alcGetString(NULL, ALC_DEFAULT*_DEVICE_SPECIFIER) - those are cached
		// snapshots on Windows/OpenAL Soft and still name the OLD endpoint
		// right after a change.
		const ALCboolean ok = alcReopenDeviceSoft(device, nullptr,
			hasInitAttribs ? initAttribs : nullptr);
		if (ok == ALC_TRUE)
		{
			devicePinned = false;
			const ALCchar* actual = alcGetString(device, ALC_DEVICE_SPECIFIER);
			lastAppliedDevice = actual ? actual : std::string();
			AINFO("switched to default device: \"%s\"",
				lastAppliedDevice.empty() ? "<unknown>" : lastAppliedDevice.c_str());
			ALSupport::refresh();
			return true;
		}
		AWARN("alcReopenDeviceSOFT(NULL) failed (%s)", getErrorString(alcGetError(device)));
		return false;
	}

	// Switch to an explicitly named device and pin it.
	devicePinned = true;
	// already on that device
	if (name == lastAppliedDevice)
		return true;

	const ALCboolean ok = alcReopenDeviceSoft(device, name.c_str(),
		hasInitAttribs ? initAttribs : nullptr);
	if (ok == ALC_TRUE)
	{
		const ALCchar* actual = alcGetString(device, ALC_DEVICE_SPECIFIER);
		lastAppliedDevice = actual ? actual : name;
		AINFO("device reopened: \"%s\"", lastAppliedDevice.c_str());
		ALSupport::refresh();
		return true;
	}
	AWARN("alcReopenDeviceSOFT(\"%s\") failed (%s)", name.c_str(), getErrorString(alcGetError(device)));
	return false;
}

bool Engine::recoverDisconnectedDevice()
{
	AINFO("recovering from a disconnected audio device...");
	if (!valid || !device || !context || !pool)
	{
		AERRO("engine not initialized");
		return false;
	}

	// Snapshot context-level state for restoration.
	ALfloat pos[3], vel[3], orient[6];
	alGetListenerfv(AL_POSITION, pos);
	alGetListenerfv(AL_VELOCITY, vel);
	alGetListenerfv(AL_ORIENTATION, orient);
	ALfloat volume = 1.0f;
	alGetListenerf(AL_GAIN, &volume);
	const ALfloat doppler = alGetFloat(AL_DOPPLER_FACTOR);

	// Capture the currently assigned Sources (playing or paused) before the
	// context dies so they can resume automatically after the swap - their AL
	// ids are regenerated lazily by prepareAtomic() via the device generation.
	std::vector<Source*> resumeSources;
	{
		auto lk = pool->lock();
		resumeSources = pool->getPlayingSources();
	}

	// Open the replacement device+context FIRST. if no device exists,
	// the caller retries automatically once something is plugged in.
	ALCdevice* newDevice = alcOpenDevice(nullptr);
	if (!newDevice)
	{
		lastError = "Could not open audio device while recovering.";
		return false;
	}
	ALCcontext* newContext = alcCreateContext(newDevice, hasInitAttribs ? initAttribs : nullptr);
	if (!newContext)
	{
		alcCloseDevice(newDevice);
		lastError = "Could not create context while recovering.";
		return false;
	}

	// From here on the old context is being torn down. AL object ids are only
	// valid in the context that created them, so all cleanup happens BEFORE
	// destroying it (while it is still current).
#ifdef ALC_EXT_EFX
	// Effects, filters and aux slots are context objects as well.
	if (alDeleteAuxiliaryEffectSlots)
	{
		while (!slotlist.empty())
		{
			alDeleteAuxiliaryEffectSlots(1, &slotlist.top());
			slotlist.pop();
		}
	}
	for (auto& e : effectmap)
		delete e.second.effect;
	effectmap.clear();
#endif

	// Sources are deliberately NOT stopped: their state (decoder position,
	// properties) and the captured list are what allow the automatic resume
	// below; stale ids are never touched because prepareAtomic() regenerates
	// them first (generation check).

	// Make the new context current, then destroy the old one (alcDestroyContext
	// forbids destroying the current context).
	if (!alcMakeContextCurrent(newContext))
	{
		alcDestroyContext(newContext);
		alcCloseDevice(newDevice);
		AERRO("recoverDisconnectedDevice: cannot make the new context current");
		return false;
	}
	alcDestroyContext(context);
	alcCloseDevice(device);
	device = newDevice;
	context = newContext;

	// bump the device generation
	++sDeviceGeneration;

	// Rebuild context-owned objects
	createEffectSlots();
	{
		auto lk = pool->lock();
		pool->init();
	}

	// Restore the context state captured above.
	alListenerfv(AL_POSITION, pos);
	alListenerfv(AL_VELOCITY, vel);
	alListenerfv(AL_ORIENTATION, orient);
	alListenerf(AL_GAIN, volume);
	alDopplerFactor(doppler);
	setDistanceModel(distanceModel);

	std::vector<Source*> playableSources;
	playableSources.reserve(resumeSources.size());
	for (auto* s : resumeSources)
	{
		// Queue sources cannot be resumed
		if (s->getType() == Source::Type::QUEUE)
		{
			AINFO("queue-type audio source cannot be resumed automatically; re-queue it to play again");
			continue;
		}
		playableSources.push_back(s);
	}
	if (!playableSources.empty())
	{
		if (Source::playBatch(playableSources))
			AINFO("resumed %d audio source(s) on the new audio device", (int)playableSources.size());
		else
			AWARN("failed to resume all of the %d captured sources", (int)playableSources.size());
	}

	// Re-base the tracking state on the fresh device
	const ALCchar* actual = alcGetString(device, ALC_DEVICE_SPECIFIER);
	lastAppliedDevice = actual ? actual : std::string();
	devicePinned = false;
	lastDefaultName = getDefaultDeviceName();
	sDeviceEventPending.store(false, std::memory_order_release);
	ALSupport::refresh();

	AINFO("audio device recreated after disconnect: \"%s\"",
		lastAppliedDevice.empty() ? "<unknown>" : lastAppliedDevice.c_str());
	return true;
}


#ifdef ALC_EXT_EFX
namespace audio
{
	LPALGENEFFECTS alGenEffects = nullptr;
	LPALDELETEEFFECTS alDeleteEffects = nullptr;
	LPALISEFFECT alIsEffect = nullptr;
	LPALEFFECTI alEffecti = nullptr;
	LPALEFFECTIV alEffectiv = nullptr;
	LPALEFFECTF alEffectf = nullptr;
	LPALEFFECTFV alEffectfv = nullptr;
	LPALGETEFFECTI alGetEffecti = nullptr;
	LPALGETEFFECTIV alGetEffectiv = nullptr;
	LPALGETEFFECTF alGetEffectf = nullptr;
	LPALGETEFFECTFV alGetEffectfv = nullptr;
	LPALGENFILTERS alGenFilters = nullptr;
	LPALDELETEFILTERS alDeleteFilters = nullptr;
	LPALISFILTER alIsFilter = nullptr;
	LPALFILTERI alFilteri = nullptr;
	LPALFILTERIV alFilteriv = nullptr;
	LPALFILTERF alFilterf = nullptr;
	LPALFILTERFV alFilterfv = nullptr;
	LPALGETFILTERI alGetFilteri = nullptr;
	LPALGETFILTERIV alGetFilteriv = nullptr;
	LPALGETFILTERF alGetFilterf = nullptr;
	LPALGETFILTERFV alGetFilterfv = nullptr;
	LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots = nullptr;
	LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots = nullptr;
	LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot = nullptr;
	LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti = nullptr;
	LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv = nullptr;
	LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf = nullptr;
	LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv = nullptr;
	LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti = nullptr;
	LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv = nullptr;
	LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf = nullptr;
	LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv = nullptr;
}
#endif

#define GET_FUNC(TYPE, NAME) NAME = (TYPE)alGetProcAddress(#NAME); if(!(NAME)) break;

void Engine::initializeEFX()
{
#ifdef ALC_EXT_EFX
	if (alcIsExtensionPresent(device, "ALC_EXT_EFX") == AL_FALSE)
		return;

	bool ok = false;
	do
	{
		GET_FUNC(LPALGENEFFECTS, alGenEffects);
		GET_FUNC(LPALDELETEEFFECTS, alDeleteEffects);
		GET_FUNC(LPALISEFFECT, alIsEffect);
		GET_FUNC(LPALEFFECTI, alEffecti);
		GET_FUNC(LPALEFFECTIV, alEffectiv);
		GET_FUNC(LPALEFFECTF, alEffectf);
		GET_FUNC(LPALEFFECTFV, alEffectfv);
		GET_FUNC(LPALGETEFFECTI, alGetEffecti);
		GET_FUNC(LPALGETEFFECTIV, alGetEffectiv);
		GET_FUNC(LPALGETEFFECTF, alGetEffectf);
		GET_FUNC(LPALGETEFFECTFV, alGetEffectfv);
		GET_FUNC(LPALGENFILTERS, alGenFilters);
		GET_FUNC(LPALDELETEFILTERS, alDeleteFilters);
		GET_FUNC(LPALISFILTER, alIsFilter);
		GET_FUNC(LPALFILTERI, alFilteri);
		GET_FUNC(LPALFILTERIV, alFilteriv);
		GET_FUNC(LPALFILTERF, alFilterf);
		GET_FUNC(LPALFILTERFV, alFilterfv);
		GET_FUNC(LPALGETFILTERI, alGetFilteri);
		GET_FUNC(LPALGETFILTERIV, alGetFilteriv);
		GET_FUNC(LPALGETFILTERF, alGetFilterf);
		GET_FUNC(LPALGETFILTERFV, alGetFilterfv);
		GET_FUNC(LPALGENAUXILIARYEFFECTSLOTS, alGenAuxiliaryEffectSlots);
		GET_FUNC(LPALDELETEAUXILIARYEFFECTSLOTS, alDeleteAuxiliaryEffectSlots);
		GET_FUNC(LPALISAUXILIARYEFFECTSLOT, alIsAuxiliaryEffectSlot);
		GET_FUNC(LPALAUXILIARYEFFECTSLOTI, alAuxiliaryEffectSloti);
		GET_FUNC(LPALAUXILIARYEFFECTSLOTIV, alAuxiliaryEffectSlotiv);
		GET_FUNC(LPALAUXILIARYEFFECTSLOTF, alAuxiliaryEffectSlotf);
		GET_FUNC(LPALAUXILIARYEFFECTSLOTFV, alAuxiliaryEffectSlotfv);
		GET_FUNC(LPALGETAUXILIARYEFFECTSLOTI, alGetAuxiliaryEffectSloti);
		GET_FUNC(LPALGETAUXILIARYEFFECTSLOTIV, alGetAuxiliaryEffectSlotiv);
		GET_FUNC(LPALGETAUXILIARYEFFECTSLOTF, alGetAuxiliaryEffectSlotf);
		GET_FUNC(LPALGETAUXILIARYEFFECTSLOTFV, alGetAuxiliaryEffectSlotfv);
		ok = true;
	}
	while (false);
	//failed to initialize functions, revert to nullptr
	if (!ok)
	{
		alGenEffects = nullptr; alDeleteEffects = nullptr; alIsEffect = nullptr;
		alEffecti = nullptr; alEffectiv = nullptr; alEffectf = nullptr; alEffectfv = nullptr;
		alGetEffecti = nullptr; alGetEffectiv = nullptr; alGetEffectf = nullptr; alGetEffectfv = nullptr;
		alGenFilters = nullptr; alDeleteFilters = nullptr; alIsFilter = nullptr;
		alFilteri = nullptr; alFilteriv = nullptr; alFilterf = nullptr; alFilterfv = nullptr;
		alGetFilteri = nullptr; alGetFilteriv = nullptr; alGetFilterf = nullptr; alGetFilterfv = nullptr;
		alGenAuxiliaryEffectSlots = nullptr; alDeleteAuxiliaryEffectSlots = nullptr; alIsAuxiliaryEffectSlot = nullptr;
		alAuxiliaryEffectSloti = nullptr; alAuxiliaryEffectSlotiv = nullptr;
		alAuxiliaryEffectSlotf = nullptr; alAuxiliaryEffectSlotfv = nullptr;
		alGetAuxiliaryEffectSloti = nullptr; alGetAuxiliaryEffectSlotiv = nullptr;
		alGetAuxiliaryEffectSlotf = nullptr; alGetAuxiliaryEffectSlotfv = nullptr;
	}
#endif
}
