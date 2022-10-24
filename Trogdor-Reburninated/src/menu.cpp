#include "menu.h"
#include "input.h"
#include "general.h"
#include "window.h"

Sint8 currOnscreenIndex;
Sint8 initCounter;
bool menusAreInitialized = false;
FontObject *menuFont;

#define CURR_OPTION options[cursorIndex]
#define CURR_OPTION_ONSCREEN options[currOnscreenIndex]
#define CURR_SPACER_X (spacer_x * (currOnscreenIndex - topOnscreenIndex))

#define DESC_LINE_Y_TOP    (Sint16)(start_y_desc * screenScale_menu)
#define DESC_LINE_Y_UPPER  (Sint16)((start_y_desc + (spacer_y_desc / 2)) * screenScale_menu)
#define DESC_LINE_Y_MID    (Sint16)((start_y_desc + spacer_y_desc) * screenScale_menu)
#define DESC_LINE_Y_LOWER  (Sint16)((start_y_desc + (spacer_y_desc * 3 / 2)) * screenScale_menu)
#define DESC_LINE_Y_BOTTOM (Sint16)((start_y_desc + (spacer_y_desc * 2)) * screenScale_menu)

void MenuOption::prepareMenuOption(const char label_ptr[], const char *choice_ptr[], const char *desc_ptr_1[], const char *desc_ptr_2[], const char *desc_ptr_3[], const char altDesc_ptr[], Uint8 numCh, bool oneDesc, Uint8 start, bool wrap) {
	labelPtr = label_ptr;
	if (!menusAreInitialized) {
		choicePtr = choice_ptr;
		descPtr_1 = desc_ptr_1;
		descPtr_2 = desc_ptr_2;
		descPtr_3 = desc_ptr_3;
		altDescPtr = altDesc_ptr;
		numChoices = numCh;
		oneDescription = oneDesc;
		for (i = 0; i < numChoices; i++) {
			choiceIsAllowed[i] = true;
		}
		index = start;
		index_init = start;
		choicesWrap = wrap;
		optionIsLocked = false;
	}
	updateLabel();
	initChoicesAndDescriptions();
	updateChoice();
	updateDescription();
}

void MenuOption::setLocked(bool locked) {
	optionIsLocked = locked;
	updateLabel();
	updateChoice();
	updateDescription();
}

void MenuOption::updateLabel() {
	if (!optionIsLocked) {
		if (labelPtr != NULL) {
			setText(labelPtr, &label, menuFont);
		}
	} else {
		setText("???", &label, menuFont);
	}
}

// this initializes text chars used in choices that aren't initially selected
void MenuOption::initChoicesAndDescriptions() {
	if (choicePtr != NULL) {
		for (initCounter = 0; initCounter < numChoices; initCounter++) {
			setText(choicePtr[initCounter], &choice, menuFont);
		}
	}
	if (descPtr_1 != NULL) {
		if (!oneDescription) {
			for (initCounter = 0; initCounter < numChoices; initCounter++) {
				setText(descPtr_1[initCounter], &description_1, menuFont);
				setText(descPtr_2[initCounter], &description_1, menuFont);
				setText(descPtr_3[initCounter], &description_1, menuFont);
			}
		}
	}
}

void MenuOption::updateChoice() {
	if (!optionIsLocked) {
		if (choicePtr != NULL) {
			setText(choicePtr[index], &choice, menuFont);
		}
	} else {
		setText("", &choice, menuFont);
	}
}

void MenuOption::updateDescription() {
	if (!optionIsLocked) {
		if (descPtr_1 != NULL) {
			if (oneDescription) {
				setText(descPtr_1[0], &description_1, menuFont);
				setText(descPtr_2[0], &description_2, menuFont);
				setText(descPtr_3[0], &description_3, menuFont);
			} else {
				setText(descPtr_1[index], &description_1, menuFont);
				setText(descPtr_2[index], &description_2, menuFont);
				setText(descPtr_3[index], &description_3, menuFont);
			}
		}
	} else {
		if (altDescPtr != NULL) {
			setText(altDescPtr, &description_1, menuFont);
			setText("", &description_2, menuFont);
			setText("", &description_3, menuFont);
		}
	}
}

void MenuOption::render(bool renderDescription) {
	renderText_menu(label, *menuFont);
	renderText_menu(choice, *menuFont);
	if (renderDescription) {
		renderText_menu(description_1, *menuFont);
		renderText_menu(description_2, *menuFont);
		renderText_menu(description_3, *menuFont);
	}
}

bool MenuOption::isValue(Uint8 val) {
	return (!optionIsLocked && index == val);
}

