#include "media_objects_init.h"

void InitializeTextChars() {
	TTF_Init();

	setFont(font_serif_white_14, "fonts/serif_v01.ttf", 14,
		TTF_STYLE_NORMAL, textChars_font_serif_white_14, color_white, 32, 126);
	setFont(font_serif_brown_6, "fonts/serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_brown_6, color_brown, 32, 122);
	setFont(font_serif_brown_8, "fonts/serif_v01.ttf", 8,
		TTF_STYLE_NORMAL, textChars_font_serif_brown_8, color_brown, 32, 126);
	setFont(font_serif_gray_6, "fonts/serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_gray_6, color_gray, 32, 126);
	setFont(font_serif_gray_12, "fonts/serif_v01.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_serif_gray_12, color_gray, 32, 90);
	setFont(font_serif_orange_6, "fonts/serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_orange_6, color_orange, 32, 90);
	setFont(font_serif_red_6, "fonts/serif_v01.ttf", 6,
		//setFont(font_serif_red_6, "fonts/serif_v01.ttf", 8,
		TTF_STYLE_NORMAL, textChars_font_serif_red_6, color_red, 32, 126);
	setFont(font_serif_red_8, "fonts/serif_v01.ttf", 8,
		TTF_STYLE_NORMAL, textChars_font_serif_red_8, color_red, 32, 126);
	setFont(font_serif_red_12, "fonts/serif_v01.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_serif_red_12, color_red, 32, 90);
	setFont(font_serif_white_6, "fonts/serif_v01.ttf", 6,
		//setFont(font_serif_white_6, "fonts/serif_v01.ttf", 8,
		TTF_STYLE_NORMAL, textChars_font_serif_white_6, color_white, 32, 126);
	setFont(font_serif_white_9, "fonts/serif_v01.ttf", 9,
		TTF_STYLE_NORMAL, textChars_font_serif_white_9, color_white, 32, 126);
	setFont(font_serif_white_10, "fonts/serif_v01.ttf", 10,
		TTF_STYLE_NORMAL, textChars_font_serif_white_10, color_white, 32, 126);

	setFont(font_nokia_12, "fonts/29_NOKIA 5110 FontSet.ttf", 12,
		TTF_STYLE_NORMAL, textChars_font_nokia_12, color_white, 97, 126);

	//setFont(font_serif_2_bold_black_23, "fonts/54_serif_v01.ttf", 23,
	//	TTF_STYLE_BOLD, textChars_font_serif_2_bold_black_23, color_black, 32, 90);
	//setFont(font_serif_2_bold_red_23, "fonts/54_serif_v01.ttf", 23,
	//	TTF_STYLE_BOLD, textChars_font_serif_2_bold_red_23, color_red, 32, 90);
	setFont(font_serif_2_red_6, "fonts/54_serif_v01.ttf", 6,
		TTF_STYLE_NORMAL, textChars_font_serif_2_red_6, color_red, 32, 90);
	setFont(font_serif_2_red_13, "fonts/54_serif_v01.ttf", 13,
		TTF_STYLE_NORMAL, textChars_font_serif_2_red_13, color_red, 32, 90);

	TTF_Quit();
}

void InitializeTextObjects() {
	/* 0: Loading Screen */
	SET_TEXT("loading...", text_0_loading, textChars_font_serif_white_14,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_0_loading), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, text_0_loading));
	/* 1: Videlectrix Logo */
	SET_TEXT("presents", text_1_presents, textChars_font_nokia_12,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_1_presents), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_1_presents, 0.7));
	/* 2: Title Screen */
	/* 3: Instructions Screen */
	SET_TEXT("click anywhere to START", text_3_click_anywhere_to_start, textChars_font_serif_red_8,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_click_anywhere_to_start), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_click_anywhere_to_start, 0.75));
	// Use a separate credits page instead of these
	//SET_TEXT("Programmed by Jonathan Howe", text_3_programmed, textChars_font_serif_white_6,
	//	OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_programmed), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_programmed, 0.85));
	//SET_TEXT("Designed by Mike and Matt", text_3_designed, textChars_font_serif_white_6,
	//	OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_designed), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_designed, 0.93));
	SET_TEXT("(1/4)", text_3_page, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_page), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_page, 0.95));
	SET_TEXT("Use the arrow keys to control Trogdor", text_3_instructions_1, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_1), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_instructions_1, 0.35));
	SET_TEXT("Stomp 10 peasants to achieve burnination.", text_3_instructions_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_2), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_instructions_2, 0.43));
	SET_TEXT("Burn all cottages to advance a level.", text_3_instructions_3, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_3), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_instructions_3, 0.51));
	SET_TEXT("Avoid knights and archers!", text_3_instructions_4, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_4), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_instructions_4, 0.59));
	SET_TEXT("Press SPACE to pause.", text_3_instructions_5, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_instructions_5), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_instructions_5, 0.67));
	SET_TEXT("SECRET HINTS!!", text_3_hints_1, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_1), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_hints_1, 0.39));
	SET_TEXT("-Don't let the peasants return to their cottages", text_3_hints_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_2), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_hints_2, 0.51));
	SET_TEXT("-Once you\'re burninating, you\'re invincible", text_3_hints_3, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_3), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_hints_3, 0.58));
	SET_TEXT("-Burninated peasants set their cottages on fire", text_3_hints_4, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_4), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_hints_4, 0.65));
	SET_TEXT("-Get an extra man every 300 points", text_3_hints_5, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_5), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_hints_5, 0.72));
	SET_TEXT("-What\'s a treasure hut?!?!", text_3_hints_6, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_6), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_hints_6, 0.79));
	SET_TEXT("- Secret Code?!?!", text_3_hints_7, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_hints_7), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_hints_7, 0.86));

	SET_TEXT("CREDITS", text_3_credits_1, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_credits_1), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_credits_1, 0.35));
	SET_TEXT("ORIGINAL FLASH GAME", text_3_credits_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_credits_2), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_credits_2, 0.43));
	SET_TEXT("Programming: Jonathan Howe", text_3_credits_3, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_credits_3), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_credits_3, 0.51));
	// credits for the HTML5 version will be added when stuff from the HTML5 version is added to this version
	SET_TEXT("Design: Mike Chapman, Matt Chapman", text_3_credits_4, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_credits_4), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_credits_4, 0.59));
	SET_TEXT("THIS PORT", text_3_credits_5, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_credits_5), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_credits_5, 0.69));
	SET_TEXT("Mips96", text_3_credits_6, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_credits_6), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_credits_6, 0.77));
	SET_TEXT("https://github.com/Mips96/Trogdor-Reburninated", text_3_credits_7, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_credits_7), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_credits_7, 0.85));
	SET_TEXT("COMING SOON (?)", text_3_coming_soon_1, textChars_font_serif_red_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_coming_soon_1), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_coming_soon_1, 0.35));
	SET_TEXT("\"Trogdor Classic\"", text_3_coming_soon_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_coming_soon_2), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_coming_soon_2, 0.43));
	SET_TEXT("-Fully implemented cutscenes!", text_3_coming_soon_3, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_coming_soon_3), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_coming_soon_3, 0.59));
	SET_TEXT("-Level Beaten / Game Over animations!", text_3_coming_soon_4, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_coming_soon_4), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_coming_soon_4, 0.67));
	SET_TEXT("-Unused High Scores screen restored!", text_3_coming_soon_5, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_coming_soon_5), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_coming_soon_5, 0.75));
	SET_TEXT("-Some more polish!", text_3_coming_soon_6, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_3_coming_soon_6), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_3_coming_soon_6, 0.83));
	/* 4: Game */
	SET_TEXT("SCORE:", text_4_score, textChars_font_serif_2_red_6,
		10 * gameHiResWidth / gameWidth, 1 * gameHiResHeight / gameHeight);
	SET_TEXT("??????", text_4_score_val, textChars_font_serif_red_6,
		10 * gameHiResWidth / gameWidth, 14 * gameHiResHeight / gameHeight);
	SET_TEXT("MANS:", text_4_mans, textChars_font_serif_2_red_6,
		200 * gameHiResWidth / gameWidth, 4 * gameHiResHeight / gameHeight);
	SET_TEXT("??", text_4_mans_val, textChars_font_serif_red_6,
		230 * gameHiResWidth / gameWidth, 1 * gameHiResHeight / gameHeight);
	SET_TEXT("LEVEL:", text_4_level, textChars_font_serif_2_red_6,
		195 * gameHiResWidth / gameWidth, 14 * gameHiResHeight / gameHeight);
	SET_TEXT("??", text_4_level_val, textChars_font_serif_red_6,
		230 * gameHiResWidth / gameWidth, 11 * gameHiResHeight / gameHeight);
	SET_TEXT("paused", text_4_paused_1, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_1), 145 * gameHiResHeight / gameHeight);
	SET_TEXT("press 'SPACE' to resume", text_4_paused_2, textChars_font_serif_white_6,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_4_paused_2), 160 * gameHiResHeight / gameHeight);
	/* 5: Game Over */
	/* 6: Game (Treasure Hut) */
	/* 7: Nothing */
	/* 8: End of Level Animation */
	/* 9: Level Beaten Screen */
	SET_TEXT("nice work!", text_9_nice_work, textChars_font_serif_white_10,
		OBJ_TO_SCREEN_AT_FRACTION_X(gameHiResWidth, text_9_nice_work, 0.77), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_9_nice_work, 0.45));
	/* 10: Game Over Screen */
	/* 11-23: Placeholder Message */
	SET_TEXT("cutscenes aren't finished yet!", text_placeholder_cutscene, textChars_font_serif_red_8,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_placeholder_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_placeholder_cutscene, 0.6));
	/* 11: Level 4 Interlude */
	SET_TEXT("stompin' good!", text_11_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_11_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_11_cutscene, 0.25));
	/* 12: Level 8 Interlude */
	SET_TEXT("fry 'em up dan.", text_12_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_12_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_12_cutscene, 0.25));
	/* 13: Level 12 Interlude */
	SET_TEXT("parade of trogdors", text_13_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_13_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_13_cutscene, 0.25));
	/* 14: Level 16 Interlude */
	SET_TEXT("dancin' time", text_14_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_14_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_14_cutscene, 0.25));
	/* 15: Level 20 Interlude */
	SET_TEXT("flex it, troggie.", text_15_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_15_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_15_cutscene, 0.25));
	/* 16: Level 24 Interlude */
	SET_TEXT("peasant dominoes", text_16_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_16_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_16_cutscene, 0.25));
	/* 17: Level 30 Interlude */
	SET_TEXT("trogdor incognito", text_17_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_17_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_17_cutscene, 0.25));
	/* 18: Level 34 Interlude */
	SET_TEXT("go trogdor # 2!", text_18_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_18_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_18_cutscene, 0.25));
	/* 19: Level 38 Interlude */
	SET_TEXT("forbidden peasant love", text_19_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_19_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_19_cutscene, 0.25));
	/* 20: Level 42 Interlude */
	SET_TEXT("2 cottages", text_20_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_20_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_20_cutscene, 0.25));
	/* 21: Level 46 Interlude */
	SET_TEXT("a funny joke", text_21_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_21_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_21_cutscene, 0.25));
	/* 22: Level 50 Interlude */
	SET_TEXT("smote that kerrek!", text_22_cutscene, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_22_cutscene), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_22_cutscene, 0.25));
	/* 23: Level 100 Interlude (Credits) */
	SET_TEXT("congratulations.", text_23_cutscene_1, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_1), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_1, 0.25));
	SET_TEXT("you got", text_23_cutscene_2, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_2), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_2, 0.35));
	SET_TEXT("good score", text_23_cutscene_3, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_3), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_3, 0.45));
	SET_TEXT("cast", text_23_cutscene_4, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_4), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_4, 0.25));
	SET_TEXT("trogdor", text_23_cutscene_5, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_5), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_5, 0.25));
	SET_TEXT("perez", text_23_cutscene_6, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_6), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_6, 0.25));
	SET_TEXT("hackworth", text_23_cutscene_7, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_7), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_7, 0.25));
	SET_TEXT("\'the steve\'", text_23_cutscene_8, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_8), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_8, 0.25));
	SET_TEXT("the blue knight", text_23_cutscene_9, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_9), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_9, 0.25));
	SET_TEXT("the red knight", text_23_cutscene_10, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_10), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_10, 0.25));
	SET_TEXT("the siamese archers", text_23_cutscene_11, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_11), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_11, 0.25));
	SET_TEXT("and Wordly Wise", text_23_cutscene_12, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_12), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_12, 0.25));
	SET_TEXT("as The Kerrek", text_23_cutscene_13, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_13), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_13, 0.25));
	SET_TEXT("keep playing!", text_23_cutscene_14, textChars_font_serif_white_9,
		OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_23_cutscene_14), OBJ_TO_SCREEN_AT_FRACTION_Y(gameHiResHeight, text_23_cutscene_14, 0.25));
	/* 24: Nothing? (or maybe blank transition from Credits to High Scores Screen) */
	/* 25: High Scores Screen */

	//SET_TEXT("nice work!", text_nice_work, textChars_font_serif_white_10,
	//	OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_nice_work), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, text_nice_work));
	//SET_TEXT("send'em", text_send_em, textChars_font_serif_gray_6,
	//	OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_send_em), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, text_send_em));
	//SET_TEXT("YE       OLDE       HI-SCORES", text_ye_olde_hi_scores, textChars_font_serif_2_red_13,
	//	OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_ye_olde_hi_scores), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, text_ye_olde_hi_scores));
	//SET_TEXT("1", text_one, textChars_font_serif_brown_8,
	//	OBJ_TO_MID_SCREEN_X(gameHiResWidth, text_one), OBJ_TO_MID_SCREEN_Y(gameHiResHeight, text_one));
}

