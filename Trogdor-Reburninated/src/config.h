// Project-specific config (video settings and save file)

#ifndef CONFIG_H
#define CONFIG_H

#include "include.h"

#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP)
#define PC 0
#else
#define PC 1
#endif

#define DEFAULT_GAME_WIDTH    250
#define DEFAULT_GAME_HEIGHT   180
#define DEFAULT_FRAME_RATE    16

extern Uint16 GAME_WIDTH;
extern Uint16 GAME_HEIGHT;
extern double gameWidthMult;
extern double gameHeightMult;
extern Uint16 frameRate;

#define GAME_WIDTH DEFAULT_GAME_WIDTH
#define GAME_HEIGHT DEFAULT_GAME_HEIGHT
#define GAME_WIDTH_MULT gameWidthMult
#define GAME_HEIGHT_MULT gameHeightMult
#define FRAME_RATE frameRate

#define SET_WIDTH_HEIGHT_MULTS()                              \
	gameWidthMult = ((double)GAME_WIDTH / DEFAULT_GAME_WIDTH); \
	gameHeightMult = ((double)GAME_HEIGHT / DEFAULT_GAME_HEIGHT);

#define SAVE_FILE (rootDir+"save.bin").c_str()

#define LOAD_SAVE_FILE()                                                \
	saveFile = SDL_RWFromFile(SAVE_FILE, "rb");                         \
	if (saveFile == NULL) {                                             \
		INITIALIZE_SAVE_FILE_NEW();                                     \
	} else {                                                            \
		SDL_RWread(saveFile, &videoSettings, sizeof(VideoSettings), 1); \
		SDL_RWread(saveFile, &soundSettings, sizeof(SoundSettings), 1); \
		SDL_RWclose(saveFile);                                          \
	}

#define INITIALIZE_SAVE_FILE_NEW()                                                \
    saveFile = SDL_RWFromFile(SAVE_FILE, "w+b");                                  \
    if (saveFile != NULL) {                                                       \
		videoSettings.resolutionIndex = DEFAULT_RI;                               \
		videoSettings.aspectRatioIndex = DEFAULT_ARI;                             \
        videoSettings.widthSetting = DEFAULT_WIDTH;                               \
        videoSettings.heightSetting = DEFAULT_HEIGHT;                             \
		soundSettings.musicIndex = 0;                                             \
		soundSettings.bgmVolume = 100;                                            \
		soundSettings.sfxVolume = 100;                                            \
		SDL_RWwrite(saveFile, &videoSettings.resolutionIndex, sizeof(Uint8), 1);  \
		SDL_RWwrite(saveFile, &videoSettings.aspectRatioIndex, sizeof(Uint8), 1); \
        SDL_RWwrite(saveFile, &videoSettings.widthSetting, sizeof(Uint16), 1);    \
        SDL_RWwrite(saveFile, &videoSettings.heightSetting, sizeof(Uint16), 1);   \
		SDL_RWwrite(saveFile, &soundSettings.musicIndex, sizeof(Sint8), 1);       \
		SDL_RWwrite(saveFile, &soundSettings.bgmVolume, sizeof(Sint8), 1);        \
		SDL_RWwrite(saveFile, &soundSettings.sfxVolume, sizeof(Sint8), 1);        \
        SDL_RWclose(saveFile);                                                    \
    }

// unused for now
#define SAVE_CURRENT_SAVE()         \
	INITIALIZE_SAVE_FILE_WITH_SAVE( \
		soundSettings.musicIndex,   \
		soundSettings.bgmVolume,    \
		soundSettings.sfxVolume     \
	);

#endif