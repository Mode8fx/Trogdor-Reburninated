#include "cutscenes.h"
#include "general.h"
#include "sound_logic.h"
#include "text_objects.h"
#include "classes.h"
#include "config.h"

SpriteInstance cutscene_level_beaten_trogdor;
SpriteInstance cutscene_level_beaten_smoke;
SpriteInstance cutscene_game_over_trogdor;
//SpriteInstance cutscene_game_over_banner;
SpriteInstance cutscene_game_over_text;
SpriteInstance cutscene_game_over_jonathan_howe;
SpriteInstance cutscene_cottage_fire;
SpriteInstance cutscene_peasant_1;
SpriteInstance cutscene_peasant_2;
SpriteInstance cutscene_peasant_3;
SpriteInstance cutscene_peasant_4;
SpriteInstance cutscene_peasant_5;
SpriteInstance cutscene_peasant_6;
SpriteInstance cutscene_peasant_7;
SpriteInstance cutscene_peasant_8;
SpriteInstance cutscene_peasant_9;
SpriteInstance cutscene_peasant_10;
SpriteInstance cutscene_trogdor_1;
SpriteInstance cutscene_trogdor_2;
SpriteInstance cutscene_trogdor_3;
SpriteInstance cutscene_trogdor_4;
SpriteInstance cutscene_trogdor_5;
SpriteInstance cutscene_trogdor_6;
SpriteInstance cutscene_trogdor_fire;
SpriteInstance cutscene_trogdor_flexing;
SpriteInstance cutscene_trogdor_ending;
SpriteInstance cutscene_heart;
SpriteInstance cutscene_knight_1;
SpriteInstance cutscene_knight_2;
SpriteInstance cutscene_knight_funnyjoke;
SpriteInstance cutscene_kerrek;
SpriteInstance cutscene_kerrek_smoked;
SpriteInstance cutscene_strong_bad;
SpriteInstance cutscene_strong_bad_ending;
SpriteInstance cutscene_cottage_1;
SpriteInstance cutscene_cottage_2;
SpriteInstance cutscene_archer_1;
SpriteInstance cutscene_archer_2;
SpriteInstance cutscene_arrow_1;
SpriteInstance cutscene_arrow_2;
SpriteInstance cutscene_arrow_3;

Sint8 cutscene_level_100_screen_counter;
Uint8 sound_channel_level_beaten = 99;

void InitializeCutsceneObjects() {
	cutscene_level_beaten_trogdor = SpriteInstance(&sprite_level_beaten_trogdor, 0, 0);
	cutscene_level_beaten_smoke = SpriteInstance(&sprite_level_beaten_smoke, 0, 0);
	cutscene_game_over_trogdor = SpriteInstance(&sprite_game_over_trogdor, 0, 0);
	//cutscene_game_over_banner = SpriteInstance(&sprite_game_over_banner, 0, 0);
	cutscene_game_over_text = SpriteInstance(&sprite_game_over_text, 0, 0);
	cutscene_game_over_jonathan_howe = SpriteInstance(&sprite_game_over_jonathan_howe, 0, 0);
	cutscene_cottage_fire = SpriteInstance(&sprite_cottage_fire, 0, 0);
	cutscene_peasant_1 = SpriteInstance(&sprite_peasant, 0, 0);
	cutscene_peasant_2 = SpriteInstance(&sprite_peasant, 0, 0);
	cutscene_peasant_3 = SpriteInstance(&sprite_peasant, 0, 0);
	cutscene_peasant_4 = SpriteInstance(&sprite_peasant, 0, 0);
	cutscene_peasant_5 = SpriteInstance(&sprite_peasant, 0, 0);
	cutscene_peasant_6 = SpriteInstance(&sprite_peasant, 0, 0);
	cutscene_peasant_7 = SpriteInstance(&sprite_peasant, 0, 0);
	cutscene_peasant_8 = SpriteInstance(&sprite_peasant, 0, 0);
	cutscene_peasant_9 = SpriteInstance(&sprite_peasant, 0, 0);
	cutscene_peasant_10 = SpriteInstance(&sprite_peasant, 0, 0);
	InitializeCutsceneObjects_trogdor();
	cutscene_trogdor_fire = SpriteInstance(&sprite_trogdor_fire, 0, 0);
	cutscene_trogdor_flexing = SpriteInstance(&sprite_trogdor_flexing, 0, 0);
	cutscene_trogdor_ending = SpriteInstance(&sprite_trogdor_ending, 0, 0);
	cutscene_heart = SpriteInstance(&sprite_heart, 0, 0);
	cutscene_knight_1 = SpriteInstance(&sprite_knight, 0, 0);
	cutscene_knight_2 = SpriteInstance(&sprite_knight, 0, 0);
	cutscene_knight_funnyjoke = SpriteInstance(&sprite_knight_funnyjoke, 0, 0);
	cutscene_kerrek = SpriteInstance(&sprite_kerrek, 0, 0);
	cutscene_kerrek_smoked = SpriteInstance(&sprite_kerrek_smoked, 0, 0);
	cutscene_strong_bad = SpriteInstance(&sprite_strong_bad, 0, 0);
	cutscene_strong_bad_ending = SpriteInstance(&sprite_strong_bad_ending, 0, 0);
	cutscene_cottage_1 = SpriteInstance(&sprite_cottage, 0, 0);
	cutscene_cottage_2 = SpriteInstance(&sprite_cottage, 0, 0);
	cutscene_archer_1 = SpriteInstance(&sprite_archer, 0, 0);
	cutscene_archer_2 = SpriteInstance(&sprite_archer, 0, 0);
	cutscene_arrow_1 = SpriteInstance(&sprite_arrow_funnyjoke, 0, 0);
	cutscene_arrow_2 = SpriteInstance(&sprite_arrow_funnyjoke, 0, 0);
	cutscene_arrow_3 = SpriteInstance(&sprite_arrow_funnyjoke, 0, 0);
}

