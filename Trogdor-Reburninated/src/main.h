#ifndef MAIN_H
#define MAIN_H

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
Sint16 controllerAxis_leftStickY;
#if !(defined(GAMECUBE) || defined(PSP))
Sint32 mouseInput_x;
Sint32 mouseInput_x_last;
Sint32 mouseInput_y;
Sint32 mouseInput_y_last;
#endif

/* Audio */
#if !defined(PSP)
Mix_Music *bgm;
#else
OSL_SOUND *bgm;
#endif
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
SoundEffect sfx_shutup;

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
SpriteObject sprite_level_beaten_smoke_1;
SpriteObject sprite_level_beaten_smoke_2;
SpriteObject sprite_level_beaten_smoke_3;
SpriteObject sprite_game_over_trogdor;
SpriteObject sprite_loot;
SpriteObject sprite_overlay_basement_top;
SpriteObject sprite_overlay_basement_bottom;
SpriteObject sprite_overlay_basement_left;
SpriteObject sprite_overlay_basement_right;
SDL_Rect     divider_level_beaten_rect;

/* Fonts */
SDL_Color color_white  = { 255, 255, 255 };
SDL_Color color_black  = {   0,   0,   0 };
SDL_Color color_red    = { 255,   0,   0 };
SDL_Color color_gray   = { 102, 102, 102 };
SDL_Color color_orange = { 255, 204,   0 };
SDL_Color color_brown  = { 153, 102,   0 };
FontObject font_serif_brown_6;
FontObject font_serif_brown_8;
FontObject font_serif_gray_6;
FontObject font_serif_gray_12;
FontObject font_serif_orange_6;
FontObject font_serif_red_6;
FontObject font_serif_red_6_mult;
FontObject font_serif_red_8;
FontObject font_serif_red_8_mult;
FontObject font_serif_red_12;
FontObject font_serif_white_6;
FontObject font_serif_white_6_mult;
FontObject font_serif_white_9;
FontObject font_serif_white_10;
FontObject font_serif_white_14;
FontObject font_nokia_12;
//FontObject font_serif_2_bold_black_23;
//FontObject font_serif_2_bold_red_23;
FontObject font_serif_2_red_6;
FontObject font_serif_2_red_13;
FontObject font_commodore_error_1;
FontObject font_commodore_error_2;

/* Text Objects */
char tempCharArray[64];
Uint8 charCounter;
Sint16 charWidthCounter;
string tempStr;
TextObject text_0_loading;
SDL_Rect text_0_loading_censor_rect;
TextObject text_1_presents;
TextObject text_3_click_anywhere_to_start;
TextObject text_3_quit;
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
TextObject text_3_credits_8;
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
TextObject text_4_paused_3;
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
TextObject text_error_1;
TextObject text_error_2;

/* Window */
#if !defined(SDL1)
SDL_Window *window;
SDL_Renderer *renderer;
#else
SDL_Surface *windowScreen;
SDL_Surface *transparentScreen;
#endif
SDL_Rect gameSrcRect = { 0, 0, gameWidth, gameHeight };
//SDL_Rect gameToAppDstRect = { 0, 0, gameWidth, gameHeight };
SDL_Rect gameHiResSrcRect = { 0, 0, gameWidth, gameHeight };
SDL_Rect appSrcRect = { 0, 0, appWidth, appHeight };
SDL_Rect appToWindowDstRect = { 0, 0, appWidth, appHeight };
SDL_Rect gameToWindowDstRect = { 0, 0, gameWidth, gameHeight };
bool isWindowed = true;
double screenScale = 1;
int trueScreenScaleInt = 1;
double trueScreenScaleFull = 1;
bool allowHiRes = true;
Sint8 scalingType = 0;
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
Uint32 ticksPerFrame;

/* Save File */
SDL_RWops *saveFile;
SoundSettings soundSettings;
VideoSettings videoSettings;



