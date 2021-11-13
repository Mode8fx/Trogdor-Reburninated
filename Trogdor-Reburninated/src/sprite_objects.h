#include "config.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

#if !defined(SDL1)

struct SpriteObject {
    SDL_Texture *texture;
    SDL_Rect srcrect, dstrect;
};

#define PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, numSprites_x, numSprites_y, scale)       \
    spriteObj.srcrect = { 0, 0, 0, 0 };                                                          \
    spriteObj.dstrect = { 0, 0, 0, 0 };                                                          \
    temp = IMG_Load(path);                                                                       \
    SDL_SetColorKey(temp, SDL_TRUE, 0xFF00FF);                                                   \
    spriteObj.texture = SDL_CreateTextureFromSurface(renderer, temp);                            \
    SDL_FreeSurface(temp);                                                                       \
    SDL_QueryTexture(spriteObj.texture, NULL, NULL, &spriteObj.srcrect.w, &spriteObj.srcrect.h); \
    spriteObj.srcrect.w /= numSprites_x;                                                         \
    spriteObj.srcrect.h /= numSprites_y;                                                         \
    SET_SPRITE_SCALE(spriteObj, scale);                                                          \
	spriteObj.dstrect.x = (int)rect_x;                                                           \
    spriteObj.dstrect.y = (int)rect_y;

#define RENDER_SPRITE(spriteObj) \
    SDL_RenderCopy(renderer, spriteObj.texture, &spriteObj.srcrect, &spriteObj.dstrect);

#define RENDER_SPRITE_ALT(spriteObj) \
    SDL_RenderCopy(renderer, spriteObj->texture, &spriteObj->srcrect, &spriteObj->dstrect);

#define SET_SPRITE_SCALE(spriteObj, scale)                                                             \
    spriteObj.dstrect.w = (int)(spriteObj.srcrect.w * min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT) * scale); \
    spriteObj.dstrect.h = (int)(spriteObj.srcrect.h * min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT) * scale);

#define DRAW_RECT(rect, r, g, b)                    \
    SDL_SetRenderDrawColor(renderer, r, g, b, 255); \
    SDL_RenderFillRect(renderer, &rect);

#else

struct SpriteObject {
    SDL_Surface *surface;
    SDL_Rect srcrect, dstrect;
};

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

// Makes color key transparent, but does NOT scale
#define RENDER_SPRITE(spriteObj) \
    SDL_BlitSurface(spriteObj.surface, &spriteObj.srcrect, screen, &spriteObj.dstrect);

#define RENDER_SPRITE_ALT(spriteObj) \
    SDL_BlitSurface(spriteObj->surface, &spriteObj->srcrect, screen, &spriteObj->dstrect);

// Scales, but does NOT make color key transparent. Pick your poison...
#define RENDER_SPRITE_SCALED(spriteObj) \
    SDL_SoftStretch(spriteObj.surface, &spriteObj.srcrect, screen, &spriteObj.dstrect);

#define RENDER_SPRITE_SCALED_ALT(spriteObj) \
    SDL_SoftStretch(spriteObj->surface, &spriteObj->srcrect, screen, &spriteObj->dstrect);

#define SET_SPRITE_SCALE(spriteObj, scale)                                                             \
    spriteObj.dstrect.w = (int)(spriteObj.srcrect.w * min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT) * scale); \
    spriteObj.dstrect.h = (int)(spriteObj.srcrect.h * min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT) * scale);

#define DRAW_RECT(rect, r, g, b) \
    SDL_FillRect(screen, &rect, ((r<<16) + (g<<8) + (b)));

#endif


#define OBJ_TO_MID_SCREEN_X(obj) \
    ((GAME_WIDTH - obj.dstrect.w) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION_X(obj, val) \
    ((GAME_WIDTH * val) - (obj.dstrect.w / 2))

#define OBJ_TO_MID_SCREEN_Y(obj) \
    ((GAME_HEIGHT - obj.dstrect.h) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION_Y(obj, val) \
    ((GAME_HEIGHT * val) - (obj.dstrect.h / 2))

#endif