#include "include.h"
#include "config.h"
#include "general.h"
#include "classes.h"
#include "input.h"
#include "main.h"
#include "sound_logic.h"
#include "sprite_objects.h"
#include "system_specific_macros.h"
#if !defined(SDL1)
#include "text_objects_sdl2.h"
#else
#include "text_objects_sdl1.h"
#endif
#include "media_objects_init.h"

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

/* Fonts */
SDL_Color color_white  = { 255, 255, 255 };
SDL_Color color_black  = {   0,   0,   0 };
SDL_Color color_red    = { 255,   0,   0 };
SDL_Color color_gray   = { 102, 102, 102 };
SDL_Color color_orange = { 255, 204,   0 };
SDL_Color color_brown  = { 153, 102,   0 };

/* Text Objects */
char tempCharArray[64];
Uint8 charCounter;
Uint16 charWidthCounter;
std::stringstream ss;
string tempStr;

/* Timer */
Timer timer_global;
Uint32 deltaTime;

/* Framerate */
Uint32 frameTime;

/* SDL Save File */
SDL_RWops *saveFile;

/* Program State */
Sint8 sceneState = 3;
Sint16 frameState = 1;
Sint16 textTestState = 0;
Uint16 rand_var;
bool isRunning = true;
bool isWindowed = true;

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
Uint16 frameRate;
GameManager GM;

/* General-use Variables */
Sint8 i, j, k;
int int_i, int_j, int_k;
Uint32 uint_i, uint_j, uint_k;
float float_i;

