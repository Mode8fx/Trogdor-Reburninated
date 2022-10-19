#include "menu.h"

void MenuOption::prepareMenuOption(const char label_ptr[], const char *choice_ptr[], const char **desc_ptr[], const char altDesc_ptr[], Uint8 numCh, Uint8 start, bool wrap, bool locked) {
	labelPtr = label_ptr;
	choicePtr = choice_ptr;
	descPtr = desc_ptr;
	altDescPtr = altDesc_ptr;
	numChoices = numCh;
	for (i = 0; i < numChoices; i++) {
		choiceIsAllowed[i] = true;
	}
	index = start;
	index_init = start;
	isActive = true;
	choicesWrap = wrap;
	optionIsLocked = locked;
	updateLabel();
	updateChoice();
	updateDescription();
}

void MenuOption::updateLabel() {
	if (!optionIsLocked) {
		if (labelPtr != NULL) {
			setText(labelPtr, &label, &font_serif_white_6_mult);
		}
	} else {
		setText("???", &label, &font_serif_white_6_mult);
	}
}

void MenuOption::updateChoice() {
	if (!optionIsLocked) {
		if (choicePtr != NULL) {
			setText(choicePtr[index], &choice, &font_serif_white_6_mult);
		}
	} else {
		setText("", &choice, &font_serif_white_6_mult);
	}
}

void MenuOption::updateDescription() {
	if (!optionIsLocked) {
		if (descPtr != NULL) {
			setText(descPtr[index][0], &description_1, &font_serif_white_6_mult);
			setText(descPtr[index][1], &description_2, &font_serif_white_6_mult);
			setText(descPtr[index][2], &description_3, &font_serif_white_6_mult);
		}
	} else {
		if (altDescPtr != NULL) {
			setText(altDescPtr, &description_1, &font_serif_white_6_mult);
			setText("", &description_2, &font_serif_white_6_mult);
			setText("", &description_3, &font_serif_white_6_mult);
		}
	}
}

Menu::Menu(Uint8 numOpt, Uint8 numOns, SpriteInstance *spriteIns, bool keepIndex, Sint8 space_scroll, Sint16 st_x_label, Sint16 st_x_choice, Sint16 sp_x, Sint16 st_y, Sint16 sp_y, Sint8 at_label, Sint8 at_choice, bool wrap) {
	numOptions = numOpt;
	numOnscreen = min(numOns, numOptions);
	options = (MenuOption*)malloc(numOptions * sizeof(MenuOption));
	cursor = spriteIns;
	cursorIndex = 0;
	scrollIndex = 0;
	cursorIndex_onscreen = 0;
	keepIndexOnExit = keepIndex;
	scrollSpacer = space_scroll;
	start_x_label = st_x_label;
	start_x_choice = st_x_choice;
	spacer_x = sp_x;
	start_y = st_y;
	spacer_y = sp_y;
	alignType_label = at_label;
	alignType_choice = at_choice;
	optionsWrap = wrap;
}

void Menu::handleControls() {
	if (keyPressed(INPUT_UP)) {
		decrementOption();
	}
	if (keyPressed(INPUT_DOWN)) {
		incrementOption();
	}
	if (keyPressed(INPUT_LEFT)) {
		decrementCurrOptionChoice();
	}
	if (keyPressed(INPUT_RIGHT)) {
		incrementCurrOptionChoice();
	}
}

void Menu::incrementOption() {
	if (cursorIndex < numOptions - 1) {
		cursorIndex++;
		cursorIndex_onscreen++;
		if (cursorIndex_onscreen > numOnscreen - scrollSpacer) {
			scrollIndex++;
			cursorIndex_onscreen--;
		}
		updateOptionPositions();
	} else if (optionsWrap) {
		cursorIndex = 0;
		scrollIndex = 0;
		cursorIndex_onscreen = 0;
		updateOptionPositions();
	}
}

void Menu::decrementOption() {
	if (cursorIndex > 0) {
		cursorIndex--;
		cursorIndex_onscreen--;
		if (cursorIndex_onscreen < scrollSpacer) {
			scrollIndex--;
			cursorIndex_onscreen++;
		}
		updateOptionPositions();
	} else if (optionsWrap) {
		cursorIndex = numOptions - 1;
		scrollIndex = numOptions - numOnscreen;
		cursorIndex_onscreen = numOnscreen - 1;
		updateOptionPositions();
	}
}

