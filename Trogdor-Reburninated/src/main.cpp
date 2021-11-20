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
bool isWindowed = true;

/* Other */
GameManager GM;
SDL_Rect gameScreenRect;

/* General-use Variables */
Sint8 i, j, k;
int int_i, int_j, int_k;
Uint32 uint_i, uint_j, uint_k;
float float_i;

int main(int argv, char** args) {
	SYSTEM_SPECIFIC_OPEN();

	/* Initialize SDL */
	SDL_Init(SDL_INIT_EVERYTHING);

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
#if !defined(SDL1)
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
#if !defined(SDL1) && !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(WII) && !defined(GAMECUBE)
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							uint_i = SDL_GetWindowSurface(window)->w;
							uint_j = SDL_GetWindowSurface(window)->h;
							if ((uint_i / DEFAULT_GAME_WIDTH) < (uint_j / DEFAULT_GAME_HEIGHT)) {
								float_i = (uint_i / DEFAULT_GAME_WIDTH);
							} else {
								float_i = (uint_j / DEFAULT_GAME_HEIGHT);
							}
							if (float_i < 1) {
								SDL_SetWindowSize(window, DEFAULT_GAME_WIDTH, DEFAULT_GAME_HEIGHT);
								SDL_RenderSetScale(renderer, 1, 1);
							} else {
								SDL_SetWindowSize(window, (int)(DEFAULT_GAME_WIDTH * float_i), (int)(DEFAULT_GAME_HEIGHT * float_i));
								SDL_RenderSetScale(renderer, float_i, float_i);
							}
							break;
						case SDL_WINDOWEVENT_MAXIMIZED:
							SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
							break;
						default:
							break;
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
#if !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(WII) && !defined(GAMECUBE)
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
					RENDER_SPRITE(sprite_videlectrix_logo, NULL, &sprite_videlectrix_logo.dstrect);
#else
					RENDER_SPRITE_SCALED(sprite_videlectrix_logo, NULL, &sprite_videlectrix_logo.dstrect);
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
					PLAY_MUSIC_WITHOUT_LOOP(MUSIC_TITLE_SCREEN);
				}
				if (frameState < 192) {
					frameState++;
				} else {
					Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_trogador, 0);
					sceneState = 3;
					frameState = 3; // 3 is intentional
				}
				RENDER_SPRITE(sprite_title_screen, NULL, &sprite_title_screen.dstrect);
				break;
			/* Instructions Screen */
			case 3:
				frameState++;
				if (KEY_PRESSED(INPUT_A)) {
					GM = GameManager(sprite_trogdor, 4);
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
					GM.getPlayerInput();
					if (GM.burnination == 0) {

					} else {
						GM.testBurnHut();
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
#if !defined(SDL1)
				SDL_RenderCopy(renderer, sprite_level_background->texture, NULL, &sprite_level_background->dstrect);
#else
				SDL_BlitSurface(sprite_level_background->surface, NULL, screen, &sprite_level_background->dstrect);
#endif
				RENDER_TEXT(text_4_score, textChars_font_serif_2_red_6);
				RENDER_TEXT(text_4_score_val, textChars_font_serif_red_6);
				RENDER_TEXT(text_4_mans, textChars_font_serif_2_red_6);
				RENDER_TEXT(text_4_mans_val, textChars_font_serif_red_6);
				RENDER_TEXT(text_4_level, textChars_font_serif_2_red_6);
				RENDER_TEXT(text_4_level_val, textChars_font_serif_red_6);
				// render peasantometer/burnination meter (depending on their values)
				if (GM.burnination > 0) {
					RENDER_SPRITE(sprite_burnination_meter_empty);
					RENDER_SPRITE(sprite_burnination_meter_full);
				} else {
					sprite_peasantometer_icon.dstrect.x = sprite_peasantometer_icon_init_x;
					sprite_peasantometer_icon.srcrect.x = sprite_peasantometer_icon.srcrect.w;
					for (i = 0; i < 10; i++) {
						if (GM.peasantometer == i) {
							sprite_peasantometer_icon.srcrect.x = 0;
						}
						RENDER_SPRITE(sprite_peasantometer_icon);
						sprite_peasantometer_icon.dstrect.x += (sprite_peasantometer_icon.dstrect.w * 1.5);
					}
				}
				RENDER_AND_ANIMATE_UPPER_COTTAGES();
				RENDER_SPRITE_ALT(GM.player.sprite);
				RENDER_AND_ANIMATE_LOWER_COTTAGES();
				//DRAW_RECT(GM.player.collision, color_red.r, color_red.g, color_red.b);
				//for (i = 0; i < MAX_NUM_HUTS; i++) {
				//	DRAW_RECT(GM.hutArray[i].collision, color_red.r, color_red.g, color_red.b);
				//}
				if (GM.manually_paused) {
					// Here, the original game renders a black circle around the top-right of the center of the screen...
					// I think it's a mistake? I may add it later, but I'll leave it out for now.
#if !defined(SDL1)
					DRAW_RECT_WITH_ALPHA(gameScreenRect, color_black.r, color_black.g, color_black.b, 0xC8);
#else
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
					SDL_Surface *screen_transparent = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, gameWidth, gameHeight, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
#else
					SDL_Surface *screen_transparent = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, gameWidth, gameHeight, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
#endif
					SDL_FillRect(screen_transparent, NULL, 0xC8000000);
					SDL_BlitSurface(screen_transparent, NULL, screen, &gameScreenRect);
					SDL_FreeSurface(screen_transparent);
#endif
					if ((frameCounter_global - GM.manually_paused) % 10 < 5) {
						RENDER_TEXT(text_6_paused_1, textChars_font_serif_white_6);
						RENDER_TEXT(text_6_paused_2, textChars_font_serif_white_6);
					}
				}
				break;
			///* Nothing? (or maybe Game) */
			//case 5:
			//	break;
			///* Pause Screen (overlayed on Game) */
			//case 6:
			//	break;
			/* Nothing */
			case 7:
				break;
			/* End of Level Animation */
			case 8:
				break;
			/* Level Beaten Screen */
			case 9:
				break;
			/* Game Over Screen */
			case 10:
				break;
			/* Level 4 Interlude */
			case 11:
				break;
			/* Level 8 Interlude */
			case 12:
				break;
			/* Level 12 Interlude */
			case 13:
				break;
			/* Level 16 Interlude */
			case 14:
				break;
			/* Level 20 Interlude */
			case 15:
				break;
			/* Level 24 Interlude */
			case 16:
				break;
			/* Level 30 Interlude */
			case 17:
				break;
			/* Level 34 Interlude */
			case 18:
				break;
			/* Level 38 Interlude */
			case 19:
				break;
			/* Level 42 Interlude */
			case 20:
				break;
			/* Level 46 Interlude */
			case 21:
				break;
			/* Level 50 Interlude */
			case 22:
				break;
			/* Level 100 Interlude (Credits) */
			case 23:
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

#if !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(WII) && !defined(GAMECUBE)
		/* Update Mouse Position */
		mouseInput_x_last = mouseInput_x;
		mouseInput_y_last = mouseInput_y;
#endif

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