void InitializeCutsceneObjects_trogdor() {
	if (GM.bigHeadMode) {
		cutscene_trogdor_1 = SpriteInstance(&sprite_trogdor_bighead, 0, 0);
		cutscene_trogdor_2 = SpriteInstance(&sprite_trogdor_bighead, 0, 0);
		cutscene_trogdor_3 = SpriteInstance(&sprite_trogdor_bighead, 0, 0);
		cutscene_trogdor_4 = SpriteInstance(&sprite_trogdor_bighead, 0, 0);
		cutscene_trogdor_5 = SpriteInstance(&sprite_trogdor_bighead, 0, 0);
		cutscene_trogdor_6 = SpriteInstance(&sprite_trogdor_bighead, 0, 0);
	} else {
		cutscene_trogdor_1 = SpriteInstance(&sprite_trogdor, 0, 0);
		cutscene_trogdor_2 = SpriteInstance(&sprite_trogdor, 0, 0);
		cutscene_trogdor_3 = SpriteInstance(&sprite_trogdor, 0, 0);
		cutscene_trogdor_4 = SpriteInstance(&sprite_trogdor, 0, 0);
		cutscene_trogdor_5 = SpriteInstance(&sprite_trogdor, 0, 0);
		cutscene_trogdor_6 = SpriteInstance(&sprite_trogdor, 0, 0);
	}
}

void cutscene_level_beaten() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 277:
				cutsceneIsPlaying = true;
				sound_channel_level_beaten = loadAndPlaySound(SFX_BURNINATE);
				cutscene_level_beaten_trogdor.isActive = false;
				cutscene_level_beaten_smoke.isActive = false;
				cutscene_cottage_fire.isActive = false;
				cutscene_level_beaten_trogdor.prepareAsCSO(-5, 41, 0, 0, 0, 0, 0, 0);
				cutscene_level_beaten_smoke.prepareAsCSO(125, 83.0 - cutscene_level_beaten_smoke.spriteObj->dstrect.h, 0, 0, 1, 8, 0, 0);
				break;
			case 281:
				cutscene_cottage_fire.prepareAsCSO(222, 0, 0, 0, 2, 0, 0, 0);
				break;
			case 289:
				cutscene_cottage_fire.isActive = false;
				break;
			case 308:
				cutscene_level_beaten_smoke.isActive = false;
				break;
			default:
				break;
		}
	}
	cutscene_level_beaten_trogdor.renderAsCSO(false);
	cutscene_level_beaten_smoke.renderAsCSO(false);
	cutscene_cottage_fire.renderAsCSO(false);
	renderText(text_9_nice_work, font_serif_white_10);
	renderText(text_9_level_gray, font_serif_gray_12);
	renderText(text_9_beaten_gray, font_serif_gray_12);
	renderText(text_9_level_red, font_serif_red_12);
	renderText(text_9_beaten_red, font_serif_red_12);
}

void cutscene_game_over() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 321:
				stopMusic();
				loadAndPlaySound(SFX_GAMEOVER);
				cutscene_game_over_trogdor.isActive = false;
				//cutscene_game_over_banner.isActive = false;
				cutscene_game_over_text.isActive = false;
				cutscene_game_over_jonathan_howe.isActive = false;
				cutscene_game_over_trogdor.prepareAsCSO(-13, 75, 0, 0, 0, 0, 0, 0);
				//cutscene_game_over_banner.prepareAsCSO(185, 156, 0, 0, 0, 0, 0, 0);
				cutscene_game_over_text.prepareAsCSO(44, 45, 0, 0, 0, 2, 0, 0);
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
					cutscene_game_over_jonathan_howe.prepareAsCSO(40, 173, 0, 0, 0, 1, 0, 0); // original is 41, 173
				}
				GM.setMans(0);
				break;
			default:
				break;
		}
	}
	cutscene_game_over_trogdor.renderAsCSO(false);
	//cutscene_game_over_banner.renderAsCSO(false);
	cutscene_game_over_text.renderAsCSO(false);
	cutscene_game_over_jonathan_howe.renderAsCSO(false);
}

void cutscene_level_4() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 420:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_peasant_1.isActive = false;
				cutscene_trogdor_1.isActive = false;
				cutscene_trogdor_fire.isActive = false;
				cutscene_knight_1.isActive = false;
				cutscene_knight_2.isActive = false;
				cutscene_peasant_1.prepareAsCSO(21, 82, 1, 0, 0, 0, 0, 0);
				cutscene_trogdor_1.prepareAsCSO(246, 70, 0, 0, 2, 0, -8, 0);
				break;
			case 427:
				cutscene_knight_1.prepareAsCSO(241, 75, 0, 0, 4, 0, -7, 0);
				break;
			case 431:
				cutscene_knight_2.prepareAsCSO(240, 86, 1, 0, 4, 0, -7, 0);
				break;
			case 448:
				cutscene_peasant_1.prepareAsCSO(24, 81, 0, 3, 0, 0, 0, 0);
				break;
			case 449:
				cutscene_trogdor_1.prepareAsCSO(25, 70, 0, 1, 2, 0, 8, 0);
				cutscene_trogdor_fire.prepareAsCSO(63, 78, 0, 1, 2, 0, 8, 0);
				cutscene_knight_1.setFrame(0);
				cutscene_knight_2.setFrame(0);
				break;
			case 450:
				cutscene_knight_1.prepareAsCSO(101, 75, 4, 1, 4, 0, 8, 0);
				cutscene_knight_2.prepareAsCSO(130, 86, 4, 1, 4, 0, 8, 0);
				break;
			case 453:
				cutscene_knight_1.setFrame(5);
				cutscene_knight_1.animFrameCounter = 0;
				cutscene_knight_2.setFrame(5);
				cutscene_knight_2.animFrameCounter = 0;
				break;
			case 492:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	cutscene_peasant_1.renderAsCSO(false);
	cutscene_trogdor_1.renderAsCSO(false);
	cutscene_knight_1.renderAsCSO(false);
	cutscene_knight_2.renderAsCSO(false);
	cutscene_trogdor_fire.renderAsCSO(false);
	renderText(text_11_cutscene, font_serif_white_9);
