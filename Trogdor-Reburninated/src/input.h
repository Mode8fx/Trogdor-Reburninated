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

constexpr auto STICK_DEADZONE = 10922; // 32767 / 3



inline bool keyPressed(Uint16 key) {
	return (keyInputs & key);
}

inline bool keyHeld(Uint16 button) {
	return (heldKeys & button);
}

inline bool dirHeld(Uint8 dir) {
	return (heldDirs & dir);
}

inline void handleAnalogInput() {
	if (controllerAxis_leftStickY < 0) {
		heldDirs_stick |= INPUT_UP;
	} else {
		heldDirs_stick &= ~INPUT_UP;
	}
	if (controllerAxis_leftStickY > 0) {
		heldDirs_stick |= INPUT_DOWN;
	} else {
		heldDirs_stick &= ~INPUT_DOWN;
	}
	if (controllerAxis_leftStickX < 0) {
		heldDirs_stick |= INPUT_LEFT;
	} else {
		heldDirs_stick &= ~INPUT_LEFT;
	}
	if (controllerAxis_leftStickX > 0) {
		heldDirs_stick |= INPUT_RIGHT;
	} else {
		heldDirs_stick &= ~INPUT_RIGHT;
	}
}

inline void handleHeldKeys(Uint32 deltaTime) {
	heldDirs = heldDirs_kb | heldDirs_dpad | heldDirs_stick;
	heldKeys &= ~INPUT_ALL_DIRS;
	heldKeys |= heldDirs;
	keyInputs = heldKeys & ~heldKeys_last;
	if (timer_buttonHold > 0) {
		keyInputs &= ~INPUT_ALL_DIRS;
		if (timer_buttonHold > 500) {
			timer_buttonHold_repeater += deltaTime;
			if (timer_buttonHold_repeater >= 33) {
				keyInputs |= heldDirs;
				timer_buttonHold_repeater -= 33;
			}
		}
	}
}

inline void handleInput() {
	keyInputs = 0;
	/* Update Key/Button Presses, Mouse/Touch Input, and Window Resizing */
#if !defined(SDL1) && !defined(PSP)
	/* Update Controller Axes (SDL2 only; SDL1 axes are handled later) */
	controllerAxis_leftStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	controllerAxis_leftStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
	if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
		controllerAxis_leftStickX = 0;
	}
	if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
		controllerAxis_leftStickY = 0;
	}
#else
	/* Update Controller Hat Positions (SDL1 only; SDL2 D-Pad buttons are handled later) */
	joystickHat = SDL_JoystickGetHat(joystick, 0);
#if defined(WII)
	if (joystickHat & SDL_HAT_UP) {
		heldDirs_dpad |= INPUT_LEFT;
	} else {
		heldDirs_dpad &= ~INPUT_LEFT;
	}
	if (joystickHat & SDL_HAT_DOWN) {
		heldDirs_dpad |= INPUT_RIGHT;
	} else {
		heldDirs_dpad &= ~INPUT_RIGHT;
	}
	if (joystickHat & SDL_HAT_LEFT) {
		heldDirs_dpad |= INPUT_DOWN;
	} else {
		heldDirs_dpad &= ~INPUT_DOWN;
	}
	if (joystickHat & SDL_HAT_RIGHT) {
		heldDirs_dpad |= INPUT_UP;
	} else {
		heldDirs_dpad &= ~INPUT_UP;
	}
#else
	if (joystickHat & SDL_HAT_UP) {
		heldDirs_dpad |= INPUT_UP;
	} else {
		heldDirs_dpad &= ~INPUT_UP;
	}
	if (joystickHat & SDL_HAT_DOWN) {
		heldDirs_dpad |= INPUT_DOWN;
	} else {
		heldDirs_dpad &= ~INPUT_DOWN;
	}
	if (joystickHat & SDL_HAT_LEFT) {
		heldDirs_dpad |= INPUT_LEFT;
	} else {
		heldDirs_dpad &= ~INPUT_LEFT;
	}
	if (joystickHat & SDL_HAT_RIGHT) {
		heldDirs_dpad |= INPUT_RIGHT;
	} else {
		heldDirs_dpad &= ~INPUT_RIGHT;
	}
#endif
#endif
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP)) && !defined(SDL1)
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					windowSizeChanged = true;
				}
				break;
