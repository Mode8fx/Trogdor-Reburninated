#include "input.h"
#include "general.h"

constexpr auto STICK_DEADZONE = 10922; // 32767 / 3

bool keyPressed(Uint16 key) {
	return (keyInputs & key);
}

bool keyHeld(Uint16 button) {
	return (heldKeys & button);
}

inline static bool dirHeld(Uint8 dir) {
	return (heldDirs & dir);
}

inline static void handleAnalogInput() {
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

inline static void handleHeldKeys(Uint32 deltaTime) {
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

inline static void applyStickDeadZoneX() {
	if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
		controllerAxis_leftStickX = 0;
	}
}

inline static void applyStickDeadZoneY() {
	if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
		controllerAxis_leftStickY = 0;
	}
}

#if defined(WII)
inline static void wii_mapWiiDir(Uint32 wiimoteInput, Uint32 ccInput, Uint32 output) {
	if (wii_keysDown & wiimoteInput || wii_keysDown & ccInput) {
		heldDirs_dpad |= output;
	} else if (wii_keysUp & wiimoteInput || wii_keysUp & ccInput) {
		heldDirs_dpad &= ~output;
	}
}

inline static void wii_mapWiiButton(Uint32 wiimoteInput, Uint32 ccInput, Uint32 output) {
	if (wii_keysDown & wiimoteInput || wii_keysDown & ccInput) {
		heldKeys |= output;
	} else if (wii_keysUp & wiimoteInput || wii_keysUp & ccInput) {
		heldKeys &= ~output;
	}
}

inline static void wii_mapGCDir(Uint32 gcInput, Uint32 output) {
	if (wii_keysDown & gcInput) {
		heldDirs_dpad |= output;
	} else if (wii_keysUp & gcInput) {
		heldDirs_dpad &= ~output;
	}
}

inline static void wii_mapGCButton(Uint32 gcInput, Uint32 output) {
	if (wii_keysDown & gcInput) {
		heldKeys |= output;
	} else if (wii_keysUp & gcInput) {
		heldKeys &= ~output;
	}
}
#elif defined(GAMECUBE)
inline static void gc_mapDir(Uint32 gcInput, Uint32 output) {
	if (gc_keysDown & gcInput) {
		heldDirs_dpad |= output;
	} else if (gc_keysUp & gcInput) {
		heldDirs_dpad &= ~output;
	}
}

inline static void gc_mapButton(Uint32 gcInput, Uint32 output) {
	if (gc_keysDown & gcInput) {
		heldKeys |= output;
	} else if (gc_keysUp & gcInput) {
		heldKeys &= ~output;
	}
}
#endif

