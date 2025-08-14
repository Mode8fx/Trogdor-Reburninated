#include "media_objects_init.h"
#include "text_objects.h"
#include "window.h"
#include "sound_logic.h"
#include "sprite_objects.h"
#include "config.h"
#include "general.h"
#include "input.h"
#include "include_fonts.h"
#include "include_graphics.h"
#include "include_sfx.h"

ifstream ifile;

void InitializeFontsAndText() {
	TTF_Init();

	setFont(&font_serif_white_14, serif_v01_ttf, serif_v01_ttf_len, 14, 14, TTF_STYLE_NORMAL, color_white, false);
	SET_TEXT("loading...", text_0_loading, font_serif_white_14,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_0_loading), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, text_0_loading));
	TTF_CloseFont(font_serif_white_14.font);

	setFont(&font_serif_white_6_mult, serif_v01_ttf, serif_v01_ttf_len, 8, 5, TTF_STYLE_NORMAL, color_white, false);
	setFont(&font_serif_white_8_mult, serif_v01_ttf, serif_v01_ttf_len, 8, 6.666, TTF_STYLE_NORMAL, color_white, false);
	setFont(&font_serif_red_6_mult, serif_v01_ttf, serif_v01_ttf_len, 8, 5, TTF_STYLE_NORMAL, color_red, false);
	setFont(&font_serif_red_8_mult, serif_v01_ttf, serif_v01_ttf_len, 8, 6.666, TTF_STYLE_NORMAL, color_red, false);
	initializeFont_numbers(&font_serif_white_6_mult);
	InitializeText_HomeScreen();
	TTF_CloseFont(font_serif_white_6_mult.font);
	TTF_CloseFont(font_serif_white_8_mult.font);
	TTF_CloseFont(font_serif_red_6_mult.font);
	TTF_CloseFont(font_serif_red_8_mult.font);

	setFont(&font_serif_white_8, serif_v01_ttf, serif_v01_ttf_len, 8, 5, TTF_STYLE_NORMAL, color_white, true);
	TTF_CloseFont(font_serif_white_8.font);

	//setFont(&font_serif_brown_6, serif_v01_ttf, serif_v01_ttf_len, 6, 6, TTF_STYLE_NORMAL, color_brown);
	//TTF_CloseFont(font_serif_brown_6.font);

	//setFont(&font_serif_brown_8, serif_v01_ttf, serif_v01_ttf_len, 8, 8, TTF_STYLE_NORMAL, color_brown);
	//TTF_CloseFont(font_serif_brown_8.font);

	//setFont(&font_serif_gray_6, serif_v01_ttf, serif_v01_ttf_len, 6, 6, TTF_STYLE_NORMAL, color_gray);
	//TTF_CloseFont(font_serif_gray_6.font);

	setFont(&font_serif_gray_12, serif_v01_ttf, serif_v01_ttf_len, 12, 12, TTF_STYLE_NORMAL, color_gray, false);
	SET_TEXT("LEVEL", text_9_level_gray, font_serif_gray_12,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_9_level_gray, 0.77) - 2, (111 + 1) * gameHiResMult);
	SET_TEXT("BEATEN!", text_9_beaten_gray, font_serif_gray_12,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_9_beaten_gray, 0.77) - 2, (132 + 1) * gameHiResMult);
	TTF_CloseFont(font_serif_gray_12.font);

	//setFont(&font_serif_orange_6, serif_v01_ttf, serif_v01_ttf_len, 6, 6, TTF_STYLE_NORMAL, color_orange);
	//TTF_CloseFont(font_serif_orange_6.font);

	setFont(&font_serif_red_6, serif_v01_ttf, serif_v01_ttf_len, 8, 6, TTF_STYLE_NORMAL, color_red, false);
	initializeFont_numbers(&font_serif_red_6);
	SET_TEXT("??????", text_4_score_val, font_serif_red_6,
		5 * gameHiResMult, 11 * gameHiResMult);
	SET_TEXT("??", text_4_mans_val, font_serif_red_6,
		230 * gameHiResMult, 1 * gameHiResMult);
	SET_TEXT("??", text_4_level_val, font_serif_red_6,
		230 * gameHiResMult, 11 * gameHiResMult);
	if (font_serif_red_6.size == 8) {
		text_4_score_val.dstrect.y -= 1;
		text_4_mans_val.dstrect.y -= 2;
		text_4_level_val.dstrect.y -= 1;
	}
	TTF_CloseFont(font_serif_red_6.font);

	//setFont(&font_serif_red_8, serif_v01_ttf, serif_v01_ttf_len, 8, 8, TTF_STYLE_NORMAL, color_red);
	//TTF_CloseFont(font_serif_red_8.font);

	setFont(&font_serif_red_12, serif_v01_ttf, serif_v01_ttf_len, 12, 12, TTF_STYLE_NORMAL, color_red, false);
	SET_TEXT("LEVEL", text_9_level_red, font_serif_red_12,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_9_level_red, 0.77), 111 * gameHiResMult);
	SET_TEXT("BEATEN!", text_9_beaten_red, font_serif_red_12,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_9_beaten_red, 0.77), 132 * gameHiResMult);
	TTF_CloseFont(font_serif_red_12.font);

	setFont(&font_serif_white_6, serif_v01_ttf, serif_v01_ttf_len, 6, 6, TTF_STYLE_NORMAL, color_white, false);
	InitializeText_PauseScreen();
	TTF_CloseFont(font_serif_white_6.font);

	setFont(&font_serif_white_9, serif_v01_ttf, serif_v01_ttf_len, 9, 9, TTF_STYLE_NORMAL, color_white, false);
	InitializeText_Cutscenes();
	TTF_CloseFont(font_serif_white_9.font);

	setFont(&font_serif_white_10, serif_v01_ttf, serif_v01_ttf_len, 10, 10, TTF_STYLE_NORMAL, color_white, false);
	SET_TEXT("nice work!", text_9_nice_work, font_serif_white_10,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_9_nice_work, 0.77), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_9_nice_work, 0.45));
	TTF_CloseFont(font_serif_white_10.font);

	setFont(&font_nokia_12, __29_NOKIA_5110_FontSet_ttf, __29_NOKIA_5110_FontSet_ttf_len, 12, 12, TTF_STYLE_NORMAL, color_white, true);
#if defined(PSP)
	SET_TEXT("presents", text_1_presents_1, font_nokia_12,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_1_presents_1), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_1_presents_1, 0.7));
	SET_TEXT(" ", text_1_presents_2, font_nokia_12,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_1_presents_2), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_1_presents_2, 0.8));
#else
	SET_TEXT("original game", text_1_presents_1, font_nokia_12,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_1_presents_1), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_1_presents_1, 0.23));
	SET_TEXT("by", text_1_presents_2, font_nokia_12,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_1_presents_2), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_1_presents_2, 0.3));
