#include "sound_logic.h"

void playMusic(const char *music) {
	bgm = Mix_LoadMUS(music);
#if !defined(PSP)
	Mix_PlayMusic(bgm, -1);
#else
	Mix_PlayMusic(bgm, 0);
#endif
}

void playMusicWithoutLoop(const char *music) {
	bgm = Mix_LoadMUS(music);
	Mix_PlayMusic(bgm, 0);
}

void playMusicAtIndex(Uint8 index) {
	if (soundSettings.musicIndex != 0) {
		Mix_HaltMusic();
		Mix_FreeMusic(bgm);
	}
	soundSettings.musicIndex = index;
	switch (soundSettings.musicIndex) {
		case 1:
		//	bgm = Mix_LoadMUS(MUSIC_1);
		//	Mix_PlayMusic(bgm, -1);
			break;
		default:
			break;
	}
}

void stopMusic() {
	Mix_HaltMusic();
	Mix_FreeMusic(bgm);
}