#if !defined(SDL1)
	SDL_RenderFillRect(renderer, &right_overlay_padding);
#else
	SDL_FillRect(windowScreen, &right_overlay_padding, 0);
#endif
}

void cutscene_level_8() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 493:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_trogdor_1.isActive = false;
				cutscene_trogdor_fire.isActive = false;
				cutscene_peasant_1.isActive = false;
				cutscene_peasant_2.isActive = false;
				cutscene_peasant_3.isActive = false;
				cutscene_peasant_4.isActive = false;
				cutscene_trogdor_1.prepareAsCSO(128, 85, 0, 0, 0, 0, 0, 0);
				cutscene_peasant_1.prepareAsCSO(-8, 97, 1, 0, 0, 0, 6, 0);
				cutscene_peasant_2.prepareAsCSO(-64, 97, 1, 0, 0, 0, 6, 0);
				cutscene_peasant_3.prepareAsCSO(-120, 97, 1, 0, 0, 0, 6, 0);
				break;
			case 510:
				cutscene_peasant_1.vel_x = 0;
				break;
			case 513:
				cutscene_trogdor_fire.prepareAsCSO(106, 96, 0, 0, 2, 0, 0, 0);
				cutscene_peasant_1.setFrameAndForm(0, 1);
				cutscene_peasant_4.prepareAsCSO(-56, 97, 1, 0, 0, 0, 6, 0);
				break;
			case 514:
				cutscene_peasant_1.vel_y = 7;
				break;
			case 518:
				cutscene_trogdor_fire.isActive = false;
				break;
			case 519:
				cutscene_peasant_2.vel_x = 0;
				break;
			case 522:
				cutscene_trogdor_fire.isActive = true;
				cutscene_peasant_2.setFrameAndForm(0, 1);
				break;
			case 523:
				cutscene_peasant_2.vel_y = 7;
				break;
			case 527:
				cutscene_trogdor_fire.isActive = false;
				break;
			case 529:
				cutscene_peasant_3.vel_x = 0;
				break;
			case 532:
				cutscene_trogdor_fire.isActive = true;
				cutscene_peasant_3.setFrameAndForm(0, 1);
				break;
			case 533:
				cutscene_peasant_3.vel_y = 7;
				break;
			case 537:
				cutscene_trogdor_fire.isActive = false;
				break;
			case 538:
				cutscene_peasant_4.vel_x = 0;
				break;
			case 541:
				cutscene_trogdor_fire.isActive = true;
				cutscene_peasant_4.setFrameAndForm(0, 1);
				break;
			case 542:
				cutscene_peasant_4.vel_y = 7;
				break;
			case 546:
				cutscene_trogdor_fire.isActive = false;
				break;
			case 566:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	cutscene_peasant_1.renderAsCSO(false);
	cutscene_peasant_2.renderAsCSO(false);
	cutscene_peasant_3.renderAsCSO(false);
	cutscene_peasant_4.renderAsCSO(false);
	cutscene_trogdor_1.renderAsCSO(false);
	cutscene_trogdor_fire.renderAsCSO(false);
	renderText(text_12_cutscene, font_serif_white_9);
}

void cutscene_level_12() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 567:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_trogdor_1.isActive = false;
				cutscene_trogdor_2.isActive = false;
				cutscene_trogdor_3.isActive = false;
				cutscene_trogdor_4.isActive = false;
				cutscene_trogdor_5.isActive = false;
				cutscene_trogdor_6.isActive = false;
				cutscene_trogdor_1.prepareAsCSO(193, 70, 0, 0, 2, 0, -9, 0);
				break;
			case 570:
				cutscene_trogdor_2.prepareAsCSO(218, 70, 0, 0, 2, 0, -9, 0);
				break;
			case 575:
				cutscene_trogdor_3.prepareAsCSO(218, 70, 0, 0, 2, 0, -9, 0);
				break;
			case 580:
				cutscene_trogdor_4.prepareAsCSO(218, 70, 0, 0, 2, 0, -9, 0);
				break;
			case 585:
				cutscene_trogdor_5.prepareAsCSO(218, 70, 0, 0, 2, 0, -9, 0);
				break;
			case 590:
				cutscene_trogdor_6.prepareAsCSO(218, 70, 0, 0, 2, 0, -9, 0);
				break;
			case 595:
				cutscene_trogdor_1.prepareAsCSO(218, 70, 0, 0, 2, 0, -9, 0);
				break;
			case 600:
				cutscene_trogdor_2.prepareAsCSO(218, 70, 0, 0, 2, 0, -9, 0);
				break;
			case 605:
				cutscene_trogdor_3.prepareAsCSO(218, 70, 0, 0, 2, 0, -9, 0);
				break;
			case 640:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	cutscene_trogdor_1.renderAsCSO(false);
	cutscene_trogdor_2.renderAsCSO(false);
	cutscene_trogdor_3.renderAsCSO(false);
	cutscene_trogdor_4.renderAsCSO(false);
	cutscene_trogdor_5.renderAsCSO(false);
	cutscene_trogdor_6.renderAsCSO(false);
	renderText(text_13_cutscene, font_serif_white_9);
}

