#ifndef GENERAL_H
#define GENERAL_H

/* General-use Variables */
extern Sint8 i, j, k;
extern int int_i, int_j, int_k;
extern Uint32 uint_i, uint_j, uint_k;
extern float float_i;

struct Timer {
    double now;
    double last;
};

#define PI 3.14159265

#define RANDINT(min, max) \
    (rand() % ((max) - (min) + 1) + min)

#define LEN(arr) \
    (sizeof(arr) / sizeof(arr[0]))

#define ZERO_OUT_ARRAY(arr) \
    (memset(arr, 0, sizeof(arr)))

#if defined(PC)
#define PRINT(str) \
    cout << str << endl
#else
#define PRINT(str)
#endif

#define SIN_WAVE(timeVal, halfPeriod, amplitude) \
    (sin((timeVal) * PI / (halfPeriod)) * (amplitude))

#define COS_WAVE(timeVal, halfPeriod, amplitude) \
    (cos((timeVal) * PI / (halfPeriod)) * (amplitude))

#define MOVE_FAST_THEN_DECELERATE(dist, numSeconds, timeVal) \
    (0.5 * pow(((((numSeconds) - (timeVal)) / (numSeconds)) * sqrt(2 * (dist))), 2))

#define UPDATE_TIMER(timer) \
    timer.last = timer.now; \
    timer.now = SDL_GetTicks() / 1000.0;



#if !defined(PC) || defined(SDL1)
#define SDL_TOGGLE_FULLSCREEN()
#else
#define SDL_TOGGLE_FULLSCREEN()                                 \
	isWindowed = !isWindowed;                                   \
	if (isWindowed)                                             \
		SDL_SetWindowFullscreen(window, 0);                     \
	else                                                        \
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); \
	SET_SCALING();
#endif

#define SDL_TOGGLE_INTEGER_SCALE()    \
	isIntegerScale = !isIntegerScale; \
	SET_SCALING();

#if !defined(PC) || defined(SDL1)
#define SCALING_WIDTH DEFAULT_GAME_WIDTH
#define SCALING_HEIGHT DEFAULT_GAME_HEIGHT
#else
#define SCALING_WIDTH SDL_GetWindowSurface(window)->w
#define SCALING_HEIGHT SDL_GetWindowSurface(window)->h
#endif

#if defined(ANDROID)
#define SET_SCALING()
#else
#define SET_SCALING()                                                                      \
	if (isIntegerScale) {                                                                  \
		int_i = min((int)(SCALING_WIDTH / gameWidth), (int)(SCALING_HEIGHT / gameHeight)); \
		if (int_i < 1) int_i = 1;                                                          \
		gameWindowDstRect.w = gameWidth * int_i;                                           \
		gameWindowDstRect.h = gameHeight * int_i;                                          \
	} else {                                                                               \
		screenScale = (double)SCALING_WIDTH / gameWidth;                                   \
		if ((double)SCALING_HEIGHT / gameHeight < screenScale) {                           \
			screenScale = (double)SCALING_HEIGHT / gameHeight;                             \
		}                                                                                  \
		if (screenScale < 1) screenScale = 1;                                              \
		gameWindowDstRect.w = (int)(gameWidth * screenScale);                              \
		gameWindowDstRect.h = (int)(gameHeight * screenScale);                             \
	}                                                                                      \
	gameWindowDstRect.x = max((int)((SCALING_WIDTH - gameWindowDstRect.w) / 2), 0);        \
	gameWindowDstRect.y = max((int)((SCALING_HEIGHT - gameWindowDstRect.h) / 2), 0);       \
	UPDATE_BORDER_RECTS();
//SDL_RenderSetClipRect(renderer, &gameWindowDstRect);
#endif

#define UPDATE_BORDER_RECTS()                             \
	topRect.x = -(SCALING_WIDTH - gameWidth) / 2 - 50;    \
	topRect.y = -(SCALING_HEIGHT - gameHeight) / 2 - 100; \
	topRect.w = SCALING_WIDTH + 100;                      \
	topRect.h = (SCALING_HEIGHT - gameHeight) / 2 + 100;  \
	bottomRect.x = topRect.x;                             \
	bottomRect.y = gameHeight;                            \
	bottomRect.w = topRect.w;                             \
	bottomRect.h = topRect.h;                             \
	leftRect.x = -(SCALING_WIDTH - gameWidth) / 2 - 100;  \
	leftRect.y = -(SCALING_HEIGHT - gameHeight) / 2 - 50; \
	leftRect.w = (SCALING_WIDTH - gameWidth) / 2 + 100;   \
	leftRect.h = SCALING_HEIGHT + 100;                    \
	rightRect.x = gameWidth;                              \
	rightRect.y = leftRect.y;                             \
	rightRect.w = leftRect.w;                             \
	rightRect.h = leftRect.h;

#if !defined(SDL1)
#define RENDER_BORDER_RECTS()                  \
	SDL_RenderFillRect(renderer, &topRect);    \
	SDL_RenderFillRect(renderer, &bottomRect); \
	SDL_RenderFillRect(renderer, &leftRect);   \
	SDL_RenderFillRect(renderer, &rightRect);
#else
#define RENDER_BORDER_RECTS()
#endif

#endif