void Menu::prepareMenu(Uint8 numOpt, Uint8 numOns, SpriteObject *spriteObj, bool keepIndex, Sint8 space_scroll,
	Sint16 st_x_label, Sint16 st_x_choice, Sint16 sp_x, Sint16 st_y_option, Sint16 st_y_desc, Sint16 sp_y_option, Sint16 sp_y_desc,
	Sint8 at_label, Sint8 at_choice, bool wrap) {
	start_x_label = st_x_label;
	start_x_choice = st_x_choice;
	spacer_x = sp_x;
	start_y_option = st_y_option;
	start_y_desc = st_y_desc;
	spacer_y_option = sp_y_option;
	spacer_y_desc = sp_y_desc;
	alignType_label = at_label;
	alignType_choice = at_choice;
	if (!menusAreInitialized) {
		numOptions = numOpt;
		numOnscreen = min(numOns, numOptions);
		cursor = SpriteInstance(spriteObj, 0, 0);
		cursorIndex = 0;
		scrollIndex = 0;
		cursorIndex_onscreen = 0;
		keepIndexOnExit = keepIndex;
		scrollSpacer = space_scroll;
		topOnscreenIndex = 0;
		bottomOnscreenIndex = 0;
		optionsWrap = wrap;
	}
}

Sint8 Menu::handleInput() {
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
	if (keyPressed(INPUT_A)) {
		return cursorIndex;
	}
	if (keyPressed(INPUT_B)) {
		return -1;
	}
	return -2;
}

