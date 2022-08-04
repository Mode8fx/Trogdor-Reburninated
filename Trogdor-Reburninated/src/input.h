#ifndef INPUT_H
#define INPUT_H

/* General Input */
extern Uint32 keyInputs;
extern Uint32 heldKeys;

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

constexpr auto STICK_DEADZONE = 3277; // 32767 * 0.1



inline bool keyPressed(Uint16 key) {
	return (keyInputs & key);
}

inline bool keyHeld(Uint16 button) {
	return (heldKeys & button);
}

#endif