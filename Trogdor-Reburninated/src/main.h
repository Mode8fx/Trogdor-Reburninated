#ifndef MAIN_H
#define MAIN_H

#include "media_objects_init.h"
#include "system_specific_macros.h"

SDL_Event event;

/* SDL Input */
#if !defined(SDL1) && !defined(PSP)
SDL_GameController *controller = nullptr;
#else
SDL_Joystick *joystick = nullptr;
Uint8 joystickHat;
#endif
Sint16 controllerAxis_leftStickX;
Sint16 controllerAxis_leftStickY;
Sint16 controllerAxis_rightStickX;
Sint16 controllerAxis_rightStickY;
Sint16 controllerAxis_LT;
Sint16 controllerAxis_RT;
#if defined(PC)
Sint32 mouseInput_x;
Sint32 mouseInput_x_last;
Sint32 mouseInput_y;
Sint32 mouseInput_y_last;
#endif

/* Audio */
Mix_Music *bgm;
Mix_Chunk *music_title_screen;
Mix_Chunk *sfx_burn_hut;
Mix_Chunk *sfx_goldget;
Mix_Chunk *sfx_peasantscream;
Mix_Chunk *sfx_sb1;
Mix_Chunk *sfx_sb2;
Mix_Chunk *sfx_sb3;
Mix_Chunk *sfx_sb4;
Mix_Chunk *sfx_sb5;
Mix_Chunk *sfx_sb6;
Mix_Chunk *sfx_sb7;
Mix_Chunk *sfx_sbarch;
Mix_Chunk *sfx_sbarchend;
Mix_Chunk *sfx_sbbest;
Mix_Chunk *sfx_sbdooj;
Mix_Chunk *sfx_sbgameover;
Mix_Chunk *sfx_sbkerrek;
Mix_Chunk *sfx_sblevelbeat;
Mix_Chunk *sfx_sbscore;
Mix_Chunk *sfx_sbsecret;
Mix_Chunk *sfx_sbsquish1;
Mix_Chunk *sfx_sbsquish2;
Mix_Chunk *sfx_sbwin;
Mix_Chunk *sfx_sbwin2;
Mix_Chunk *sfx_sbworst;
Mix_Chunk *sfx_sfx2;
Mix_Chunk *sfx_trogador;
Mix_Chunk *sfx_arrow;
Mix_Chunk *sfx_squish;
Mix_Chunk *sfx_death;
Mix_Chunk *sfx_kick;
Mix_Chunk *sfx_burninate;
Mix_Chunk *sfx_cutscene;
Mix_Chunk *sfx_gameover;

/* Sprite Objects */
SDL_Surface  *temp;
SpriteObject sprite_videlectrix_logo;
SpriteObject sprite_title_screen;
SpriteObject sprite_trogdor_logo;
SpriteObject sprite_level_background_1;
SpriteObject sprite_level_background_2;
SpriteObject sprite_level_background_3;
SpriteObject sprite_level_background_4;
SpriteObject sprite_level_background_th;
SpriteObject *sprite_level_background;
SpriteObject sprite_trogdor;
SpriteObject sprite_burnination_meter_full;
SpriteObject sprite_burnination_meter_empty;
SpriteObject sprite_cottage;
SpriteObject sprite_cottage_fire;
SpriteObject sprite_peasantometer_icon;
Uint8 sprite_peasantometer_icon_init_x;
SpriteObject sprite_archer;
SpriteObject sprite_arrow;
SpriteObject sprite_trogdor_fire;
SpriteObject sprite_trogdor_dead;
SpriteObject sprite_knight;
SpriteObject sprite_peasant;
SpriteObject sprite_end_of_level_flash;
SpriteObject sprite_end_of_level_trogdor;
SpriteObject sprite_death_message;
SpriteObject sprite_burninate_text;
SpriteObject sprite_burninate_fire;
SpriteObject sprite_loot;
SDL_Rect     divider_level_beaten_rect;

