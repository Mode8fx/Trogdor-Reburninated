#include "config.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

struct SpriteObject {
    SDL_Surface *surface;
    SDL_Rect srcrect, dstrect;
};

extern SDL_Rect outputRect;

extern void prepareSprite(SpriteObject *, const char [], int, int);
extern void setSpriteScale(SpriteObject *, double);
extern void setSpritePos(SpriteObject *, int, int);
extern void renderSprite(SpriteObject);
extern void renderSprite_app(SpriteObject);
extern void renderSprite_hiRes(SpriteObject);
extern void renderSpriteAtRect(SpriteObject, SDL_Rect);
extern void renderSpriteUsingRects(SpriteObject, SDL_Rect, SDL_Rect);
extern void renderSpriteScaled(SpriteObject);
extern void drawRect(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRect_gameTextScreen(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRectWithAlpha(SDL_Rect, Uint8, Uint8, Uint8, Uint8);

#define PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, numSprites_x, numSprites_y, scale) \
    prepareSprite(&spriteObj, path, numSprites_x, numSprites_y);                           \
    setSpriteScale(&spriteObj, scale);                                                     \
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