int main(int argv, char** args) {
	SYSTEM_SPECIFIC_OPEN();

	/* Initialize SDL */
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	/* Load Save File */
	LOAD_SAVE_FILE();
	gameWidth = DEFAULT_GAME_WIDTH;
	gameHeight = DEFAULT_GAME_HEIGHT;
	SET_WIDTH_HEIGHT_MULTS();
	frameRate = DEFAULT_FRAME_RATE;

	/* Set Window/Renderer */
#if !defined(SDL1)
	window = SDL_CreateWindow("Trogdor Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWidth, gameHeight, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#elif defined(WII) || defined(GAMECUBE)
	SDL_WM_SetCaption("Trogdor Reburninated", NULL);
	SDL_Surface* screen = SDL_SetVideoMode(gameWidth, gameHeight, 24, SDL_DOUBLEBUF);
#else
	SDL_WM_SetCaption("Trogdor Reburninated", NULL);
	SDL_Surface *screen = SDL_SetVideoMode(gameWidth, gameHeight, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
#endif

	/* Initialize Sound */
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

	/* Controller */
#if !defined(SDL1)
	for (Sint8 i = 0; i < SDL_NumJoysticks(); i++) {
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

	/* Set Sprites */
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
	/* Set Text */
	SET_FONT(font_serif_brown_6, "fonts/27_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_brown_6, color_brown, 32, 122);
	SET_FONT(font_serif_brown_8, "fonts/27_serif_v01.ttf", 8,
		TTF_STYLE_NORMAL, textChars_font_serif_brown_8, color_brown, 32, 126);
	SET_FONT(font_serif_gray_6, "fonts/27_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_gray_6, color_gray, 32, 126);
	SET_FONT(font_serif_gray_12, "fonts/27_serif_v01.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_serif_gray_12, color_gray, 32, 90);
	SET_FONT(font_serif_orange_6, "fonts/27_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_orange_6, color_orange, 32, 90);
	SET_FONT(font_serif_red_6, "fonts/27_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_red_6, color_red, 32, 126);
	SET_FONT(font_serif_red_8, "fonts/27_serif_v01.ttf", 8,
		TTF_STYLE_NORMAL, textChars_font_serif_red_8, color_red, 32, 126);
	SET_FONT(font_serif_red_12, "fonts/27_serif_v01.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_serif_red_12, color_red, 32, 90);
	SET_FONT(font_serif_white_6, "fonts/27_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_white_6, color_white, 32, 126);
	SET_FONT(font_serif_white_9, "fonts/27_serif_v01.ttf", 9,
		TTF_STYLE_NORMAL, textChars_font_serif_white_9, color_white, 32, 126);
	SET_FONT(font_serif_white_10, "fonts/27_serif_v01.ttf", 10,
		TTF_STYLE_NORMAL, textChars_font_serif_white_10, color_white, 32, 126);
	SET_FONT(font_serif_white_14, "fonts/27_serif_v01.ttf", 14,
		TTF_STYLE_NORMAL, textChars_font_serif_white_14, color_white, 32, 126);

	SET_FONT(font_nokia_12, "fonts/29_NOKIA 5110 FontSet.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_nokia_12, color_white, 97, 126);

	SET_FONT(font_serif_2_bold_black_23, "fonts/54_serif_v01.ttf", 23,
		TTF_STYLE_BOLD, textChars_font_serif_2_bold_black_23, color_black, 32, 90);
	SET_FONT(font_serif_2_bold_red_23, "fonts/54_serif_v01.ttf", 23,
		TTF_STYLE_BOLD, textChars_font_serif_2_bold_red_23, color_red, 32, 90);
	SET_FONT(font_serif_2_red_6, "fonts/54_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_2_red_6, color_red, 32, 90);
	SET_FONT(font_serif_2_red_13, "fonts/54_serif_v01.ttf", 13,
		TTF_STYLE_NORMAL, textChars_font_serif_2_red_13, color_red, 32, 90);

	/* Text Objects */
	/* 0: Loading Screen */
	SET_TEXT("loading...", text_0_loading, textChars_font_serif_white_14,
		OBJ_TO_MID_SCREEN_X(text_0_loading), OBJ_TO_MID_SCREEN_Y(text_0_loading));
	SDL_Rect text_0_loading_censor_rect = { text_0_loading.dstrect.x, text_0_loading.dstrect.y,
		text_0_loading.dstrect.w, text_0_loading.dstrect.h };
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

	SET_TEXT("nice work!", text_nice_work, textChars_font_serif_white_10,
		OBJ_TO_MID_SCREEN_X(text_nice_work), OBJ_TO_MID_SCREEN_Y(text_nice_work));
	SET_TEXT("send'em", text_send_em, textChars_font_serif_gray_6,
		OBJ_TO_MID_SCREEN_X(text_send_em), OBJ_TO_MID_SCREEN_Y(text_send_em));
	SET_TEXT("stompin' good!", text_stompin_good, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(text_stompin_good), OBJ_TO_MID_SCREEN_Y(text_stompin_good));
	SET_TEXT("YE       OLDE       HI-SCORES", text_ye_olde_hi_scores, textChars_font_serif_2_red_13,
		OBJ_TO_MID_SCREEN_X(text_ye_olde_hi_scores), OBJ_TO_MID_SCREEN_Y(text_ye_olde_hi_scores));
	SET_TEXT("1", text_one, textChars_font_serif_brown_8,
		OBJ_TO_MID_SCREEN_X(text_one), OBJ_TO_MID_SCREEN_Y(text_one));

	while (isRunning) {
		/* Update Timers */
		timer_global.last = timer_global.now;
		timer_global.now = SDL_GetTicks();
		deltaTime = timer_global.now - timer_global.last;

		/* Update Key/Button Presses, Mouse/Touch Input, and Window Resizing */
#if !defined(SDL1)
		/* Update Controller Axes (SDL2 only; SDL1 axes are handled later) */
		controllerAxis_leftStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
		controllerAxis_leftStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
		controllerAxis_rightStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
		controllerAxis_rightStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
		controllerAxis_LT = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
		controllerAxis_RT = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
			controllerAxis_leftStickX = 0;
		}
		if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
			controllerAxis_leftStickY = 0;
		}
		if ((controllerAxis_rightStickX > -STICK_DEADZONE) && (controllerAxis_rightStickX < STICK_DEADZONE)) {
			controllerAxis_rightStickX = 0;
		}
		if ((controllerAxis_rightStickY > -STICK_DEADZONE) && (controllerAxis_rightStickY < STICK_DEADZONE)) {
			controllerAxis_rightStickY = 0;
		}
		if (controllerAxis_LT < STICK_DEADZONE) {
			controllerAxis_LT = 0;
		}
		if (controllerAxis_RT < STICK_DEADZONE) {
			controllerAxis_RT = 0;
		}
#else
		/* Update Controller Hat Positions (SDL1 only; SDL2 D-Pad buttons are handled later) */
		joystickHat = SDL_JoystickGetHat(joystick, 0);
		if (joystickHat & SDL_HAT_UP) {
			heldKeys |= INPUT_UP;
		} else {
			heldKeys &= ~INPUT_UP;
		}
		if (joystickHat & SDL_HAT_DOWN) {
			heldKeys |= INPUT_DOWN;
		} else {
			heldKeys &= ~INPUT_DOWN;
		}
		if (joystickHat & SDL_HAT_LEFT) {
			heldKeys |= INPUT_LEFT;
		} else {
			heldKeys &= ~INPUT_LEFT;
		}
		if (joystickHat & SDL_HAT_RIGHT) {
			heldKeys |= INPUT_RIGHT;
		} else {
			heldKeys &= ~INPUT_RIGHT;
		}
#endif
		keyInputs = 0;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
#if !defined(SDL1) && !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(WII) && !defined(GAMECUBE)
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							uint_i = SDL_GetWindowSurface(window)->w;
							uint_j = SDL_GetWindowSurface(window)->h;
							if ((uint_i / DEFAULT_GAME_WIDTH) < (uint_j / DEFAULT_GAME_HEIGHT)) {
								float_i = (uint_i / DEFAULT_GAME_WIDTH);
							} else {
								float_i = (uint_j / DEFAULT_GAME_HEIGHT);
							}
							SDL_SetWindowSize(window, (int)(DEFAULT_GAME_WIDTH * float_i), (int)(DEFAULT_GAME_HEIGHT * float_i));
							SDL_RenderSetScale(renderer, float_i, float_i);
							break;
						case SDL_WINDOWEVENT_MAXIMIZED:
							SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
							break;
						default:
							break;
					}
					break;
#endif
				case SDL_KEYDOWN: // keycodes
					if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
						keyInputs |= INPUT_UP;
						heldKeys |= INPUT_UP;
						break;
					}
					if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
						keyInputs |= INPUT_DOWN;
						heldKeys |= INPUT_DOWN;
						break;
					}
					if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
						keyInputs |= INPUT_LEFT;
						heldKeys |= INPUT_LEFT;
						break;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
						keyInputs |= INPUT_RIGHT;
						heldKeys |= INPUT_RIGHT;
						break;
					}
					if (event.key.keysym.sym == SDLK_z) {
						keyInputs |= INPUT_A;
						heldKeys |= INPUT_A;
						break;
					}
					if (event.key.keysym.sym == SDLK_x) {
						keyInputs |= INPUT_B;
						heldKeys |= INPUT_B;
						break;
					}
					if (event.key.keysym.sym == SDLK_c) {
						keyInputs |= INPUT_X;
						heldKeys |= INPUT_X;
						break;
					}
					if (event.key.keysym.sym == SDLK_v) {
						keyInputs |= INPUT_Y;
						heldKeys |= INPUT_Y;
						break;
					}
					if (event.key.keysym.sym == SDLK_q) {
						keyInputs |= INPUT_L;
						heldKeys |= INPUT_L;
						break;
					}
					if (event.key.keysym.sym == SDLK_e) {
						keyInputs |= INPUT_R;
						heldKeys |= INPUT_R;
						break;
					}
					if (event.key.keysym.sym == SDLK_RETURN) {
						keyInputs |= INPUT_START;
						heldKeys |= INPUT_START;
						break;
					}
					if (event.key.keysym.sym == SDLK_BACKQUOTE) {
						keyInputs |= INPUT_SELECT;
						heldKeys |= INPUT_SELECT;
						break;
					}
					if (event.key.keysym.sym == SDLK_f) {
						keyInputs |= INPUT_FULLSCREEN;
						break;
					}
					break;
				case SDL_KEYUP: // keycodes
					if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
						heldKeys &= ~INPUT_UP;
						break;
					}
					if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
						heldKeys &= ~INPUT_DOWN;
						break;
					}
					if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
						heldKeys &= ~INPUT_LEFT;
						break;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
						heldKeys &= ~INPUT_RIGHT;
						break;
					}
					if (event.key.keysym.sym == SDLK_z) {
						heldKeys &= ~INPUT_A;
						break;
					}
					if (event.key.keysym.sym == SDLK_x) {
						heldKeys &= ~INPUT_B;
						break;
					}
					if (event.key.keysym.sym == SDLK_c) {
						heldKeys &= ~INPUT_X;
						break;
					}
					if (event.key.keysym.sym == SDLK_v) {
						heldKeys &= ~INPUT_Y;
						break;
					}
					if (event.key.keysym.sym == SDLK_q) {
						heldKeys &= ~INPUT_L;
						break;
					}
					if (event.key.keysym.sym == SDLK_e) {
						heldKeys &= ~INPUT_R;
						break;
					}
					if (event.key.keysym.sym == SDLK_RETURN) {
						heldKeys &= ~INPUT_START;
						break;
					}
					if (event.key.keysym.sym == SDLK_BACKQUOTE) {
						heldKeys &= ~INPUT_SELECT;
						break;
					}
					break;
#if !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(WII) && !defined(GAMECUBE)
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&mouseInput_x, &mouseInput_y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						break;
					}
					if (event.button.button == SDL_BUTTON_RIGHT) {
						break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					break;
#endif
#if !defined(SDL1)
				case SDL_CONTROLLERBUTTONDOWN:
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
						keyInputs |= INPUT_UP;
						heldKeys |= INPUT_UP;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
						keyInputs |= INPUT_DOWN;
						heldKeys |= INPUT_DOWN;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
						keyInputs |= INPUT_LEFT;
						heldKeys |= INPUT_LEFT;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
						keyInputs |= INPUT_RIGHT;
						heldKeys |= INPUT_RIGHT;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#endif
						keyInputs |= INPUT_A;
						heldKeys |= INPUT_A;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#endif
						keyInputs |= INPUT_B;
						heldKeys |= INPUT_B;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#endif
						keyInputs |= INPUT_X;
						heldKeys |= INPUT_X;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#endif
						keyInputs |= INPUT_Y;
						heldKeys |= INPUT_Y;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
						keyInputs |= INPUT_L;
						heldKeys |= INPUT_L;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
						keyInputs |= INPUT_R;
						heldKeys |= INPUT_R;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
						keyInputs |= INPUT_START;
						heldKeys |= INPUT_START;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
						keyInputs |= INPUT_SELECT;
						heldKeys |= INPUT_SELECT;
						break;
					}
					break;
				case SDL_CONTROLLERBUTTONUP:
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
						heldKeys &= ~INPUT_UP;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
						heldKeys &= ~INPUT_DOWN;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
						heldKeys &= ~INPUT_LEFT;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
						heldKeys &= ~INPUT_RIGHT;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#endif
						heldKeys &= ~INPUT_A;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#endif
						heldKeys &= ~INPUT_B;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#endif
						heldKeys &= ~INPUT_X;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#endif
						heldKeys &= ~INPUT_Y;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
						heldKeys &= ~INPUT_L;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
						heldKeys &= ~INPUT_R;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
						heldKeys &= ~INPUT_START;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
						heldKeys &= ~INPUT_SELECT;
						break;
					}
					break;
				case SDL_FINGERDOWN:
					mouseInput_x = (Sint32)(event.tfinger.x * gameWidth);
					mouseInput_y = (Sint32)(event.tfinger.y * gameHeight);
					break;
				case SDL_FINGERMOTION:
					mouseInput_x = (Sint32)(event.tfinger.x * gameWidth);
					mouseInput_y = (Sint32)(event.tfinger.y * gameHeight);
					break;
				case SDL_FINGERUP:
					break;
				default:
					break;
#else
				case SDL_JOYHATMOTION:
					if (event.jhat.value & SDL_HAT_UP) {
						keyInputs |= INPUT_UP;
						break;
					} else {
						heldKeys &= ~INPUT_UP;
					}
					if (event.jhat.value & SDL_HAT_DOWN) {
						keyInputs |= INPUT_DOWN;
						break;
					} else {
						heldKeys &= ~INPUT_DOWN;
					}
					if (event.jhat.value & SDL_HAT_LEFT) {
						keyInputs |= INPUT_LEFT;
						break;
					} else {
						heldKeys &= ~INPUT_LEFT;
					}
					if (event.jhat.value & SDL_HAT_RIGHT) {
						keyInputs |= INPUT_RIGHT;
						break;
					} else {
						heldKeys &= ~INPUT_RIGHT;
					}
					break;
				case SDL_JOYBUTTONDOWN:
					if (event.jbutton.button == 0) {
						keyInputs |= INPUT_A;
						heldKeys |= INPUT_A;
						break;
					}
					if (event.jbutton.button == 1) {
						keyInputs |= INPUT_B;
						heldKeys |= INPUT_B;
						break;
					}
					if (event.jbutton.button == 2) {
						keyInputs |= INPUT_X;
						heldKeys |= INPUT_X;
						break;
					}
					if (event.jbutton.button == 3) {
						keyInputs |= INPUT_Y;
						heldKeys |= INPUT_Y;
						break;
					}
					if (event.jbutton.button == 4) {
						keyInputs |= INPUT_L;
						heldKeys |= INPUT_L;
						break;
					}
					if (event.jbutton.button == 5) {
						keyInputs |= INPUT_R;
						heldKeys |= INPUT_R;
						break;
					}
					if (event.jbutton.button == 7) {
						keyInputs |= INPUT_START;
						heldKeys |= INPUT_START;
						break;
					}
					if (event.jbutton.button == 6) {
						keyInputs |= INPUT_SELECT;
						heldKeys |= INPUT_SELECT;
						break;
					}
					break;
				case SDL_JOYBUTTONUP:
					if (event.jbutton.button == 0) {
						heldKeys &= ~INPUT_A;
						break;
					}
					if (event.jbutton.button == 1) {
						heldKeys &= ~INPUT_B;
						break;
					}
					if (event.jbutton.button == 2) {
						heldKeys &= ~INPUT_X;
						break;
					}
					if (event.jbutton.button == 3) {
						heldKeys &= ~INPUT_Y;
						break;
					}
					if (event.jbutton.button == 4) {
						heldKeys &= ~INPUT_L;
						break;
					}
					if (event.jbutton.button == 5) {
						heldKeys &= ~INPUT_R;
						break;
					}
					if (event.jbutton.button == 7) {
						heldKeys &= ~INPUT_START;
						break;
					}
					if (event.jbutton.button == 6) {
						heldKeys &= ~INPUT_SELECT;
						break;
					}
					break;
				case SDL_JOYAXISMOTION:
					switch (event.jaxis.axis) {
						case 0:
							controllerAxis_leftStickX = event.jaxis.value;
							if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
								controllerAxis_leftStickX = 0;
							}
							break;
						case 1:
							controllerAxis_leftStickY = event.jaxis.value;
							if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
								controllerAxis_leftStickY = 0;
							}
							break;
						case 2:
							if (event.jaxis.value > STICK_DEADZONE) {
								controllerAxis_LT = event.jaxis.value;
							} else {
								controllerAxis_LT = 0;
							}
							if (event.jaxis.value < -STICK_DEADZONE) {
								controllerAxis_RT = event.jaxis.value;
							} else {
								controllerAxis_RT = 0;
							}
							break;
						case 3:
							controllerAxis_rightStickY = event.jaxis.value;
							if ((controllerAxis_rightStickY > -STICK_DEADZONE) && (controllerAxis_rightStickY < STICK_DEADZONE)) {
								controllerAxis_rightStickY = 0;
							}
							break;
						case 4:
							controllerAxis_rightStickX = event.jaxis.value;
							if ((controllerAxis_rightStickX > -STICK_DEADZONE) && (controllerAxis_rightStickX < STICK_DEADZONE)) {
								controllerAxis_rightStickX = 0;
							}
							break;
						default:
							break;
					}
					break;
#endif
			}
		}

		/* Key Presses (Always Active) */
		if (KEY_PRESSED(INPUT_FULLSCREEN)) {
			SDL_TOGGLE_FULLSCREEN();
		}

		/* Clear Screen */