/* Fonts */
SDL_Color color_white  = { 255, 255, 255 };
SDL_Color color_black  = {   0,   0,   0 };
SDL_Color color_red    = { 255,   0,   0 };
SDL_Color color_gray   = { 102, 102, 102 };
SDL_Color color_orange = { 255, 204,   0 };
SDL_Color color_brown  = { 153, 102,   0 };
TTF_Font *font_serif_brown_6;
TextCharObject textChars_font_serif_brown_6[122 + 1 - 32];
TTF_Font *font_serif_brown_8;
TextCharObject textChars_font_serif_brown_8[126 + 1 - 32];
TTF_Font *font_serif_gray_6;
TextCharObject textChars_font_serif_gray_6[126 + 1 - 32];
TTF_Font *font_serif_gray_12;
TextCharObject textChars_font_serif_gray_12[90 + 1 - 32];
TTF_Font *font_serif_orange_6;
TextCharObject textChars_font_serif_orange_6[90 + 1 - 32];
TTF_Font *font_serif_red_6;
TextCharObject textChars_font_serif_red_6[126 + 1 - 32];
TTF_Font *font_serif_red_8;
TextCharObject textChars_font_serif_red_8[126 + 1 - 32];
TTF_Font *font_serif_red_12;
TextCharObject textChars_font_serif_red_12[90 + 1 - 32];
TTF_Font *font_serif_white_6;
TextCharObject textChars_font_serif_white_6[126 + 1 - 32];
TTF_Font *font_serif_white_9;
TextCharObject textChars_font_serif_white_9[126 + 1 - 32];
TTF_Font *font_serif_white_10;
TextCharObject textChars_font_serif_white_10[126 + 1 - 32];
TTF_Font *font_serif_white_14;
TextCharObject textChars_font_serif_white_14[126 + 1 - 32];
TTF_Font *font_nokia_12;
TextCharObject textChars_font_nokia_12[126 + 1 - 32];
//TTF_Font *font_serif_2_bold_black_23;
//TextCharObject textChars_font_serif_2_bold_black_23[90 + 1 - 32];
//TTF_Font *font_serif_2_bold_red_23;
//TextCharObject textChars_font_serif_2_bold_red_23[90 + 1 - 32];
TTF_Font *font_serif_2_red_6;
TextCharObject textChars_font_serif_2_red_6[90 + 1 - 32];
TTF_Font *font_serif_2_red_13;
TextCharObject textChars_font_serif_2_red_13[90 + 1 - 32];

/* Text Objects */
char tempCharArray[64];
Uint8 charCounter;
Sint16 charWidthCounter;
std::stringstream ss;
string tempStr;
TextObject text_0_loading;
SDL_Rect text_0_loading_censor_rect;
TextObject text_1_presents;
TextObject text_3_click_anywhere_to_start;
//TextObject text_3_programmed;
//TextObject text_3_designed;
TextObject text_3_page;
TextObject text_3_instructions_1;
TextObject text_3_instructions_2;
TextObject text_3_instructions_3;
TextObject text_3_instructions_4;
TextObject text_3_instructions_5;
TextObject text_3_hints_1;
TextObject text_3_hints_2;
TextObject text_3_hints_3;
TextObject text_3_hints_4;
TextObject text_3_hints_5;
TextObject text_3_hints_6;
TextObject text_3_hints_7;
TextObject text_3_credits_1;
TextObject text_3_credits_2;
TextObject text_3_credits_3;
TextObject text_3_credits_4;
TextObject text_3_credits_5;
TextObject text_3_credits_6;
TextObject text_3_credits_7;
TextObject text_4_score_val;
TextObject text_4_mans_val;
TextObject text_4_level_val;
TextObject text_4_score;
TextObject text_4_mans;
TextObject text_4_level;
TextObject text_4_burninate_black;
TextObject text_4_burninate_red;
TextObject text_6_paused_1;
TextObject text_6_paused_2;
TextObject text_9_level_gray;
TextObject text_9_beaten_gray;
TextObject text_9_level_red;
TextObject text_9_beaten_red;
TextObject text_9_nice_work;
TextObject text_10_again_gray;
TextObject text_10_challenge_gray;
TextObject text_10_again_white;
TextObject text_10_challenge_white;
TextObject text_10_again_red;
TextObject text_10_challenge_red;
TextObject text_10_again_orange;
TextObject text_10_challenge_orange;
TextObject text_10_its_over_gray;
TextObject text_10_its_over_red;
TextObject text_10_username_val;
TextObject text_10_enter_initials;
TextObject text_10_send_em;
TextObject text_10_hi_scores_gray;
TextObject text_10_view_gray;
TextObject text_10_hi_scores_white;
TextObject text_10_view_white;
TextObject text_10_hi_scores_red;
TextObject text_10_view_red;
TextObject text_10_hi_scores_orange;
TextObject text_10_view_orange;
TextObject text_11_cutscene;
TextObject text_12_cutscene;
TextObject text_13_cutscene;
TextObject text_14_cutscene;
TextObject text_15_cutscene;
TextObject text_16_cutscene;
TextObject text_17_cutscene;
TextObject text_18_cutscene;
TextObject text_19_cutscene;
TextObject text_20_cutscene;
TextObject text_21_cutscene;
TextObject text_22_cutscene;
TextObject text_23_congratulations;
TextObject text_23_you_got;
TextObject text_23_good_score;
TextObject text_23_cast;
TextObject text_23_trogdor;
TextObject text_23_perez;
TextObject text_23_hackworth;
TextObject text_23_the_steve;
TextObject text_23_the_blue_knight;
TextObject text_23_the_red_knight;
TextObject text_23_the_siamese;
TextObject text_23_archers;
TextObject text_23_and_wordly_wise;
TextObject text_23_as_the_kerrek;
TextObject text_23_keep_playing;
TextObject text_25_ye_olde_high_scores;
TextObject text_25_name;
TextObject text_25_level;
TextObject text_25_score;
TextObject text_25_name_1_val;
TextObject text_25_level_1_val;
TextObject text_25_score_1_val;
TextObject text_25_1;
TextObject text_25_name_2_val;
TextObject text_25_level_2_val;
TextObject text_25_score_2_val;
TextObject text_25_2;
TextObject text_25_name_3_val;
TextObject text_25_level_3_val;
TextObject text_25_score_3_val;
TextObject text_25_3;
TextObject text_25_name_4_val;
TextObject text_25_level_4_val;
TextObject text_25_score_4_val;
TextObject text_25_4;
TextObject text_25_name_5_val;
TextObject text_25_level_5_val;
TextObject text_25_score_5_val;
TextObject text_25_5;
TextObject text_25_name_6_val;
TextObject text_25_level_6_val;
TextObject text_25_score_6_val;
TextObject text_25_6;
TextObject text_25_name_7_val;
TextObject text_25_level_7_val;
TextObject text_25_score_7_val;
TextObject text_25_7;
TextObject text_25_name_8_val;
TextObject text_25_level_8_val;
TextObject text_25_score_8_val;
TextObject text_25_8;
TextObject text_25_name_9_val;
TextObject text_25_level_9_val;
TextObject text_25_score_9_val;
TextObject text_25_9;
TextObject text_25_name_10_val;
TextObject text_25_level_10_val;
TextObject text_25_score_10_val;
TextObject text_25_10;

