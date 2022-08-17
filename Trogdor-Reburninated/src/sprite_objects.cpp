#include "sprite_objects.h"

SDL_Rect outputRect;
SDL_Surface *temp;

void prepareSprite(SpriteObject *spriteObj, const char path[], Sint8 numAnimFrames, Sint8 numForms) {
    temp = IMG_Load(path);
#if !defined(SDL1)
    SDL_SetColorKey(temp, SDL_TRUE, 0xFF00FF);
    spriteObj->surface = SDL_ConvertSurfaceFormat(temp, SDL_GetWindowPixelFormat(window), 0);
    spriteObj->frame_w = spriteObj->surface->w / numAnimFrames;
    spriteObj->frame_h = spriteObj->surface->h / numForms;
#else
    SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0xFF00FF);
    if (screenScale > 1) {
        spriteObj->surface = zoomSurface(temp, screenScale, screenScale, SMOOTHING_OFF);
    } else {
        spriteObj->surface = SDL_DisplayFormat(temp);
    }
    spriteObj->frame_w = (Sint16)(spriteObj->surface->w / screenScale / numAnimFrames);
    spriteObj->frame_h = (Sint16)(spriteObj->surface->h / screenScale / numForms);
#endif
    spriteObj->scaled_w = spriteObj->surface->w / numAnimFrames;
    spriteObj->scaled_h = spriteObj->surface->h / numForms;
    SDL_FreeSurface(temp);
    spriteObj->numAnimFrames = numAnimFrames;
    spriteObj->numForms = numForms;
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

inline Sint16 spriteFrame(SpriteObject spriteObj, Sint8 frameNum) {
    return spriteObj.scaled_w * frameNum;
}

inline Sint16 spriteForm(SpriteObject spriteObj, Sint8 formNum) {
    return spriteObj.scaled_h * formNum;
}

void renderSprite(SpriteObject spriteObj, SDL_Rect srect, SDL_Surface *screen, SDL_Rect drect) {
    outputRect = drect;
#if defined(SDL1)
    if (screen != gameHiResScreen) {
        outputRect.x = (Sint16)(outputRect.x * screenScale);
        outputRect.y = (Sint16)(outputRect.y * screenScale);
        outputRect.w = (Uint16)(outputRect.w * screenScale);
        outputRect.h = (Uint16)(outputRect.h * screenScale);
    }
#endif
    SDL_BlitSurface(spriteObj.surface, &srect, screen, &outputRect);
}

void renderSprite_static(SpriteObject spriteObj, SDL_Surface *screen) {
    outputRect = spriteObj.dstrect;
#if defined(SDL1)
    outputRect.x = (Sint16)(outputRect.x * screenScale);
    outputRect.y = (Sint16)(outputRect.y * screenScale);
#endif
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
    outputRect = rect;
#if defined(SDL1)
    outputRect.x = (Sint16)(outputRect.x * screenScale);
    outputRect.y = (Sint16)(outputRect.y * screenScale);
    outputRect.w = (Uint16)(outputRect.w * screenScale);
    outputRect.h = (Uint16)(outputRect.h * screenScale);
#endif
    SDL_FillRect(gameScreen, &rect, ((r << 16) + (g << 8) + (b)));
}

void drawRect_gameTextScreen(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b) {
    SDL_FillRect(gameHiResScreen, &rect, ((r << 16) + (g << 8) + (b)));
}

void drawRectWithAlpha(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_FillRect(gameScreen, &rect, ((a << 24) + (r << 16) + (g << 8) + (b)));
}