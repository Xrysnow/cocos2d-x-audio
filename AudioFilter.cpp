#include "AudioFilter.h"
#include "AudioEngine.h"

using namespace audio;

Filter::Filter()
{
	type = Type::BASIC;
	generateFilter();
}

Filter::Filter(const Filter &s)
	: Filter()
{
	Filter::setParams(s.getParams());
}

Filter::~Filter()
{
	deleteFilter();
}

Filter::Type Filter::getType() const
{
	return type;
}

Filter *Filter::clone()
{
	return new Filter(*this);
}

bool Filter::generateFilter()
{
#ifdef ALC_EXT_EFX
	if (!alGenFilters)
		return false;

	if (filter != AL_FILTER_NULL)
		return true;

	alGenFilters(1, &filter);
	if (alGetError() != AL_NO_ERROR)
	{
		//throw love::Exception("Failed to create sound Filter.");
		return false;
	}

	return true;
#else
	return false;
#endif
}

void Filter::deleteFilter()
{
#ifdef ALC_EXT_EFX
	if (filter != AL_FILTER_NULL)
		alDeleteFilters(1, &filter);
#endif
	filter = AL_FILTER_NULL;
}

ALuint Filter::getFilter() const
{
	return filter;
}

bool Filter::setParams(const ParamMap& params_)
{
	params = params_;
	if (params.find(Parameter::TYPE) == params.end())
		return false;
	type = (Type)(int)params[Parameter::TYPE];

	if (!generateFilter())
		return false;

#ifdef ALC_EXT_EFX
	switch (type)
	{
	case Type::LOWPASS:
		alFilteri(filter, AL_FILTER_TYPE, AL_FILTER_LOWPASS);
		break;
	case Type::HIGHPASS:
		alFilteri(filter, AL_FILTER_TYPE, AL_FILTER_HIGHPASS);
		break;
	case Type::BANDPASS:
		alFilteri(filter, AL_FILTER_TYPE, AL_FILTER_BANDPASS);
		break;
	case Type::BASIC:
	case Type::MAX_ENUM:
		break;
	}

	//failed to make filter specific type - not supported etc.
	if (alGetError() != AL_NO_ERROR)
	{
		deleteFilter();
		return false;
	}

#define clampf(v,l,h) fmax(fmin((v),(h)),(l))
#define PARAMSTR(i,e,v) filter,AL_##e##_##v,clampf(getValue(Parameter::i,AL_##e##_DEFAULT_##v),AL_##e##_MIN_##v,AL_##e##_MAX_##v)
	switch (type)
	{
	case Type::LOWPASS:
		alFilterf(PARAMSTR(VOLUME, LOWPASS, GAIN));
		alFilterf(PARAMSTR(HIGHGAIN, LOWPASS, GAINHF));
		break;
	case Type::HIGHPASS:
		alFilterf(PARAMSTR(VOLUME, HIGHPASS, GAIN));
		alFilterf(PARAMSTR(LOWGAIN, HIGHPASS, GAINLF));
		break;
	case Type::BANDPASS:
		alFilterf(PARAMSTR(VOLUME, BANDPASS, GAIN));
		alFilterf(PARAMSTR(LOWGAIN, BANDPASS, GAINLF));
		alFilterf(PARAMSTR(HIGHGAIN, BANDPASS, GAINHF));
		break;
	case Type::BASIC:
	case Type::MAX_ENUM:
		break;
	}
#undef clampf
#undef PARAMSTR
	//alGetError();

	return true;
#else
	return false;
#endif
}

const Filter::ParamMap& Filter::getParams() const
{
	return params;
}

float Filter::getValue(Parameter in, float def) const
{
	return params.find(in) == params.end() ? def : params.at(in);
}

int Filter::getValue(Parameter in, int def) const
{
	return params.find(in) == params.end() ? def : static_cast<int>(params.at(in));
}
