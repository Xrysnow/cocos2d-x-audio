#pragma once

#include <stdint.h>
#include "platform/CCPlatformDefine.h"
#include "../fcyLib/fcyStream.h"
#include "AudioParam.h"

namespace xAudio {

/**
 * @brief The class for decoding compressed audio file to PCM buffer.
 */
class AudioDecoder
{
public:
    static const uint32_t INVALID_FRAME_INDEX = UINT32_MAX;

    /**
     * @brief Opens an audio file specified by a file path.
     * @return true if succeed, otherwise false.
     */
    virtual bool open(const char* path) = 0;

	virtual bool open(fcyStream* stream, double loopA = 0, double loopB = -1);

    /**
     * @brief Checks whether decoder has opened file successfully.
     * @return true if succeed, otherwise false.
     */
    virtual bool isOpened() const;

    /**
     * @brief Closes opened audio file.
     * @note The method will also be automatically invoked in the destructor.
     */
    virtual void close() = 0;

    /**
     * @brief Reads audio frames of PCM format.
     * @param framesToRead The number of frames excepted to be read.
     * @param pcmBuf The buffer to hold the frames to be read, its size should be >= |framesToRead| * _bytesPerFrame.
     * @return The number of frames actually read, it's probably less than 'framesToRead'. Returns 0 means reach the end of file.
     */
    virtual uint32_t read(uint32_t framesToRead, char* pcmBuf) = 0;

    virtual uint32_t read_loop(uint32_t framesToRead, char* pcmBuf);

    /**
     * @brief Reads fixed audio frames of PCM format.
     * @param framesToRead The number of frames excepted to be read.
     * @param pcmBuf The buffer to hold the frames to be read, its size should be >= |framesToRead| * _bytesPerFrame.
     * @return The number of frames actually read, it's probably less than |framesToRead|. Returns 0 means reach the end of file.
     * @note The different between |read| and |readFixedFrames| is |readFixedFrames| will do multiple reading operations if |framesToRead| frames
     *       isn't filled entirely, while |read| just does reading operation once whatever |framesToRead| is or isn't filled entirely.
     *       If current position reaches the end of frames, the return value may smaller than |framesToRead| and the remaining
     *       buffer in |pcmBuf| will be set with silence data (0x00).
     */
    virtual uint32_t readFixedFrames(uint32_t framesToRead, char* pcmBuf);

    /**
     * @brief Sets frame offest to be read.
     * @param frameOffset The frame offest to be set.
     * @return true if succeed, otherwise false
     */
    virtual bool seek(uint32_t frameOffset) = 0;

    /**
     * @brief Tells the current frame offset.
     * @return The current frame offset.
     */
    virtual uint32_t tell() const = 0;

    /** Gets total frames of current audio.*/
    virtual uint32_t getTotalFrames() const;

    /** Gets bytes per frame of current audio.*/
    virtual uint32_t getBytesPerFrame() const;

    /** Gets sample rate of current audio.*/
    virtual uint32_t getSampleRate() const;

    /** Gets the channel count of current audio.
     * @note Currently we only support 1 or 2 channels.
     */
    virtual uint32_t getChannelCount() const;

	// Adjust total frames by setting position to the end of frames and try to read more data.
	// This is a workaround for https://github.com/cocos2d/cocos2d-x/issues/16938
	virtual uint32_t fixLength(std::vector<uint8_t>* buffer = nullptr);

	virtual bool writeToFile(const std::string& filePath);

	const SourceInfo& getSourceInfo() const { return sourceInfo; }

	bool isABLoop() const { return _isABLoop; }
protected:

    AudioDecoder();
    virtual ~AudioDecoder();
	void calcLoopAB(double tA, double tB);

	bool _isOpened = false;
    bool _isABLoop = false;
	SourceInfo sourceInfo;

	fcyStream* stream = nullptr;
	uint32_t loopA = 0;
	uint32_t loopB = 0;

	bool in_read_loop = false;

    friend class AudioDecoderManager;
    friend class AudioCache;
};

}
