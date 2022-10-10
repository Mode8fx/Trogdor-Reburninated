#include "sprite_objects.h"

SDL_Rect outputRect;
SDL_Surface *temp_sprite;
SDL_Surface *temp_sprite_sheet;
SDL_Surface *temp_sprite_single;
SDL_Rect single_srcrect;
SDL_Rect single_dstrect;
Uint32 *pixels;
int bpp;
Uint8 *p;
Sint16 offsetStart;
Sint16 offsetEnd;
#if defined(SDL1)
SDL_Surface *temp_sprite_2;
SDL_Surface *temp_sprite_single_zoom;
#endif

Uint32 getpixel(SDL_Surface* surface, int x, int y) {
    /* Here p is the address to the pixel we want to retrieve */
    p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
        case 1:
            return *p;
        case 2:
            return *(Uint16*)p;
        case 3:
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            return p[0] << 16 | p[1] << 8 | p[2];
#else
            return p[0] | p[1] << 8 | p[2] << 16;
#endif
        case 4:
            return *(Uint32*)p;
        default:
            return 0;
    }
}

Sint8 getXOffsetStart(SpriteObject *spriteObj, Sint8 x, Sint8 y) {
    offsetStart = spriteObj->frame_w * x;
    offsetEnd = offsetStart + spriteObj->frame_w - 1;
    for (int_i = offsetStart; int_i < offsetEnd; int_i++) {
        for (int_j = spriteObj->frame_h * y; int_j < spriteObj->frame_h * (y + 1); int_j++) {
            if (getpixel(temp_sprite_sheet, int_i, int_j) != 0xFF00FF) {
                return (Sint8)(int_i - offsetStart);
            }
        }
    }
    return (Sint8)spriteObj->frame_w - 1;
}

Sint8 getXOffsetEnd(SpriteObject *spriteObj, Sint8 x, Sint8 y) {
    offsetStart = spriteObj->frame_w * x;
    offsetEnd = offsetStart + spriteObj->frame_w - 1;
    for (int_i = offsetEnd; int_i > offsetStart; int_i--) {
        for (int_j = spriteObj->frame_h * y; int_j < spriteObj->frame_h * (y + 1); int_j++) {
            if (getpixel(temp_sprite_sheet, int_i, int_j) != 0xFF00FF) {
                return (Sint8)(int_i - offsetStart);
            }
        }
    }
    return 0;
}

Sint8 getYOffsetStart(SpriteObject *spriteObj, Sint8 x, Sint8 y) {
    offsetStart = spriteObj->frame_h * y;
    offsetEnd = offsetStart + spriteObj->frame_h - 1;
    for (int_j = offsetStart; int_j < offsetEnd; int_j++) {
        for (int_i = spriteObj->frame_w * x; int_i < spriteObj->frame_w * (x + 1); int_i++) {
            if (getpixel(temp_sprite_sheet, int_i, int_j) != 0xFF00FF) {
                return (Sint8)(int_j - offsetStart);
            }
        }
    }
    return (Sint8)spriteObj->frame_h - 1;
}

Sint8 getYOffsetEnd(SpriteObject *spriteObj, Sint8 x, Sint8 y) {
    offsetStart = spriteObj->frame_h * y;
    offsetEnd = offsetStart + spriteObj->frame_h - 1;
    for (int_j = offsetEnd; int_j > offsetStart; int_j--) {
        for (int_i = spriteObj->frame_w * x; int_i < spriteObj->frame_w * (x + 1); int_i++) {
            if (getpixel(temp_sprite_sheet, int_i, int_j) != 0xFF00FF) {
                return (Sint8)(int_j - offsetStart);
            }
        }
    }
    return 0;
}

