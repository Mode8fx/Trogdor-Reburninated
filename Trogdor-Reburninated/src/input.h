#ifndef INPUT_H
#define INPUT_H

// A/B/X/Y are Xbox-style
#define INPUT_UP          (1 <<  0)
#define INPUT_DOWN        (1 <<  1)
#define INPUT_LEFT        (1 <<  2)
#define INPUT_RIGHT       (1 <<  3)
#define INPUT_A           (1 <<  4)
#define INPUT_B           (1 <<  5)
#define INPUT_X           (1 <<  6)
#define INPUT_Y           (1 <<  7)
#define INPUT_L           (1 <<  8)
#define INPUT_R           (1 <<  9)
#define INPUT_START       (1 << 10)
#define INPUT_SELECT      (1 << 11)
#define INPUT_FULLSCREEN  (1 << 12)

#define STICK_DEADZONE (32767 * 0.1)



extern Uint32 keyInputs;
extern Uint32 heldKeys;

#define KEY_PRESSED(key) \
    (keyInputs & key)

#define KEY_HELD(button) \
	(heldKeys & button)

#endif