#if !defined(SDL1)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
#else
		SDL_FillRect(screen, NULL, 0x000000);
#endif

		/* Scene states:
		 *  0: Loading Screen
		 *  1: Videlectrix Logo
		 *  2: Title Screen
		 *  3: Instructions Screen
		 *  4: Game
		 *  5: Nothing? (or maybe Game)
		 *  6: Pause Screen (overlayed on Game)
		 *  7: Nothing
		 *  8: End of Level Animation
		 *  9: Level Beaten Screen
		 * 10: Game Over Screen
		 * 11: Level 4 Interlude
		 * 12: Level 8 Interlude
		 * 13: Level 12 Interlude
		 * 14: Level 16 Interlude
		 * 15: Level 20 Interlude
		 * 16: Level 24 Interlude
		 * 17: Level 30 Interlude
		 * 18: Level 34 Interlude
		 * 19: Level 38 Interlude
		 * 20: Level 42 Interlude
		 * 21: Level 46 Interlude
		 * 22: Level 50 Interlude
		 * 23: Level 100 Interlude (Credits)
		 * 24: Nothing? (or maybe blank transition from Credits to High Scores Screen)
		 * 25: High Scores Screen
		 */
		switch (sceneState) {
			/* Loading Screen */
			case 0:
				switch (frameState) {
					case 1:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x = text_0_loading.dstrect.x;
						frameState++;
						break;
					case 2:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['l' - 32].dstrect.w;
						frameState++;
						break;
					case 3:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['o' - 32].dstrect.w;
						frameState++;
						break;
					case 4:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['a' - 32].dstrect.w;
						frameState++;
						break;
					case 5:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['d' - 32].dstrect.w;
						frameState++;
						break;
					case 6:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['i' - 32].dstrect.w;
						frameState++;
						break;
					case 7:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['n' - 32].dstrect.w;
						frameState++;
						break;
					case 8:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['g' - 32].dstrect.w;
						frameState++;
						break;
					case 9:
					case 10:
					case 11:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['.' - 32].dstrect.w;
						frameState++;
						break;
					case 12:
					case 13:
					case 14:
					case 15:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						frameState++;
						break;
					case 16:
						frameState++;
						break;
					default:
						sceneState = 1;
						frameState = 18;
						break;
				}
				DRAW_RECT(text_0_loading_censor_rect, color_black.r, color_black.g, color_black.b);
				break;
			/* Videlectrix logo */
			case 1:
				if (frameState < 65) {
#if !defined(SDL1)
					RENDER_SPRITE(sprite_videlectrix_logo, NULL, &sprite_videlectrix_logo.dstrect);
#else
					RENDER_SPRITE_SCALED(sprite_videlectrix_logo, NULL, &sprite_videlectrix_logo.dstrect);
#endif
					RENDER_TEXT(text_1_presents, textChars_font_nokia_12);
				}
				if (frameState < 72) {
					frameState++;
				} else {
					sceneState = 2;
					frameState = 73;
				}
				break;
			/* Title Screen */
			case 2:
				if (frameState == 73) {
					PLAY_MUSIC_WITHOUT_LOOP(MUSIC_TITLE_SCREEN);
				}
				if (frameState < 192) {
					frameState++;
				} else {
					Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_trogador, 0);
					sceneState = 3;
					frameState = 3; // 3 is intentional
				}
				RENDER_SPRITE(sprite_title_screen, NULL, &sprite_title_screen.dstrect);
				break;
			/* Instructions Screen */
			case 3:
				frameState++;
				if (KEY_PRESSED(INPUT_A)) {
					GM = GameManager(sprite_trogdor, 4);
					GM.levelInit();
					UPDATE_TEXT(text_4_score_val, to_string(GM.score));
					UPDATE_TEXT(text_4_mans_val, to_string(GM.mans));
					UPDATE_TEXT(text_4_level_val, to_string(GM.level));
					sceneState = 4;
				}
				RENDER_SPRITE(sprite_trogdor_logo);
				RENDER_TEXT(text_3_instructions_1, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_instructions_2, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_instructions_3, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_instructions_4, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_instructions_5, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_programmed, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_designed, textChars_font_serif_white_6);
				if (frameState % 4 < 2) {
					RENDER_TEXT(text_3_click_anywhere_to_start, textChars_font_serif_red_8);
				}
				break;
			/* Game */
			case 4:
				if (KEY_PRESSED(INPUT_B)) {
					GM.burninationIncreaseTest();
				}
				if (KEY_PRESSED(INPUT_A)) {
					GM.burninationDecreaseTest();
				}
				GM.getPlayerInput();
				if (GM.burnination == 0) {

				} else {
					GM.testBurnHut();
				}
