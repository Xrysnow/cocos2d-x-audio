#include "AudioDecoder.h"
#include "AudioMacros.h"
#include "platform/CCFileUtils.h"

#define LOG_TAG "AudioDecoder"
using namespace xAudio;
//using namespace cocos2d::experimental;

AudioDecoder::AudioDecoder()
{

}

AudioDecoder::~AudioDecoder()
{
}


bool AudioDecoder::open(AudioStream* src, double loopA, double loopB)
{
	return false;
}

bool AudioDecoder::isOpened() const
{
	return _isOpened;
}

uint32_t AudioDecoder::read_loop(uint32_t framesToRead, char* pcmBuf)
{
	uint32_t ret = 0;
	if (_isABLoop && !in_read_loop)
	{
		in_read_loop = true;
		// 需要读取的采样个数
		auto tSampleToRead = framesToRead;

		auto pBuffer = pcmBuf;
		auto last_loopB = loopB;
		uint32_t real_read = 0;

		// 填充音频数据
		while (tSampleToRead)
		{
			// 获得当前解码器位置(采样)
			auto tCurSample = tell();

			// 检查读取位置是否超出循环节
			if (tCurSample + tSampleToRead > loopB)
			{
				// 填充尚未填充数据
				if (tCurSample < loopB)
				{
					auto tVaildSample = loopB - tCurSample;
					auto tVaildSize = tVaildSample * sourceInfo.bytesPerFrame;

					ret = read(tVaildSample, pBuffer);
					real_read += ret;
					if (ret == 0)
						return real_read;
					// 指针后移
					pBuffer += tVaildSize;
					// 减少采样
					tSampleToRead -= tVaildSample;
				}
				// 跳到循环头
				seek(loopA);
			}
			else
			{
				// 直接填充数据
				ret = read(tSampleToRead, pBuffer);
				real_read += ret;
				break;
			}
		}
		//ret = framesToRead * sourceInfo.bytesPerFrame;
		ret = real_read;
		in_read_loop = false;
	}
	return ret;
}

uint32_t AudioDecoder::readFixedFrames(uint32_t framesToRead, char* pcmBuf)
{
	uint32_t framesRead = 0;
	uint32_t framesReadOnce = 0;
	do
	{
		framesReadOnce = read(framesToRead - framesRead, pcmBuf + framesRead * sourceInfo.bytesPerFrame);
		framesRead += framesReadOnce;
	} while (framesReadOnce != 0 && framesRead < framesToRead);

	if (framesRead < framesToRead)
	{
		ALOGV("[AudioDecoder::readFixedFrames] Not enough frames, fill %d more with 0.", framesToRead - framesRead);
		memset(pcmBuf + framesRead * sourceInfo.bytesPerFrame, 0x00, (framesToRead - framesRead) * sourceInfo.bytesPerFrame);
	}

	return framesRead;
}

uint32_t AudioDecoder::getTotalFrames() const
{
	return sourceInfo.totalFrames;
}

uint32_t AudioDecoder::getBytesPerFrame() const
{
	return sourceInfo.bytesPerFrame;
}

uint32_t AudioDecoder::getSampleRate() const
{
	return sourceInfo.sampleRate;
}

uint32_t AudioDecoder::getChannelCount() const
{
	return sourceInfo.channelCount;
}

uint32_t AudioDecoder::fixLength(std::vector<uint8_t>* buffer)
{
	auto last_loop = in_read_loop;
	in_read_loop = true;
	seek(sourceInfo.totalFrames);
	auto step = sourceInfo.totalFrames;
	auto bytesPerFrame = sourceInfo.bytesPerFrame;
	if(buffer){
		buffer->clear();
		buffer->reserve(step*bytesPerFrame);
	}
	auto buf = (char*)malloc(step*bytesPerFrame);
	uint32_t ret;
	do
	{
		ret = read(step, buf);
		sourceInfo.totalFrames += ret;
		if (buffer)
			buffer->insert(buffer->end(), buf, buf + ret*bytesPerFrame);
	} while (ret > 0);
	free(buf);
	in_read_loop = last_loop;
	if (step < sourceInfo.totalFrames)
	{
		ALOGV("[AudioDecoder::fixLength] Total frames: %u => %u",
			step, sourceInfo.totalFrames);
	}
	CC_ASSERT((sourceInfo.totalFrames - step)*bytesPerFrame == buffer->size());
	return sourceInfo.totalFrames - step;
}

bool AudioDecoder::writeToFile(const std::string& filePath)
{
	if (!_isOpened)
		return false;
	auto buf_size = getTotalFrames()*getBytesPerFrame();
	CC_ASSERT(buf_size > 0);
	auto buf = (char*)malloc(buf_size);
	seek(0);
	readFixedFrames(getTotalFrames(), buf);
	seek(0);
	cocos2d::Data d;
	d.fastSet((uint8_t*)buf, buf_size);
	return cocos2d::FileUtils::getInstance()->writeDataToFile(d, filePath);
}

void AudioDecoder::calcLoopAB(double tA, double tB)
{
	if (tA >= 0.0 && tB > 0.0 && tA < tB)
	{
		_isABLoop = true;
		loopA = std::min(uint32_t(sourceInfo.sampleRate*tA), sourceInfo.totalFrames);
		loopB = std::min(uint32_t(sourceInfo.sampleRate*tB), sourceInfo.totalFrames);
		if (loopA == loopB)
		{
			loopA = loopB = 0;
			_isABLoop = false;
		}
	}
	else
		_isABLoop = false;
}

