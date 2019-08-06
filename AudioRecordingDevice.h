#pragma once
#include "AudioMacros.h"
#include "AudioSoundData.h"
#include "base/CCRef.h"
#include "ALHeader.h"
#include <string>

namespace audio
{
	class RecordingDevice : public cocos2d::Ref
	{
	public:

		static const int DEFAULT_SAMPLES = 8192;
		static const int DEFAULT_SAMPLE_RATE = 8000;
		static const int DEFAULT_BIT_DEPTH = 16;
		static const int DEFAULT_CHANNELS = 1;

	protected:
		friend class Engine;
		RecordingDevice(const char *name);
	public:
		virtual ~RecordingDevice();

		/**
		 * Begins audio input recording process.
		 * @param samples Number of samples to buffer.
		 * @param sampleRate Desired sample rate.
		 * @param bitDepth Desired bit depth (8 or 16).
		 * @param channels Desired number of channels.
		 * @return True if recording started successfully.
		 **/
		virtual bool start(int samples, int sampleRate, int bitDepth, int channels);

		/**
		 * Stops audio input recording.
		 **/
		virtual void stop();

		/**
		 * Retreives recorded data.
		 * @return SoundData containing data obtained from recording device.
		 **/
		virtual SoundData* getData();

		/**
		 * @return device name.
		 **/
		virtual std::string getName() const;

		/**
		 * @return Number of samples currently recorded.
		 **/
		virtual int getSampleCount() const;

		/**
		 * Gets the maximum number of samples that will be buffered, as set by start().
		 **/
		virtual int getMaxSamples() const;

		/**
		 * @return Sample rate for recording.
		 **/
		virtual int getSampleRate() const;

		/**
		 * @return Bit depth for recording.
		 **/
		virtual int getBitDepth() const;

		/**
		 * @return Number of channels for recording.
		 **/
		virtual int getChannelCount() const;

		/**
		 * @return True if currently recording.
		 **/
		virtual bool isRecording() const;

	private:

		int samples = DEFAULT_SAMPLES;
		int sampleRate = DEFAULT_SAMPLE_RATE;
		int bitDepth = DEFAULT_BIT_DEPTH;
		int channels = DEFAULT_CHANNELS;

		std::string name;
		ALCdevice *device = nullptr;

		std::string lastError;
	};
}
