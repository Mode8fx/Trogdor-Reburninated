#include "sprite_objects.h"
#include "general.h"
#include "window.h"

SDL_RWops *rw;
SDL_Surface *temp_sprite_sheet;
SDL_Surface *temp_sprite_single;
#if defined(SDL1)
SDL_Surface *temp_sprite_single_zoom;
#endif
SDL_Rect single_srcrect;
SDL_Rect single_dstrect;
Uint32 *pixels;
int bpp;
Uint8 *p;
Sint16 offsetStart;
Sint16 offsetEnd;
Sint16 frame_w;
Sint16 frame_h;
double currScreenScale;

#if defined(SDL1)
inline bool SDL_HasIntersection(const SDL_Rect *A, const SDL_Rect *B) {
	return (!((A->x + A->w < B->x) || (B->x + B->w < A->x) || (A->y + A->h < B->y) || (B->y + B->h < A->y)));
}
#endif

Uint32 getPixel(SDL_Surface *surface, int x, int y) {
    // p is the address to the pixel we want to retrieve
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
    offsetStart = frame_w * x;
    offsetEnd = offsetStart + frame_w - 1;
    for (int_i = offsetStart; int_i < offsetEnd; int_i++) {
        for (int_j = frame_h * y; int_j < frame_h * (y + 1); int_j++) {
            if (getPixel(temp_sprite_sheet, int_i, int_j) != SDL_MapRGB(temp_sprite_sheet->format, 0xFF, 0, 0xFF)) {
                return (Sint8)(int_i - offsetStart);
            }
        }
    }
    return (Sint8)frame_w - 1;
}

Sint16 getXOffsetEnd(SpriteObject *spriteObj, Sint8 x, Sint8 y) {
    offsetStart = frame_w * x;
    offsetEnd = offsetStart + frame_w - 1;
    for (int_i = offsetEnd; int_i > offsetStart; int_i--) {
        for (int_j = frame_h * y; int_j < frame_h * (y + 1); int_j++) {
            if (getPixel(temp_sprite_sheet, int_i, int_j) != SDL_MapRGB(temp_sprite_sheet->format, 0xFF, 0, 0xFF)) {
                return (Sint16)(int_i - offsetStart);
            }
        }
    }
    return 0;
}

Sint8 getYOffsetStart(SpriteObject *spriteObj, Sint8 x, Sint8 y) {
    offsetStart = frame_h * y;
    offsetEnd = offsetStart + frame_h - 1;
    for (int_j = offsetStart; int_j < offsetEnd; int_j++) {
        for (int_i = frame_w * x; int_i < frame_w * (x + 1); int_i++) {
            if (getPixel(temp_sprite_sheet, int_i, int_j) != SDL_MapRGB(temp_sprite_sheet->format, 0xFF, 0, 0xFF)) {
                return (Sint8)(int_j - offsetStart);
            }
        }
    }
    return (Sint8)frame_h - 1;
}

Sint16 getYOffsetEnd(SpriteObject *spriteObj, Sint8 x, Sint8 y) {
    offsetStart = frame_h * y;
    offsetEnd = offsetStart + frame_h - 1;
    for (int_j = offsetEnd; int_j > offsetStart; int_j--) {
        for (int_i = frame_w * x; int_i < frame_w * (x + 1); int_i++) {
            if (getPixel(temp_sprite_sheet, int_i, int_j) != SDL_MapRGB(temp_sprite_sheet->format, 0xFF, 0, 0xFF)) {
                return (Sint16)(int_j - offsetStart);
            }
        }
    }
    return 0;
}

