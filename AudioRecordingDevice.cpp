#include "AudioRecordingDevice.h"
#include "AudioEngine.h"
#include "AudioSoundData.h"

using namespace audio;

RecordingDevice::RecordingDevice(const char *name)
	: name(name)
{
}

RecordingDevice::~RecordingDevice()
{
	RecordingDevice::stop();
}

bool RecordingDevice::start(int samples, int sampleRate, int bitDepth, int channels)
{
	ALenum format = Engine::getFormat(bitDepth, channels);
	if (format == AL_NONE)
	{
#include "cocos2d.h"
		lastError = string_format("Recording %d channels with %d bits per sample is not supported.", channels, bitDepth);
		return false;
	}

	if (samples <= 0)
	{
		lastError = "Invalid number of samples.";
		return false;
	}

	if (sampleRate <= 0)
	{
		lastError = "Invalid sample rate.";
		return false;
	}

	if (isRecording())
		stop();

	device = alcCaptureOpenDevice(name.c_str(), sampleRate, format, samples);
	if (device == nullptr)
		return false;

	alcCaptureStart(device);

	this->samples = samples;
	this->sampleRate = sampleRate;
	this->bitDepth = bitDepth;
	this->channels = channels;

	return true;
}

void RecordingDevice::stop()
{
	if (!isRecording())
		return;

	alcCaptureStop(device);
	alcCaptureCloseDevice(device);
	device = nullptr;
}

SoundData *RecordingDevice::getData()
{
	if (!isRecording())
		return nullptr;

	int samples = getSampleCount();
	if (samples == 0)
		return nullptr;

	SoundData *soundData = new SoundData(samples, sampleRate, bitDepth, channels);

	alcCaptureSamples(device, soundData->getData(), samples);

	return soundData;
}

int RecordingDevice::getSampleCount() const
{
	if (!isRecording())
		return 0;

	ALCint samples;
	alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, sizeof(ALCint), &samples);
	return (int)samples;
}

int RecordingDevice::getMaxSamples() const
{
	return samples;
}

int RecordingDevice::getSampleRate() const
{
	return sampleRate;
}

int RecordingDevice::getBitDepth() const
{
	return bitDepth;
}

int RecordingDevice::getChannelCount() const
{
	return channels;
}

std::string RecordingDevice::getName() const
{
	return name;
}

bool RecordingDevice::isRecording() const
{
	return device != nullptr;
}