void cutscene_level_16() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 641:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_trogdor_1.isActive = false;
				cutscene_knight_1.isActive = false;
				cutscene_knight_2.isActive = false;
				cutscene_peasant_1.isActive = false;
				cutscene_peasant_2.isActive = false;
				cutscene_peasant_3.isActive = false;
				cutscene_peasant_4.isActive = false;
				cutscene_peasant_5.isActive = false;
				cutscene_peasant_6.isActive = false;
				cutscene_peasant_7.isActive = false;
				cutscene_peasant_8.isActive = false;
				cutscene_peasant_9.isActive = false;
				cutscene_peasant_10.isActive = false;
				cutscene_trogdor_1.prepareAsCSO(102, 72, 0, 0, 0, 2, 0, 0);
				cutscene_knight_1.prepareAsCSO(78, 86, 0, 0, 4, 0, 0, 0);
				cutscene_knight_2.prepareAsCSO(143, 86, 0, 1, 4, 0, 0, 0);
				cutscene_peasant_1.prepareAsCSO(3, 71, 0, 2, 1, 0, 0, 0);
				cutscene_peasant_2.prepareAsCSO(19, 74, 0, 2, 1, 0, 0, 0);
				cutscene_peasant_3.prepareAsCSO(34, 77, 0, 2, 1, 0, 0, 0);
				cutscene_peasant_4.prepareAsCSO(50, 79, 0, 2, 1, 0, 0, 0);
				cutscene_peasant_5.prepareAsCSO(65, 82, 0, 2, 1, 0, 0, 0);
				cutscene_peasant_6.prepareAsCSO(160, 82, 0, 1, 1, 0, 0, 0);
				cutscene_peasant_7.prepareAsCSO(177, 79, 0, 1, 1, 0, 0, 0);
				cutscene_peasant_8.prepareAsCSO(194, 77, 0, 1, 1, 0, 0, 0);
				cutscene_peasant_9.prepareAsCSO(211, 74, 0, 1, 1, 0, 0, 0);
				cutscene_peasant_10.prepareAsCSO(227, 71, 0, 1, 1, 0, 0, 0);
				break;
			case 709:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	cutscene_trogdor_1.renderAsCSO(false);
	cutscene_knight_1.renderAsCSO(false);
	cutscene_knight_2.renderAsCSO(false);
	cutscene_peasant_1.renderAsCSO(false);
	cutscene_peasant_2.renderAsCSO(false);
	cutscene_peasant_3.renderAsCSO(false);
	cutscene_peasant_4.renderAsCSO(false);
	cutscene_peasant_5.renderAsCSO(false);
	cutscene_peasant_6.renderAsCSO(false);
	cutscene_peasant_7.renderAsCSO(false);
	cutscene_peasant_8.renderAsCSO(false);
	cutscene_peasant_9.renderAsCSO(false);
	cutscene_peasant_10.renderAsCSO(false);
	renderText(text_14_cutscene, font_serif_white_9);
}

void cutscene_level_20() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 710:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_trogdor_flexing.isActive = false;
				cutscene_trogdor_flexing.prepareAsCSO(92, 72, 0, GM.bigHeadMode, 0, 0, 0, 0);
				break;
			case 729:
			case 747:
			case 765:
				cutscene_trogdor_flexing.setFrame(0);
				break;
			case 716:
			case 727:
			case 734:
			case 745:
			case 752:
			case 763:
			case 770:
				cutscene_trogdor_flexing.setFrame(1);
				break;
			case 718:
			case 725:
			case 736:
			case 743:
			case 754:
			case 761:
			case 772:
				cutscene_trogdor_flexing.setFrame(2);
				break;
			case 720:
			case 738:
			case 756:
			case 774:
				cutscene_trogdor_flexing.setFrame(3);
				break;
			case 779:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	cutscene_trogdor_flexing.renderAsCSO(false);
	renderText(text_15_cutscene, font_serif_white_9);
}