void prepareSurfaceFromSpriteSheet(SpriteObject *spriteObj) {
    single_srcrect.x = (frame_w * i) + spriteObj->sub[i][j].x_offset_start;
    single_srcrect.y = (frame_h * j) + spriteObj->sub[i][j].y_offset_start;
    single_srcrect.w = spriteObj->sub[i][j].x_offset_end - spriteObj->sub[i][j].x_offset_start + 1;
    single_srcrect.h = spriteObj->sub[i][j].y_offset_end - spriteObj->sub[i][j].y_offset_start + 1;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    temp_sprite_single = SDL_CreateRGBSurface(0, single_srcrect.w, single_srcrect.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#elif defined(VITA)
    temp_sprite_single = SDL_CreateRGBSurface(0, single_srcrect.w, single_srcrect.h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
#else
    temp_sprite_single = SDL_CreateRGBSurface(0, single_srcrect.w, single_srcrect.h, 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
#endif
    single_dstrect = { 0, 0, single_srcrect.w, single_srcrect.h };
    SDL_BlitSurface(temp_sprite_sheet, &single_srcrect, temp_sprite_single, &single_dstrect);
}

void prepareSprite(SpriteObject *spriteObj, unsigned char sprite_data[], unsigned int sprite_len, Sint8 numFrames, Sint8 numForms, double scale, bool isMenuSprite, bool isTransparent, bool useOffset) {
  spriteObj->spriteScale = scale;
  // Check if the surface/texture already exists
#if !defined(SDL1)
  if (spriteObj->sub[0] != NULL) {
    return;
  }
#endif
  if (isMenuSprite) {
    currScreenScale = screenScale_menu;
  } else {
    currScreenScale = screenScale;
  }
  // Allocate the SpriteSubObject array; each element of this 2D array represents a single sprite from the sprite sheet
  for (i = 0; i < numFrames; i++) {
    if (spriteObj->sub[i] != NULL) {
#if defined(SDL1)
      for (j = 0; j < numForms; j++) {
        SDL_FreeSurface(spriteObj->sub[i][j].surface);
      }
#endif
      free(spriteObj->sub[i]);
    }
    spriteObj->sub[i] = (SpriteSubObject*)malloc(numForms * sizeof(SpriteSubObject));
  }
  // Load the sprite sheet as a surface
  rw = SDL_RWFromConstMem(sprite_data, sprite_len);
  temp_sprite_sheet = IMG_Load_RW(rw, 1);
  if (isTransparent) {
    SDL_SetColorKey(temp_sprite_sheet, SDL_TRUE, 0xFF00FF);
  }
  // Store the size values of the sprite sheet
  frame_w = (Sint16)(temp_sprite_sheet->w / numFrames);
  frame_h = (Sint16)(temp_sprite_sheet->h / numForms);
  spriteObj->numFrames = numFrames;
  spriteObj->numForms = numForms;
  // Iterate through each section (sprite) of the sprite sheet
  // Convert the pixels to 32 bit
  pixels = (Uint32*)temp_sprite_sheet->pixels;
  bpp = temp_sprite_sheet->format->BytesPerPixel;
  for (i = 0; i < numFrames; i++) {
    for (j = 0; j < numForms; j++) {
      SpriteSubObject &subSprite = spriteObj->sub[i][j];
      // Get the sprite's left/right boundary (the x position where the sprite actually begins/ends)
      if (useOffset) {
        subSprite.x_offset_start = getXOffsetStart(spriteObj, i, j);
        subSprite.x_offset_end = getXOffsetEnd(spriteObj, i, j);
      } else {
        subSprite.x_offset_start = 0;
        subSprite.x_offset_end = frame_w - 1;
      }
      if (subSprite.x_offset_end < subSprite.x_offset_start) { // blank sprite
        subSprite.x_offset_end = subSprite.x_offset_start;
      }
      subSprite.center_x = (subSprite.x_offset_end - subSprite.x_offset_start) / 2;
      // Get the sprite's upper/lower boundary (the y position where the sprite actually begins/ends)
      if (useOffset) {
        subSprite.y_offset_start = getYOffsetStart(spriteObj, i, j);
        subSprite.y_offset_end = getYOffsetEnd(spriteObj, i, j);
      } else {
        subSprite.y_offset_start = 0;
        subSprite.y_offset_end = frame_h - 1;
      }
      if (subSprite.y_offset_end < subSprite.y_offset_start) { // blank sprite
        subSprite.y_offset_end = subSprite.y_offset_start;
      }
      subSprite.center_y = (subSprite.y_offset_end - subSprite.y_offset_start) / 2;
      // Create a new surface from the boundaries of the sprite (temp_sprite_single)
      prepareSurfaceFromSpriteSheet(spriteObj);
      // Get info from temp_sprite_single
      subSprite.w = temp_sprite_single->w;
      subSprite.h = temp_sprite_single->h;
      subSprite.scaled_w = (int)(subSprite.w * scale * currScreenScale);
      subSprite.scaled_h = (int)(subSprite.h * scale * currScreenScale);
#if !defined(SDL1)
      // [SDL2] Create a texture from temp_sprite_single
      applyColorKey(temp_sprite_single, isTransparent);
      subSprite.texture = SDL_CreateTextureFromSurface(renderer, temp_sprite_single);
#else
      if (currScreenScale == 1 && scale == 1) {
        // [SDL1 Normal] Create a new surface from temp_sprite_single
        applyColorKey(temp_sprite_single, isTransparent);
        subSprite.surface = SDL_DisplayFormat(temp_sprite_single);
      } else {
        // [SDL1 Zoom] Create a zoomed surface from temp_sprite_single and zoom it
        temp_sprite_single_zoom = zoomSurface(temp_sprite_single, currScreenScale * scale, currScreenScale * scale, SMOOTHING_OFF);
        applyColorKey(temp_sprite_single_zoom, isTransparent);
        subSprite.surface = SDL_DisplayFormat(temp_sprite_single_zoom);
        SDL_FreeSurface(temp_sprite_single_zoom);
        temp_sprite_single_zoom = NULL;
      }
#endif
      // Free temp_sprite_single since we no longer need it
      SDL_FreeSurface(temp_sprite_single);
      temp_sprite_single = NULL;
      // Adjust offsets according to scale
      subSprite.x_offset_start = static_cast<Uint8>(subSprite.x_offset_start * scale);
      subSprite.x_offset_end = static_cast<Uint8>(subSprite.x_offset_end * scale);
      subSprite.y_offset_start = static_cast<Uint8>(subSprite.y_offset_start * scale);
      subSprite.y_offset_end = static_cast<Uint8>(subSprite.y_offset_end * scale);
    }
  }
  // Free the sprite sheet since we no longer need it
  SDL_FreeSurface(temp_sprite_sheet);
  temp_sprite_sheet = NULL;

  setSpriteScale(spriteObj);
}

void setSpriteScale(SpriteObject *spriteObj) {
    spriteObj->dstrect = { 0, 0, 0, 0 };
    spriteObj->dstrect.w = (int)(frame_w * spriteObj->spriteScale);
    spriteObj->dstrect.h = (int)(frame_h * spriteObj->spriteScale);
}

void setSpritePos(SpriteObject *spriteObj, int rect_x, int rect_y) {
    spriteObj->dstrect.x = (int)rect_x;
    spriteObj->dstrect.y = (int)rect_y;
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

void sdl1_createTransparentScreen() {
#if defined(SDL1)
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    transparentScreen = SDL_CreateRGBSurface(0, gameHiResWidth, gameHiResHeight, 16, 0xF000, 0x00F0, 0x0F00, 0x000F);
    SDL_FillRect(transparentScreen, NULL, 0x0008);
#else
    transparentScreen = SDL_CreateRGBSurface(0, gameHiResWidth, gameHiResHeight, 16, 0x000F, 0x0F00, 0x00F0, 0xF000);
    SDL_FillRect(transparentScreen, NULL, 0x8000);
#endif
#endif
}

SpriteInstance::SpriteInstance(SpriteObject *so, Sint8 frame, Sint8 form) {
    spriteObj = so;
    if (spriteObj->numFrames > 0) {
        srcrect.x = 0;
        srcrect.y = 0;
        dstrect.x = spriteObj->dstrect.x;
        dstrect.y = spriteObj->dstrect.y;
        setFrameAndForm(frame, form);
        animFrameTime = 0;
        animFrameCounter = 0;
        animFormTime = 0;
        animFormCounter = 0;
    }
}

SpriteInstance::SpriteInstance(SpriteObject *so, Sint8 frame, Sint8 form, float x, float y) {
    spriteObj = so;
    if (spriteObj->numFrames > 0) {
        srcrect.x = 0;
        srcrect.y = 0;
        setPos(x, y);
        setFrameAndForm(frame, form);
    }
}

void SpriteInstance::setFrame(Sint8 frame) {
    animFrame = frame;
    updateCurrSprite();
}

void SpriteInstance::setForm(Sint8 form) {
    animForm = form;
    updateCurrSprite();
}

void SpriteInstance::setFrameAndForm(Sint8 frame, Sint8 form) {
    animFrame = frame;
    animForm = form;
    updateCurrSprite();
}

void SpriteInstance::animateFrame() {
    if (animFrameTime > 0) {
        animFrameCounter += frameRateMult;
        while (animFrameCounter >= animFrameTime) {
            animFrameCounter -= animFrameTime;
            setFrame((animFrame + 1) % spriteObj->numFrames);
        }
    }
}

void SpriteInstance::animateForm() {
    if (animFormTime > 0) {
        animFormCounter += frameRateMult;
        while (animFormCounter >= animFormTime) {
            animFormCounter -= animFormTime;
            setForm((animForm + 1) % spriteObj->numForms);
        }
    }
}

// used only in special cases; it is assumed that animFrameTime is > 0; animFormTime is unused
void SpriteInstance::animateWrap() {
    animFrameCounter += frameRateMult;
    while (animFrameCounter >= animFrameTime) {
        animFrameCounter -= animFrameTime;
        if (animFrame + 1 < spriteObj->numFrames) {
            setFrame(animFrame + 1);
        } else {
            setFrame((animFrame + 1) % spriteObj->numFrames);
            setForm((animForm + 1) % spriteObj->numForms);
        }
    }
}

void SpriteInstance::updateCurrSprite() {
#if !defined(SDL1)
    currSprite = spriteObj->sub[animFrame][animForm].texture;
#else
    currSprite = spriteObj->sub[animFrame][animForm].surface;
#endif
    currSpriteXOffset = spriteObj->sub[animFrame][animForm].x_offset_start;
    currSpriteYOffset = spriteObj->sub[animFrame][animForm].y_offset_start;
    currSpriteCenterX = spriteObj->sub[animFrame][animForm].center_x;
    currSpriteCenterY = spriteObj->sub[animFrame][animForm].center_y;
#if !defined(SDL1)
    srcrect.w = spriteObj->sub[animFrame][animForm].w;
    srcrect.h = spriteObj->sub[animFrame][animForm].h;
#else
    srcrect.w = spriteObj->sub[animFrame][animForm].scaled_w;
    srcrect.h = spriteObj->sub[animFrame][animForm].scaled_h;
#endif
    dstrect.w = (int)(spriteObj->sub[animFrame][animForm].w * spriteObj->spriteScale);
    dstrect.h = (int)(spriteObj->sub[animFrame][animForm].h * spriteObj->spriteScale);
}

inline void SpriteInstance::moveSprite() {
    if (vel_x != 0) {
        addPosX(vel_x);
    }
    if (vel_y != 0) {
        addPosY(vel_y);
    }
}

void SpriteInstance::setPosX(float x) {
    pos_x = x;
    dstrect.x = (Sint16)x;
}

void SpriteInstance::setPosY(float y) {
    pos_y = y;
    dstrect.y = (Sint16)y;
}

void SpriteInstance::addPosX(float x) {
    pos_x += (x * frameRateMult);
    dstrect.x = (Sint16)pos_x;
}

void SpriteInstance::addPosY(float y) {
    pos_y += (y * frameRateMult);
    dstrect.y = (Sint16)pos_y;
}

void SpriteInstance::setPos(float x, float y) {
    setPosX(x);
    setPosY(y);
}

void SpriteInstance::renderSprite_game() {
    outputRect.x = (Sint16)((dstrect.x + currSpriteXOffset) * screenScale) + gameToWindowDstRect.x;
    outputRect.y = (Sint16)((dstrect.y + currSpriteYOffset) * screenScale) + gameToWindowDstRect.y;
    outputRect.w = (int)(dstrect.w * screenScale);
    outputRect.h = (int)(dstrect.h * screenScale);
#if !defined(SDL1)
    SDL_RenderCopy(renderer, currSprite, &srcrect, &outputRect);
#else
    SDL_BlitSurface(currSprite, &srcrect, windowScreen, &outputRect);
#endif
}

void SpriteInstance::renderSpriteAsCSO_game() {
    outputRect.x = (Sint16)(((dstrect.x / TWIPS_PER_PIXEL) - currSpriteCenterX) * screenScale) + gameToWindowDstRect.x;
    outputRect.y = (Sint16)(((dstrect.y / TWIPS_PER_PIXEL) - currSpriteCenterY) * screenScale) + gameToWindowDstRect.y;
    outputRect.w = (int)(dstrect.w * screenScale);
    outputRect.h = (int)(dstrect.h * screenScale);
#if !defined(SDL1)
    SDL_RenderCopy(renderer, currSprite, &srcrect, &outputRect);
#else
    SDL_BlitSurface(currSprite, &srcrect, windowScreen, &outputRect);
#endif
}

void SpriteInstance::renderSprite_app() {
    outputRect.x = (Sint16)(dstrect.x + currSpriteXOffset);
    outputRect.y = (Sint16)(dstrect.y + currSpriteYOffset);
    outputRect.w = (int)(dstrect.w * screenScale);
    outputRect.h = (int)(dstrect.h * screenScale);
#if !defined(SDL1)
    SDL_RenderCopy(renderer, currSprite, &srcrect, &outputRect);
#else
    SDL_BlitSurface(currSprite, &srcrect, windowScreen, &outputRect);
#endif
}

void SpriteInstance::renderSprite_menu() {
    outputRect.x = (dstrect.x + currSpriteXOffset) + menuToWindowDstRect.x;
    outputRect.y = (dstrect.y + currSpriteYOffset) + menuToWindowDstRect.y;
    outputRect.w = (int)(dstrect.w * screenScale_menu);
    outputRect.h = (int)(dstrect.h * screenScale_menu);
#if !defined(SDL1)
    SDL_RenderCopy(renderer, currSprite, &srcrect, &outputRect);
#else
    SDL_BlitSurface(currSprite, &srcrect, windowScreen, &outputRect);
#endif
}

void SpriteInstance::renderSprite_overlay() {
    outputRect = dstrect;
#if !defined(SDL1)
    SDL_RenderCopy(renderer, currSprite, NULL, &outputRect);
#else
    SDL_BlitSurface(currSprite, NULL, windowScreen, &outputRect);
#endif
}

void SpriteInstance::renderEmptyOverlay() {
    outputRect = dstrect;
#if !defined(SDL1)
    SDL_RenderFillRect(renderer, &outputRect);
#else
    SDL_FillRect(windowScreen, &outputRect, 0);
#endif
}

void SpriteInstance::prepareAsCSO(float x, float y, Sint8 frame, Sint8 form, Sint8 frameTime, Sint8 formTime, float vx, float vy) {
    setPos(x, y);
    setFrameAndForm(frame, form);
    animFrameTime = frameTime;
    animFrameCounter = 0;
    animFormTime = formTime;
    animFormCounter = 0;
    vel_x = vx;
    vel_y = vy;
    isActive = true;
}

void SpriteInstance::renderAsCSO(bool useWrap = false) {
    if (isActive) {
        //if (useTwips) {
        //    renderSpriteAsCSO_game();
        //} else if (SDL_HasIntersection(&gameSrcRect_unscaled, &dstrect)) {
        //    renderSprite_game();
        //}
        if (SDL_HasIntersection(&gameSrcRect_unscaled, &dstrect)) {
            renderSprite_game();
        }
        moveSprite();
        if (useWrap) {
            animateWrap();
        } else {
            animateFrame();
            animateForm();
        }
    }
}