#endif
	TTF_CloseFont(font_nokia_12.font);

	//setFont(font_serif_2_bold_black_23, "fonts/54_serif_v01.ttf", 23, 23, TTF_STYLE_BOLD, color_black);
	//setFont(font_serif_2_bold_red_23, "fonts/54_serif_v01.ttf", 23, 23, TTF_STYLE_BOLD, color_red);
	setFont(&font_serif_2_red_6, serif_v01_ttf, serif_v01_ttf_len, 8, 6, TTF_STYLE_NORMAL, color_red, false);
	SET_TEXT("SCORE:", text_4_score, font_serif_2_red_6,
		5 * gameHiResMult, 1 * gameHiResMult);
	SET_TEXT("MANS:", text_4_mans, font_serif_2_red_6,
		200 * gameHiResMult, 1 * gameHiResMult);
	SET_TEXT("LEVEL:", text_4_level, font_serif_2_red_6,
		195 * gameHiResMult, 11 * gameHiResMult);
	if (font_serif_2_red_6.size == 8) {
		text_4_score.dstrect.y -= 2;
		text_4_mans.dstrect.x -= font_serif_2_red_6.size;
		text_4_mans.dstrect.y -= 2;
		text_4_level.dstrect.x -= font_serif_2_red_6.size;
		text_4_level.dstrect.y -= 1;
	}
	TTF_CloseFont(font_serif_2_red_6.font);

	//setFont(&font_serif_2_red_13, "fonts/54_serif_v01.ttf", 13, 13, TTF_STYLE_NORMAL, color_red);
	//TTF_CloseFont(font_serif_2_red_13.font);

	//SET_TEXT("nice work!", text_nice_work, font_serif_white_10,
	//	OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_nice_work), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, text_nice_work));
	//SET_TEXT("send'em", text_send_em, font_serif_gray_6,
	//	OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_send_em), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, text_send_em));
	//SET_TEXT("YE       OLDE       HI-SCORES", text_ye_olde_hi_scores, font_serif_2_red_13,
	//	OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_ye_olde_hi_scores), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, text_ye_olde_hi_scores));
	//SET_TEXT("1", text_one, font_serif_brown_8,
	//	OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_one), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, text_one));

	TTF_Quit();
}

void InitializeText_HomeScreen() {
	if (gameHiResMult < 2) {
		SET_TEXT(("(1/"+to_string(MAX_PAGE_NUM_LOWRES)+")").c_str(), text_3_page, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_page), 157 * gameHiResMult);
#if defined(PC)
		SET_TEXT("Use the arrows to control Trogdor", text_3_instructions_1, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_1), 59 * gameHiResMult);
#else
		SET_TEXT("Use the D-pad to control Trogdor", text_3_instructions_1, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_1), 59 * gameHiResMult);
#endif
		SET_TEXT("Stomp 10 peasants to achieve", text_3_instructions_2, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_2), 73 * gameHiResMult);
		SET_TEXT("burnination.", text_3_instructions_2a, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_2a), 87 * gameHiResMult);
		SET_TEXT("Burn all cottages to advance.", text_3_instructions_3, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_3), 101 * gameHiResMult);
		SET_TEXT("Avoid knights and archers!", text_3_instructions_4, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_4), 115 * gameHiResMult);
		SET_TEXT("Press " + INPUT_PAUSE + " to pause.", text_3_instructions_5, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_5), 129 * gameHiResMult);
		SET_TEXT("press " + INPUT_PAUSE + " to START", text_3_click_anywhere_to_start, font_serif_red_8_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_click_anywhere_to_start), 129 * gameHiResMult);
		SET_TEXT("Press " + INPUT_MISC + " for OPTIONS.", text_3_quit, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_quit), 143 * gameHiResMult);
		SET_TEXT("SECRET HINTS!!", text_3_hints_1, font_serif_red_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_1), 59 * gameHiResMult);
		SET_TEXT("-Don't let the peasants return", text_3_hints_2, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_2), 73 * gameHiResMult);
		SET_TEXT("to their cottages", text_3_hints_2a, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_2a), 87 * gameHiResMult);
		SET_TEXT("-Once you\'re burninating,", text_3_hints_3, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_3), 101 * gameHiResMult);
		SET_TEXT("you\'re invincible", text_3_hints_3a, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_3a), 115 * gameHiResMult);
		SET_TEXT("-Burninated peasants set their", text_3_hints_4, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_4), 129 * gameHiResMult);
		SET_TEXT("cottages on fire", text_3_hints_4a, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_4a), 143 * gameHiResMult);
		SET_TEXT("-Get an extra man every", text_3_hints_5, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_5), 87 * gameHiResMult);
		SET_TEXT("300 points", text_3_hints_5a, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_5a), 101 * gameHiResMult);
		SET_TEXT("-What\'s a treasure hut?!?!", text_3_hints_6, font_serif_red_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_6), 115 * gameHiResMult);
		SET_TEXT("- Secret Codes?!?!", text_3_hints_7, font_serif_red_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_7), 129 * gameHiResMult);
	} else {
		SET_TEXT(("(1/"+to_string(MAX_PAGE_NUM_HIRES)+")").c_str(), text_3_page, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_page), 157 * gameHiResMult);
#if defined(PC)
		SET_TEXT("Use the arrow keys to control Trogdor", text_3_instructions_1, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_1), 59 * gameHiResMult);
#else
		SET_TEXT("Use the D-pad to control Trogdor", text_3_instructions_1, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_1), 59 * gameHiResMult);
#endif
		SET_TEXT("Stomp 10 peasants to achieve burnination.", text_3_instructions_2, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_2), 73 * gameHiResMult);
		SET_TEXT("Burn all cottages to advance a level.", text_3_instructions_3, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_3), 87 * gameHiResMult);
		SET_TEXT("Avoid knights and archers!", text_3_instructions_4, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_4), 101 * gameHiResMult);
		SET_TEXT("Press " + INPUT_PAUSE + " to pause.", text_3_instructions_5, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_5), 115 * gameHiResMult);
		SET_TEXT("press " + INPUT_PAUSE + " to START", text_3_click_anywhere_to_start, font_serif_red_8_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_click_anywhere_to_start), 129 * gameHiResMult);
		SET_TEXT("Press " + INPUT_MISC + " for OPTIONS.", text_3_quit, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_quit), 143 * gameHiResMult);
		SET_TEXT("SECRET HINTS!!", text_3_hints_1, font_serif_red_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_1), 59 * gameHiResMult);
		SET_TEXT("-Don't let the peasants return to their cottages", text_3_hints_2, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_2), 73 * gameHiResMult);
		SET_TEXT("-Once you\'re burninating, you\'re invincible", text_3_hints_3, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_3), 87 * gameHiResMult);
		SET_TEXT("-Burninated peasants set their cottages on fire", text_3_hints_4, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_4), 101 * gameHiResMult);
		SET_TEXT("-Get an extra man every 300 points", text_3_hints_5, font_serif_white_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_5), 115 * gameHiResMult);
		SET_TEXT("-What\'s a treasure hut?!?!", text_3_hints_6, font_serif_red_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_6), 129 * gameHiResMult);
		SET_TEXT("- Secret Codes?!?!", text_3_hints_7, font_serif_red_6_mult,
			OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_7), 143 * gameHiResMult);
	}
	SET_TEXT("WHILE PAUSED OR", text_3_controls_1, font_serif_red_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_1), 59 * gameHiResMult);
	SET_TEXT("ON THIS SCREEN:", text_3_controls_2, font_serif_red_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_2), 73 * gameHiResMult);
