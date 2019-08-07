#include "AudioSoundData.h"
#include "AudioDecoder.h"
#include "AudioEngine.h"

#include <cstdlib>
#include <cstring>
#include <limits>
#include <iostream>
#include <vector>

using namespace audio;

#define Exception(STR, ...) lastError = string_format(STR, ##__VA_ARGS__); return

/*
SoundData::SoundData(Decoder *decoder)
	: data(0)
	, size(0)
	, sampleRate(Decoder::DEFAULT_SAMPLE_RATE)
	, bitDepth(0)
	, channels(0)
{
	if (decoder->getBitDepth() != 8 && decoder->getBitDepth() != 16)
	{
		Exception("Invalid bit depth: %d", decoder->getBitDepth());
	}

	size_t bufferSize = 524288; // 0x80000
	int decoded = decoder->decode();

	while (decoded > 0)
	{
		// Expand or allocate buffer. Note that realloc may move
		// memory to other locations.
		if (!data || bufferSize < size + decoded)
		{
			while (bufferSize < size + decoded)
				bufferSize <<= 1;
			data = (uint8_t *)realloc(data, bufferSize);
		}

		if (!data)
		{
			Exception("Not enough memory.");
		}

		// Copy memory into new part of memory.
		memcpy(data + size, decoder->getBuffer(), decoded);

		// Overflow check.
		if (size > std::numeric_limits<size_t>::max() - decoded)
		{
			free(data);
			Exception("Not enough memory.");
		}

		// Keep this up to date.
		size += decoded;

		decoded = decoder->decode();
	}

	// Shrink buffer if necessary.
	if (data && bufferSize > size)
		data = (uint8_t *)realloc(data, size);

	channels = decoder->getChannelCount();
	bitDepth = decoder->getBitDepth();
	sampleRate = decoder->getSampleRate();
}
*/

SoundData::SoundData(int samples, int sampleRate, int bitDepth, int channels)
	: data(0)
	, size(0)
	, sampleRate(0)
	, bitDepth(0)
	, channels(0)
{
	load(samples, sampleRate, bitDepth, channels);
}

SoundData::SoundData(void *d, int samples, int sampleRate, int bitDepth, int channels)
	: data(0)
	, size(0)
	, sampleRate(0)
	, bitDepth(0)
	, channels(0)
{
	load(samples, sampleRate, bitDepth, channels, d);
}

SoundData::SoundData(const SoundData &c)
	: data(0)
	, size(0)
	, sampleRate(0)
	, bitDepth(0)
	, channels(0)
{
	load(c.getSampleCount(), c.getSampleRate(), c.getBitDepth(), c.getChannelCount(), c.getData());
}

SoundData::~SoundData()
{
	if (data)
		free(data);
}

SoundData *SoundData::clone() const
{
	return new SoundData(*this);
}

void SoundData::load(int samples, int sampleRate, int bitDepth, int channels, void *newData)
{
	if (samples <= 0)
	{
		Exception("Invalid sample count: %d", samples);
	}

	if (sampleRate <= 0)
	{
		Exception("Invalid sample rate: %d", sampleRate);
	}

	if (bitDepth != 8 && bitDepth != 16)
	{
		Exception("Invalid bit depth: %d", bitDepth);
	}

	if (channels <= 0)
	{
		Exception("Invalid channel count: %d", channels);
	}

	if (data)
	{
		free(data);
		data = nullptr;
	}

	size = samples * (bitDepth / 8) * channels;
	this->sampleRate = sampleRate;
	this->bitDepth = bitDepth;
	this->channels = channels;

	double realsize = samples;
	realsize *= (bitDepth / 8) * channels;
	if (realsize > std::numeric_limits<size_t>::max())
	{
		Exception("Data is too big!");
	}

	data = (uint8_t*)malloc(size);
	if (!data)
	{
		Exception("Not enough memory.");
	}

	if (newData)
		memcpy(data, newData, size);
	else
		memset(data, bitDepth == 8 ? 128 : 0, size);
}

void *SoundData::getData() const
{
	return (void *)data;
}

size_t SoundData::getSize() const
{
	return size;
}

int SoundData::getChannelCount() const
{
	return channels;
}

int SoundData::getBitDepth() const
{
	return bitDepth;
}

int SoundData::getSampleRate() const
{
	return sampleRate;
}

int SoundData::getSampleCount() const
{
	return (int)((size / channels) / (bitDepth / 8));
}

double SoundData::getDuration() const
{
	return double(size) / (double(channels) * sampleRate * bitDepth / 8);
}

void SoundData::setSample(int i, float sample)
{
	// Check range.
	if (i < 0 || (size_t)i >= size / (bitDepth / 8))
	{
		Exception("Attempt to set out-of-range sample!");
	}

	if (bitDepth == 16)
	{
		// 16-bit sample values are signed.
		int16_t *s = (int16_t *)data;
		s[i] = (int16_t)(sample * (float)INT16_MAX);
	}
	else
	{
		// 8-bit sample values are unsigned internally.
		data[i] = (uint8_t)((sample * 127.0f) + 128.0f);
	}
}

void SoundData::setSample(int i, int channel, float sample)
{
	if (channel < 1 || channel > channels)
	{
		Exception("Attempt to set sample from out-of-range channel!");
	}

	return setSample(i * channels + (channel - 1), sample);
}

float SoundData::getSample(int i)
{
	// Check range.
	if (i < 0 || (size_t)i >= size / (bitDepth / 8))
	{
		lastError = string_format("Attempt to get out-of-range sample!");
		return 0;
	}

	if (bitDepth == 16)
	{
		// 16-bit sample values are signed.
		int16_t *s = (int16_t *)data;
		return (float)s[i] / (float)INT16_MAX;
	}
	else
	{
		// 8-bit sample values are unsigned internally.
		return ((float)data[i] - 128.0f) / 127.0f;
	}
}

float SoundData::getSample(int i, int channel)
{
	if (channel < 1 || channel > channels)
	{
		lastError = string_format("Attempt to get sample from out-of-range channel!");
		return 0;
	}

	return getSample(i * channels + (channel - 1));
}
