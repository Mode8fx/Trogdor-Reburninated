#include "main.h"
#include "on_open_and_close.h"
#include "cutscenes.h"
#include "input.h"
#include "media_objects_init.h"
#include "level_data.h"

bool renderOverlay;
#if defined(THREEDS)
bool showOverlay = false;
#else
bool showOverlay = true;
#endif
bool menuMusicHasStarted = false;
Sint8 lastMusicPlayed = -1;

int main(int argv, char** args) {
	isRunning = true;
	g_sceneState = 0;
	g_frameState.set(1);
	systemSpecificOpen();

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
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX)
	SDL_ShowCursor(SDL_DISABLE);
#endif
	InitializeController();

#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX))
	try {
#endif
	loadGameState_partial();
	scalingType = gameState.settings_cosmetic.scaling;
	InitializeDisplay();
	loadGameState();

#if defined(ANDROID)
	/* Initialize SDL_ttf, fonts, text objects, and sprite objects (already done for other systems in InitializeDisplay() via setScaling() */
	InitializeFontsAndText();
	InitializeSpritesPart1();
	InitializeSpritesPart2();
#endif

	InitializeCutsceneObjects();

	/* Initialize Loading Screen rect */
	text_0_loading_censor_rect = { text_0_loading.dstrect.x, text_0_loading.dstrect.y,
		(Uint16)text_0_loading.dstrect.w, (Uint16)text_0_loading.dstrect.h };

	while (isRunning) {
		/* Update Timers */
		timer_global.last = timer_global.now;
		timer_global.now = SDL_GetTicks();
		deltaTime = (Uint32)(timer_global.now - timer_global.last);
		if (heldDirs > 0) {
			timer_buttonHold += deltaTime;
		} else {
			timer_buttonHold = 0;
			timer_buttonHold_repeater = 0;
		}
		handlePlayerInput();
		if (keyPressed(INPUT_FULLSCREEN)) {
			SDL_toggleFullscreen();
		}
#if !defined(THREEDS)
		if (keyPressed(INPUT_Y) && (g_sceneState == 2 || g_sceneState == 3 || GM.manually_paused)) {
			do {
				scalingType = (scalingType + 1) % 4;
				menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
			} while (MENU_SCALING->choiceIsAllowed[scalingType] == false);
			windowSizeChanged = true;
		}
#endif
#if defined(WII)
		if (keyPressed(INPUT_R) && (g_sceneState == 2 || g_sceneState == 3 || GM.manually_paused)) {
#else
		if (keyPressed(INPUT_X) && (g_sceneState == 2 || g_sceneState == 3 || GM.manually_paused)) {
#endif
			showOverlay = !showOverlay;
		}
		/* Handle Window Size Changes */
		if (windowSizeChanged) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX)) && !defined(SDL1)
			if (scalingType % 2 == 1 && SDL_GetWindowSurface(window)->w >= appWidth && SDL_GetWindowSurface(window)->h >= appHeight) {
				if (SDL_GetWindowSurface(window)->w < gameWidth)
					SDL_SetWindowSize(window, gameWidth, SDL_GetWindowSurface(window)->h);
				if (SDL_GetWindowSurface(window)->h < gameHeight)
					SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, gameHeight);
			} else {
				if (SDL_GetWindowSurface(window)->w < appWidth)
					SDL_SetWindowSize(window, appWidth, SDL_GetWindowSurface(window)->h);
				if (SDL_GetWindowSurface(window)->h < appHeight)
					SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, appHeight);
			}
			// If you resize the window to within 6% of an integer ratio, snap to that ratio
			if (scalingType == 0) {
				snapWindow_x(0.06, appWidth);
				snapWindow_y(0.06, appHeight);
			} else if (scalingType == 1) {
				snapWindow_x(0.06, gameWidth);
				snapWindow_y(0.06, gameHeight);
			}
#endif
			setScaling();
			updateText(&text_4_score_val, to_string(GM.score));
			updateText(&text_4_mans_val, to_string(GM.mans));
			updateText(&text_4_level_val, to_string(GM.level));
			menu_main.updateOptionPositions();
			menu_difficulty.updateOptionPositions();
			menu_cosmetic.updateOptionPositions();
			menu_other.updateOptionPositions();
			menu_cheats.updateOptionPositions();
			menu_quit.updateOptionPositions();
			if (gameHiResMult < 2) {
				MM.maxPageNum = MAX_PAGE_NUM_LOWRES;
				updateText(&text_3_page, "("+to_string(MM.page)+"/"+to_string(MM.maxPageNum)+")");
			} else {
				MM.maxPageNum = MAX_PAGE_NUM_HIRES;
				if (MM.page > MM.maxPageNum) MM.page = MM.maxPageNum;
				updateText(&text_3_page, "("+to_string(MM.page)+"/"+to_string(MM.maxPageNum)+")");
			}
			if (GM.initialized) {
				GM.resetAllSrcRects();
#if defined(SDL1)
				if (GM.manually_paused) {
					SDL_FreeSurface(transparentScreen);
					sdl1_createTransparentScreen();
				}
#endif
			}
			windowSizeChanged = false;
		}

		/* Clear Screen */
#if !defined(SDL1)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
#else
		SDL_FillRect(windowScreen, NULL, 0x000000);
