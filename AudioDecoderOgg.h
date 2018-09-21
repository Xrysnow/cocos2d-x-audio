/****************************************************************************
 Copyright (c) 2016-2017 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#pragma once

#include "AudioDecoder.h"

#include "../../external/OggDecoder/include/vorbis/vorbisfile.h"

namespace xAudio {

	class AudioDecoderOgg : public AudioDecoder
	{
	public:
		bool open(const char* path) override;
		bool open(fcyStream* stream, double loopA = 0, double loopB = -1) override;
		void close() override;
		uint32_t read(uint32_t framesToRead, char* pcmBuf) override;
		bool seek(uint32_t frameOffset) override;
		uint32_t tell() const override;

	private:
		static size_t streamReadFunc(void *ptr, size_t size, size_t nmemb, void *datasource);
		static int streamSeekFunc(void *datasource, ogg_int64_t offset, int whence);
		static int streamCloseFunc(void *datasource);
		static long streamTellFunc(void *datasource);
	protected:
		AudioDecoderOgg();
		~AudioDecoderOgg();

		OggVorbis_File _vf;
		vorbis_info* vInfo = nullptr;
		int currentSec = 0;

		friend class AudioDecoderManager;
	};

}