#endif
			case SDL_KEYDOWN: // keycodes
				if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
					heldDirs_kb |= INPUT_UP;
					break;
				}
				if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
					heldDirs_kb |= INPUT_DOWN;
					break;
				}
				if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
					heldDirs_kb |= INPUT_LEFT;
					break;
				}
				if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
					heldDirs_kb |= INPUT_RIGHT;
					break;
				}
				if (event.key.keysym.sym == SDLK_z) {
					heldKeys |= INPUT_A;
					break;
				}
				if (event.key.keysym.sym == SDLK_x) {
					heldKeys |= INPUT_B;
					break;
				}
				if (event.key.keysym.sym == SDLK_c) {
					heldKeys |= INPUT_X;
					break;
				}
				if (event.key.keysym.sym == SDLK_v) {
					heldKeys |= INPUT_Y;
					break;
				}
				if (event.key.keysym.sym == SDLK_q) {
					heldKeys |= INPUT_L;
					break;
				}
				if (event.key.keysym.sym == SDLK_e) {
					heldKeys |= INPUT_R;
					break;
				}
				if (event.key.keysym.sym == SDLK_RETURN) {
					heldKeys |= INPUT_START;
					break;
				}
				if (event.key.keysym.sym == SDLK_BACKSPACE) {
					heldKeys |= INPUT_SELECT;
					break;
				}
				if (event.key.keysym.sym == SDLK_f) {
					heldKeys |= INPUT_FULLSCREEN;
					break;
				}
				break;
			case SDL_KEYUP: // keycodes
				if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
					heldDirs_kb &= ~INPUT_UP;
					break;
				}
				if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
					heldDirs_kb &= ~INPUT_DOWN;
					break;
				}
				if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
					heldDirs_kb &= ~INPUT_LEFT;
					break;
				}
				if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
					heldDirs_kb &= ~INPUT_RIGHT;
					break;
				}
				if (event.key.keysym.sym == SDLK_z) {
					heldKeys &= ~INPUT_A;
					break;
				}
				if (event.key.keysym.sym == SDLK_x) {
					heldKeys &= ~INPUT_B;
					break;
				}
				if (event.key.keysym.sym == SDLK_c) {
					heldKeys &= ~INPUT_X;
					break;
				}
				if (event.key.keysym.sym == SDLK_v) {
					heldKeys &= ~INPUT_Y;
					break;
				}
				if (event.key.keysym.sym == SDLK_q) {
					heldKeys &= ~INPUT_L;
					break;
				}
				if (event.key.keysym.sym == SDLK_e) {
					heldKeys &= ~INPUT_R;
					break;
				}
				if (event.key.keysym.sym == SDLK_RETURN) {
					heldKeys &= ~INPUT_START;
					break;
				}
				if (event.key.keysym.sym == SDLK_BACKSPACE) {
					heldKeys &= ~INPUT_SELECT;
					break;
				}
				if (event.key.keysym.sym == SDLK_f) {
					heldKeys &= ~INPUT_FULLSCREEN;
					break;
				}
				break;
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP))
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseInput_x, &mouseInput_y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					break;
				}
				if (event.button.button == SDL_BUTTON_RIGHT) {
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				break;
#endif
#if !defined(SDL1) && !defined(PSP)
			case SDL_CONTROLLERBUTTONDOWN:
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
					heldDirs_dpad |= INPUT_UP;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
					heldDirs_dpad |= INPUT_DOWN;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
					heldDirs_dpad |= INPUT_LEFT;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
					heldDirs_dpad |= INPUT_RIGHT;
					break;
				}
#if defined(WII_U) || defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#endif
					heldKeys |= INPUT_A;
					break;
				}
#if defined(WII_U) || defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#endif
					heldKeys |= INPUT_B;
					break;
				}
#if defined(WII_U) || defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#endif
					heldKeys |= INPUT_X;
					break;
				}
#if defined(WII_U) || defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#endif
					heldKeys |= INPUT_Y;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
					heldKeys |= INPUT_L;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
					heldKeys |= INPUT_R;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
					heldKeys |= INPUT_START;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
					heldKeys |= INPUT_SELECT;
					break;
				}
				break;
			case SDL_CONTROLLERBUTTONUP:
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
					heldDirs_dpad &= ~INPUT_UP;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
					heldDirs_dpad &= ~INPUT_DOWN;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
					heldDirs_dpad &= ~INPUT_LEFT;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
					heldDirs_dpad &= ~INPUT_RIGHT;
					break;
				}