#if defined(VITA) || defined(PSP)
	SET_TEXT("-Press Square to change overlay", text_3_controls_5, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_5), 101 * gameHiResMult);
	SET_TEXT(" ", text_3_controls_6, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_6), 115 * gameHiResMult);
	SET_TEXT("-Press Triangle to change scaling", text_3_controls_3, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_3), 129 * gameHiResMult);
	SET_TEXT(" ", text_3_controls_4, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_4), 143 * gameHiResMult);
#elif defined(WII)
	SET_TEXT("-Press A (Wii) / X (GC) to change overlay", text_3_controls_5, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_5), 101 * gameHiResMult);
	SET_TEXT(" ", text_3_controls_6, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_6), 115 * gameHiResMult);
	SET_TEXT("-Press Home (Wii) / Y (GC) to change scaling", text_3_controls_3, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_3), 129 * gameHiResMult);
	SET_TEXT(" ", text_3_controls_4, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_4), 143 * gameHiResMult);
#elif defined(PC)
	SET_TEXT("-Press C / X to change overlay", text_3_controls_5, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_5), 101 * gameHiResMult);
	SET_TEXT("-Press V / Y to change scaling", text_3_controls_3, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_3), 115 * gameHiResMult);
	SET_TEXT("-Press F11 / ESC / Right Stick", text_3_controls_4, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_4), 129 * gameHiResMult);
	SET_TEXT("for fullscreen", text_3_controls_6, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_6), 143 * gameHiResMult);
#else
	SET_TEXT("-Press X to change overlay", text_3_controls_5, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_5), 101 * gameHiResMult);
	SET_TEXT(" ", text_3_controls_6, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_6), 115 * gameHiResMult);
	SET_TEXT("-Press Y to change scaling", text_3_controls_3, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_3), 129 * gameHiResMult);
	SET_TEXT(" ", text_3_controls_4, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_controls_4), 143 * gameHiResMult);
#endif
#if defined(PC)
	SET_TEXT("HEY, KEYBOARD USERS!", text_3_keyboard_1, font_serif_red_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_keyboard_1), 59 * gameHiResMult);
	SET_TEXT("For cheat input:", text_3_keyboard_2, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_keyboard_2), 87 * gameHiResMult);
	SET_TEXT("D-Pad -> WASD/Arrows", text_3_keyboard_3, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_keyboard_3), 101 * gameHiResMult);
	SET_TEXT(" A -> Z      B -> X", text_3_keyboard_4, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_keyboard_4), 115 * gameHiResMult);
	SET_TEXT(" L -> Q      R -> E", text_3_keyboard_5, font_serif_white_6_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_keyboard_5), 129 * gameHiResMult);
#endif
	SET_TEXT("Continue", text_3_continue_1, font_serif_white_8_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_continue_1), 110 * gameHiResMult);
	SET_TEXT("New Game", text_3_continue_2, font_serif_white_8_mult,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_continue_2), 130 * gameHiResMult);
}

void InitializeText_Cutscenes() {
	/* 11: Level 4 Interlude */
	SET_TEXT("stompin' good!", text_11_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_11_cutscene, 0.48), 46 * gameHiResMult);
	/* 12: Level 8 Interlude */
	SET_TEXT("fry 'em up dan.", text_12_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_12_cutscene, 0.48), 46 * gameHiResMult);
	/* 13: Level 12 Interlude */
	SET_TEXT("parade of trogdors", text_13_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_13_cutscene, 0.48), 46 * gameHiResMult);
	/* 14: Level 16 Interlude */
	SET_TEXT("dancin' time", text_14_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_14_cutscene, 0.48), 46 * gameHiResMult);
	/* 15: Level 20 Interlude */
	SET_TEXT("flex it, troggie.", text_15_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_15_cutscene, 0.48), 46 * gameHiResMult);
	/* 16: Level 24 Interlude */
	SET_TEXT("peasant dominoes", text_16_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_16_cutscene, 0.48), 46 * gameHiResMult);
	/* 17: Level 30 Interlude */
	SET_TEXT("trogdor incognito", text_17_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_17_cutscene, 0.48), 46 * gameHiResMult);
	/* 18: Level 34 Interlude */
	SET_TEXT("go trogdor # 2!", text_18_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_18_cutscene, 0.48), 46 * gameHiResMult);
	/* 19: Level 38 Interlude */
	SET_TEXT("forbidden peasant love", text_19_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_19_cutscene, 0.48), 46 * gameHiResMult);
	/* 20: Level 42 Interlude */
	SET_TEXT("2 cottages", text_20_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_20_cutscene, 0.48), 46 * gameHiResMult);
	/* 21: Level 46 Interlude */
	SET_TEXT("a funny joke", text_21_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_21_cutscene, 0.48), 46 * gameHiResMult);
	/* 22: Level 50 Interlude */
	SET_TEXT("smote that kerrek!", text_22_cutscene, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_22_cutscene, 0.48), 46 * gameHiResMult);
	/* 23: Level 100 Interlude (Credits) */
	SET_TEXT("congratulations.", text_23_cutscene_1, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_1, 0.48), 46 * gameHiResMult);
	SET_TEXT("you got", text_23_cutscene_2, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_2, 0.48), 57 * gameHiResMult);
	SET_TEXT("good score", text_23_cutscene_3, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_3, 0.48), 68 * gameHiResMult);
	SET_TEXT("cast", text_23_cutscene_4, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_4, 0.48), 46 * gameHiResMult);
	SET_TEXT("trogdor", text_23_cutscene_5, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_5, 0.48), 46 * gameHiResMult);
	SET_TEXT("perez", text_23_cutscene_6, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_6, 0.48), 46 * gameHiResMult);
	SET_TEXT("hackworth", text_23_cutscene_7, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_7, 0.48), 46 * gameHiResMult);
	SET_TEXT("\'the steve\'", text_23_cutscene_8, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_8, 0.48), 46 * gameHiResMult);
	SET_TEXT("the blue knight", text_23_cutscene_9, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_9, 0.48), 46 * gameHiResMult);
	SET_TEXT("the red knight", text_23_cutscene_10, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_10, 0.48), 46 * gameHiResMult);
	SET_TEXT("the siamese", text_23_cutscene_11, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_11, 0.48), 46 * gameHiResMult);
	SET_TEXT("archers", text_23_cutscene_12, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_12, 0.48), 57 * gameHiResMult);
	SET_TEXT("and Wordly Wise", text_23_cutscene_13, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_13, 0.48), 46 * gameHiResMult);
	SET_TEXT("as The Kerrek", text_23_cutscene_14, font_serif_white_9,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_23_cutscene_14, 0.48), 57 * gameHiResMult);
	SET_TEXT("keep playing!", text_23_cutscene_15, font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_15), 46 * gameHiResMult);
}

void InitializeText_PauseScreen() {
	SET_TEXT("paused", text_4_paused_1, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_1), 130 * gameHiResMult);
#if defined(WII)
	SET_TEXT("press 'START' to resume", text_4_paused_2, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_2), 145 * gameHiResMult);
	SET_TEXT("press 'SELECT/Z' to quit", text_4_paused_3, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_3), 160 * gameHiResMult);