void handlePlayerInput() {
#if defined(WII)
	WPAD_ScanPads();
	WPAD_Expansion(WPAD_CHAN_0, &wii_exp);
	wii_keysDown = WPAD_ButtonsDown(0) | WPAD_ButtonsDown(1) | WPAD_ButtonsDown(2) | WPAD_ButtonsDown(3);
	wii_keysUp = WPAD_ButtonsUp(0) | WPAD_ButtonsUp(1) | WPAD_ButtonsUp(2) | WPAD_ButtonsUp(3);
	wii_mapWiiDir(WPAD_BUTTON_UP, WPAD_CLASSIC_BUTTON_LEFT, INPUT_LEFT);
	wii_mapWiiDir(WPAD_BUTTON_DOWN, WPAD_CLASSIC_BUTTON_RIGHT, INPUT_RIGHT);
	wii_mapWiiDir(WPAD_BUTTON_LEFT, WPAD_CLASSIC_BUTTON_DOWN, INPUT_DOWN);
	wii_mapWiiDir(WPAD_BUTTON_RIGHT, WPAD_CLASSIC_BUTTON_UP, INPUT_UP);
	wii_mapWiiButton(WPAD_BUTTON_A, WPAD_CLASSIC_BUTTON_FULL_R, INPUT_R);
	wii_mapWiiButton(WPAD_BUTTON_B, WPAD_CLASSIC_BUTTON_FULL_L, INPUT_L);
	wii_mapWiiButton(WPAD_BUTTON_1, WPAD_CLASSIC_BUTTON_B, INPUT_B);
	wii_mapWiiButton(WPAD_BUTTON_2, WPAD_CLASSIC_BUTTON_A, INPUT_A);
	wii_mapWiiButton(WPAD_BUTTON_PLUS, WPAD_CLASSIC_BUTTON_PLUS, INPUT_START);
	wii_mapWiiButton(WPAD_BUTTON_MINUS, WPAD_CLASSIC_BUTTON_MINUS, INPUT_SELECT);
	wii_mapWiiButton(WPAD_BUTTON_HOME, WPAD_CLASSIC_BUTTON_HOME, INPUT_Y);
	wii_mapWiiButton(WPAD_BUTTON_HOME, WPAD_CLASSIC_BUTTON_Y, INPUT_Y);
	if (wii_exp.type == EXP_CLASSIC) {
		controllerAxis_leftStickX = ((Sint16)wii_exp.classic.ljs.pos.x - 32) * 1023;
		controllerAxis_leftStickY = ((Sint16)wii_exp.classic.ljs.pos.y - 32) * -1023;
		applyStickDeadZoneX();
		applyStickDeadZoneY();
	} else {
		controllerAxis_leftStickX = 0;
		controllerAxis_leftStickY = 0;
	}

	PAD_ScanPads();
	wii_keysDown = PAD_ButtonsDown(0) | PAD_ButtonsDown(1) | PAD_ButtonsDown(2) | PAD_ButtonsDown(3);
	wii_keysUp = PAD_ButtonsUp(0) | PAD_ButtonsUp(1) | PAD_ButtonsUp(2) | PAD_ButtonsUp(3);
	wii_mapGCDir(PAD_BUTTON_UP, INPUT_UP);
	wii_mapGCDir(PAD_BUTTON_DOWN, INPUT_DOWN);
	wii_mapGCDir(PAD_BUTTON_LEFT, INPUT_LEFT);
	wii_mapGCDir(PAD_BUTTON_RIGHT, INPUT_RIGHT);
	wii_mapGCButton(PAD_BUTTON_A, INPUT_A);
	wii_mapGCButton(PAD_BUTTON_B, INPUT_B);
	wii_mapGCButton(PAD_BUTTON_X, INPUT_X);
	wii_mapGCButton(PAD_BUTTON_Y, INPUT_Y);
	wii_mapGCButton(PAD_TRIGGER_L, INPUT_L);
	wii_mapGCButton(PAD_TRIGGER_R, INPUT_R);
	wii_mapGCButton(PAD_TRIGGER_Z, INPUT_SELECT);
	wii_mapGCButton(PAD_BUTTON_START, INPUT_START);
	for (char i = 0; i < 4; i++) {
		controllerAxis_leftStickX = PAD_StickX(i) * 256;
		controllerAxis_leftStickY = PAD_StickY(i) * -256;
		applyStickDeadZoneX();
		applyStickDeadZoneY();
		if (controllerAxis_leftStickX != 0 || controllerAxis_leftStickY != 0) {
			break;
		}
	}
#elif defined(GAMECUBE)
	PAD_ScanPads();
	gc_keysDown = PAD_ButtonsDown(0) | PAD_ButtonsDown(1) | PAD_ButtonsDown(2) | PAD_ButtonsDown(3);
	gc_keysUp = PAD_ButtonsUp(0) | PAD_ButtonsUp(1) | PAD_ButtonsUp(2) | PAD_ButtonsUp(3);
	gc_mapDir(PAD_BUTTON_UP, INPUT_UP);
	gc_mapDir(PAD_BUTTON_DOWN, INPUT_DOWN);
	gc_mapDir(PAD_BUTTON_LEFT, INPUT_LEFT);
	gc_mapDir(PAD_BUTTON_RIGHT, INPUT_RIGHT);
	gc_mapButton(PAD_BUTTON_A, INPUT_A);
	gc_mapButton(PAD_BUTTON_B, INPUT_B);
	gc_mapButton(PAD_BUTTON_X, INPUT_X);
	gc_mapButton(PAD_BUTTON_Y, INPUT_Y);
	gc_mapButton(PAD_TRIGGER_L, INPUT_L);
	gc_mapButton(PAD_TRIGGER_R, INPUT_R);
	gc_mapButton(PAD_TRIGGER_Z, INPUT_SELECT);
	gc_mapButton(PAD_BUTTON_START, INPUT_START);
	for (char i = 0; i < 4; i++) {
		controllerAxis_leftStickX = PAD_StickX(i) << 8;
		controllerAxis_leftStickY = -(PAD_StickY(i) << 8);
		applyStickDeadZoneX();
		applyStickDeadZoneY();
		if (controllerAxis_leftStickX != 0 || controllerAxis_leftStickY != 0) {
			break;
		}
	}
#else
	keyInputs = 0;
	/* Update Key/Button Presses, Mouse/Touch Input, and Window Resizing */
#if !defined(SDL1) && !defined(PSP)
	/* Update Controller Axes (SDL2 only; SDL1 axes are handled later) */
	for (char i = 0; i < 8; i++) {
		controllerAxis_leftStickX = SDL_GameControllerGetAxis(controllers[i], SDL_CONTROLLER_AXIS_LEFTX);
		controllerAxis_leftStickY = SDL_GameControllerGetAxis(controllers[i], SDL_CONTROLLER_AXIS_LEFTY);
		applyStickDeadZoneX();
		applyStickDeadZoneY();
		if (controllerAxis_leftStickX != 0 || controllerAxis_leftStickY != 0) {
			break;
		}
	}
#endif
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
#if defined(PC) && !defined(SDL1)
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
				if (event.key.keysym.sym == SDLK_F11 || event.key.keysym.sym == SDLK_ESCAPE) {
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
				if (event.key.keysym.sym == SDLK_F11 || event.key.keysym.sym == SDLK_ESCAPE) {
					heldKeys &= ~INPUT_FULLSCREEN;
					break;
				}
				break;
#if defined(PC)
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
#if defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#endif
					heldKeys |= INPUT_A;
					break;
				}
#if defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#endif
					heldKeys |= INPUT_B;
					break;
				}