void prepareSurfaceFromSpriteSheet(SDL_Surface *surface, SpriteObject *spriteObj) {
    int_i = spriteObj->sub[i][j].x_offset_end - spriteObj->sub[i][j].x_offset_start + 1;
    int_j = spriteObj->sub[i][j].y_offset_end - spriteObj->sub[i][j].y_offset_start + 1;
#if (defined(WII) || defined(GAMECUBE))
    surface = SDL_CreateRGBSurface(0, int_i, int_j, 24, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#elif SDL_BYTEORDER == SDL_BIG_ENDIAN
    surface = SDL_CreateRGBSurface(0, int_i, int_j, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#else
    surface = SDL_CreateRGBSurface(0, int_i, int_j, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
#endif
#if !defined(SDL1)
    SDL_SetColorKey(surface, SDL_TRUE, 0xFF00FF);
#else
    SDL_SetColorKey(surface, SDL_SRCCOLORKEY, 0xFF00FF);
#endif
    SDL_FillRect(surface, NULL, 0xFF00FF);
    single_srcrect.x = (spriteObj->frame_w * i) + spriteObj->sub[i][j].x_offset_start;
    single_srcrect.y = (spriteObj->frame_h * j) + spriteObj->sub[i][j].y_offset_start;
    single_srcrect.w = int_i;
    single_srcrect.h = int_j;
    single_dstrect.x = 0;
    single_dstrect.y = 0;
    single_dstrect.w = int_i;
    single_dstrect.h = int_j;
    SDL_BlitSurface(temp_sprite_sheet, &single_srcrect, surface, &single_dstrect);
}

void prepareSprite(SpriteObject *spriteObj, const char path[], Sint8 numAnimFrames, Sint8 numForms, double scale) {
    // Check if the surface/texture already exists
#if !defined(SDL1)
    if (spriteObj->sub[0] != NULL) {
        return;
    }
#endif
    // Allocate the SpriteSubObject array; each element of this 2D array represents a single sprite from the sprite sheet
    for (i = 0; i < numAnimFrames; i++) {
        if (spriteObj->sub[i] != NULL) {
            free(spriteObj->sub[i]);
        }
        spriteObj->sub[i] = (SpriteSubObject*)malloc(numForms * sizeof(SpriteSubObject));
    }
    // Load the sprite sheet as a surface
    temp_sprite_sheet = IMG_Load(path);
#if !defined(XBOX)
    // If there was an error (e.g. missing file), crash to error screen
    if (temp_sprite_sheet == NULL) {
        throw(path);
    }
#endif
    // Store the size values of the sprite sheet
    spriteObj->frame_w = (Sint16)(temp_sprite_sheet->w / numAnimFrames);
    spriteObj->frame_h = (Sint16)(temp_sprite_sheet->h / numForms);
    spriteObj->scaled_w = (Uint16)(spriteObj->frame_w);
    spriteObj->scaled_h = (Uint16)(spriteObj->frame_h);
    spriteObj->numAnimFrames = numAnimFrames;
    spriteObj->numForms = numForms;
    // Iterate through each section (sprite) of the sprite sheet
    //Convert the pixels to 32 bit
    pixels = (Uint32*)temp_sprite_sheet->pixels;
    bpp = temp_sprite_sheet->format->BytesPerPixel;
    for (i = 0; i < numAnimFrames; i++) {
        for (j = 0; j < numForms; j++) {
            // Get the sprite's left/right boundary (the x position where the sprite actually begins/ends)
            spriteObj->sub[i][j].x_offset_start = getXOffsetStart(spriteObj, i, j);
            spriteObj->sub[i][j].x_offset_end = getXOffsetEnd(spriteObj, i, j);
            // Get the sprite's upper/lower boundary (the y position where the sprite actually begins/ends)
            spriteObj->sub[i][j].y_offset_start = getYOffsetStart(spriteObj, i, j);
            spriteObj->sub[i][j].y_offset_end = getYOffsetEnd(spriteObj, i, j);
#if !defined(SDL1)
            // [SDL2] Create a new surface from the boundaries of the sprite, then create a texture from it
            prepareSurfaceFromSpriteSheet(temp_sprite_single, spriteObj);
            //spriteObj->surface = SDL_DisplayFormat(temp_sprite);
            spriteObj->sub[i][j].texture = SDL_CreateTextureFromSurface(renderer, temp_sprite_single);
            SDL_FreeSurface(temp_sprite_single);
            temp_sprite_single = NULL;
#else
            if (spriteObj->sub[i][j]->surface != NULL) {
                SDL_FreeSurface(spriteObj->sub[i][j].surface);
            }
            if (screenScale == 1 && scale == 1) {
                // [SDL1 Normal] Create a new surface from the boundaries of the sprite
                prepareSurfaceFromSpriteSheet(spriteObj->sub[i][j].surface, spriteObj);
            } else {
                // [SDL1 Zoom] Create a new surface from the boundaries of the sprite and zoom it
                prepareSurfaceFromSpriteSheet(temp_sprite_single, spriteObj);
                spriteObj->sub[i][j].surface = zoomSurface(temp_sprite_single, screenScale * scale, screenScale * scale, SMOOTHING_OFF);
                SDL_FreeSurface(temp_sprite_single);
                temp_sprite_single = NULL;
            }
#endif
        }
    }
    SDL_SetColorKey(temp_sprite_sheet, SDL_TRUE, 0xFF00FF);
    spriteObj->texture = SDL_CreateTextureFromSurface(renderer, temp_sprite_sheet);
    // Free the sprite sheet since we no longer need it
    SDL_FreeSurface(temp_sprite_sheet);
    temp_sprite_sheet = NULL;
}

void prepareSprite_old(SpriteObject *spriteObj, const char path[], Sint8 numAnimFrames, Sint8 numForms, double scale) {
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