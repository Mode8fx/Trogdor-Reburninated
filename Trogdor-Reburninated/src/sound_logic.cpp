#include "sound_logic.h"

bool sfxShouldBePlaying = false;
Uint8 sfxIndex = 0;
SoundEffect *sfxArr[NUM_SOUND_EFFECTS_SFX];
SoundEffect *sfxChannelArr[NUM_SOUND_CHANNELS_SFX] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
//SoundEffect *sfxArr_gameMusic[NUM_SOUND_EFFECTS_GAMEMUSIC];
//SoundEffect *sfxChannel_gameMusic = NULL;
SoundEffect *sfxArr_strongBad[NUM_SOUND_EFFECTS_STRONG_BAD];
SoundEffect *sfxChannel_strongBad = NULL;

void playMusic(const char *musicRelPath) {
	bgm = Mix_LoadMUS((rootDir + musicRelPath).c_str());
#if !defined(PSP)
	Mix_PlayMusic(bgm, -1);
#else
	Mix_PlayMusic(bgm, 0);
#endif
}

void playMusicWithoutLoop(const char *musicRelPath) {
	bgm = Mix_LoadMUS((rootDir + musicRelPath).c_str());
	Mix_PlayMusic(bgm, 1);
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

void pauseMusic() {
	Mix_PauseMusic();
}

void loadAndPlaySound(SoundEffect *sfx) {
	if (!sfx->isPlaying) {
#if !defined(VITA)
		sfx->chunk = Mix_LoadWAV((rootDir + sfx->path).c_str());
#endif
		sfx->isPlaying = true;
	}
	if (sfx->type == 0) {
		sfxIndex = Mix_PlayChannel(SFX_CHANNEL_GAME, sfx->chunk, 0);
		sfxChannelArr[sfxIndex] = sfx;
	} else {
		Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx->chunk, 0);
		sfxChannel_strongBad = sfx;
	}
}

void freeFinishedSoundChunks() {
	for (sfxIndex = 0; sfxIndex < NUM_SOUND_CHANNELS_SFX; sfxIndex++) {
		if (sfxChannelArr[sfxIndex] != NULL && !Mix_Playing(sfxIndex)) {
			sfxChannelArr[sfxIndex] = NULL;
		}
	}
	if (sfxChannel_strongBad != NULL && !Mix_Playing(SFX_CHANNEL_STRONG_BAD)) {
		sfxChannel_strongBad = NULL;
	}
	for (sfxIndex = 0; sfxIndex < NUM_SOUND_EFFECTS_SFX; sfxIndex++) {
		if (sfxArr[sfxIndex]->isPlaying) {
			sfxShouldBePlaying = false;
			for (j = 0; j < NUM_SOUND_CHANNELS_SFX; j++) {
				if (sfxArr[sfxIndex] == sfxChannelArr[j]) {
					sfxShouldBePlaying = true;
					break;
				}
			}
			if (!sfxShouldBePlaying) {
#if !defined(VITA)
				Mix_FreeChunk(sfxArr[sfxIndex]->chunk);
				sfxArr[sfxIndex]->chunk = NULL;
#endif
				sfxArr[sfxIndex]->isPlaying = false;
			}
		}
	}
	for (sfxIndex = 0; sfxIndex < NUM_SOUND_EFFECTS_STRONG_BAD; sfxIndex++) {
		if (sfxArr_strongBad[sfxIndex]->isPlaying) {
			sfxShouldBePlaying = false;
			if (sfxArr_strongBad[sfxIndex] != sfxChannel_strongBad) {
#if !defined(VITA)
				Mix_FreeChunk(sfxArr_strongBad[sfxIndex]->chunk);
				sfxArr_strongBad[sfxIndex]->chunk = NULL;
#endif
				sfxArr_strongBad[sfxIndex]->isPlaying = false;
			}
		}
	}
}