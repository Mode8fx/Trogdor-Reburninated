#include "config.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

/*
* @brief A single sprite from a sprite sheet.
* 
* @param texture (SDL2) The sprite texture, with no empty space around the sprite.
* @param surface (SDL1) The sprite surface, with no empty space around the sprite.
* @param w The unscaled width of the sprite, with no empty space.
* @param h The unscaled height of the sprite, with no empty space.
* @param scaled_w The width of the sprite, with no empty space, scaled by screenScale and spriteScale.
* @param scaled_h The height of the sprite, with no empty space, scaled by screenScale and spriteScale.
* @param x_offset_start The unscaled x-position of the first non-colorkeyed pixel.
* @param x_offset_end The unscaled x-position of the last non-colorkeyed pixel.
* @param y_offset_start The unscaled y-position of the first non-colorkeyed pixel.
* @param y_offset_end The unscaled y-position of the last non-colorkeyed pixel.
* @param x_center The midpoint between x_offset_start and x_offset_end, rounded down.
* @param y_center The midpoint between y_offset_start and y_offset_end, rounded down.
*/
struct SpriteSubObject {
#if !defined(SDL1)
    SDL_Texture *texture;
#else
    SDL_Surface *surface;
#endif
    Sint16 w;
    Sint16 h;
    Sint16 scaled_w;
    Sint16 scaled_h;
    Sint8 x_offset_start;
    Sint16 x_offset_end;
    Sint8 y_offset_start;
    Sint16 y_offset_end;
    Sint8 x_center;
    Sint8 y_center;
};

/*
* @brief A sprite sheet.
* 
* @param sub A 2D array containing pointers to malloc'd SpriteSubObjects. sub[i][j] contains the pointer to the SpriteSubObject representing Frame i, Form j.
* @param frame_w The unadjusted width of a single sprite, equal to (sprite sheet width) / (number of frames).
* @param frame_h The unadjusted height of a single sprite, equal to (sprite sheet height) / (number of forms).
* @param spriteScale The scale multiplier of each sprite in the sprite sheet, not accounting for screenScale.
* @param numAnimFrames The number of frames; or, the max number of sprites on one row of the sprite sheet.
* @param numForms The number of forms; or, the max number of sprites on one column of the sprite sheet.
* @param dstrect x and y represent the default position of a sprite, while w and h represent the frame_w and frame_h respectively, each scaled up by spriteScale.
*/
struct SpriteObject {
    SpriteSubObject *sub[8]; // the max number of frames a sprite sheet can have is 8
    Sint16 frame_w;      // the original width of a single animation frame
    Sint16 frame_h;      // the original height of a single animation frame
    double spriteScale;  // the custom scale used for some sprites
    Sint8 numAnimFrames; // e.g. Trogdor has four frames in his walking animation
    Sint8 numForms;      // e.g. Trogdor has two forms (facing left, facing right)
    SDL_Rect dstrect;    // represents the size of a sprite, even if it was resized
};

/*
* @brief A single instance of a sprite (e.g. if there a lot of coins onscreen at the same time, each coin would have its own SpriteInstance).
* 
* @param spriteObj A pointer to the SpriteObject represented by this SpriteInstance.
* @param currSprite A pointer to the texture (SDL2) or surface (SDL1) of the SpriteSubObject being represented by this SpriteInstance.
* @param currSpriteXOffset Equivalent to spriteObj->sub[animFrame][animForm].x_offset_start.
* @param currSpriteYOffset Equivalent to spriteObj->sub[animFrame][animForm].y_offset_start.
* @param srcrect (SDL2) The position (0,0) and size (unscaled) of the currently-represented SpriteSubObject.
* @param srcrect (SDL1) The position (0,0) and size (already scaled according to screenScale and spriteScale) of the currently-represented SpriteSubObject.
* @param dstrect The position (using internal game logic, NOT final screen placement) of the sprite frame (including empty space), and the w and h of the current SpriteSubObject scaled only by spriteScale. Transformations such as x/yOffset, screenScale, and gameToWindowDstRect are applied temporarily as they are needed.
* @param collision The collision rect relative to dstrect x and y (that's sprite frame position, including empty space, according to internal game logic).
* @param isActive Whether or not the sprite is active; usually, this means "is the sprite visible and/or doing things".
* @param facingRight Is the sprite facing right; used for some sprites.
*/
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
extern void sdl1_createTransparentScreen();

#define PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, numAnimFrames, numForms, scale) \
    prepareSprite(&spriteObj, path, numAnimFrames, numForms, scale);                    \
    setSpriteScale(&spriteObj);                                                         \
    setSpritePos(&spriteObj, (int)rect_x, (int)rect_y);

#define PREPARE_SPRITE_BG(spriteObj, path, rect_x, rect_y)          \
    PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, 1, 1, 1);       \
    spriteObj.dstrect.x = (int)(spriteObj.dstrect.x * screenScale); \
    spriteObj.dstrect.y = (int)(spriteObj.dstrect.y * screenScale); \
    spriteObj.dstrect.w = (int)(spriteObj.dstrect.w * screenScale); \
    spriteObj.dstrect.h = (int)(spriteObj.dstrect.h * screenScale);

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