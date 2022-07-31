#include "include.h"
#include "config.h"
#include "general.h"
#include "classes.h"
#include "input.h"
#include "main.h"
#include "sound_logic.h"
#include "sprite_objects.h"

/* Timer */
Timer timer_global;
Uint32 deltaTime;

/* Framerate */
Uint32 frameTime;
Uint32 frameCounter_global;

/* Program State */
Sint8 sceneState = 3;
Sint16 frameState = 1;
Uint16 rand_var;
bool isRunning = true;

/* Other */
MenuManager MM;
GameManager GM;
SDL_Rect gameScreenRect;
Uint8 contraArrayKey[10] = { 0, 0, 1, 1, 2, 3, 2, 3, 5, 4 }; // Up Up Down Down Left Right Left Right B A

/* General-use Variables */
Sint8 i, j, k;
int int_i, int_j, int_k;
Uint32 uint_i, uint_j, uint_k;
float float_i;

int main(int argv, char** args) {
	SYSTEM_SPECIFIC_OPEN();

	/* Initialize SDL */
#if defined(SDL1) || defined(PSP)
	if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) != 0) {
#else
	if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER) != 0) {
#endif
#if !defined(SDL1) && !defined(ANDROID)
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
#endif
		return 1;
	}

	LOAD_SAVE_FILE();
	InitializeDisplay();
	gameScreenRect = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
	InitializeTextChars();
	InitializeTextObjects();
	InitializeSound();
	InitializeSprites();
	InitializeController();

	while (isRunning) {
		/* Update Timers */
		timer_global.last = timer_global.now;
		timer_global.now = SDL_GetTicks();
		deltaTime = timer_global.now - timer_global.last;

		/* Update Key/Button Presses, Mouse/Touch Input, and Window Resizing */
#if !defined(SDL1) && !defined(PSP)
		/* Update Controller Axes (SDL2 only; SDL1 axes are handled later) */
		controllerAxis_leftStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
		controllerAxis_leftStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
		controllerAxis_rightStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
		controllerAxis_rightStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
		controllerAxis_LT = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
		controllerAxis_RT = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
			controllerAxis_leftStickX = 0;
		}
		if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
			controllerAxis_leftStickY = 0;
		}
		if ((controllerAxis_rightStickX > -STICK_DEADZONE) && (controllerAxis_rightStickX < STICK_DEADZONE)) {
			controllerAxis_rightStickX = 0;
		}
		if ((controllerAxis_rightStickY > -STICK_DEADZONE) && (controllerAxis_rightStickY < STICK_DEADZONE)) {
			controllerAxis_rightStickY = 0;
		}
		if (controllerAxis_LT < STICK_DEADZONE) {
			controllerAxis_LT = 0;
		}
		if (controllerAxis_RT < STICK_DEADZONE) {
			controllerAxis_RT = 0;
		}
#else
		/* Update Controller Hat Positions (SDL1 only; SDL2 D-Pad buttons are handled later) */
		joystickHat = SDL_JoystickGetHat(joystick, 0);
		if (joystickHat & SDL_HAT_UP) {
			heldKeys |= INPUT_UP;
		} else {
			heldKeys &= ~INPUT_UP;
		}
		if (joystickHat & SDL_HAT_DOWN) {
			heldKeys |= INPUT_DOWN;
		} else {
			heldKeys &= ~INPUT_DOWN;
		}
		if (joystickHat & SDL_HAT_LEFT) {
			heldKeys |= INPUT_LEFT;
		} else {
			heldKeys &= ~INPUT_LEFT;
		}
		if (joystickHat & SDL_HAT_RIGHT) {
			heldKeys |= INPUT_RIGHT;
		} else {
			heldKeys &= ~INPUT_RIGHT;
		}
#endif
		keyInputs = 0;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
#if defined(PC) && !defined(SDL1)
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						if (SDL_GetWindowSurface(window)->w < gameWidth)
							SDL_SetWindowSize(window, gameWidth, SDL_GetWindowSurface(window)->h);
						if (SDL_GetWindowSurface(window)->h < gameHeight)
							SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, gameHeight);
						SET_SCALING();
					}
					break;
