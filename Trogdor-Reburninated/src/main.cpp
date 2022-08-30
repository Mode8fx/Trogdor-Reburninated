#include "main.h"

/* General Input */
Uint32 keyInputs;
Uint32 heldKeys;
Uint32 heldKeys_last;
Uint8  heldDirs;
Uint8  heldDirs_last;
Uint8  heldDirs_kb;
Uint8  heldDirs_dpad;
Uint8  heldDirs_stick;
Sint32 timer_buttonHold;
Sint32 timer_buttonHold_repeater;

/* Timer */
Timer timer_global;
Uint32 deltaTime;

/* Framerate */
Uint32 frameTime;
Uint32 frameCounter_global;

/* Program State */
Sint8 sceneState = 0;
Sint16 frameState = 1;
Uint16 rand_var;

/* Other */
MenuManager MM;
GameManager GM;
Uint8 contraArrayKey[10] = { 0, 0, 1, 1, 2, 3, 2, 3, 5, 4 }; // Up Up Down Down Left Right Left Right B A (Konami code)
Uint8 pacmanArrayKey[11] = { 0, 0, 0, 1, 1, 1, 2, 3, 2, 3, 2 }; // Up Up Up Down Down Down Left Right Left Right Left (play Pac-Man on a Ms. Pac-Man + Galaga arcade cabinet)
Uint8 s3kArrayKey[9] = { 2, 2, 2, 3, 3, 3, 0, 0, 0 }; // Left Left Left Right Right Right Up Up Up (Sonic & Knuckles and S3&K level select)
Uint8 fzxArrayKey[8] = { 2, 5, 3, 0, 1, 2, 3, 4 }; // Left B Right Up Down Left Right A ((roughly) unlock everything in F-Zero X)

/* General-use Variables */
Sint8 i, j, k;
int int_i, int_j, int_k;
Uint32 uint_i, uint_j, uint_k;
float float_i;
double double_i;

int main(int argv, char** args) {
	isRunning = true;
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
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP)
	SDL_ShowCursor(SDL_DISABLE);
#endif

	loadSaveFile();
	InitializeDisplay();

#if defined(ANDROID)
	/* Initialize SDL_ttf, fonts, text objects, and sprite objects (already done for other systems in InitializeDisplay() via setScaling() */
	InitializeTextChars();
	InitializeTextObjects();
	InitializeSpritesPart1();
	InitializeSpritesPart2();
#endif

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

		handleInput();

		if (keyPressed(INPUT_FULLSCREEN)) {
			SDL_toggleFullscreen();
		}
		if (keyPressed(INPUT_Y)) {
			isIntegerScale = !isIntegerScale;
			windowSizeChanged = true;
		}
		/* Handle Window Size Changes */
		if (windowSizeChanged) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP)) && !defined(SDL1)
			if (SDL_GetWindowSurface(window)->w < appWidth)
				SDL_SetWindowSize(window, appWidth, SDL_GetWindowSurface(window)->h);
			if (SDL_GetWindowSurface(window)->h < appHeight)
				SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, appHeight);
			// If you resize the window to within 6% of an integer ratio, snap to that ratio
			if (isIntegerScale) {
				snapWindow_x(0.06);
				snapWindow_y(0.06);
			}
