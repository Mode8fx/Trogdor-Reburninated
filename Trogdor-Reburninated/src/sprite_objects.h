#include "include.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

#if defined(SDL1)
inline bool SDL_HasIntersection(const SDL_Rect *A, const SDL_Rect *B);
#endif

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
    SpriteSubObject *sub[9];
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
* @param dstrect The position (using internal game logic, NOT final screen placement) of the sprite frame (including empty space), and the w and h of the current SpriteSubObject scaled only by spriteScale. Transformations such as x/yOffset, screenScale, and gameToWindowDstRect are applied temporarily as they are needed.
* @param vel_x The x-velocity, used for some SpriteInstances.
* @param vel_y The y-velocity, used for some SpriteInstances.
* @param pos_x The exact x-position, using double precision.
* @param pos_y The exact y-position, using double precision.
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
        float vel_x;
        float vel_y;
        float pos_x;
        float pos_y;
        Sint8 animFrame;
        Sint8 animForm;
        Sint8 animFrameTime;
        float animFrameCounter;
        Sint8 animFormTime;
        float animFormCounter;
        SDL_Rect collision;
        bool isActive;
        bool facingRight;
        SpriteInstance() {
        }
        SpriteInstance(SpriteObject *, Sint8, Sint8);
        SpriteInstance(SpriteObject *, Sint8, Sint8, float, float);
        void setFrame(Sint8);
        void setForm(Sint8);
        void setFrameAndForm(Sint8, Sint8);
        void animateFrame();
        void animateForm();
        void animateWrap();
        void updateCurrSprite();
        void moveSprite();
        void setPosX(float);
        void setPosY(float);
        void addPosX(float);
        void addPosY(float);
        void setPos(float, float);
        void renderSprite_game();
        void renderSpriteAsCSO_game();
        void renderSprite_app();
        void renderSprite_menu();
        void renderSprite_overlay();
        void renderEmptyOverlay();
        void prepareAsCSO(float, float, Sint8, Sint8, Sint8, Sint8, float, float);
        void renderAsCSO(bool);
};

