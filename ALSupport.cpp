#include "ALSupport.h"
#include <unordered_map>

using namespace std;
using namespace audio;

bool _isLoaded = false;
bool _has_ALC_ENUMERATE_ALL_EXT = true;
vector<string> DeviceNames;
string DefaultDeviceName;
vector<string> CaptureDeviceNames;
string DefaultCaptureDeviceName;

vector<string> PossibleBufferFormats = {
	"AL_FORMAT_MONO8",
	"AL_FORMAT_MONO16",
	"AL_FORMAT_STEREO8",
	"AL_FORMAT_STEREO16",
	// AL_LOKI_IMA_ADPCM_format
	"AL_FORMAT_IMA_ADPCM_MONO16_EXT",
	"AL_FORMAT_IMA_ADPCM_STEREO16_EXT",
	// AL_LOKI_WAVE_format
	"AL_FORMAT_WAVE_EXT",
	// AL_EXT_vorbis
	"AL_FORMAT_VORBIS_EXT",
	// AL_LOKI_quadriphonic
	"AL_FORMAT_QUAD8_LOKI",
	"AL_FORMAT_QUAD16_LOKI",
	// AL_EXT_float32
	"AL_FORMAT_MONO_FLOAT32",
	"AL_FORMAT_STEREO_FLOAT32",
	// AL_EXT_double
	"AL_FORMAT_MONO_DOUBLE_EXT",
	"AL_FORMAT_STEREO_DOUBLE_EXT",
	// AL_EXT_MULAW
	"AL_FORMAT_MONO_MULAW_EXT",
	"AL_FORMAT_STEREO_MULAW_EXT",
	// AL_EXT_ALAW
	"AL_FORMAT_MONO_ALAW_EXT",
	"AL_FORMAT_STEREO_ALAW_EXT",
	// AL_EXT_MCFORMATS
	"AL_FORMAT_QUAD8",
	"AL_FORMAT_QUAD16",
	"AL_FORMAT_QUAD32",
	"AL_FORMAT_REAR8",
	"AL_FORMAT_REAR16",
	"AL_FORMAT_REAR32",
	"AL_FORMAT_51CHN8",
	"AL_FORMAT_51CHN16",
	"AL_FORMAT_51CHN32",
	"AL_FORMAT_61CHN8",
	"AL_FORMAT_61CHN16",
	"AL_FORMAT_61CHN32",
	"AL_FORMAT_71CHN8",
	"AL_FORMAT_71CHN16",
	"AL_FORMAT_71CHN32",
	// AL_EXT_MULAW_MCFORMATS
	"AL_FORMAT_MONO_MULAW",
	"AL_FORMAT_STEREO_MULAW",
	"AL_FORMAT_QUAD_MULAW",
	"AL_FORMAT_REAR_MULAW",
	"AL_FORMAT_51CHN_MULAW",
	"AL_FORMAT_61CHN_MULAW",
	"AL_FORMAT_71CHN_MULAW",
	// AL_EXT_IMA4
	"AL_FORMAT_MONO_IMA4",
	"AL_FORMAT_STEREO_IMA4",
	// AL_SOFT_MSADPCM
	"AL_FORMAT_MONO_MSADPCM_SOFT",
	"AL_FORMAT_STEREO_MSADPCM_SOFT",
	// AL_EXT_BFORMAT
	"AL_FORMAT_BFORMAT2D_8",
	"AL_FORMAT_BFORMAT2D_16",
	"AL_FORMAT_BFORMAT2D_FLOAT32",
	"AL_FORMAT_BFORMAT3D_8",
	"AL_FORMAT_BFORMAT3D_16",
	"AL_FORMAT_BFORMAT3D_FLOAT32",
	// AL_EXT_MULAW_BFORMAT
	"AL_FORMAT_BFORMAT2D_MULAW",
	"AL_FORMAT_BFORMAT3D_MULAW",
};
unordered_map<string, ALenum> SupportedBufferFormats;

vector<string> PossibleALExtensions = {
	"AL_EXT_vorbis",
	"AL_EXT_float32",
	"AL_EXT_double",
	"AL_EXT_MULAW",
	"AL_EXT_ALAW",
	"AL_EXT_MCFORMATS",
	"AL_EXT_MULAW_MCFORMATS",
	"AL_EXT_IMA4",
	"AL_EXT_STATIC_BUFFER",
	"AL_EXT_source_distance_model",
	"AL_EXT_FOLDBACK",
	"AL_EXT_STEREO_ANGLES",
	"AL_EXT_SOURCE_RADIUS",
	"AL_EXT_BFORMAT",
	"AL_EXT_MULAW_BFORMAT",
};
unordered_map<string, bool> SupportedALExtensions;

vector<string> PossibleALCExtensions = {
	"ALC_EXT_EFX",
	"ALC_EXT_disconnect",
	"ALC_EXT_thread_local_context",
	"ALC_EXT_DEDICATED",
	"ALC_EXT_DEFAULT_FILTER_ORDER",
};
unordered_map<string, bool> SupportedALCExtensions;

string ReadableInfo;

vector<string> SplitAlString(const char* str)
{
	vector<string> ret;
	if (!str) return ret;
	auto p = str;
	auto p0 = str;
	while (*p != '\0' || *(p + 1) != '\0')
	{
		if (*(p + 1) == '\0')
		{
			auto s = string(p0, p + 1);
			if(!s.empty())
				ret.emplace_back(p0, p + 1);
			p0 = p + 2;
		}
		p++;
	}
	return ret;
}