void cutscene_level_24() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 780:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_trogdor_1.isActive = false;
				cutscene_trogdor_fire.isActive = false;
				cutscene_peasant_1.isActive = false;
				cutscene_peasant_2.isActive = false;
				cutscene_peasant_3.isActive = false;
				cutscene_peasant_4.isActive = false;
				cutscene_peasant_5.isActive = false;
				cutscene_peasant_6.isActive = false;
				cutscene_peasant_7.isActive = false;
				cutscene_trogdor_1.prepareAsCSO(175, 72, 0, 0, 0, 0, 0, 0);
				cutscene_peasant_1.prepareAsCSO(28, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_2.prepareAsCSO(46, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_3.prepareAsCSO(65, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_4.prepareAsCSO(83, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_5.prepareAsCSO(102, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_6.prepareAsCSO(120, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_7.prepareAsCSO(138, 90, 1, 0, 0, 0, 0, 0);
				break;
			case 798:
				cutscene_trogdor_fire.prepareAsCSO(154, 83, 0, 0, 2, 0, 0, 0);
				break;
			case 801:
				cutscene_peasant_7.prepareAsCSO(138, 90, 0, 1, 0, 0, 0, 0);
				break;
			case 803:
				cutscene_peasant_7.setForm(3);
				cutscene_peasant_6.prepareAsCSO(120, 90, 0, 1, 0, 0, 0, 0);
				break;
			case 805:
				cutscene_peasant_6.setForm(3);
				cutscene_peasant_5.prepareAsCSO(102, 90, 0, 1, 0, 0, 0, 0);
				break;
			case 807:
				cutscene_trogdor_fire.isActive = false;
				cutscene_peasant_5.setForm(3);
				cutscene_peasant_4.prepareAsCSO(83, 90, 0, 1, 0, 0, 0, 0);
				break;
			case 809:
				cutscene_peasant_4.setForm(3);
				cutscene_peasant_3.prepareAsCSO(65, 90, 0, 1, 0, 0, 0, 0);
				break;
			case 811:
				cutscene_peasant_3.setForm(3);
				cutscene_peasant_2.prepareAsCSO(46, 90, 0, 1, 0, 0, 0, 0);
				break;
			case 813:
				cutscene_peasant_2.setForm(3);
				cutscene_peasant_1.prepareAsCSO(28, 90, 0, 1, 0, 0, 0, 0);
				break;
			case 815:
				cutscene_peasant_1.setForm(3);
				break;
			case 833:
			case 837:
			case 841:
			case 845:
			case 849:
				cutscene_trogdor_1.dstrect.y = 69;
				break;
			case 835:
			case 839:
			case 843:
			case 847:
				cutscene_trogdor_1.dstrect.y = 72;
				break;
			case 850:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	cutscene_trogdor_1.renderAsCSO(false);
	cutscene_peasant_1.renderAsCSO(false);
	cutscene_peasant_2.renderAsCSO(false);
	cutscene_peasant_3.renderAsCSO(false);
	cutscene_peasant_4.renderAsCSO(false);
	cutscene_peasant_5.renderAsCSO(false);
	cutscene_peasant_6.renderAsCSO(false);
	cutscene_peasant_7.renderAsCSO(false);
	cutscene_trogdor_fire.renderAsCSO(false);
	renderText(text_16_cutscene, font_serif_white_9);
}

void cutscene_level_30() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 853:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_peasant_1.isActive = false;
				cutscene_peasant_2.isActive = false;
				cutscene_trogdor_fire.isActive = false;
				break;
			case 860:
				cutscene_peasant_1.prepareAsCSO(17, 95, 1, 0, 0, 0, 3.2, 0);
				cutscene_peasant_2.prepareAsCSO(200, 95, 1, 0, 0, 0, -2.76, 0);
				break;
			case 885:
				cutscene_peasant_1.vel_x = 0;
				cutscene_peasant_2.vel_x = 0;
				break;
			case 894:
				cutscene_trogdor_fire.prepareAsCSO(114, 99, 0, 1, 2, 0, 0, 0);
				break;
			case 897:
				cutscene_peasant_2.prepareAsCSO(131, 95, 0, 1, 1, 0, 5, 0);
				break;
			case 903:
				cutscene_trogdor_fire.isActive = false;
				break;
			case 916:
			case 919:
			case 922:
				cutscene_peasant_1.dstrect.y = 92;
				break;
			case 917:
			case 920:
			case 923:
				cutscene_peasant_1.dstrect.y = 95;
				break;
			case 924:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	cutscene_peasant_1.renderAsCSO(false);
	cutscene_peasant_2.renderAsCSO(false);
	cutscene_trogdor_fire.renderAsCSO(false);
	renderText(text_17_cutscene, font_serif_white_9);
}

void cutscene_level_34() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 927:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_peasant_1.isActive = false;
				cutscene_peasant_2.isActive = false;
				cutscene_peasant_3.isActive = false;
				cutscene_peasant_4.isActive = false;
				cutscene_peasant_5.isActive = false;
				cutscene_peasant_6.isActive = false;
				cutscene_peasant_7.isActive = false;
				cutscene_trogdor_1.isActive = false;
				cutscene_trogdor_2.isActive = false;
				cutscene_peasant_1.prepareAsCSO(52, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_2.prepareAsCSO(70, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_3.prepareAsCSO(89, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_4.prepareAsCSO(107, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_5.prepareAsCSO(126, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_6.prepareAsCSO(144, 90, 1, 0, 0, 0, 0, 0);
				cutscene_peasant_7.prepareAsCSO(162, 90, 1, 0, 0, 0, 0, 0);
				break;
			case 931:
				cutscene_trogdor_1.prepareAsCSO(9, 87, 0, 1, 2, 0, 2, 0);
				break;
			case 936:
				cutscene_trogdor_2.prepareAsCSO(4, 101, 0, 1, 2, 0, 3.544, 0); // 202.0 / 57
				break;
			case 941:
				cutscene_trogdor_1.vel_x = 6.667; // 60.0 / 9
				break;
			case 950:
				cutscene_trogdor_1.vel_x = 1.667; // 5.0 / 3
				break;
			case 962:
				cutscene_trogdor_1.vel_x = 2.692; // 35.0 / 13
				break;
			case 975:
				cutscene_trogdor_1.vel_x = 5.455; // 60.0 / 11
				break;
			case 987:
				cutscene_trogdor_1.isActive = false;
				break;
			case 994:
				cutscene_trogdor_2.isActive = false;
				break;
			case 995:
				cutscene_peasant_2.dstrect.y = 88;
				cutscene_peasant_4.dstrect.y = 90;
				cutscene_peasant_5.dstrect.y = 90;
				cutscene_peasant_6.dstrect.y = 88;
				break;
			case 997:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
		if (g_frameState.frame <= 992) {
			switch ((g_frameState.frame - 927) % 6) {
				case 0:
					cutscene_peasant_1.dstrect.y = 88;
					cutscene_peasant_3.dstrect.y = 88;
					cutscene_peasant_4.dstrect.y = 90;
					cutscene_peasant_5.dstrect.y = 90;
					cutscene_peasant_7.dstrect.y = 88;
					break;
				case 2:
					cutscene_peasant_1.dstrect.y = 90;
					cutscene_peasant_2.dstrect.y = 88;
					cutscene_peasant_3.dstrect.y = 90;
					cutscene_peasant_6.dstrect.y = 88;
					cutscene_peasant_7.dstrect.y = 90;
					break;
				case 4:
					cutscene_peasant_2.dstrect.y = 90;
					cutscene_peasant_4.dstrect.y = 88;
					cutscene_peasant_5.dstrect.y = 88;
					cutscene_peasant_6.dstrect.y = 90;
					break;
				default:
					break;
			}
		}
	}
	cutscene_peasant_1.renderAsCSO(false);
	cutscene_peasant_2.renderAsCSO(false);
	cutscene_peasant_3.renderAsCSO(false);
	cutscene_peasant_4.renderAsCSO(false);
	cutscene_peasant_5.renderAsCSO(false);
	cutscene_peasant_6.renderAsCSO(false);
	cutscene_peasant_7.renderAsCSO(false);
	cutscene_trogdor_1.renderAsCSO(false);
	cutscene_trogdor_2.renderAsCSO(false);
	renderText(text_18_cutscene, font_serif_white_9);
}

void cutscene_level_38() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 1000:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_peasant_1.isActive = false;
				cutscene_peasant_2.isActive = false;
				cutscene_heart.isActive = false;
				cutscene_knight_1.isActive = false;
				cutscene_peasant_1.prepareAsCSO(190, 95, 1, 0, 0, 0, -2.732, 0);
				cutscene_peasant_2.prepareAsCSO(204, 95, 1, 0, 0, 0, -2.732, 0);
				cutscene_heart.prepareAsCSO(197, 85, 0, 0, 0, 0, -2.732, 0);
				break;
			case 1021:
				cutscene_knight_1.prepareAsCSO(224, 95, 1, 0, 4, 0, -8.316, 0);
				break;
			case 1040:
				cutscene_knight_1.vel_x = 0;
				break;
			case 1041:
				cutscene_peasant_1.vel_x = 0;
				cutscene_peasant_2.vel_x = 0;
				cutscene_heart.vel_x = 0;
				cutscene_knight_1.dstrect.x = 66;
				cutscene_knight_1.setForm(1);
				break;
			case 1046:
				cutscene_knight_1.vel_x = 9.867;
				cutscene_peasant_1.vel_x = 10.067;
				break;
			case 1062:
				cutscene_peasant_1.isActive = false;
				cutscene_knight_1.isActive = false;
				break;
			case 1066:
				cutscene_heart.animFrameTime = 1;
				break;
			case 1071:
				cutscene_heart.isActive = false;
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	cutscene_peasant_1.renderAsCSO(false);
	cutscene_peasant_2.renderAsCSO(false);
	cutscene_heart.renderAsCSO(false);
	cutscene_knight_1.renderAsCSO(false);
	renderText(text_19_cutscene, font_serif_white_9);
}

void cutscene_level_42() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 1076:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_cottage_1.isActive = false;
				cutscene_cottage_2.isActive = false;
				cutscene_cottage_1.prepareAsCSO(81, 79, 0, 3, 0, 0, 0, 0);
				cutscene_cottage_2.prepareAsCSO(131, 79, 0, 2, 0, 0, 0, 0);
				break;
			case 1147:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	cutscene_cottage_1.renderAsCSO(false);
	cutscene_cottage_2.renderAsCSO(false);
	renderText(text_20_cutscene, font_serif_white_9);
}

void cutscene_level_46_arrow_helper(SpriteInstance *arrowObj, Sint16 startingFrame) {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame - startingFrame) {
			case 0:
				cutscene_archer_1.setFrame(1);
				arrowObj->isActive = true;
				arrowObj->prepareAsCSO(225, 93, 0, 0, 0, 0, 0, 0); // was 223; changed since there's no outer screen frame
				break;
			case 3:
				cutscene_archer_1.setFrame(0);
				arrowObj->prepareAsCSO(199, 93, 0, 0, 0, 0, -18.343, 0);
				break;
			case 11:
				cutscene_knight_funnyjoke.setFrame(1);
				arrowObj->prepareAsCSO(84, 84, 1, 0, 0, 0, 0, 0);
				break;
			case 12:
				cutscene_knight_funnyjoke.setFrame(0);
				arrowObj->prepareAsCSO(100, 83, 2, 0, 0, 0, 0, 0);
				break;
			case 13:
				arrowObj->prepareAsCSO(124, 103, 3, 0, 0, 0, 0, 0);
				break;
			case 14:
				arrowObj->setPos(134, 119);
				break;
			case 15:
				arrowObj->isActive = false;
				break;
			default:
				break;
		}
	}
}

void cutscene_level_46() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 1153:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_knight_funnyjoke.isActive = false;
				cutscene_knight_1.isActive = false;
				cutscene_archer_1.isActive = false;
				cutscene_arrow_1.isActive = false;
				cutscene_arrow_2.isActive = false;
				cutscene_arrow_3.isActive = false;
				cutscene_knight_funnyjoke.prepareAsCSO(58, 91, 0, 0, 0, 0, 0, 0);
				break;
			case 1166:
				cutscene_archer_1.prepareAsCSO(248, 90, 0, 0, 0, 0, -3.6, 0); // was 246; changed since there's no outer screen frame
				break;
			case 1171:
				cutscene_archer_1.vel_x = 0;
				break;
			case 1212:
				cutscene_archer_1.vel_x = 9.5;
				break;
			case 1215:
				cutscene_archer_1.isActive = false;
				break;
			case 1216:
				cutscene_knight_funnyjoke.setFrame(2);
				break;
			case 1217:
				cutscene_knight_funnyjoke.isActive = false;
				cutscene_knight_1.prepareAsCSO(59, 93, 0, 1, 0, 0, 0, 0);
				break;
			case 1222:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
		cutscene_level_46_arrow_helper(&cutscene_arrow_1, 1173);
		cutscene_level_46_arrow_helper(&cutscene_arrow_2, 1180);
		cutscene_level_46_arrow_helper(&cutscene_arrow_3, 1187);
		cutscene_level_46_arrow_helper(&cutscene_arrow_1, 1194);
		cutscene_level_46_arrow_helper(&cutscene_arrow_2, 1201);
	}
	cutscene_knight_funnyjoke.renderAsCSO(false);
	cutscene_knight_1.renderAsCSO(false);
	cutscene_archer_1.renderAsCSO(false);
	cutscene_arrow_1.renderAsCSO(false);
	cutscene_arrow_2.renderAsCSO(false);
	cutscene_arrow_3.renderAsCSO(false);
	renderText(text_21_cutscene, font_serif_white_9);
}

void cutscene_level_50() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 1226:
				cutsceneIsPlaying = true;
				loadAndPlaySound(SFX_CUTSCENE);
				cutscene_trogdor_1.isActive = false;
				cutscene_trogdor_fire.isActive = false;
				cutscene_kerrek.isActive = false;
				cutscene_kerrek_smoked.isActive = false;
				cutscene_trogdor_1.prepareAsCSO(77, 90, 0, 1, 0, 0, 0, 0);
				cutscene_kerrek.prepareAsCSO(132, 75, 0, 0, 0, 0, 0, 0);
				break;
			case 1235:
				cutscene_kerrek.setFrame(1);
				break;
			case 1237:
				cutscene_kerrek.setFrame(0);
				break;
			case 1243:
				cutscene_kerrek.setFrame(1);
				break;
			case 1245:
				cutscene_kerrek.setFrame(0);
				break;
			case 1251:
				cutscene_kerrek.setFrame(1);
				break;
			case 1253:
				cutscene_kerrek.setFrame(0);
				break;
			case 1260:
				cutscene_trogdor_fire.prepareAsCSO(114, 99, 0, 1, 2, 0, 0, 0);
				cutscene_kerrek.setFrame(1);
				break;
			case 1262:
				cutscene_kerrek.setFrame(0);
				break;
			case 1267:
				cutscene_kerrek.prepareAsCSO(132, 75, 2, 0, 2, 0, 0, 0);
				break;
			case 1275:
				cutscene_trogdor_fire.isActive = false;
				break;
			case 1281:
				cutscene_kerrek.isActive = false;
				cutscene_kerrek_smoked.prepareAsCSO(136, 88, 0, 0, 0, 0, 0, 0);
				break;
			case 1282:
				cutscene_kerrek_smoked.setFrame(1);
				break;
			case 1287:
				cutscene_kerrek_smoked.prepareAsCSO(136, 106, 2, 0, 0, 0, 0, 0);
				break;
			case 1288:
			case 1290:
				cutscene_kerrek_smoked.prepareAsCSO(136, 116, 3, 0, 0, 0, 0, 0);
				break;
			case 1289:
				cutscene_kerrek_smoked.prepareAsCSO(135, 119, 4, 0, 0, 0, 0, 0);
				break;
			case 1291:
				cutscene_kerrek_smoked.prepareAsCSO(137, 120, 1, 0, 0, 0, 0, 0);
				break;
			case 1297:
				if (rand() % 100 < 50 * GM.sbVoiceMult) {
					loadAndPlaySound(SFX_SBKERREK);
				}
				break;
			case 1334:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	cutscene_trogdor_1.renderAsCSO(false);
	cutscene_trogdor_fire.renderAsCSO(false);
	cutscene_kerrek.renderAsCSO(false);
	cutscene_kerrek_smoked.renderAsCSO(false);
	renderText(text_22_cutscene, font_serif_white_9);
}

