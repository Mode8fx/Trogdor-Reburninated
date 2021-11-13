#ifndef INCLUDE_H
#define INCLUDE_H

// to fix conflicting int32_t and uint32_t definitions, comment their typedefs out in `include/SDL/SDL_config_wii.h`

#if !defined(WII)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#endif
#include <iostream>
// #include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include <algorithm>
#include <vector>
#if defined(WII_U)
#include <unistd.h>
#include <whb/sdcard.h>
#elif defined(VITA)
#include <psp2/kernel/processmgr.h>
#elif defined(SWITCH)
#include <switch.h>
#elif defined(WII)
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <dirent.h>
#include <fat.h>
#elif defined(GAMECUBE)
#include <gccore.h>
#include <ogc/pad.h>
#include <dirent.h>
#include <fat.h>
#endif

using namespace std;

#endif