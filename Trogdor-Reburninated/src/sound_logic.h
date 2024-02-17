#include "include.h"

#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

constexpr auto NUM_SOUND_EFFECTS_SFX = 13; // hardcoded; change this as more sound effects are added
//constexpr auto NUM_SOUND_EFFECTS_GAMEMUSIC = 0;
constexpr auto NUM_SOUND_EFFECTS_STRONG_BAD = 23;
constexpr auto NUM_SOUND_CHANNELS = 8;
constexpr auto NUM_SOUND_CHANNELS_SFX = NUM_SOUND_CHANNELS - 2;
constexpr auto SFX_CHANNEL_GAME = -1; // any free channel
constexpr auto SFX_CHANNEL_GAME_MUSIC = NUM_SOUND_CHANNELS - 2;
constexpr auto SFX_CHANNEL_STRONG_BAD = NUM_SOUND_CHANNELS - 1; // highest channel

#if defined(PSP)
constexpr auto MUSIC_TITLE_SCREEN = "music/title_screen.bgm";
constexpr auto MUSIC_MENU = "music/menu.bgm";
constexpr auto MUSIC_ENDING_1 = "music/ending_1.bgm";
constexpr auto MUSIC_ENDING_2 = "music/ending_2.bgm";
constexpr auto MUSIC_STINKOMAN_DAY = "music/stinkoman_level_1.bgm";
constexpr auto MUSIC_STINKOMAN_EVENING = "music/stinkoman_level_2.bgm";
constexpr auto MUSIC_STINKOMAN_NIGHT = "music/stinkoman_level_5.bgm";
constexpr auto MUSIC_STINKOMAN_DAWN = "music/stinkoman_level_6.bgm";
constexpr auto MUSIC_STINKOMAN_MIDPOINT = "music/stinkoman_level_9.bgm";
constexpr auto MUSIC_STINKOMAN_LAST_10 = "music/stinkoman_level_10.bgm";
constexpr auto MUSIC_STINKOMAN_BOSS = "music/stinkoman_boss_fight.bgm";
constexpr auto MUSIC_STINKOMAN_HOMESTRETCH = "music/stinkoman_z_sabre.bgm";
constexpr auto MUSIC_STINKOMAN_FINAL_BOSS = "music/stinkoman_mecha_trogador.bgm";
#elif defined(THREEDS) // an old 3DS can already barely keep up without needing to decompress OGG
constexpr auto MUSIC_TITLE_SCREEN = "music/title_screen.wav";
constexpr auto MUSIC_MENU = "music/menu.wav";
constexpr auto MUSIC_ENDING_1 = "music/ending_1.wav";
constexpr auto MUSIC_ENDING_2 = "music/ending_2.wav";
constexpr auto MUSIC_STINKOMAN_DAY = "music/stinkoman_level_1.wav";
constexpr auto MUSIC_STINKOMAN_EVENING = "music/stinkoman_level_2.wav";
constexpr auto MUSIC_STINKOMAN_NIGHT = "music/stinkoman_level_5.wav";
constexpr auto MUSIC_STINKOMAN_DAWN = "music/stinkoman_level_6.wav";
constexpr auto MUSIC_STINKOMAN_MIDPOINT = "music/stinkoman_level_9.wav";
constexpr auto MUSIC_STINKOMAN_LAST_10 = "music/stinkoman_level_10.wav";
constexpr auto MUSIC_STINKOMAN_BOSS = "music/stinkoman_boss_fight.wav";
constexpr auto MUSIC_STINKOMAN_HOMESTRETCH = "music/stinkoman_z_sabre.wav";
constexpr auto MUSIC_STINKOMAN_FINAL_BOSS = "music/stinkoman_mecha_trogador.wav";
#else
constexpr auto MUSIC_TITLE_SCREEN = "music/title_screen.ogg";
constexpr auto MUSIC_MENU = "music/menu.ogg";
constexpr auto MUSIC_ENDING_1 = "music/ending_1.ogg";
constexpr auto MUSIC_ENDING_2 = "music/ending_2.ogg";
constexpr auto MUSIC_STINKOMAN_DAY = "music/stinkoman_level_1.ogg";
constexpr auto MUSIC_STINKOMAN_EVENING = "music/stinkoman_level_2.ogg";
constexpr auto MUSIC_STINKOMAN_NIGHT = "music/stinkoman_level_5.ogg";
constexpr auto MUSIC_STINKOMAN_DAWN = "music/stinkoman_level_6.ogg";
constexpr auto MUSIC_STINKOMAN_MIDPOINT = "music/stinkoman_level_9.ogg";
constexpr auto MUSIC_STINKOMAN_LAST_10 = "music/stinkoman_level_10.ogg";
constexpr auto MUSIC_STINKOMAN_BOSS = "music/stinkoman_boss_fight.ogg";
constexpr auto MUSIC_STINKOMAN_HOMESTRETCH = "music/stinkoman_z_sabre.ogg";
constexpr auto MUSIC_STINKOMAN_FINAL_BOSS = "music/stinkoman_mecha_trogador.ogg";
#endif