#endif
				case SDL_KEYDOWN: // keycodes
					if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
						keyInputs |= INPUT_UP;
						heldKeys |= INPUT_UP;
						break;
					}
					if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
						keyInputs |= INPUT_DOWN;
						heldKeys |= INPUT_DOWN;
						break;
					}
					if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
						keyInputs |= INPUT_LEFT;
						heldKeys |= INPUT_LEFT;
						break;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
						keyInputs |= INPUT_RIGHT;
						heldKeys |= INPUT_RIGHT;
						break;
					}
					if (event.key.keysym.sym == SDLK_z) {
						keyInputs |= INPUT_A;
						heldKeys |= INPUT_A;
						break;
					}
					if (event.key.keysym.sym == SDLK_x) {
						keyInputs |= INPUT_B;
						heldKeys |= INPUT_B;
						break;
					}
					if (event.key.keysym.sym == SDLK_c) {
						keyInputs |= INPUT_X;
						heldKeys |= INPUT_X;
						break;
					}
					if (event.key.keysym.sym == SDLK_v) {
						keyInputs |= INPUT_Y;
						heldKeys |= INPUT_Y;
						break;
					}
					if (event.key.keysym.sym == SDLK_q) {
						keyInputs |= INPUT_L;
						heldKeys |= INPUT_L;
						break;
					}
					if (event.key.keysym.sym == SDLK_e) {
						keyInputs |= INPUT_R;
						heldKeys |= INPUT_R;
						break;
					}
					if (event.key.keysym.sym == SDLK_RETURN) {
						keyInputs |= INPUT_START;
						heldKeys |= INPUT_START;
						break;
					}
					if (event.key.keysym.sym == SDLK_BACKQUOTE) {
						keyInputs |= INPUT_SELECT;
						heldKeys |= INPUT_SELECT;
						break;
					}
					if (event.key.keysym.sym == SDLK_f) {
						keyInputs |= INPUT_FULLSCREEN;
						break;
					}
					break;
				case SDL_KEYUP: // keycodes
					if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
						heldKeys &= ~INPUT_UP;
						break;
					}
					if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
						heldKeys &= ~INPUT_DOWN;
						break;
					}
					if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
						heldKeys &= ~INPUT_LEFT;
						break;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
						heldKeys &= ~INPUT_RIGHT;
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
					if (event.key.keysym.sym == SDLK_BACKQUOTE) {
						heldKeys &= ~INPUT_SELECT;
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
#if !defined(SDL1)
				case SDL_CONTROLLERBUTTONDOWN:
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
						keyInputs |= INPUT_UP;
						heldKeys |= INPUT_UP;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
						keyInputs |= INPUT_DOWN;
						heldKeys |= INPUT_DOWN;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
						keyInputs |= INPUT_LEFT;
						heldKeys |= INPUT_LEFT;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
						keyInputs |= INPUT_RIGHT;
						heldKeys |= INPUT_RIGHT;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#endif
						keyInputs |= INPUT_A;
						heldKeys |= INPUT_A;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#endif
						keyInputs |= INPUT_B;
						heldKeys |= INPUT_B;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#endif
						keyInputs |= INPUT_X;
						heldKeys |= INPUT_X;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
#endif
						keyInputs |= INPUT_Y;
						heldKeys |= INPUT_Y;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
						keyInputs |= INPUT_L;
						heldKeys |= INPUT_L;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
						keyInputs |= INPUT_R;
						heldKeys |= INPUT_R;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
						keyInputs |= INPUT_START;
						heldKeys |= INPUT_START;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
						keyInputs |= INPUT_SELECT;
						heldKeys |= INPUT_SELECT;
						break;
					}
					break;
				case SDL_CONTROLLERBUTTONUP:
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
						heldKeys &= ~INPUT_UP;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
						heldKeys &= ~INPUT_DOWN;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
						heldKeys &= ~INPUT_LEFT;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
						heldKeys &= ~INPUT_RIGHT;
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
				case SDL_FINGERDOWN:
					mouseInput_x = (Sint32)(event.tfinger.x * gameWidth);
					mouseInput_y = (Sint32)(event.tfinger.y * gameHeight);
					break;
				case SDL_FINGERMOTION:
					mouseInput_x = (Sint32)(event.tfinger.x * gameWidth);
					mouseInput_y = (Sint32)(event.tfinger.y * gameHeight);
					break;
				case SDL_FINGERUP:
					break;
				default:
					break;
