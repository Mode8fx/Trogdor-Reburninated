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

struct State_Settings_General {
	Sint8 bgmVolume;
	Sint8 sfxVolume;
};

struct State_Settings_Difficulty {
	Sint8 preset;
	Sint8 extraLives;
	Sint8 livesInterval;
	Sint8 peasantPenalty;
	Sint8 knightSpeed;
	Sint8 arrowSpeed;
	Sint8 archerFreq;
	Sint8 treasureHuts;
};

struct State_Settings_Cosmetic {
	Sint8 frameRate;
	Sint8 music;
	Sint8 commentFreq;
	Sint8 bigHeadMode;
	Sint8 scaling;
};

struct State_Settings_Other {
	Sint8 startingLevel;
	Sint8 shuffleLevels;
	Sint8 respawnBehavior;
	Sint8 levelTran;
};

struct State_Settings_Cheats {
	Sint8 infLives;
	Sint8 speedyMode;
	Sint8 noclip;
	Sint8 debugMode;
};

struct State_Settings_Unlocks {
	bool locked_infLives;
	bool locked_speedyMode;
	bool locked_noclip;
	bool locked_debugMode;
};

struct State_Autosave {
	Sint16 mans;                          // lives
	Uint32 score;                         // score
	Uint8 level;                          // current level
	bool treasureHutFound;                // treasure hut has been found in this level
	Sint8 treasureHutLevel;               // the level index of the first treasure hut you entered; default is 0
	Uint32 randomSeed;                    // random seed
	State_Settings_Difficulty difficulty; // Difficulty settings when the game was started
	Sint8 shuffleLevels;                  // whether or not levels are shuffled
	State_Settings_Cheats cheats;         // Cheat settings when the game was started
};

struct State_HighScores {
	Uint32 custom;
	Uint32 flash;
	Uint32 html5;
	Uint32 hard;
	Uint32 cruel;
	Uint32 mipsChoice;
};

struct State_Addon_v_2_1 {
	Sint8 knightMovement;
	Uint32 chaos;
};

struct GameState {
	State_Settings_General    settings_general;
	State_Settings_Difficulty settings_difficulty;
	State_Settings_Cosmetic   settings_cosmetic;
	State_Settings_Other      settings_other;
	State_Settings_Cheats     settings_cheats;
	State_Settings_Unlocks    settings_unlocks;
	State_Autosave            autosave;
	State_HighScores          highscores;
	State_Addon_v_2_1         addon_v_2_1;
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
extern Uint16 DEFAULT_WIDTH;
extern Uint16 DEFAULT_HEIGHT;
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

extern void saveGameState_settings();
extern void loadGameState();
extern void loadGameState_partial();
extern void setOptionsFromSaveData();
extern void initializeDefaultGameState();
extern void fixSaveDataIntegrity();

#endif