void cutscene_level_100() {
	if (g_frameState.atStartOfFrame) {
		switch (g_frameState.frame) {
			case 1337:
				cutsceneIsPlaying = true;
				cutscene_level_100_screen_counter = 0;
				cutscene_strong_bad.isActive = false;
				cutscene_trogdor_1.isActive = false;
				cutscene_peasant_1.isActive = false;
				cutscene_knight_1.isActive = false;
				cutscene_archer_1.isActive = false;
				cutscene_archer_2.isActive = false;
				cutscene_kerrek.isActive = false;
				cutscene_kerrek_smoked.isActive = false;
				cutscene_trogdor_ending.isActive = false;
				cutscene_strong_bad_ending.isActive = false;
				break;
			case 1347:
				cutscene_strong_bad.prepareAsCSO(220, 100, 0, 0, 1, 0, -3.372, 0);
				break;
			case 1349:
				if (rand() % 100 < 50 * GM.sbVoiceMult) {
					loadAndPlaySound(SFX_SBWIN);
				}
				break;
			case 1377:
				cutscene_strong_bad.prepareAsCSO(115, 99, 0, 1, 0, 0, 0, 0);
				break;
			case 1397:
				cutscene_level_100_screen_counter++;
				playMusic(MUSIC_ENDING_1, false, DEFAULT_VOLUME_GAME);
				cutscene_strong_bad.prepareAsCSO(115, 99, 0, 1, 3, 0, 0, 0);
				break;
			case 1415:
				cutscene_strong_bad.prepareAsCSO(115, 99, 0, 1, 0, 0, 0, 0);
				break;
			case 1423:
				cutscene_level_100_screen_counter++;
				cutscene_strong_bad.prepareAsCSO(115, 99, 1, 1, 3, 0, 0, 0);
				break;
			case 1432:
				cutscene_strong_bad.prepareAsCSO(115, 99, 0, 1, 0, 0, 0, 0);
				break;
			case 1437:
				cutscene_strong_bad.prepareAsCSO(115, 99, 1, 1, 3, 0, 0, 0);
				break;
			case 1440:
				cutscene_level_100_screen_counter++;
				break;
			case 1446:
				cutscene_strong_bad.prepareAsCSO(115, 99, 0, 1, 0, 0, 0, 0);
				break;
			case 1456:
				if (rand() % 100 < 50 * GM.sbVoiceMult) {
					loadAndPlaySound(SFX_SBWIN2);
				}
				break;
			case 1493:
				cutscene_strong_bad.isActive = false;
				break;
			case 1501:
				cutscene_level_100_screen_counter++;
				playMusic(MUSIC_ENDING_2, false, DEFAULT_VOLUME_GAME);
				break;
			case 1522:
				cutscene_level_100_screen_counter++;
				cutscene_trogdor_1.prepareAsCSO(107, 83, 0, 1, 0, 0, 0, 0);
				break;
			case 1543:
				cutscene_level_100_screen_counter++;
				cutscene_trogdor_1.isActive = false;
				cutscene_peasant_1.prepareAsCSO(115, 91, 0, 0, 0, 0, 0, 0);
				break;
			case 1562:
				cutscene_level_100_screen_counter++;
				cutscene_peasant_1.prepareAsCSO(115, 91, 1, 0, 0, 0, 0, 0);
				break;
			case 1582:
				cutscene_level_100_screen_counter++;
				cutscene_peasant_1.prepareAsCSO(115, 91, 0, 1, 0, 0, 0, 0);
				break;
			case 1601:
				cutscene_level_100_screen_counter++;
				cutscene_peasant_1.isActive = false;
				cutscene_knight_1.prepareAsCSO(117, 91, 0, 1, 0, 0, 0, 0);
				break;
			case 1621:
				cutscene_level_100_screen_counter++;
				cutscene_knight_1.prepareAsCSO(115, 91, 1, 0, 0, 0, 0, 0);
				break;
			case 1641:
				cutscene_level_100_screen_counter++;
				cutscene_knight_1.isActive = false;
				cutscene_archer_1.prepareAsCSO(106, 94, 1, 0, 0, 0, 0, 0);
				cutscene_archer_2.prepareAsCSO(106 + (double)cutscene_archer_1.spriteObj->dstrect.w, 94, 0, 1, 0, 0, 0, 0);
				break;
			case 1660:
				cutscene_level_100_screen_counter++;
				cutscene_archer_1.isActive = false;
				cutscene_archer_2.isActive = false;
				cutscene_kerrek.prepareAsCSO(106, 73, 0, 0, 0, 0, 0, 0);
				break;
			case 1662:
				cutscene_kerrek.prepareAsCSO(106, 73, 2, 0, 2, 0, 0, 0);
				break;
			case 1676:
				cutscene_kerrek.isActive = false;
				cutscene_kerrek_smoked.prepareAsCSO(110, 86, 0, 0, 0, 0, 0, 0);
				break;
			case 1677:
				cutscene_kerrek_smoked.setFrame(1);
				break;
			case 1681:
				cutscene_level_100_screen_counter++;
				cutscene_kerrek_smoked.isActive = false;
				cutscene_trogdor_ending.prepareAsCSO(90, 84, 0, GM.bigHeadMode, 0, 0, 0, 0);
				cutscene_strong_bad_ending.prepareAsCSO(138, 94, 0, 0, 0, 0, 0, 0);
				break;
			case 1716:
				cutsceneIsPlaying = false;
				break;
			default:
				break;
		}
	}
	switch (cutscene_level_100_screen_counter) {
		case 0:
			cutscene_strong_bad.renderAsCSO(false);
			break;
		case 1:
			cutscene_strong_bad.renderAsCSO(false);
			renderText(text_23_cutscene_1, font_serif_white_9);
			break;
		case 2:
			cutscene_strong_bad.renderAsCSO(false);
			renderText(text_23_cutscene_1, font_serif_white_9);
			renderText(text_23_cutscene_2, font_serif_white_9);
			break;
		case 3:
			cutscene_strong_bad.renderAsCSO(false);
			renderText(text_23_cutscene_1, font_serif_white_9);
			renderText(text_23_cutscene_2, font_serif_white_9);
			renderText(text_23_cutscene_3, font_serif_white_9);
			break;
		case 4:
			renderText(text_23_cutscene_4, font_serif_white_9);
			break;
		case 5:
			cutscene_trogdor_1.renderAsCSO(false);
			renderText(text_23_cutscene_5, font_serif_white_9);
			break;
		case 6:
			cutscene_peasant_1.renderAsCSO(false);
			renderText(text_23_cutscene_6, font_serif_white_9);
			break;
		case 7:
			cutscene_peasant_1.renderAsCSO(false);
			renderText(text_23_cutscene_7, font_serif_white_9);
			break;
		case 8:
			cutscene_peasant_1.renderAsCSO(false);
			renderText(text_23_cutscene_8, font_serif_white_9);
			break;
		case 9:
			cutscene_knight_1.renderAsCSO(false);
			renderText(text_23_cutscene_9, font_serif_white_9);
			break;
		case 10:
			cutscene_knight_1.renderAsCSO(false);
			renderText(text_23_cutscene_10, font_serif_white_9);
			break;
		case 11:
			cutscene_archer_1.renderAsCSO(false);
			cutscene_archer_2.renderAsCSO(false);
			renderText(text_23_cutscene_11, font_serif_white_9);
			renderText(text_23_cutscene_12, font_serif_white_9);
			break;
		case 12:
			cutscene_kerrek.renderAsCSO(false);
			cutscene_kerrek_smoked.renderAsCSO(false);
			renderText(text_23_cutscene_13, font_serif_white_9);
			renderText(text_23_cutscene_14, font_serif_white_9);
			break;
		case 13:
			cutscene_trogdor_ending.renderAsCSO(false);
			cutscene_strong_bad_ending.renderAsCSO(false);
			renderText(text_23_cutscene_15, font_serif_white_9);
			break;
		default:
			break;
	}
}