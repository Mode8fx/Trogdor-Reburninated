#include "include.h"

#ifndef CONFIG_H
#define CONFIG_H

constexpr auto DEFAULT_VOLUME_GAME = 100;
constexpr auto DEFAULT_VOLUME_MUSIC = 35;
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX))
#define MAX_PAGE_NUM_LOWRES 5
#define MAX_PAGE_NUM_HIRES 4
#else
#define MAX_PAGE_NUM_LOWRES 4
#define MAX_PAGE_NUM_HIRES 3
#endif

struct State_Settings {
	Sint8 bgmVolume;
	Sint8 sfxVolume;
	Sint8 startingLevel;
	Sint8 extraLives;
	Sint8 livesInterval;
	Sint8 peasantPenalty;
	Sint8 treasureHuts;
	Sint8 archerFreq;
	Sint8 knightBehavior;
	Sint8 frameRate;
	Sint8 levelTran;
	Sint8 music;
	Sint8 commentFreq;
	Sint8 scaling;
	Sint8 infLives;
	Sint8 debugMode;
	Sint8 bigHeadMode;
	Sint8 noclip;
	bool  locked_infLives;
	bool  locked_debugMode;
	bool  locked_bigHeadMode;
	bool  locked_noclip;
};

struct GameState {
	State_Settings settings;
};

/* Save File */
extern SDL_RWops *saveBin;
extern GameState gameState;

/* System-Specific Variables */
#if defined(VITA)
const string rootDir = "ux0:data/Trogdor-RB/";
#elif defined(WII)
const string rootDir = "sd:/apps/Trogdor-RB/";
#elif defined(GAMECUBE)
const string rootDir = "cardb:/Trogdor-RB/";
#elif defined(THREEDS)
const string rootDir = "sdmc:/3ds/Trogdor-RB/";
#else
const string rootDir = "";
#endif

#define SAVE_FILE (rootDir+"save.bin").c_str()

#define CREATE_DEBUG_FILE(str) \
	saveBin = SDL_RWFromFile((rootDir + str).c_str(), "w+b"); \
	SDL_RWclose(saveBin);

#if !defined(SDL1)
extern SDL_DisplayMode DM;
#endif

#if defined(WII_U)
constexpr auto DEFAULT_WIDTH = 1280;
constexpr auto DEFAULT_HEIGHT = 720;
#elif defined(VITA)
constexpr auto DEFAULT_WIDTH = 960;
constexpr auto DEFAULT_HEIGHT = 544;
#elif defined(SWITCH)
constexpr auto DEFAULT_WIDTH = 1920;
constexpr auto DEFAULT_HEIGHT = 1080;
#elif defined(PSP)
constexpr auto DEFAULT_WIDTH = 480;
constexpr auto DEFAULT_HEIGHT = 272;
#elif defined(WII) || defined(GAMECUBE) || defined(XBOX)
constexpr auto DEFAULT_WIDTH = 640;
constexpr auto DEFAULT_HEIGHT = 480;
#elif defined(THREEDS)
constexpr auto DEFAULT_WIDTH = 400;
constexpr auto DEFAULT_HEIGHT = 240;
#elif defined(ANDROID)
#define DEFAULT_WIDTH  max(DM.w, DM.h)
#define DEFAULT_HEIGHT min(DM.w, DM.h)
#elif defined(SDL1)
constexpr auto DEFAULT_WIDTH = 320;
constexpr auto DEFAULT_HEIGHT = 240;
#else
constexpr auto DEFAULT_WIDTH = 640;
constexpr auto DEFAULT_HEIGHT = 480;
#endif

extern void saveGameState();
extern void loadGameState();

#endif