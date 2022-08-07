#include "config.h"

#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

constexpr auto NUM_SOUND_EFFECTS_SFX = 12; // hardcoded; change this as more sound effects are added
//constexpr auto NUM_SOUND_EFFECTS_GAMEMUSIC = 0;
constexpr auto NUM_SOUND_EFFECTS_STRONG_BAD = 21;
constexpr auto NUM_SOUND_CHANNELS = 16;
constexpr auto NUM_SOUND_CHANNELS_SFX = NUM_SOUND_CHANNELS - 2;
constexpr auto SFX_CHANNEL_GAME = -1; // any free channel
constexpr auto SFX_CHANNEL_GAME_MUSIC = NUM_SOUND_CHANNELS - 2;
constexpr auto SFX_CHANNEL_STRONG_BAD = NUM_SOUND_CHANNELS - 1; // highest channel

constexpr auto MUSIC_TITLE_SCREEN = "music/title_screen.wav";

struct SoundEffect {
	bool isPlaying = false;
	Uint8 type = 0;
	const char *path;
	Mix_Chunk *chunk;
};

extern Mix_Music *bgm;
extern bool sfxShouldBePlaying;
extern SoundEffect *sfxArr[NUM_SOUND_EFFECTS_SFX];
extern SoundEffect *sfxChannelArr[NUM_SOUND_CHANNELS_SFX];
//extern SoundEffect *sfxArr_gameMusic[NUM_SOUND_EFFECTS_GAMEMUSIC];
//extern SoundEffect *sfxChannel_gameMusic;
extern SoundEffect *sfxArr_strongBad[NUM_SOUND_EFFECTS_STRONG_BAD];
extern SoundEffect *sfxChannel_strongBad;

extern void playMusic(const char *);
extern void playMusicWithoutLoop(const char *);
extern void playMusicAtIndex(Uint8);
extern void stopMusic();
extern void pauseMusic();
extern void loadAndPlaySound(SoundEffect *);
extern void freeFinishedSoundChunks();

#endif