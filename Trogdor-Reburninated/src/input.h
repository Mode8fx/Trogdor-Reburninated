#ifndef INPUT_H
#define INPUT_H

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

inline void handleKeyPresses(Uint32 deltaTime) {
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

#endif