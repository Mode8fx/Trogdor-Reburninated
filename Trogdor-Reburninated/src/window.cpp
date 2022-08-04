#include "window.h"

void setWidthHeightMults() {
	gameWidthMult = ((double)GAME_WIDTH / DEFAULT_GAME_WIDTH);
	gameHeightMult = ((double)GAME_HEIGHT / DEFAULT_GAME_HEIGHT);
}

void updateBorderRects() {
	topRect.x = -(SCALING_WIDTH - GAME_WIDTH) / 2 - 50;
	topRect.y = -(SCALING_HEIGHT - GAME_HEIGHT) / 2 - 100;
	topRect.w = SCALING_WIDTH + 100;
	topRect.h = (SCALING_HEIGHT - GAME_HEIGHT) / 2 + 100;
	bottomRect.x = topRect.x;
	bottomRect.y = GAME_HEIGHT;
	bottomRect.w = topRect.w;
	bottomRect.h = topRect.h;
	leftRect.x = -(SCALING_WIDTH - GAME_WIDTH) / 2 - 100;
	leftRect.y = -(SCALING_HEIGHT - GAME_HEIGHT) / 2 - 50;
	leftRect.w = (SCALING_WIDTH - GAME_WIDTH) / 2 + 100;
	leftRect.h = SCALING_HEIGHT + 100;
	rightRect.x = GAME_WIDTH;
	rightRect.y = leftRect.y;
	rightRect.w = leftRect.w;
	rightRect.h = leftRect.h;
}

void setScaling() {
#if !defined(ANDROID)
	if (isIntegerScale) {
		int_i = min((int)(SCALING_WIDTH / GAME_WIDTH), (int)(SCALING_HEIGHT / GAME_HEIGHT));
		if (int_i < 1) int_i = 1;
		gameWindowDstRect.w = GAME_WIDTH * int_i;
		gameWindowDstRect.h = GAME_HEIGHT * int_i;
	} else {
		screenScale = (double)SCALING_WIDTH / GAME_WIDTH;
		if ((double)SCALING_HEIGHT / GAME_HEIGHT < screenScale) {
			screenScale = (double)SCALING_HEIGHT / GAME_HEIGHT;
		}
		if (screenScale < 1) screenScale = 1;
		gameWindowDstRect.w = (int)(GAME_WIDTH * screenScale);
		gameWindowDstRect.h = (int)(GAME_HEIGHT * screenScale);
	}
	gameWindowDstRect.x = max((int)((SCALING_WIDTH - gameWindowDstRect.w) / 2), 0);
	gameWindowDstRect.y = max((int)((SCALING_HEIGHT - gameWindowDstRect.h) / 2), 0);
	updateBorderRects();
	//SDL_RenderSetClipRect(renderer, &gameWindowDstRect);
#endif
}

void SDL_toggleFullscreen() {
#if defined(PC) && !defined(SDL1)
	isWindowed = !isWindowed;
	if (isWindowed)
		SDL_SetWindowFullscreen(window, 0);
	else
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	setScaling();
#endif
}

void SDL_toggleIntegerScale() {
	isIntegerScale = !isIntegerScale;
	setScaling();
}

void renderBorderRects() {
#if !defined(SDL1)
	SDL_RenderFillRect(renderer, &topRect);
	SDL_RenderFillRect(renderer, &bottomRect);
	SDL_RenderFillRect(renderer, &leftRect);
	SDL_RenderFillRect(renderer, &rightRect);
#endif
}