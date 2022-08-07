#include "sound_logic.h"

bool sfxShouldBePlaying = false;
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
		sfx->chunk = Mix_LoadWAV((rootDir + sfx->path).c_str());
		sfx->isPlaying = true;
	}
	if (sfx->type == 0) {
		i = Mix_PlayChannel(SFX_CHANNEL_GAME, sfx->chunk, 0);
		sfxChannelArr[i] = sfx;
	} else {
		Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx->chunk, 0);
		sfxChannel_strongBad = sfx;
	}
}

void freeFinishedSoundChunks() {
	for (i = 0; i < NUM_SOUND_CHANNELS_SFX; i++) {
		if (sfxChannelArr[i] != NULL && !Mix_Playing(i)) {
			sfxChannelArr[i] = NULL;
		}
	}
	if (sfxChannel_strongBad != NULL && !Mix_Playing(SFX_CHANNEL_STRONG_BAD)) {
		sfxChannel_strongBad = NULL;
	}
	for (i = 0; i < NUM_SOUND_EFFECTS_SFX; i++) {
		if (sfxArr[i]->isPlaying) {
			sfxShouldBePlaying = false;
			for (j = 0; j < NUM_SOUND_CHANNELS_SFX; j++) {
				if (sfxArr[i] == sfxChannelArr[j]) {
					sfxShouldBePlaying = true;
					break;
				}
			}
			if (!sfxShouldBePlaying) {
				Mix_FreeChunk(sfxArr[i]->chunk);
				sfxArr[i]->isPlaying = false;
			}
		}
	}
	for (i = 0; i < NUM_SOUND_EFFECTS_STRONG_BAD; i++) {
		if (sfxArr_strongBad[i]->isPlaying) {
			sfxShouldBePlaying = false;
			if (sfxArr_strongBad[i] != sfxChannel_strongBad) {
				Mix_FreeChunk(sfxArr_strongBad[i]->chunk);
				sfxArr_strongBad[i]->isPlaying = false;
			}
		}
	}
}