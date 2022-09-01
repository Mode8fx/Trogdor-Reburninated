#include "sprite_objects.h"

SDL_Rect outputRect;
SDL_Surface *temp_sprite;

void prepareSprite(SpriteObject *spriteObj, const char path[], Sint8 numAnimFrames, Sint8 numForms, double scale) {
#if !defined(SDL1)
    if (spriteObj->texture == NULL) {
        temp_sprite = IMG_Load(path);
        spriteObj->frame_w = (Sint16)(temp_sprite->w / numAnimFrames);
        spriteObj->frame_h = (Sint16)(temp_sprite->h / numForms);
        spriteObj->numAnimFrames = numAnimFrames;
        spriteObj->numForms = numForms;
        SDL_SetColorKey(temp_sprite, SDL_TRUE, 0xFF00FF);
        spriteObj->texture = SDL_CreateTextureFromSurface(renderer, temp_sprite);
        SDL_FreeSurface(temp_sprite);
        spriteObj->scaled_w = (Uint16)(spriteObj->frame_w);
        spriteObj->scaled_h = (Uint16)(spriteObj->frame_h);
    }
#else
    if (spriteObj->surface != NULL) {
        SDL_FreeSurface(spriteObj->surface);
    }
    temp_sprite = IMG_Load(path);
    spriteObj->frame_w = (Sint16)(temp_sprite->w * scale / numAnimFrames);
    spriteObj->frame_h = (Sint16)(temp_sprite->h * scale / numForms);
    spriteObj->numAnimFrames = numAnimFrames;
    spriteObj->numForms = numForms;
    SDL_SetColorKey(temp_sprite, SDL_SRCCOLORKEY, 0xFF00FF);
    if (screenScale > 1 || scale > 1) {
        spriteObj->surface = zoomSurface(temp_sprite, screenScale * scale, screenScale * scale, SMOOTHING_OFF);
    } else {
        spriteObj->surface = SDL_DisplayFormat(temp_sprite);
    }
    SDL_FreeSurface(temp_sprite);
    spriteObj->scaled_w = (Uint16)(spriteObj->frame_w * screenScale);
    spriteObj->scaled_h = (Uint16)(spriteObj->frame_h * screenScale);
#endif
}

void setSpriteScale(SpriteObject *spriteObj, double scale) {
    spriteObj->dstrect = { 0, 0, 0, 0 };
#if !defined(SDL1)
    spriteObj->dstrect.w = (int)(spriteObj->frame_w * scale);
    spriteObj->dstrect.h = (int)(spriteObj->frame_h * scale);
#else
    spriteObj->dstrect.w = (int)(spriteObj->frame_w);
    spriteObj->dstrect.h = (int)(spriteObj->frame_h);
#endif
}

void setSpritePos(SpriteObject *spriteObj, int rect_x, int rect_y) {
    spriteObj->dstrect.x = (int)rect_x;
    spriteObj->dstrect.y = (int)rect_y;
}

Sint16 spriteFrame(SpriteObject spriteObj, Sint8 frameNum) {
    return spriteObj.scaled_w * frameNum;
}

Sint16 spriteForm(SpriteObject spriteObj, Sint8 formNum) {
    return spriteObj.scaled_h * formNum;
}

void renderSprite_game(SpriteObject spriteObj, SDL_Rect srect, SDL_Rect drect) {
    outputRect = drect;
    outputRect.x = (int)(outputRect.x * screenScale) + gameToWindowDstRect.x;
    outputRect.y = (int)(outputRect.y * screenScale) + gameToWindowDstRect.y;
    outputRect.w = (int)(outputRect.w * screenScale);
    outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
    SDL_RenderCopy(renderer, spriteObj.texture, &srect, &outputRect);
#else
    SDL_BlitSurface(spriteObj.surface, &srect, windowScreen, &outputRect);
#endif
}

void renderSprite_app(SpriteObject spriteObj, SDL_Rect srect, SDL_Rect drect) {
    outputRect = drect;
    outputRect.x = (int)(outputRect.x * screenScale) + appToWindowDstRect.x;
    outputRect.y = (int)(outputRect.y * screenScale) + appToWindowDstRect.y;
    outputRect.w = (int)(outputRect.w * screenScale);
    outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
    SDL_RenderCopy(renderer, spriteObj.texture, &srect, &outputRect);
#else
    SDL_BlitSurface(spriteObj.surface, &srect, windowScreen, &outputRect);
#endif
}

void renderSprite_static_game(SpriteObject spriteObj) {
    outputRect = spriteObj.dstrect;
    outputRect.x = (int)(outputRect.x * screenScale) + gameToWindowDstRect.x;
    outputRect.y = (int)(outputRect.y * screenScale) + gameToWindowDstRect.y;
    outputRect.w = (int)(outputRect.w * screenScale);
    outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
    SDL_RenderCopy(renderer, spriteObj.texture, NULL, &outputRect);
#else
    SDL_BlitSurface(spriteObj.surface, NULL, windowScreen, &outputRect);
#endif
}

void renderSprite_static_app(SpriteObject spriteObj) {
    outputRect = spriteObj.dstrect;
    outputRect.x = (int)(outputRect.x * screenScale) + appToWindowDstRect.x;
    outputRect.y = (int)(outputRect.y * screenScale) + appToWindowDstRect.y;
    outputRect.w = (int)(outputRect.w * screenScale);
    outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
    SDL_RenderCopy(renderer, spriteObj.texture, NULL, &outputRect);
#else
    SDL_BlitSurface(spriteObj.surface, NULL, windowScreen, &outputRect);
#endif
}

void drawRect(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b) {
    outputRect = rect;
    outputRect.x = (Sint16)(outputRect.x * screenScale) + appToWindowDstRect.x;
    outputRect.y = (Sint16)(outputRect.y * screenScale) + appToWindowDstRect.y;
    outputRect.w = (Uint16)(outputRect.w * screenScale);
    outputRect.h = (Uint16)(outputRect.h * screenScale);
#if !defined(SDL1)
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &outputRect);
#else
    SDL_FillRect(windowScreen, &outputRect, ((r << 16) + (g << 8) + (b)));
#endif
}

void drawRect_gameTextScreen(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b) {
    outputRect = rect;
    outputRect.x += gameToWindowDstRect.x;
    outputRect.y += gameToWindowDstRect.y;
#if !defined(SDL1)
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &outputRect);
#else
    SDL_FillRect(windowScreen, &outputRect, ((r << 16) + (g << 8) + (b)));
#endif
}

void drawRectWithAlpha(SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    outputRect = rect;
    outputRect.x += appToWindowDstRect.x;
    outputRect.y += appToWindowDstRect.y;
#if !defined(SDL1)
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &outputRect);
#else
    SDL_FillRect(windowScreen, &outputRect, ((r << 16) + (g << 8) + (b)));
#endif
}