#pragma once
#include "AudioMacros.h"
#include "AudioSource.h"
#include "AudioEffect.h"
#include "AudioPool.h"

#include "ALHeader.h"
#include "AudioRecordingDevice.h"
#include "AudioDecoder.h"

#include <map>
#include <vector>
#include <stack>
#include <cmath>

namespace audio
{
	class Engine
	{
	public:
		/**
		 * Attenuation by distance.
		 */
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
	private:

		static Engine* s_instance;
		Engine();
		virtual ~Engine();
	public:

		static Engine* getInstance();
		static void destroyInstance();

		/**
		 * Gets the OpenAL format identifier based on number of
		 * channels and bits.
		 * @param channels
		 * @param bitDepth Either 8-bit samples, or 16-bit samples.
		 * @return One of AL_FORMAT_*, or AL_NONE if unsupported format.
		 **/
		static ALenum getFormat(int bitDepth, int channels);

		//Source *newSource(Decoder *decoder);
		//Source *newSource(SoundData *soundData);
		//Source *newSource(int sampleRate, int bitDepth, int channels, int buffers);

		/**
		 * Gets the current number of simultaneous playing sources.
		 * @return The current number of simultaneous playing sources.
		 **/
		int getActiveSourceCount() const;

		/**
		 * Gets the maximum supported number of simultaneous playing sources.
		 * @return The maximum supported number of simultaneous playing sources.
		 **/
		int getMaxSources() const;

		/**
		 * Play the specified Source.
		 * @param source The Source to play.
		 **/
		//bool play(Source *source);

		/**
		 * Play the specified Sources.
		 * @param sources The Sources to play.
		 **/
		bool play(const std::vector<Source*> &sources);

		/**
		 * Stops playback on the specified source.
		 * @param source The source on which to stop the playback.
		 **/
		//void stop(Source *source);

		/**
		 * Stops playback on the specified sources.
		 * @param sources The sources on which to stop the playback.
		 **/
		void stop(const std::vector<Source*> &sources);

		/**
		 * Stops all playing audio.
		 **/
		void stop();

		/**
		 * Pauses playback on the specified source.
		 * @param source The source on which to pause the playback.
		 **/
		//void pause(Source *source);

		/**
		 * Pauses playback on the specified sources.
		 * @param sources The sources on which to pause the playback.
		 **/
		void pause(const std::vector<Source*> &sources);

		/**
		 * Pauses all audio.
		 **/
		std::vector<Source*> pause();

		/**
		 * Sets the master volume, where 0.0f is min (off) and 1.0f is max.
		 * @param volume The new master volume.
		 **/
		void setVolume(float volume);

		/**
		 * Gets the master volume.
		 * @return The current master volume.
		 **/
		float getVolume() const;

		/**
		 * Gets the position of the listener.
		 **/
		cocos2d::Vec3 getPosition() const;

		/**
		 * Sets the position of the listener.
		 **/
		void setPosition(const cocos2d::Vec3& v);

		/**
		 * Gets the orientation of the listener.
		 * @return A vector array of size 2 containing the forward
		 * vector and the up vector.
		 **/
		std::array<cocos2d::Vec3, 2> getOrientation() const;

		/**
		 * Sets the orientation of the listener.
		 * @param forward the forward vector
		 * @param up the up vector.
		 **/
		void setOrientation(const cocos2d::Vec3& forward, const cocos2d::Vec3& up);

		/**
		 * Gets the velocity of the listener.
		 **/
		cocos2d::Vec3 getVelocity() const;

		/**
		 * Sets the velocity of the listener.
		 **/
		void setVelocity(const cocos2d::Vec3& v);

		void setDopplerScale(float scale);

		float getDopplerScale() const;

		//void setMeter(float scale);

		//float getMeter() const;

		/**
		 * @return Reference to a vector of pointers to recording devices. May be empty.
		 **/
		std::vector<RecordingDevice*> getRecordingDevices();

		/**
		 * Gets the distance model used for attenuation.
		 * @return Distance model.
		 */
		DistanceModel getDistanceModel() const;

		/**
		 * Sets the distance model used for attenuation.
		 * @param distanceModel Distance model.
		 */
		void setDistanceModel(DistanceModel distanceModel);

		/**
		 * Sets scene EFX effect.
		 * @param name Effect name to use.
		 * @param params Effect description table.
		 * @return true if successful, false otherwise.
		 */
		bool setEffect(const std::string& name, const Effect::ParamMap& params);

		/**
		 * Removes scene EFX effect.
		 * @param name Effect name to clear.
		 * @return true if successful, false otherwise.
		 */
		bool unsetEffect(const std::string& name);

		/**
		 * Gets scene EFX effect.
		 * @param name Effect name to get data from.
		 * @return Effect description table.
		 */
		Effect::ParamMap getEffect(const std::string& name);

		/**
		 * Gets list of EFX effect names.
		 * @return List of EFX names to fill.
		 */
		std::vector<std::string> getActiveEffects() const;

		/**
		 * Gets maximum number of scene EFX effects.
		 * @return number of effects.
		 */
		int getMaxSceneEffects() const;

		/**
		 * Gets maximum number of source EFX effects.
		 * @return number of effects.
		 */
		int getMaxSourceEffects() const;

		/**
		 * Gets EFX (or analog) availability.
		 * @return true if supported.
		 */
		bool isEFXsupported() const;

		/**
		 * Sets whether audio from other apps mixes with love.audio or is muted,
		 * on supported platforms.
		 **/
		//bool setMixWithSystem(bool mix);

		bool getEffectID(const std::string& name, ALuint &id);

		void onEnterBackground();
		void onEnterForeground();

		std::string getLastError() const { return lastError; }
		bool isValid() const { return valid; }

	private:

		bool init();
		void finish();

		void initializeEFX();

		bool valid = false;
		// The OpenAL device.
		ALCdevice *device;

		// The OpenAL capture devices.
		cocos2d::Vector<RecordingDevice*> capture;

		// The OpenAL context.
		ALCcontext *context;

		// The OpenAL effects
		struct EffectMapStorage
		{
			Effect *effect;
			ALuint slot;
		};
		std::map<std::string, struct EffectMapStorage> effectmap;
		std::stack<ALuint> slotlist;
		int MAX_SCENE_EFFECTS = 64;
		int MAX_SOURCE_EFFECTS = 64;

		// The Pool.
		Pool *pool;

		cocos2d::Vector<Source*> tempSources;

		DistanceModel distanceModel;
		//float metersPerUnit = 1.0;

		std::string lastError;
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
