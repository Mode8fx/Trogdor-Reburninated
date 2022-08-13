#ifndef INPUT_H
#define INPUT_H

/* General Input */
extern Uint32 keyInputs;
extern Uint32 heldKeys;
extern Uint8 dirInputs;
extern Uint8 heldDirs;
extern Sint32 timer_buttonHold;
extern Sint32 timer_buttonHold_repeater;
extern Sint16 controllerAxis_leftStickX;
extern Sint16 controllerAxis_leftStickX_last;
extern Sint16 controllerAxis_leftStickY;
extern Sint16 controllerAxis_leftStickY_last;

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
constexpr auto INPUT_SELECT     = (1 << 11); // ` (backquote)
constexpr auto INPUT_FULLSCREEN = (1 << 12); // f

constexpr auto STICK_DEADZONE = 10922; // 32767 / 3

constexpr auto LEFT_PRESSED    = (1 << 0);
constexpr auto LEFT_DEPRESSED  = (1 << 1);
constexpr auto RIGHT_PRESSED   = (1 << 2);
constexpr auto RIGHT_DEPRESSED = (1 << 3);
constexpr auto UP_PRESSED      = (1 << 4);
constexpr auto UP_DEPRESSED    = (1 << 5);
constexpr auto DOWN_PRESSED    = (1 << 6);
constexpr auto DOWN_DEPRESSED  = (1 << 7);



inline bool keyPressed(Uint16 key) {
	return (keyInputs & key);
}

inline bool keyHeld(Uint16 button) {
	return (heldKeys & button);
}

inline bool dirHeld(Uint8 dir) {
	return (heldDirs & dir);
}

inline void dirHandler(Uint8 pressedVal, Uint8 depressedVal, Uint16 inputVal) {
	if (dirInputs & depressedVal) {
		heldDirs &= ~inputVal;
	} else if (dirInputs & pressedVal) {
		keyInputs |= inputVal;
		heldDirs |= inputVal;
	} 
}

inline void getDirectionInput(double deltaTime) {
	if ((controllerAxis_leftStickY < 0) && !(controllerAxis_leftStickY_last < 0)) {
		dirInputs |= UP_PRESSED;
		heldKeys |= INPUT_UP;
	} else if (!(controllerAxis_leftStickY < 0) && (controllerAxis_leftStickY_last < 0)) { // a little redundant, but easier to read
		dirInputs |= UP_DEPRESSED;
		heldKeys &= ~INPUT_UP;
	}
	if ((controllerAxis_leftStickY > 0) && !(controllerAxis_leftStickY_last > 0)) {
		dirInputs |= DOWN_PRESSED;
		heldKeys |= INPUT_DOWN;
	} else if (!(controllerAxis_leftStickY > 0) && (controllerAxis_leftStickY_last > 0)) {
		dirInputs |= DOWN_DEPRESSED;
		heldKeys &= ~INPUT_DOWN;
	}
	if ((controllerAxis_leftStickX < 0) && !(controllerAxis_leftStickX_last < 0)) {
		dirInputs |= LEFT_PRESSED;
		heldKeys |= INPUT_LEFT;
	} else if (!(controllerAxis_leftStickX < 0) && (controllerAxis_leftStickX_last < 0)) {
		dirInputs |= LEFT_DEPRESSED;
		heldKeys &= ~INPUT_LEFT;
	}
	if ((controllerAxis_leftStickX > 0) && !(controllerAxis_leftStickX_last > 0)) {
		dirInputs |= RIGHT_PRESSED;
		heldKeys |= INPUT_RIGHT;
	} else if (!(controllerAxis_leftStickX > 0) && (controllerAxis_leftStickX_last > 0)) {
		dirInputs |= RIGHT_DEPRESSED;
		heldKeys &= ~INPUT_RIGHT;
	}
	dirHandler(UP_PRESSED, UP_DEPRESSED, INPUT_UP);
	dirHandler(DOWN_PRESSED, DOWN_DEPRESSED, INPUT_DOWN);
	dirHandler(LEFT_PRESSED, LEFT_DEPRESSED, INPUT_LEFT);
	dirHandler(RIGHT_PRESSED, RIGHT_DEPRESSED, INPUT_RIGHT);
	if (timer_buttonHold > 500) {
		timer_buttonHold_repeater += deltaTime;
		if (timer_buttonHold_repeater >= 33) {
			if (dirHeld(INPUT_UP)) {
				keyInputs |= INPUT_UP;
			}
			if (dirHeld(INPUT_DOWN)) {
				keyInputs |= INPUT_DOWN;
			}
			if (dirHeld(INPUT_LEFT)) {
				keyInputs |= INPUT_LEFT;
			}
			if (dirHeld(INPUT_RIGHT)) {
				keyInputs |= INPUT_RIGHT;
			}
			timer_buttonHold_repeater -= 33;
		}
	}
}

#endif