// This assumes at least one choice is allowed
void Menu::incrementCurrOptionChoice() {
	if (options[cursorIndex].choicesWrap) {
		do {
			options[cursorIndex].index = (options[cursorIndex].index + 1) % options[cursorIndex].numChoices;
		} while (!options[cursorIndex].choiceIsAllowed[options[cursorIndex].index]);
	} else {
		while (options[cursorIndex].index < options[cursorIndex].numChoices - 1 && !options[cursorIndex].choiceIsAllowed[options[cursorIndex].index]) {
			options[cursorIndex].index++;
		}
	}
	updateCurrOptionChoicePositions();
}

// This assumes at least one choice is allowed
void Menu::decrementCurrOptionChoice() {
	if (options[cursorIndex].choicesWrap) {
		do {
			options[cursorIndex].index = options[cursorIndex].index--;
			if (options[cursorIndex].index < 0) {
				options[cursorIndex].index += options[cursorIndex].numChoices;
			}
		} while (!options[cursorIndex].choiceIsAllowed[options[cursorIndex].index]);
	} else {
		while (options[cursorIndex].index > 0 && !options[cursorIndex].choiceIsAllowed[options[cursorIndex].index]) {
			options[cursorIndex].index--;
		}
	}
	updateCurrOptionChoicePositions();
}

void Menu::updateOptionPositions() {
	for (i = 0; i < options[i].numChoices; i++) {
		options[i].isActive = false;
	}
	j = cursorIndex - cursorIndex_onscreen;
	for (i = j; i < j + numOnscreen; i++) {
		options[i].isActive = true;
		switch (alignType_label) {
			case 0:
				options[i].label.dstrect.x = start_x_label + (spacer_x * (i - j));
				break;
			case 1:
				options[i].label.dstrect.x = start_x_label + (spacer_x * (i - j)) - (options[i].label.dstrect.w / 2);
				break;
			default:
				options[i].label.dstrect.x = start_x_label + (spacer_x * (i - j)) - options[i].label.dstrect.w;
				break;
		}
		options[i].label.dstrect.y = start_y + (spacer_y * (i - j));
		updateCurrOptionChoicePositions();
	}
	cursor->dstrect.x = options[cursorIndex_onscreen].label.dstrect.x - (cursor->dstrect.w * 2);
	cursor->dstrect.y = options[cursorIndex_onscreen].label.dstrect.y + ((options[cursorIndex_onscreen].label.dstrect.h - cursor->dstrect.h) / 2);
}

void Menu::updateCurrOptionChoicePositions() {
	options[cursorIndex].updateChoice();
	switch (alignType_choice) {
		case 0:
			options[cursorIndex].choice.dstrect.x = start_x_choice + (spacer_x * (i - j));
			break;
		case 1:
			options[cursorIndex].choice.dstrect.x = start_x_choice + (spacer_x * (i - j)) - (options[cursorIndex].choice.dstrect.w / 2);
			break;
		case 2:
			options[cursorIndex].choice.dstrect.x = start_x_choice + (spacer_x * (i - j)) - options[cursorIndex].choice.dstrect.w;
			break;
	}
	options[cursorIndex].choice.dstrect.y = start_y + (spacer_y * (i - j));
	updateCurrOptionChoiceDescription();
}

void Menu::updateCurrOptionChoiceDescription() {
	// TODO: Update description line positions below
	if (options[cursorIndex].description_2.dstrect.w == 0) {
		setTextPos(&options[cursorIndex].description_1, 0, 0);
	} else if (options[cursorIndex].description_3.dstrect.w == 0) {
		setTextPos(&options[cursorIndex].description_1, 0, 0);
		setTextPos(&options[cursorIndex].description_2, 0, 0);
	} else {
		setTextPos(&options[cursorIndex].description_1, 0, 0);
		setTextPos(&options[cursorIndex].description_2, 0, 0);
		setTextPos(&options[cursorIndex].description_3, 0, 0);
	}
}

void Menu::openMenu() {
	if (!keepIndexOnExit) {
		cursorIndex = 0;
		scrollIndex = 0;
		cursorIndex_onscreen = 0;
	}
	updateOptionPositions();
}

