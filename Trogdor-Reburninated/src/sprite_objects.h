#include "config.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

struct SpriteSubObject {
#if !defined(SDL1)
    SDL_Texture *texture;
#else
    SDL_Surface *surface;
#endif
    Sint16 w;
    Sint16 h;
    Sint8 x_offset_start;
    Sint16 x_offset_end;
    Sint8 y_offset_start;
    Sint16 y_offset_end;
    Sint8 x_center;
    Sint8 y_center;
};

struct SpriteObject {
    SpriteSubObject *sub[8]; // the max number of frames a sprite sheet can have is 8
    Sint16 frame_w;      // the original width of a single animation frame
    Sint16 frame_h;      // the original height of a single animation frame
    double spriteScale;  // the custom scale used for some sprites
    Sint8 numAnimFrames; // e.g. Trogdor has four frames in his walking animation
    Sint8 numForms;      // e.g. Trogdor has two forms (facing left, facing right)
    SDL_Rect dstrect;    // represents the size of a sprite, even if it was resized
};

class SpriteInstance {
    public:
        SpriteObject *spriteObj;
#if !defined(SDL1)
        SDL_Texture *currSprite;
#else
        SDL_Surface *currSprite;
#endif
        Sint8 currSpriteXOffset;
        Sint8 currSpriteYOffset;
        SDL_Rect srcrect;
        SDL_Rect dstrect;
        Sint8 animFrame;
        Sint8 animForm;
        SDL_Rect collision;
        bool isActive;
        bool facingRight;
        SpriteInstance() {
        }
        SpriteInstance(SpriteObject *, Sint8, Sint8);
        SpriteInstance(SpriteObject *, Sint8, Sint8, int, int);
        void setFrame(Sint8);
        void setForm(Sint8);
        void setFrameAndForm(Sint8, Sint8);
        void updateCurrSprite();
        void renderSprite_game();
        void renderSprite_app();
        void renderSprite_overlay();
        void renderEmptyOverlay();
};

extern SDL_Rect outputRect;

extern void prepareSprite(SpriteObject *, const char [], Sint8, Sint8, double);
extern void setSpriteScale(SpriteObject *);
extern void setSpritePos(SpriteObject *, int, int);
extern void drawRect(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRect_gameTextScreen(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRectWithAlpha(SDL_Rect, Uint8, Uint8, Uint8, Uint8);

#define PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, numAnimFrames, numForms, scale) \
    prepareSprite(&spriteObj, path, numAnimFrames, numForms, scale);                    \
    setSpriteScale(&spriteObj);                                                         \
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