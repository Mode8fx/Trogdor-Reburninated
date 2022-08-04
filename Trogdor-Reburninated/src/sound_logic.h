#include "config.h"

#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

constexpr auto SFX_CHANNEL_GAME = -1; // any free channel
constexpr auto SFX_CHANNEL_GAME_MUSIC = 6;
constexpr auto SFX_CHANNEL_STRONG_BAD = 7; // highest channel

extern Mix_Music *bgm;

extern void playMusic(const char *);
extern void playMusicWithoutLoop(const char *);
extern void playMusicAtIndex(Uint8);
extern void stopMusic();

#endif