/* Window */
#if !defined(SDL1)
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *gameTexture;
#endif
SDL_Surface *gameScreen;
SDL_Rect gameWindowDstRect = { 0, 0, DEFAULT_GAME_WIDTH, DEFAULT_GAME_HEIGHT };
SDL_Rect appScreenRect;
SDL_Rect topRect;
SDL_Rect bottomRect;
SDL_Rect leftRect;
SDL_Rect rightRect;
bool isWindowed = true;
double screenScale = 1;
bool isIntegerScale = true;
#if !defined(SDL1)
SDL_DisplayMode DM;
#endif
double gameWidthMult;
double gameHeightMult;
Uint16 frameRate;

/* Save File */
SDL_RWops *saveFile;
SoundSettings soundSettings;
VideoSettings videoSettings;



void InitializeDisplay() {
#if !defined(SDL1)
	SDL_GetCurrentDisplayMode(0, &DM);
#endif
#if !defined(ANDROID)
	switch (videoSettings.aspectRatioIndex) {
		case 1:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_9[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_16_9)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_9[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_16_9)];
			break;
		case 2:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_10[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_16_10)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_10[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_16_10)];
			break;
		case 3:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_21_9[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_21_9)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_21_9[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_21_9)];
			break;
		default:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_4_3[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_4_3)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_4_3[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_4_3)];
			break;
	}
#else
	videoSettings.widthSetting = SYSTEM_WIDTH;
	videoSettings.heightSetting = SYSTEM_HEIGHT;
	SDL_SetHint(SDL_HINT_ORIENTATIONS, "Landscape");
#endif
	videoSettings.widthSetting = 640;
	videoSettings.heightSetting = 480;
	setWidthHeightMults();
	frameRate = DEFAULT_FRAME_RATE;

	/* Set Window/Renderer */
