#include "sprite_objects.h"

SDL_Rect outputRect;
SDL_Surface *temp;

void prepareSprite(SpriteObject *spriteObj, const char path[], Sint8 numAnimFrames, Sint8 numForms) {
    temp = IMG_Load(path);
#if !defined(SDL1)
    SDL_SetColorKey(temp, SDL_TRUE, 0xFF00FF);
    spriteObj->surface = SDL_ConvertSurfaceFormat(temp, SDL_GetWindowPixelFormat(window), 0);
#else
    SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0xFF00FF);
    spriteObj->surface = SDL_DisplayFormat(temp);
#endif
    SDL_FreeSurface(temp);
    spriteObj->numAnimFrames = numAnimFrames;
    spriteObj->numForms = numForms;
    spriteObj->frame_w = spriteObj->surface->w / numAnimFrames;
    spriteObj->frame_h = spriteObj->surface->h / numForms;
}

void setSpriteScale(SpriteObject *spriteObj, double scale) {
    spriteObj->dstrect = { 0, 0, 0, 0 };
    spriteObj->dstrect.w = (int)(spriteObj->surface->w * scale / spriteObj->numAnimFrames);
    spriteObj->dstrect.h = (int)(spriteObj->surface->h * scale / spriteObj->numForms);
}

void setSpritePos(SpriteObject *spriteObj, int rect_x, int rect_y) {
    spriteObj->dstrect.x = (int)rect_x;
    spriteObj->dstrect.y = (int)rect_y;
}

inline int spriteFrame(SpriteObject spriteObj, Uint8 frameNum) {
    return spriteObj.frame_w * frameNum;
}

inline int spriteForm(SpriteObject spriteObj, Uint8 formNum) {
    return spriteObj.frame_h * formNum;
}

void renderSprite(SpriteObject spriteObj, SDL_Rect srect, SDL_Surface *screen, SDL_Rect drect) {
    outputRect = drect;
    SDL_BlitSurface(spriteObj.surface, &srect, screen, &outputRect);
}

void renderSprite_static(SpriteObject spriteObj, SDL_Surface *screen) {
    outputRect = spriteObj.dstrect;
    SDL_BlitSurface(spriteObj.surface, NULL, screen, &outputRect);
}

void renderSprite_static_hiRes(SpriteObject spriteObj) {
    outputRect = spriteObj.dstrect;
#if !defined(SDL1)
    SDL_BlitScaled(spriteObj.surface, NULL, gameHiResScreen, &outputRect);
#else
    SDL_BlitSurface(spriteObj.surface, NULL, gameHiResScreen, &outputRect);
#endif
}

void drawRect(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b) {
    SDL_FillRect(gameScreen, &rect, ((r << 16) + (g << 8) + (b)));
}

void drawRect_gameTextScreen(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b) {
    SDL_FillRect(gameHiResScreen, &rect, ((r << 16) + (g << 8) + (b)));
}

void drawRectWithAlpha(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_FillRect(gameScreen, &rect, ((a << 24) + (r << 16) + (g << 8) + (b)));
}