#pragma once
#include "AudioSource.h"
#include "AudioEffect.h"
#include "AudioPool.h"
#include "AudioDecoder.h"
#include "AudioRecordingDevice.h"
#include "base/CCVector.h"
#include <vector>
#include <stack>
#include <array>
#include <string>
#include <map>

namespace audio
{
	class Engine
	{
	public:
		/**
		 * The different distance models.
		 */
		enum class DistanceModel
		{
			/** Sources do not get attenuated. */
			NONE,
			/** Inverse distance attenuation. */
			INVERSE,
			/** Inverse distance attenuation. Gain is clamped. */
			INVERSE_CLAMPED,
			/** Linear attenuation. */
			LINEAR,
			/** Linear attenuation. Gain is clamped. */
			LINEAR_CLAMPED,
			/** Exponential attenuation. */
			EXPONENT,
			/** Exponential attenuation. Gain is clamped. */
			EXPONENT_CLAMPED,
			MAX_ENUM
		};

		/**
		 * Gets the OpenAL format identifier based on number of
		 * channels and bits.
		 * @param channels Number of channels
		 * @param bitDepth Either 8-bit samples, or 16-bit samples.
		 * @return One of AL_FORMAT_*, or AL_NONE if unsupported format.
		 */
		static ALenum getFormat(int bitDepth, int channels);

		/**
		 * Gets the current number of simultaneous playing sources.
		 * @return The current number of simultaneous playing sources.
		 */
		static int getActiveSourceCount();

		/**
		 * Gets the maximum supported number of simultaneous playing sources.
		 * @return The maximum supported number of simultaneous playing sources.
		 */
		static int getMaxSourceCount();

		/**
		 * Simultaneously plays all given Sources.
		 * @param sources A list containing Sources to play.
		 */
		static bool play(const std::vector<Source*> &sources);

		/**
		 * Simultaneously stops all given Sources.
		 * @param sources A list containing Sources to stop.
		 */
		static void stop(const std::vector<Source*> &sources);

		/**
		 * Stops all currently active sources.
		 */
		static void stop();

		/**
		 * Pauses the given Sources.
		 * @param sources A list containing Sources to pause.
		 */
		static void pause(const std::vector<Source*> &sources);

		/**
		 * Pauses all currently active Sources and returns them.
		 * @return A list containing Sources that were paused by this call.
		 */
		static std::vector<Source*> pause();

		/**
		 * Sets the master volume, where 0.0f is min (off) and 1.0f is max.
		 * @param volume The new master volume.
		 */
		static void setVolume(float volume);

		/**
		 * Gets the master volume.
		 * @return The current master volume.
		 */
		static float getVolume();

		/**
		 * Gets the position of the listener.
		 * @note Positional audio only works for mono (i.e. non-stereo) sources.
		 * @return The position of the listener.
		 */
		static cocos2d::Vec3 getPosition();

		/**
		 * Sets the position of the listener.
		 * @param v The position of the listener.
		 */
		static void setPosition(const cocos2d::Vec3& v);

		/**
		 * Gets the orientation of the listener.
		 * @return A vector array of size 2 containing the forward
		 * vector and the up vector of the listener orientation.
		 */
		static std::array<cocos2d::Vec3, 2> getOrientation();

		/**
		 * Sets the orientation of the listener.
		 * @param forward Forward vector of the listener orientation.
		 * @param up Up vector of the listener orientation.
		 */
		static void setOrientation(const cocos2d::Vec3& forward, const cocos2d::Vec3& up);

		/**
		 * Gets the velocity of the listener.
		 * @return The velocity of the listener.
		 */
		static cocos2d::Vec3 getVelocity();

		/**
		 * Sets the velocity of the listener.
		 * @param v The velocity of the listener.
		 */
		static void setVelocity(const cocos2d::Vec3& v);

		/**
		 * Sets a global scale factor for velocity-based doppler effects. The default scale value is 1.
		 * @param scale The new doppler scale factor. The scale must be greater than 0.
		 */
		static void setDopplerScale(float scale);

		/**
		 * Gets the current global scale factor for velocity-based doppler effects.
		 * @return The current doppler scale factor.
		 */
		static float getDopplerScale();

		//void setMeter(float scale);

		//float getMeter() const;

		/**
		 * Gets a list of RecordingDevices on the system.
		 * 
		 * The first device in the list is the user's default recording device. The list may be empty
		 * if there are no microphones connected to the system.
		 * @return The list of connected recording devices.
		 */
		static std::vector<RecordingDevice*> getRecordingDevices();