#if !defined(SDL1)
				SDL_RenderCopy(renderer, sprite_level_background->texture, NULL, &sprite_level_background->dstrect);
#else
				SDL_BlitSurface(sprite_level_background->surface, NULL, screen, &sprite_level_background->dstrect);
#endif
				RENDER_TEXT(text_4_score, textChars_font_serif_2_red_6);
				RENDER_TEXT(text_4_score_val, textChars_font_serif_red_6);
				RENDER_TEXT(text_4_mans, textChars_font_serif_2_red_6);
				RENDER_TEXT(text_4_mans_val, textChars_font_serif_red_6);
				RENDER_TEXT(text_4_level, textChars_font_serif_2_red_6);
				RENDER_TEXT(text_4_level_val, textChars_font_serif_red_6);
				if (GM.burnination > 0) {
					RENDER_SPRITE(sprite_burnination_meter_empty);
					RENDER_SPRITE(sprite_burnination_meter_full);
				}
				RENDER_AND_ANIMATE_COTTAGES();
				RENDER_SPRITE(sprite_trogdor);
				break;
			/* Nothing? (or maybe Game) */
			case 5:
				break;
			/* Pause Screen (overlayed on Game) */
			case 6:
				break;
			/* Nothing */
			case 7:
				break;
			/* End of Level Animation */
			case 8:
				break;
			/* Level Beaten Screen */
			case 9:
				break;
			/* Game Over Screen */
			case 10:
				break;
			/* Level 4 Interlude */
			case 11:
				break;
			/* Level 8 Interlude */
			case 12:
				break;
			/* Level 12 Interlude */
			case 13:
				break;
			/* Level 16 Interlude */
			case 14:
				break;
			/* Level 20 Interlude */
			case 15:
				break;
			/* Level 24 Interlude */
			case 16:
				break;
			/* Level 30 Interlude */
			case 17:
				break;
			/* Level 34 Interlude */
			case 18:
				break;
			/* Level 38 Interlude */
			case 19:
				break;
			/* Level 42 Interlude */
			case 20:
				break;
			/* Level 46 Interlude */
			case 21:
				break;
			/* Level 50 Interlude */
			case 22:
				break;
			/* Level 100 Interlude (Credits) */
			case 23:
				break;
			/* Nothing? (or maybe blank transition from Credits to High Scores Screen) */
			case 24:
				break;
			/* High Scores Screen */
			case 25:
				break;
			/* DEBUG - Text Test Screen */
			case 101:
				if (KEY_PRESSED(INPUT_RIGHT)) {
					textTestState = (textTestState + 1) % 17;
				}
				if (KEY_PRESSED(INPUT_LEFT)) {
					textTestState--;
					while (textTestState < 0) {
						textTestState += 17;
					}
				}
				if (KEY_PRESSED(INPUT_SELECT)) {
					sceneState = 0;
				}
				switch (textTestState) {
					case 0:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						break;
					case 1:
						RENDER_TEXT(text_1_presents, textChars_font_nokia_12);
						break;
					case 2:
						RENDER_TEXT(text_3_click_anywhere_to_start, textChars_font_serif_red_8);
						break;
					case 3:
						RENDER_TEXT(text_3_programmed, textChars_font_serif_white_6);
						break;
					case 4:
						RENDER_TEXT(text_3_designed, textChars_font_serif_white_6);
						break;
					case 5:
						RENDER_TEXT(text_3_instructions_1, textChars_font_serif_white_6);
						break;
					case 6:
						RENDER_TEXT(text_3_instructions_2, textChars_font_serif_white_6);
						break;
					case 7:
						RENDER_TEXT(text_3_instructions_3, textChars_font_serif_white_6);
						break;
					case 8:
						RENDER_TEXT(text_3_instructions_4, textChars_font_serif_white_6);
						break;
					case 9:
						RENDER_TEXT(text_3_instructions_5, textChars_font_serif_white_6);
						break;
					case 10:
						RENDER_TEXT(text_3_hints_1, textChars_font_serif_red_6);
						break;
					case 11:
						RENDER_TEXT(text_3_hints_2, textChars_font_serif_white_6);
						break;
					case 12:
						RENDER_TEXT(text_3_hints_3, textChars_font_serif_white_6);
						break;
					case 13:
						RENDER_TEXT(text_3_hints_4, textChars_font_serif_white_6);
						break;
					case 14:
						RENDER_TEXT(text_3_hints_5, textChars_font_serif_white_6);
						break;
					case 15:
						RENDER_TEXT(text_3_hints_6, textChars_font_serif_red_6);
						break;
					case 16:
						RENDER_TEXT(text_3_hints_7, textChars_font_serif_red_6);
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}

#if !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(WII) && !defined(GAMECUBE)
		/* Update Mouse Position */
		mouseInput_x_last = mouseInput_x;
		mouseInput_y_last = mouseInput_y;
#endif

		/* Update Screen */
#if !defined(SDL1)
		SDL_RenderPresent(renderer);
#else
		SDL_Flip(screen);
#endif
		
		/* Cap Framerate */
		frameTime = SDL_GetTicks() - (Uint32)timer_global.now;
		if (frameTime < (1000 / FRAME_RATE)) {
			SDL_Delay((1000 / FRAME_RATE) - frameTime);
		}
	}

	/* Destroy all SDL objects and properly close program */
	DESTROY_ALL();

	return 0;
}