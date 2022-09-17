#include "window.h"

void setWidthHeightMults() {
	appWidthMult = (double)windowWidth / appWidth;
	appHeightMult = (double)windowHeight / appHeight;
	gameWidthMult = (double)appWidth / gameWidth;
	gameHeightMult = (double)appHeight / gameHeight;
	gameHiResMult = (double)gameHiResWidth / gameWidth;
}

void scaleGameByApp() {
	screenScale = (double)windowWidth / appWidth;
	if ((double)windowHeight / appHeight < screenScale) {
		screenScale = (double)windowHeight / appHeight;
	}
	if (screenScale < 1) screenScale = 1;
	trueScreenScaleInt = (int)screenScale;
}

void scaleAppByGame() {
	screenScale = (double)windowWidth / gameWidth;
	if ((double)windowHeight / gameHeight < screenScale) {
		screenScale = (double)windowHeight / gameHeight;
	}
	if (screenScale < 1) screenScale = 1;
	trueScreenScaleInt = (int)screenScale;
}

void scaleGameAndApp() {
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(PSP) || defined(THREEDS) || defined(XBOX)
	windowWidth = DEFAULT_WIDTH;
	windowHeight = DEFAULT_HEIGHT;
#elif !defined(SDL1)
	windowWidth = SDL_GetWindowSurface(window)->w;
	windowHeight = SDL_GetWindowSurface(window)->h;
#else
	windowWidth = SDL_GetVideoInfo()->current_w;
	windowHeight = SDL_GetVideoInfo()->current_h;
#endif
	//allowHiRes = (screenScale >= 2);
	allowHiRes = false;
	switch (scalingType) {
		case 0:  // integer app
			scaleGameByApp();
			screenScale = (int)screenScale;
			if (allowHiRes) {
				trueScreenScaleFull = (double)trueScreenScaleInt - (trueScreenScaleInt % 2); // integer scale relative to hi-res
			} else {
				trueScreenScaleFull = (double)trueScreenScaleInt;
			}
			break;
		case 1:  // integer game
			scaleAppByGame();
			screenScale = (int)screenScale;
			if (allowHiRes) {
				trueScreenScaleFull = (double)trueScreenScaleInt - (trueScreenScaleInt % 2); // integer scale relative to hi-res
			} else {
				trueScreenScaleFull = (double)trueScreenScaleInt;
			}
			break;
		case 2:  // non-integer app
			scaleGameByApp();
			trueScreenScaleFull = screenScale;
			break;
		default: // non-integer game
			scaleAppByGame();
			trueScreenScaleFull = screenScale;
			break;
	}
	gameSrcRect.w = (int)(gameWidth * screenScale);
	gameSrcRect.h = (int)(gameHeight * screenScale);
	appSrcRect.w = (int)(appWidth * screenScale);
	appSrcRect.h = (int)(appHeight * screenScale);
	appToWindowDstRect.w = (int)(appWidth * trueScreenScaleFull);
	appToWindowDstRect.h = (int)(appHeight * trueScreenScaleFull);
	appToWindowDstRect.x = max((int)((windowWidth - appToWindowDstRect.w) / 2), 0);
	appToWindowDstRect.y = max((int)((windowHeight - appToWindowDstRect.h) / 2), 0);
	gameToWindowDstRect.w = (int)(gameWidth * trueScreenScaleFull);
	gameToWindowDstRect.h = (int)(gameHeight * trueScreenScaleFull);
	gameToWindowDstRect.x = max((int)((windowWidth - gameToWindowDstRect.w) / 2), 0);
	gameToWindowDstRect.y = max((int)((windowHeight - gameToWindowDstRect.h) / 2), 0);
	gameHiResWidth = gameToWindowDstRect.w;
	gameHiResHeight = gameToWindowDstRect.h;
	gameHiResSrcRect.w = gameHiResWidth;
	gameHiResSrcRect.h = gameHiResHeight;
}

void repositionOverlay() {
	sprite_overlay_basement_top.dstrect.x = gameToWindowDstRect.x - (int)(sprite_overlay_basement_left.dstrect.w * screenScale);
	sprite_overlay_basement_top.dstrect.y = gameToWindowDstRect.y - (int)(sprite_overlay_basement_top.dstrect.h * screenScale);
	sprite_overlay_basement_bottom.dstrect.x = sprite_overlay_basement_top.dstrect.x;
	sprite_overlay_basement_bottom.dstrect.y = gameToWindowDstRect.y + gameToWindowDstRect.h;
	sprite_overlay_basement_left.dstrect.x = sprite_overlay_basement_top.dstrect.x;
	sprite_overlay_basement_left.dstrect.y = gameToWindowDstRect.y;
	sprite_overlay_basement_right.dstrect.x = gameToWindowDstRect.x + gameToWindowDstRect.w;
	uint_i = sprite_overlay_basement_top.dstrect.x + (int)(sprite_overlay_basement_top.dstrect.w * screenScale);
	uint_j = sprite_overlay_basement_right.dstrect.x + (int)(sprite_overlay_basement_right.dstrect.w * screenScale);
	sprite_overlay_basement_right.dstrect.x += (uint_i - uint_j);
	sprite_overlay_basement_right.dstrect.y = sprite_overlay_basement_left.dstrect.y;
}

void setScaling() {
#if !defined(ANDROID)
	scaleGameAndApp();
	setWidthHeightMults();
	InitializeSpritesPart1();
	InitializeSpritesPart2();
	repositionOverlay();
	destroyAllTextChars();
	InitializeFontsAndText();
#endif
}

void snapWindow_x(double range, Uint16 size) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX)) && !defined(SDL1)
	double_i = ((float)SDL_GetWindowSurface(window)->w / size);
	if ((double_i - floor(double_i)) >= pow(1 - range, floor(double_i))) {
		if ((size * ceil(double_i)) < DM.w) {
			SDL_SetWindowSize(window, size * (short)(ceil(double_i)), SDL_GetWindowSurface(window)->h);
		}
	} else if ((double_i - floor(double_i)) < 1 - pow(1 - range, (short)(floor(double_i))) && (SDL_GetWindowSurface(window)->w % size != 0)) {
		SDL_SetWindowSize(window, size * (short)floor(double_i), SDL_GetWindowSurface(window)->h);
	}
#endif
}

void snapWindow_y(double range, Uint16 size) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX)) && !defined(SDL1)
	double_i = ((float)SDL_GetWindowSurface(window)->h / size);
	if ((double_i - floor(double_i)) >= pow(1 - range, (short)(floor(double_i)))) {
		if ((size * ceil(double_i)) < DM.h) {
			SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, size * (short)ceil(double_i));
		}
	} else if ((double_i - floor(double_i)) < 1 - pow(1 - range, (short)(floor(double_i))) && (SDL_GetWindowSurface(window)->h % size != 0)) {
		SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, size * (short)floor(double_i));
	}
#endif
}

void SDL_toggleFullscreen() {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX)) && !defined(SDL1)
	isWindowed = !isWindowed;
	if (isWindowed) {
		SDL_SetWindowFullscreen(window, 0);
	} else {
		SDL_SetWindowSize(window, appWidth, appHeight);
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	//setScaling();
#endif
}