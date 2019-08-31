#pragma once
#include "AudioPool.h"
#include "AudioFilter.h"
#include "AudioEffect.h"
#include "AudioMacros.h"
#include "ALHeader.h"
#include "base/CCRef.h"
#include <array>
#include <limits>

namespace audio
{

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	// OpenAL on iOS barfs if the max distance is +inf.
	static const float MAX_ATTENUATION_DISTANCE = 1000000.0f;
#else
	static const float MAX_ATTENUATION_DISTANCE = std::numeric_limits<float>::max();
#endif

	class Engine;
	class Pool;
	class SoundData;
	class Decoder;

	// Basically just a reference-counted non-streaming OpenAL buffer object.
	class StaticDataBuffer : public cocos2d::Ref
	{
	public:
		StaticDataBuffer(ALenum format, const ALvoid *data, ALsizei size, ALsizei freq);
		virtual ~StaticDataBuffer();
		ALuint getBuffer() const {
			return buffer;
		}
		ALsizei getSize() const {
			return size;
		}
	private:
		ALuint buffer;
		ALsizei size;
	};

	class Source : public cocos2d::Ref
	{
		friend class Pool;
	public:

		enum class Type
		{
			STATIC, // play from SoundData
			STREAM, // play from Decoder
			QUEUE,  // play with queue
			MAX_ENUM
		};

	private:

		Source();
		bool initWithSoundData(SoundData *soundData);
		bool initWithDecoder(Decoder *decoder);
		bool init(int sampleRate, int bitDepth, int channels, int buffers);
		bool initWithOther(const Source &s);

	public:

		virtual ~Source();

		static Source* createFromSoundData(SoundData *soundData);
		static Source* createFromDecoder(Decoder *decoder);
		static Source* create(int sampleRate, int bitDepth, int channels, int buffers);

		virtual Source* clone();
		virtual bool play();
		virtual void stop();
		virtual void pause();
		virtual bool isPlaying() const;
		virtual bool isFinished() const;
		// run in a seperate thread
		virtual bool update();
		virtual void setPitch(float value);
		virtual float getPitch() const;
		virtual void setVolume(float value);
		virtual float getVolume() const;
		virtual void seek(int64_t offset);
		virtual int64_t tell();
		virtual void setTime(double seconds);
		virtual double getTime();
		virtual double getTotalTime();
		virtual int64_t getTotalFrames();
		virtual void setPosition(const cocos2d::Vec3& v);
		virtual cocos2d::Vec3 getPosition();
		virtual void setVelocity(const cocos2d::Vec3& v);
		virtual cocos2d::Vec3 getVelocity();
		virtual void setDirection(const cocos2d::Vec3& v);
		virtual cocos2d::Vec3 getDirection();
		virtual void setCone(float innerAngle, float outerAngle, float outerVolume, float outerHighGain);
		virtual void setCone(const std::array<float, 4>& param);
		virtual std::array<float, 4> getCone(); // innerAngle, outerAngle, outerVolume, outerHighGain
		virtual void setRelative(bool enable);
		virtual bool isRelative();
		void setLooping(bool enable);
		bool isLooping() const;
		void setLoopingPoint(double tStart, double tEnd);
		bool isSupportLoopingPoint() const;
		double getLoopingStart() const;
		double getLoopingEnd() const;
		virtual void setMinVolume(float value);
		virtual float getMinVolume() const;
		virtual void setMaxVolume(float value);
		virtual float getMaxVolume() const;
		virtual void setReferenceDistance(float value);
		virtual float getReferenceDistance();
		virtual void setRolloffFactor(float value);
		virtual float getRolloffFactor();
		virtual void setMaxDistance(float value);
		virtual float getMaxDistance();
		virtual void setAirAbsorptionFactor(float value);
		virtual float getAirAbsorptionFactor();

		virtual int getChannelCount() const { return channels; }
		virtual int getSampleRate() const { return sampleRate; }
		virtual int getBitDepth() const { return bitDepth; }
		virtual int getBytesPerFrame() const { return channels * bitDepth / 8; }

		/**
		 * \brief Sets a low-pass, high-pass, or band-pass filter to apply when playing the Source.
		 * \param params The filter settings to use for this Source.
		 * \return Whether the filter was successfully applied to the Source.
		 * 
		 * \note Audio filter functionality is not supported on iOS.
		 *  While the cutoff frequency cannot be set directly, changing high/lowgain has the effect of altering the cutoff.
		 */
		virtual bool setFilter(const Filter::ParamMap& params);
		/**
		 * \brief Disables filtering on this Source.
		 */
		virtual bool removeFilter();
		/**
		 * \brief Gets the filter settings currently applied to the Source.
		 * \return The filter settings to use for this Source, or empty map if the Source has no active filter.
		 */
		virtual Filter::ParamMap getFilter();

