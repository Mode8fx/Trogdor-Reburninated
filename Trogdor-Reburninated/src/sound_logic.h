#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

struct SoundSettings {
	Sint8 musicIndex;
	Sint8 bgmVolume = 100;
	Sint8 sfxVolume = 100;
};

#define MUSIC_TITLE_SCREEN (rootDir+"music/title_screen.wav").c_str()

#define SFX_CHANNEL_GAME 1
#define SFX_CHANNEL_STRONG_BAD 2

#define PLAY_MUSIC(music)     \
	bgm = Mix_LoadMUS(music); \
	Mix_PlayMusic(bgm, -1);

#define PLAY_MUSIC_WITHOUT_LOOP(music) \
	bgm = Mix_LoadMUS(music);          \
	Mix_PlayMusic(bgm, 0);

#define PLAY_MUSIC_AT_INDEX(index)       \
	if (soundSettings.musicIndex != 0) { \
		Mix_HaltMusic();                 \
		Mix_FreeMusic(bgm);              \
	}                                    \
	soundSettings.musicIndex = index;    \
	switch (soundSettings.musicIndex) {  \
		case 1:                          \
			bgm = Mix_LoadMUS(MUSIC_1);  \
			Mix_PlayMusic(bgm, -1);      \
			break;                       \
		case 2:                          \
			bgm = Mix_LoadMUS(MUSIC_2);  \
			Mix_PlayMusic(bgm, -1);      \
			break;                       \
		default:                         \
			break;                       \
	}

#define STOP_MUSIC() \
	Mix_HaltMusic(); \
	Mix_FreeMusic(bgm);

#endif