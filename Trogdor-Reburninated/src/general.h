#include "include.h"

#ifndef GENERAL_H
#define GENERAL_H

struct Timer {
    double now;
    double last;
};

class FrameState {
	public:
		Uint16 frame;
		float subFrame;
		Uint16 nextFrame;
		float nextSubFrame;
		bool atStartOfFrame; // for things that should only happen once, at the start of a frame (e.g. playing a sound)
		bool atEndOfFrame;   // for things that shouldn't happen until the end of a frame (e.g. changing scenes)
		FrameState();
		void set(Uint16);
		void increment();
		bool startingFrame(Uint16);
		bool endingFrame(Uint16);
		void subtract(float);
		void mod(Uint8);
};

/* Program State */
extern bool isRunning;
extern bool windowSizeChanged;
extern Sint16 g_sceneState;
extern FrameState g_frameState;
extern Uint32 rand_var;
extern SDL_Event event;

/* General-use Variables */
extern Sint8 i, j, k;
extern int int_i, int_j, int_k;
extern Uint32 uint_i, uint_j, uint_k;
extern float float_i;
extern double double_i;
extern SDL_Rect outputRect;

/* Timer */
extern Timer timer_global;
extern Uint32 deltaTime;

/* Framerate */
extern Uint32 frameTime;
extern Uint32 frameCounter_global;
constexpr auto ORIGINAL_FRAME_RATE = 16;
extern Uint8 frameRate;
extern float frameRateMult;
extern Uint16 popRandVal;

constexpr auto PI = 3.14159265;

#if defined(SDL1) && !defined(WII) && !defined(GAMECUBE) && !defined(PSP) && !defined(THREEDS)
extern FILE _iob[];

extern "C" FILE * __cdecl __iob_func(void);
#endif

#if defined(_WIN32) && !defined(_WIN64)
#define AUDIO_TROG_FORMAT AUDIO_S32SYS
#else
#define AUDIO_TROG_FORMAT MIX_DEFAULT_FORMAT
#endif

#if defined(THREEDS) || defined(VITA)
constexpr auto AUDIO_SAMPLE_RATE = 22050;
#else
constexpr auto AUDIO_SAMPLE_RATE = 44100;
#endif

extern void applyColorKey(SDL_Surface *);
extern void systemSpecificOpen();
extern void systemSpecificClose();

#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX) || defined(LINUX))
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

#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX))
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