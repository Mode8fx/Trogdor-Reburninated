#include "config.h"

#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

constexpr auto NUM_SOUND_EFFECTS_SFX = 13; // hardcoded; change this as more sound effects are added
//constexpr auto NUM_SOUND_EFFECTS_GAMEMUSIC = 0;
constexpr auto NUM_SOUND_EFFECTS_STRONG_BAD = 21;
constexpr auto NUM_SOUND_CHANNELS = 8;
constexpr auto NUM_SOUND_CHANNELS_SFX = NUM_SOUND_CHANNELS - 2;
constexpr auto SFX_CHANNEL_GAME = -1; // any free channel
constexpr auto SFX_CHANNEL_GAME_MUSIC = NUM_SOUND_CHANNELS - 2;
constexpr auto SFX_CHANNEL_STRONG_BAD = NUM_SOUND_CHANNELS - 1; // highest channel

#if !defined(PSP)
constexpr auto MUSIC_TITLE_SCREEN = "music/title_screen.wav";
#else
constexpr auto MUSIC_TITLE_SCREEN = "music/title_screen.bgm";
#endif

struct SoundEffect {
	bool isPlaying = false;
	Uint8 type = 0;
	bool isStatic = false;
	const char *path;
#if !defined(PSP)
	Mix_Chunk *chunk;
#else
	OSL_SOUND *chunk;
#endif
};

#if !defined(PSP)
extern Mix_Music *bgm;
#else
extern OSL_SOUND *bgm;
#endif
extern bool sfxShouldBePlaying;
extern Uint8 sfxIndex;
extern SoundEffect *sfxArr[NUM_SOUND_EFFECTS_SFX];
extern SoundEffect *sfxChannelArr[NUM_SOUND_CHANNELS_SFX];
//extern SoundEffect *sfxArr_gameMusic[NUM_SOUND_EFFECTS_GAMEMUSIC];
//extern SoundEffect *sfxChannel_gameMusic;
extern SoundEffect *sfxArr_strongBad[NUM_SOUND_EFFECTS_STRONG_BAD];
extern SoundEffect *sfxChannel_strongBad;

extern void playMusic(const char *, bool);
extern void playMusicAtIndex(Uint8);
extern void stopMusic();
extern void pauseMusic();
extern void loadAndPlaySound(SoundEffect *);
extern void makeSoundStatic(SoundEffect *);
extern void freeFinishedSoundChunks();

#endif