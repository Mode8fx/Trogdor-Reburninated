#ifndef GENERAL_H
#define GENERAL_H

#include "include.h"

struct Timer {
    double now;
    double last;
};

static bool isRunning;
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP)) && !defined(SDL1)
static bool windowSizeChanged;
#endif
extern SDL_Event event;

/* General-use Variables */
extern Sint8 i, j, k;
extern int int_i, int_j, int_k;
extern Uint32 uint_i, uint_j, uint_k;
extern float float_i;
extern double double_i;

/* Timer */
extern Timer timer_global;
extern Uint32 deltaTime;

/* Framerate */
extern Uint32 frameTime;
extern Uint32 frameCounter_global;

constexpr auto PI = 3.14159265;

#if defined(SDL1) && !defined(WII) && !defined(GAMECUBE) && !defined(PSP)
extern FILE _iob[];

extern "C" FILE * __cdecl __iob_func(void);
#endif

extern void SYSTEM_SPECIFIC_OPEN();
extern void SYSTEM_SPECIFIC_CLOSE();

#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP))
#define STRCPY(dest, src) strcpy_s(dest, src);
#else
#define STRCPY(dest, src) strcpy(dest, src);
#endif

#define RANDINT(min, max) \
    (rand() % ((max) - (min) + 1) + min)

#define LEN(arr) \
    (sizeof(arr) / sizeof(arr[0]))

#define ZERO_OUT_ARRAY(arr) \
    (memset(arr, 0, sizeof(arr)))

#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP))
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

#endif