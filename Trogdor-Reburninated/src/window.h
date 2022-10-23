#ifndef WINDOW_H
#define WINDOW_H

#include "config.h"
#include "media_objects_init.h"

constexpr auto gameWidth = 250;
constexpr auto gameHeight = 180;
constexpr auto DEFAULT_FRAME_RATE = 16;
constexpr auto TWIPS_PER_PIXEL = 20;

extern Uint16 gameHiResWidth;
extern Uint16 gameHiResHeight;
extern Uint16 appWidth;
extern Uint16 appHeight;
extern double gameWidthMult; // game scaling relative to app
extern double gameHeightMult; // game scaling relative to app
extern double gameHiResMult; // hi-res screen scaling
extern Uint16 windowWidth;
extern Uint16 windowHeight;
extern double appWidthMult; // app scaling relative to window
extern double appHeightMult; // app scaling relative to window
extern Uint16 frameRate;
extern Uint32 ticksPerFrame;

#if !defined(SDL1)
extern SDL_Window *window;
extern SDL_Renderer *renderer;
#else
extern SDL_Surface *windowScreen;
extern SDL_Surface *transparentScreen;
#endif
extern SDL_Rect gameSrcRect;
//extern SDL_Rect gameToAppDstRect; // game screen mapping to app
extern SDL_Rect gameHiResSrcRect;
extern SDL_Rect appSrcRect;
extern SDL_Rect appToWindowDstRect; // app mapping to window
extern SDL_Rect gameToWindowDstRect; // game screen mapping to window
extern SDL_Rect menuToWindowDstRect; // menu mapping to window

extern bool isWindowed;
extern double screenScale; // the multiplier by which graphics should be scaled via SDL_gfx; caps out at 2
extern int trueScreenScaleInt; // the multiplier by which the screen should be scaled via renderer
extern double trueScreenScaleFull; // the multiplier by which the screen should be scaled via renderer
extern double screenScale_menu;
extern bool allowHiRes;
extern Sint8 scalingType;
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
constexpr auto DEFAULT_WIDTH = 1280;
constexpr auto DEFAULT_HEIGHT = 720;
#elif defined(VITA)
constexpr auto DEFAULT_WIDTH = 960;
constexpr auto DEFAULT_HEIGHT = 544;
#elif defined(SWITCH)
constexpr auto DEFAULT_WIDTH = 1920;
constexpr auto DEFAULT_HEIGHT = 1080;
#elif defined(PSP)
constexpr auto DEFAULT_WIDTH = 480;
constexpr auto DEFAULT_HEIGHT = 272;
#elif defined(WII) || defined(GAMECUBE) || defined(XBOX)
constexpr auto DEFAULT_WIDTH = 640;
constexpr auto DEFAULT_HEIGHT = 480;
#elif defined(THREEDS)
constexpr auto DEFAULT_WIDTH = 400;
constexpr auto DEFAULT_HEIGHT = 240;
#elif defined(ANDROID)
#define DEFAULT_WIDTH  SYSTEM_WIDTH
#define DEFAULT_HEIGHT SYSTEM_HEIGHT
#elif defined(SDL1)
constexpr auto DEFAULT_WIDTH = 320;
constexpr auto DEFAULT_HEIGHT = 240;
#else
constexpr auto DEFAULT_WIDTH = 640;
constexpr auto DEFAULT_HEIGHT = 480;
#endif

extern void setWidthHeightMults();
extern void setScaling();
extern void snapWindow_x(double, Uint16);
extern void snapWindow_y(double, Uint16);
extern void SDL_toggleFullscreen();
extern void InitializeMenus(); // this is in menu.cpp

#endif