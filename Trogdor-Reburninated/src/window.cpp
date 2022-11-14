#include "window.h"
#include "sprite_objects.h"
#include "general.h"
#include "media_objects_init.h"
#include "config.h"

void setWidthHeightMults() {
	appWidthMult = (double)windowWidth / appWidth;
	appHeightMult = (double)windowHeight / appHeight;
	gameWidthMult = (double)appWidth / gameWidth;
	gameHeightMult = (double)appHeight / gameHeight;
	gameHiResMult = (double)gameHiResWidth / gameWidth;
}

double getScreenScale_app() {
	if (windowWidth <= appWidth || windowHeight <= appHeight) return 1;
	return min(((double)windowWidth / appWidth), ((double)windowHeight / appHeight));
}

void scaleGameByApp() {
	screenScale = getScreenScale_app();
	trueScreenScaleInt = (int)screenScale;
}

double getScreenScale_game() {
	if (windowWidth <= gameWidth || windowHeight <= gameHeight) return 1;
	return min(((double)windowWidth / gameWidth), ((double)windowHeight / gameHeight));
}

void scaleAppByGame() {
	screenScale = getScreenScale_game();
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
	screenScale_menu = (int)getScreenScale_app();
	menuToWindowDstRect.w = (int)(appWidth * screenScale_menu);
	menuToWindowDstRect.h = (int)(appHeight * screenScale_menu);
	menuToWindowDstRect.x = max((int)((windowWidth - menuToWindowDstRect.w) / 2), 0);
	menuToWindowDstRect.y = max((int)((windowHeight - menuToWindowDstRect.h) / 2), 0);
}

void repositionOverlay() {
	sprite_overlay_basement_top_ins.dstrect.w = (int)(sprite_overlay_basement_top.dstrect.w * screenScale);
	sprite_overlay_basement_top_ins.dstrect.h = (int)(sprite_overlay_basement_top.dstrect.h * screenScale);
	sprite_overlay_basement_bottom_ins.dstrect.w = (int)(sprite_overlay_basement_bottom.dstrect.w * screenScale);
	sprite_overlay_basement_bottom_ins.dstrect.h = (int)(sprite_overlay_basement_bottom.dstrect.h * screenScale);
	sprite_overlay_basement_left_ins.dstrect.w = (int)(sprite_overlay_basement_left.dstrect.w * screenScale);
	sprite_overlay_basement_left_ins.dstrect.h = (int)(sprite_overlay_basement_left.dstrect.h * screenScale);
	sprite_overlay_basement_right_ins.dstrect.w = (int)(sprite_overlay_basement_right.dstrect.w * screenScale);
	sprite_overlay_basement_right_ins.dstrect.h = (int)(sprite_overlay_basement_right.dstrect.h * screenScale);
	sprite_overlay_basement_top_ins.dstrect.x = gameToWindowDstRect.x - sprite_overlay_basement_left_ins.dstrect.w;
	sprite_overlay_basement_top_ins.dstrect.y = gameToWindowDstRect.y - sprite_overlay_basement_top_ins.dstrect.h;
	sprite_overlay_basement_bottom_ins.dstrect.x = sprite_overlay_basement_top_ins.dstrect.x;
	sprite_overlay_basement_bottom_ins.dstrect.y = gameToWindowDstRect.y + gameToWindowDstRect.h;
	sprite_overlay_basement_left_ins.dstrect.x = sprite_overlay_basement_top_ins.dstrect.x;
	sprite_overlay_basement_left_ins.dstrect.y = gameToWindowDstRect.y;
	sprite_overlay_basement_right_ins.dstrect.x = gameToWindowDstRect.x + gameToWindowDstRect.w;
	uint_i = sprite_overlay_basement_top_ins.dstrect.x + sprite_overlay_basement_top_ins.dstrect.w;
	uint_j = sprite_overlay_basement_right_ins.dstrect.x + sprite_overlay_basement_right_ins.dstrect.w;
	sprite_overlay_basement_right_ins.dstrect.x += (uint_i - uint_j);
	sprite_overlay_basement_right_ins.dstrect.y = sprite_overlay_basement_left_ins.dstrect.y;
	sprite_overlay_basement_top_ins.dstrect = sprite_overlay_basement_top_ins.dstrect;
	sprite_overlay_basement_bottom_ins.dstrect = sprite_overlay_basement_bottom_ins.dstrect;
	sprite_overlay_basement_left_ins.dstrect = sprite_overlay_basement_left_ins.dstrect;
	sprite_overlay_basement_right_ins.dstrect = sprite_overlay_basement_right_ins.dstrect;
	right_overlay_padding = sprite_overlay_basement_right_ins.dstrect;
	right_overlay_padding.x += right_overlay_padding.w;
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
	InitializeMenus();
#endif
}

void snapWindow_x(double range, Uint16 size) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX)) && !defined(SDL1)
	if (isWindowed) {
		double_i = ((float)SDL_GetWindowSurface(window)->w / size);
		if ((double_i - floor(double_i)) >= pow(1 - range, floor(double_i))) {
			if ((size * ceil(double_i)) < DM.w) {
				SDL_SetWindowSize(window, size * (short)(ceil(double_i)), SDL_GetWindowSurface(window)->h);
			}
		} else if ((double_i - floor(double_i)) < 1 - pow(1 - range, (short)(floor(double_i))) && (SDL_GetWindowSurface(window)->w % size != 0)) {
			SDL_SetWindowSize(window, size * (short)floor(double_i), SDL_GetWindowSurface(window)->h);
		}
	}
#endif
}

void snapWindow_y(double range, Uint16 size) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX)) && !defined(SDL1)
	if (isWindowed) {
		double_i = ((float)SDL_GetWindowSurface(window)->h / size);
		if ((double_i - floor(double_i)) >= pow(1 - range, (short)(floor(double_i)))) {
			if ((size * ceil(double_i)) < DM.h) {
				SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, size * (short)ceil(double_i));
			}
		} else if ((double_i - floor(double_i)) < 1 - pow(1 - range, (short)(floor(double_i))) && (SDL_GetWindowSurface(window)->h % size != 0)) {
			SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, size * (short)floor(double_i));
		}
	}
#endif
}

void SDL_toggleFullscreen() {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX)) && !defined(SDL1)
	isWindowed = !isWindowed;
	if (isWindowed) {
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowSize(window, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	} else {
		SDL_SetWindowSize(window, DM.w, DM.h);
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	//setScaling();
#endif
}