#elif defined(GAMECUBE)
	SET_TEXT("press 'START' to resume", text_4_paused_2, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_2), 145 * gameHiResMult);
	SET_TEXT("press 'Z' to quit", text_4_paused_3, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_3), 160 * gameHiResMult);
#elif defined(VITA) || defined(PSP)
	SET_TEXT("press 'START' to resume", text_4_paused_2, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_2), 145 * gameHiResMult);
	SET_TEXT("press 'SELECT' to quit", text_4_paused_3, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_3), 160 * gameHiResMult);
#elif defined(SWITCH)
	SET_TEXT("press '+' to resume", text_4_paused_2, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_2), 145 * gameHiResMult);
	SET_TEXT("press '-' to quit", text_4_paused_3, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_3), 160 * gameHiResMult);
#elif defined(XBOX)
	SET_TEXT("press 'START' to resume", text_4_paused_2, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_2), 145 * gameHiResMult);
	SET_TEXT("press 'BACK' to quit", text_4_paused_3, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_3), 160 * gameHiResMult);
#elif defined(PC)
	SET_TEXT("press 'ENTER/START' to resume", text_4_paused_2, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_2), 145 * gameHiResMult);
	SET_TEXT("press 'BACKSPACE/SELECT' to quit", text_4_paused_3, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_3), 160 * gameHiResMult);
#else
	SET_TEXT("press 'START' to resume", text_4_paused_2, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_2), 145 * gameHiResMult);
	SET_TEXT("press 'SELECT' to quit", text_4_paused_3, font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_3), 160 * gameHiResMult);
#endif
}

void InitializeText_OptionsMenu(FontObject *fontObj) {
	//setText("PLACEHOLDER", &textVar, fontObj);
}

void InitializeMusic() {
}

void InitializeSFX() {
#if defined(OGG_SFX)
	sfx_burn_hut.path = "sfx/burn_hut.ogg";
	sfx_goldget.path = "sfx/trog_goldget.ogg";
	sfx_peasantscream.path = "sfx/trog_peasantscream.ogg";
	sfx_sfx2.path = "sfx/trog_sfx2.ogg";
	sfx_trogador.path = "sfx/trogador.ogg";
	sfx_arrow.path = "sfx/trog_arrow.ogg";
	sfx_squish.path = "sfx/squish.ogg";
	sfx_death.path = "sfx/death.ogg";
	sfx_kick.path = "sfx/kick.ogg";
	sfx_burninate.path = "sfx/burninate.ogg";
	sfx_cutscene.path = "sfx/cutscene.ogg";
	sfx_gameover.path = "sfx/gameover.ogg";
	sfx_speedincreased.path = "sfx/speedincreased.ogg";
	sfx_sb1.path = "sfx/trog_sb1.ogg";
	sfx_sb2.path = "sfx/trog_sb2.ogg";
	sfx_sb3.path = "sfx/trog_sb3.ogg";
	sfx_sb4.path = "sfx/trog_sb4.ogg";
	sfx_sb5.path = "sfx/trog_sb5.ogg";
	sfx_sb6.path = "sfx/trog_sb6.ogg";
	sfx_sb7.path = "sfx/trog_sb7.ogg";
	sfx_sbarch.path = "sfx/trog_sbarch.ogg";
	sfx_sbarchend.path = "sfx/trog_sbarchend.ogg";
	sfx_sbbest.path = "sfx/trog_sbbest.ogg";
	sfx_sbdooj.path = "sfx/trog_sbdooj.ogg";
	sfx_sbgameover.path = "sfx/trog_sbgameover.ogg";
	sfx_sbkerrek.path = "sfx/trog_sbkerrek.ogg";
	sfx_sblevelbeat.path = "sfx/trog_sblevelbeat.ogg";
	sfx_sbscore.path = "sfx/trog_sbscore.ogg";
	sfx_sbsecret.path = "sfx/trog_sbsecret.ogg";
	sfx_sbsquish1.path = "sfx/trog_sbsquish1.ogg";
	sfx_sbsquish2.path = "sfx/trog_sbsquish2.ogg";
	sfx_sbwin.path = "sfx/trog_sbwin.ogg";
	sfx_sbwin2.path = "sfx/trog_sbwin2.ogg";
	sfx_sbworst.path = "sfx/trog_sbworst.ogg";
	sfx_sbdooj_short.path = "sfx/sbdooj_short.ogg";
	sfx_itsover.path = "sfx/soundboard_itsover.ogg";
#else
	sfx_burn_hut.path = "sfx/burn_hut.wav";
	sfx_goldget.path = "sfx/trog_goldget.wav";
	sfx_peasantscream.path = "sfx/trog_peasantscream.wav";
	sfx_sfx2.path = "sfx/trog_sfx2.wav";
	sfx_trogador.path = "sfx/trogador.wav";
	sfx_arrow.path = "sfx/trog_arrow.wav";
	sfx_squish.path = "sfx/squish.wav";
	sfx_death.path = "sfx/death.wav";
	sfx_kick.path = "sfx/kick.wav";
	sfx_burninate.path = "sfx/burninate.wav";
	sfx_cutscene.path = "sfx/cutscene.wav";
	sfx_gameover.path = "sfx/gameover.wav";
	sfx_speedincreased.path = "sfx/speedincreased.wav";
	sfx_sb1.path = "sfx/trog_sb1.wav";
	sfx_sb2.path = "sfx/trog_sb2.wav";
	sfx_sb3.path = "sfx/trog_sb3.wav";
	sfx_sb4.path = "sfx/trog_sb4.wav";
	sfx_sb5.path = "sfx/trog_sb5.wav";
	sfx_sb6.path = "sfx/trog_sb6.wav";
	sfx_sb7.path = "sfx/trog_sb7.wav";
	sfx_sbarch.path = "sfx/trog_sbarch.wav";
	sfx_sbarchend.path = "sfx/trog_sbarchend.wav";
	sfx_sbbest.path = "sfx/trog_sbbest.wav";
	sfx_sbdooj.path = "sfx/trog_sbdooj.wav";
	sfx_sbgameover.path = "sfx/trog_sbgameover.wav";
	sfx_sbkerrek.path = "sfx/trog_sbkerrek.wav";
	sfx_sblevelbeat.path = "sfx/trog_sblevelbeat.wav";
	sfx_sbscore.path = "sfx/trog_sbscore.wav";
	sfx_sbsecret.path = "sfx/trog_sbsecret.wav";
	sfx_sbsquish1.path = "sfx/trog_sbsquish1.wav";
	sfx_sbsquish2.path = "sfx/trog_sbsquish2.wav";
	sfx_sbwin.path = "sfx/trog_sbwin.wav";
	sfx_sbwin2.path = "sfx/trog_sbwin2.wav";
	sfx_sbworst.path = "sfx/trog_sbworst.wav";
	sfx_sbdooj_short.path = "sfx/sbdooj_short.wav";
	sfx_itsover.path = "sfx/soundboard_itsover.wav";
#endif
	sfxArr[0] = &sfx_burn_hut;
	makeSoundStatic(sfxArr[0]);
	sfxArr[1] = &sfx_goldget;
	makeSoundStatic(sfxArr[1]);
	sfxArr[2] = &sfx_peasantscream;
	makeSoundStatic(sfxArr[2]);
	sfxArr[3] = &sfx_sfx2;
	sfxArr[4] = &sfx_trogador;
	sfxArr[5] = &sfx_arrow;
	makeSoundStatic(sfxArr[5]);
	sfxArr[6] = &sfx_squish;
	makeSoundStatic(sfxArr[6]);
	sfxArr[7] = &sfx_death;
	sfxArr[8] = &sfx_kick;
	sfxArr[9] = &sfx_burninate;
	sfxArr[10] = &sfx_cutscene;
	sfxArr[11] = &sfx_gameover;
	sfxArr[12] = &sfx_speedincreased;
	sfxArr_strongBad[0] = &sfx_sb1;
	sfxArr_strongBad[1] = &sfx_sb2;
	sfxArr_strongBad[2] = &sfx_sb3;
	sfxArr_strongBad[3] = &sfx_sb4;
	sfxArr_strongBad[4] = &sfx_sb5;
	sfxArr_strongBad[5] = &sfx_sb6;
	sfxArr_strongBad[6] = &sfx_sb7;
	sfxArr_strongBad[7] = &sfx_sbarch;
	sfxArr_strongBad[8] = &sfx_sbarchend;
	sfxArr_strongBad[9] = &sfx_sbbest;
	sfxArr_strongBad[10] = &sfx_sbdooj;
	sfxArr_strongBad[11] = &sfx_sbgameover;
	sfxArr_strongBad[12] = &sfx_sbkerrek;
	sfxArr_strongBad[13] = &sfx_sblevelbeat;
	sfxArr_strongBad[14] = &sfx_sbscore;
	sfxArr_strongBad[15] = &sfx_sbsecret;
	sfxArr_strongBad[16] = &sfx_sbsquish1;
	sfxArr_strongBad[17] = &sfx_sbsquish2;
	sfxArr_strongBad[18] = &sfx_sbwin;
	sfxArr_strongBad[19] = &sfx_sbwin2;
	sfxArr_strongBad[20] = &sfx_sbworst;
	sfxArr_strongBad[21] = &sfx_sbdooj_short;
	sfxArr_strongBad[22] = &sfx_itsover;
	for (i = 0; i < NUM_SOUND_EFFECTS_STRONG_BAD; i++) {
		sfxArr_strongBad[i]->type = 1;
	}
#if defined(PRELOAD_SOUNDS)
	for (i = 0; i < NUM_SOUND_EFFECTS_SFX; i++) {
		makeSoundStatic(sfxArr[i]);
	}
	for (i = 0; i < NUM_SOUND_EFFECTS_STRONG_BAD; i++) {
		makeSoundStatic(sfxArr_strongBad[i]);
	}
#endif
	for (i = 0; i < NUM_SOUND_EFFECTS_SFX; i++) {
		exceptMissingFile(sfxArr[i]->path);
	}
	for (i = 0; i < NUM_SOUND_EFFECTS_STRONG_BAD; i++) {
		exceptMissingFile(sfxArr_strongBad[i]->path);
	}
}