const char *option_main_1_label = "Starting Level";
const char *option_main_1_choices[5] = { "1", "21", "41", "61", "81" };
const char *option_main_1_descriptions[1][3] = {
	{ "The level that the game starts on.", "", "" },
};
const char *option_main_2_label = "Starting Lives";
const char *option_main_2_choices[8] = { "1", "2", "3", "4", "5", "10", "20", "30" };
const char *option_main_2_descriptions[1][3] = {
	{ "The number of lives you start with.", "", "" },
};
const char *option_main_3_label = "Extra Lives";
const char *option_main_3_choices[8] = { "Every 300 points", "Every 500 points", "Every 1000 points", "500 points only", "500 and 1000 only", "1000 points only", "1000 and 2000 only", "None" };
const char *option_main_3_descriptions[8][3] = {
	{ "Get an extra life", "every 300 points.", "" },
	{ "Get an extra life", "every 500 points.", "" },
	{ "Get an extra life", "every 1000 points.", "" },
	{ "Get an extra life", "at 500 points.", "" },
	{ "Get an extra life", "at 500 and 1000 points.", "" },
	{ "Get an extra life", "at 1000 points.", "" },
	{ "Get an extra life", "at 1000 and 2000 points.", "" },
	{ "No extra lives.", "", "" },
};
const char *option_main_4_label = "Peasant Penalty";
const char *option_main_4_choices[2] = { "On", "Off" };
const char *option_main_4_descriptions[2][3] = {
	{ "The peasant meter decreases", "every time a peasant escapes.", "" },
	{ "No penalty for escaped peasants.", "", "" },
};
const char *option_main_5_label = "Archer Frequency";
const char *option_main_5_choices[4] = { "Scaling", "Low", "Medium", "High" };
const char *option_main_5_descriptions[4][3] = {
	{ "Archers appear more in later levels.", "", "" },
	{ "Archers do not appear often.", "", "" },
	{ "Archers appear semi-often.", "", "" },
	{ "Archers appear very often.", "", "" },
};
const char *option_main_6_label = "Commentary Frequency";
const char *option_main_6_choices[6] = { "Off", "Very Low", "Low", "Normal", "High", "Very High", };
const char *option_main_6_descriptions[6][3] = {
	{ "Strong Bad does not talk.", "", "" },
	{ "Strong Bad talks 50% less often.", "", "" },
	{ "Strong Bad talks 25% less often.", "", "" },
	{ "Strong Bad talks as often", "as he did in the original game.", "" },
	{ "Strong Bad talks 25% more often.", "", "" },
	{ "Strong Bad talks 50% more often.", "", "" },
};
const char *option_main_7_label = "Scaling";
const char *option_main_7_choices[4] = { "Full Overlay", "Full Game", "Pixel-Perfect Overlay", "Pixel-Perfect Game" };
const char *option_main_7_descriptions[4][3] = {
	{ "Scale everything so that", "the overlay fills the screen.", "" },
	{ "Scale the game window to fill the", "screen. The overlay will be", "cut off." },
	{ "Scale so that everything uses", "integer scaling. The most", "accurate, but possibly smallest." },
	{ "Scale the game window to be as big as", "possible with integer scaling. The most", "accurate, but overlay may be cut off." },
};
const char *option_main_8_label = "Cheats";
const char *option_main_8_choices[1] = { "" };
const char *option_main_8_descriptions[1][3] = {
	{ "Toggle hidden cheats.", "", "" },
};
const char *option_cheats_1_label = "Infinite Lives";
const char *option_cheats_1_choices[2] = { "On", "Off" };
const char *option_cheats_1_descriptions[1][3] = {
	{ "Infinite lives, play forever!", "Unlocking this cheat also unlocks", "more starting lives options." },
};
const char *option_cheats_1_description_alt = "Secret Code?!?!";
const char *option_cheats_2_label = "Debug Cheat";
const char *option_cheats_2_choices[2] = { "On", "Off" };
const char *option_cheats_2_descriptions[1][3] = {
	{ "Enable Debug Mode. A/B to change", "peasant meter, L/R to", "change level, Select to win level." },
};
const char *option_cheats_2_description_alt = "Class of 1981";
const char *option_cheats_3_label = "Big Head Mode";
const char *option_cheats_3_choices[2] = { "On", "Off" };
const char *option_cheats_3_descriptions[1][3] = {
	{ "Give Trogdor a more husky head.", "", "" },
};
const char *option_cheats_3_description_alt = "Echidna Mushroom Pulley";
const char *option_cheats_4_label = "Noclip";
const char *option_cheats_4_choices[2] = { "On", "Off" };
const char *option_cheats_4_descriptions[1][3] = {
	{ "Remove the game's difficulty", "by walking through cottages.", "" },
};
const char *option_cheats_4_description_alt = "1994 Country";