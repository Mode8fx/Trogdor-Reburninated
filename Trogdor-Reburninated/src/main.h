#ifndef MAIN_H
#define MAIN_H

#include "media_objects_init.h"
#include "system_specific_macros.h"

/* SDL Window */
#if !defined(SDL1)
SDL_Window *window;
SDL_Renderer *renderer;
#else
SDL_Surface *screen;
#endif
SDL_Event event;

/* General Input */
Uint32 keyInputs;

/* SDL Input */
#if !defined(SDL1)
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
#if !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(WII) && !defined(GAMECUBE)
Sint32 mouseInput_x;
Sint32 mouseInput_x_last;
Sint32 mouseInput_y;
Sint32 mouseInput_y_last;
#endif
Uint32 heldKeys;

/* Audio */
SoundSettings soundSettings;
Mix_Music *bgm;
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
TTF_Font *font_serif_2_bold_black_23;
TextCharObject textChars_font_serif_2_bold_black_23[90 + 1 - 32];
TTF_Font *font_serif_2_bold_red_23;
TextCharObject textChars_font_serif_2_bold_red_23[90 + 1 - 32];
TTF_Font *font_serif_2_red_6;
TextCharObject textChars_font_serif_2_red_6[90 + 1 - 32];
TTF_Font *font_serif_2_red_13;
TextCharObject textChars_font_serif_2_red_13[90 + 1 - 32];

/* Text Objects */
char tempCharArray[64];
Uint8 charCounter;
Uint16 charWidthCounter;
std::stringstream ss;
string tempStr;
TextObject text_0_loading;
SDL_Rect text_0_loading_censor_rect;
TextObject text_1_presents;
TextObject text_3_click_anywhere_to_start;
TextObject text_3_programmed;
TextObject text_3_designed;
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

/* SDL Save File */
SDL_RWops *saveFile;

/* System-Specific Variables */
#if defined(VITA)
string rootDir = "ux0:data/TrogdorRB/";
#elif defined(WII) || defined(GAMECUBE)
string rootDir = "sd:/apps/TrogdorRB/";
#else
string rootDir = "";
#endif

/* Other */
Uint16 gameWidth;
Uint16 gameHeight;
double gameWidthMult;
double gameHeightMult;
Uint16 frameRate;

void InitializeDisplay() {
	gameWidth = DEFAULT_GAME_WIDTH;
	gameHeight = DEFAULT_GAME_HEIGHT;
	SET_WIDTH_HEIGHT_MULTS();
	frameRate = DEFAULT_FRAME_RATE;

	/* Set Window/Renderer */
#if !defined(SDL1)
	window = SDL_CreateWindow("Trogdor Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWidth, gameHeight, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#elif defined(WII) || defined(GAMECUBE)
	SDL_WM_SetCaption("Trogdor Reburninated", NULL);
	screen = SDL_SetVideoMode(gameWidth, gameHeight, 24, SDL_DOUBLEBUF);
#else
	SDL_WM_SetCaption("Trogdor Reburninated", NULL);
	screen = SDL_SetVideoMode(gameWidth, gameHeight, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
#endif
}

void InitializeSound() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		PRINT(Mix_GetError());
	}
	Mix_VolumeMusic((int)(soundSettings.bgmVolume * 128.0 / 100));
	Mix_Volume(SFX_CHANNEL_GAME, (int)(soundSettings.sfxVolume * 128.0 / 100));
	Mix_Volume(SFX_CHANNEL_STRONG_BAD, (int)(soundSettings.sfxVolume * 128.0 / 100));
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
}