void InitializeDisplay() {
#if !defined(SDL1)
	SDL_GetCurrentDisplayMode(0, &DM);
#endif
	videoSettings.widthSetting = DEFAULT_WIDTH;
	videoSettings.heightSetting = DEFAULT_HEIGHT;
#if defined(ANDROID)
	SDL_SetHint(SDL_HINT_ORIENTATIONS, "Landscape");
#endif
	appWidth = 320;
	appHeight = 240;
	appSrcRect = { 0, 0, appWidth, appHeight };
	frameRate = DEFAULT_FRAME_RATE;
	ticksPerFrame = (Uint32)(1000 / frameRate);
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
#elif defined(WII) || defined(GAMECUBE) || defined(THREEDS)
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
	setScaling();
}

void InitializeSound() {
#if !defined(PSP)
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
#if !defined(SDL1) && !defined(ANDROID)
		SDL_Log(Mix_GetError());
#endif
	}
	Mix_VolumeMusic((int)(soundSettings.bgmVolume * 128.0 / 100));
	Mix_AllocateChannels(NUM_SOUND_CHANNELS);
	Mix_Volume(SFX_CHANNEL_GAME, (int)(soundSettings.sfxVolume * 128.0 / 100));
	Mix_Volume(SFX_CHANNEL_STRONG_BAD, (int)(soundSettings.sfxVolume * 128.0 / 100));
#else
	oslInitAudio();
#endif
}

void InitializeController() {
#if defined(SDL1) // also applies to PSP SDL1
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
#elif defined(PSP)
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	joystick = SDL_JoystickOpen(0);
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
	outputRect = sprite_level_background->dstrect;
	outputRect.x = (Sint16)(outputRect.x * screenScale) + gameToWindowDstRect.x;
	outputRect.y = (Sint16)(outputRect.y * screenScale) + gameToWindowDstRect.y;
	outputRect.w = (Uint16)(outputRect.w * screenScale);
	outputRect.h = (Uint16)(outputRect.h * screenScale);
#if !defined(SDL1)
	SDL_RenderCopy(renderer, sprite_level_background->texture, NULL, &outputRect);
#else
	SDL_BlitSurface(sprite_level_background->surface, NULL, windowScreen, &outputRect);
#endif
}

void renderTransparentForeground() {
#if !defined(THREEDS)
	outputRect = gameToWindowDstRect;
#if !defined(SDL1)
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_RenderFillRect(renderer, &outputRect);
#else
	SDL_BlitSurface(transparentScreen, NULL, windowScreen, &outputRect);
#endif
#endif
}



void closeController() {
#if defined(PSP)
	SDL_JoystickClose(joystick);
#elif defined(SDL1)
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
}

void DestroyAll() {
	/* Surfaces */
	destroyAllSprites();
	/* Text Chars */
	destroyAllTextChars();
	/* Sound */
	for (i = 0; i < NUM_SOUND_EFFECTS_SFX; i++) {
		if (sfxArr[i]->chunk != NULL) {
#if !defined(PSP)
			Mix_FreeChunk(sfxArr[i]->chunk);
#else
			oslDeleteSound(sfxArr[i]->chunk);
#endif
		}
	}
	for (i = 0; i < NUM_SOUND_EFFECTS_STRONG_BAD; i++) {
		if (sfxArr_strongBad[i]->chunk != NULL) {
#if !defined(PSP)
			Mix_FreeChunk(sfxArr_strongBad[i]->chunk);
#else
			oslDeleteSound(sfxArr_strongBad[i]->chunk);
#endif
		}
	}
#if defined(PSP)
	if (bgm != NULL) {
		oslDeleteSound(bgm);
	}
	oslDeinitAudio();
#else
	Mix_FreeMusic(bgm);
	Mix_CloseAudio();
#if !defined(WII) && !defined(GAMECUBE)
	Mix_Quit();
#endif
#endif
	/* Controller */
	closeController();
	/* Renderer/Screen and Window */
	destroyDisplay();
	SDL_Quit();
	systemSpecificClose();
}

#endif