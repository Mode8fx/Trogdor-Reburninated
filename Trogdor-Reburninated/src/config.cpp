#include "config.h"

void loadSaveFile() {
	saveFile = SDL_RWFromFile(SAVE_FILE, "rb");
	if (saveFile == NULL) {
		initializeSaveFileNew();
	} else {
		SDL_RWread(saveFile, &videoSettings, sizeof(VideoSettings), 1);
		SDL_RWread(saveFile, &soundSettings, sizeof(SoundSettings), 1);
		SDL_RWclose(saveFile);
	}
}

void initializeSaveFileNew() {
	saveFile = SDL_RWFromFile(SAVE_FILE, "w+b");
	if (saveFile != NULL) {
		videoSettings.resolutionIndex = DEFAULT_RI;
		videoSettings.aspectRatioIndex = DEFAULT_ARI;
		videoSettings.widthSetting = DEFAULT_WIDTH;
		videoSettings.heightSetting = DEFAULT_HEIGHT;
		soundSettings.musicIndex = 0;
		soundSettings.bgmVolume = 100;
		soundSettings.sfxVolume = 100;
		SDL_RWwrite(saveFile, &videoSettings.resolutionIndex, sizeof(Uint8), 1);
		SDL_RWwrite(saveFile, &videoSettings.aspectRatioIndex, sizeof(Uint8), 1);
		SDL_RWwrite(saveFile, &videoSettings.widthSetting, sizeof(Uint16), 1);
		SDL_RWwrite(saveFile, &videoSettings.heightSetting, sizeof(Uint16), 1);
		SDL_RWwrite(saveFile, &soundSettings.musicIndex, sizeof(Sint8), 1);
		SDL_RWwrite(saveFile, &soundSettings.bgmVolume, sizeof(Sint8), 1);
		SDL_RWwrite(saveFile, &soundSettings.sfxVolume, sizeof(Sint8), 1);
		SDL_RWclose(saveFile);
	}
}

// unused for now
//void SAVE_CURRENT_SAVE() {
//	INITIALIZE_SAVE_FILE_WITH_SAVE(
//		soundSettings.musicIndex,
//		soundSettings.bgmVolume,
//		soundSettings.sfxVolume
//	);
//}