void Menu::incrementOption() {
	if (cursorIndex < numOptions - 1) {
		cursorIndex++;
		cursorIndex_onscreen++;
		if ((cursorIndex_onscreen >= numOnscreen - scrollSpacer) && (scrollIndex < numOptions - numOnscreen)) {
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
		if ((cursorIndex_onscreen < scrollSpacer) && (scrollIndex > 0)) {
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
	if (CURR_OPTION->choicesWrap) {
		do {
			CURR_OPTION->index = (CURR_OPTION->index + 1) % CURR_OPTION->numChoices;
		} while (!CURR_OPTION->choiceIsAllowed[CURR_OPTION->index]);
	} else if (CURR_OPTION->index < CURR_OPTION->numChoices - 1) {
		do {
			CURR_OPTION->index++;
		} while (CURR_OPTION->index < CURR_OPTION->numChoices - 1 && !CURR_OPTION->choiceIsAllowed[CURR_OPTION->index]);
	}
	CURR_OPTION->updateChoice();
	CURR_OPTION->updateDescription();
	updateOptionChoicePosition(cursorIndex);
}

// This assumes at least one choice is allowed
void Menu::decrementCurrOptionChoice() {
	if (CURR_OPTION->choicesWrap) {
		do {
			CURR_OPTION->index = CURR_OPTION->index--;
			if (CURR_OPTION->index < 0) {
				CURR_OPTION->index += CURR_OPTION->numChoices;
			}
		} while (!CURR_OPTION->choiceIsAllowed[CURR_OPTION->index]);
	} else if (!CURR_OPTION->choiceIsAllowed[CURR_OPTION->index]){
		do {
			CURR_OPTION->index--;
		} while (CURR_OPTION->index > 0 && !CURR_OPTION->choiceIsAllowed[CURR_OPTION->index]);
	}
	CURR_OPTION->updateChoice();
	CURR_OPTION->updateDescription();
	updateOptionChoicePosition(cursorIndex);
}

void Menu::updateOptionPositions() {
	topOnscreenIndex = cursorIndex - cursorIndex_onscreen;
	bottomOnscreenIndex = min(topOnscreenIndex + numOnscreen, (int)numOptions) - 1;
	for (currOnscreenIndex = topOnscreenIndex; currOnscreenIndex <= bottomOnscreenIndex; currOnscreenIndex++) {
		// Update Label 
		switch (alignType_label) {
			case 0:
				CURR_OPTION_ONSCREEN->label.dstrect.x = start_x_label + CURR_SPACER_X;
				break;
			case 1:
				CURR_OPTION_ONSCREEN->label.dstrect.x = start_x_label + CURR_SPACER_X - (CURR_OPTION_ONSCREEN->label.dstrect.w / 2);
				break;
			default:
				CURR_OPTION_ONSCREEN->label.dstrect.x = start_x_label + CURR_SPACER_X - CURR_OPTION_ONSCREEN->label.dstrect.w;
				break;
		}
		CURR_OPTION_ONSCREEN->label.dstrect.y = start_y_option + (spacer_y_option * (currOnscreenIndex - topOnscreenIndex));

		CURR_OPTION_ONSCREEN->label.dstrect.x = (Sint16)(CURR_OPTION_ONSCREEN->label.dstrect.x * screenScale_menu);
		CURR_OPTION_ONSCREEN->label.dstrect.y = (Sint16)(CURR_OPTION_ONSCREEN->label.dstrect.y * screenScale_menu);
		updateOptionChoicePosition(currOnscreenIndex);
	}
	cursor.dstrect.x = CURR_OPTION->label.dstrect.x - (Sint16)(cursor.dstrect.w * screenScale_menu * 2);
	cursor.dstrect.y = CURR_OPTION->label.dstrect.y + ((CURR_OPTION->label.dstrect.h - (Sint16)(cursor.dstrect.h * screenScale_menu)) / 2);
}

void Menu::updateOptionChoicePosition(Sint8 optionIndex) {
	switch (alignType_choice) {
		case 0:
			options[optionIndex]->choice.dstrect.x = start_x_choice + CURR_SPACER_X;
			break;
		case 1:
			options[optionIndex]->choice.dstrect.x = start_x_choice + CURR_SPACER_X - (CURR_OPTION->choice.dstrect.w / 2);
			break;
		case 2:
			options[optionIndex]->choice.dstrect.x = start_x_choice + CURR_SPACER_X - CURR_OPTION->choice.dstrect.w;
			break;
	}
	options[optionIndex]->choice.dstrect.y = options[optionIndex]->label.dstrect.y;

	options[optionIndex]->choice.dstrect.x = (Sint16)(options[optionIndex]->choice.dstrect.x * screenScale_menu);
	updateOptionDescPosition(optionIndex);
}

void Menu::updateOptionDescPosition(Sint8 optionIndex) {
	if (options[optionIndex]->description_2.dstrect.w == 0) {
		setTextPos(&options[optionIndex]->description_1, OBJ_TO_MID_SCREEN_X((Sint16)(appWidth * screenScale_menu), options[optionIndex]->description_1), DESC_LINE_Y_MID);
	} else if (options[optionIndex]->description_3.dstrect.w == 0) {
		setTextPos(&options[optionIndex]->description_1, OBJ_TO_MID_SCREEN_X((Sint16)(appWidth * screenScale_menu), options[optionIndex]->description_1), DESC_LINE_Y_UPPER);
		setTextPos(&options[optionIndex]->description_2, OBJ_TO_MID_SCREEN_X((Sint16)(appWidth * screenScale_menu), options[optionIndex]->description_2), DESC_LINE_Y_LOWER);
	} else {
		setTextPos(&options[optionIndex]->description_1, OBJ_TO_MID_SCREEN_X((Sint16)(appWidth * screenScale_menu), options[optionIndex]->description_1), DESC_LINE_Y_TOP);
		setTextPos(&options[optionIndex]->description_2, OBJ_TO_MID_SCREEN_X((Sint16)(appWidth * screenScale_menu), options[optionIndex]->description_2), DESC_LINE_Y_MID);
		setTextPos(&options[optionIndex]->description_3, OBJ_TO_MID_SCREEN_X((Sint16)(appWidth * screenScale_menu), options[optionIndex]->description_3), DESC_LINE_Y_BOTTOM);
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

void Menu::renderMenu() {
	for (i = topOnscreenIndex; i <= bottomOnscreenIndex; i++) {
		options[i]->render(cursorIndex == i);
	}
	cursor.renderSprite_menu();
}

const char *option_on_off[2] = { "On", "Off" };
const char *option_empty[1] = { "" };
const char *option_main_1_choices[10] = { "1", "11", "21", "31", "41", "51", "61", "71", "81", "91"};
const char *option_main_1_descriptions_line_1[1] = { "The level that the game starts on." };
const char *option_main_2_choices[9] = { "0", "1", "2", "3", "4", "5", "10", "20", "30" };
const char *option_main_2_descriptions_line_1[1] = { "The number of extra lives you start with." };
const char *option_main_3_choices[8] = { "Every 300 points", "Every 500 points", "Every 1000 points", "500 points only", "500 and 1000 only", "1000 points only", "1000 and 2000 only", "None" };
const char *option_main_3_descriptions_line_1[8] = { "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "No extra lives." };
const char *option_main_3_descriptions_line_2[8] = { "every 300 points.", "every 500 points.", "every 1000 points.", "at 500 points.", "at 500 and 1000 points.", "at 1000 points.", "at 1000 and 2000 points.", "" };
const char *option_main_3_descriptions_line_3[8] = { "", "", "", "", "", "", "", "" };
const char *option_main_4_descriptions_line_1[2] = { "The peasant meter decreases", "No penalty for escaped peasants." };
const char *option_main_4_descriptions_line_2[2] = { "every time a peasant escapes.", "" };
const char *option_main_4_descriptions_line_3[2] = { "", "" };
const char *option_main_5_choices[5] = { "Scaling", "Low", "Medium", "High", "Very High"};
const char *option_main_5_descriptions_line_1[5] = { "Archers appear more in later levels.", "Archers do not appear often.", "Archers appear semi-often.", "Archers appear very often.", "Archers appear non-stop!"};
const char *option_main_5_descriptions_line_2[5] = { "", "", "", "", "" };
const char *option_main_5_descriptions_line_3[5] = { "", "", "", "", "" };
const char *option_main_6_choices[6] = { "Off", "Very Low", "Low", "Normal", "High", "Very High", };
const char *option_main_6_descriptions_line_1[6] = { "Strong Bad does not talk.", "Strong Bad talks 50% less often.", "Strong Bad talks 25% less often.", "Strong Bad talks as often", "Strong Bad talks 25% more often.", "Strong Bad talks 50% more often." };
const char *option_main_6_descriptions_line_2[6] = { "", "", "", "as he did in the original game.", "", "" };
const char *option_main_6_descriptions_line_3[6] = { "", "", "", "", "", "" };
const char *option_main_7_choices[4] = { "Full", "Full Game", "Pixel-Perfect", "Pixel-Perfect Game" };
const char *option_main_7_descriptions_line_1[4] = { "Scale everything so that", "Scale the game to fill the screen.", "Scale so that everything uses integer", "Scale the game to be as big as possible" };
const char *option_main_7_descriptions_line_2[4] = { "the overlay fills the screen.", "The overlay will be cut off.", "scaling. Accurate, but possibly small.", "with integer scaling. The most accurate." };
const char *option_main_7_descriptions_line_3[4] = { "(Press A to apply, may take a few seconds)", "(Press A to apply, may take a few seconds)", "(Press A to apply, may take a few seconds)", "(Press A to apply, may take a few seconds)" };
const char *option_main_8_descriptions_line_1[1] = { "Toggle hidden cheats." };
const char *option_main_9_descriptions_line_1[1] = { "View the credits." };
const char *option_main_10_descriptions_line_1[1] = { "Quit the game." };
const char *option_cheats_1_descriptions_line_1[1] = { "Infinite lives, play forever!" };
const char *option_cheats_1_descriptions_line_2[1] = { "Unlocking this cheat also unlocks" };
const char *option_cheats_1_descriptions_line_3[1] = { "more starting lives options." };
const char *option_cheats_2_descriptions_line_1[1] = { "Enable Debug Mode. A/B to change" };
const char *option_cheats_2_descriptions_line_2[1] = { "peasant meter, L/R to" };
const char *option_cheats_2_descriptions_line_3[1] = { "change level, Select to win level." };
const char *option_cheats_3_descriptions_line_1[1] = { "Give Trogdor a more husky head." };
const char *option_cheats_4_descriptions_line_1[1] = { "Remove the game's difficulty" };
const char *option_cheats_4_descriptions_line_2[1] = { "by walking through cottages." };

void InitializeMenus() {
	TTF_Init();
	// if the menu font would end up being the same as font_serif_white_6_mult, just use that instead of creating a new font
	if (font_serif_white_6_mult.size == max(8, (int)(8 * screenScale_menu))) {
		menuFont = &font_serif_white_6_mult;
		setFont(menuFont, "fonts/serif_v01.ttf", 8, 5, TTF_STYLE_NORMAL, color_white, true);
	} else {
		menuFont = &font_serif_white_8;
		setFont(menuFont, "fonts/serif_v01.ttf", 8, 5, TTF_STYLE_NORMAL, color_white, true);
	}

	menu_main.prepareMenu(10, 6, &sprite_menu_cursor, false, 1, 32 + (16 * (screenScale_menu >= 2)), 168 + (8 * (screenScale_menu >= 2)), 0, 25, 175, 25, 15, 0, 0, true);
	if (!menusAreInitialized) {
		for (i = 0; i < 10; i++) {
			menu_main.options[i] = new MenuOption();
		}
	}
	MENU_STARTING_LEVEL->prepareMenuOption("Starting Level", option_main_1_choices,
		option_main_1_descriptions_line_1, option_empty, option_empty,
		NULL, 10, true, 0, true);
	MENU_STARTING_LIVES->prepareMenuOption("Starting Lives", option_main_2_choices,
		option_main_2_descriptions_line_1, option_empty, option_empty,
		NULL, 9, true, 3, true);
	MENU_EXTRA_LIVES->prepareMenuOption("Lives Interval", option_main_3_choices,
		option_main_3_descriptions_line_1, option_main_3_descriptions_line_2, option_main_3_descriptions_line_3,
		NULL, 8, false, 0, true);
	MENU_PEASANT_PENALTY->prepareMenuOption("Peasant Penalty", option_on_off,
		option_main_4_descriptions_line_1, option_main_4_descriptions_line_2, option_main_4_descriptions_line_3,
		NULL, 2, false, 0, true);
	MENU_ARCHER_FREQ->prepareMenuOption("Archer Frequency", option_main_5_choices,
		option_main_5_descriptions_line_1, option_main_5_descriptions_line_2, option_main_5_descriptions_line_3,
		NULL, 5, false, 0, true);
	if (screenScale_menu < 2) {
		MENU_COMMENT_FREQ->prepareMenuOption("Commentary Freq.", option_main_6_choices,
			option_main_6_descriptions_line_1, option_main_6_descriptions_line_2, option_main_6_descriptions_line_3,
			NULL, 6, false, 3, true);
	} else {
		MENU_COMMENT_FREQ->prepareMenuOption("Commentary Frequency", option_main_6_choices,
			option_main_6_descriptions_line_1, option_main_6_descriptions_line_2, option_main_6_descriptions_line_3,
			NULL, 6, false, 3, true);
	}
	MENU_SCALING->prepareMenuOption("Scaling", option_main_7_choices,
		option_main_7_descriptions_line_1, option_main_7_descriptions_line_2, option_main_7_descriptions_line_3,
		NULL, 4, false, 2, true);
	menu_main.options[7]->prepareMenuOption("Cheats", option_empty,
		option_main_8_descriptions_line_1, option_empty, option_empty,
		NULL, 1, true, 0, true);
	menu_main.options[8]->prepareMenuOption("Credits", option_empty,
		option_main_9_descriptions_line_1, option_empty, option_empty,
		NULL, 1, true, 0, true);
	menu_main.options[9]->prepareMenuOption("Quit Game", option_empty,
		option_main_10_descriptions_line_1, option_empty, option_empty,
		NULL, 1, true, 0, true);

	menu_cheats.prepareMenu(4, 6, &sprite_menu_cursor, false, 1, 32 + (16 * (screenScale_menu >= 2)), 160 + (16 * (screenScale_menu >= 2)), 0, 25, 175, 25, 15, 0, 0, true);
	if (!menusAreInitialized) {
		for (i = 0; i < 4; i++) {
			menu_cheats.options[i] = new MenuOption();
		}
	}
	CHEATS_INF_LIVES->prepareMenuOption("Infinite Lives", option_on_off,
		option_cheats_1_descriptions_line_1, option_cheats_1_descriptions_line_2, option_cheats_1_descriptions_line_3,
		"Secret Code?!?!", 2, true, 0, true);
	CHEAT_DEBUG_MODE->prepareMenuOption("Debug Mode", option_on_off,
		option_cheats_2_descriptions_line_1, option_cheats_2_descriptions_line_2, option_cheats_2_descriptions_line_3,
		"Class of 1981", 2, true, 0, true);
	CHEAT_BIG_HEAD_MODE->prepareMenuOption("Big Head Mode", option_on_off,
		option_cheats_3_descriptions_line_1, option_empty, option_empty,
		"Echidna Mushroom Pulley", 2, true, 0, true);
	CHEAT_NOCLIP->prepareMenuOption("Noclip", option_on_off,
		option_cheats_4_descriptions_line_1, option_cheats_4_descriptions_line_2, option_empty,
		"1994 Country", 2, true, 0, true);

	if (!menusAreInitialized) {
		MENU_STARTING_LIVES->choiceIsAllowed[6] = false;
		MENU_STARTING_LIVES->choiceIsAllowed[7] = false;
		MENU_STARTING_LIVES->choiceIsAllowed[8] = false;
		CHEATS_INF_LIVES->setLocked(true);
		CHEAT_DEBUG_MODE->setLocked(true);
		CHEAT_BIG_HEAD_MODE->setLocked(true);
		CHEAT_NOCLIP->setLocked(true);
	}

	menu_main.updateOptionPositions();
	menu_cheats.updateOptionPositions();

	menusAreInitialized = true;

	TTF_CloseFont(menuFont->font);
	TTF_Quit();
}