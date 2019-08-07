#pragma once
#include "base/CCRef.h"
#include <cstdint>
#include <string>

namespace audio
{
	class SoundData;

	class Stream : public cocos2d::Ref
	{
	public:
		enum class SeekOrigin
		{
			/** Seek from the beginning. */
			BEGINNING = 0,
			/** Seek from current position. */
			CURRENT = 1,
			/** Seek from the end. */
			END = 2
		};

		virtual uint64_t size() = 0;
		virtual uint64_t tell() = 0;
		virtual bool seek(SeekOrigin origin, int64_t offset) = 0;
		virtual bool read(uint8_t* dst, uint64_t length, uint64_t* bytesRead = nullptr) = 0;

		virtual void lock() = 0;
		virtual void unlock() = 0;

		virtual ~Stream() = default;

		static Stream* createFromFile(const std::string& path);
		static Stream* createFromLocalFile(const std::string& path);
		static Stream* createFromStringData(const std::string& str);
		static Stream* createFromSoundData(SoundData* soundData);
	};
}
