#include "shared.h"
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

extern void setWidthHeightMults();
extern void updateBorderRects();
extern void setScaling();
extern void SDL_toggleFullscreen();
extern void SDL_toggleIntegerScale();
extern void renderBorderRects();

#endif