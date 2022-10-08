#include "sprite_objects.h"

SDL_Rect outputRect;
SDL_Surface *temp_sprite;
#if defined(SDL1)
SDL_Rect single_srcrect;
SDL_Rect single_dstrect;
SDL_Surface *temp_sprite_2;
SDL_Surface *temp_sprite_single;
SDL_Surface *temp_sprite_single_zoom;
#endif

void prepareSprite(SpriteObject *spriteObj, const char path[], Sint8 numAnimFrames, Sint8 numForms, double scale) {
#if !defined(SDL1)
    if (spriteObj->texture == NULL) {
        temp_sprite = IMG_Load(path);
#if !defined(XBOX)
        if (temp_sprite == NULL) {
            throw(path);
        }
#endif
        spriteObj->frame_w = (Sint16)(temp_sprite->w / numAnimFrames);
        spriteObj->frame_h = (Sint16)(temp_sprite->h / numForms);
        spriteObj->scaled_w = (Uint16)(spriteObj->frame_w);
        spriteObj->scaled_h = (Uint16)(spriteObj->frame_h);
        spriteObj->numAnimFrames = numAnimFrames;
        spriteObj->numForms = numForms;
        SDL_SetColorKey(temp_sprite, SDL_TRUE, 0xFF00FF);
        spriteObj->texture = SDL_CreateTextureFromSurface(renderer, temp_sprite);
        SDL_FreeSurface(temp_sprite);
        temp_sprite = NULL;
    }
#else
    if (spriteObj->surface != NULL) {
        SDL_FreeSurface(spriteObj->surface);
    }
    temp_sprite = IMG_Load(path);
    if (temp_sprite == NULL) {
        throw(path);
    }
    spriteObj->frame_w = (Sint16)(temp_sprite->w * scale / numAnimFrames);
    spriteObj->frame_h = (Sint16)(temp_sprite->h * scale / numForms);
    spriteObj->scaled_w = (Uint16)(spriteObj->frame_w * screenScale);
    spriteObj->scaled_h = (Uint16)(spriteObj->frame_h * screenScale);
    spriteObj->numAnimFrames = numAnimFrames;
    spriteObj->numForms = numForms;
    if (screenScale > 1 || scale > 1) {
        if (screenScale == (int)screenScale) {
            SDL_SetColorKey(temp_sprite, SDL_SRCCOLORKEY, 0xFF00FF);
            spriteObj->surface = zoomSurface(temp_sprite, screenScale * scale, screenScale * scale, SMOOTHING_OFF);
        } else {
            // if non-integer scaling is used, each sprite needs to be zoomed individually or there are graphical bugs (sprites bleeding into each other, etc.)
#if (defined(WII) || defined(GAMECUBE))
            temp_sprite_2 = SDL_CreateRGBSurface(0, spriteObj->scaled_w * spriteObj->numAnimFrames, spriteObj->scaled_h * spriteObj->numForms, 24, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#elif SDL_BYTEORDER == SDL_BIG_ENDIAN
            temp_sprite_2 = SDL_CreateRGBSurface(0, spriteObj->scaled_w * spriteObj->numAnimFrames, spriteObj->scaled_h * spriteObj->numForms, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#else
            temp_sprite_2 = SDL_CreateRGBSurface(0, spriteObj->scaled_w * spriteObj->numAnimFrames, spriteObj->scaled_h * spriteObj->numForms, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
#endif
            SDL_SetColorKey(temp_sprite_2, SDL_SRCCOLORKEY, 0xFF00FF);
            SDL_FillRect(temp_sprite_2, NULL, 0xFF00FF);
            spriteObj->surface = SDL_DisplayFormat(temp_sprite_2);
            SDL_FreeSurface(temp_sprite_2);
            temp_sprite_2 = NULL;
            temp_sprite_single = SDL_CreateRGBSurface(0, spriteObj->frame_w, spriteObj->frame_h, 32, 0, 0, 0, 0);
            single_srcrect.w = spriteObj->frame_w;
            single_dstrect.w = spriteObj->scaled_w;
            single_srcrect.h = spriteObj->frame_h;
            single_dstrect.h = spriteObj->scaled_h;
            for (i = 0; i < spriteObj->numAnimFrames; i++) {
                single_srcrect.x = spriteObj->frame_w * i;
                single_dstrect.x = spriteObj->scaled_w * i;
                for (j = 0; j < spriteObj->numForms; j++) {
                    single_srcrect.y = spriteObj->frame_h * j;
                    single_dstrect.y = spriteObj->scaled_h * j;
                    SDL_BlitSurface(temp_sprite, &single_srcrect, temp_sprite_single, NULL);
                    temp_sprite_single_zoom = zoomSurface(temp_sprite_single, screenScale * scale, screenScale * scale, SMOOTHING_OFF);
                    SDL_BlitSurface(temp_sprite_single_zoom, NULL, spriteObj->surface, &single_dstrect);
                    SDL_FreeSurface(temp_sprite_single_zoom);
                    temp_sprite_single_zoom = NULL;
                }
            }
            SDL_FreeSurface(temp_sprite_single);
            temp_sprite_single = NULL;
        }
    } else {
        SDL_SetColorKey(temp_sprite, SDL_SRCCOLORKEY, 0xFF00FF);
        spriteObj->surface = SDL_DisplayFormat(temp_sprite);
    }
    SDL_FreeSurface(temp_sprite);
    temp_sprite = NULL;
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

void setSpriteFrame(SpriteInstance *sprite, SpriteObject spriteObj, Sint8 frame) {
    sprite->animFrame = frame;
    sprite->srcrect.x = spriteFrame(spriteObj, frame);
}

void setSpriteForm(SpriteInstance *sprite, SpriteObject spriteObj, Sint8 form) {
    sprite->animForm = form;
    sprite->srcrect.y = spriteForm(spriteObj, form);
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

void renderSprite_overlay(SpriteObject spriteObj) {
    outputRect = spriteObj.dstrect;
    outputRect.w = (int)(outputRect.w * screenScale);
    outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
    SDL_RenderCopy(renderer, spriteObj.texture, NULL, &outputRect);
#else
    SDL_BlitSurface(spriteObj.surface, NULL, windowScreen, &outputRect);
#endif
}

void renderEmptyOverlay(SpriteObject spriteObj) {
    outputRect = spriteObj.dstrect;
    outputRect.w = (int)(outputRect.w * screenScale);
    outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
    SDL_RenderFillRect(renderer, &outputRect);
#else
    SDL_FillRect(windowScreen, &outputRect, 0);
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