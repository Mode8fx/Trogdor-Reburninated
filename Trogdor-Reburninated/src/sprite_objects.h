#include "config.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

struct SpriteObject {
    SDL_Surface *surface;
    Uint16 frame_w;      // the width of a single frame
    Uint16 frame_h;      // the height of a single animation frame
    Sint8 numAnimFrames; // e.g. Trogdor has four frames in his walking animation
    Sint8 numForms;      // e.g. Trogdor has two forms (facing left, facing right)
    SDL_Rect dstrect;    // only used for static, singular objects (like logos), not objects that are represented by a class (like peasants)
};

extern SDL_Rect outputRect;

extern void prepareSprite(SpriteObject *, const char [], Sint8, Sint8);
extern void setSpriteScale(SpriteObject *, double);
extern void setSpritePos(SpriteObject *, int, int);
extern int  spriteFrame(SpriteObject, Uint8);
extern int  spriteForm(SpriteObject, Uint8);
extern void renderSprite(SpriteObject, SDL_Rect, SDL_Surface *, SDL_Rect);
extern void renderSprite_static(SpriteObject, SDL_Surface *);
extern void renderSprite_static_hiRes(SpriteObject);
extern void drawRect(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRect_gameTextScreen(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRectWithAlpha(SDL_Rect, Uint8, Uint8, Uint8, Uint8);

#define PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, numAnimFrames, numForms, scale) \
    prepareSprite(&spriteObj, path, numAnimFrames, numForms);                           \
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

#endif