		/**
		 * \brief Applies the given previously defined effect to this Source.
		 * \param name The name of the effect previously set up with Engine::setEffect.
		 * \return Whether the effect was successfully applied to this Source.
		 */
		virtual bool setEffect(const std::string& name);
		/**
		 * \brief Applies the given previously defined effect to this Source,
		 *  and applies a filter to the Source which affects the sound fed into the effect.
		 * \param name The name of the effect previously set up with Engine::setEffect.
		 * \param filterParams The filter settings to apply prior to the effect.
		 * \return Whether the effect and filter were successfully applied to this Source.
		 */
		virtual bool setEffect(const std::string& name, const Filter::ParamMap& filterParams);
		/**
		 * \brief Disables the effect.
		 * \param name The name of the effect previously set up with Engine::setEffect.
		 */
		virtual bool removeEffect(const std::string& name);
		/**
		 * \brief Gets the filter settings associated to a specific effect.
		 *  This function returns empty map if the effect was applied with no filter settings associated to it.
		 * \param name The name of the effect.
		 * \return The settings for the filter associated to this effect.
		 */
		virtual Filter::ParamMap getEffect(const std::string& name);
		/**
		 * \brief Gets a list of the Source's active effect names.
		 * \return A list of the source's active effect names.
		 */
		virtual std::vector<std::string> getActiveEffects() const;

		/**
		 * \brief Gets the number of free buffer slots in a queueable Source.
		 *  If the queueable Source is playing, this value will increase up to the amount the Source was created with.
		 *  If the queueable Source is stopped, it will process all of its internal buffers first, in which case this
		 *  function will always return the amount it was created with.
		 * \return How many more SoundData objects can be queued up.
		 */
		virtual int getFreeBufferCount() const;

		virtual bool queueData(void* data, size_t length, int dataSampleRate, int dataBitDepth, int dataChannels);

		/**
		 * \brief Queues SoundData for playback in a queueable Source.
		 * \param data The data to queue. The SoundData's sample rate, bit depth, and channel count must match the Source's.
		 * \param offset 
		 * \param length 
		 * \return True if the data was successfully queued for playback, false if there were no available buffers to use for queueing.
		 */
		virtual bool queue(SoundData* data, ssize_t offset = -1, ssize_t length = -1);

	protected:

		void prepareAtomic();
		void teardownAtomic();

		bool playAtomic(ALuint source);
		void stopAtomic();
		void pauseAtomic();
		void resumeAtomic();

	public:

		size_t copyBuffer(char* dst, size_t size, size_t offset);
		int64_t getBufferOffset();

		std::string getLastError() const { return lastError; }

		static bool playBatch(const std::vector<Source*>& sources);
		static void stopBatch(const std::vector<Source*>& sources);
		static void pauseBatch(const std::vector<Source*>& sources);

		static std::vector<Source*> pauseAll();
		static void stopAll();

	private:

		bool releaseSource(bool stop = true);

		void reset();

		int streamAtomic(ALuint buffer, Decoder *d);

		void InvalidFormatException(int channelCount, int bitDepth);
		void SpatialSupportException();
		void QueueLoopingException();
		void QueueTypeMismatchException();
		void QueueFormatMismatchException();
		void QueueMalformedLengthException(int bytesPerSample);

		Type sourceType;
		Pool* pool = nullptr;
		ALuint source = 0;
		bool valid = false;
		std::string lastError;

		const static int DEFAULT_BUFFERS = 8;
		const static int MAX_BUFFERS = 64;
		std::queue<ALuint> streamBuffers;
		std::stack<ALuint> unusedBuffers;

		StaticDataBuffer* staticBuffer = nullptr;

		float pitch = 1.0f;
		float volume = 1.0f;
		cocos2d::Vec3 position;
		cocos2d::Vec3 velocity;
		cocos2d::Vec3 direction;
		bool relative = false;
		bool looping = false;
		float minVolume = 0.0f;
		float maxVolume = 1.0f;
		float referenceDistance = 1.0f;
		float rolloffFactor = 1.0f;
		float absorptionFactor = 0.0f;
		float maxDistance = MAX_ATTENUATION_DISTANCE;

		struct Cone
		{
			int innerAngle = 360; // degrees
			int outerAngle = 360; // degrees
			float outerVolume = 0.0f;
			float outerHighGain = 1.0f;
		} cone;

		int64_t offsetSamples = 0;

		int sampleRate = 0;
		int channels = 0;
		int bitDepth = 0;

		Decoder* decoder = nullptr;

		uint64_t toLoop = 0;
		int64_t bufferedBytes = 0;
		int buffers = 0;

		Filter* directfilter = nullptr;

		struct EffectMapStorage
		{
			Filter* filter;
			ALuint slot, target;
		};
		std::map<std::string, EffectMapStorage> effectmap;
		std::stack<ALuint> slotlist;
	};	
}
