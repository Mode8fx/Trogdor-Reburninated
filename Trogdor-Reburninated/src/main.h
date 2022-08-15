#ifndef MAIN_H
#define MAIN_H

#include "include.h"
#include "classes.h"

SDL_Event event;

/* SDL Input */
#if !defined(SDL1) && !defined(PSP)
SDL_GameController *controller = nullptr;
#else
SDL_Joystick *joystick = nullptr;
Uint8 joystickHat;
#endif
Sint16 controllerAxis_leftStickX;
Sint16 controllerAxis_leftStickX_last;
Sint16 controllerAxis_leftStickY;
Sint16 controllerAxis_leftStickY_last;
#if !(defined(GAMECUBE) || defined(PSP))
Sint32 mouseInput_x;
Sint32 mouseInput_x_last;
Sint32 mouseInput_y;
Sint32 mouseInput_y_last;
#endif

/* Audio */
Mix_Music *bgm;
SoundEffect sfx_burn_hut;
SoundEffect sfx_goldget;
SoundEffect sfx_peasantscream;
SoundEffect sfx_sb1;
SoundEffect sfx_sb2;
SoundEffect sfx_sb3;
SoundEffect sfx_sb4;
SoundEffect sfx_sb5;
SoundEffect sfx_sb6;
SoundEffect sfx_sb7;
SoundEffect sfx_sbarch;
SoundEffect sfx_sbarchend;
SoundEffect sfx_sbbest;
SoundEffect sfx_sbdooj;
SoundEffect sfx_sbgameover;
SoundEffect sfx_sbkerrek;
SoundEffect sfx_sblevelbeat;
SoundEffect sfx_sbscore;
SoundEffect sfx_sbsecret;
SoundEffect sfx_sbsquish1;
SoundEffect sfx_sbsquish2;
SoundEffect sfx_sbwin;
SoundEffect sfx_sbwin2;
SoundEffect sfx_sbworst;
SoundEffect sfx_sfx2;
SoundEffect sfx_trogador;
SoundEffect sfx_arrow;
SoundEffect sfx_squish;
SoundEffect sfx_death;
SoundEffect sfx_kick;
SoundEffect sfx_burninate;
SoundEffect sfx_cutscene;
SoundEffect sfx_gameover;

/* Sprite Objects */
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
SpriteObject sprite_level_beaten_trogdor;
SpriteObject sprite_game_over_trogdor;
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
TTF_Font *font_serif_red_6_mult;
TextCharObject textChars_font_serif_red_6_mult[126 + 1 - 32];
TTF_Font *font_serif_red_8;
TextCharObject textChars_font_serif_red_8[126 + 1 - 32];
TTF_Font *font_serif_red_8_mult;
TextCharObject textChars_font_serif_red_8_mult[126 + 1 - 32];
TTF_Font *font_serif_red_12;
TextCharObject textChars_font_serif_red_12[90 + 1 - 32];
TTF_Font *font_serif_white_6;
TextCharObject textChars_font_serif_white_6[126 + 1 - 32];
TTF_Font *font_serif_white_6_mult;
TextCharObject textChars_font_serif_white_6_mult[126 + 1 - 32];
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
TextObject text_3_coming_soon_1;
TextObject text_3_coming_soon_2;
TextObject text_3_coming_soon_3;
TextObject text_3_coming_soon_4;
TextObject text_3_coming_soon_5;
TextObject text_3_coming_soon_6;
TextObject text_3_instructions_2a;
TextObject text_3_hints_2a;
TextObject text_3_hints_3a;
TextObject text_3_hints_4a;
TextObject text_3_hints_5a;
TextObject text_3_coming_soon_4a;
TextObject text_4_score_val;
TextObject text_4_mans_val;
TextObject text_4_level_val;
TextObject text_4_score;
TextObject text_4_mans;
TextObject text_4_level;
TextObject text_4_burninate_black;
TextObject text_4_burninate_red;
TextObject text_4_paused_1;
TextObject text_4_paused_2;
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
TextObject text_placeholder_cutscene;
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
TextObject text_23_cutscene_1;
TextObject text_23_cutscene_2;
TextObject text_23_cutscene_3;
TextObject text_23_cutscene_4;
TextObject text_23_cutscene_5;
TextObject text_23_cutscene_6;
TextObject text_23_cutscene_7;
TextObject text_23_cutscene_8;
TextObject text_23_cutscene_9;
TextObject text_23_cutscene_10;
TextObject text_23_cutscene_11;
TextObject text_23_cutscene_12;
TextObject text_23_cutscene_13;
TextObject text_23_cutscene_14;
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
SDL_Texture *outputTexture;
#else
SDL_Surface *windowScreen;
#endif
SDL_Surface *gameScreen;
SDL_Rect gameSrcRect = { 0, 0, gameWidth, gameHeight };
SDL_Rect gameToAppDstRect = { 0, 0, gameWidth, gameHeight };
SDL_Surface *gameHiResScreen;
SDL_Rect gameHiResSrcRect = { 0, 0, gameWidth, gameHeight };
SDL_Surface *appScreen;
SDL_Rect appSrcRect = { 0, 0, appWidth, appHeight };
SDL_Rect appToWindowDstRect = { 0, 0, appWidth, appHeight };
SDL_Rect gameToWindowDstRect = { 0, 0, gameWidth, gameHeight };
bool isWindowed = true;
double screenScale = 1;
bool isIntegerScale = true;
#if !defined(SDL1)
SDL_DisplayMode DM;
#endif
Uint16 gameHiResWidth;
Uint16 gameHiResHeight;
Uint16 appWidth;
Uint16 appHeight;
double gameWidthMult;
double gameHeightMult;
double gameHiResMult;
Uint16 windowWidth;
Uint16 windowHeight;
double appWidthMult;
double appHeightMult;
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
	appWidth = gameHeight * 16 / 9; // for now
	appHeight = gameHeight;
	appSrcRect = { 0, 0, appWidth, appHeight };
	frameRate = DEFAULT_FRAME_RATE;
	setWidthHeightMults();

	/* Set Window/Renderer */