#endif
			setScaling();
			updateText(&text_4_score_val, to_string(GM.score));
			updateText(&text_4_mans_val, to_string(GM.mans));
			updateText(&text_4_level_val, to_string(GM.level));
			if (gameHiResMult < 2) {
				MM.maxPageNum = 5;
				updateText(&text_3_page, "("+to_string(MM.page)+"/"+to_string(MM.maxPageNum)+")");
			} else {
				MM.maxPageNum = 4;
				if (MM.page > MM.maxPageNum) MM.page = MM.maxPageNum;
				updateText(&text_3_page, "("+to_string(MM.page)+"/"+to_string(MM.maxPageNum)+")");
			}
			GM.resetAllSrcRects();
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
		switch (sceneState) {
			/* Loading Screen */
			case 0:
				switch (frameState) {
					case 1:
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x = text_0_loading.dstrect.x;
						frameState++;
						break;
					case 2:
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['l' - 32].dstrect.w;
						frameState++;
						break;
					case 3:
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['o' - 32].dstrect.w;
						frameState++;
						break;
					case 4:
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['a' - 32].dstrect.w;
						frameState++;
						break;
					case 5:
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['d' - 32].dstrect.w;
						frameState++;
						break;
					case 6:
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['i' - 32].dstrect.w;
						frameState++;
						break;
					case 7:
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['n' - 32].dstrect.w;
						frameState++;
						break;
					case 8:
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['g' - 32].dstrect.w;
						frameState++;
						break;
					case 9:
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['.' - 32].dstrect.w;
						frameState++;
						break;
					case 10:
						InitializeSound();
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['.' - 32].dstrect.w;
						frameState++;
						break;
					case 11:
						InitializeMusic();
						renderText(text_0_loading, textChars_font_serif_white_14);
						text_0_loading_censor_rect.x += textChars_font_serif_white_14['.' - 32].dstrect.w;
						frameState++;
						break;
					case 12:
						InitializeController();
						renderText(text_0_loading, textChars_font_serif_white_14);
						frameState++;
						break;
					case 13:
						InitializeSFX();
						renderText(text_0_loading, textChars_font_serif_white_14);
						frameState++;
						break;
					case 14:
						renderText(text_0_loading, textChars_font_serif_white_14);
						frameState++;
						break;
					case 15:
						renderText(text_0_loading, textChars_font_serif_white_14);
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
				drawRect_gameTextScreen(text_0_loading_censor_rect, color_black.r, color_black.g, color_black.b);
				break;
			/* Videlectrix logo */
			case 1:
				if (frameState < 65) {
					renderSprite_static_app(sprite_videlectrix_logo);
					renderText(text_1_presents, textChars_font_nokia_12);
				}
				if (frameState < 72) {
					frameState++;
				} else {
					sceneState = 2;
					frameState = 73;
				}
				if (keyPressed(INPUT_START)) {
					loadAndPlaySound(SFX_TROGADOR);
					sceneState = 3;
					frameState = 3; // 3 is intentional
					MM = MenuManager();
				}
				break;
			/* Title Screen */
			case 2:
				if (frameState == 73) {
					playMusicWithoutLoop(MUSIC_TITLE_SCREEN);
				}
				if (frameState < 192) {
					frameState++;
				} else {
					loadAndPlaySound(SFX_TROGADOR);
					sceneState = 3;
					frameState = 3; // 3 is intentional
					MM = MenuManager();
				}
				renderSprite_static_game(sprite_title_screen);
				break;
			/* Instructions Screen */
			case 3:
				frameState++;
				MM.typeStuff();
				MM.handlePageChange();
				if (MM.page == 1) {
					if (keyPressed(INPUT_START)) {
						GM = GameManager(MM);
						GM.levelInit();
						updateText(&text_4_score_val, to_string(GM.score));
						updateText(&text_4_mans_val, to_string(GM.mans));
						updateText(&text_4_level_val, to_string(GM.level));
						sceneState = 4;
					} else if (keyPressed(INPUT_SELECT)) {
						isRunning = false;
					}
				}
				renderSprite_static_game(sprite_trogdor_logo);
				if (gameHiResMult < 2) {
					switch (MM.page) {
						case 1:
							renderText(text_3_instructions_1, textChars_font_serif_white_6_mult);
							renderText(text_3_instructions_2, textChars_font_serif_white_6_mult);
							renderText(text_3_instructions_2a, textChars_font_serif_white_6_mult);
							renderText(text_3_instructions_3, textChars_font_serif_white_6_mult);
							renderText(text_3_instructions_4, textChars_font_serif_white_6_mult);
							renderText(text_3_instructions_5, textChars_font_serif_white_6_mult);
							if (frameState % 4 < 2) {
								renderText(text_3_click_anywhere_to_start, textChars_font_serif_red_8_mult);
							}
							break;
						case 2:
							renderText(text_3_hints_1, textChars_font_serif_red_6_mult);
							renderText(text_3_hints_2, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_2a, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_3, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_3a, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_4, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_4a, textChars_font_serif_white_6_mult);
							break;
						case 3:
							renderText(text_3_hints_1, textChars_font_serif_red_6_mult);
							renderText(text_3_hints_5, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_5a, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_6, textChars_font_serif_red_6_mult);
							renderText(text_3_hints_7, textChars_font_serif_red_6_mult);
							break;
						case 4:
							renderText(text_3_credits_1, textChars_font_serif_red_6_mult);
							renderText(text_3_credits_2, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_3, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_4, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_5, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_6, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_7, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_8, textChars_font_serif_white_6_mult);
							break;
						case 5:
							renderText(text_3_coming_soon_1, textChars_font_serif_red_6_mult);
							renderText(text_3_coming_soon_2, textChars_font_serif_white_6_mult);
							renderText(text_3_coming_soon_3, textChars_font_serif_white_6_mult);
							renderText(text_3_coming_soon_4, textChars_font_serif_white_6_mult);
							renderText(text_3_coming_soon_4a, textChars_font_serif_white_6_mult);
							renderText(text_3_coming_soon_5, textChars_font_serif_white_6_mult);
							renderText(text_3_coming_soon_6, textChars_font_serif_white_6_mult);
							break;
						default:
							break;
					}
				} else {
					switch (MM.page) {
						case 1:
							renderText(text_3_instructions_1, textChars_font_serif_white_6_mult);
							renderText(text_3_instructions_2, textChars_font_serif_white_6_mult);
							renderText(text_3_instructions_3, textChars_font_serif_white_6_mult);
							renderText(text_3_instructions_4, textChars_font_serif_white_6_mult);
							renderText(text_3_instructions_5, textChars_font_serif_white_6_mult);
							if (frameState % 4 < 2) {
								renderText(text_3_click_anywhere_to_start, textChars_font_serif_red_8_mult);
							}
							renderText(text_3_quit, textChars_font_serif_white_6_mult);
							break;
						case 2:
							renderText(text_3_hints_1, textChars_font_serif_red_6_mult);
							renderText(text_3_hints_2, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_3, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_4, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_5, textChars_font_serif_white_6_mult);
							renderText(text_3_hints_6, textChars_font_serif_red_6_mult);
							renderText(text_3_hints_7, textChars_font_serif_red_6_mult);
							break;
						case 3:
							renderText(text_3_credits_1, textChars_font_serif_red_6_mult);
							renderText(text_3_credits_2, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_3, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_4, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_5, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_6, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_7, textChars_font_serif_white_6_mult);
							renderText(text_3_credits_8, textChars_font_serif_white_6_mult);
							break;
						default:
							renderText(text_3_coming_soon_1, textChars_font_serif_red_6_mult);
							renderText(text_3_coming_soon_2, textChars_font_serif_white_6_mult);
							renderText(text_3_coming_soon_3, textChars_font_serif_white_6_mult);
							renderText(text_3_coming_soon_4, textChars_font_serif_white_6_mult);
							renderText(text_3_coming_soon_5, textChars_font_serif_white_6_mult);
							renderText(text_3_coming_soon_6, textChars_font_serif_white_6_mult);
							break;
					}
				}
				renderText(text_3_page, textChars_font_serif_white_6_mult);
				break;
			/* Game */
			case 4:
				if (!GM.paused && !GM.manually_paused) {
					if (MM.pacmanActive) {
						GM.handleDebugCheat();
					}

					GM.player.invinceCheck();
					GM.popArchers();
					GM.updateArchersAndArrows();
					GM.getPlayerInput();
					GM.updateKnightHome();
					GM.updateKnightOffsetAndMove();
					if (GM.testWon() || (MM.pacmanActive && keyPressed(INPUT_SELECT))) {
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
						if (keyPressed(INPUT_START)) {
							GM.startDown = true;
						}
						if (GM.startDown && !keyHeld(INPUT_START)) {
							GM.startDown = false;
							GM.manually_paused = 0;
#if defined(SDL1)
							SDL_FreeSurface(transparentScreen);
#endif
						}
					} else {
						GM.updateKnightOffsetAndMove();
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
					renderBackground();
					GM.renderTopBar();
					GM.renderAndAnimateCottages();
					GM.renderKnights();
					GM.renderPeasants();
					GM.renderTrogdor();
					if (GM.burnination > 0) {
						renderSprite_game(sprite_trogdor_fire, GM.player.fire_srcrect, GM.player.fire_dstrect);
					}
					GM.renderArchers();
					GM.renderArrows();
					if (GM.dm_visible) {
						renderSprite_game(sprite_death_message, GM.dm_srcrect, sprite_death_message.dstrect);
					} else if (GM.b_visible) {
						renderSprite_game(sprite_burninate_fire, GM.bf_srcrect, GM.bf_dstrect);
						renderSprite_static_game(sprite_burninate_text);
					}
					if (GM.manually_paused) {
						// Here, the original game renders a black circle around the top-right of the center of the screen...
						// I think it's a mistake? I may add it later, but I'll leave it out for now.
						renderTransparentForeground();
						if ((frameCounter_global - GM.manually_paused) % 10 < 5) {
							renderText(text_4_paused_1, textChars_font_serif_white_6);
							renderText(text_4_paused_2, textChars_font_serif_white_6);
							renderText(text_4_paused_3, textChars_font_serif_white_6);
						}
						if (keyHeld(INPUT_A) && keyPressed(INPUT_SELECT)) {
							sceneState = 3;
							MM = MenuManager();
						}
					}
					if (GM.inTreasureHut) {
						GM.paused = true;
						GM.treasureHutFound = true;
						GM.player.dstrect.x = 211;
						GM.player.dstrect.y = 118;
						GM.treasureHut_timer = 110;
						GM.set_level_background(5);
						loadAndPlaySound(SFX_SFX2);
						GM.player.visible = true;
						sceneState = 6;
					}
					break;
				}
			/* Game Over Screen */
			case 5:
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				// TODO: draw "IT'S OVER!" and whatever else needs to be handled for this screen
				renderSprite_static_game(sprite_game_over_trogdor);
				switch (frameState) {
					case 321:
						loadAndPlaySound(SFX_GAMEOVER);
						if (GM.score < 2000) {
							if (GM.arched) {
								if ((rand() % 100) < 50 * GM.sbVoiceMult) {
									loadAndPlaySound(SFX_SBARCHEND);
								}
							} else if ((GM.score > 1000) && ((rand() % 100) < 70 * GM.sbVoiceMult)) {
								loadAndPlaySound(SFX_SBSCORE);
							} else if ((rand() % 100) < 70 * GM.sbVoiceMult) {
								loadAndPlaySound(SFX_SBGAMEOVER);
							}
						} else {
							if (GM.sbVoiceMult > 0) {
								loadAndPlaySound(SFX_SBSECRET);
							}
						}
						GM.setMans(0);
						break;
					default:
						break;
				}
				// TODO: high score-related things here
				if (keyPressed(INPUT_START)) { // TODO: placeholder; remove this later
					sceneState = 3;
					MM = MenuManager();
				}
				if (sceneState == 5) {
					frameState++;
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
						GM.manually_paused = 0;
#if defined(SDL1)
						SDL_FreeSurface(transparentScreen);
#endif
					}
				} else {
					GM.handle_treasure_hut();
					GM.updateKnightOffsetAndMove();
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
					renderBackground();
					GM.renderTopBar();
					GM.renderLoot();
					GM.renderTrogdor();
					if (GM.burnination > 0) {
						renderSprite_game(sprite_trogdor_fire, GM.player.fire_srcrect, GM.player.fire_dstrect);
					}
					if (GM.dm_visible) {
						renderSprite_game(sprite_death_message, GM.dm_srcrect, sprite_death_message.dstrect);
					} else if (GM.b_visible) {
						renderSprite_game(sprite_burninate_fire, GM.bf_srcrect, GM.bf_dstrect);
						renderSprite_static_game(sprite_burninate_text);
					}
					if (GM.manually_paused) {
						// Here, the original game renders a black circle around the top-right of the center of the screen...
						// I think it's a mistake? I may add it later, but I'll leave it out for now.
						renderTransparentForeground();
						if ((frameCounter_global - GM.manually_paused) % 10 < 5) {
							renderText(text_4_paused_1, textChars_font_serif_white_6);
							renderText(text_4_paused_2, textChars_font_serif_white_6);
							renderText(text_4_paused_3, textChars_font_serif_white_6);
						}
						if (keyHeld(INPUT_A) && keyPressed(INPUT_SELECT)) {
							sceneState = 3;
							MM = MenuManager();
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
				renderBackground();
				GM.renderTopBar();
				GM.renderAndAnimateCottages();
				if (((frameState - 1) / 2) % 2 == 0) {
					renderSprite_static_game(sprite_end_of_level_flash);
				}
				switch (frameState) {
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
						if ((rand() % 100) < 10 * GM.sbVoiceMult) {
							loadAndPlaySound(SFX_SBBEST);
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
				renderSprite_static_hiRes(sprite_end_of_level_trogdor);
				break;
			/* Level Beaten Screen */
			case 9:
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_9_nice_work, textChars_font_serif_white_10);
				// TODO: draw "LEVEL BEATEN!", smoke, and level fire
				renderSprite_static_game(sprite_level_beaten_trogdor);
				switch (frameState) {
					case 277:
						loadAndPlaySound(SFX_BURNINATE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_11_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 420:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_12_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 493:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_13_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 567:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_14_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 641:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_15_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 710:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_16_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 780:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_17_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 853:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_18_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 927:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_19_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 1000:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_20_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 1076:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_21_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 1153:
						loadAndPlaySound(SFX_CUTSCENE);
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_22_cutscene, textChars_font_serif_white_9);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				switch (frameState) {
					case 1226:
						loadAndPlaySound(SFX_CUTSCENE);
						break;
					case 1297:
						if (rand() % 100 < 50 * GM.sbVoiceMult) {
							loadAndPlaySound(SFX_SBKERREK);
						}
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
				GM.renderTopBar();
				//drawRect(divider_level_beaten_rect, color_black.r, color_black.g, color_black.b);
				renderText(text_placeholder_cutscene, textChars_font_serif_red_8);
				// TODO: implement cutscene
				if (keyPressed(INPUT_START)) { // placeholder
					frameState = 1715;
				}
				switch (frameState) {
					// the uses of renderText here are wrong, but just a placeholder until the animation system is reworked
					case 1337:
						break;
					case 1349:
						if (rand() % 100 < 50 * GM.sbVoiceMult) {
							loadAndPlaySound(SFX_SBWIN);
						}
						break;
					case 1397:
						renderText(text_23_cutscene_1, textChars_font_serif_white_9);
						break;
					case 1423:
						renderText(text_23_cutscene_2, textChars_font_serif_white_9);
						break;
					case 1440:
						renderText(text_23_cutscene_3, textChars_font_serif_white_9);
						break;
					case 1456:
						if (rand() % 100 < 50 * GM.sbVoiceMult) {
							loadAndPlaySound(SFX_SBWIN2);
						}
						break;
					case 1501:
						renderText(text_23_cutscene_4, textChars_font_serif_white_9);
						break;
					case 1522:
						renderText(text_23_cutscene_5, textChars_font_serif_white_9);
						break;
					case 1543:
						renderText(text_23_cutscene_6, textChars_font_serif_white_9);
						break;
					case 1562:
						renderText(text_23_cutscene_7, textChars_font_serif_white_9);
						break;
					case 1582:
						renderText(text_23_cutscene_8, textChars_font_serif_white_9);
						break;
					case 1601:
						renderText(text_23_cutscene_9, textChars_font_serif_white_9);
						break;
					case 1621:
						renderText(text_23_cutscene_10, textChars_font_serif_white_9);
						break;
					case 1641:
						renderText(text_23_cutscene_11, textChars_font_serif_white_9);
						break;
					case 1660:
						renderText(text_23_cutscene_12, textChars_font_serif_white_9);
						break;
					case 1681:
						renderText(text_23_cutscene_13, textChars_font_serif_white_9);
						break;
					case 1716:
						GM.levelInit();
						sceneState = 4;
						break;
					default:
						break;
				}
				if (sceneState == 23) {
					frameState++;
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
#if !(defined(GAMECUBE)|| defined(PSP))
		/* Update Mouse Position */
		mouseInput_x_last = mouseInput_x;
		mouseInput_y_last = mouseInput_y;
#endif

		/* Free Sound Effects That Have Finished Playing */
		if (sceneState > 0) freeFinishedSoundChunks();

		/* Draw Overlay (this can and probably should be optimized later) */
		if (sceneState >= 2 && isIntegerScale) {
			renderSprite_static_app(sprite_overlay_basement);
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
}