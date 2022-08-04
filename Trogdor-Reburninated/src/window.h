#include "config.h"
#include "general.h"

#ifndef WINDOW_H
#define WINDOW_H

#define DEFAULT_GAME_WIDTH    250
#define DEFAULT_GAME_HEIGHT   180
#define DEFAULT_FRAME_RATE    16

extern Uint16 GAME_WIDTH;
extern Uint16 GAME_HEIGHT;
extern double gameWidthMult;
extern double gameHeightMult;
extern Uint16 frameRate;

#define GAME_WIDTH DEFAULT_GAME_WIDTH
#define GAME_HEIGHT DEFAULT_GAME_HEIGHT
#define GAME_WIDTH_MULT gameWidthMult
#define GAME_HEIGHT_MULT gameHeightMult
#define FRAME_RATE frameRate

#if !defined(PC) || defined(SDL1)
#define SCALING_WIDTH DEFAULT_GAME_WIDTH
#define SCALING_HEIGHT DEFAULT_GAME_HEIGHT
#else
#define SCALING_WIDTH SDL_GetWindowSurface(window)->w
#define SCALING_HEIGHT SDL_GetWindowSurface(window)->h
#endif

#if !defined(SDL1)
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *gameTexture;
#endif
extern SDL_Surface *gameScreen;
const SDL_Rect gameWindowSrcRect = { 0, 0, DEFAULT_GAME_WIDTH, DEFAULT_GAME_HEIGHT };
extern SDL_Rect gameWindowDstRect;
extern SDL_Rect appScreenRect;

extern SDL_Rect topRect;
extern SDL_Rect bottomRect;
extern SDL_Rect leftRect;
extern SDL_Rect rightRect;
extern bool isWindowed;
extern double screenScale;
extern bool isIntegerScale;
#if !defined(SDL1)
extern SDL_DisplayMode DM;
#endif
//#if !defined(ANDROID)
//#define SYSTEM_WIDTH  DM.w
//#define SYSTEM_HEIGHT DM.h
#if defined(ANDROID)
#define SYSTEM_WIDTH  max(DM.w, DM.h)
#define SYSTEM_HEIGHT min(DM.w, DM.h)
#endif
#if defined(WII_U)
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[7] = { 320,  362,  640,  725,  768,  800,  960 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[7] = { 240,  272,  480,  544,  576,  600,  720 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[6] = { 426,  480,  853,  960, 1176, 1280 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[6] = { 240,  272,  480,  544,  664,  720 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[3] = { 435,  720, 1152 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[3] = { 272,  480,  720 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[3] = { 480,  960, 1280 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[3] = { 205,  410,  548 };
#define DEFAULT_WIDTH  1280
#define DEFAULT_HEIGHT 720
#define DEFAULT_RI     5
#define DEFAULT_ARI    1
#elif defined(VITA)
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[4] = { 320, 362, 640, 725 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[4] = { 240, 272, 480, 544 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[4] = { 426, 480, 853, 960 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[4] = { 240, 272, 480, 544 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[2] = { 435, 720 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[2] = { 272, 480 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[2] = { 480, 960 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[2] = { 205, 410 };
#define DEFAULT_WIDTH  960
#define DEFAULT_HEIGHT 544
#define DEFAULT_RI     3
#define DEFAULT_ARI    1
#elif defined(SWITCH)
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[11] = { 320,  362,  640,  725,  768,  800,  960, 1024, 1152, 1280, 1440 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[11] = { 240,  272,  480,  544,  576,  600,  720,  768,  864,  960, 1080 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[9] = { 426,  480,  853,  960, 1176, 1280, 1360, 1600, 1920 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[9] = { 240,  272,  480,  544,  664,  720,  768,  900, 1080 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[7] = { 435,  720, 1152, 1280, 1440, 1600, 1680 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[7] = { 272,  480,  720,  800,  900, 1024, 1050 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[3] = { 480,  960, 1280 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[3] = { 205,  410,  548 };
#define DEFAULT_WIDTH  1920
#define DEFAULT_HEIGHT 1080
#define DEFAULT_RI     8
#define DEFAULT_ARI    1
#elif defined(PSP)
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[2] = { 320, 362 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[2] = { 240, 272 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[2] = { 426, 480 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[2] = { 240, 272 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[1] = { 435 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[1] = { 272 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[1] = { 480 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[1] = { 205 };
#define DEFAULT_WIDTH  480
#define DEFAULT_HEIGHT 272
#define DEFAULT_RI     1
#define DEFAULT_ARI    1
#elif defined(WII) || defined(GAMECUBE)
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[3] = { 320, 362, 640 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[3] = { 240, 272, 480 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[3] = { 426, 480, 640 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[3] = { 240, 272, 360 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[2] = { 435, 640 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[2] = { 272, 400 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[2] = { 480, 640 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[2] = { 205, 274 };
#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480
#define DEFAULT_RI     2
#define DEFAULT_ARI    0
#else
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[14] = { 320,  362,  640,  725,  768,  800,  960, 1024, 1152, 1280, 1440, 1600, 1920, 2880 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[14] = { 240,  272,  480,  544,  576,  600,  720,  768,  864,  960, 1080, 1200, 1440, 2160 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[12] = { 426,  480,  853,  960, 1176, 1280, 1360, 1600, 1920, 2560, 3620, 3840 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[12] = { 240,  272,  480,  544,  664,  720,  768,  900, 1080, 1440, 2036, 2160 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[10] = { 435,  720, 1152, 1280, 1440, 1600, 1680, 1920, 2560, 3840 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[10] = { 272,  480,  720,  800,  900, 1024, 1050, 1200, 1600, 2400 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[6] = { 480,  960, 1280, 2560, 3440, 5120 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[6] = { 205,  410,  548, 1080, 1440, 2160 };
#if defined(ANDROID)
#define DEFAULT_WIDTH  SYSTEM_WIDTH
#define DEFAULT_HEIGHT SYSTEM_HEIGHT
#define DEFAULT_RI     0
#define DEFAULT_ARI    0
#else
#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480
#define DEFAULT_RI     2
#define DEFAULT_ARI    0
#endif
#endif

extern void setWidthHeightMults();
extern void updateBorderRects();
extern void setScaling();
extern void SDL_toggleFullscreen();
extern void SDL_toggleIntegerScale();
extern void renderBorderRects();

#endif