void InitializeSprites() {
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
		OBJ_TO_MID_SCREEN_X(sprite_level_background_th), OBJ_TO_MID_SCREEN_Y(sprite_level_background_th), 1, 1, 1);
	PREPARE_SPRITE(sprite_trogdor, (rootDir + "graphics/trogdor.bmp").c_str(),
		0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_burnination_meter_full, (rootDir + "graphics/burnination_meter/full.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_burnination_meter_full), 8, 1, 1, 1);
	PREPARE_SPRITE(sprite_burnination_meter_empty, (rootDir + "graphics/burnination_meter/empty.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(sprite_burnination_meter_empty), 8, 1, 1, 1);
	PREPARE_SPRITE(sprite_cottage, (rootDir + "graphics/cottage.bmp").c_str(),
		0, 0, 2, 4, 1);
	PREPARE_SPRITE(sprite_cottage_fire, (rootDir + "graphics/cottage_fire.bmp").c_str(),
		0, 0, 4, 1, 1);
	PREPARE_SPRITE(sprite_peasantometer_icon, (rootDir + "graphics/peasantometer.bmp").c_str(),
		0, 3, 2, 1, 1);
	sprite_peasantometer_icon_init_x = (Uint8)(GAME_WIDTH * 66 / 250);
	PREPARE_SPRITE(sprite_archer, (rootDir + "graphics/archer.bmp").c_str(),
		0, 3, 2, 2, 1);
	PREPARE_SPRITE(sprite_arrow, (rootDir + "graphics/arrow.bmp").c_str(),
		0, 3, 1, 2, 1);
}

void InitializeTextChars() {
	TTF_Init();

	SET_FONT(font_serif_brown_6, "fonts/27_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_brown_6, color_brown, 32, 122);
	TTF_CloseFont(font_serif_brown_6);
	SET_FONT(font_serif_brown_8, "fonts/27_serif_v01.ttf", 8,
		TTF_STYLE_NORMAL, textChars_font_serif_brown_8, color_brown, 32, 126);
	TTF_CloseFont(font_serif_brown_8);
	SET_FONT(font_serif_gray_6, "fonts/27_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_gray_6, color_gray, 32, 126);
	TTF_CloseFont(font_serif_gray_6);
	SET_FONT(font_serif_gray_12, "fonts/27_serif_v01.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_serif_gray_12, color_gray, 32, 90);
	TTF_CloseFont(font_serif_gray_12);
	SET_FONT(font_serif_orange_6, "fonts/27_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_orange_6, color_orange, 32, 90);
	TTF_CloseFont(font_serif_orange_6);
	SET_FONT(font_serif_red_6, "fonts/27_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_red_6, color_red, 32, 126);
	TTF_CloseFont(font_serif_red_6);
	SET_FONT(font_serif_red_8, "fonts/27_serif_v01.ttf", 8,
		TTF_STYLE_NORMAL, textChars_font_serif_red_8, color_red, 32, 126);
	TTF_CloseFont(font_serif_red_8);
	SET_FONT(font_serif_red_12, "fonts/27_serif_v01.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_serif_red_12, color_red, 32, 90);
	TTF_CloseFont(font_serif_red_12);
	SET_FONT(font_serif_white_6, "fonts/27_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_white_6, color_white, 32, 126);
	TTF_CloseFont(font_serif_white_6);
	SET_FONT(font_serif_white_9, "fonts/27_serif_v01.ttf", 9,
		TTF_STYLE_NORMAL, textChars_font_serif_white_9, color_white, 32, 126);
	TTF_CloseFont(font_serif_white_9);
	SET_FONT(font_serif_white_10, "fonts/27_serif_v01.ttf", 10,
		TTF_STYLE_NORMAL, textChars_font_serif_white_10, color_white, 32, 126);
	TTF_CloseFont(font_serif_white_10);
	SET_FONT(font_serif_white_14, "fonts/27_serif_v01.ttf", 14,
		TTF_STYLE_NORMAL, textChars_font_serif_white_14, color_white, 32, 126);
	TTF_CloseFont(font_serif_white_14);

	SET_FONT(font_nokia_12, "fonts/29_NOKIA 5110 FontSet.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_nokia_12, color_white, 97, 126);
	TTF_CloseFont(font_nokia_12);

	SET_FONT(font_serif_2_bold_black_23, "fonts/54_serif_v01.ttf", 23,
		TTF_STYLE_BOLD, textChars_font_serif_2_bold_black_23, color_black, 32, 90);
	TTF_CloseFont(font_serif_2_bold_black_23);
	SET_FONT(font_serif_2_bold_red_23, "fonts/54_serif_v01.ttf", 23,
		TTF_STYLE_BOLD, textChars_font_serif_2_bold_red_23, color_red, 32, 90);
	TTF_CloseFont(font_serif_2_bold_red_23);
	SET_FONT(font_serif_2_red_6, "fonts/54_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_2_red_6, color_red, 32, 90);
	TTF_CloseFont(font_serif_2_red_6);
	SET_FONT(font_serif_2_red_13, "fonts/54_serif_v01.ttf", 13,
		TTF_STYLE_NORMAL, textChars_font_serif_2_red_13, color_red, 32, 90);
	TTF_CloseFont(font_serif_2_red_13);

	TTF_Quit();
}

void InitializeTextObjects() {
	/* 0: Loading Screen */
	SET_TEXT("loading...", text_0_loading, textChars_font_serif_white_14,
		OBJ_TO_MID_SCREEN_X(text_0_loading), OBJ_TO_MID_SCREEN_Y(text_0_loading));
	text_0_loading_censor_rect = { text_0_loading.dstrect.x, text_0_loading.dstrect.y,
		(Uint16)text_0_loading.dstrect.w, (Uint16)text_0_loading.dstrect.h };
	/* 1: Videlectrix Logo */
	SET_TEXT("presents", text_1_presents, textChars_font_nokia_12,
		OBJ_TO_MID_SCREEN_X(text_1_presents), OBJ_TO_SCREEN_AT_FRACTION_Y(text_1_presents, 0.7));
	/* 2: Title Screen */
	/* 3: Instructions Screen */
	SET_TEXT("click anywhere to START", text_3_click_anywhere_to_start, textChars_font_serif_red_8,
		OBJ_TO_MID_SCREEN_X(text_3_click_anywhere_to_start), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_click_anywhere_to_start, 0.75));
	SET_TEXT("Programmed by Jonathan Howe", text_3_programmed, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_programmed), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_programmed, 0.85));
	SET_TEXT("Designed by Mike and Matt", text_3_designed, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_designed), OBJ_TO_SCREEN_AT_FRACTION_Y(text_3_designed, 0.93));
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
		OBJ_TO_MID_SCREEN_X(text_3_hints_1), OBJ_TO_MID_SCREEN_Y(text_3_hints_1));
	SET_TEXT("-Don't let the peasants return to their cottages", text_3_hints_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_2), OBJ_TO_MID_SCREEN_Y(text_3_hints_2));
	SET_TEXT("-Once you\'re burninating, you\'re invincible", text_3_hints_3, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_3), OBJ_TO_MID_SCREEN_Y(text_3_hints_3));
	SET_TEXT("-Burninated peasants set their cottages on fire", text_3_hints_4, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_4), OBJ_TO_MID_SCREEN_Y(text_3_hints_4));
	SET_TEXT("-Get an extra man every 300 points", text_3_hints_5, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_5), OBJ_TO_MID_SCREEN_Y(text_3_hints_5));
	SET_TEXT("-What\'s a treasure hut?!?!", text_3_hints_6, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_6), OBJ_TO_MID_SCREEN_Y(text_3_hints_6));
	SET_TEXT("- Secret Code?!?!", text_3_hints_7, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(text_3_hints_7), OBJ_TO_MID_SCREEN_Y(text_3_hints_7));
	/* 4: Game */
	SET_TEXT("SCORE:", text_4_score, textChars_font_serif_2_red_6,
		10, 4);
	SET_TEXT("012345", text_4_score_val, textChars_font_serif_red_6,
		10, 14);
	SET_TEXT("MANS:", text_4_mans, textChars_font_serif_2_red_6,
		210, 4);
	SET_TEXT("67", text_4_mans_val, textChars_font_serif_red_6,
		240, 4);
	SET_TEXT("LEVEL:", text_4_level, textChars_font_serif_2_red_6,
		205, 14);
	SET_TEXT("89", text_4_level_val, textChars_font_serif_red_6,
		240, 14);
	/* 5: Nothing? (or maybe Game) */
	/* 6: Pause Screen (overlayed on Game) */
	SET_TEXT("paused", text_6_paused_1, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_6_paused_1), 145);
	SET_TEXT("press 'SPACE' to resume", text_6_paused_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(text_6_paused_2), 160);
	/* 7: Nothing */
	/* 8: End of Level Animation */
	/* 9: Level Beaten Screen */
	/* 10: Game Over Screen */
	/* 11: Level 4 Interlude */
	/* 12: Level 8 Interlude */
	/* 13: Level 12 Interlude */
	/* 14: Level 16 Interlude */
	/* 15: Level 20 Interlude */
	/* 16: Level 24 Interlude */
	/* 17: Level 30 Interlude */
	/* 18: Level 34 Interlude */
	/* 19: Level 38 Interlude */
	/* 20: Level 42 Interlude */
	/* 21: Level 46 Interlude */
	/* 22: Level 50 Interlude */
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
#if !defined(SDL1)
	for (i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			break;
		}
	}
#else
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
#endif
}



