#pragma once
#include <cstdint>
#include <string>

namespace audio
{
	class Decoder;

	class SoundData
	{
	public:

		//SoundData(Decoder *decoder);
		SoundData(int samples, int sampleRate, int bitDepth, int channels);
		SoundData(void *d, int samples, int sampleRate, int bitDepth, int channels);
		SoundData(const SoundData &c);

		virtual ~SoundData();

		SoundData* clone() const;
		void* getData() const;
		/**
		 * \brief Gets the Data's size in bytes.
		 * \return The size of the Data in bytes.
		 */
		size_t getSize() const;

		virtual int getChannelCount() const;
		virtual int getBitDepth() const;
		virtual int getSampleRate() const;
		virtual int getSampleCount() const;

		/**
		 * \brief Gets the duration of the sound data.
		 * \return The duration of the sound data in seconds.
		 */
		virtual double getDuration() const;

		/**
		 * \brief Sets the value of the sample-point at the specified position.
		 *  For stereo SoundData objects, the data from the left and right channels are interleaved in that order.
		 * \param i An integer value specifying the position of the sample (starting at 0).
		 * \param sample The normalized samplepoint (range -1.0 to 1.0).
		 */
		void setSample(int i, float sample);
		/**
		 * \brief Sets the value of a sample using an explicit sample index instead of interleaving them in the sample position parameter.
		 * \param i An integer value specifying the position of the sample (starting at 0).
		 * \param channel The index of the channel to set within the given sample.
		 * \param sample The normalized samplepoint (range -1.0 to 1.0).
		 */
		void setSample(int i, int channel, float sample);
		/**
		 * \brief Gets the value of the sample-point at the specified position.
		 *  For stereo SoundData objects, the data from the left and right channels are interleaved in that order.
		 * \param i An integer value specifying the position of the sample (starting at 0).
		 * \return The normalized samplepoint (range -1.0 to 1.0).
		 */
		float getSample(int i);
		/**
		 * \brief Gets the value of a sample using an explicit sample index instead of interleaving them in the sample position parameter.
		 * \param i An integer value specifying the position of the sample (starting at 0).
		 * \param channel The index of the channel to get within the given sample.
		 * \return The normalized samplepoint (range -1.0 to 1.0).
		 */
		float getSample(int i, int channel);

		std::string getLastError() const { return lastError; }
	private:

		void load(int samples, int sampleRate, int bitDepth, int channels, void *newData = 0);

		uint8_t* data;
		size_t size;

		int sampleRate;
		int bitDepth;
		int channels;

		std::string lastError;
	};	
}