#if defined(WII_U) || defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#endif
					heldKeys &= ~INPUT_A;
					break;
				}
#if defined(WII_U) || defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#endif
					heldKeys &= ~INPUT_B;
					break;
				}
#if defined(WII_U) || defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#endif
					heldKeys &= ~INPUT_X;
					break;
				}
#if defined(WII_U) || defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#endif
					heldKeys &= ~INPUT_Y;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
					heldKeys &= ~INPUT_L;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
					heldKeys &= ~INPUT_R;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
					heldKeys &= ~INPUT_START;
					break;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
					heldKeys &= ~INPUT_SELECT;
					break;
				}
				break;
#if !defined(PSP)
			case SDL_FINGERDOWN:
				mouseInput_x = (Sint32)(event.tfinger.x * windowWidth);
				mouseInput_y = (Sint32)(event.tfinger.y * windowHeight);
				break;
			case SDL_FINGERMOTION:
				mouseInput_x = (Sint32)(event.tfinger.x * windowWidth);
				mouseInput_y = (Sint32)(event.tfinger.y * windowHeight);
				break;
			case SDL_FINGERUP:
				break;
#endif
			default:
				break;
#else
#if defined(WII)
			case SDL_JOYBUTTONDOWN:
				if (event.jbutton.button == 0) {
					heldKeys |= INPUT_R;
					break;
				}
				if (event.jbutton.button == 1) {
					heldKeys |= INPUT_L;
					break;
				}
				if (event.jbutton.button == 2) {
					heldKeys |= INPUT_B;
					break;
				}
				if (event.jbutton.button == 3) {
					heldKeys |= INPUT_A;
					break;
				}
				if (event.jbutton.button == 4) {
					heldKeys |= INPUT_SELECT;
					break;
				}
				if (event.jbutton.button == 5) {
					heldKeys |= INPUT_START;
					break;
				}
				if (event.jbutton.button == 6) {
					heldKeys |= INPUT_Y;
					break;
				}
				if (event.jbutton.button == 7) {
					heldKeys |= INPUT_START;
					break;
				}
				break;
			case SDL_JOYBUTTONUP:
				if (event.jbutton.button == 0) {
					heldKeys &= ~INPUT_R;
					break;
				}
				if (event.jbutton.button == 1) {
					heldKeys &= ~INPUT_L;
					break;
				}
				if (event.jbutton.button == 2) {
					heldKeys &= ~INPUT_B;
					break;
				}
				if (event.jbutton.button == 3) {
					heldKeys &= ~INPUT_A;
					break;
				}
				if (event.jbutton.button == 4) {
					heldKeys &= ~INPUT_SELECT;
					break;
				}
				if (event.jbutton.button == 5) {
					heldKeys &= ~INPUT_START;
					break;
				}
				if (event.jbutton.button == 6) {
					heldKeys &= ~INPUT_Y;
					break;
				}
				if (event.jbutton.button == 7) {
					heldKeys &= ~INPUT_START;
					break;
				}
				break;
#elif defined(GAMECUBE)
			case SDL_JOYBUTTONDOWN:
				if (event.jbutton.button == 0) {
					heldKeys |= INPUT_A;
					break;
				}
				if (event.jbutton.button == 1) {
					heldKeys |= INPUT_B;
					break;
				}
				if (event.jbutton.button == 2) {
					heldKeys |= INPUT_X;
					break;
				}
				if (event.jbutton.button == 3) {
					heldKeys |= INPUT_Y;
					break;
				}
				if (event.jbutton.button == 4) {
					heldKeys |= INPUT_SELECT;
					break;
				}
				if (event.jbutton.button == 5) {
					heldKeys |= INPUT_R;
					break;
				}
				if (event.jbutton.button == 6) {
					heldKeys |= INPUT_L;
					break;
				}
				if (event.jbutton.button == 7) {
					heldKeys |= INPUT_START;
					break;
				}
				break;
			case SDL_JOYBUTTONUP:
				if (event.jbutton.button == 0) {
					heldKeys &= ~INPUT_A;
					break;
				}
				if (event.jbutton.button == 1) {
					heldKeys &= ~INPUT_B;
					break;
				}
				if (event.jbutton.button == 2) {
					heldKeys &= ~INPUT_X;
					break;
				}
				if (event.jbutton.button == 3) {
					heldKeys &= ~INPUT_Y;
					break;
				}
				if (event.jbutton.button == 4) {
					heldKeys &= ~INPUT_SELECT;
					break;
				}
				if (event.jbutton.button == 5) {
					heldKeys &= ~INPUT_R;
					break;
				}
				if (event.jbutton.button == 6) {
					heldKeys &= ~INPUT_L;
					break;
				}
				if (event.jbutton.button == 7) {
					heldKeys &= ~INPUT_START;
					break;
				}
				break;
