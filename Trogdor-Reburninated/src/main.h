#include "include.h"
#include "menu.h"
#include "sound_logic.h"
#include "text_objects.h"
#include "general.h"
#include "config.h"
#include "window.h"
#include "classes.h"

#ifndef MAIN_H
#define MAIN_H

/* Program State */
bool isRunning;
bool windowSizeChanged;
Sint16 g_sceneState;
Sint16 g_frameState;
Uint16 rand_var;
SDL_Event event;

/* General-use Variables */
Sint8 i, j, k;
int int_i, int_j, int_k;
Uint32 uint_i, uint_j, uint_k;
float float_i;
double double_i;
SDL_Rect outputRect;

/* Timer */
Timer timer_global;
Uint32 deltaTime;

/* Framerate */
Uint32 frameTime;
Uint32 frameCounter_global;

/* SDL Input */
#if !defined(SDL1) && !defined(PSP)
SDL_GameController *controller;
#else
SDL_Joystick *joystick;
Uint8 joystickHat;
#endif

/* General Input */
Uint32 keyInputs;
Uint32 heldKeys;
Uint32 heldKeys_last;
Uint8  heldDirs;
Uint8  heldDirs_last;
Uint8  heldDirs_kb;
Uint8  heldDirs_dpad;
Uint8  heldDirs_stick;
Sint32 timer_buttonHold;
Sint32 timer_buttonHold_repeater;
Sint16 controllerAxis_leftStickX;
Sint16 controllerAxis_leftStickY;
#if defined(WII)
Uint32 wii_keysDown;
Uint32 wii_keysUp;
#endif
#if !(defined(GAMECUBE) || defined(PSP) || defined(XBOX))
Sint32 mouseInput_x;
Sint32 mouseInput_x_last;
Sint32 mouseInput_y;
Sint32 mouseInput_y_last;
#endif

/* Save File */
SDL_RWops *saveFile;
SoundSettings soundSettings;
VideoSettings videoSettings;

/* Cutscenes */
bool cutsceneIsPlaying = false;

/* Menus */
Menu menu_main;
Menu menu_difficulty;
Menu menu_cosmetic;
Menu menu_cheats;
MenuNotebook menu_credits;

/* Audio */
#if defined(PSP)
OSL_SOUND *bgm;
#elif defined(XBOX)
int *bgm;
#else
Mix_Music *bgm;
#endif
SoundEffect *sfxArr[NUM_SOUND_EFFECTS_SFX];
//SoundEffect *sfxArr_gameMusic[NUM_SOUND_EFFECTS_GAMEMUSIC];
SoundEffect *sfxArr_strongBad[NUM_SOUND_EFFECTS_STRONG_BAD];

/* Audio (SoundEffects) */
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
SoundEffect sfx_huskyhead;
SoundEffect sfx_sbdooj_short;

/* Sprite Objects */
SpriteObject sprite_videlectrix_logo;
SpriteInstance sprite_videlectrix_logo_ins;
SpriteObject sprite_title_screen;
SpriteInstance sprite_title_screen_ins;
SpriteObject sprite_trogdor_logo;
SpriteInstance sprite_trogdor_logo_ins;
SpriteObject sprite_level_background_1;
SpriteObject sprite_level_background_2;
SpriteObject sprite_level_background_3;
SpriteObject sprite_level_background_4;
SpriteObject sprite_level_background_th;
SpriteObject *sprite_level_background;
SpriteObject sprite_burnination_meter_full;
SpriteObject sprite_burnination_meter_empty;
SpriteInstance sprite_burnination_meter_empty_ins;
SpriteObject sprite_end_of_level_flash;
SpriteInstance sprite_end_of_level_flash_ins;
SpriteObject sprite_death_message;
SpriteObject sprite_burninate_text;
SpriteObject sprite_burninate_fire;
SpriteObject sprite_level_beaten_trogdor;
SpriteObject sprite_level_beaten_smoke;
SpriteObject sprite_game_over_trogdor;
SpriteObject sprite_overlay_basement_top;
SpriteInstance sprite_overlay_basement_top_ins;
SpriteObject sprite_overlay_basement_bottom;
SpriteInstance sprite_overlay_basement_bottom_ins;
SpriteObject sprite_overlay_basement_left;
SpriteInstance sprite_overlay_basement_left_ins;
SpriteObject sprite_overlay_basement_right;
SpriteInstance sprite_overlay_basement_right_ins;
SDL_Rect right_overlay_padding;
SpriteObject sprite_trogdor;
SpriteObject sprite_trogdor_bighead;
SpriteObject sprite_cottage;
SpriteObject sprite_cottage_fire;
SpriteObject sprite_peasantometer_icon;
Uint8        sprite_peasantometer_icon_init_x;
int          sprite_peasantometer_icon_step;
SpriteObject sprite_archer;
SpriteObject sprite_arrow;
SpriteObject sprite_trogdor_fire;
SpriteObject sprite_trogdor_dead;
SpriteObject sprite_knight;
SpriteObject sprite_peasant;
SpriteObject sprite_end_of_level_trogdor;
SpriteObject sprite_loot;
SpriteObject sprite_trogdor_flexing;
SpriteObject sprite_trogdor_ending;
SpriteObject sprite_heart;
SpriteObject sprite_knight_funnyjoke;
SpriteObject sprite_arrow_funnyjoke;
SpriteObject sprite_kerrek;
SpriteObject sprite_kerrek_smoked;
SpriteObject sprite_strong_bad;
SpriteObject sprite_strong_bad_ending;
SpriteObject sprite_menu_cursor;
SpriteObject sprite_menu_background;
SpriteInstance sprite_menu_background_ins;
//SpriteObject sprite_game_over_banner;
SpriteObject sprite_game_over_text;
SpriteObject sprite_game_over_jonathan_howe;
SDL_Rect     divider_level_beaten_rect;

/* Colors */
SDL_Color color_white  = { 255, 255, 255 };
SDL_Color color_black  = {   0,   0,   0 };
SDL_Color color_red    = { 255,   0,   0 };
SDL_Color color_gray   = { 102, 102, 102 };
SDL_Color color_orange = { 255, 204,   0 };
SDL_Color color_brown  = { 153, 102,   0 };

/* Fonts */
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
FontObject font_serif_white_8;
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
TextObject text_0_loading;
SDL_Rect text_0_loading_censor_rect;
TextObject text_1_presents_1;
TextObject text_1_presents_2;
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
TextObject text_3_controls_1;
TextObject text_3_controls_2;
TextObject text_3_controls_3;
TextObject text_3_controls_4;
TextObject text_3_controls_5;
TextObject text_3_controls_6;
TextObject text_3_keyboard_1;
TextObject text_3_keyboard_2;
TextObject text_3_keyboard_3;
TextObject text_3_keyboard_4;
TextObject text_3_keyboard_5;
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
TextObject text_23_cutscene_15;
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
SDL_Rect menuToWindowDstRect = { 0, 0, appWidth, appHeight };

bool isWindowed = true;
double screenScale = 1;
int trueScreenScaleInt = 1;
double trueScreenScaleFull = 1;
double screenScale_menu = 1;
bool allowHiRes = true;
#if defined(VITA) || defined(WII_U) || defined(SWITCH)
Sint8 scalingType = 1;
#elif defined(PSP)
Sint8 scalingType = 3;
#else
Sint8 scalingType = 0;
#endif
#if !defined(SDL1)
SDL_DisplayMode DM;
#endif

/* Managers */
MenuManager MM;
GameManager GM;

#endif