#else
				case SDL_JOYHATMOTION:
					if (event.jhat.value & SDL_HAT_UP) {
						keyInputs |= INPUT_UP;
						break;
					} else {
						heldKeys &= ~INPUT_UP;
					}
					if (event.jhat.value & SDL_HAT_DOWN) {
						keyInputs |= INPUT_DOWN;
						break;
					} else {
						heldKeys &= ~INPUT_DOWN;
					}
					if (event.jhat.value & SDL_HAT_LEFT) {
						keyInputs |= INPUT_LEFT;
						break;
					} else {
						heldKeys &= ~INPUT_LEFT;
					}
					if (event.jhat.value & SDL_HAT_RIGHT) {
						keyInputs |= INPUT_RIGHT;
						break;
					} else {
						heldKeys &= ~INPUT_RIGHT;
					}
					break;
				case SDL_JOYBUTTONDOWN:
					if (event.jbutton.button == 0) {
						keyInputs |= INPUT_A;
						heldKeys |= INPUT_A;
						break;
					}
					if (event.jbutton.button == 1) {
						keyInputs |= INPUT_B;
						heldKeys |= INPUT_B;
						break;
					}
					if (event.jbutton.button == 2) {
						keyInputs |= INPUT_X;
						heldKeys |= INPUT_X;
						break;
					}
					if (event.jbutton.button == 3) {
						keyInputs |= INPUT_Y;
						heldKeys |= INPUT_Y;
						break;
					}
					if (event.jbutton.button == 4) {
						keyInputs |= INPUT_L;
						heldKeys |= INPUT_L;
						break;
					}
					if (event.jbutton.button == 5) {
						keyInputs |= INPUT_R;
						heldKeys |= INPUT_R;
						break;
					}
					if (event.jbutton.button == 7) {
						keyInputs |= INPUT_START;
						heldKeys |= INPUT_START;
						break;
					}
					if (event.jbutton.button == 6) {
						keyInputs |= INPUT_SELECT;
						heldKeys |= INPUT_SELECT;
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
						heldKeys &= ~INPUT_L;
						break;
					}
					if (event.jbutton.button == 5) {
						heldKeys &= ~INPUT_R;
						break;
					}
					if (event.jbutton.button == 7) {
						heldKeys &= ~INPUT_START;
						break;
					}
					if (event.jbutton.button == 6) {
						heldKeys &= ~INPUT_SELECT;
						break;
					}
					break;
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
						case 2:
							if (event.jaxis.value > STICK_DEADZONE) {
								controllerAxis_LT = event.jaxis.value;
							} else {
								controllerAxis_LT = 0;
							}
							if (event.jaxis.value < -STICK_DEADZONE) {
								controllerAxis_RT = event.jaxis.value;
							} else {
								controllerAxis_RT = 0;
							}
							break;
						case 3:
							controllerAxis_rightStickY = event.jaxis.value;
							if ((controllerAxis_rightStickY > -STICK_DEADZONE) && (controllerAxis_rightStickY < STICK_DEADZONE)) {
								controllerAxis_rightStickY = 0;
							}
							break;
						case 4:
							controllerAxis_rightStickX = event.jaxis.value;
							if ((controllerAxis_rightStickX > -STICK_DEADZONE) && (controllerAxis_rightStickX < STICK_DEADZONE)) {
								controllerAxis_rightStickX = 0;
							}
							break;
						default:
							break;
					}
					break;
#endif
			}
		}

		/* Key Presses (Always Active) */
		if (KEY_PRESSED(INPUT_FULLSCREEN)) {
			SDL_TOGGLE_FULLSCREEN();
		}
		if (KEY_PRESSED(INPUT_R)) {
			SDL_TOGGLE_INTEGER_SCALE();
			PRINT(isIntegerScale);
		}

		/* Clear Screen */
#if !defined(SDL1)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
#else
		SDL_FillRect(screen, NULL, 0x000000);
