#pragma once
#include "AudioMacros.h"
#include "AudioSource.h"
#include "AudioEffect.h"
#include "AudioPool.h"
#include "AudioDecoder.h"
#include "AudioRecordingDevice.h"
#include "ALHeader.h"
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
		enum class DistanceModel
		{
			NONE,
			INVERSE,
			INVERSE_CLAMPED,
			LINEAR,
			LINEAR_CLAMPED,
			EXPONENT,
			EXPONENT_CLAMPED,
			MAX_ENUM
		};

		/**
		 * Gets the OpenAL format identifier based on number of
		 * channels and bits.
		 * @param channels
		 * @param bitDepth Either 8-bit samples, or 16-bit samples.
		 * @return One of AL_FORMAT_*, or AL_NONE if unsupported format.
		 **/
		static ALenum getFormat(int bitDepth, int channels);

		/**
		 * Gets the current number of simultaneous playing sources.
		 * @return The current number of simultaneous playing sources.
		 **/
		static int getActiveSourceCount();

		/**
		 * Gets the maximum supported number of simultaneous playing sources.
		 * @return The maximum supported number of simultaneous playing sources.
		 **/
		static int getMaxSourceCount();

		/**
		 * Play the specified Sources.
		 * @param sources The Sources to play.
		 **/
		static bool play(const std::vector<Source*> &sources);

		/**
		 * Stops playback on the specified sources.
		 * @param sources The sources on which to stop the playback.
		 **/
		static void stop(const std::vector<Source*> &sources);

		/**
		 * Stops all playing audio.
		 **/
		static void stop();

		/**
		 * Pauses playback on the specified sources.
		 * @param sources The sources on which to pause the playback.
		 **/
		static void pause(const std::vector<Source*> &sources);

		/**
		 * Pauses all audio.
		 **/
		static std::vector<Source*> pause();

		/**
		 * Sets the master volume, where 0.0f is min (off) and 1.0f is max.
		 * @param volume The new master volume.
		 **/
		static void setVolume(float volume);

		/**
		 * Gets the master volume.
		 * @return The current master volume.
		 **/
		static float getVolume();

		/**
		 * Gets the position of the listener.
		 **/
		static cocos2d::Vec3 getPosition();

		/**
		 * Sets the position of the listener.
		 **/
		static void setPosition(const cocos2d::Vec3& v);

		/**
		 * Gets the orientation of the listener.
		 * @return A vector array of size 2 containing the forward
		 * vector and the up vector.
		 **/
		static std::array<cocos2d::Vec3, 2> getOrientation();

		/**
		 * Sets the orientation of the listener.
		 * @param forward the forward vector
		 * @param up the up vector.
		 **/
		static void setOrientation(const cocos2d::Vec3& forward, const cocos2d::Vec3& up);

		/**
		 * Gets the velocity of the listener.
		 **/
		static cocos2d::Vec3 getVelocity();

		/**
		 * Sets the velocity of the listener.
		 **/
		static void setVelocity(const cocos2d::Vec3& v);

		static void setDopplerScale(float scale);

		static float getDopplerScale();

		//void setMeter(float scale);

		//float getMeter() const;

		/**
		 * @return Reference to a vector of pointers to recording devices. May be empty.
		 **/
		static std::vector<RecordingDevice*> getRecordingDevices();

		/**
		 * Gets the distance model used for attenuation.
		 * @return Distance model.
		 */
		static DistanceModel getDistanceModel();

		/**
		 * Sets the distance model used for attenuation.
		 * @param distanceModel Distance model.
		 */
		static void setDistanceModel(DistanceModel distanceModel);

		/**
		 * Sets scene EFX effect.
		 * @param name Effect name to use.
		 * @param params Effect description table.
		 * @return true if successful, false otherwise.
		 */
		static bool setEffect(const std::string& name, const Effect::ParamMap& params);

		/**
		 * Removes scene EFX effect.
		 * @param name Effect name to clear.
		 * @return true if successful, false otherwise.
		 */
		static bool removeEffect(const std::string& name);

		/**
		 * Gets scene EFX effect.
		 * @param name Effect name to get data from.
		 * @return Effect description table.
		 */
		static Effect::ParamMap getEffect(const std::string& name);

		/**
		 * Gets list of EFX effect names.
		 * @return List of EFX names to fill.
		 */
		static std::vector<std::string> getActiveEffects();

		/**
		 * Gets maximum number of scene EFX effects.
		 * @return number of effects.
		 */
		static int getMaxEffectCount();

		/**
		 * Gets maximum number of source EFX effects.
		 * @return number of effects.
		 */
		static int getMaxSourceEffectCount();

		/**
		 * Gets EFX (or analog) availability.
		 * @return true if supported.
		 */
		static bool isEffectSupported();

		/**
		 * Sets whether audio from other apps mixes with love.audio or is muted,
		 * on supported platforms.
		 **/
		//static bool setMixWithSystem(bool mix);

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

	std::string string_format(const char* format, ...);

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