void destroySprite(SpriteObject *sprite) {
	for (i = 0; i < sprite->numFrames; i++) {
		for (j = 0; j < sprite->numForms; j++) {
			if (&sprite->sub[i][j] != NULL) {
#if !defined(SDL1)
				SDL_DestroyTexture(sprite->sub[i][j].texture);
#else
				SDL_FreeSurface(sprite->sub[i][j].surface);
#endif
			}
		}
		if (sprite->sub[i] != NULL) {
			free(sprite->sub[i]);
			sprite->sub[i] = NULL;
		}
	}
}

void InitializeSpritesPart1() {
	PREPARE_SPRITE_MENU(sprite_videlectrix_logo, videlectrix_logo_big_img, videlectrix_logo_big_img_len, 0, 0, 1, 1, 1);
	sprite_videlectrix_logo_ins = SpriteInstance(&sprite_videlectrix_logo, 0, 0);
	sprite_videlectrix_logo_ins.setPos((windowWidth - (sprite_videlectrix_logo_ins.dstrect.w * screenScale_menu)) / 2 - menuToWindowDstRect.x, (windowHeight - (sprite_videlectrix_logo_ins.dstrect.h * screenScale_menu)) / 2 - menuToWindowDstRect.y);
	PREPARE_SPRITE_OPAQUE(sprite_title_screen, title_screen_img, title_screen_img_len, 0, 0, 1, 1, 1);
	sprite_title_screen_ins = SpriteInstance(&sprite_title_screen, 0, 0);
	PREPARE_SPRITE(sprite_trogdor_logo, trogdor_logo_img, trogdor_logo_img_len,
		OBJ_FRAME_TO_MID_SCREEN_X(gameWidth, sprite_trogdor_logo), 15, 1, 1, 1);
	sprite_trogdor_logo_ins = SpriteInstance(&sprite_trogdor_logo, 0, 0);
	PREPARE_SPRITE_BG(sprite_level_background_1, bg_1_img, bg_1_img_len, 0, 25);
	PREPARE_SPRITE_BG(sprite_level_background_2, bg_2_img, bg_2_img_len, 0, 25);
	PREPARE_SPRITE_BG(sprite_level_background_3, bg_3_img, bg_3_img_len, 0, 25);
	PREPARE_SPRITE_BG(sprite_level_background_4, bg_4_img, bg_4_img_len, 0, 25);
	PREPARE_SPRITE_BG(sprite_level_background_th, bg_treasure_hut_img, bg_treasure_hut_img_len, 0, 25);
	PREPARE_SPRITE(sprite_burnination_meter_full, bm_full_img, bm_full_img_len,
		OBJ_FRAME_TO_MID_SCREEN_X(gameWidth, sprite_burnination_meter_full), 8, 1, 1, 1);
	PREPARE_SPRITE(sprite_burnination_meter_empty, bm_empty_img, bm_empty_img_len,
		OBJ_FRAME_TO_MID_SCREEN_X(gameWidth, sprite_burnination_meter_empty), 8, 1, 1, 1);
	sprite_burnination_meter_empty_ins = SpriteInstance(&sprite_burnination_meter_empty, 0, 0);
	PREPARE_SPRITE(sprite_end_of_level_flash, end_of_level_flash_img, end_of_level_flash_img_len, 65, 53, 1, 1, 1);
	sprite_end_of_level_flash_ins = SpriteInstance(&sprite_end_of_level_flash, 0, 0);
	PREPARE_SPRITE(sprite_death_message, death_message_img, death_message_img_len,
		OBJ_FRAME_TO_MID_SCREEN_X(gameWidth, sprite_death_message), OBJ_FRAME_TO_MID_SCREEN_Y(gameHeight, sprite_death_message), 2, 5, 1);
	PREPARE_SPRITE(sprite_burninate_text, burninate_text_img, burninate_text_img_len,
		OBJ_FRAME_TO_MID_SCREEN_X(gameWidth, sprite_burninate_text), OBJ_FRAME_TO_MID_SCREEN_Y(gameHeight, sprite_burninate_text), 1, 1, 1);
	PREPARE_SPRITE(sprite_burninate_fire, burninate_message_fire_img, burninate_message_fire_img_len,
		OBJ_FRAME_TO_MID_SCREEN_X(gameWidth, sprite_burninate_fire), OBJ_FRAME_TO_MID_SCREEN_Y(gameHeight, sprite_burninate_fire), 1, 12, 1);
	PREPARE_SPRITE(sprite_level_beaten_trogdor, level_beaten_trogdor_scaled_img, level_beaten_trogdor_scaled_img_len, -5, 41, 1, 1, 1);
	destroySprite(&sprite_level_beaten_smoke);
	if (gameHiResMult < 1.6) {
		PREPARE_SPRITE_NO_OFFSET(sprite_level_beaten_smoke, level_beaten_smoke_small_img, level_beaten_smoke_small_img_len, 100, 100, 8, 4, 1);
	} else {
		PREPARE_SPRITE_NO_OFFSET(sprite_level_beaten_smoke, level_beaten_smoke_img, level_beaten_smoke_img_len, 100, 100, 8, 4, 0.6667);
	}
	PREPARE_SPRITE(sprite_game_over_trogdor, game_over_trogdor_img, game_over_trogdor_img_len, -13, 75, 1, 1, 1);
#if defined(THREEDS) || defined(PSP)
	PREPARE_SPRITE_OPAQUE(sprite_overlay_basement_top, basement_top_240p_img, basement_top_240p_img_len, 0, 0, 1, 1, 1);
	sprite_overlay_basement_top_ins = SpriteInstance(&sprite_overlay_basement_top, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_basement_bottom, basement_bottom_240p_img, basement_bottom_240p_img_len, 0, 210, 1, 1, 1);
	sprite_overlay_basement_bottom_ins = SpriteInstance(&sprite_overlay_basement_bottom, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_basement_left, basement_left_240p_img, basement_left_240p_img_len, 0, 30, 1, 1, 1);
	sprite_overlay_basement_left_ins = SpriteInstance(&sprite_overlay_basement_left, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_basement_right, basement_right_240p_img, basement_right_240p_img_len, 285, 30, 1, 1, 1);
	sprite_overlay_basement_right_ins = SpriteInstance(&sprite_overlay_basement_right, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_compy_top, compy_top_240p_img, compy_top_240p_img_len, 0, 0, 1, 1, 1);
	sprite_overlay_compy_top_ins = SpriteInstance(&sprite_overlay_compy_top, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_compy_bottom, compy_bottom_240p_img, compy_bottom_240p_img_len, 0, 210, 1, 1, 1);
	sprite_overlay_compy_bottom_ins = SpriteInstance(&sprite_overlay_compy_bottom, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_compy_left, compy_left_240p_img, compy_left_240p_img_len, 0, 30, 1, 1, 1);
	sprite_overlay_compy_left_ins = SpriteInstance(&sprite_overlay_compy_left, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_compy_right, compy_right_240p_img, compy_right_240p_img_len, 285, 30, 1, 1, 1);
	sprite_overlay_compy_right_ins = SpriteInstance(&sprite_overlay_compy_right, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_strong_badia_top, strong_badia_top_240p_img, strong_badia_top_240p_img_len, 0, 0, 1, 1, 1);
	sprite_overlay_strong_badia_top_ins = SpriteInstance(&sprite_overlay_strong_badia_top, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_strong_badia_bottom, strong_badia_bottom_240p_img, strong_badia_bottom_240p_img_len, 0, 210, 1, 1, 1);
	sprite_overlay_strong_badia_bottom_ins = SpriteInstance(&sprite_overlay_strong_badia_bottom, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_strong_badia_left, strong_badia_left_240p_img, strong_badia_left_240p_img_len, 0, 30, 1, 1, 1);
	sprite_overlay_strong_badia_left_ins = SpriteInstance(&sprite_overlay_strong_badia_left, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_strong_badia_right, strong_badia_right_240p_img, strong_badia_right_240p_img_len, 285, 30, 1, 1, 1);
	sprite_overlay_strong_badia_right_ins = SpriteInstance(&sprite_overlay_strong_badia_right, 0, 0);
#else
	PREPARE_SPRITE_OPAQUE(sprite_overlay_basement_top, basement_top_img, basement_top_img_len, 0, 0, 1, 1, 0.5);
	sprite_overlay_basement_top_ins = SpriteInstance(&sprite_overlay_basement_top, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_basement_bottom, basement_bottom_img, basement_bottom_img_len, 0, 210, 1, 1, 0.5);
	sprite_overlay_basement_bottom_ins = SpriteInstance(&sprite_overlay_basement_bottom, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_basement_left, basement_left_img, basement_left_img_len, 0, 30, 1, 1, 0.5);
	sprite_overlay_basement_left_ins = SpriteInstance(&sprite_overlay_basement_left, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_basement_right, basement_right_img, basement_right_img_len, 285, 30, 1, 1, 0.5);
	sprite_overlay_basement_right_ins = SpriteInstance(&sprite_overlay_basement_right, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_compy_top, compy_top_img, compy_top_img_len, 0, 0, 1, 1, 0.5);
	sprite_overlay_compy_top_ins = SpriteInstance(&sprite_overlay_compy_top, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_compy_bottom, compy_bottom_img, compy_bottom_img_len, 0, 210, 1, 1, 0.5);
	sprite_overlay_compy_bottom_ins = SpriteInstance(&sprite_overlay_compy_bottom, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_compy_left, compy_left_img, compy_left_img_len, 0, 30, 1, 1, 0.5);
	sprite_overlay_compy_left_ins = SpriteInstance(&sprite_overlay_compy_left, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_compy_right, compy_right_img, compy_right_img_len, 285, 30, 1, 1, 0.5);
	sprite_overlay_compy_right_ins = SpriteInstance(&sprite_overlay_compy_right, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_strong_badia_top, strong_badia_top_img, strong_badia_top_img_len, 0, 0, 1, 1, 0.5);
	sprite_overlay_strong_badia_top_ins = SpriteInstance(&sprite_overlay_strong_badia_top, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_strong_badia_bottom, strong_badia_bottom_img, strong_badia_bottom_img_len, 0, 210, 1, 1, 0.5);
	sprite_overlay_strong_badia_bottom_ins = SpriteInstance(&sprite_overlay_strong_badia_bottom, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_strong_badia_left, strong_badia_left_img, strong_badia_left_img_len, 0, 30, 1, 1, 0.5);
	sprite_overlay_strong_badia_left_ins = SpriteInstance(&sprite_overlay_strong_badia_left, 0, 0);
	PREPARE_SPRITE_OPAQUE(sprite_overlay_strong_badia_right, strong_badia_right_img, strong_badia_right_img_len, 285, 30, 1, 1, 0.5);
	sprite_overlay_strong_badia_right_ins = SpriteInstance(&sprite_overlay_strong_badia_right, 0, 0);
#endif
	divider_level_beaten_rect = { 0, 25, gameWidth, 2 };
}

