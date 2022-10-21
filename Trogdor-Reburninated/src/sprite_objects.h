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
* @param center_x The midpoint between x_offset_start and x_offset_end, rounded down.
* @param center_y The midpoint between y_offset_start and y_offset_end, rounded down.
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
    Uint8 x_offset_start;
    Uint16 x_offset_end;
    Uint8 y_offset_start;
    Uint16 y_offset_end;
    Uint8 center_x;
    Uint8 center_y;
};

/*
* @brief A sprite sheet.
* 
* @param sub A 2D array containing pointers to malloc'd SpriteSubObjects. sub[i][j] contains the pointer to the SpriteSubObject representing Frame i, Form j.
* @param spriteScale The scale multiplier of each sprite in the sprite sheet, not accounting for screenScale.
* @param numFrames The number of frames; or, the max number of sprites on one row of the sprite sheet.
* @param numForms The number of forms; or, the max number of sprites on one column of the sprite sheet.
* @param dstrect x and y represent the default position of a sprite, while w and h represent the original frame width and height (including empty space) respectively, each scaled up by spriteScale.
*/
struct SpriteObject {
    SpriteSubObject *sub[8];
    double spriteScale;
    Sint8 numFrames;
    Sint8 numForms;
    SDL_Rect dstrect;
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
* @param vel_x The x-velocity, used for some SpriteInstances.
* @param vel_y The y-velocity, used for some SpriteInstances.
* @param pos_x The exact x-position, using double precision.
* @param pos_y The exact y-position, using double precision.
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
        Uint8 currSpriteCenterX;
        Uint8 currSpriteCenterY;
        SDL_Rect srcrect;
        SDL_Rect dstrect;
        double vel_x;
        double vel_y;
        double pos_x;
        double pos_y;
        Sint8 animFrame;
        Sint8 animForm;
        Sint8 animFrameTime;
        Uint8 animFrameCounter;
        Sint8 animFormTime;
        Uint8 animFormCounter;
        SDL_Rect collision;
        bool isActive;
        bool facingRight;
        SpriteInstance() {
        }
        SpriteInstance(SpriteObject *, Sint8, Sint8);
        SpriteInstance(SpriteObject *, Sint8, Sint8, double, double);
        void setFrame(Sint8);
        void setForm(Sint8);
        void setFrameAndForm(Sint8, Sint8);
        void animateFrame();
        void animateForm();
        void updateCurrSprite();
        void moveSprite();
        void setPosX(double);
        void setPosY(double);
        void addPosX(double);
        void addPosY(double);
        void setPos(double, double);
        void renderSprite_game();
        void renderSpriteAsCSO_game();
        void renderSprite_app();
        void renderSprite_overlay();
        void renderEmptyOverlay();
        void prepareAsCSO(double, double, Sint8, Sint8, Sint8, Sint8, double, double);
        void renderAsCSO(bool);
};

extern SDL_Rect outputRect;

extern void prepareSprite(SpriteObject *, const char [], Sint8, Sint8, double);
extern void setSpriteScale(SpriteObject *);
extern void setSpritePos(SpriteObject *, int, int);
extern void drawRect(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRect_gameTextScreen(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRectWithAlpha(SDL_Rect, Uint8, Uint8, Uint8, Uint8);
extern void sdl1_createTransparentScreen();

#define PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, numFrames, numForms, scale) \
    prepareSprite(&spriteObj, path, numFrames, numForms, scale);                    \
    setSpritePos(&spriteObj, (int)rect_x, (int)rect_y);

#define PREPARE_SPRITE_BG(spriteObj, path, rect_x, rect_y) \
    PREPARE_SPRITE(spriteObj, path, rect_x, rect_y, 1, 1, 1);

#define OBJ_TO_MID_SCREEN_X(width, obj) \
    ((width - obj.dstrect.w) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION_X(width, obj, val) \
    (((double)width * val) - (obj.dstrect.w / 2))

#define OBJ_TO_MID_SCREEN_Y(height, obj) \
    ((height - obj.dstrect.h) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION_Y(height, obj, val) \
    (((double)height * val) - (obj.dstrect.h / 2))

#define OBJ_FRAME_TO_MID_SCREEN_X(width, obj) \
    ((width - obj.dstrect.w) / 2)

#define OBJ_FRAME_TO_SCREEN_AT_FRACTION_X(width, obj, val) \
    (((double)width * val) - (obj.dstrect.w / 2))

#define OBJ_FRAME_TO_MID_SCREEN_Y(height, obj) \
    ((height - obj.dstrect.h) / 2)

#define OBJ_FRAME_TO_SCREEN_AT_FRACTION_Y(height, obj, val) \
    (((double)height * val) - (obj.dstrect.h / 2))

#endif