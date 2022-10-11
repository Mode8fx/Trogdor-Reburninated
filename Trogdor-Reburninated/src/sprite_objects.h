#include "config.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

struct SpriteSubObject {
#if !defined(SDL1)
    SDL_Texture *texture;
#else
    SDL_Surface *surface;
#endif
    Sint8 x_offset_start;
    Sint8 x_offset_end;
    Sint8 y_offset_start;
    Sint8 y_offset_end;
    Sint8 x_center;
    Sint8 y_center;
};

struct SpriteObject {
    SpriteSubObject *sub[8]; // the max number of frames a sprite sheet can have is 8
    Sint16 frame_w;      // the original width of a single animation frame
    Sint16 frame_h;      // the original height of a single animation frame
    Uint16 scaled_w;     // the scaled (actual) width of a single animation frame
    Uint16 scaled_h;     // the scaled (actual) height of a single animation frame
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
            SpriteInstance(NULL, 0, 0);
        }
        SpriteInstance(SpriteObject *spriteObj, Sint8 frame, Sint8 form) {
            spriteObj = spriteObj;
            resetSrcrect();
            dstrect = spriteObj->dstrect;
            setFrame(frame);
            setForm(form);
        }
        void resetSrcrect() {
            srcrect = { 0, 0, spriteObj->scaled_w, spriteObj->scaled_h };
        }
        void setFrame(Sint8 frame) {
            animFrame = frame;
            srcrect.x = spriteObj->scaled_w * animFrame;
        }
        void setForm(Sint8 form) {
            animForm = form;
            srcrect.y = spriteObj->scaled_h * animForm;
        }
        void updateCurrSprite() {
#if !defined(SDL1)
            currSprite = spriteObj->sub[animFrame][animForm].texture;
#else
            currSprite = spriteObj->sub[animFrame][animForm].surface;
#endif
            currSpriteXOffset = spriteObj->sub[animFrame][animForm].x_offset_start;
            currSpriteYOffset = spriteObj->sub[animFrame][animForm].y_offset_start;
        }
        void renderSprite_game() {
            outputRect = dstrect;
            outputRect.x = (int)(outputRect.x * screenScale) + gameToWindowDstRect.x + currSpriteXOffset;
            outputRect.y = (int)(outputRect.y * screenScale) + gameToWindowDstRect.y + currSpriteYOffset;
            outputRect.w = (int)(outputRect.w * screenScale);
            outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
            SDL_RenderCopy(renderer, currSprite, &srcrect, &outputRect);
#else
            SDL_BlitSurface(currSprite, &srcrect, windowScreen, &outputRect);
#endif
        }
        void renderSprite_app() {
            outputRect = dstrect;
            outputRect.x = (int)(outputRect.x * screenScale) + appToWindowDstRect.x + currSpriteXOffset;
            outputRect.y = (int)(outputRect.y * screenScale) + appToWindowDstRect.y + currSpriteYOffset;
            outputRect.w = (int)(outputRect.w * screenScale);
            outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
            SDL_RenderCopy(renderer, currSprite, &srcrect, &outputRect);
#else
            SDL_BlitSurface(currSprite, &srcrect, windowScreen, &outputRect);
#endif
        }
        void renderSprite_overlay() {
            outputRect = dstrect;
            outputRect.w = (int)(outputRect.w * screenScale);
            outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
            SDL_RenderCopy(renderer, currSprite, NULL, &outputRect);
#else
            SDL_BlitSurface(currSprite, NULL, windowScreen, &outputRect);
#endif
        }
        void renderEmptyOverlay() {
            outputRect = dstrect;
            outputRect.w = (int)(outputRect.w * screenScale);
            outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
            SDL_RenderFillRect(renderer, &outputRect);
#else
            SDL_FillRect(windowScreen, &outputRect, 0);
#endif
        }
};

extern SDL_Rect outputRect;

extern void prepareSprite(SpriteObject *, const char [], Sint8, Sint8, double);
extern void setSpriteScale(SpriteObject *, double);
extern void setSpritePos(SpriteObject *, int, int);
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