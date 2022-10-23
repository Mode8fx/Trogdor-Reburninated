#include "sound_logic.h"

bool sfxShouldBePlaying = false;
Uint8 sfxIndex = 0;
SoundEffect *sfxChannelArr[NUM_SOUND_CHANNELS_SFX] = { NULL, NULL, NULL, NULL, NULL, NULL };
//SoundEffect *sfxChannel_gameMusic = NULL;
SoundEffect *sfxChannel_strongBad = NULL;

#if defined(PSP)
#define LOAD_MUSIC(path)       oslLoadSoundFile((rootDir + path).c_str(), OSL_FMT_STREAM)
#define STOP_MUSIC()           oslStopSound(bgm)
#define FREE_MUSIC()           oslDeleteSound(bgm)
#define PAUSE_MUSIC()          oslPauseSound(bgm, 1)
#define LOAD_SFX(path)         oslLoadSoundFile((rootDir + path).c_str(), OSL_FMT_NONE)
#define PLAY_SFX(sfx, channel) oslPlaySound(sfx->chunk, channel)
#define FREE_SFX(sfx)          oslDeleteSound(sfx->chunk)
#elif defined(XBOX)
#define LOAD_MUSIC(path)       NULL
#define STOP_MUSIC()           NULL
#define FREE_MUSIC()           NULL
#define PAUSE_MUSIC()          NULL
#define LOAD_SFX(path)         NULL
#define PLAY_SFX(sfx, channel) NULL
#define FREE_SFX(sfx)          NULL
#else
#define LOAD_MUSIC(path)       Mix_LoadMUS((rootDir + path).c_str())
#define STOP_MUSIC()           Mix_HaltMusic()
#define FREE_MUSIC()           Mix_FreeMusic(bgm)
#define PAUSE_MUSIC()          Mix_PauseMusic()
#define LOAD_SFX(path)         Mix_LoadWAV((rootDir + path).c_str())
#define PLAY_SFX(sfx, channel) Mix_PlayChannel(channel, sfx->chunk, 0)
#define FREE_SFX(sfx)          Mix_FreeChunk(sfx->chunk)
#endif

void playMusic(const char *musicRelPath, bool loop) {
	bgm = LOAD_MUSIC(musicRelPath);
#if defined(PSP)
	if (loop) {
		oslSetSoundLoop(bgm, true);
	}
	oslPlaySound(bgm, SFX_CHANNEL_GAME_MUSIC);
#elif defined(XBOX)
#else
	if (loop) {
		Mix_PlayMusic(bgm, -1);
	} else {
		Mix_PlayMusic(bgm, 1);
	}
#endif
}

void playMusicAtIndex(Uint8 index) {
	if (soundSettings.musicIndex != 0) {
		stopMusic();
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
	STOP_MUSIC();
	FREE_MUSIC();
}

void pauseMusic() {
	PAUSE_MUSIC();
}

void loadAndPlaySound(SoundEffect *sfx) {
	if (!sfx->isPlaying) {
		if (!sfx->isStatic) {
			sfx->chunk = LOAD_SFX(sfx->path);
		}
		sfx->isPlaying = true;
	}
	if (sfx->type == 0) {
#if defined(PSP)
		sfxIndex = (sfxIndex + 1) % SFX_CHANNEL_GAME_MUSIC;
		PLAY_SFX(sfx, sfxIndex);
#elif defined(XBOX)
#else
		sfxIndex = PLAY_SFX(sfx, SFX_CHANNEL_GAME);
#endif
		sfxChannelArr[sfxIndex] = sfx;
	} else {
		PLAY_SFX(sfx, SFX_CHANNEL_STRONG_BAD);
		sfxChannel_strongBad = sfx;
	}
}

void makeSoundStatic(SoundEffect *sfx) {
	if (!sfx->isStatic) {
		sfx->isStatic = true;
		sfx->chunk = LOAD_SFX(sfx->path);
	}
}

void freeFinishedSoundChunks() {
	for (sfxIndex = 0; sfxIndex < NUM_SOUND_CHANNELS_SFX; sfxIndex++) {
		if (sfxChannelArr[sfxIndex] != NULL) {
#if defined(PSP)
			if (oslGetSoundChannel(sfxChannelArr[sfxIndex]->chunk) < 0) {
#elif defined(XBOX)
			if (false) {
#else
			if (!Mix_Playing(sfxIndex)) {
#endif
				sfxChannelArr[sfxIndex] = NULL;
			}
		}
	}
	if (sfxChannel_strongBad != NULL) {
#if defined(PSP)
		if (oslGetSoundChannel(sfxChannel_strongBad->chunk) < 0) {
#elif defined(XBOX)
		if (false) {
#else
		if (!Mix_Playing(SFX_CHANNEL_STRONG_BAD)) {
#endif
			sfxChannel_strongBad = NULL;
		}
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
				if (!sfxArr[sfxIndex]->isStatic) {
					FREE_SFX(sfxArr[sfxIndex]);
					sfxArr[sfxIndex]->chunk = NULL;
				}
				sfxArr[sfxIndex]->isPlaying = false;
			}
		}
	}
	for (sfxIndex = 0; sfxIndex < NUM_SOUND_EFFECTS_STRONG_BAD; sfxIndex++) {
		if (sfxArr_strongBad[sfxIndex]->isPlaying) {
			sfxShouldBePlaying = false;
			if (sfxArr_strongBad[sfxIndex] != sfxChannel_strongBad) {
				if (!sfxArr_strongBad[sfxIndex]->isStatic) {
					FREE_SFX(sfxArr_strongBad[sfxIndex]);
					sfxArr_strongBad[sfxIndex]->chunk = NULL;
				}
				sfxArr_strongBad[sfxIndex]->isPlaying = false;
			}
		}
	}
}