#endif

		/* Scene states:
		 *  0: Loading Screen
		 *  1: Videlectrix Logo
		 *  2: Title Screen
		 *  3: Instructions Screen
		 *  4: Game
		 *  5: Game Over Screen
		 *  6: Game (Treasure Hut)
		 *  7: Nothing
		 *  8: End of Level Animation
		 *  9: Level Beaten Screen
		 * 10: Nothing
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
		switch (g_sceneState) {
			/* Loading Screen */
			case 0:
				if (g_frameState.atStartOfFrame) {
					switch (g_frameState.frame) {
						case 1:
							text_0_loading_censor_rect.x = text_0_loading.dstrect.x;
							break;
						case 2:
							text_0_loading_censor_rect.x += font_serif_white_14.textChars['l' - 32].dstrect.w;
							break;
						case 3:
							text_0_loading_censor_rect.x += font_serif_white_14.textChars['o' - 32].dstrect.w;
							break;
						case 4:
							text_0_loading_censor_rect.x += font_serif_white_14.textChars['a' - 32].dstrect.w;
							break;
						case 5:
							text_0_loading_censor_rect.x += font_serif_white_14.textChars['d' - 32].dstrect.w;
							break;
						case 6:
							text_0_loading_censor_rect.x += font_serif_white_14.textChars['i' - 32].dstrect.w;
							break;
						case 7:
							text_0_loading_censor_rect.x += font_serif_white_14.textChars['n' - 32].dstrect.w;
							break;
						case 8:
							text_0_loading_censor_rect.x += font_serif_white_14.textChars['g' - 32].dstrect.w;
							break;
						case 9:
							text_0_loading_censor_rect.x += font_serif_white_14.textChars['.' - 32].dstrect.w;
							break;
						case 10:
							InitializeSound();
							text_0_loading_censor_rect.x += font_serif_white_14.textChars['.' - 32].dstrect.w;
							break;
						case 11:
							InitializeMusic();
							text_0_loading_censor_rect.x += font_serif_white_14.textChars['.' - 32].dstrect.w;
							break;
						case 13:
							InitializeSFX();
							break;
						default:
							break;
					}
				}
				if (g_frameState.frame <= 16) {
					if (g_frameState.frame <= 15) {
						renderText(text_0_loading, font_serif_white_14);
					}
					g_frameState.increment();
				} else {
					g_sceneState = 1;
					g_frameState.set(18);
				}
				drawRect_gameTextScreen(text_0_loading_censor_rect, color_black.r, color_black.g, color_black.b);
				break;
			/* Videlectrix logo */
			case 1:
				if (g_frameState.frame < 65) {
					sprite_videlectrix_logo_ins.renderSprite_app();
					renderText(text_1_presents_1, font_nokia_12);
					renderText(text_1_presents_2, font_nokia_12);
				}
				if (g_frameState.frame < 72) {
					g_frameState.increment();
				} else {
					g_sceneState = 2;
					g_frameState.set(73);
				}
				if (keyPressed(INPUT_START)) {
					loadAndPlaySound(SFX_TROGADOR);
					g_sceneState = 3;
					g_frameState.set(3); // 3 is intentional
					MM = MenuManager();
				}
				break;
			/* Title Screen */
			case 2:
				if (g_frameState.startingFrame(73)) {
					playMusic(MUSIC_TITLE_SCREEN, false, DEFAULT_VOLUME_GAME);
					renderOverlay = true;
				}
				if (g_frameState.frame >= 192 || keyPressed(INPUT_START)) {
					if (keyPressed(INPUT_START)) stopMusic();
					loadAndPlaySound(SFX_TROGADOR);
					g_sceneState = 3;
					g_frameState.set(3); // 3 is intentional
					MM = MenuManager();
				} else {
					g_frameState.increment();
				}
				sprite_title_screen_ins.renderSprite_game();
				break;
			/* Instructions Screen */
			case 3:
				g_frameState.increment();
				renderOverlay = true;
				MM.typeStuff();
				MM.handlePageChange();
				if (MM.page == 1) {
					if (keyPressed(INPUT_START)) {
						if (gameState.autosave.mans >= 0) {
							MM.continueHighlighted = true;
							MM.cursor.dstrect.x = (int)((double)text_3_continue_1.dstrect.x / gameHiResMult) - (MM.cursor.dstrect.w * 2);
							MM.cursor.dstrect.y = (int)(text_3_continue_1.dstrect.y / gameHiResMult);
							g_sceneState = 3001;
						} else {
							MM.continueHighlighted = false;
							GM = GameManager(MM);
							GM.levelInit();
							updateText(&text_4_score_val, to_string(GM.score));
							updateText(&text_4_mans_val, to_string(GM.mans));
							updateText(&text_4_level_val, to_string(GM.level));
							InitializeCutsceneObjects_trogdor(); // needed in case Big Head Mode was toggled
							g_sceneState = 4;
						}
					} else if (keyPressed(INPUT_SELECT)) {
						menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
						menu_main.openMenu();
						if (!menuMusicHasStarted) {
							playMusic(MUSIC_MENU, true, DEFAULT_VOLUME_MUSIC);
							menuMusicHasStarted = true;
						} else {
							resumeMusic();
						}
						g_sceneState = 301;
					}
				}
				sprite_trogdor_logo_ins.renderSprite_game();
				if (gameHiResMult < 2) {
					switch (MM.page) {
						case 1:
							renderText(text_3_instructions_1, font_serif_white_6_mult);
							renderText(text_3_instructions_2, font_serif_white_6_mult);
							renderText(text_3_instructions_2a, font_serif_white_6_mult);
							renderText(text_3_instructions_3, font_serif_white_6_mult);
							renderText(text_3_instructions_4, font_serif_white_6_mult);
							//renderText(text_3_instructions_5, font_serif_white_6_mult);
							if (g_frameState.frame % 4 < 2) {
								renderText(text_3_click_anywhere_to_start, font_serif_red_8_mult);
							}
							renderText(text_3_quit, font_serif_white_6_mult);
							break;
						case 2:
							renderText(text_3_hints_1, font_serif_red_6_mult);
							renderText(text_3_hints_2, font_serif_white_6_mult);
							renderText(text_3_hints_2a, font_serif_white_6_mult);
							renderText(text_3_hints_3, font_serif_white_6_mult);
							renderText(text_3_hints_3a, font_serif_white_6_mult);
							renderText(text_3_hints_4, font_serif_white_6_mult);
							renderText(text_3_hints_4a, font_serif_white_6_mult);
							break;
						case 3:
							renderText(text_3_hints_1, font_serif_red_6_mult);
							renderText(text_3_hints_5, font_serif_white_6_mult);
							renderText(text_3_hints_5a, font_serif_white_6_mult);
							renderText(text_3_hints_6, font_serif_red_6_mult);
							renderText(text_3_hints_7, font_serif_red_6_mult);
							break;
						case 4:
							renderText(text_3_controls_1, font_serif_red_6_mult);
							renderText(text_3_controls_2, font_serif_red_6_mult);
							renderText(text_3_controls_3, font_serif_white_6_mult);
							renderText(text_3_controls_4, font_serif_white_6_mult);
							renderText(text_3_controls_5, font_serif_white_6_mult);
							renderText(text_3_controls_6, font_serif_white_6_mult);
							break;
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX))
						case 5:
							renderText(text_3_keyboard_1, font_serif_red_6_mult);
							renderText(text_3_keyboard_2, font_serif_white_6_mult);
							renderText(text_3_keyboard_3, font_serif_white_6_mult);
							renderText(text_3_keyboard_4, font_serif_white_6_mult);
							renderText(text_3_keyboard_5, font_serif_white_6_mult);
							break;