#endif

		/* Scene states:
		 *  0: Loading Screen
		 *  1: Videlectrix Logo
		 *  2: Title Screen
		 *  3: Instructions Screen
		 *  4: Game
		 *  5: Nothing? (or maybe Game)
		 *  6: Pause Screen (overlayed on Game)
		 *  7: Nothing
		 *  8: End of Level Animation
		 *  9: Level Beaten Screen
		 * 10: Game Over Screen
		 * 11: Level 4 Interlude
		 * 12: Level 8 Interlude
		 * 13: Level 12 Interlude
		 * 14: Level 16 Interlude
		 * 15: Level 20 Interlude
		 * 16: Level 24 Interlude
		 * 17: Level 30 Interlude
		 * 18: Level 34 Interlude
		 * 19: Level 38 Interlude
		 * 20: Level 42 Interlude
		 * 21: Level 46 Interlude
		 * 22: Level 50 Interlude
		 * 23: Level 100 Interlude (Credits)
		 * 24: Nothing? (or maybe blank transition from Credits to High Scores Screen)
		 * 25: High Scores Screen
		 */
		switch (sceneState) {
			/* Loading Screen */
			case 0:
				switch (frameState) {
					case 1:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x = text_0_loading.dstrect.x;
						frameState++;
						break;
					case 2:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['l' - 32].dstrect.w;
						frameState++;
						break;
					case 3:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['o' - 32].dstrect.w;
						frameState++;
						break;
					case 4:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['a' - 32].dstrect.w;
						frameState++;
						break;
					case 5:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['d' - 32].dstrect.w;
						frameState++;
						break;
					case 6:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['i' - 32].dstrect.w;
						frameState++;
						break;
					case 7:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['n' - 32].dstrect.w;
						frameState++;
						break;
					case 8:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['g' - 32].dstrect.w;
						frameState++;
						break;
					case 9:
					case 10:
					case 11:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['.' - 32].dstrect.w;
						frameState++;
						break;
					case 12:
					case 13:
					case 14:
					case 15:
						RENDER_TEXT(text_0_loading, textChars_font_serif_white_14);
						frameState++;
						break;
					case 16:
						frameState++;
						break;
					default:
						sceneState = 1;
						frameState = 18;
						break;
				}
				DRAW_RECT(text_0_loading_censor_rect, color_black.r, color_black.g, color_black.b);
				break;
			/* Videlectrix logo */
			case 1:
				if (frameState < 65) {
#if !defined(SDL1)
					RENDER_SPRITE(sprite_videlectrix_logo);
#else
					RENDER_SPRITE_SCALED(sprite_videlectrix_logo);
#endif
					RENDER_TEXT(text_1_presents, textChars_font_nokia_12);
				}
				if (frameState < 72) {
					frameState++;
				} else {
					sceneState = 2;
					frameState = 73;
				}
				break;
			/* Title Screen */
			case 2:
				if (frameState == 73) {
					Mix_PlayChannel(SFX_CHANNEL_GAME_MUSIC, music_title_screen, 0);
				}
				if (frameState < 192) {
					frameState++;
				} else {
					Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_trogador, 0);
					sceneState = 3;
					frameState = 3; // 3 is intentional
					MM = MenuManager();
				}
				RENDER_SPRITE(sprite_title_screen);
				break;
			/* Instructions Screen */
			case 3:
				frameState++;
				MM.typeStuff();
				if (KEY_PRESSED(INPUT_A)) {
					if (MM.contraActive) {
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_sfx2, 0);
						GM = GameManager(30);
					} else {
						GM = GameManager(3);
					}
					GM.levelInit();
					UPDATE_TEXT(text_4_score_val, to_string(GM.score));
					UPDATE_TEXT(text_4_mans_val, to_string(GM.mans));
					UPDATE_TEXT(text_4_level_val, to_string(GM.level));
					sceneState = 4;
				}
				RENDER_SPRITE(sprite_trogdor_logo);
				RENDER_TEXT(text_3_instructions_1, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_instructions_2, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_instructions_3, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_instructions_4, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_instructions_5, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_programmed, textChars_font_serif_white_6);
				RENDER_TEXT(text_3_designed, textChars_font_serif_white_6);
				if (frameState % 4 < 2) {
					RENDER_TEXT(text_3_click_anywhere_to_start, textChars_font_serif_red_8);
				}
				break;
			/* Game */
			case 4:
				if (!GM.paused && !GM.manually_paused) {
					if (KEY_PRESSED(INPUT_B)) {
						GM.burninationIncreaseTest();
					}
					if (KEY_PRESSED(INPUT_A)) {
						GM.burninationDecreaseTest();
					}

					GM.player.invinceCheck();
					GM.popArchers();
					GM.updateArchersAndArrows();
					GM.getPlayerInput();
					GM.updateKnight();
					if (GM.testWon()) {
						GM.updateScore(min((20 + ((GM.level / 5) + 1) * 5), 200));
						GM.clearArrows();
						sceneState = 8;
						frameState = 256;
					}
					if (!GM.burnination) {
						GM.popPeasants();
						GM.peasantEatTest();
						GM.peasantTimerClick();
						GM.testKnightHit();
						GM.arrowHitEventHandler();
					} else {
						GM.updateBurnmeter();
						GM.testBurnHut();
						GM.testBurnPeasant();
						GM.peasantTimerClick();
					}
				} else {
					if (GM.manually_paused) {
						if (KEY_HELD(INPUT_START)) {
							GM.startDown = true;
						}
						if (GM.startDown && !KEY_HELD(INPUT_START)) {
							GM.startDown = false;
							GM.manually_paused = 0;
						}
					}
				}
				if (!GM.manually_paused) {
					if (GM.dm_frameState >= 3) {
						GM.dm_updateFrameState();
					}
					if (GM.b_frameState >= 1) {
						GM.b_updateFrameState();
					}
					if (GM.player.frameState >= 19) {
						GM.player.updateFrameState();
					}
				}
				if (GM.gameOver) {
					sceneState = 5;
					frameState = 321;
					// no break; it should continue directly to the next state on the current frame
				} else {
					if (GM.kick_frameState > 0) {
						GM.kick_updateFrameState();
					}
					// render everything
					RENDER_BACKGROUND();
					RENDER_TOP_BAR();
					//RENDER_AND_ANIMATE_UPPER_COTTAGES();
					RENDER_AND_ANIMATE_COTTAGES();
					RENDER_KNIGHTS();
					RENDER_PEASANTS();
					RENDER_TROGDOR();
					//RENDER_AND_ANIMATE_LOWER_COTTAGES();
					if (GM.burnination > 0) {
						RENDER_SPRITE_USING_RECTS(sprite_trogdor_fire, GM.player.fire_srcrect, GM.player.fire_dstrect);
					}
					RENDER_ARCHERS();
					RENDER_ARROWS();
					if (GM.dm_visible) {
						RENDER_SPRITE_USING_RECTS(sprite_death_message, GM.dm_srcrect, GM.dm_dstrect);
					} else if (GM.b_visible) {
						RENDER_SPRITE_USING_RECTS(sprite_burninate_fire, GM.bf_srcrect, GM.bf_dstrect);
						RENDER_SPRITE_USING_RECTS(sprite_burninate_text, GM.bt_srcrect, GM.bt_dstrect);
					}
					if (GM.manually_paused) {
						// Here, the original game renders a black circle around the top-right of the center of the screen...
						// I think it's a mistake? I may add it later, but I'll leave it out for now.
						RENDER_TRANSPARENT_FOREGROUND();
						if ((frameCounter_global - GM.manually_paused) % 10 < 5) {
							RENDER_TEXT(text_6_paused_1, textChars_font_serif_white_6);
							RENDER_TEXT(text_6_paused_2, textChars_font_serif_white_6);
						}
					}
					if (GM.inTreasureHut) {
						GM.paused = true;
						GM.treasureHutFound = true;
						GM.player.dstrect.x = 211;
						GM.player.dstrect.y = 118;
						GM.treasureHut_timer = 110;
						GM.set_level_background(5);
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_sfx2, 0);
						sceneState = 6;
					}
					break;
				}
			/* Game Over Screen */
			case 5:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				// TODO: draw Trogdor, "IT'S OVER!", and whatever else needs to be handled for this screen
				switch (frameState) {
					case 321:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_gameover, 0);
						if (GM.score < 2000) {
							if (GM.arched) {
								if ((rand() % 100) < 50) {
									Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sbarchend, 0);
								}
							} else if ((GM.score > 1000) && ((rand() % 100) < 70)) {
								Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sbscore, 0);
							} else if ((rand() % 100) < 70) {
								Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sbgameover, 0);
							}
						} else {
							Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sbsecret, 0);
						}
						GM.setMans(0);
						break;
					default:
						break;
				}
				// TODO: high score-related things here
				if (KEY_PRESSED(INPUT_START)) { // TODO: placeholder; remove this later
					sceneState = 3;
				}
				if (sceneState == 5) {
					frameState++;
				}
				break;
			/* Game (Treasure Hut) */
			case 6:
				if (GM.manually_paused) {
					if (KEY_HELD(INPUT_START)) {
						GM.startDown = true;
					}
					if (GM.startDown && !KEY_HELD(INPUT_START)) {
						GM.startDown = false;
						GM.manually_paused = 0;
					}
				} else {
					GM.handle_treasure_hut();
					if (GM.dm_frameState >= 3) {
						GM.dm_updateFrameState();
					}
					if (GM.b_frameState >= 1) {
						GM.b_updateFrameState();
					}
					if (GM.player.frameState >= 19) {
						GM.player.updateFrameState();
					}
				}
				if (GM.gameOver) {
					sceneState = 5;
					frameState = 321;
					break;
				} else {
					if (GM.kick_frameState > 0) {
						GM.kick_updateFrameState();
					}
					// render everything
					RENDER_BACKGROUND();
					RENDER_TOP_BAR();
					RENDER_LOOT();
					RENDER_TROGDOR();
					if (GM.burnination > 0) {
						RENDER_SPRITE_USING_RECTS(sprite_trogdor_fire, GM.player.fire_srcrect, GM.player.fire_dstrect);
					}
					if (GM.dm_visible) {
						RENDER_SPRITE_USING_RECTS(sprite_death_message, GM.dm_srcrect, GM.dm_dstrect);
					} else if (GM.b_visible) {
						RENDER_SPRITE_USING_RECTS(sprite_burninate_fire, GM.bf_srcrect, GM.bf_dstrect);
						RENDER_SPRITE_USING_RECTS(sprite_burninate_text, GM.bt_srcrect, GM.bt_dstrect);
					}
					if (GM.manually_paused) {
						// Here, the original game renders a black circle around the top-right of the center of the screen...
						// I think it's a mistake? I may add it later, but I'll leave it out for now.
						RENDER_TRANSPARENT_FOREGROUND();
						if ((frameCounter_global - GM.manually_paused) % 10 < 5) {
							RENDER_TEXT(text_6_paused_1, textChars_font_serif_white_6);
							RENDER_TEXT(text_6_paused_2, textChars_font_serif_white_6);
						}
					}
					if (!GM.inTreasureHut) {
						GM.paused = false;
						GM.player.dstrect.x = GM.storex;
						GM.player.dstrect.y = GM.storey;
						GM.set_level_background(levels[GM.levelIndex][0]);
						sceneState = 4;
					}
					break;
				}
			case 7:
				break;
			/* End of Level Animation */
			case 8:
				RENDER_BACKGROUND();
				RENDER_TOP_BAR();
				RENDER_AND_ANIMATE_COTTAGES();
				if (((frameState - 1) / 2) % 2 == 0) {
					RENDER_SPRITE(sprite_end_of_level_flash);
				}
				switch (frameState) {
					case 257:
						if ((rand() % 100) < 10) {
							if ((rand() % 100) < 50) {
								Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sblevelbeat, 0);
							} else {
								Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sb1, 0);
							}
						}
						break;
					case 265:
						if ((rand() % 100) < 10) {
							Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sbbest, 0);
						}
						break;
					case 276:
						sceneState = 9;
						frameState = 277;
						break;
					default:
						break;
				}
				if (sceneState == 8) {
					frameState++;
				}
				RENDER_SPRITE(sprite_end_of_level_trogdor);
				break;
			/* Level Beaten Screen */
			case 9:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_9_nice_work, textChars_font_serif_white_10);
				// TODO: draw Trogdor, "LEVEL BEATEN!", smoke, and level fire
				switch (frameState) {
					case 277:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_burninate, 0);
						break;
					case 285:
						GM.updateLevel(1);
						break;
					case 316:
						switch (GM.level) {
							case 5:
								sceneState = 11;
								frameState = 420;
								break;
							case 9:
								sceneState = 12;
								frameState = 493;
								break;
							case 13:
								sceneState = 13;
								frameState = 567;
								break;
							case 17:
								sceneState = 14;
								frameState = 641;
								break;
							case 21:
								sceneState = 15;
								frameState = 710;
								break;
							case 25:
								sceneState = 16;
								frameState = 780;
								break;
							case 31:
								sceneState = 17;
								frameState = 853;
								break;
							case 35:
								sceneState = 18;
								frameState = 927;
								break;
							case 39:
								sceneState = 19;
								frameState = 1000;
								break;
							case 43:
								sceneState = 20;
								frameState = 1076;
								break;
							case 47:
								sceneState = 21;
								frameState = 1153;
								break;
							case 51:
								sceneState = 22;
								frameState = 1226;
								break;
							case 101:
								sceneState = 23;
								frameState = 1337;
								break;
							default:
								GM.levelInit();
								sceneState = 4;
								break;
						}
						break;
					default:
						break;
				}
				if (sceneState == 9) {
					frameState++;
				}
				break;
			/* Nothing */
			case 10:
				break;
			/* Level 4 Interlude */
			case 11:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_11_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 420:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 492:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 11) {
					frameState++;
				}
				break;
			/* Level 8 Interlude */
			case 12:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_12_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 493:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 566:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 12) {
					frameState++;
				}
				break;
			/* Level 12 Interlude */
			case 13:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_13_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 567:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 640:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 13) {
					frameState++;
				}
				break;
			/* Level 16 Interlude */
			case 14:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_14_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 641:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 709:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 14) {
					frameState++;
				}
				break;
			/* Level 20 Interlude */
			case 15:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_15_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 710:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 779:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 15) {
					frameState++;
				}
				break;
			/* Level 24 Interlude */
			case 16:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_16_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 780:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 850:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 16) {
					frameState++;
				}
				break;
			/* Level 30 Interlude */
			case 17:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_17_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 853:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 924:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 17) {
					frameState++;
				}
				break;
			/* Level 34 Interlude */
			case 18:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_18_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 927:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 997:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 18) {
					frameState++;
				}
				break;
			/* Level 38 Interlude */
			case 19:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_19_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 1000:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 1071:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 19) {
					frameState++;
				}
				break;
			/* Level 42 Interlude */
			case 20:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_20_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 1076:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 1147:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 20) {
					frameState++;
				}
				break;
			/* Level 46 Interlude */
			case 21:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_21_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 1153:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 1222:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 21) {
					frameState++;
				}
				break;
			/* Level 50 Interlude */
			case 22:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				RENDER_TEXT(text_22_cutscene, textChars_font_serif_white_9);
				// TODO: implement cutscene
				switch (frameState) {
					case 1226:
						Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_cutscene, 0);
						break;
					case 1334:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 22) {
					frameState++;
				}
				break;
			/* Level 100 Interlude (Credits) */
			case 23:
				RENDER_TOP_BAR();
				DRAW_RECT(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				// TODO: implement cutscene
				break;
			/* Nothing? (or maybe blank transition from Credits to High Scores Screen) */
			case 24:
				break;
			/* High Scores Screen */
			case 25:
				break;
			default:
				break;
		}

#if defined(PC)
		/* Update Mouse Position */
		mouseInput_x_last = mouseInput_x;
		mouseInput_y_last = mouseInput_y;
#endif

		/* Draw Black Rectangles */
		RENDER_BORDER_RECTS();

		/* Update Screen */
#if !defined(SDL1)
		SDL_RenderPresent(renderer);
#else
		SDL_Flip(screen);
#endif
		
		/* Cap Framerate */
		frameCounter_global++;
		frameTime = SDL_GetTicks() - (Uint32)timer_global.now;
		if (frameTime < (1000 / FRAME_RATE)) {
			SDL_Delay((1000 / FRAME_RATE) - frameTime);
		}
	}

	/* Destroy all SDL objects and properly close program */
	DestroyAll();

	return 0;
}