		/**
		 * Gets the distance attenuation model. The default is 'INVERSE_CLAMPED'.
		 * @return The current distance model.
		 */
		static DistanceModel getDistanceModel();

		/**
		 * Sets the distance attenuation model.
		 * @param distanceModel The new distance model.
		 */
		static void setDistanceModel(DistanceModel distanceModel);

		/**
		 * Defines an effect that can be applied to a Source.
		 * @note Not all system supports audio effects. Use isEffectsSupported to check.
		 * @param name Name of the effect.
		 * @param params The parameters to use for the effect.
		 * @return Whether the effect was successfully created.
		 */
		static bool setEffect(const std::string& name, const Effect::ParamMap& params);

		/**
		 * Removes the specific effect.
		 * @param name Name of the effect.
		 * @return Whether the effect was successfully removed.
		 */
		static bool removeEffect(const std::string& name);

		/**
		 * Gets parameters of the specific effect.
		 * @param name Name of the effect.
		 * @return Effect parameters.
		 */
		static Effect::ParamMap getEffect(const std::string& name);

		/**
		 * Gets a list of the names of the currently enabled effects.
		 * @return The list of the names of the currently enabled effects.
		 */
		static std::vector<std::string> getActiveEffects();

		/**
		 * Gets maximum number of active effects supported by the system.
		 * @return The maximum number of active effects.
		 */
		static int getMaxEffectCount();

		/**
		 * Gets maximum number of active Effects in a single Source.
		 * @note This function return 0 for system that doesn't support audio effects.
		 * @return The maximum number of active Effects per Source.
		 */
		static int getMaxSourceEffectCount();

		/**
		 * Gets whether audio effects are supported in the system.
		 * @note Older Linux distributions that ship with older OpenAL library may not support audio effects.
		 * Furthermore, iOS doesn't support audio effects.
		 * @return True if effects are supported, false otherwise.
		 */
		static bool isEffectSupported();

		static bool getEffectID(const std::string& name, ALuint &id);

		static void onEnterBackground();
		static void onEnterForeground();

		static std::string getLastError() { return lastError; }
		static bool isValid() { return valid; }

		static bool init();
		static void end();

	private:

		static void initializeEFX();

		static bool valid;
		// The OpenAL device.
		static ALCdevice *device;

		// The OpenAL context.
		static ALCcontext *context;

		// The OpenAL capture devices.
		static cocos2d::Vector<RecordingDevice*> capture;

		// The OpenAL effects
		struct EffectMapStorage
		{
			Effect *effect;
			ALuint slot;
		};
		static std::map<std::string, struct EffectMapStorage> effectmap;
		static std::stack<ALuint> slotlist;
		static int MAX_SCENE_EFFECTS;
		static int MAX_SOURCE_EFFECTS;

		// The Pool.
		static Pool *pool;

		static cocos2d::Vector<Source*> tempSources;

		static DistanceModel distanceModel;
		//static float metersPerUnit = 1.0;

		static std::string lastError;
	};

#ifdef ALC_EXT_EFX
	// Effect objects
	extern LPALGENEFFECTS alGenEffects;
	extern LPALDELETEEFFECTS alDeleteEffects;
	extern LPALISEFFECT alIsEffect;
	extern LPALEFFECTI alEffecti;
	extern LPALEFFECTIV alEffectiv;
	extern LPALEFFECTF alEffectf;
	extern LPALEFFECTFV alEffectfv;
	extern LPALGETEFFECTI alGetEffecti;
	extern LPALGETEFFECTIV alGetEffectiv;
	extern LPALGETEFFECTF alGetEffectf;
	extern LPALGETEFFECTFV alGetEffectfv;

	//Filter objects
	extern LPALGENFILTERS alGenFilters;
	extern LPALDELETEFILTERS alDeleteFilters;
	extern LPALISFILTER alIsFilter;
	extern LPALFILTERI alFilteri;
	extern LPALFILTERIV alFilteriv;
	extern LPALFILTERF alFilterf;
	extern LPALFILTERFV alFilterfv;
	extern LPALGETFILTERI alGetFilteri;
	extern LPALGETFILTERIV alGetFilteriv;
	extern LPALGETFILTERF alGetFilterf;
	extern LPALGETFILTERFV alGetFilterfv;

	// Auxiliary slot object
	extern LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
	extern LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
	extern LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
	extern LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
	extern LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
	extern LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
	extern LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
	extern LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
	extern LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
	extern LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
	extern LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;
#endif

}