#endif
						default:
							break;
					}
				} else {
					switch (MM.page) {
						case 1:
							renderText(text_3_instructions_1, font_serif_white_6_mult);
							renderText(text_3_instructions_2, font_serif_white_6_mult);
							renderText(text_3_instructions_3, font_serif_white_6_mult);
							renderText(text_3_instructions_4, font_serif_white_6_mult);
							renderText(text_3_instructions_5, font_serif_white_6_mult);
							if (g_frameState.frame % 4 < 2) {
								renderText(text_3_click_anywhere_to_start, font_serif_red_8_mult);
							}
							renderText(text_3_quit, font_serif_white_6_mult);
							break;
						case 2:
							renderText(text_3_hints_1, font_serif_red_6_mult);
							renderText(text_3_hints_2, font_serif_white_6_mult);
							renderText(text_3_hints_3, font_serif_white_6_mult);
							renderText(text_3_hints_4, font_serif_white_6_mult);
							renderText(text_3_hints_5, font_serif_white_6_mult);
							renderText(text_3_hints_6, font_serif_red_6_mult);
							renderText(text_3_hints_7, font_serif_red_6_mult);
							break;
						case 3:
							renderText(text_3_controls_1, font_serif_red_6_mult);
							renderText(text_3_controls_2, font_serif_red_6_mult);
							renderText(text_3_controls_3, font_serif_white_6_mult);
							renderText(text_3_controls_4, font_serif_white_6_mult);
							renderText(text_3_controls_5, font_serif_white_6_mult);
							renderText(text_3_controls_6, font_serif_white_6_mult);
							break;
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX))
						case 4:
							renderText(text_3_keyboard_1, font_serif_red_6_mult);
							renderText(text_3_keyboard_2, font_serif_white_6_mult);
							renderText(text_3_keyboard_3, font_serif_white_6_mult);
							renderText(text_3_keyboard_4, font_serif_white_6_mult);
							renderText(text_3_keyboard_5, font_serif_white_6_mult);
							break;
