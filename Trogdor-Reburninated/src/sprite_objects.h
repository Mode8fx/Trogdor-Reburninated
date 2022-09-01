#include "config.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

struct SpriteObject {
#if !defined(SDL1)
    SDL_Texture *texture;
#else
    SDL_Surface *surface;
#endif
    Sint16 frame_w;      // the original width of a single animation frame
    Sint16 frame_h;      // the original height of a single animation frame
    Uint16 scaled_w;     // the scaled (actual) width of a single animation frame
    Uint16 scaled_h;     // the scaled (actual) height of a single animation frame
    Sint8 numAnimFrames; // e.g. Trogdor has four frames in his walking animation
    Sint8 numForms;      // e.g. Trogdor has two forms (facing left, facing right)
    SDL_Rect dstrect;    // represents the size of a sprite, even if it was resized
};

extern SDL_Rect outputRect;

extern void prepareSprite(SpriteObject *, const char [], Sint8, Sint8, double);
extern void setSpriteScale(SpriteObject *, double);
extern void setSpritePos(SpriteObject *, int, int);
extern Sint16 spriteFrame(SpriteObject, Sint8);
extern Sint16 spriteForm(SpriteObject, Sint8);
extern void renderSprite_game(SpriteObject, SDL_Rect, SDL_Rect);
extern void renderSprite_app(SpriteObject, SDL_Rect, SDL_Rect);
extern void renderSprite_static_game(SpriteObject);
extern void renderSprite_static_app(SpriteObject);
extern void drawRect(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRect_gameTextScreen(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRectWithAlpha(SDL_Rect, Uint8, Uint8, Uint8, Uint8);

#define PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, numAnimFrames, numForms, scale) \
    prepareSprite(&spriteObj, path, numAnimFrames, numForms, scale);                    \
    setSpriteScale(&spriteObj, scale);                                                  \
    setSpritePos(&spriteObj, (int)rect_x, (int)rect_y);

#define OBJ_TO_MID_SCREEN_X(width, obj) \
    ((width - obj.dstrect.w) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION_X(width, obj, val) \
    (((double)width * val) - (obj.dstrect.w / 2))

#define OBJ_TO_MID_SCREEN_Y(height, obj) \
    ((height - obj.dstrect.h) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION_Y(height, obj, val) \
    (((double)height * val) - (obj.dstrect.h / 2))

#define OBJ_FRAME_TO_MID_SCREEN_X(width, obj) \
    ((width - obj.frame_w) / 2)

#define OBJ_FRAME_TO_SCREEN_AT_FRACTION_X(width, obj, val) \
    (((double)width * val) - (obj.frame_w / 2))

#define OBJ_FRAME_TO_MID_SCREEN_Y(height, obj) \
    ((height - obj.frame_h) / 2)

#define OBJ_FRAME_TO_SCREEN_AT_FRACTION_Y(height, obj, val) \
    (((double)height * val) - (obj.frame_h / 2))

#endif