#if defined(PSP)
	window = SDL_CreateWindow("Trogdor Beta", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, videoSettings.widthSetting, videoSettings.heightSetting, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#elif defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID)
	window = SDL_CreateWindow("Trogdor Beta", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, videoSettings.widthSetting, videoSettings.heightSetting, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#elif defined(WII) || defined(GAMECUBE)
	SDL_WM_SetCaption("Trogdor Beta", NULL);
	windowScreen = SDL_SetVideoMode(videoSettings.widthSetting, videoSettings.heightSetting, 24, SDL_DOUBLEBUF);
#elif defined(SDL1)
	SDL_WM_SetCaption("Trogdor Beta", NULL);
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
	windowScreen = SDL_SetVideoMode(640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
#else
	window = SDL_CreateWindow("Trogdor Beta", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, videoSettings.widthSetting, videoSettings.heightSetting, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#endif
	gameScreen = SDL_CreateRGBSurface(0, gameWidth, gameHeight, 24, 0, 0, 0, 0);
	gameHiResScreen = SDL_CreateRGBSurface(0, gameToAppDstRect.w, gameToAppDstRect.h, 24, 0, 0, 0, 0);
	appScreen = SDL_CreateRGBSurface(0, appWidth, appHeight, 24, 0, 0, 0, 0);
#if !defined(SDL1)
	SDL_SetColorKey(appScreen, SDL_TRUE, 0xFF00FF);
#else
	SDL_SetColorKey(appScreen, SDL_SRCCOLORKEY, 0xFF00FF);
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
	Mix_AllocateChannels(NUM_SOUND_CHANNELS);
	Mix_Volume(SFX_CHANNEL_GAME, (int)(soundSettings.sfxVolume * 128.0 / 100));
	Mix_Volume(SFX_CHANNEL_STRONG_BAD, (int)(soundSettings.sfxVolume * 128.0 / 100));
}

void InitializeMusic() {
}

void InitializeSFX() {
	sfxArr[0] = &sfx_burn_hut;
	sfx_burn_hut.path = "sfx/burn_hut.wav";
	sfxArr[1] = &sfx_goldget;
	sfx_goldget.path = "sfx/trog_goldget.wav";
	sfxArr[2] = &sfx_peasantscream;
	sfx_peasantscream.path = "sfx/trog_peasantscream.wav";
	sfxArr[3] = &sfx_sfx2;
	sfx_sfx2.path = "sfx/trog_sfx2.wav";
	sfxArr[4] = &sfx_trogador;
	sfx_trogador.path = "sfx/trogador.wav";
	sfxArr[5] = &sfx_arrow;
	sfx_arrow.path = "sfx/arrow.wav";
	sfxArr[6] = &sfx_squish;
	sfx_squish.path = "sfx/squish.wav";
	sfxArr[7] = &sfx_death;
	sfx_death.path = "sfx/death.wav";
	sfxArr[8] = &sfx_kick;
	sfx_kick.path = "sfx/kick.wav";
	sfxArr[9] = &sfx_burninate;
	sfx_burninate.path = "sfx/burninate.wav";
	sfxArr[10] = &sfx_cutscene;
	sfx_cutscene.path = "sfx/cutscene.wav";
	sfxArr[11] = &sfx_gameover;
	sfx_gameover.path = "sfx/gameover.wav";
	sfxArr_strongBad[0] = &sfx_sb1;
	sfx_sb1.path = "sfx/trog_sb1.wav";
	sfxArr_strongBad[1] = &sfx_sb2;
	sfx_sb2.path = "sfx/trog_sb2.wav";
	sfxArr_strongBad[2] = &sfx_sb3;
	sfx_sb3.path = "sfx/trog_sb3.wav";
	sfxArr_strongBad[3] = &sfx_sb4;
	sfx_sb4.path = "sfx/trog_sb4.wav";
	sfxArr_strongBad[4] = &sfx_sb5;
	sfx_sb5.path = "sfx/trog_sb5.wav";
	sfxArr_strongBad[5] = &sfx_sb6;
	sfx_sb6.path = "sfx/trog_sb6.wav";
	sfxArr_strongBad[6] = &sfx_sb7;
	sfx_sb7.path = "sfx/trog_sb7.wav";
	sfxArr_strongBad[7] = &sfx_sbarch;
	sfx_sbarch.path = "sfx/trog_sbarch.wav";
	sfxArr_strongBad[8] = &sfx_sbarchend;
	sfx_sbarchend.path = "sfx/trog_sbarchend.wav";
	sfxArr_strongBad[9] = &sfx_sbbest;
	sfx_sbbest.path = "sfx/trog_sbbest.wav";
	sfxArr_strongBad[10] = &sfx_sbdooj;
	sfx_sbdooj.path = "sfx/trog_sbdooj.wav";
	sfxArr_strongBad[11] = &sfx_sbgameover;
	sfx_sbgameover.path = "sfx/trog_sbgameover.wav";
	sfxArr_strongBad[12] = &sfx_sbkerrek;
	sfx_sbkerrek.path = "sfx/trog_sbkerrek.wav";
	sfxArr_strongBad[13] = &sfx_sblevelbeat;
	sfx_sblevelbeat.path = "sfx/trog_sblevelbeat.wav";
	sfxArr_strongBad[14] = &sfx_sbscore;
	sfx_sbscore.path = "sfx/trog_sbscore.wav";
	sfxArr_strongBad[15] = &sfx_sbsecret;
	sfx_sbsecret.path = "sfx/trog_sbsecret.wav";
	sfxArr_strongBad[16] = &sfx_sbsquish1;
	sfx_sbsquish1.path = "sfx/trog_sbsquish1.wav";
	sfxArr_strongBad[17] = &sfx_sbsquish2;
	sfx_sbsquish2.path = "sfx/trog_sbsquish2.wav";
	sfxArr_strongBad[18] = &sfx_sbwin;
	sfx_sbwin.path = "sfx/trog_sbwin.wav";
	sfxArr_strongBad[19] = &sfx_sbwin2;
	sfx_sbwin2.path = "sfx/trog_sbwin2.wav";
	sfxArr_strongBad[20] = &sfx_sbworst;
	sfx_sbworst.path = "sfx/trog_sbworst.wav";
	for (i = 0; i < NUM_SOUND_EFFECTS_STRONG_BAD; i++) {
		sfxArr_strongBad[i]->type = 1;
	}
}

void InitializeSpritesPart1() {
	PREPARE_SPRITE(sprite_videlectrix_logo, (rootDir + "graphics/videlectrix_logo_big.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(appWidth, sprite_videlectrix_logo), OBJ_TO_MID_SCREEN_Y(appHeight, sprite_videlectrix_logo), 1, 1, 1);
	// I'm gonna be lazy and just use the title screen directly instead of its separate components
	PREPARE_SPRITE(sprite_title_screen, (rootDir + "graphics/title_screen.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_title_screen), OBJ_TO_MID_SCREEN_Y(gameHeight, sprite_title_screen), 1, 1, 1);
	PREPARE_SPRITE(sprite_trogdor_logo, (rootDir + "graphics/trogdor_logo.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_trogdor_logo), 15, 1, 1, 1);
	// ((2466 + 23) / 5000.0) = 0.4978
	// (2466 / 5000.0) = 0.4932
	// ((2183 - 133) / 3600.0) = 0.5694
	// (2183 / 3600.0) = 0.6064
	PREPARE_SPRITE(sprite_level_background_1, (rootDir + "graphics/backgrounds/1.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_level_background_1), 25, 1, 1, 1);
	PREPARE_SPRITE(sprite_level_background_2, (rootDir + "graphics/backgrounds/2.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_level_background_2), 25, 1, 1, 1);
	PREPARE_SPRITE(sprite_level_background_3, (rootDir + "graphics/backgrounds/3.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_level_background_3), 25, 1, 1, 1);
	PREPARE_SPRITE(sprite_level_background_4, (rootDir + "graphics/backgrounds/4.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_level_background_4), 25, 1, 1, 1);
	PREPARE_SPRITE(sprite_level_background_th, (rootDir + "graphics/backgrounds/treasure_hut.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_level_background_th), 25, 1, 1, 1);
}

void InitializeSpritesPart2() {
	PREPARE_SPRITE(sprite_trogdor, (rootDir + "graphics/trogdor.bmp").c_str(),
		0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_burnination_meter_full, (rootDir + "graphics/burnination_meter/full.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_burnination_meter_full), 8, 1, 1, 1);
	PREPARE_SPRITE(sprite_burnination_meter_empty, (rootDir + "graphics/burnination_meter/empty.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_burnination_meter_empty), 8, 1, 1, 1);
	PREPARE_SPRITE(sprite_cottage, (rootDir + "graphics/cottage.bmp").c_str(),
		0, 0, 2, 4, 1);
	PREPARE_SPRITE(sprite_cottage_fire, (rootDir + "graphics/cottage_fire.bmp").c_str(),
		0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_peasantometer_icon, (rootDir + "graphics/peasantometer.bmp").c_str(),
		0, 3, 2, 1, 1);
	sprite_peasantometer_icon_init_x = (Uint8)(gameWidth * 66 / gameWidth);
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
		65, 53, 1, 1, 1);
	if (gameHiResMult >= 2) {
		PREPARE_SPRITE(sprite_end_of_level_trogdor, (rootDir + "graphics/end_of_level_trogdor_small.bmp").c_str(),
			OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, sprite_end_of_level_trogdor, 0.476), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, sprite_end_of_level_trogdor, 0.6), 1, 1, (int)(ceil(gameHiResMult * 1.5)));
	} else {
		PREPARE_SPRITE(sprite_end_of_level_trogdor, (rootDir + "graphics/end_of_level_trogdor_big.bmp").c_str(),
			OBJ_TO_SCREEN_AT_FRACTION_X(gameWidth, sprite_end_of_level_trogdor, 0.476), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHeight, sprite_end_of_level_trogdor, 0.6), 1, 1, 1);
	}
	PREPARE_SPRITE(sprite_death_message, (rootDir + "graphics/death_message.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_death_message), OBJ_TO_MID_SCREEN_Y(gameHeight, sprite_death_message), 2, 5, 1);
	PREPARE_SPRITE(sprite_burninate_text, (rootDir + "graphics/burninate_text.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_burninate_text), OBJ_TO_MID_SCREEN_Y(gameHeight, sprite_burninate_text), 1, 1, 1);
	PREPARE_SPRITE(sprite_burninate_fire, (rootDir + "graphics/burninate_message_fire.bmp").c_str(),
		OBJ_TO_MID_SCREEN_X(gameWidth, sprite_burninate_fire), OBJ_TO_MID_SCREEN_Y(gameHeight, sprite_burninate_fire), 1, 14, 1);
	PREPARE_SPRITE(sprite_loot, (rootDir + "graphics/loot.bmp").c_str(),
		0, 0, 1, 1, 1);
	PREPARE_SPRITE(sprite_level_beaten_trogdor, (rootDir + "graphics/level_beaten_trogdor_scaled.bmp").c_str(),
		-5, 41, 1, 1, 1);
	PREPARE_SPRITE(sprite_game_over_trogdor, (rootDir + "graphics/game_over_trogdor.bmp").c_str(),
		-13, 75, 1, 1, 1);
	divider_level_beaten_rect = { 0, 25, gameWidth, 2 };
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
		gameWidth, gameHeight, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#else
	SDL_Surface *screen_transparent = SDL_CreateRGBSurface(0,
		gameWidth, gameHeight, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
#endif
	SDL_FillRect(screen_transparent, NULL, 0xC8000000);
	SDL_BlitSurface(screen_transparent, NULL, gameScreen, &gameSrcRect);
	SDL_FreeSurface(screen_transparent);
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
#else
	SDL_FreeSurface(windowScreen);
#endif
	SDL_FreeSurface(gameScreen);
	SDL_FreeSurface(gameHiResScreen);
	SDL_FreeSurface(appScreen);
}

void DestroyAll() {
	/* Surfaces */
	/* Text Chars */
	destroyAllTextChars();
	/* Sound */
	for (i = 0; i < NUM_SOUND_EFFECTS_SFX; i++) {
		if (sfxArr[i]->chunk != NULL && sfxArr[i]->isPlaying) {
			Mix_FreeChunk(sfxArr[i]->chunk);
		}
	}
	for (i = 0; i < NUM_SOUND_EFFECTS_STRONG_BAD; i++) {
		if (sfxArr_strongBad[i]->chunk != NULL && sfxArr_strongBad[i]->isPlaying) {
			Mix_FreeChunk(sfxArr_strongBad[i]->chunk);
		}
	}
	Mix_FreeMusic(bgm);
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