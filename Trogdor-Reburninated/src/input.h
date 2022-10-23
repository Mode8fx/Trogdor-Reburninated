#ifndef INPUT_H
#define INPUT_H

#include "general.h"

/* SDL Input */
#if !defined(SDL1) && !defined(PSP)
extern SDL_GameController *controller;
#else
extern SDL_Joystick *joystick;
extern Uint8 joystickHat;
#endif

/* General Input */
extern Uint32 keyInputs;
extern Uint32 heldKeys;
extern Uint32 heldKeys_last;
extern Uint8  heldDirs;
extern Uint8  heldDirs_last;
extern Uint8  heldDirs_kb;
extern Uint8  heldDirs_dpad;
extern Uint8  heldDirs_stick;
extern Sint32 timer_buttonHold;
extern Sint32 timer_buttonHold_repeater;
extern Sint16 controllerAxis_leftStickX;
extern Sint16 controllerAxis_leftStickY;
#if defined(WII)
extern Uint32 wii_keysDown;
extern Uint32 wii_keysUp;
#endif
#if !(defined(GAMECUBE) || defined(PSP))
extern Sint32 mouseInput_x;
extern Sint32 mouseInput_x_last;
extern Sint32 mouseInput_y;
extern Sint32 mouseInput_y_last;
#endif

// A/B/X/Y are Xbox-style
constexpr auto INPUT_UP         = (1 <<  0); // up/w
constexpr auto INPUT_DOWN       = (1 <<  1); // down/s
constexpr auto INPUT_LEFT       = (1 <<  2); // left/a
constexpr auto INPUT_RIGHT      = (1 <<  3); // right/d
constexpr auto INPUT_A          = (1 <<  4); // z
constexpr auto INPUT_B          = (1 <<  5); // x
constexpr auto INPUT_X          = (1 <<  6); // c
constexpr auto INPUT_Y          = (1 <<  7); // v
constexpr auto INPUT_L          = (1 <<  8); // q
constexpr auto INPUT_R          = (1 <<  9); // e
constexpr auto INPUT_START      = (1 << 10); // enter
constexpr auto INPUT_SELECT     = (1 << 11); // backspace
constexpr auto INPUT_FULLSCREEN = (1 << 12); // f
constexpr auto INPUT_ALL_DIRS   = INPUT_UP | INPUT_DOWN | INPUT_LEFT | INPUT_RIGHT;

bool keyPressed(Uint16 key);
bool keyHeld(Uint16 button);
inline bool dirHeld(Uint8 dir);
inline void handleAnalogInput();
inline void handleHeldKeys(Uint32 deltaTime);
#if defined(WII)
inline void wii_mapWiiDir(Uint32 wiimoteInput, Uint32 ccInput, Uint32 output);
inline void wii_mapWiiButton(Uint32 wiimoteInput, Uint32 ccInput, Uint32 output);
inline void wii_mapGCDir(Uint32 gcInput, Uint32 output);
inline void wii_mapGCButton(Uint32 gcInput, Uint32 output);
#endif
void handleInput();

#endif