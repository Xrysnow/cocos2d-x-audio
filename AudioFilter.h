#pragma once
#include "AudioMacros.h"
#include "ALHeader.h"
#include <string>
#include <vector>
#include <map>

#ifndef AL_FILTER_NULL
#define AL_FILTER_NULL (0)
#endif

namespace audio
{
	class Filter
	{
	public:
		enum class Type
		{
			BASIC,
			LOWPASS,
			HIGHPASS,
			BANDPASS,
			MAX_ENUM
		};

		enum class Parameter
		{
			TYPE,
			VOLUME,

			LOWGAIN,  // HIGHPASS, BANDPASS
			HIGHGAIN, // LOWPASS, BANDPASS

			MAX_ENUM
		};

		using ParamMap = std::map<Parameter, float>;

		Filter();
		Filter(const Filter &s);
		virtual ~Filter();
		Type getType() const;

		virtual Filter* clone();
		ALuint getFilter() const;
		virtual bool setParams(const ParamMap& params);
		virtual const ParamMap& getParams() const;

	protected:
		Type type;
		bool generateFilter();
		void deleteFilter();
		float getValue(Parameter in, float def) const;
		int getValue(Parameter in, int def) const;
		ALuint filter = AL_FILTER_NULL;
		ParamMap params;
	};	
}