extern Uint32 getPixel(SDL_Surface *surface, int x, int y);
extern Sint8 getXOffsetStart(SpriteObject *spriteObj, Sint8 x, Sint8 y);
extern Sint16 getXOffsetEnd(SpriteObject *spriteObj, Sint8 x, Sint8 y);
extern Sint8 getYOffsetStart(SpriteObject *spriteObj, Sint8 x, Sint8 y);
extern Sint16 getYOffsetEnd(SpriteObject *spriteObj, Sint8 x, Sint8 y);
extern void prepareSurfaceFromSpriteSheet(SpriteObject *spriteObj);
extern void prepareSprite(SpriteObject *, unsigned char[], unsigned int, Sint8, Sint8, double, bool, bool);
extern void setSpriteScale(SpriteObject *);
extern void setSpritePos(SpriteObject *, int, int);
extern void drawRect(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRect_gameTextScreen(SDL_Rect, Uint8, Uint8, Uint8);
extern void drawRectWithAlpha(SDL_Rect, Uint8, Uint8, Uint8, Uint8);
extern void sdl1_createTransparentScreen();

#define PREPARE_SPRITE(spriteObj, sprite_data, sprite_len, rect_x, rect_y, numFrames, numForms, scale) \
    prepareSprite(&spriteObj, sprite_data, sprite_len, numFrames, numForms, scale, false, true);       \
    setSpritePos(&spriteObj, (int)rect_x, (int)rect_y);

#define PREPARE_SPRITE_OPAQUE(spriteObj, sprite_data, sprite_len, rect_x, rect_y, numFrames, numForms, scale) \
    prepareSprite(&spriteObj, sprite_data, sprite_len, numFrames, numForms, scale, false, false);             \
    setSpritePos(&spriteObj, (int)rect_x, (int)rect_y);

#define PREPARE_SPRITE_MENU(spriteObj, sprite_data, sprite_len, rect_x, rect_y, numFrames, numForms, scale) \
    prepareSprite(&spriteObj, sprite_data, sprite_len, numFrames, numForms, scale, true, true);             \
    setSpritePos(&spriteObj, (int)rect_x, (int)rect_y);

#define PREPARE_SPRITE_MENU_OPAQUE(spriteObj, sprite_data, sprite_len, rect_x, rect_y, numFrames, numForms, scale) \
    prepareSprite(&spriteObj, sprite_data, sprite_len, numFrames, numForms, scale, true, false);                   \
    setSpritePos(&spriteObj, (int)rect_x, (int)rect_y);

#define PREPARE_SPRITE_BG(spriteObj, sprite_data, sprite_len, rect_x, rect_y) \
    PREPARE_SPRITE_OPAQUE(spriteObj, sprite_data, sprite_len, rect_x, rect_y, 1, 1, 1);

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

extern SpriteObject sprite_videlectrix_logo;
extern SpriteInstance sprite_videlectrix_logo_ins;
extern SpriteObject sprite_title_screen;
extern SpriteInstance sprite_title_screen_ins;
extern SpriteObject sprite_trogdor_logo;
extern SpriteInstance sprite_trogdor_logo_ins;
extern SpriteObject sprite_level_background_1;
extern SpriteObject sprite_level_background_2;
extern SpriteObject sprite_level_background_3;
extern SpriteObject sprite_level_background_4;
extern SpriteObject sprite_level_background_th;
extern SpriteObject *sprite_level_background;
extern SpriteObject sprite_burnination_meter_full;
extern SpriteObject sprite_burnination_meter_empty;
extern SpriteInstance sprite_burnination_meter_empty_ins;
extern SpriteObject sprite_end_of_level_flash;
extern SpriteInstance sprite_end_of_level_flash_ins;
extern SpriteObject sprite_death_message;
extern SpriteObject sprite_burninate_text;
extern SpriteObject sprite_burninate_fire;
extern SpriteObject sprite_level_beaten_trogdor;
extern SpriteObject sprite_level_beaten_smoke;
extern SpriteObject sprite_game_over_trogdor;
extern SpriteObject sprite_overlay_basement_top;
extern SpriteInstance sprite_overlay_basement_top_ins;
extern SpriteObject sprite_overlay_basement_bottom;
extern SpriteInstance sprite_overlay_basement_bottom_ins;
//extern SpriteObject sprite_overlay_basement_left;
//extern SpriteInstance sprite_overlay_basement_left_ins;
//extern SpriteObject sprite_overlay_basement_right;
//extern SpriteInstance sprite_overlay_basement_right_ins;
extern SpriteObject sprite_overlay_compy_top;
extern SpriteInstance sprite_overlay_compy_top_ins;
extern SpriteObject sprite_overlay_compy_bottom;
extern SpriteInstance sprite_overlay_compy_bottom_ins;
//extern SpriteObject sprite_overlay_compy_left;
//extern SpriteInstance sprite_overlay_compy_left_ins;
//extern SpriteObject sprite_overlay_compy_right;
//extern SpriteInstance sprite_overlay_compy_right_ins;
extern SpriteObject sprite_overlay_strong_badia_top;
extern SpriteInstance sprite_overlay_strong_badia_top_ins;
extern SpriteObject sprite_overlay_strong_badia_bottom;
extern SpriteInstance sprite_overlay_strong_badia_bottom_ins;
//extern SpriteObject sprite_overlay_strong_badia_left;
//extern SpriteInstance sprite_overlay_strong_badia_left_ins;
//extern SpriteObject sprite_overlay_strong_badia_right;
//extern SpriteInstance sprite_overlay_strong_badia_right_ins;
extern SDL_Rect right_overlay_padding;
extern SpriteObject sprite_trogdor;
extern SpriteObject sprite_trogdor_bighead;
extern SpriteObject sprite_cottage;
extern SpriteObject sprite_cottage_fire;
extern SpriteObject sprite_peasantometer_icon;
extern Uint8        sprite_peasantometer_icon_init_x;
extern int          sprite_peasantometer_icon_step;
extern SpriteObject sprite_archer;
extern SpriteObject sprite_arrow;
extern SpriteObject sprite_trogdor_fire;
extern SpriteObject sprite_trogdor_dead;
extern SpriteObject sprite_knight;
extern SpriteObject sprite_peasant;
extern SpriteObject sprite_end_of_level_trogdor;
extern SpriteObject sprite_loot;
extern SpriteObject sprite_trogdor_flexing;
extern SpriteObject sprite_trogdor_ending;
extern SpriteObject sprite_heart;
extern SpriteObject sprite_knight_funnyjoke;
extern SpriteObject sprite_arrow_funnyjoke;
extern SpriteObject sprite_kerrek;
extern SpriteObject sprite_kerrek_smoked;
extern SpriteObject sprite_strong_bad;
extern SpriteObject sprite_strong_bad_ending;
extern SpriteObject sprite_cursor;
extern SpriteObject sprite_menu_cursor;
extern SpriteObject sprite_menu_background;
extern SpriteInstance sprite_menu_background_ins;
//extern SpriteObject sprite_game_over_banner;
extern SpriteObject sprite_game_over_text;
extern SpriteObject sprite_game_over_jonathan_howe;
extern SDL_Rect     divider_level_beaten_rect;

#endif