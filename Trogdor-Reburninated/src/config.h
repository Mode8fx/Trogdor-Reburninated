#include "include.h"

#ifndef CONFIG_H
#define CONFIG_H

constexpr auto DEFAULT_VOLUME_GAME = 100;
constexpr auto DEFAULT_VOLUME_MUSIC = 35;
constexpr auto DEFAULT_VOLUME_MUSIC_LATE_LEVEL = 18;
constexpr auto DEFAULT_VOLUME_MUSIC_PAUSED = 11;
#if defined(PC)
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
	Uint32 chance;
};

struct State_Addon_v_2_2_1 {
	Sint8 overlay;
	Sint8 windowed;
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
	State_Addon_v_2_2_1       addon_v_2_2_1;
};

/* Save File */
extern SDL_RWops *saveBin;
extern GameState gameState;

/* System-Specific Variables */
extern string getExeDirectory();
extern string rootDir;

#define SAVE_FILE "/mnt/FunKey/.trogdorrb/save.bin"

#define CREATE_DEBUG_FILE(str) \
	saveBin = SDL_RWFromFile((rootDir + str).c_str(), "w+b"); \
	SDL_RWclose(saveBin);

extern Uint16 displayRefreshRate;

constexpr auto DEFAULT_WIDTH = 240;
constexpr auto DEFAULT_HEIGHT = 240;

extern void setRootDir();
extern void saveGameState_settings();
extern void loadGameState();
extern void loadGameState_partial();
extern void setOptionsFromSaveData();
extern void initializeDefaultGameState();
extern void fixSaveDataIntegrity();
extern void saveGameState_all();

#endif