#else // PSP
			case SDL_JOYBUTTONDOWN:
				if (event.jbutton.button == 8) { // Up
					heldDirs_dpad |= INPUT_UP;
					break;
				}
				if (event.jbutton.button == 6) { // Down
					heldDirs_dpad |= INPUT_DOWN;
					break;
				}
				if (event.jbutton.button == 7) { // Left
					heldDirs_dpad |= INPUT_LEFT;
					break;
				}
				if (event.jbutton.button == 9) { // Right
					heldDirs_dpad |= INPUT_RIGHT;
					break;
				}
				if (event.jbutton.button == 1) { // O
					heldKeys |= INPUT_B;
					break;
				}
				if (event.jbutton.button == 2) { // X
					heldKeys |= INPUT_A;
					break;
				}
				if (event.jbutton.button == 11) { // Start
					heldKeys |= INPUT_START;
					break;
				}
				if (event.jbutton.button == 10) { // Select
					heldKeys |= INPUT_SELECT;
					break;
				}
				if (event.jbutton.button == 0) { // Triangle
					heldKeys |= INPUT_Y;
					break;
				}
				if (event.jbutton.button == 3) { // Square
					heldKeys |= INPUT_X;
					break;
				}
				if (event.jbutton.button == 4) { // L
					heldKeys |= INPUT_L;
					break;
				}
				if (event.jbutton.button == 5) { // R
					heldKeys |= INPUT_R;
					break;
				}
				break;
			case SDL_JOYBUTTONUP:
				if (event.jbutton.button == 8) { // Up
					heldDirs_dpad &= ~INPUT_UP;
					break;
				}
				if (event.jbutton.button == 6) { // Down
					heldDirs_dpad &= ~INPUT_DOWN;
					break;
				}
				if (event.jbutton.button == 7) { // Left
					heldDirs_dpad &= ~INPUT_LEFT;
					break;
				}
				if (event.jbutton.button == 9) { // Right
					heldDirs_dpad &= ~INPUT_RIGHT;
					break;
				}
				if (event.jbutton.button == 1) { // O
					heldKeys &= ~INPUT_B;
					break;
				}
				if (event.jbutton.button == 2) { // X
					heldKeys &= ~INPUT_A;
					break;
				}
				if (event.jbutton.button == 11) { // Start
					heldKeys &= ~INPUT_START;
					break;
				}
				if (event.jbutton.button == 10) { // Select
					heldKeys &= ~INPUT_SELECT;
					break;
				}
				if (event.jbutton.button == 0) { // Triangle
					heldKeys &= ~INPUT_Y;
					break;
				}
				if (event.jbutton.button == 3) { // Square
					heldKeys &= ~INPUT_X;
					break;
				}
				if (event.jbutton.button == 4) { // L
					heldKeys &= ~INPUT_L;
					break;
				}
				if (event.jbutton.button == 5) { // R
					heldKeys &= ~INPUT_R;
					break;
				}
				break;
#endif
			case SDL_JOYAXISMOTION:
				switch (event.jaxis.axis) {
					case 0:
						controllerAxis_leftStickX = event.jaxis.value;
						if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
							controllerAxis_leftStickX = 0;
						}
						break;
					case 1:
						controllerAxis_leftStickY = event.jaxis.value;
						if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
							controllerAxis_leftStickY = 0;
						}
						break;
					default:
						break;
				}
				break;
#endif
		}
	}
	handleAnalogInput();
	handleHeldKeys(deltaTime);
}

#endif