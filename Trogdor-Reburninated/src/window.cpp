#include "window.h"

void setWidthHeightMults() {
	appWidthMult = (double)windowWidth / appWidth;
	appHeightMult = (double)windowHeight / appHeight;
	gameWidthMult = (double)appWidth / gameWidth;
	gameHeightMult = (double)appHeight / gameHeight;
	gameHiResMult = (double)gameHiResWidth / gameWidth;
}

void scaleAppRelativeToWindow() {
#if !defined(SDL1)
	windowWidth = SDL_GetWindowSurface(window)->w;
	windowHeight = SDL_GetWindowSurface(window)->h;
#elif defined(WII) or defined(GAMECUBE)
	windowWidth = 320;
	windowHeight = 240;
#else
	windowWidth = SDL_GetVideoInfo()->current_w;
	windowHeight = SDL_GetVideoInfo()->current_h;
#endif
	if (isIntegerScale) {
		int_i = min((int)(windowWidth / appWidth), (int)(windowHeight / appHeight));
		if (int_i < 1) int_i = 1;
		appToWindowDstRect.w = appWidth * int_i;
		appToWindowDstRect.h = appHeight * int_i;
	} else {
		screenScale = (double)windowWidth / appWidth;
		if ((double)windowHeight / appHeight < screenScale) {
			screenScale = (double)windowHeight / appHeight;
		}
		if (screenScale < 1) screenScale = 1;
		appToWindowDstRect.w = (int)(appWidth * screenScale);
		appToWindowDstRect.h = (int)(appHeight * screenScale);
	}
	appToWindowDstRect.x = max((int)((windowWidth - appToWindowDstRect.w) / 2), 0);
	appToWindowDstRect.y = max((int)((windowHeight - appToWindowDstRect.h) / 2), 0);
}

void scaleGameRelativeToApp() {
	if (isIntegerScale) {
		int_i = min((int)(appToWindowDstRect.w / appWidth), (int)(appToWindowDstRect.h / appHeight));
		if (int_i < 1) int_i = 1;
		gameToAppDstRect.w = gameWidth * int_i;
		gameToAppDstRect.h = gameHeight * int_i;
		gameToWindowDstRect.w = gameToAppDstRect.w;
		gameToWindowDstRect.h = gameToAppDstRect.h;
	} else {
		screenScale = (double)appToWindowDstRect.w / appWidth;
		if ((double)appToWindowDstRect.h / appHeight < screenScale) {
			screenScale = (double)appToWindowDstRect.h / appHeight;
		}
		if (screenScale < 1) screenScale = 1;
		gameToAppDstRect.w = (int)(gameWidth * screenScale);
		gameToAppDstRect.h = (int)(gameHeight * screenScale);
		gameToWindowDstRect.w = gameToAppDstRect.w;
		gameToWindowDstRect.h = gameToAppDstRect.h;
	}
	gameToAppDstRect.x = max((int)((appToWindowDstRect.w - gameToAppDstRect.w) / 2), 0);
	gameToAppDstRect.y = max((int)((appToWindowDstRect.h - gameToAppDstRect.h) / 2), 0);
	gameToWindowDstRect.x = gameToAppDstRect.x + appToWindowDstRect.x;
	gameToWindowDstRect.y = gameToAppDstRect.y + appToWindowDstRect.y;
	SDL_FreeSurface(gameHiResScreen);
	gameHiResScreen = SDL_CreateRGBSurface(0, gameToAppDstRect.w, gameToAppDstRect.h, 24, 0, 0, 0, 0);
#if !defined(SDL1)
	SDL_SetColorKey(gameHiResScreen, SDL_TRUE, 0xFF00FF);
#else
	SDL_SetColorKey(gameHiResScreen, SDL_SRCCOLORKEY, 0xFF00FF);
#endif
	gameHiResWidth = gameToAppDstRect.w;
	gameHiResHeight = gameToAppDstRect.h;
	gameHiResSrcRect.w = gameHiResWidth;
	gameHiResSrcRect.h = gameHiResHeight;
}

void setScaling() {
#if !defined(ANDROID)
	scaleAppRelativeToWindow();
	scaleGameRelativeToApp();
	setWidthHeightMults();
	destroyAllTextChars();
	InitializeTextChars();
	InitializeTextObjects();
	SDL_FreeSurface(sprite_end_of_level_trogdor.surface);
	if (gameHiResMult >= 2) {
		PREPARE_SPRITE(sprite_end_of_level_trogdor, (rootDir + "graphics/end_of_level_trogdor_small.bmp").c_str(),
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, sprite_end_of_level_trogdor), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, sprite_end_of_level_trogdor), 1, 1, (int)(ceil(gameHiResMult * 1.5)));
	} else {
		PREPARE_SPRITE(sprite_end_of_level_trogdor, (rootDir + "graphics/end_of_level_trogdor_big.bmp").c_str(),
			OBJ_TO_MID_SCREEN_X(gameWidth, sprite_end_of_level_trogdor), OBJ_TO_MID_SCREEN_Y(gameHeight, sprite_end_of_level_trogdor), 1, 1, 1);
	}
#endif
}

void snapWindow_x(double val) {
#if defined(PC) && !defined(SDL1)
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
#if defined(PC) && !defined(SDL1)
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
#if defined(PC) && !defined(SDL1)
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

void SDL_toggleIntegerScale() {
	isIntegerScale = !isIntegerScale;
	setScaling();
}