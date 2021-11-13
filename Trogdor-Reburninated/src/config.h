// Project-specific config (video settings and save file)

#ifndef CONFIG_H
#define CONFIG_H

#include "include.h"

#define DEFAULT_GAME_WIDTH    250
#define DEFAULT_GAME_HEIGHT   180
#define DEFAULT_FRAME_RATE    16

extern Uint16 gameWidth;
extern Uint16 gameHeight;
extern double gameWidthMult;
extern double gameHeightMult;
extern Uint16 frameRate;

#define GAME_WIDTH gameWidth
#define GAME_HEIGHT gameHeight
#define GAME_WIDTH_MULT gameWidthMult
#define GAME_HEIGHT_MULT gameHeightMult
#define FRAME_RATE frameRate

#define SET_WIDTH_HEIGHT_MULTS()                                     \
	double gameWidthMult = ((double)gameWidth / DEFAULT_GAME_WIDTH); \
	double gameHeightMult = ((double)gameHeight / DEFAULT_GAME_HEIGHT);

#define SAVE_FILE (rootDir+"save.bin").c_str()

#define LOAD_SAVE_FILE()                        \
	saveFile = SDL_RWFromFile(SAVE_FILE, "rb"); \
	if (saveFile == NULL) {                     \
		INITIALIZE_SAVE_FILE_WITH_SAVE();       \
	} else {                                    \
		SDL_RWclose(saveFile);                  \
	}

#define INITIALIZE_SAVE_FILE_WITH_SAVE()         \
    saveFile = SDL_RWFromFile(SAVE_FILE, "w+b"); \
    if (saveFile != NULL) {                      \
        SDL_RWclose(saveFile);                   \
    }

#define SAVE_CURRENT_SAVE()         \
	INITIALIZE_SAVE_FILE_WITH_SAVE( \
		soundSettings.musicIndex,   \
		soundSettings.bgmVolume,    \
		soundSettings.sfxVolume     \
	);

#endif