void destroyTextChars(TextCharObject textChars[], Uint8 numChars) {
	for (i = 0; i < numChars; i++) {
		SDL_FreeSurface(textChars[i].surface);
	}
}

void destroyAllTextChars() {
	destroyTextChars(textChars_font_serif_brown_6, 122 + 1 - 32);
	destroyTextChars(textChars_font_serif_brown_8, 126 + 1 - 32);
	destroyTextChars(textChars_font_serif_gray_6, 126 + 1 - 32);
	destroyTextChars(textChars_font_serif_gray_12, 90 + 1 - 32);
	destroyTextChars(textChars_font_serif_orange_6, 90 + 1 - 32);
	destroyTextChars(textChars_font_serif_red_6, 126 + 1 - 32);
	destroyTextChars(textChars_font_serif_red_8, 126 + 1 - 32);
	destroyTextChars(textChars_font_serif_red_12, 90 + 1 - 32);
	destroyTextChars(textChars_font_serif_white_6, 126 + 1 - 32);
	destroyTextChars(textChars_font_serif_white_9, 126 + 1 - 32);
	destroyTextChars(textChars_font_serif_white_10, 126 + 1 - 32);
	destroyTextChars(textChars_font_serif_white_14, 126 + 1 - 32);
	destroyTextChars(textChars_font_nokia_12, 126 + 1 - 32);
	//destroyTextChars(textChars_font_serif_2_bold_black_23, 90 + 1 - 32);
	//destroyTextChars(textChars_font_serif_2_bold_red_23, 90 + 1 - 32);
	destroyTextChars(textChars_font_serif_2_red_6, 90 + 1 - 32);
	destroyTextChars(textChars_font_serif_2_red_13, 90 + 1 - 32);
}