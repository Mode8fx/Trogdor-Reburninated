#ifndef INPUT_H
#define INPUT_H

// A/B/X/Y are Xbox-style
#define INPUT_UP          (1 <<  0) // up/w
#define INPUT_DOWN        (1 <<  1) // down/s
#define INPUT_LEFT        (1 <<  2) // left/a
#define INPUT_RIGHT       (1 <<  3) // right/d
#define INPUT_A           (1 <<  4) // z
#define INPUT_B           (1 <<  5) // x
#define INPUT_X           (1 <<  6) // c
#define INPUT_Y           (1 <<  7) // v
#define INPUT_L           (1 <<  8) // q
#define INPUT_R           (1 <<  9) // e
#define INPUT_START       (1 << 10) // enter
#define INPUT_SELECT      (1 << 11) // ` (backquote)
#define INPUT_FULLSCREEN  (1 << 12) // f

#define STICK_DEADZONE (32767 * 0.1)



extern Uint32 keyInputs;
extern Uint32 heldKeys;

#define KEY_PRESSED(key) \
    (keyInputs & key)

#define KEY_HELD(button) \
	(heldKeys & button)

#endif