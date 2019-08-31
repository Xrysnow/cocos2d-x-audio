#include "AudioEngine.h"
#include <functional>

using namespace std;
using namespace audio;

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
		while (true)
		{
			{
				_lock lock(mutex);
				if (finish)
					return;
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
		worker = new std::thread(std::bind(&PoolThread::threadFunction, this));
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
		std::string str((ALCchar*)&devstr[offset]);
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
	// Passing null for default device.
	device = alcOpenDevice(nullptr);

	if (device == nullptr)
	{
		lastError = "Could not open device.";
		return false;
	}

#ifdef ALC_EXT_EFX
	ALint attribs[4] = { ALC_MAX_AUXILIARY_SENDS, MAX_SOURCE_EFFECTS, 0, 0 };
#else
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

#ifdef ALC_EXT_EFX
	initializeEFX();

	alcGetIntegerv(device, ALC_MAX_AUXILIARY_SENDS, 1, &MAX_SOURCE_EFFECTS);

	alGetError();
	if (alGenAuxiliaryEffectSlots)
	{
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

	pool = Pool::getInstance();
	if(!pool)
	{
		//for (auto c : capture)
		//	delete c;
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
		alcDestroyContext(context);
		alcCloseDevice(device);
		lastError = "Could not initialize source pool.";
		return false;
	}
	PoolThread::Instance = new PoolThread(pool);
	valid = true;
	return true;
}

void Engine::end()
{
	valid = false;
	PoolThread::Instance->setFinish();
	delete PoolThread::Instance;
	delete pool;

	capture.clear();

#ifdef ALC_EXT_EFX
	for (auto e : effectmap)
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
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
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

std::string audio::string_format(const char* format, ...)
{
	constexpr auto BUFFER_LENGTH = 512;
	va_list args;
	std::string buffer(BUFFER_LENGTH, '\0');

	va_start(args, format);
	int nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
	va_end(args);

	if (nret >= 0) {
		if ((unsigned int)nret < buffer.length()) {
			buffer.resize(nret);
		}
		else if ((unsigned int)nret > buffer.length()) { // VS2015/2017 or later Visual Studio Version
			buffer.resize(nret);

			va_start(args, format);
			nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
			va_end(args);

			assert(nret == buffer.length());
		}
		// else equals, do nothing.
	}
	else { // less or equal VS2013 and Unix System glibc implement.
		do {
			buffer.resize(buffer.length() * 3 / 2);

			va_start(args, format);
			nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
			va_end(args);

		} while (nret < 0);

		buffer.resize(nret);
	}

	return buffer;
}