#endif
						default:
							break;
					}
				}
				renderText(text_3_page, font_serif_white_6_mult);
				break;
			/* Continue Screen */
				case 3001:
					g_frameState.increment();
					if (keyPressed(INPUT_B) || keyPressed(INPUT_SELECT)) {
						g_sceneState = 3;
					} else if (keyPressed(INPUT_UP) || keyPressed(INPUT_DOWN)) {
						MM.continueHighlighted = !MM.continueHighlighted;
						if (MM.continueHighlighted) {
							MM.cursor.dstrect.y = (int)(text_3_continue_1.dstrect.y / gameHiResMult);
						} else {
							MM.cursor.dstrect.y = (int)(text_3_continue_2.dstrect.y / gameHiResMult);
						}
					} else if (keyPressed(INPUT_A) || keyPressed(INPUT_START)) {
						GM = GameManager(MM);
						GM.levelInit();
						updateText(&text_4_score_val, to_string(GM.score));
						updateText(&text_4_mans_val, to_string(GM.mans));
						updateText(&text_4_level_val, to_string(GM.level));
						InitializeCutsceneObjects_trogdor(); // needed in case Big Head Mode was toggled
						g_sceneState = 4;
					}
					sprite_trogdor_logo_ins.renderSprite_game();
					renderText(text_3_continue_1, font_serif_white_8_mult);
					renderText(text_3_continue_2, font_serif_white_8_mult);
					MM.cursor.renderSprite_game();
					break;
			/* Options Menu */
			case 301:
				g_frameState.increment();
				renderOverlay = false;
				sprite_menu_background_ins.renderSprite_menu();
				menu_main.renderMenu();
				switch (menu_main.handleInput(0)) {
					case MENU_DIFFICULTY_INDEX:
						menu_difficulty.openMenu();
						g_sceneState = 302;
						break;
					case MENU_COSMETIC_INDEX:
						menu_cosmetic.openMenu();
						g_sceneState = 303;
						break;
					case MENU_OTHER_INDEX:
						menu_other.openMenu();
						g_sceneState = 304;
						break;
					case MENU_CHEATS_INDEX:
						menu_cheats.openMenu();
						g_sceneState = 305;
						break;
					case MENU_RESET_SETTINGS_INDEX:
						menu_difficulty.setOptionChoice(MENU_PRESET_INDEX, MENU_PRESET->index_init);
						menu_difficulty.setOptionChoice(MENU_EXTRA_LIVES_INDEX, MENU_EXTRA_LIVES->index_init);
						menu_difficulty.setOptionChoice(MENU_LIVES_INTERVAL_INDEX, MENU_LIVES_INTERVAL->index_init);
						menu_difficulty.setOptionChoice(MENU_PEASANT_PENALTY_INDEX, MENU_PEASANT_PENALTY->index_init);
						menu_difficulty.setOptionChoice(MENU_KNIGHT_SPEED_INDEX, MENU_KNIGHT_SPEED->index_init);
						menu_difficulty.setOptionChoice(MENU_ARROW_SPEED_INDEX, MENU_ARROW_SPEED->index_init);
						menu_difficulty.setOptionChoice(MENU_ARCHER_FREQ_INDEX, MENU_ARCHER_FREQ->index_init);
						menu_difficulty.setOptionChoice(MENU_TREASURE_HUTS_INDEX, MENU_TREASURE_HUTS->index_init);
						menu_cosmetic.setOptionChoice(MENU_FRAME_RATE_INDEX, MENU_FRAME_RATE->index_init);
						updateFrameRate();
						menu_cosmetic.setOptionChoice(MENU_MUSIC_INDEX, MENU_MUSIC->index_init);
						menu_cosmetic.setOptionChoice(MENU_COMMENT_FREQ_INDEX, MENU_COMMENT_FREQ->index_init);
						menu_cosmetic.setOptionChoice(MENU_BIG_HEAD_MODE_INDEX, MENU_BIG_HEAD_MODE->index_init);
						//menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, MENU_SCALING->index_init);
						menu_other.setOptionChoice(MENU_STARTING_LEVEL_INDEX, MENU_STARTING_LEVEL->index_init);
						menu_other.setOptionChoice(MENU_SHUFFLE_LEVELS_INDEX, MENU_SHUFFLE_LEVELS->index_init);
						menu_other.setOptionChoice(MENU_KNIGHT_MOVEMENT_INDEX, MENU_KNIGHT_MOVEMENT->index_init);
						menu_other.setOptionChoice(MENU_RESPAWN_BEHAVIOR_INDEX, MENU_RESPAWN_BEHAVIOR->index_init);
						menu_other.setOptionChoice(MENU_LEVEL_TRAN_INDEX, MENU_LEVEL_TRAN->index_init);
						menu_cheats.setOptionChoice(MENU_INF_LIVES_INDEX, MENU_INF_LIVES->index_init);
						menu_cheats.setOptionChoice(MENU_SPEEDY_MODE_INDEX, MENU_SPEEDY_MODE->index_init);
						menu_cheats.setOptionChoice(MENU_NOCLIP_INDEX, MENU_NOCLIP->index_init);
						menu_cheats.setOptionChoice(MENU_DEBUG_MODE_INDEX, MENU_DEBUG_MODE->index_init);
						loadAndPlaySound(SFX_SBDOOJ_SHORT);
						break;
					case MENU_HIGHSCORES_INDEX:
						menu_highscores_1.openNotebook();
						menu_highscores_2.openNotebook();
						menu_highscores_3.openNotebook();
						updateHighScores();
						g_sceneState = 306;
						break;
#if defined(WII)
					case MENU_GBA_DEMO_INDEX:
						menu_gba_demo.openNotebook();
						g_sceneState = 307;
						break;
#endif
					case MENU_SOUND_INDEX:
						menu_sound.openMenu();
						if (lastMusicPlayed == -1) {
							stopMusic();
						}
						g_sceneState = 308;
						break;
					case MENU_CREDITS_INDEX:
						menu_credits.openNotebook();
						g_sceneState = 309;
						break;
					case MENU_QUIT_INDEX: // Quit Game
						menu_quit.openMenu();
						j = (rand() % 7);
						QUIT_BACK->setDescriptionToIndex(j);
						QUIT_CONFIRM->setDescriptionToIndex(j);
						menu_quit.updateOptionPositions();
						g_sceneState = 310;
						break;
					case -1: // Press B/Select
						g_sceneState = 3;
						pauseMusic();
						saveGameState_settings();
						MM = MenuManager();
						break;
					default:
						break;
				}
				break;
			/* Difficulty Settings Menu */
			case 302:
				g_frameState.increment();
				sprite_menu_background_ins.renderSprite_menu();
				menu_difficulty.renderMenu();
				switch (menu_difficulty.handleInput(1)) {
					case -1: // Press B/Select
						menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
						g_sceneState = 301;
						break;
					default:
						break;
				}
				break;
			/* Cosmetic Settings Menu */
			case 303:
				g_frameState.increment();
				sprite_menu_background_ins.renderSprite_menu();
				menu_cosmetic.renderMenu();
				switch (menu_cosmetic.handleInput(0)) {
#if !defined(THREEDS)
					case MENU_SCALING_INDEX:
						scalingType = MENU_SCALING->index;
						windowSizeChanged = true;
						break;
#endif
					case -1: // Press B/Select
						menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
						updateFrameRate();
						g_sceneState = 301;
						break;
					default:
						break;
				}
				break;
			/* Other Settings Menu */
			case 304:
				g_frameState.increment();
				sprite_menu_background_ins.renderSprite_menu();
				menu_other.renderMenu();
				switch (menu_other.handleInput(0)) {
					case -1: // Press B/Select
						menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
						g_sceneState = 301;
						break;
					default:
						break;
				}
				break;
			/* Cheats Menu */
			case 305:
				g_frameState.increment();
				sprite_menu_background_ins.renderSprite_menu();
				menu_cheats.renderMenu();
				switch (menu_cheats.handleInput(0)) {
					case -1: // Press B/Select
						menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
						g_sceneState = 301;
						break;
					default:
						break;
				}
				break;
			/* High Scores Screen */
			case 306:
				g_frameState.increment();
				sprite_menu_background_ins.renderSprite_menu();
				menu_highscores_1.renderNotebook();
				menu_highscores_2.renderNotebook();
				menu_highscores_3.renderNotebook();
				switch (menu_highscores_1.handleInput()) {
					case -1: // Press B/Select
						menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
						g_sceneState = 301;
						break;
					default:
						break;
				}
				break;
