#include "window.h"

void setWidthHeightMults() {
	appWidthMult = (double)windowWidth / appWidth;
	appHeightMult = (double)windowHeight / appHeight;
	gameWidthMult = (double)appWidth / gameWidth;
	gameHeightMult = (double)appHeight / gameHeight;
	gameHiResMult = (double)gameHiResWidth / gameWidth;
}

void scaleAppRelativeToWindow() {
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(PSP)
	windowWidth = DEFAULT_WIDTH;
	windowHeight = DEFAULT_HEIGHT;
#elif !defined(SDL1)
	windowWidth = SDL_GetWindowSurface(window)->w;
	windowHeight = SDL_GetWindowSurface(window)->h;
#else
	windowWidth = SDL_GetVideoInfo()->current_w;
	windowHeight = SDL_GetVideoInfo()->current_h;
#endif
	screenScale = (double)windowWidth / appWidth;
	if ((double)windowHeight / appHeight < screenScale) {
		screenScale = (double)windowHeight / appHeight;
	}
	if (screenScale < 1) screenScale = 1;
	trueScreenScaleInt = (int)screenScale;
	//allowHiRes = (screenScale >= 2);
	allowHiRes = false;
	if (isIntegerScale) {
		screenScale = (int)screenScale;
		if (allowHiRes) {
			trueScreenScaleFull = (double)trueScreenScaleInt - (trueScreenScaleInt % 2); // integer scale relative to hi-res
		} else {
			trueScreenScaleFull = (double)trueScreenScaleInt;
		}
	} else {
		trueScreenScaleFull = screenScale;
	}
	PRINT(trueScreenScaleFull);
#if !defined(SDL1)
	// In SDL2, non-integer game screen scaling is handled by render scaling
	screenScale = (int)screenScale;
	if (screenScale > 2) screenScale = 2;
	screenScale = 1; // temporary
#endif
	gameSrcRect.w = (int)(gameWidth * screenScale);
	gameSrcRect.h = (int)(gameHeight * screenScale);
	appSrcRect.w = (int)(appWidth * screenScale);
	appSrcRect.h = (int)(appHeight * screenScale);
	appToWindowDstRect.w = (int)(appWidth * trueScreenScaleFull);
	appToWindowDstRect.h = (int)(appHeight * trueScreenScaleFull);
	appToWindowDstRect.x = max((int)((windowWidth - appToWindowDstRect.w) / 2), 0);
	appToWindowDstRect.y = max((int)((windowHeight - appToWindowDstRect.h) / 2), 0);
}

void scaleGameRelativeToApp() {
	gameToWindowDstRect.w = (int)(gameWidth * trueScreenScaleFull);
	gameToWindowDstRect.h = (int)(gameHeight * trueScreenScaleFull);
	gameToWindowDstRect.x = max((int)((windowWidth - gameToWindowDstRect.w) / 2), 0);
	gameToWindowDstRect.y = max((int)((windowHeight - gameToWindowDstRect.h) / 2), 0);
	gameHiResWidth = gameToWindowDstRect.w;
	gameHiResHeight = gameToWindowDstRect.h;
	gameHiResSrcRect.w = gameHiResWidth;
	gameHiResSrcRect.h = gameHiResHeight;
}

void setScaling() {
#if !defined(ANDROID)
	scaleAppRelativeToWindow();
	scaleGameRelativeToApp();
	setWidthHeightMults();
	SDL_FreeSurface(gameScreen);
	SDL_FreeSurface(appScreen);
	SDL_FreeSurface(gameHiResScreen);
#if !defined(PSP)
	gameScreen = SDL_CreateRGBSurface(0, gameToWindowDstRect.w, gameToWindowDstRect.h, 24, 0, 0, 0, 0);
	appScreen = SDL_CreateRGBSurface(0, appToWindowDstRect.w, appToWindowDstRect.h, 24, 0, 0, 0, 0);
	gameHiResScreen = SDL_CreateRGBSurface(0, gameToWindowDstRect.w, gameToWindowDstRect.h, 24, 0, 0, 0, 0);
#else
	gameScreen = SDL_CreateRGBSurface(0, gameToWindowDstRect.w, gameToWindowDstRect.h, 32, 0, 0, 0, 0);
	appScreen = SDL_CreateRGBSurface(0, appToWindowDstRect.w, appToWindowDstRect.h, 32, 0, 0, 0, 0);
	gameHiResScreen = SDL_CreateRGBSurface(0, gameToWindowDstRect.w, gameToWindowDstRect.h, 32, 0, 0, 0, 0);
#endif
#if !defined(SDL1)
	SDL_SetColorKey(appScreen, SDL_TRUE, 0xFF00FF);
	SDL_SetColorKey(gameHiResScreen, SDL_TRUE, 0xFF00FF);
#else
	SDL_SetColorKey(appScreen, SDL_SRCCOLORKEY, 0xFF00FF);
	SDL_SetColorKey(gameHiResScreen, SDL_SRCCOLORKEY, 0xFF00FF);
#endif
	destroyAllSprites();
	InitializeSpritesPart1();
	InitializeSpritesPart2();
	destroyAllTextChars();
	InitializeTextChars();
	InitializeTextObjects();
#endif
}

void snapWindow_x(double val) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP)) && !defined(SDL1)
	double_i = ((float)SDL_GetWindowSurface(window)->w / appWidth);
	if ((double_i - floor(double_i)) >= pow(1 - val, floor(double_i))) {
		if ((appWidth * ceil(double_i)) < DM.w) {
			SDL_SetWindowSize(window, appWidth * (short)(ceil(double_i)), SDL_GetWindowSurface(window)->h);
		}
	} else if ((double_i - floor(double_i)) < 1 - pow(1 - val, (short)(floor(double_i))) && (SDL_GetWindowSurface(window)->w % appWidth != 0)) {
		SDL_SetWindowSize(window, appWidth * (short)floor(double_i), SDL_GetWindowSurface(window)->h);
	}
#endif
}

void snapWindow_y(double val) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP)) && !defined(SDL1)
	double_i = ((float)SDL_GetWindowSurface(window)->h / appHeight);
	if ((double_i - floor(double_i)) >= pow(1 - val, (short)(floor(double_i)))) {
		if ((appHeight * ceil(double_i)) < DM.h) {
			SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, appHeight * (short)ceil(double_i));
		}
	} else if ((double_i - floor(double_i)) < 1 - pow(1 - val, (short)(floor(double_i))) && (SDL_GetWindowSurface(window)->h % appHeight != 0)) {
		SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, appHeight * (short)floor(double_i));
	}
#endif
}

void SDL_toggleFullscreen() {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP)) && !defined(SDL1)
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