struct SoundEffect {
	bool isPlaying = false;
	Uint8 type = 0;
	bool isStatic = false;
	const char *path;
	unsigned char *data;
	unsigned int len;
#if defined(PSP)
	OSL_SOUND *chunk;
#elif defined(XBOX)
	int *chunk;
#else
	Mix_Chunk *chunk;
#endif
};

#if defined(PSP)
extern OSL_SOUND *bgm;
#elif defined(XBOX)
extern int *bgm;
#else
extern Mix_Music *bgm;
#endif
extern bool sfxShouldBePlaying;
extern Uint8 sfxIndex;
extern SoundEffect *sfxArr[NUM_SOUND_EFFECTS_SFX];
extern SoundEffect *sfxChannelArr[NUM_SOUND_CHANNELS_SFX];
//extern SoundEffect *sfxArr_gameMusic[NUM_SOUND_EFFECTS_GAMEMUSIC];
//extern SoundEffect *sfxChannel_gameMusic;
extern SoundEffect *sfxArr_strongBad[NUM_SOUND_EFFECTS_STRONG_BAD];
extern SoundEffect *sfxChannel_strongBad;

extern void playMusic(const char *, bool, Uint8);
extern void stopMusic();
extern void pauseMusic();
extern void resumeMusic();
extern void fadeMusic(Uint16);
extern Uint8 loadAndPlaySound(SoundEffect *);
extern void makeSoundStatic(SoundEffect *);
extern void freeFinishedSoundChunks();
extern void setVolume_music(Uint8);

#define SFX_BURN_HUT      sfxArr[0]
#define SFX_GOLDGET       sfxArr[1]
#define SFX_PEASANTSCREAM sfxArr[2]
#define SFX_SFX2          sfxArr[3]
#define SFX_TROGADOR      sfxArr[4]
#define SFX_ARROW         sfxArr[5]
#define SFX_SQUISH        sfxArr[6]
#define SFX_DEATH         sfxArr[7]
#define SFX_KICK          sfxArr[8]
#define SFX_BURNINATE     sfxArr[9]
#define SFX_CUTSCENE      sfxArr[10]
#define SFX_GAMEOVER      sfxArr[11]
#define SFX_SPEEDINCREASED sfxArr[12]
#define SFX_SB1           sfxArr_strongBad[0]
#define SFX_SB2           sfxArr_strongBad[1]
#define SFX_SB3           sfxArr_strongBad[2]
#define SFX_SB4           sfxArr_strongBad[3]
#define SFX_SB5           sfxArr_strongBad[4]
#define SFX_SB6           sfxArr_strongBad[5]
#define SFX_SB7           sfxArr_strongBad[6]
#define SFX_SBARCH        sfxArr_strongBad[7]
#define SFX_SBARCHEND     sfxArr_strongBad[8]
#define SFX_SBBEST        sfxArr_strongBad[9]
#define SFX_SBDOOJ        sfxArr_strongBad[10]
#define SFX_SBGAMEOVER    sfxArr_strongBad[11]
#define SFX_SBKERREK      sfxArr_strongBad[12]
#define SFX_SBLEVELBEAT   sfxArr_strongBad[13]
#define SFX_SBSCORE       sfxArr_strongBad[14]
#define SFX_SBSECRET      sfxArr_strongBad[15]
#define SFX_SBSQUISH1     sfxArr_strongBad[16]
#define SFX_SBSQUISH2     sfxArr_strongBad[17]
#define SFX_SBWIN         sfxArr_strongBad[18]
#define SFX_SBWIN2        sfxArr_strongBad[19]
#define SFX_SBWORST       sfxArr_strongBad[20]
#define SFX_SBDOOJ_SHORT  sfxArr_strongBad[21]
#define SFX_ITSOVER       sfxArr_strongBad[22]
extern SoundEffect sfx_burn_hut;
extern SoundEffect sfx_goldget;
extern SoundEffect sfx_peasantscream;
extern SoundEffect sfx_sb1;
extern SoundEffect sfx_sb2;
extern SoundEffect sfx_sb3;
extern SoundEffect sfx_sb4;
extern SoundEffect sfx_sb5;
extern SoundEffect sfx_sb6;
extern SoundEffect sfx_sb7;
extern SoundEffect sfx_sbarch;
extern SoundEffect sfx_sbarchend;
extern SoundEffect sfx_sbbest;
extern SoundEffect sfx_sbdooj;
extern SoundEffect sfx_sbgameover;
extern SoundEffect sfx_sbkerrek;
extern SoundEffect sfx_sblevelbeat;
extern SoundEffect sfx_sbscore;
extern SoundEffect sfx_sbsecret;
extern SoundEffect sfx_sbsquish1;
extern SoundEffect sfx_sbsquish2;
extern SoundEffect sfx_sbwin;
extern SoundEffect sfx_sbwin2;
extern SoundEffect sfx_sbworst;
extern SoundEffect sfx_sfx2;
extern SoundEffect sfx_trogador;
extern SoundEffect sfx_arrow;
extern SoundEffect sfx_squish;
extern SoundEffect sfx_death;
extern SoundEffect sfx_kick;
extern SoundEffect sfx_burninate;
extern SoundEffect sfx_cutscene;
extern SoundEffect sfx_gameover;
extern SoundEffect sfx_speedincreased;
extern SoundEffect sfx_sbdooj_short;
extern SoundEffect sfx_itsover;

#endif