void InitializeSpritesPart2() {
	PREPARE_SPRITE(sprite_trogdor, trogdor_img, trogdor_img_len, 0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_trogdor_bighead, trogdor_bighead_img, trogdor_bighead_img_len, 0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_cottage, cottage_img, cottage_img_len, 0, 0, 2, 4, 1);
	PREPARE_SPRITE(sprite_cottage_fire, cottage_fire_img, cottage_fire_img_len, 0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_peasantometer_icon, peasantometer_img, peasantometer_img_len, 0, 3, 2, 1, 1);
	sprite_peasantometer_icon_init_x = (Uint8)(gameWidth * 66 / gameWidth);
	sprite_peasantometer_icon_step = (int)(sprite_peasantometer_icon.dstrect.w * 1.5);
	PREPARE_SPRITE(sprite_archer, archer_img, archer_img_len, 0, 0, 2, 2, 1);
	PREPARE_SPRITE(sprite_arrow, arrow_img, arrow_img_len, 0, 0, 1, 2, 1);
	PREPARE_SPRITE(sprite_trogdor_fire, trogdor_fire_img, trogdor_fire_img_len, 0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_trogdor_dead, trogdor_dead_img, trogdor_dead_img_len, 0, 0, 2, 2, 1);
	PREPARE_SPRITE(sprite_knight, knight_img, knight_img_len, 0, 0, 6, 2, 1);
	PREPARE_SPRITE(sprite_peasant, peasant_img, peasant_img_len, 0, 0, 2, 4, 1);
	destroySprite(&sprite_end_of_level_trogdor);
	if (gameHiResMult < 1.6) {
		PREPARE_SPRITE(sprite_end_of_level_trogdor, end_of_level_trogdor_img, end_of_level_trogdor_img_len,
			OBJ_TO_SCREEN_AT_FRACTION_X(gameWidth, sprite_end_of_level_trogdor, 0.476), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHeight, sprite_end_of_level_trogdor, 0.6), 1, 2, 2);
	} else { // TODO: this could be polished a bit further for (1.6 <= gameHiResMult < 2)
		PREPARE_SPRITE(sprite_end_of_level_trogdor, end_of_level_trogdor_img, end_of_level_trogdor_img_len,
			OBJ_TO_SCREEN_AT_FRACTION_X(gameWidth, sprite_end_of_level_trogdor, 0.476), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHeight, sprite_end_of_level_trogdor, 0.6), 1, 2, 1.5);
	}
	PREPARE_SPRITE(sprite_loot, loot_img, loot_img_len, 0, 0, 1, 1, 1);
	PREPARE_SPRITE(sprite_trogdor_flexing, trogdor_flexing_img, trogdor_flexing_img_len, 0, 0, 4, 2, 1);
	PREPARE_SPRITE(sprite_trogdor_ending, trogdor_ending_img, trogdor_ending_img_len, 0, 0, 1, 2, 1);
	PREPARE_SPRITE(sprite_heart, heart_img, heart_img_len, 0, 0, 5, 1, 1);
	PREPARE_SPRITE(sprite_knight_funnyjoke, knight_funnyjoke_img, knight_funnyjoke_img_len, 0, 0, 3, 1, 1);
	PREPARE_SPRITE(sprite_arrow_funnyjoke, arrow_funnyjoke_img, arrow_funnyjoke_img_len, 0, 0, 4, 1, 1);
	PREPARE_SPRITE(sprite_kerrek, kerrek_img, kerrek_img_len, 0, 0, 9, 1, 1);
	PREPARE_SPRITE(sprite_kerrek_smoked, kerrek_smoked_img, kerrek_smoked_img_len, 0, 0, 5, 1, 1);
	PREPARE_SPRITE(sprite_strong_bad, strong_bad_img, strong_bad_img_len, 0, 0, 2, 2, 1);
	PREPARE_SPRITE(sprite_strong_bad_ending, strong_bad_ending_img, strong_bad_ending_img_len, 0, 0, 1, 1, 1);
	PREPARE_SPRITE(sprite_cursor, menu_cursor_img, menu_cursor_img_len, 0, 0, 1, 1, 1);
	PREPARE_SPRITE_MENU(sprite_menu_cursor, menu_cursor_img, menu_cursor_img_len, 0, 0, 1, 1, 1);