#define DESTROY_TEXTCHARS(textChars)       \
	for (i = 0; i < LEN(textChars); i++) { \
		DESTROY_SPRITE(textChars[i]);      \
	}

#if !defined(SDL1)
#define DESTROY_SPRITE(sprite) \
	SDL_DestroyTexture(sprite.texture);
#define CLOSE_CONTROLLER() \
	if (controller != NULL) {                \
		SDL_GameControllerClose(controller); \
	}
#define DESTROY_DISPLAY()          \
	SDL_DestroyRenderer(renderer); \
	SDL_DestroyWindow(window);
#else
#define DESTROY_SPRITE(sprite) \
	SDL_FreeSurface(sprite.surface);
#define CLOSE_CONTROLLER() \
	if (SDL_JoystickOpened(0)) {     \
		SDL_JoystickClose(joystick); \
	}
#define DESTROY_DISPLAY() \
	SDL_FreeSurface(screen);
#endif

void DestroyAll() {
	/* Textures */
	/* Text Chars */
	DESTROY_TEXTCHARS(textChars_font_serif_brown_6);
	DESTROY_TEXTCHARS(textChars_font_serif_brown_8);
	DESTROY_TEXTCHARS(textChars_font_serif_gray_6);
	DESTROY_TEXTCHARS(textChars_font_serif_gray_12);
	DESTROY_TEXTCHARS(textChars_font_serif_orange_6);
	DESTROY_TEXTCHARS(textChars_font_serif_red_6);
	DESTROY_TEXTCHARS(textChars_font_serif_red_8);
	DESTROY_TEXTCHARS(textChars_font_serif_red_12);
	DESTROY_TEXTCHARS(textChars_font_serif_white_6);
	DESTROY_TEXTCHARS(textChars_font_serif_white_9);
	DESTROY_TEXTCHARS(textChars_font_serif_white_10);
	DESTROY_TEXTCHARS(textChars_font_serif_white_14);
	DESTROY_TEXTCHARS(textChars_font_nokia_12);
	DESTROY_TEXTCHARS(textChars_font_serif_2_bold_black_23);
	DESTROY_TEXTCHARS(textChars_font_serif_2_bold_red_23);
	DESTROY_TEXTCHARS(textChars_font_serif_2_red_6);
	DESTROY_TEXTCHARS(textChars_font_serif_2_red_13);
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
	CLOSE_CONTROLLER();
	/* Renderer/Screen and Window */
	DESTROY_DISPLAY();
	SDL_Quit();
	SYSTEM_SPECIFIC_CLOSE();
}

#endif