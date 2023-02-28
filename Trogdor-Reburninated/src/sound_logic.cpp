#include "sound_logic.h"
#include "config.h"
#include "general.h"

bool sfxShouldBePlaying = false;
Uint8 sfxIndex = 0;
SoundEffect *sfxChannelArr[NUM_SOUND_CHANNELS_SFX] = { NULL, NULL, NULL, NULL, NULL, NULL };
//SoundEffect *sfxChannel_gameMusic = NULL;
SoundEffect *sfxChannel_strongBad = NULL;

#if defined(PSP)
#define LOAD_MUSIC(path)       oslLoadSoundFile((rootDir + path).c_str(), OSL_FMT_STREAM)
#define STOP_MUSIC()           oslStopSound(bgm)
#define FREE_MUSIC()           oslDeleteSound(bgm); bgm = NULL;
#define PAUSE_MUSIC()          oslPauseSound(bgm, 1)
#define RESUME_MUSIC()         oslPauseSound(bgm, 0)
#define FADE_MUSIC(ms)         STOP_MUSIC()
#define LOAD_SFX(path)         oslLoadSoundFile((rootDir + path).c_str(), OSL_FMT_NONE)
#define PLAY_SFX(sfx, channel) oslPlaySound(sfx->chunk, channel)
#define FREE_SFX(sfx)          oslDeleteSound(sfx->chunk)
#define SET_VOLUME_MUSIC(vol)  bgm->volumeLeft = bgm->volumeRight = ((vol * OSL_VOLUME_MAX) / 100)
#define MUSIC_IS_PLAYING()     (bgm != NULL)
#elif defined(XBOX)
#define LOAD_MUSIC(path)       NULL
#define STOP_MUSIC()           NULL
#define FREE_MUSIC()           NULL
#define PAUSE_MUSIC()          NULL
#define RESUME_MUSIC()         NULL
#define FADE_MUSIC(ms)         NULL
#define LOAD_SFX(path)         NULL
#define PLAY_SFX(sfx, channel) NULL
#define FREE_SFX(sfx)          NULL
#define SET_VOLUME_MUSIC(vol)  NULL
#define MUSIC_IS_PLAYING()     NULL
#else
#define LOAD_MUSIC(path)       Mix_LoadMUS((rootDir + path).c_str())
#define STOP_MUSIC()           Mix_HaltMusic()
#define FREE_MUSIC()           Mix_FreeMusic(bgm); bgm = NULL;
#define PAUSE_MUSIC()          Mix_PauseMusic()
#define RESUME_MUSIC()         Mix_ResumeMusic()
#define FADE_MUSIC(ms)         Mix_FadeOutMusic(ms)
#define LOAD_SFX(path)         Mix_LoadWAV((rootDir + path).c_str())
#define PLAY_SFX(sfx, channel) Mix_PlayChannel(channel, sfx->chunk, 0)
#define FREE_SFX(sfx)          Mix_FreeChunk(sfx->chunk)
#define SET_VOLUME_MUSIC(vol)  Mix_VolumeMusic(vol * 128 / 100)
#define MUSIC_IS_PLAYING()     Mix_PlayingMusic()
#endif

void playMusic(const char *musicRelPath, bool loop, Uint8 vol) {
	if (MUSIC_IS_PLAYING()) {
		stopMusic();
	}
	bgm = LOAD_MUSIC(musicRelPath);
#if defined(PSP)
	if (loop) {
		oslSetSoundLoop(bgm, true);
	}
	oslPlaySound(bgm, SFX_CHANNEL_GAME_MUSIC);
	setVolume_music(vol);
#elif defined(XBOX)
#else
	setVolume_music(vol);
	if (loop) {
		Mix_PlayMusic(bgm, -1);
	} else {
		Mix_PlayMusic(bgm, 1);
	}
#endif
}

void stopMusic() {
	if (MUSIC_IS_PLAYING()) {
		STOP_MUSIC();
#if !(defined(PSP) || defined(THREEDS))
		FREE_MUSIC();
#endif
	}
}

void pauseMusic() {
	if (MUSIC_IS_PLAYING()) {
		PAUSE_MUSIC();
	}
}

void resumeMusic() {
	if (MUSIC_IS_PLAYING()) {
		RESUME_MUSIC();
	}
}

void fadeMusic(Uint16 ms) {
	if (MUSIC_IS_PLAYING()) {
		FADE_MUSIC(ms);
	}
}

Uint8 loadAndPlaySound(SoundEffect *sfx) {
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
		sfxIndex = 0;
#else
		sfxIndex = PLAY_SFX(sfx, SFX_CHANNEL_GAME);
#endif
		sfxChannelArr[sfxIndex] = sfx;
		return sfxIndex;
	} else {
		PLAY_SFX(sfx, SFX_CHANNEL_STRONG_BAD);
		sfxChannel_strongBad = sfx;
		return SFX_CHANNEL_STRONG_BAD;
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

void setVolume_music(Uint8 vol) {
#if defined(PSP)
	if (MUSIC_IS_PLAYING()) {
		SET_VOLUME_MUSIC(vol);
	}
#else
	SET_VOLUME_MUSIC(vol);
#endif
}