#if defined(THREEDS) || defined(PSP)
	PREPARE_SPRITE_MENU(sprite_menu_background, options_menu_240p_img, options_menu_240p_img_len, 0, 0, 1, 1, 1);
#else
	PREPARE_SPRITE_MENU(sprite_menu_background, options_menu_img, options_menu_img_len, 0, 0, 1, 1, 0.5);
#endif
	sprite_menu_background_ins = SpriteInstance(&sprite_menu_background, 0, 0);
	// PREPARE_SPRITE(sprite_game_over_banner, game_over_banner_img, game_over_banner_img_len, 0, 0, 1, 1, 1);
	PREPARE_SPRITE(sprite_game_over_text, game_over_text_img, game_over_text_img_len, 0, 0, 1, 5, 1);
	PREPARE_SPRITE(sprite_game_over_jonathan_howe, jonathan_howe_img, jonathan_howe_img_len, 0, 0, 1, 6, 1);
}

void exceptMissingFile(const char *path) {
#if defined(PC)
	ifile.open(path);
	if (!ifile) {
		throw(path);
	}
	ifile.close();
#endif
}

void destroyAllSprites() {
	destroySprite(&sprite_videlectrix_logo);
	destroySprite(&sprite_title_screen);
	destroySprite(&sprite_trogdor_logo);
	destroySprite(&sprite_level_background_1);
	destroySprite(&sprite_level_background_2);
	destroySprite(&sprite_level_background_3);
	destroySprite(&sprite_level_background_4);
	destroySprite(&sprite_level_background_th);
	destroySprite(&sprite_burnination_meter_full);
	destroySprite(&sprite_burnination_meter_empty);
	destroySprite(&sprite_end_of_level_flash);
	destroySprite(&sprite_death_message);
	destroySprite(&sprite_burninate_text);
	destroySprite(&sprite_burninate_fire);
	destroySprite(&sprite_level_beaten_trogdor);
	destroySprite(&sprite_level_beaten_smoke);
	destroySprite(&sprite_game_over_trogdor);
	destroySprite(&sprite_trogdor);
	destroySprite(&sprite_trogdor_bighead);
	destroySprite(&sprite_cottage);
	destroySprite(&sprite_cottage_fire);
	destroySprite(&sprite_peasantometer_icon);
	destroySprite(&sprite_archer);
	destroySprite(&sprite_arrow);
	destroySprite(&sprite_trogdor_fire);
	destroySprite(&sprite_trogdor_dead);
	destroySprite(&sprite_knight);
	destroySprite(&sprite_peasant);
	destroySprite(&sprite_end_of_level_trogdor);
	destroySprite(&sprite_loot);
	destroySprite(&sprite_trogdor_flexing);
	destroySprite(&sprite_trogdor_ending);
	destroySprite(&sprite_heart);
	destroySprite(&sprite_knight_funnyjoke);
	destroySprite(&sprite_arrow_funnyjoke);
	destroySprite(&sprite_kerrek);
	destroySprite(&sprite_kerrek_smoked);
	destroySprite(&sprite_strong_bad);
	destroySprite(&sprite_strong_bad_ending);
	destroySprite(&sprite_menu_cursor);
	destroySprite(&sprite_menu_background);
	//destroySprite(&sprite_game_over_banner);
	destroySprite(&sprite_game_over_text);
	destroySprite(&sprite_game_over_jonathan_howe);
	destroySprite(&sprite_overlay_basement_top);
	destroySprite(&sprite_overlay_basement_bottom);
	destroySprite(&sprite_overlay_basement_left);
	destroySprite(&sprite_overlay_basement_right);
	destroySprite(&sprite_overlay_compy_top);
	destroySprite(&sprite_overlay_compy_bottom);
	destroySprite(&sprite_overlay_compy_left);
	destroySprite(&sprite_overlay_compy_right);
	destroySprite(&sprite_overlay_strong_badia_top);
	destroySprite(&sprite_overlay_strong_badia_bottom);
	destroySprite(&sprite_overlay_strong_badia_left);
	destroySprite(&sprite_overlay_strong_badia_right);
}