#if defined(WII)
			/* Trogba Demo Screen */
			case 307:
				g_frameState.increment();
				sprite_menu_background_ins.renderSprite_menu();
				menu_gba_demo.renderNotebook();
				switch (menu_gba_demo.index) {
					case 0:
						if (keyPressed(INPUT_A)) {
							prepare_rom();
							menu_gba_demo.index = 1;
						}
						break;
					case 1:
						if (wait_for_gba() == 0) {
							menu_gba_demo.index = 2;
						}
						break;
					case 2:
						SDL_Flip(windowScreen);
						send_rom();
						menu_gba_demo.index = 3;
						break;
					default:
						break;
				}
				if (menu_gba_demo.index != 2 && (keyPressed(INPUT_B) || keyPressed(INPUT_SELECT))) {
					menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
					g_sceneState = 301;
				}
				break;
#endif
			/* Sound Menu */
			case 308:
				g_frameState.increment();
				sprite_menu_background_ins.renderSprite_menu();
				menu_sound.renderMenu();
				switch (menu_sound.handleInput(0)) {
					case 0:
						if (lastMusicPlayed == MENU_MUSIC_TEST->index) {
							stopMusic();
							lastMusicPlayed = -1;
						} else {
							switch (MENU_MUSIC_TEST->index) {
								case 0:
									playMusic(MUSIC_TITLE_SCREEN, false, DEFAULT_VOLUME_GAME);
									break;
								case 1:
									playMusic(MUSIC_MENU, true, DEFAULT_VOLUME_MUSIC);
									break;
								case 2:
									playMusic(MUSIC_STINKOMAN_DAY, true, DEFAULT_VOLUME_MUSIC);
									break;
								case 3:
									playMusic(MUSIC_STINKOMAN_EVENING, true, DEFAULT_VOLUME_MUSIC);
									break;
								case 4:
									playMusic(MUSIC_STINKOMAN_NIGHT, true, DEFAULT_VOLUME_MUSIC);
									break;
								case 5:
									playMusic(MUSIC_STINKOMAN_DAWN, true, DEFAULT_VOLUME_MUSIC);
									break;
								case 6:
									playMusic(MUSIC_STINKOMAN_MIDPOINT, true, DEFAULT_VOLUME_MUSIC);
									break;
								case 7:
									playMusic(MUSIC_STINKOMAN_BOSS, true, DEFAULT_VOLUME_MUSIC);
									break;
								case 8:
									playMusic(MUSIC_STINKOMAN_LAST_10, true, DEFAULT_VOLUME_MUSIC);
									break;
								case 9:
									playMusic(MUSIC_STINKOMAN_HOMESTRETCH, true, DEFAULT_VOLUME_MUSIC);
									break;
								case 10:
									playMusic(MUSIC_STINKOMAN_FINAL_BOSS, true, DEFAULT_VOLUME_MUSIC);
									break;
								case 11:
									playMusic(MUSIC_ENDING_1, false, DEFAULT_VOLUME_MUSIC);
									break;
								case 12:
									playMusic(MUSIC_ENDING_2, false, DEFAULT_VOLUME_MUSIC);
									break;
								default:
									break;
							}
							lastMusicPlayed = MENU_MUSIC_TEST->index;
						}
						break;
					case 1:
						loadAndPlaySound(sfxArr[MENU_SFX_TEST->index]);
						break;
					case 2:
						loadAndPlaySound(sfxArr_strongBad[MENU_VOICE_TEST->index]);
						break;
					case -1: // Press B/Select
						menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
						g_sceneState = 301;
						if (lastMusicPlayed == -1) {
							playMusic(MUSIC_MENU, true, DEFAULT_VOLUME_MUSIC);
						}
						break;
					default:
						break;
				}
				break;
			/* Credits Screen */
			case 309:
				g_frameState.increment();
				sprite_menu_background_ins.renderSprite_menu();
				menu_credits.renderNotebook();
				switch (menu_credits.handleInput()) {
					case -1: // Press B/Select
						menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
						g_sceneState = 301;
						break;
					default:
						break;
				}
				break;
			/* Quit Screen */
			case 310:
				g_frameState.increment();
				sprite_menu_background_ins.renderSprite_menu();
				menu_quit.renderMenu();
				switch (menu_quit.handleInput(2)) {
					case QUIT_BACK_INDEX:
						menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
						g_sceneState = 301;
						break;
					case QUIT_CONFIRM_INDEX:
						stopMusic();
						saveGameState_settings();
						loadAndPlaySound(SFX_ITSOVER);
						while (sfxChannel_strongBad != NULL) {
							freeFinishedSoundChunks(); // wait for sound to stop playing
						}
						isRunning = false;
						break;
					case -1: // Press B/Select
						menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, scalingType);
						g_sceneState = 301;
						break;
					default:
						break;
				}
				break;
			/* Game */
			case 4:
				if (!GM.paused && !GM.manually_paused) {
					if (GM.debugMode) {
						GM.handleDebugCheat();
					}

					GM.player.invinceCheck();
					GM.popArchers();
					GM.updateArchersAndArrows();
					GM.getPlayerInput();
					GM.updateKnightHome();
					GM.updateKnightOffsetAndMove();
					if (GM.testWon() || (keyPressed(INPUT_SELECT) && GM.debugMode)) {
						GM.updateScore(min((20 + ((GM.level / 5) + 1) * 5), 200));
						GM.clearArrows();
						if (!(GM.level == 47 || GM.level == 49 || (GM.level >= 91 && GM.level <= 94) || GM.level == 96 || GM.level == 98 || GM.level == 99)) {
							fadeMusic(1200);
						}
						g_sceneState = 8;
						g_frameState.set(256);
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
						if (keyPressed(INPUT_START)) {
							GM.startDown = true;
						}
						if (GM.startDown && !keyHeld(INPUT_START)) {
							GM.startDown = false;
							setVolume_music(DEFAULT_VOLUME_MUSIC);
							GM.manually_paused = 0;
#if defined(SDL1)
							SDL_FreeSurface(transparentScreen);
#endif
						}
					} else {
						if (MENU_RESPAWN_BEHAVIOR->isValue(1)) {
							GM.updateKnightHome();
						}
						GM.updateKnightOffsetAndMove();
					}
				}
				if (!GM.manually_paused) {
					if (GM.dm_frameState.frame >= 4) {
						GM.dm_updateFrameState();
					}
					if (GM.b_frameState.frame >= 2) {
						GM.b_updateFrameState();
					}
					if (GM.player.frameState.frame >= 20) {
						GM.player.updateFrameState();
					}
				}
				if (GM.gameOver) {
					g_sceneState = 5;
					g_frameState.set(321);
					// no break; it should continue directly to the next state on the current frame
				} else {
					if (GM.kick_frameState.frame > 1) {
						GM.kick_updateFrameState();
					}
					// render everything
					renderBackground();
					GM.renderTopBar();
					GM.renderAndAnimateCottages();
					GM.renderKnights();
					GM.renderPeasants();
					GM.renderTrogdor();
					if (GM.burnination > 0) {
						GM.player.sprite_fire.renderSprite_game();
					}
					GM.renderArchers();
					GM.renderArrows();
					if (GM.sprite_dm.isActive) {
						GM.sprite_dm.renderSprite_game();
					} else if (GM.b_visible) {
						GM.sprite_bf.renderSprite_game();
						GM.sprite_bt.renderSprite_game();
					}
					if (GM.manually_paused) {
						// Here, the original game renders a black circle around the top-right of the center of the screen...
						// I think it's a mistake? I may add it later, but I'll leave it out for now.
						renderTransparentForeground();
						if ((int)((frameCounter_global - GM.manually_paused) * frameRateMult) % 10 < 5) {
							renderText(text_4_paused_1, font_serif_white_6);
							renderText(text_4_paused_2, font_serif_white_6);
							renderText(text_4_paused_3, font_serif_white_6);
						}
						if (keyHeld(INPUT_A) && keyPressed(INPUT_SELECT)) {
							g_sceneState = 3;
							lastMusicPlayed = -1;
							GM.saveGameState_autosave();
							stopMusic();
							setVolume_music(DEFAULT_VOLUME_MUSIC);
							menuMusicHasStarted = false;
							MM = MenuManager();
							GM.manually_paused = 0;
						}
					}
					if (GM.inTreasureHut) {
						GM.paused = true;
						GM.treasureHutFound = true;
						GM.player.sprite.setPosX(211);
						GM.player.sprite.setPosY(118);
						GM.treasureHut_timer = 110;
						GM.set_level_background(5);
						loadAndPlaySound(SFX_SFX2);
						GM.player.sprite.isActive = true;
						g_sceneState = 6;
					}
					break;
				}
			/* Game Over Screen */
			case 5:
				GM.renderTopBar();
				cutscene_game_over();
				if (g_sceneState == 5) {
					g_frameState.increment();
				}
				if (keyPressed(INPUT_START)) {
					g_sceneState = 3;
					lastMusicPlayed = -1;
					stopMusic();
					menuMusicHasStarted = false;
					MM = MenuManager();
				}
				if (g_sceneState == 5) {
					g_frameState.increment();
				}
				break;
			/* Game (Treasure Hut) */
			case 6:
				if (GM.manually_paused) {
					if (keyPressed(INPUT_START)) {
						GM.startDown = true;
					}
					if (GM.startDown && !keyHeld(INPUT_START)) {
						GM.startDown = false;
						setVolume_music(DEFAULT_VOLUME_MUSIC);
						GM.manually_paused = 0;
#if defined(SDL1)
						SDL_FreeSurface(transparentScreen);
#endif
					}
				} else {
					GM.handle_treasure_hut();
					GM.updateKnightOffsetAndMove();
					if (GM.dm_frameState.frame >= 4) {
						GM.dm_updateFrameState();
					}
					if (GM.b_frameState.frame >= 2) {
						GM.b_updateFrameState();
					}
					if (GM.player.frameState.frame >= 20) {
						GM.player.updateFrameState();
					}
				}
				if (GM.gameOver) {
					g_sceneState = 5;
					g_frameState.set(321);
					break;
				} else {
					if (GM.kick_frameState.frame > 1) {
						GM.kick_updateFrameState();
					}
					// render everything
					renderBackground();
					GM.renderTopBar();
					GM.renderLoot();
					GM.renderTrogdor();
					if (GM.burnination > 0) {
						GM.player.sprite_fire.renderSprite_game();
					}
					if (GM.sprite_dm.isActive) {
						GM.sprite_dm.renderSprite_game();
					} else if (GM.b_visible) {
						GM.sprite_bf.renderSprite_game();
						GM.sprite_bt.renderSprite_game();
					}
					if (GM.manually_paused) {
						// Here, the original game renders a black circle around the top-right of the center of the screen...
						// I think it's a mistake? I may add it later, but I'll leave it out for now.
						renderTransparentForeground();
						if ((int)((frameCounter_global - GM.manually_paused) * frameRateMult) % 10 < 5) {
							renderText(text_4_paused_1, font_serif_white_6);
							renderText(text_4_paused_2, font_serif_white_6);
							renderText(text_4_paused_3, font_serif_white_6);
						}
						if (keyHeld(INPUT_A) && keyPressed(INPUT_SELECT)) {
							g_sceneState = 3;
							lastMusicPlayed = -1;
							GM.saveGameState_autosave();
							stopMusic();
							menuMusicHasStarted = false;
							MM = MenuManager();
							GM.manually_paused = 0;
						}
					}
					if (!GM.inTreasureHut) {
						GM.paused = false;
						GM.player.sprite.setPosX(GM.store_x);
						GM.player.sprite.setPosY(GM.store_y);
						GM.set_level_background(levels[GM.levelIndex][0]);
						g_sceneState = 4;
					}
					break;
				}
			case 7:
				break;
			/* End of Level Animation */
			case 8:
				renderBackground();
				GM.renderTopBar();
				GM.renderAndAnimateCottages();
				if (((g_frameState.frame - 1) / 2) % 2 == 0) {
					sprite_end_of_level_flash_ins.renderSprite_game();
				}
				if (g_frameState.frame) {
					switch (g_frameState.frame) {
						case 257:
							if ((rand() % 100) < 10 * GM.sbVoiceMult) {
								if ((rand() % 100) < 50) {
									loadAndPlaySound(SFX_SBLEVELBEAT);
								} else {
									loadAndPlaySound(SFX_SB1);
								}
							}
							break;
						case 265:
							if ((sfxChannel_strongBad == NULL) && ((rand() % 100) < 10 * GM.sbVoiceMult)) {
								loadAndPlaySound(SFX_SBBEST);
							}
							break;
						case 276:
							g_sceneState = 9;
							g_frameState.set(277);
							break;
						default:
							break;
					}
				}
				if (g_sceneState == 8) {
					g_frameState.increment();
				}
				GM.player.sprite_end_of_level.renderSprite_game();
				break;
			/* Level Beaten Screen */
			case 9:
				GM.renderTopBar();
				cutscene_level_beaten();
				if (g_frameState.startingFrame(285)) {
					GM.updateLevel(1);
					GM.saveGameState_autosave();
				} else if ((MENU_LEVEL_TRAN->isValue(0) && g_frameState.frame == 316) || (MENU_LEVEL_TRAN->isValue(1) && (keyPressed(INPUT_A) || keyPressed(INPUT_START)))) {
					if (g_frameState.frame < 285) {
						GM.updateLevel(1);
						GM.saveGameState_autosave();
					}
					switch (GM.level) {
						case 5:
							g_sceneState = 11;
							g_frameState.set(420);
							break;
						case 9:
							g_sceneState = 12;
							g_frameState.set(493);
							break;
						case 13:
							g_sceneState = 13;
							g_frameState.set(567);
							break;
						case 17:
							g_sceneState = 14;
							g_frameState.set(641);
							break;
						case 21:
							g_sceneState = 15;
							g_frameState.set(710);
							break;
						case 25:
							g_sceneState = 16;
							g_frameState.set(780);
							break;
						case 31:
							g_sceneState = 17;
							g_frameState.set(853);
							break;
						case 35:
							g_sceneState = 18;
							g_frameState.set(927);
							break;
						case 39:
							g_sceneState = 19;
							g_frameState.set(1000);
							break;
						case 43:
							g_sceneState = 20;
							g_frameState.set(1076);
							break;
						case 47:
							g_sceneState = 21;
							g_frameState.set(1153);
							break;
						case 51:
							g_sceneState = 22;
							g_frameState.set(1226);
							break;
						case 101:
							g_sceneState = 23;
							g_frameState.set(1337);
							break;
						default:
							GM.levelInit();
							g_sceneState = 4;
							break;
					}
					if (sound_channel_level_beaten != 99) {
						sfxChannelArr[sound_channel_level_beaten] = NULL;
					}
					sound_channel_level_beaten = 99;
				}
				if (g_sceneState == 9) {
					g_frameState.increment();
				}
				break;
			/* Nothing */
			case 10:
				break;
			/* Level 4 Interlude */
			case 11:
				GM.renderTopBar();
				cutscene_level_4();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 11) {
					g_frameState.increment();
				}
				break;
			/* Level 8 Interlude */
			case 12:
				GM.renderTopBar();
				cutscene_level_8();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 12) {
					g_frameState.increment();
				}
				break;
			/* Level 12 Interlude */
			case 13:
				GM.renderTopBar();
				cutscene_level_12();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 13) {
					g_frameState.increment();
				}
				break;
			/* Level 16 Interlude */
			case 14:
				GM.renderTopBar();
				cutscene_level_16();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 14) {
					g_frameState.increment();
				}
				break;
			/* Level 20 Interlude */
			case 15:
				GM.renderTopBar();
				cutscene_level_20();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 15) {
					g_frameState.increment();
				}
				break;
			/* Level 24 Interlude */
			case 16:
				GM.renderTopBar();
				cutscene_level_24();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 16) {
					g_frameState.increment();
				}
				break;
			/* Level 30 Interlude */
			case 17:
				GM.renderTopBar();
				cutscene_level_30();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 17) {
					g_frameState.increment();
				}
				break;
			/* Level 34 Interlude */
			case 18:
				GM.renderTopBar();
				cutscene_level_34();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 18) {
					g_frameState.increment();
				}
				break;
			/* Level 38 Interlude */
			case 19:
				GM.renderTopBar();
				cutscene_level_38();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 19) {
					g_frameState.increment();
				}
				break;
			/* Level 42 Interlude */
			case 20:
				GM.renderTopBar();
				cutscene_level_42();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 20) {
					g_frameState.increment();
				}
				break;
			/* Level 46 Interlude */
			case 21:
				GM.renderTopBar();
				cutscene_level_46();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 21) {
					g_frameState.increment();
				}
				break;
			/* Level 50 Interlude */
			case 22:
				GM.renderTopBar();
				cutscene_level_50();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 22) {
					g_frameState.increment();
				}
				break;
			/* Level 100 Interlude (Credits) */
			case 23:
				GM.renderTopBar();
				cutscene_level_100();
				if (!cutsceneIsPlaying) {
					GM.levelInit();
					g_sceneState = 4;
				}
				if (g_sceneState == 23) {
					g_frameState.increment();
				}
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

		heldKeys_last = heldKeys;
		heldDirs_last = heldDirs;