#if defined(PSP)
	window = SDL_CreateWindow("Trogdor Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, videoSettings.widthSetting, videoSettings.heightSetting, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	gameSurface = SDL_CreateRGBSurface(0, DEFAULT_GAME_WIDTH, DEFAULT_GAME_HEIGHT, 24, 0, 0, 0, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#elif defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID)
	window = SDL_CreateWindow("Trogdor Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, videoSettings.widthSetting, videoSettings.heightSetting, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	gameSurface = SDL_CreateRGBSurface(0, DEFAULT_GAME_WIDTH, DEFAULT_GAME_HEIGHT, 24, 0, 0, 0, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#elif defined(WII) || defined(GAMECUBE)
	SDL_WM_SetCaption("Trogdor Reburninated", NULL);
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
	gameScreen = SDL_SetVideoMode(GAME_WIDTH, GAME_HEIGHT, 24, SDL_DOUBLEBUF);
#elif defined(SDL1)
	SDL_WM_SetCaption("Trogdor Reburninated", NULL);
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
	gameScreen = SDL_SetVideoMode(GAME_WIDTH, GAME_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
#else
	window = SDL_CreateWindow("Trogdor Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, videoSettings.widthSetting, videoSettings.heightSetting, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	gameScreen = SDL_CreateRGBSurface(0, DEFAULT_GAME_WIDTH, DEFAULT_GAME_HEIGHT, 24, 0, 0, 0, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#endif
	setScaling();
}

void InitializeSound() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
#if !defined(SDL1) && !defined(ANDROID)
		SDL_Log(Mix_GetError());
#endif
	}
	Mix_VolumeMusic((int)(soundSettings.bgmVolume * 128.0 / 100));
	Mix_AllocateChannels(8);
	Mix_Volume(SFX_CHANNEL_GAME, (int)(soundSettings.sfxVolume * 128.0 / 100));
	Mix_Volume(SFX_CHANNEL_STRONG_BAD, (int)(soundSettings.sfxVolume * 128.0 / 100));
}

void InitializeMusic() {
	music_title_screen = Mix_LoadWAV((rootDir + "music/title_screen.wav").c_str());
}

void InitializeSFX() {
	sfx_burn_hut = Mix_LoadWAV((rootDir + "sfx/burn_hut.wav").c_str());
	sfx_goldget = Mix_LoadWAV((rootDir + "sfx/trog_goldget.wav").c_str());
	sfx_peasantscream = Mix_LoadWAV((rootDir + "sfx/trog_peasantscream.wav").c_str());
	sfx_sb1 = Mix_LoadWAV((rootDir + "sfx/trog_sb1.wav").c_str());
	sfx_sb2 = Mix_LoadWAV((rootDir + "sfx/trog_sb2.wav").c_str());
	sfx_sb3 = Mix_LoadWAV((rootDir + "sfx/trog_sb3.wav").c_str());
	sfx_sb4 = Mix_LoadWAV((rootDir + "sfx/trog_sb4.wav").c_str());
	sfx_sb5 = Mix_LoadWAV((rootDir + "sfx/trog_sb5.wav").c_str());
	sfx_sb6 = Mix_LoadWAV((rootDir + "sfx/trog_sb6.wav").c_str());
	sfx_sb7 = Mix_LoadWAV((rootDir + "sfx/trog_sb7.wav").c_str());
	sfx_sbarch = Mix_LoadWAV((rootDir + "sfx/trog_sbarch.wav").c_str());
	sfx_sbarchend = Mix_LoadWAV((rootDir + "sfx/trog_sbarchend.wav").c_str());
	sfx_sbbest = Mix_LoadWAV((rootDir + "sfx/trog_sbbest.wav").c_str());
	sfx_sbdooj = Mix_LoadWAV((rootDir + "sfx/trog_sbdooj.wav").c_str());
	sfx_sbgameover = Mix_LoadWAV((rootDir + "sfx/trog_sbgameover.wav").c_str());
	sfx_sbkerrek = Mix_LoadWAV((rootDir + "sfx/trog_sbkerrek.wav").c_str());
	sfx_sblevelbeat = Mix_LoadWAV((rootDir + "sfx/trog_sblevelbeat.wav").c_str());
	sfx_sbscore = Mix_LoadWAV((rootDir + "sfx/trog_sbscore.wav").c_str());
	sfx_sbsecret = Mix_LoadWAV((rootDir + "sfx/trog_sbsecret.wav").c_str());
	sfx_sbsquish1 = Mix_LoadWAV((rootDir + "sfx/trog_sbsquish1.wav").c_str());
	sfx_sbsquish2 = Mix_LoadWAV((rootDir + "sfx/trog_sbsquish2.wav").c_str());
	sfx_sbwin = Mix_LoadWAV((rootDir + "sfx/trog_sbwin.wav").c_str());
	sfx_sbwin2 = Mix_LoadWAV((rootDir + "sfx/trog_sbwin2.wav").c_str());
	sfx_sbworst = Mix_LoadWAV((rootDir + "sfx/trog_sbworst.wav").c_str());
	sfx_sfx2 = Mix_LoadWAV((rootDir + "sfx/trog_sfx2.wav").c_str());
	sfx_trogador = Mix_LoadWAV((rootDir + "sfx/trogador.wav").c_str());
	sfx_arrow = Mix_LoadWAV((rootDir + "sfx/arrow.wav").c_str());
	sfx_squish = Mix_LoadWAV((rootDir + "sfx/squish.wav").c_str());
	sfx_death = Mix_LoadWAV((rootDir + "sfx/death.wav").c_str());
	sfx_kick = Mix_LoadWAV((rootDir + "sfx/kick.wav").c_str());
	sfx_burninate = Mix_LoadWAV((rootDir + "sfx/burninate.wav").c_str());
	sfx_cutscene = Mix_LoadWAV((rootDir + "sfx/cutscene.wav").c_str());
	sfx_gameover = Mix_LoadWAV((rootDir + "sfx/gameover.wav").c_str());
}

void InitializeSpritesPart1() {
	PREPARE_SPRITE(sprite_videlectrix_logo, (rootDir + "graphics/videlectrix_logo.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_videlectrix_logo), OBJ_TO_MID_SCREEN_Y(sprite_videlectrix_logo), 1, 1, (221.0 / 300));
	// I'm gonna be lazy and just use the title screen directly instead of its separate components
	PREPARE_SPRITE(sprite_title_screen, (rootDir + "graphics/title_screen.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_title_screen), OBJ_TO_MID_SCREEN_Y(sprite_title_screen), 1, 1, 1);
	PREPARE_SPRITE(sprite_trogdor_logo, (rootDir + "graphics/trogdor_logo.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_trogdor_logo), OBJ_TO_SCREEN_AT_FRACTION_Y(sprite_trogdor_logo, 0.1666), 1, 1, 1);
	// ((2466 + 23) / 5000.0) = 0.4978
	// (2466 / 5000.0) = 0.4932
	// ((2183 - 133) / 3600.0) = 0.5694
	// (2183 / 3600.0) = 0.6064
	PREPARE_SPRITE(sprite_level_background_1, (rootDir + "graphics/backgrounds/1.bmp").c_str(),
		OBJ_TO_SCREEN_AT_FRACTION_X(sprite_level_background_1, 0.4978), OBJ_TO_SCREEN_AT_FRACTION_Y(sprite_level_background_1, 0.573), 1, 1, 1);
	PREPARE_SPRITE(sprite_level_background_2, (rootDir + "graphics/backgrounds/2.bmp").c_str(),
		OBJ_TO_SCREEN_AT_FRACTION_X(sprite_level_background_2, 0.4978), OBJ_TO_SCREEN_AT_FRACTION_Y(sprite_level_background_2, 0.573), 1, 1, 1);
	PREPARE_SPRITE(sprite_level_background_3, (rootDir + "graphics/backgrounds/3.bmp").c_str(),
		OBJ_TO_SCREEN_AT_FRACTION_X(sprite_level_background_3, 0.4978), OBJ_TO_SCREEN_AT_FRACTION_Y(sprite_level_background_3, 0.573), 1, 1, 1);
	PREPARE_SPRITE(sprite_level_background_4, (rootDir + "graphics/backgrounds/4.bmp").c_str(),
		OBJ_TO_SCREEN_AT_FRACTION_X(sprite_level_background_4, 0.4932), OBJ_TO_SCREEN_AT_FRACTION_Y(sprite_level_background_4, 0.6064), 1, 1, 1);
	PREPARE_SPRITE(sprite_level_background_th, (rootDir + "graphics/backgrounds/treasure_hut.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_level_background_th), OBJ_TO_SCREEN_AT_FRACTION_Y(sprite_level_background_th, 0.567), 1, 1, 1);
}

void InitializeSpritesPart2() {
	PREPARE_SPRITE(sprite_trogdor, (rootDir + "graphics/trogdor.bmp").c_str(),
		0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_burnination_meter_full, (rootDir + "graphics/burnination_meter/full.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_burnination_meter_full), 8, 1, 1, 1);
	PREPARE_SPRITE(sprite_burnination_meter_empty, (rootDir + "graphics/burnination_meter/empty.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_burnination_meter_empty), 8, 1, 1, 1);
	PREPARE_SPRITE(sprite_cottage, (rootDir + "graphics/cottage.bmp").c_str(),
		0, 0, 2, 4, 1);
	PREPARE_SPRITE(sprite_cottage_fire, (rootDir + "graphics/cottage_fire.bmp").c_str(),
		0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_peasantometer_icon, (rootDir + "graphics/peasantometer.bmp").c_str(),
		0, 3, 2, 1, 1);
	sprite_peasantometer_icon_init_x = (Uint8)(GAME_WIDTH * 66 / 250);
	PREPARE_SPRITE(sprite_archer, (rootDir + "graphics/archer.bmp").c_str(),
		0, 0, 2, 2, 1);
	PREPARE_SPRITE(sprite_arrow, (rootDir + "graphics/arrow.bmp").c_str(),
		0, 0, 1, 2, 1);
	PREPARE_SPRITE(sprite_trogdor_fire, (rootDir + "graphics/trogdor_fire.bmp").c_str(),
		0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_trogdor_dead, (rootDir + "graphics/trogdor_dead.bmp").c_str(),
		0, 0, 2, 1, 1);
	PREPARE_SPRITE(sprite_knight, (rootDir + "graphics/knight.bmp").c_str(),
		0, 0, 3, 2, 1);
	PREPARE_SPRITE(sprite_peasant, (rootDir + "graphics/peasant.bmp").c_str(),
		0, 0, 2, 3, 1);
	PREPARE_SPRITE(sprite_end_of_level_flash, (rootDir + "graphics/end_of_level_flash.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_end_of_level_flash), OBJ_TO_MID_SCREEN_Y(sprite_end_of_level_flash), 1, 1, 1);
	PREPARE_SPRITE(sprite_end_of_level_trogdor, (rootDir + "graphics/end_of_level_trogdor.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_end_of_level_trogdor), OBJ_TO_MID_SCREEN_Y(sprite_end_of_level_trogdor), 1, 1, 1);
	PREPARE_SPRITE(sprite_death_message, (rootDir + "graphics/death_message.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_death_message), OBJ_TO_MID_SCREEN_Y(sprite_death_message), 2, 5, 1);
	PREPARE_SPRITE(sprite_burninate_text, (rootDir + "graphics/burninate_text.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_burninate_text), OBJ_TO_MID_SCREEN_Y(sprite_burninate_text), 1, 1, 1);
	PREPARE_SPRITE(sprite_burninate_fire, (rootDir + "graphics/burninate_message_fire.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_burninate_fire), OBJ_TO_MID_SCREEN_Y(sprite_burninate_fire), 1, 14, 1);
	PREPARE_SPRITE(sprite_loot, (rootDir + "graphics/loot.bmp").c_str(),
		0, 0, 1, 1, 1);
	divider_level_beaten_rect = { 0, 25, GAME_WIDTH, 2 };
}

void InitializeTextChars() {
	setFont(font_serif_brown_6, "fonts/serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_brown_6, color_brown, 32, 122);
	TTF_CloseFont(font_serif_brown_6);
	setFont(font_serif_brown_8, "fonts/serif_v01.ttf", 8,
		TTF_STYLE_NORMAL, textChars_font_serif_brown_8, color_brown, 32, 126);
	TTF_CloseFont(font_serif_brown_8);
	setFont(font_serif_gray_6, "fonts/serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_gray_6, color_gray, 32, 126);
	TTF_CloseFont(font_serif_gray_6);
	setFont(font_serif_gray_12, "fonts/serif_v01.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_serif_gray_12, color_gray, 32, 90);
	TTF_CloseFont(font_serif_gray_12);
	setFont(font_serif_orange_6, "fonts/serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_orange_6, color_orange, 32, 90);
	TTF_CloseFont(font_serif_orange_6);
	setFont(font_serif_red_6, "fonts/serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_red_6, color_red, 32, 126);
	TTF_CloseFont(font_serif_red_6);
	setFont(font_serif_red_8, "fonts/serif_v01.ttf", 8,
		TTF_STYLE_NORMAL, textChars_font_serif_red_8, color_red, 32, 126);
	TTF_CloseFont(font_serif_red_8);
	setFont(font_serif_red_12, "fonts/serif_v01.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_serif_red_12, color_red, 32, 90);
	TTF_CloseFont(font_serif_red_12);
	setFont(font_serif_white_6, "fonts/serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_white_6, color_white, 32, 126);
	TTF_CloseFont(font_serif_white_6);
	setFont(font_serif_white_9, "fonts/serif_v01.ttf", 9,
		TTF_STYLE_NORMAL, textChars_font_serif_white_9, color_white, 32, 126);
	TTF_CloseFont(font_serif_white_9);
	setFont(font_serif_white_10, "fonts/serif_v01.ttf", 10,
		TTF_STYLE_NORMAL, textChars_font_serif_white_10, color_white, 32, 126);
	TTF_CloseFont(font_serif_white_10);

	setFont(font_nokia_12, "fonts/29_NOKIA 5110 FontSet.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_nokia_12, color_white, 97, 126);
	TTF_CloseFont(font_nokia_12);

	//setFont(font_serif_2_bold_black_23, "fonts/54_serif_v01.ttf", 23,
	//	TTF_STYLE_BOLD, textChars_font_serif_2_bold_black_23, color_black, 32, 90);
	//TTF_CloseFont(font_serif_2_bold_black_23);
	//setFont(font_serif_2_bold_red_23, "fonts/54_serif_v01.ttf", 23,
	//	TTF_STYLE_BOLD, textChars_font_serif_2_bold_red_23, color_red, 32, 90);
	//TTF_CloseFont(font_serif_2_bold_red_23);
	setFont(font_serif_2_red_6, "fonts/54_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_2_red_6, color_red, 32, 90);
	TTF_CloseFont(font_serif_2_red_6);
	setFont(font_serif_2_red_13, "fonts/54_serif_v01.ttf", 13,
		TTF_STYLE_NORMAL, textChars_font_serif_2_red_13, color_red, 32, 90);
	TTF_CloseFont(font_serif_2_red_13);

	TTF_Quit();
}

void InitializeTextObjects() {
	/* 1: Videlectrix Logo */
	SET_TEXT("presents", text_1_presents, textChars_font_nokia_12,
		OBJ_TO_MID_SCREEN_X(text_1_presents), OBJ_TO_SCREEN_AT_FRACTION_Y(text_1_presents, 0.7));
	/* 2: Title Screen */
	/* 3: Instructions Screen */
	SET_TEXT("click anywhere to START", text_3_click_anywhere_to_start, textChars_font_serif_red_8,
		OBJ_TO_MID_SCREEN_X(text_3_click_anywhere_to_start), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_click_anywhere_to_start, 0.75));
	// Use a separate credits page instead of these
	//SET_TEXT("Programmed by Jonathan Howe", text_3_programmed, textChars_font_serif_white_6,
	//	OBJ_TO_MID_SCREEN_X(text_3_programmed), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_programmed, 0.85));
	//SET_TEXT("Designed by Mike and Matt", text_3_designed, textChars_font_serif_white_6,
	//	OBJ_TO_MID_SCREEN_X(text_3_designed), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_designed, 0.93));
	SET_TEXT("(1/3)", text_3_page, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_page), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_page, 0.95));
	SET_TEXT("Use the arrow keys to control Trogdor", text_3_instructions_1, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_instructions_1), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_instructions_1, 0.35));
	SET_TEXT("Stomp 10 peasants to achieve burnination.", text_3_instructions_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_instructions_2), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_instructions_2, 0.43));
	SET_TEXT("Burn all cottages to advance a level.", text_3_instructions_3, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_instructions_3), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_instructions_3, 0.51));
	SET_TEXT("Avoid knights and archers!", text_3_instructions_4, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_instructions_4), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_instructions_4, 0.59));
	SET_TEXT("Press SPACE to pause.", text_3_instructions_5, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_instructions_5), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_instructions_5, 0.67));
	SET_TEXT("SECRET HINTS!!", text_3_hints_1, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_1), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_hints_1, 0.39));
	SET_TEXT("-Don't let the peasants return to their cottages", text_3_hints_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_2), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_hints_2, 0.51));
	SET_TEXT("-Once you\'re burninating, you\'re invincible", text_3_hints_3, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_3), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_hints_3, 0.58));
	SET_TEXT("-Burninated peasants set their cottages on fire", text_3_hints_4, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_4), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_hints_4, 0.65));
	SET_TEXT("-Get an extra man every 300 points", text_3_hints_5, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_5), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_hints_5, 0.72));
	SET_TEXT("-What\'s a treasure hut?!?!", text_3_hints_6, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_6), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_hints_6, 0.79));
	SET_TEXT("- Secret Code?!?!", text_3_hints_7, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_7), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_hints_7, 0.86));

	SET_TEXT("CREDITS", text_3_credits_1, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(text_3_credits_1), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_credits_1, 0.35));
	SET_TEXT("ORIGINAL FLASH GAME", text_3_credits_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_credits_2), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_credits_2, 0.43));
	SET_TEXT("Programming: Jonathan Howe", text_3_credits_3, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_credits_3), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_credits_3, 0.51));
	// credits for the HTML5 version will be added when stuff from the HTML5 version is added to this version
	SET_TEXT("Design: Mike Chapman, Matt Chapman", text_3_credits_4, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_credits_4), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_credits_4, 0.59));
	SET_TEXT("THIS PORT", text_3_credits_5, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_credits_5), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_credits_5, 0.69));
	SET_TEXT("Mips96", text_3_credits_6, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_credits_6), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_credits_6, 0.77));
	SET_TEXT("https://github.com/Mips96/Trogdor-Reburninated", text_3_credits_7, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_credits_7), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_credits_7, 0.85));
	/* 4: Game */
	SET_TEXT("SCORE:", text_4_score, textChars_font_serif_2_red_6,
		10, 1);
	SET_TEXT("012345", text_4_score_val, textChars_font_serif_red_6,
		10, 14);
	SET_TEXT("MANS:", text_4_mans, textChars_font_serif_2_red_6,
		200, 4);
	SET_TEXT("67", text_4_mans_val, textChars_font_serif_red_6,
		230, 1);
	SET_TEXT("LEVEL:", text_4_level, textChars_font_serif_2_red_6,
		195, 14);
	SET_TEXT("89", text_4_level_val, textChars_font_serif_red_6,
		230, 11);
	/* 5: Nothing? (or maybe Game) */
	/* 6: Pause Screen (overlayed on Game) */
	SET_TEXT("paused", text_6_paused_1, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_6_paused_1), 145);
	SET_TEXT("press 'SPACE' to resume", text_6_paused_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_6_paused_2), 160);
	/* 7: Nothing */
	/* 8: End of Level Animation */
	/* 9: Level Beaten Screen */
	SET_TEXT("nice work!", text_9_nice_work, textChars_font_serif_white_10,
		(GAME_WIDTH * 0.55), (GAME_HEIGHT * 0.45));
	/* 10: Game Over Screen */
	/* 11: Level 4 Interlude */
	SET_TEXT("stompin' good!", text_11_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_11_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_11_cutscene, 0.25));
	/* 12: Level 8 Interlude */
	SET_TEXT("fry 'em up dan.", text_12_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_12_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_12_cutscene, 0.25));
	/* 13: Level 12 Interlude */
	SET_TEXT("parade of trogdors", text_13_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_13_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_13_cutscene, 0.25));
	/* 14: Level 16 Interlude */
	SET_TEXT("dancin' time", text_14_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_14_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_14_cutscene, 0.25));
	/* 15: Level 20 Interlude */
	SET_TEXT("flex it, troggie.", text_15_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_15_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_15_cutscene, 0.25));
	/* 16: Level 24 Interlude */
	SET_TEXT("peasant dominoes", text_16_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_16_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_16_cutscene, 0.25));
	/* 17: Level 30 Interlude */
	SET_TEXT("trogdor incognito", text_17_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_17_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_17_cutscene, 0.25));
	/* 18: Level 34 Interlude */
	SET_TEXT("go trogdor # 2!", text_18_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_18_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_18_cutscene, 0.25));
	/* 19: Level 38 Interlude */
	SET_TEXT("forbidden peasant love", text_19_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_19_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_19_cutscene, 0.25));
	/* 20: Level 42 Interlude */
	SET_TEXT("2 cottages", text_20_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_20_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_20_cutscene, 0.25));
	/* 21: Level 46 Interlude */
	SET_TEXT("a funny joke", text_21_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_21_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_21_cutscene, 0.25));
	/* 22: Level 50 Interlude */
	SET_TEXT("smote that kerrek!", text_22_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_22_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(text_22_cutscene, 0.25));
	/* 23: Level 100 Interlude (Credits) */
	/* 24: Nothing? (or maybe blank transition from Credits to High Scores Screen) */
	/* 25: High Scores Screen */

	//SET_TEXT("nice work!", text_nice_work, textChars_font_serif_white_10,
	//	OBJ_TO_MID_SCREEN_X(text_nice_work), OBJ_TO_MID_SCREEN_Y(text_nice_work));
	//SET_TEXT("send'em", text_send_em, textChars_font_serif_gray_6,
	//	OBJ_TO_MID_SCREEN_X(text_send_em), OBJ_TO_MID_SCREEN_Y(text_send_em));
	//SET_TEXT("stompin' good!", text_stompin_good, textChars_font_serif_white_9,
	//	OBJ_TO_MID_SCREEN_X(text_stompin_good), OBJ_TO_MID_SCREEN_Y(text_stompin_good));
	//SET_TEXT("YE       OLDE       HI-SCORES", text_ye_olde_hi_scores, textChars_font_serif_2_red_13,
	//	OBJ_TO_MID_SCREEN_X(text_ye_olde_hi_scores), OBJ_TO_MID_SCREEN_Y(text_ye_olde_hi_scores));
	//SET_TEXT("1", text_one, textChars_font_serif_brown_8,
	//	OBJ_TO_MID_SCREEN_X(text_one), OBJ_TO_MID_SCREEN_Y(text_one));
}

