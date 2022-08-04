#include "sprite_objects.h"

SDL_Rect outputRect;
SDL_Surface *temp;

void prepareSprite(SpriteObject *spriteObj, const char path[], int numSprites_x, int numSprites_y, float scale) {
    spriteObj->srcrect = { 0, 0, 0, 0 };
    spriteObj->dstrect = { 0, 0, 0, 0 };
    temp = IMG_Load(path);
#if !defined(SDL1)
    SDL_SetColorKey(temp, SDL_TRUE, 0xFF00FF);
    spriteObj->surface = SDL_ConvertSurfaceFormat(temp, SDL_GetWindowPixelFormat(window), 0);
#else
    SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0xFF00FF);
    spriteObj.surface = SDL_DisplayFormat(temp);
#endif
    SDL_FreeSurface(temp);
    spriteObj->srcrect.w = spriteObj->surface->w / numSprites_x;
    spriteObj->srcrect.h = spriteObj->surface->h / numSprites_y;
    setSpriteScale(spriteObj, scale);
}

void setSpritePos(SpriteObject *spriteObj, int rect_x, int rect_y) {
    spriteObj->dstrect.x = (int)rect_x;
    spriteObj->dstrect.y = (int)rect_y;
}

void renderSprite(SpriteObject spriteObj) {
    outputRect = spriteObj.dstrect;
    SDL_BlitSurface(spriteObj.surface, &spriteObj.srcrect, gameScreen, &outputRect);
}

void renderSpriteAtRect(SpriteObject spriteObj, SDL_Rect rect) {
    outputRect = rect;
    SDL_BlitSurface(spriteObj.surface, &spriteObj.srcrect, gameScreen, &outputRect);
}

void renderSpriteUsingRects(SpriteObject spriteObj, SDL_Rect srect, SDL_Rect drect) {
    outputRect = drect;
    SDL_BlitSurface(spriteObj.surface, &srect, gameScreen, &outputRect);
}

// [SDL1] renderSprite() makes color key transparent, but does NOT scale.
// [SDL1] renderSpriteScaled() does NOT make color key transparent, but does scale. Pick your poison...
void renderSpriteScaled(SpriteObject spriteObj) {
    outputRect = spriteObj.dstrect;
    SDL_SoftStretch(spriteObj.surface, &spriteObj.srcrect, gameScreen, &outputRect);
}

void setSpriteScale(SpriteObject *spriteObj, float scale) {
    spriteObj->dstrect.w = (int)(spriteObj->srcrect.w * min(gameWidthMult, gameHeightMult) * scale);
    spriteObj->dstrect.h = (int)(spriteObj->srcrect.h * min(gameWidthMult, gameHeightMult) * scale);
}

void drawRect(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b) {
    SDL_FillRect(gameScreen, &rect, ((r << 16) + (g << 8) + (b)));
}

void DRAW_RECT_WITH_ALPHA(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_FillRect(gameScreen, &rect, ((a << 24) + (r << 16) + (g << 8) + (b)));
}