void destroyTextChars(FontObject *fontObj) {
	if (getDesiredFontSize(fontObj) != fontObj->size) {
		for (i = 0; i < (126 + 1 - 32); i++) {
#if !defined(SDL1)
			if (fontObj->textChars[i].texture != NULL) {
				SDL_DestroyTexture(fontObj->textChars[i].texture);
				fontObj->textChars[i].texture = NULL;
			}
#else
			if (fontObj->textChars[i].surface != NULL) {
				SDL_FreeSurface(fontObj->textChars[i].surface);
				fontObj->textChars[i].surface = NULL;
			}
#endif
		}
	}
}

void destroyAllTextChars() {
	//destroyTextChars(&font_serif_brown_6);
	//destroyTextChars(&font_serif_brown_8);
	//destroyTextChars(&font_serif_gray_6);
	destroyTextChars(&font_serif_gray_8);
	destroyTextChars(&font_serif_gray_12);
	//destroyTextChars(&font_serif_orange_6);
	destroyTextChars(&font_serif_red_6);
	destroyTextChars(&font_serif_red_6_mult);
	destroyTextChars(&font_serif_red_8);
	destroyTextChars(&font_serif_red_8_mult);
	destroyTextChars(&font_serif_red_12);
	destroyTextChars(&font_serif_white_6);
	destroyTextChars(&font_serif_white_6_mult);
	destroyTextChars(&font_serif_white_8);
	destroyTextChars(&font_serif_white_8_mult);
	destroyTextChars(&font_serif_white_9);
	destroyTextChars(&font_serif_white_10);
	destroyTextChars(&font_serif_white_14);
	destroyTextChars(&font_nokia_12);
	//destroyTextChars(&font_serif_2_bold_black_23);
	//destroyTextChars(&font_serif_2_bold_red_23);
	destroyTextChars(&font_serif_2_red_6);
	//destroyTextChars(&font_serif_2_red_13);
	destroyTextChars(&font_commodore_error_1);
	destroyTextChars(&font_commodore_error_2);
}

void closeAllFonts() {
	TTF_CloseFont(font_serif_brown_6.font);
	TTF_CloseFont(font_serif_brown_8.font);
	TTF_CloseFont(font_serif_gray_6.font);
	TTF_CloseFont(font_serif_gray_8.font);
	TTF_CloseFont(font_serif_gray_12.font);
	TTF_CloseFont(font_serif_orange_6.font);
	TTF_CloseFont(font_serif_red_6.font);
	TTF_CloseFont(font_serif_red_6_mult.font);
	TTF_CloseFont(font_serif_red_8.font);
	TTF_CloseFont(font_serif_red_8_mult.font);
	TTF_CloseFont(font_serif_red_12.font);
	TTF_CloseFont(font_serif_white_6.font);
	TTF_CloseFont(font_serif_white_6_mult.font);
	TTF_CloseFont(font_serif_white_8.font);
	TTF_CloseFont(font_serif_white_8_mult.font);
	TTF_CloseFont(font_serif_white_9.font);
	TTF_CloseFont(font_serif_white_10.font);
	TTF_CloseFont(font_serif_white_14.font);
	TTF_CloseFont(font_nokia_12.font);
	//TTF_CloseFont(font_serif_2_bold_black_23.font);
	//TTF_CloseFont(font_serif_2_bold_red_23.font);
	TTF_CloseFont(font_serif_2_red_6.font);
	TTF_CloseFont(font_serif_2_red_13.font);
	TTF_CloseFont(font_commodore_error_1.font);
	TTF_CloseFont(font_commodore_error_2.font);
}

void quickErrorTextRender_1(const char *text, double fraction) {
	SET_TEXT(text, text_error_1, font_commodore_error_1,
		OBJ_TO_MID_SCREEN_X(windowWidth, text_error_1), OBJ_TO_SCREEN_AT_FRACTION_Y(windowHeight, text_error_1, fraction));
	renderText_app(text_error_1, font_commodore_error_1);
}

void quickErrorTextRender_2(const char *text, double fraction) {
	SET_TEXT(text, text_error_2, font_commodore_error_2,
		OBJ_TO_MID_SCREEN_X(windowWidth, text_error_2), OBJ_TO_SCREEN_AT_FRACTION_Y(windowHeight, text_error_2, fraction));
	renderText_app(text_error_2, font_commodore_error_2);
}

void HandleErrorText(const char *badPath) {
	char tempCharArrayError[250];

	TTF_Init();

	STRCPY(tempCharArrayError, badPath);
	setFont(&font_commodore_error_1, Commodore_Pixelized_v1_2_ttf, Commodore_Pixelized_v1_2_ttf_len, 10, 10, TTF_STYLE_NORMAL, color_white, true);
	setFont(&font_commodore_error_2, Commodore_Pixelized_v1_2_ttf, Commodore_Pixelized_v1_2_ttf_len, 10, 9, TTF_STYLE_NORMAL, color_orange, true);
	srand(SDL_GetTicks());
	uint_i = (rand() % 4);
	switch (uint_i) {
		case 0:
			quickErrorTextRender_1("404'd!", 0.1);
			break;
		case 1:
			quickErrorTextRender_1("FLAGRANT SYSTEM ERROR", 0.1);
			break;
		case 2:
			quickErrorTextRender_1("I'm afraid I've got some bad news, boys.", 0.1);
			break;
		default:
			quickErrorTextRender_1("The System Is Down", 0.1);
			break;
	}
	quickErrorTextRender_1("If you're seeing this, the", 0.2);
	quickErrorTextRender_1("game just crashed due to a", 0.275);
	quickErrorTextRender_1("missing/invalid asset:", 0.35);
	quickErrorTextRender_2(tempCharArrayError, 0.475);
	quickErrorTextRender_1("Make sure you have the correct", 0.6);
	quickErrorTextRender_1("assets installed and try again.", 0.675);
	quickErrorTextRender_1("Press ENTER/START to quit.", 0.825);
	quickErrorTextRender_2("[Trogdor: Reburninated v2.31]", 0.9);
	TTF_CloseFont(font_commodore_error_1.font);
	TTF_CloseFont(font_commodore_error_2.font);

	TTF_Quit();
}