#if defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#endif
					heldKeys |= INPUT_X;
					break;
				}
#if defined(SWITCH)
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
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK) {
					heldKeys |= INPUT_FULLSCREEN;
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
#if defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#endif
					heldKeys &= ~INPUT_A;
					break;
				}
#if defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#endif
					heldKeys &= ~INPUT_B;
					break;
				}
#if defined(SWITCH)
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#else
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#endif
					heldKeys &= ~INPUT_X;
					break;
				}
#if defined(SWITCH)
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
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK) {
					heldKeys &= ~INPUT_FULLSCREEN;
					break;
				}
				break;
//#if !defined(PSP)
//			case SDL_FINGERDOWN:
//				mouseInput_x = (Sint32)(event.tfinger.x * windowWidth);
//				mouseInput_y = (Sint32)(event.tfinger.y * windowHeight);
//				break;
//			case SDL_FINGERMOTION:
//				mouseInput_x = (Sint32)(event.tfinger.x * windowWidth);
//				mouseInput_y = (Sint32)(event.tfinger.y * windowHeight);
//				break;
//			case SDL_FINGERUP:
//				break;
//#endif
			case SDL_CONTROLLERDEVICEADDED: {
				int controllerIndex = event.cdevice.which;
				// Find a free slot
				for (int i = 0; i < 8; i++) {
					if (controllers[i] == nullptr) {
						controllers[i] = SDL_GameControllerOpen(controllerIndex);
						break;
					}
				}
				break;
			}
			case SDL_CONTROLLERDEVICEREMOVED: {
				int controllerIndex = event.cdevice.which;
				for (int i = 0; i < 8; i++) {
					if (controllers[i] && SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controllers[i])) == controllerIndex) {
						SDL_GameControllerClose(controllers[i]);
						controllers[i] = nullptr;
						break;
					}
				}
				break;
			}
			default:
				break;
#else
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
			case SDL_JOYAXISMOTION:
				switch (event.jaxis.axis) {
					case 0:
						controllerAxis_leftStickX = event.jaxis.value;
						applyStickDeadZoneX();
						break;
					case 1:
						controllerAxis_leftStickY = event.jaxis.value;
						applyStickDeadZoneY();
						break;
					default:
						break;
				}
				break;
#endif
		}
	}
#endif
	handleAnalogInput();
	handleHeldKeys(deltaTime);
}