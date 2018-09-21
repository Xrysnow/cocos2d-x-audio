#pragma once
#include "math/Vec3.h"

namespace xAudio
{
	struct SourceParam
	{
		cocos2d::Vec3 position;
		cocos2d::Vec3 velocity;
		float volume = 1.f;
		float pitch = 1.f;
		bool loop = false;
		bool operator==(const SourceParam& other) const
		{
			return volume == other.volume&&pitch == other.pitch&&loop == other.loop&&
				position == other.position&&velocity == other.velocity;
		}
		bool operator!=(const SourceParam& other) const
		{
			return !(*this == other);
		}
		static const SourceParam DEFAULT;
	};

	struct SourceInfo
	{
		uint32_t totalFrames;
		uint32_t bytesPerFrame;
		uint32_t sampleRate;
		uint32_t channelCount;
		bool operator==(const SourceInfo& other) const
		{
			return totalFrames == other.totalFrames&&bytesPerFrame == other.bytesPerFrame&&
				sampleRate == other.sampleRate&&channelCount == other.channelCount;
		}
		bool operator!=(const SourceInfo& other) const
		{
			return !(*this == other);
		}
	};
	struct ListenerParam
	{
		cocos2d::Vec3 position;
		cocos2d::Vec3 velocity;
		cocos2d::Vec3 ori_at{ 0.f,0.f,-1.f };
		cocos2d::Vec3 ori_up{ 0.f,1.f,0.f };
		bool operator==(const ListenerParam& other) const
		{
			return position == other.position&&velocity == other.velocity&&
				ori_at == other.ori_at&&ori_up == other.ori_up;
		}
		bool operator!=(const ListenerParam& other) const
		{
			return !(*this == other);
		}
		static const ListenerParam DEFAULT;
	};
}