void InitializeController() {
#if defined(PSP)
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	joystick = SDL_JoystickOpen(0);
#elif defined(SDL1)
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
#else
	for (i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			break;
		}
	}
#endif
}

void renderBackground() {
	SDL_BlitSurface(sprite_level_background->surface, NULL, gameScreen, &sprite_level_background->dstrect);
}

void renderTransparentForeground() {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	SDL_Surface *screen_transparent = SDL_CreateRGBSurface(0,
		GAME_WIDTH, GAME_HEIGHT, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#else
	SDL_Surface *screen_transparent = SDL_CreateRGBSurface(0,
		GAME_WIDTH, GAME_HEIGHT, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
#endif
	SDL_FillRect(screen_transparent, NULL, 0xC8000000);
	SDL_BlitSurface(screen_transparent, NULL, gameScreen, &appScreenRect);
	SDL_FreeSurface(screen_transparent);
}



void destroyTextChars(TextCharObject textChars[]) {
	for (i = 0; i < LEN(textChars); i++) {
		SDL_FreeSurface(textChars[i].surface);
	}
}

void destroySprite(SpriteObject sprite) {
	SDL_FreeSurface(sprite.surface);
}

void closeController() {
#if defined(PSP) || defined(SDL1)
	if (SDL_JoystickOpened(0)) {
		SDL_JoystickClose(joystick);
	}
#else
	if (controller != NULL) {
		SDL_GameControllerClose(controller);
	}
#endif
}

void destroyDisplay() {
#if !defined(SDL1)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
#endif
	SDL_FreeSurface(gameScreen);
}

void DestroyAll() {
	/* Textures */
	/* Text Chars */
	//destroyTextChars(textChars_font_serif_brown_6);
	//destroyTextChars(textChars_font_serif_brown_8);
	//destroyTextChars(textChars_font_serif_gray_6);
	////destroyTextChars(textChars_font_serif_gray_12);
	//destroyTextChars(textChars_font_serif_orange_6);
	//destroyTextChars(textChars_font_serif_red_6);
	//destroyTextChars(textChars_font_serif_red_8);
	////destroyTextChars(textChars_font_serif_red_12);
	//destroyTextChars(textChars_font_serif_white_6);
	//destroyTextChars(textChars_font_serif_white_9);
	//destroyTextChars(textChars_font_serif_white_10);
	//destroyTextChars(textChars_font_serif_white_14);
	//destroyTextChars(textChars_font_nokia_12);
	////destroyTextChars(textChars_font_serif_2_bold_black_23);
	////destroyTextChars(textChars_font_serif_2_bold_red_23);
	//destroyTextChars(textChars_font_serif_2_red_6);
	//destroyTextChars(textChars_font_serif_2_red_13);
	/* Sound */
	if (soundSettings.musicIndex != 0) {
		Mix_FreeMusic(bgm);
	}
	Mix_FreeChunk(sfx_trogador);
	Mix_CloseAudio();
#if !defined(WII) && !defined(GAMECUBE)
	Mix_Quit();
#endif
	/* Controller */
	closeController();
	/* Renderer/Screen and Window */
	destroyDisplay();
	SDL_Quit();
	SYSTEM_SPECIFIC_CLOSE();
}

#endif