#if !(defined(GAMECUBE)|| defined(PSP) || defined(XBOX))
		/* Update Mouse Position */
		mouseInput_x_last = mouseInput_x;
		mouseInput_y_last = mouseInput_y;
#endif

		/* Free Sound Effects That Have Finished Playing */
		if (g_sceneState > 0) freeFinishedSoundChunks();

		/* Draw Overlay */
		if (renderOverlay) {
			if (showOverlay) {
				sprite_overlay_basement_top_ins.renderSprite_overlay();
				sprite_overlay_basement_bottom_ins.renderSprite_overlay();
				sprite_overlay_basement_left_ins.renderSprite_overlay();
				sprite_overlay_basement_right_ins.renderSprite_overlay();
			} else {
#if !defined(SDL1)
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
#endif
				sprite_overlay_basement_top_ins.renderEmptyOverlay();
				sprite_overlay_basement_bottom_ins.renderEmptyOverlay();
				sprite_overlay_basement_left_ins.renderEmptyOverlay();
				sprite_overlay_basement_right_ins.renderEmptyOverlay();
			}
		}

		/* Update Screen */
#if !defined(SDL1)
		SDL_RenderPresent(renderer);
#else
		SDL_Flip(windowScreen);
#endif
		
		/* Cap Framerate */
		frameCounter_global++;
		frameTime = SDL_GetTicks() - (Uint32)timer_global.now;
		if (frameTime < ticksPerFrame) {
			SDL_Delay(ticksPerFrame - frameTime);
		}
	}

	/* Destroy all SDL objects and properly close program */
	DestroyAll();

	return 0;

#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP) || defined(THREEDS) || defined(XBOX))
	} catch (const char *badPath) {
#if !defined(SDL1)
		SDL_SetRenderDrawColor(renderer, 69, 95, 216, 255);
		SDL_RenderClear(renderer);
#else
		SDL_FillRect(windowScreen, NULL, 0x455FD8);
#endif

		isRunning = true;
		HandleErrorText(badPath);

#if !defined(SDL1)
		SDL_RenderPresent(renderer);
#else
		SDL_Flip(windowScreen);
#endif

		while (1) {
			handlePlayerInput();
			if (!isRunning || keyPressed(INPUT_START)) {
				break;
			}
		}

		return -1;
	}
#endif
}