#include "config.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

struct SpriteObject {
    SDL_Surface *surface;
    SDL_Rect srcrect, dstrect;
};

#if !defined(SDL1)
#define PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, numSprites_x, numSprites_y, scale)   \
    spriteObj.srcrect = { 0, 0, 0, 0 };                                                      \
    spriteObj.dstrect = { 0, 0, 0, 0 };                                                      \
    temp = IMG_Load(path);                                                                   \
    SDL_SetColorKey(temp, SDL_TRUE, 0xFF00FF);                                               \
    spriteObj.surface = SDL_ConvertSurfaceFormat(temp, SDL_GetWindowPixelFormat(window), 0); \
    SDL_FreeSurface(temp);                                                                   \
    spriteObj.srcrect.w = spriteObj.surface->w / numSprites_x;                               \
    spriteObj.srcrect.h = spriteObj.surface->h / numSprites_y;                               \
    SET_SPRITE_SCALE(spriteObj, scale);                                                      \
	spriteObj.dstrect.x = (int)rect_x;                                                       \
    spriteObj.dstrect.y = (int)rect_y;
#else
#define PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, numSprites_x, numSprites_y, scale) \
    spriteObj.srcrect = { 0, 0, 0, 0 };                                                    \
    spriteObj.dstrect = { 0, 0, 0, 0 };                                                    \
    temp = IMG_Load(path);                                                                 \
    SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0xFF00FF);                                      \
    spriteObj.surface = SDL_DisplayFormat(temp);                                           \
    SDL_FreeSurface(temp);                                                                 \
    spriteObj.srcrect.w = spriteObj.surface->w / numSprites_x;                             \
    spriteObj.srcrect.h = spriteObj.surface->h / numSprites_y;                             \
    SET_SPRITE_SCALE(spriteObj, scale);                                                    \
	spriteObj.dstrect.x = (int)rect_x;                                                     \
    spriteObj.dstrect.y = (int)rect_y;
#endif


#define RENDER_SPRITE(spriteObj) \
    SDL_BlitSurface(spriteObj.surface, &spriteObj.srcrect, gameScreen, &spriteObj.dstrect);

#define RENDER_SPRITE_ALT(spriteObj) \
    SDL_BlitSurface(spriteObj->surface, &spriteObj->srcrect, gameScreen, &spriteObj->dstrect);

#define RENDER_SPRITE_AT_RECT(spriteObj, rect) \
    SDL_BlitSurface(spriteObj.surface, &spriteObj.srcrect, gameScreen, &rect);

#define RENDER_SPRITE_USING_RECTS(spriteObj, srect, drect) \
    SDL_BlitSurface(spriteObj.surface, &srect, gameScreen, &drect);

// [SDL1] RENDER_SPRITE() makes color key transparent, but does NOT scale.
// [SDL1] RENDER_SPRITE_SCALED() does NOT make color key transparent, but does scale. Pick your poison...
#define RENDER_SPRITE_SCALED(spriteObj) \
    SDL_SoftStretch(spriteObj.surface, &spriteObj.srcrect, gameScreen, &spriteObj.dstrect);

#define RENDER_SPRITE_SCALED_ALT(spriteObj) \
    SDL_SoftStretch(spriteObj->surface, &spriteObj->srcrect, gameScreen, &spriteObj->dstrect);

#define SET_SPRITE_SCALE(spriteObj, scale)                                                             \
    spriteObj.dstrect.w = (int)(spriteObj.srcrect.w * min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT) * scale); \
    spriteObj.dstrect.h = (int)(spriteObj.srcrect.h * min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT) * scale);

#define DRAW_RECT(rect, r, g, b) \
    SDL_FillRect(gameScreen, &rect, ((r<<16) + (g<<8) + (b)));

#define DRAW_RECT_WITH_ALPHA(rect, r, g, b, a) \
    SDL_FillRect(gameScreen, &rect, ((a<<24) + (r<<16) + (g<<8) + (b)));

#define OBJ_TO_MID_SCREEN_X(obj) \
    ((GAME_WIDTH - obj.dstrect.w) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION_X(obj, val) \
    ((GAME_WIDTH * val) - (obj.dstrect.w / 2))

#define OBJ_TO_MID_SCREEN_Y(obj) \
    ((GAME_HEIGHT - obj.dstrect.h) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION_Y(obj, val) \
    ((GAME_HEIGHT * val) - (obj.dstrect.h / 2))

#endif