void GetDeviceNames()
{
	if (!_has_ALC_ENUMERATE_ALL_EXT)
	{
		ALOGI("ALC_ENUMERATE_ALL_EXT is not supported");
		return;
	}
	const ALCchar *defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
	if (!defaultDeviceName)
	{
		ALOGI("Cannot get default device name");
	}
	else
	{
		// defaultDeviceName contains the name of the default device
		DefaultDeviceName = string(defaultDeviceName);
	}
	// Pass in NULL device handle to get list of *all* devices 
	const ALCchar *devices = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
	if (!devices)
	{
		ALOGI("Cannot get devices");
	}
	else
	{
		// devices contains *all* the device names, separated by NULL  
		// and terminated by two consecutive NULLs. 
		DeviceNames = SplitAlString(devices);
	}
}

void GetCaptureDeviceNames()
{
	const ALCchar *defaultDeviceName = alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
	if(defaultDeviceName)
		DefaultCaptureDeviceName = string(defaultDeviceName);
	if (!_has_ALC_ENUMERATE_ALL_EXT)
		return;
	const ALCchar *devices = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
	CaptureDeviceNames = SplitAlString(devices);
}

void GetBufferFormats()
{
	ALenum format;
	for (auto& f : PossibleBufferFormats)
	{
		format = alGetEnumValue(f.c_str());
		if (format)
			SupportedBufferFormats[f] = format;
	}
}

void GetAlExtensions()
{
	for (auto& e : PossibleALExtensions)
	{
		if (alIsExtensionPresent(e.c_str())==AL_TRUE)
			SupportedALExtensions[e] = true;
	}
}

void GetAlcExtensions()
{
	for (auto& e : PossibleALCExtensions)
	{
		if (alcIsExtensionPresent(NULL, e.c_str()) == ALC_TRUE)
			SupportedALCExtensions[e] = true;
	}
}

string GetReadableInfo()
{
	string ret;

	if(DefaultDeviceName.empty()){ ret += "No default device.\n"; }
	else{ ret += "Default device:\n"; ret += DefaultDeviceName+"\n"; }

	if (DeviceNames.empty()) { ret += "No available devices.\n"; }
	else
	{
		ret += "Available devices:\n";
		for (auto& d : DeviceNames)
			ret += d + "\n";
	}
	ret += "\n";
	
	if(DefaultCaptureDeviceName.empty()){ ret += "No default capture device.\n"; }
	else { ret += "Default capture device:\n"; ret += DefaultCaptureDeviceName + "\n"; }

	if (CaptureDeviceNames.empty()) { ret += "No available capture devices.\n"; }
	else
	{
		ret += "Available capture devices:\n";
		for (auto& d : CaptureDeviceNames)
			ret += d + "\n";
	}
	ret += "\n";

	if (SupportedBufferFormats.empty()) { ret += "No available buffer formats.\n"; }
	else
	{
		ret += "Available buffer formats:\n";
		for (auto& d : SupportedBufferFormats)
			ret += d.first + "\n";
	}
	ret += "\n";

	if (SupportedALExtensions.empty()) { ret += "No available AL extensions.\n"; }
	else
	{
		ret += "Available AL extensions:\n";
		for (auto& d : SupportedALExtensions)
			ret += d.first + "\n";
	}
	ret += "\n";

	if (SupportedALCExtensions.empty()) { ret += "No available ALC extensions.\n"; }
	else
	{
		ret += "Available ALC extensions:\n";
		for (auto& d : SupportedALCExtensions)
			ret += d.first + "\n";
	}

	return ret;
}

void ALSupport::init()
{
	if (_isLoaded)return;
	if (alcIsExtensionPresent(NULL, "ALC_ENUMERATE_ALL_EXT") != AL_TRUE)
		_has_ALC_ENUMERATE_ALL_EXT = false;
	GetDeviceNames();
	GetCaptureDeviceNames();
	GetBufferFormats();
	GetAlExtensions();
	GetAlcExtensions();
	ReadableInfo = GetReadableInfo();
	_isLoaded = true;
}

string ALSupport::getReadableInfo()
{
	init();
	return ReadableInfo;
}

string ALSupport::getDeviceName()
{
	init();
	return DefaultDeviceName;
}

string ALSupport::getCaptureDeviceName()
{
	init();
	return DefaultCaptureDeviceName;
}

vector<string> ALSupport::getDeviceNames()
{
	init();
	return DeviceNames;
}

vector<string> ALSupport::getCaptureDeviceNames()
{
	init();
	return CaptureDeviceNames;
}

ALenum ALSupport::getBufferFormat(const string& name)
{
	init();
	auto it = SupportedBufferFormats.find(name);
	if (it != SupportedBufferFormats.end())
		return it->second;
	return 0;
}

bool ALSupport::hasALEXT(const string& name)
{
	init();
	const auto it = SupportedALExtensions.find(name);
	return it != SupportedALExtensions.end();
}

bool ALSupport::hasALCEXT(const string& name)
{
	init();
	const auto it = SupportedALCExtensions.find(name);
	return it != SupportedALCExtensions.end();
}
