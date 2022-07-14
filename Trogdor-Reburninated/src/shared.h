#include "include.h"

#ifndef SHARED_H
#define SHARED_H

struct SoundSettings {
	Sint8 musicIndex;
	Sint8 bgmVolume;
	Sint8 sfxVolume;
};

struct VideoSettings {
	Sint8 resolutionIndex;
	Sint8 aspectRatioIndex;
	Uint16 widthSetting;
	Uint16 heightSetting;
};

#endif
