#include "menu.h"
#include "input.h"
#include "general.h"
#include "window.h"

Sint8 currOnscreenIndex;
Sint8 counter;
bool menusAreInitialized = false;
FontObject *menuFont;
FontObject *menuFont_frozen;

#define CURR_OPTION options[cursorIndex]
#define CURR_OPTION_ONSCREEN options[currOnscreenIndex]
#define CURR_SPACER_X (spacer_x * (currOnscreenIndex - topOnscreenIndex))

#define CENTER_X(textObj)  OBJ_TO_MID_SCREEN_X((Sint16)(appWidth * screenScale_menu), textObj)
#define DESC_LINE_Y_TOP    (Sint16)(start_y_desc * screenScale_menu)
#define DESC_LINE_Y_UPPER  (Sint16)((start_y_desc + (spacer_y_desc / 2)) * screenScale_menu)
#define DESC_LINE_Y_MID    (Sint16)((start_y_desc + spacer_y_desc) * screenScale_menu)
#define DESC_LINE_Y_LOWER  (Sint16)((start_y_desc + (spacer_y_desc * 3 / 2)) * screenScale_menu)
#define DESC_LINE_Y_BOTTOM (Sint16)((start_y_desc + (spacer_y_desc * 2)) * screenScale_menu)

/*************/
/* MENU PAGE */
/*************/

void MenuPage::prepareMenuPage(Sint8 num_lines, Sint16 st_x, Sint16 st_y, Sint16 sp_y, Sint8 align_type) {
	numLines = num_lines;
	start_x = st_x;
	start_y = sp_y;
	spacer_y = sp_y;
	alignType = align_type;
}

void MenuPage::setTextLine(Sint8 index, const char text[]) {
	setText(text, &lines[index], menuFont);
	switch (alignType) {
		case 0:
			lines[index].dstrect.x = (Sint16)(start_x * screenScale_menu);
			break;
		case 1:
			lines[index].dstrect.x = CENTER_X(lines[index]);
			break;
		default:
			lines[index].dstrect.x = (Sint16)(start_x * screenScale_menu) - lines[index].dstrect.w;
			break;
	}
	lines[index].dstrect.y = (Sint16)((start_y + (spacer_y * index)) * screenScale_menu);
}

void MenuPage::render() {
	for (counter = 0; counter < numLines; counter++) {
		renderText_menu(lines[counter], *menuFont);
	}
}

/*****************/
/* MENU NOTEBOOK */
/*****************/

void MenuNotebook::prepareMenuNotebook(Sint8 num_pages, Sint16 pos_x, Sint16 pos_y, Sint8 align_type) {
	numPages = num_pages;
	pageCounter.dstrect.y = (Sint16)(pos_y * screenScale_menu);
	setText("(1/5)", &pageCounter, menuFont);
	pageCounter_x = (Sint16)(pos_x * screenScale_menu);
	alignType_pageCounter = align_type;
	if (!menusAreInitialized) {
		index = 0;
	}
	updatePageCounterText();
}

void MenuNotebook::openNotebook() {
	index = 0;
	updatePageCounterText();
}

void MenuNotebook::updatePageCounterText() {
	updateText(&pageCounter, "(" + to_string((index + 1)) + "/" + to_string(numPages) + ")");
	switch (alignType_pageCounter) {
		case 0:
			pageCounter.dstrect.x = pageCounter_x;
			break;
		case 1:
			pageCounter.dstrect.x = pageCounter_x - (pageCounter.dstrect.w / 2);
			break;
		case 2:
			pageCounter.dstrect.x = pageCounter_x - pageCounter.dstrect.w;
			break;
		default:
			pageCounter.dstrect.x = -3000;
			break;
	}
}

Sint8 MenuNotebook::handleInput() {
	if (keyPressed(INPUT_LEFT)) {
		decrementPageNum();
	}
	if (keyPressed(INPUT_RIGHT)) {
		incrementPageNum();
	}
	if (keyPressed(INPUT_A)) {
		return index;
	}
	if (keyPressed(INPUT_B) || keyPressed(INPUT_SELECT)) {
		return -1;
	}
	return -2;
}

void MenuNotebook::decrementPageNum() {
	if (index > 0) {
		index--;
		updatePageCounterText();
	}
}

void MenuNotebook::incrementPageNum() {
	if (index < numPages - 1) {
		index++;
		updatePageCounterText();
	}
}

void MenuNotebook::renderNotebook() {
	pages[index]->render();
	if (alignType_pageCounter < 3) {
		renderText_menu(pageCounter, *menuFont);
	}
}

/***************/
/* MENU OPTION */
/***************/

void MenuOption::prepareMenuOption(const char label_ptr[], std::string choice_ptr[], std::string desc_ptr_1[], std::string desc_ptr_2[], std::string desc_ptr_3[], std::string altDesc_ptr, Uint8 numCh, bool oneDesc, Sint8 start, bool wrap, bool canFreeze) {
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
		optionCanFreeze = canFreeze;
		optionIsFrozen = false;
		optionIsLocked = false;
	}
	initLabel();
	updateLabel();
	initChoicesAndDescriptions();
	updateChoice(index);
	updateDescription(index);
}

void MenuOption::setFrozen(bool frozen, Sint8 ind) {
	optionIsFrozen = frozen;
	if (optionIsFrozen) {
		updateChoice(ind);
		updateDescription(ind);
	} else {
		updateChoice(index);
		updateDescription(index);
	}
}

void MenuOption::setLocked(bool locked) {
	optionIsLocked = locked;
	//setFrozen(locked, index);
	updateLabel();
	updateChoice(index);
	updateDescription(index);
}

void MenuOption::initLabel() {
	if (!labelPtr.empty()) {
		if (optionCanFreeze) {
			setText("???", &label, menuFont_frozen);
			setText(labelPtr, &label, menuFont_frozen);
		}
		setText(labelPtr, &label, menuFont);
	}
}

void MenuOption::updateLabel() {
	if (!optionIsLocked) {
		if (!labelPtr.empty()) {
			if (optionCanFreeze && (optionIsFrozen || optionIsLocked)) {
				setText(labelPtr, &label, menuFont_frozen);
			} else {
				setText(labelPtr, &label, menuFont);
			}
		}
	} else {
		setText("???", &label, menuFont_frozen);
	}
}

// this initializes text chars used in choices that aren't initially selected
void MenuOption::initChoicesAndDescriptions() {
	if (choicePtr != NULL) {
		for (counter = 0; counter < numChoices; counter++) {
			if (optionCanFreeze) setText(choicePtr[counter], &choice, menuFont_frozen);
			setText(choicePtr[counter], &choice, menuFont);
		}
	}
	if (descPtr_1 != NULL) {
		if (!oneDescription) {
			for (counter = 0; counter < numChoices; counter++) {
				if (optionCanFreeze) {
					setText(descPtr_1[counter], &description_1, menuFont_frozen);
					setText(descPtr_2[counter], &description_1, menuFont_frozen);
					setText(descPtr_3[counter], &description_1, menuFont_frozen);
				}
				setText(descPtr_1[counter], &description_1, menuFont);
				setText(descPtr_2[counter], &description_1, menuFont);
				setText(descPtr_3[counter], &description_1, menuFont);
			}
		}
	}
}

void MenuOption::updateChoice(Sint8 ind) {
	if (!optionIsLocked) {
		if (choicePtr != NULL) {
			if (optionCanFreeze && (optionIsFrozen || optionIsLocked)) {
				setText(choicePtr[ind], &choice, menuFont_frozen);
			} else {
				setText(choicePtr[ind], &choice, menuFont);
			}
		}
	} else {
		setText("", &choice, menuFont_frozen);
	}
}

void MenuOption::updateDescription(Sint8 ind) {
	if (!optionIsLocked) {
		if (descPtr_1 != NULL) {
			if (oneDescription) {
				setText(descPtr_1[0], &description_1, menuFont);
				setText(descPtr_2[0], &description_2, menuFont);
				setText(descPtr_3[0], &description_3, menuFont);
			} else {
				setText(descPtr_1[ind], &description_1, menuFont);
				setText(descPtr_2[ind], &description_2, menuFont);
				setText(descPtr_3[ind], &description_3, menuFont);
			}
		}
	} else {
		if (!altDescPtr.empty()) {
			setText(altDescPtr, &description_1, menuFont);
			setText("", &description_2, menuFont);
			setText("", &description_3, menuFont);
		}
	}
}

void MenuOption::setDescriptionToIndex(Uint8 forcedIndex) {
	setText(descPtr_1[forcedIndex], &description_1, menuFont);
	setText(descPtr_2[forcedIndex], &description_2, menuFont);
	setText(descPtr_3[forcedIndex], &description_3, menuFont);
}

void MenuOption::render(bool renderDescription) {
	if (optionCanFreeze && (optionIsFrozen || optionIsLocked)) {
		renderText_menu(label, *menuFont_frozen);
		renderText_menu(choice, *menuFont_frozen);
	} else {
		renderText_menu(label, *menuFont);
		renderText_menu(choice, *menuFont);
	}
	if (renderDescription) {
		renderText_menu(description_1, *menuFont);
		renderText_menu(description_2, *menuFont);
		renderText_menu(description_3, *menuFont);
	}
}

bool MenuOption::isValue(Uint8 val) {
	return (!optionIsLocked && index == val);
}

/********/
/* MENU */
/********/

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
	cursor = SpriteInstance(spriteObj, 0, 0, (float)spriteObj->dstrect.x, (float)spriteObj->dstrect.y);
	if (!menusAreInitialized) {
		numOptions = numOpt;
		numOnscreen = min(numOns, numOptions);
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

Sint8 Menu::handleInput(bool isDifficultyMenu) {
	if (keyPressed(INPUT_UP)) {
		decrementOption();
	}
	if (keyPressed(INPUT_DOWN)) {
		incrementOption();
	}
	if (keyPressed(INPUT_LEFT) && !(CURR_OPTION->optionIsFrozen || CURR_OPTION->optionIsLocked)) {
		decrementCurrOptionChoice();
		if (isDifficultyMenu && cursorIndex == 0) {
			setPreset(CURR_OPTION->index);
		}
	}
	if (keyPressed(INPUT_RIGHT) && !(CURR_OPTION->optionIsFrozen || CURR_OPTION->optionIsLocked)) {
		incrementCurrOptionChoice();
		if (isDifficultyMenu && cursorIndex == 0) {
			setPreset(CURR_OPTION->index);
		}
	}
	if (keyPressed(INPUT_A) || keyPressed(INPUT_START)) {
		return cursorIndex;
	}
	if (keyPressed(INPUT_B) || keyPressed(INPUT_SELECT)) {
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
	CURR_OPTION->updateChoice(CURR_OPTION->index);
	CURR_OPTION->updateDescription(CURR_OPTION->index);
	updateOptionChoicePosition(cursorIndex);
}

// This assumes at least one choice is allowed
void Menu::decrementCurrOptionChoice() {
	if (CURR_OPTION->choicesWrap) {
		do {
			CURR_OPTION->index--;
			if (CURR_OPTION->index < 0) {
				CURR_OPTION->index += CURR_OPTION->numChoices;
			}
		} while (!CURR_OPTION->choiceIsAllowed[CURR_OPTION->index]);
	} else if (!CURR_OPTION->choiceIsAllowed[CURR_OPTION->index]){
		do {
			CURR_OPTION->index--;
		} while (CURR_OPTION->index > 0 && !CURR_OPTION->choiceIsAllowed[CURR_OPTION->index]);
	}
	CURR_OPTION->updateChoice(CURR_OPTION->index);
	CURR_OPTION->updateDescription(CURR_OPTION->index);
	updateOptionChoicePosition(cursorIndex);
}

void Menu::setOptionChoice(Sint8 optionIndex, Sint8 choiceIndex) {
	options[optionIndex]->index = choiceIndex;
	options[optionIndex]->updateChoice(options[optionIndex]->index);
	options[optionIndex]->updateDescription(options[optionIndex]->index);
	updateOptionChoicePosition(optionIndex);
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
		setTextPos(&options[optionIndex]->description_1, CENTER_X(options[optionIndex]->description_1), DESC_LINE_Y_MID);
	} else if (options[optionIndex]->description_3.dstrect.w == 0) {
		setTextPos(&options[optionIndex]->description_1, CENTER_X(options[optionIndex]->description_1), DESC_LINE_Y_UPPER);
		setTextPos(&options[optionIndex]->description_2, CENTER_X(options[optionIndex]->description_2), DESC_LINE_Y_LOWER);
	} else {
		setTextPos(&options[optionIndex]->description_1, CENTER_X(options[optionIndex]->description_1), DESC_LINE_Y_TOP);
		setTextPos(&options[optionIndex]->description_2, CENTER_X(options[optionIndex]->description_2), DESC_LINE_Y_MID);
		setTextPos(&options[optionIndex]->description_3, CENTER_X(options[optionIndex]->description_3), DESC_LINE_Y_BOTTOM);
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

/***********************/
/* MENU INITIALIZATION */
/***********************/

std::string option_on_off[2] = { "On", "Off" };
std::string option_empty[1] = { "" };
std::string option_custom_only[1] = { "(Custom preset only.)" };
std::string option_main_starting_level_choices[10] = { "1", "11", "21", "31", "41", "51", "61", "71", "81", "91" };
std::string option_main_starting_level_descriptions_line_1[1] = { "The level that the game starts on." };
std::string option_main_level_order_choices[2] = { "Original", "Shuffled" };
std::string option_shuffle_levels_descriptions_line_1[2] = { "Shuffle the level order so it's", "Play using the original level order." };
std::string option_shuffle_levels_descriptions_line_2[2] = { "different every time you play.", "" };
std::string option_shuffle_levels_descriptions_line_3[2] = { "(Custom / Mips's Choice presets only.)", "" };
std::string option_main_preset_choices[6] = { "Custom", "Flash", "HTML5", "Hard", "Cruel", "Mips's Choice" };
std::string option_main_preset_descriptions_line_1[6] = { "Make your own rules!", "Default settings. Same as", "Settings from the HTML5 port.", "Fewer extra lives, faster", "No extra lives, tons of danger.", "Someone's favorite..." };
std::string option_main_preset_descriptions_line_2[6] = { "Cheats and level select", "the original Flash game.", "No peasant penalty, all treasure huts.", "and more abundant enemies.", "For Trogdor masters!", "Fewer extra lives, crazy fast arrows," };
std::string option_main_preset_descriptions_line_3[6] = { "are also allowed.", "", "", "For Trogdor pros.", "", "all treasure huts, shuffled levels." };
std::string option_main_extra_lives_choices[9] = { "0", "1", "2", "3", "4", "5", "10", "20", "30" };
std::string option_main_extra_lives_descriptions_line_1[1] = { "The number of extra lives you start with." };
std::string option_main_lives_interval_choices[8] = { "Every 300 points", "Every 500 points", "Every 1000 points", "500 points only", "500 and 1000 only", "1000 points only", "1000 and 2000 only", "None" };
std::string option_main_lives_interval_descriptions_line_1[8] = { "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "No extra lives." };
std::string option_main_lives_interval_descriptions_line_2[8] = { "every 300 points.", "every 500 points.", "every 1000 points.", "at 500 points.", "at 500 and 1000 points.", "at 1000 points.", "at 1000 and 2000 points.", "" };
std::string option_main_lives_interval_descriptions_line_3[8] = { "", "", "", "", "", "", "", "" };
std::string option_main_music_choices[2] = { "Off", "Stinkoman 20X6"};
std::string option_main_music_descriptions_line_1[2] = { "Don't play music in-game.", "Play music from Stinkoman 20X6." };
std::string option_main_music_descriptions_line_2[2] = { "", "The song changes depending on the level." };
std::string option_main_music_descriptions_line_3[2] = { "", "" };
std::string option_main_peasant_penalty_descriptions_line_1[2] = { "The peasant meter decreases", "No penalty for escaped peasants." };
std::string option_main_peasant_penalty_descriptions_line_2[2] = { "every time a peasant escapes.", "" };
std::string option_main_peasant_penalty_descriptions_line_3[2] = { "", "" };
std::string option_main_treasure_huts_choices[3] = { "Original", "New", "Off" };
std::string option_main_treasure_huts_descriptions_line_1[3] = { "After you enter a treasure hut, you cannot", "You can enter all treasure huts.", "Treasure huts are disabled."};
std::string option_main_treasure_huts_descriptions_line_2[3] = { "enter huts from other level layouts.", "Same behavior as the HTML5 port.", ""};
std::string option_main_treasure_huts_descriptions_line_3[3] = { "Same behavior as the original game.", "", ""};
std::string option_main_archer_freq_choices[6] = { "Original", "New", "Low", "Medium", "High", "Non-stop" };
std::string option_main_archer_freq_descriptions_line_1[6] = { "Archers appear more in later levels.", "Archers appear more in later levels.", "Archers do not appear often.", "Archers appear semi-often.", "Archers appear very often.", "Archers appear non-stop!"};
std::string option_main_archer_freq_descriptions_line_2[6] = { "Same behavior as the original game.", "New scaling that's more evenly", "", "", "", ""};
std::string option_main_archer_freq_descriptions_line_3[6] = { "", "distributed between levels.", "", "", "", ""};
std::string option_main_knight_behavior_choices[2] = { "Original", "New" };
std::string option_main_knight_behavior_descriptions_line_1[2] = { "Knights briefly pause and change", "Knights do not change their" };
std::string option_main_knight_behavior_descriptions_line_2[2] = { "position after you die.", "movement after you die." };
std::string option_main_knight_behavior_descriptions_line_3[2] = { "", "Behavior is similar to the HTML5 port." };
std::string option_main_knight_speed_choices[5] = { "Very Slow", "Slow", "Normal", "Fast", "Very Fast" };
std::string option_main_knight_speed_descriptions_line_1[1] = { "Change how quickly knights move." };
std::string option_main_arrow_speed_choices[5] = { "Slow", "Normal", "Fast", "Very Fast", "Insane" };
std::string option_main_arrow_speed_descriptions_line_1[1] = { "Change how quickly arrows move." };
#if defined(WII) || defined(GAMECUBE) || defined(THREEDS)
std::string option_main_frame_rate_choices[11] = { "16 FPS (original)", "20 FPS", "25 FPS", "30 FPS", "40 FPS", "50 FPS", "55 FPS", "60 FPS (may run slow)", "90 FPS", "120 FPS", "144 FPS" };
#else
std::string option_main_frame_rate_choices[11] = { "16 FPS (original)", "20 FPS", "25 FPS", "30 FPS", "40 FPS", "50 FPS", "55 FPS", "60 FPS", "90 FPS", "120 FPS", "144 FPS" };
#endif
std::string option_main_frame_rate_descriptions_line_1[1] = { "Higher frame rate = smoother gameplay." };
std::string option_main_frame_rate_descriptions_line_2[1] = { "(Original Flash game is 16 FPS)" };
std::string option_main_frame_rate_descriptions_line_3[1] = { "" };
std::string option_main_level_tran_choices[2] = { "Original", "Button Press" };
std::string option_main_level_tran_descriptions_line_1[2] = { "After beating a level, the next", "After beating a level, press " + INPUT_CONFIRM };
std::string option_main_level_tran_descriptions_line_2[2] = { "level will load automatically.", "or " + INPUT_PAUSE + " to load the next level." };
std::string option_main_level_tran_descriptions_line_3[2] = { "", "" };
std::string option_main_comment_freq_choices[7] = { "Off", "Very Low", "Low", "Normal", "High", "Very High", "Let's-Player" };
std::string option_main_comment_freq_descriptions_line_1[7] = { "Strong Bad does not talk.", "Strong Bad rarely talks.", "Strong Bad talks less than usual.", "Strong Bad talks as often", "Strong Bad talks a bit more often.", "Strong Bad talks much more often.", "Strong Bad won't shut up!" };
std::string option_main_comment_freq_descriptions_line_2[7] = { "", "", "", "as he did in the original game.", "", "", "(He talks twice as much as usual.)"};
std::string option_main_comment_freq_descriptions_line_3[7] = { "", "", "", "", "", "", "" };
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII) || defined(GAMECUBE) || defined(THREEDS) || defined(XBOX)
std::string press_confirm_to_apply = "(Press " + INPUT_CONFIRM + " to apply, may take a few seconds)";
#else
std::string press_confirm_to_apply = "(Press " + INPUT_CONFIRM + " to apply)";
#endif
#if defined(THREEDS)
std::string option_main_scaling_choices[4] = { "N/A", "N/A", "N/A", "N/A" };
std::string option_main_scaling_descriptions_line_1[4] = { "(Unused)", "(Unused)", "(Unused)", "(Unused)" };
std::string option_main_scaling_descriptions_line_2[4] = { "", "", "", "" };
std::string option_main_scaling_descriptions_line_3[4] = { "", "", "", "" };
#elif defined(PSP)
std::string option_main_scaling_choices[4] = { "Pixel-Perfect", "", "Full", "Full Game" };
std::string option_main_scaling_descriptions_line_1[4] = { "Scale so that everything uses integer", "", "Scale everything so that", "Scale the game to fill the screen." };
std::string option_main_scaling_descriptions_line_2[4] = { "scaling. Accurate, but small.", "", "the overlay fills the screen.", "The overlay will be cut off." };
std::string option_main_scaling_descriptions_line_3[4] = { press_confirm_to_apply, "", press_confirm_to_apply, press_confirm_to_apply };
#elif defined(WII) || defined(GAMECUBE) || defined(XBOX)
std::string option_main_scaling_choices[4] = { "Pixel-Perfect", "", "", "Full Game" };
std::string option_main_scaling_descriptions_line_1[4] = { "Scale so that everything uses integer", "", "", "Scale the game to fill the screen." };
std::string option_main_scaling_descriptions_line_2[4] = { "scaling. The most accurate.", "", "", "The overlay will be cut off." };
std::string option_main_scaling_descriptions_line_3[4] = { press_confirm_to_apply, "", "", press_confirm_to_apply };
#elif defined(WII_U)
std::string option_main_scaling_choices[4] = { "Pixel-Perfect", "Pixel-Perfect Game", "", "" };
std::string option_main_scaling_descriptions_line_1[4] = { "Scale so that everything uses integer", "Scale the game to be as big as possible", "", "" };
std::string option_main_scaling_descriptions_line_2[4] = { "scaling. Accurate, but small.", "with integer scaling. The most accurate.", "", "" };
std::string option_main_scaling_descriptions_line_3[4] = { press_confirm_to_apply, press_confirm_to_apply, "", "" };
#elif defined(SWITCH)
std::string option_main_scaling_choices[4] = { "Pixel-Perfect", "Pixel-Perfect Game", "Full", "" };
std::string option_main_scaling_descriptions_line_1[4] = { "Scale so that everything uses integer", "Scale the game to be as big as possible", "Scale everything so that", "" };
std::string option_main_scaling_descriptions_line_2[4] = { "scaling. Accurate, but possibly small.", "with integer scaling. The most accurate.", "the overlay fills the screen.", "" };
std::string option_main_scaling_descriptions_line_3[4] = { press_confirm_to_apply, press_confirm_to_apply, press_confirm_to_apply, "" };
#else
std::string option_main_scaling_choices[4] = { "Pixel-Perfect", "Pixel-Perfect Game", "Full", "Full Game" };
std::string option_main_scaling_descriptions_line_1[4] = { "Scale so that everything uses integer", "Scale the game to be as big as possible", "Scale everything so that", "Scale the game to fill the screen." };
std::string option_main_scaling_descriptions_line_2[4] = { "scaling. Accurate, but possibly small.", "with integer scaling. The most accurate.", "the overlay fills the screen.", "The overlay will be cut off." };
std::string option_main_scaling_descriptions_line_3[4] = { press_confirm_to_apply, press_confirm_to_apply, press_confirm_to_apply, press_confirm_to_apply };
#endif
std::string option_main_difficulty_descriptions_line_1[1] = { "Change settings related to" };
std::string option_main_difficulty_descriptions_line_2[1] = { "game difficulty." };
std::string option_main_cosmetic_descriptions_line_1[1] = { "Change settings related to" };
std::string option_main_cosmetic_descriptions_line_2[1] = { "game audio and video." };
std::string option_main_other_descriptions_line_1[1] = { "Change miscellaneous settings." };
std::string option_main_cheats_descriptions_line_1[1] = { "Toggle secret cheats." };
std::string option_main_cheats_descriptions_line_2[1] = { "Follow the hints!" };
std::string option_main_highscores_descriptions_line_1[1] = { "View your high scores." };
std::string option_main_credits_descriptions_line_1[1] = { "View the credits." };
std::string option_main_reset_settings_descriptions_line_1[1] = { "Reset all settings to default." };
std::string option_main_quit_descriptions_line_1[1] = { "Quit the game." };
std::string option_cheats_inf_lives_descriptions_line_1[1] = { "Infinite lives, play forever!" };
std::string option_cheats_inf_lives_descriptions_line_2[1] = { "Unlocking this cheat also unlocks" };
std::string option_cheats_inf_lives_descriptions_line_3[1] = { "more starting lives options." };
std::string option_speedy_mode_choices[4] = { "Off", "Fast", "Faster", "Fastest" };
std::string option_cheats_speedy_mode_descriptions_line_1[1] = { "Trogdor moves much faster!" };
std::string option_cheats_debug_mode_descriptions_line_1[1] = { "Enable Debug Mode." };
std::string option_cheats_debug_mode_descriptions_line_2[1] = { "Press buttons to do things." };
std::string option_main_big_head_mode_descriptions_line_1[1] = { "Give Trogdor a more husky head." };
std::string option_cheats_noclip_descriptions_line_1[1] = { "Remove the game's difficulty" };
std::string option_cheats_noclip_descriptions_line_2[1] = { "by walking through cottages." };
#if defined(WII_U) || defined(VITA) || defined(PSP) || defined(WII) || defined(GAMECUBE) || defined(THREEDS) || defined(XBOX)
#if defined(WII_U)
std::string console_quit_line_1 = "WHY ARE YOU STILL USING A WII U?!";
#elif defined(VITA)
std::string console_quit_line_1 = "WHY ARE YOU STILL USING A VITA?!";
#elif defined(PSP)
std::string console_quit_line_1 = "WHY ARE YOU STILL USING A PSP?!";
#elif defined(WII)
std::string console_quit_line_1 = "WHY ARE YOU STILL USING A WII?!";
#elif defined(GAMECUBE)
std::string console_quit_line_1 = "WHY ARE YOU STILL USING A GAMECUBE?!";
#elif defined(THREEDS)
std::string console_quit_line_1 = "WHY ARE YOU STILL USING A 3DS?!";
#elif defined(XBOX)
std::string console_quit_line_1 = "WHY ARE YOU STILL USING AN XBOX?!";
#else
std::string console_quit_line_1 = "WHY ARE YOU STILL USING WINDOWS 98?!";
#endif
std::string console_quit_line_2 = "WHAT IS WRONG WITH YOU?! STOP BUYING";
std::string console_quit_line_3 = "CONSOLES FROM THRIFT STORES, MAN!";
#else
#if defined(SWITCH)
std::string console_quit_line_1 = "Switch over? Virus equals very yes?";
#elif defined(ANDROID)
std::string console_quit_line_1 = "Android over? Virus equals very yes?";
#else
std::string console_quit_line_1 = "Computer over? Virus equals very yes?";
#endif
std::string console_quit_line_2 = "";
std::string console_quit_line_3 = "";
#endif
std::string option_quit_descriptions_line_1[7] = { "Hey Player, I really like your", "Strong Bad's gonna get the", "Are you sure you want to quit this", "Don't leave yet -- There's a", "If you leave now, how will you", "Click \"Keep playing\" to email strong bad", console_quit_line_1};
std::string option_quit_descriptions_line_2[7] = { "\"quitting to play a different game\"", "high score, man, 50,000.", "great game?", "peasant around that corner!", "get ye flask?", "", console_quit_line_2};
std::string option_quit_descriptions_line_3[7] = { "costume.", "", "", "", "", "", console_quit_line_3};

void InitializeMenus() {
	TTF_Init();
	// if the menu font would end up being the same as font_serif_white_6_mult, just use that instead of initializing an exclusive font
	if (font_serif_white_6_mult.size == getDesiredFontSize(&font_serif_white_8)) {
		menuFont = &font_serif_white_6_mult;
	} else {
		menuFont = &font_serif_white_8;
	}
	setFont(menuFont, "fonts/serif_v01.ttf", 8, 5, TTF_STYLE_NORMAL, color_white, true);
	menuFont_frozen = &font_serif_gray_8;
	setFont(&font_serif_gray_8, "fonts/serif_v01.ttf", 8, 5, TTF_STYLE_NORMAL, color_gray, true);

	/* Options Menu */
	menu_main.prepareMenu(MENU_NUM_OPTIONS, 6, &sprite_menu_cursor, false, 1, 32 + (16 * (screenScale_menu >= 2)), 168 + (8 * (screenScale_menu >= 2)), 0, 25, 175, 25, 15, 0, 0, true);
	if (!menusAreInitialized) {
		for (i = 0; i < MENU_NUM_OPTIONS; i++) {
			menu_main.options[i] = new MenuOption();
		}
	}

	MENU_DIFFICULTY->prepareMenuOption("Difficulty Settings", option_empty,
		option_main_difficulty_descriptions_line_1, option_main_difficulty_descriptions_line_2, option_empty,
		"", 1, true, 0, true, false);
	MENU_COSMETIC->prepareMenuOption("Cosmetic Settings", option_empty,
		option_main_cosmetic_descriptions_line_1, option_main_cosmetic_descriptions_line_2, option_empty,
		"", 1, true, 0, true, false);
	MENU_OTHER->prepareMenuOption("Other Settings", option_empty,
		option_main_other_descriptions_line_1, option_empty, option_empty,
		"", 1, true, 0, true, false);
	MENU_CHEATS->prepareMenuOption("Cheats", option_empty,
		option_main_cheats_descriptions_line_1, option_main_cheats_descriptions_line_2, option_custom_only,
		"", 1, true, 0, true, false);
	MENU_RESET_SETTINGS->prepareMenuOption("Reset to Default", option_empty,
		option_main_reset_settings_descriptions_line_1, option_empty, option_empty,
		"", 1, true, 0, true, false);
	MENU_HIGHSCORES->prepareMenuOption("High Scores", option_empty,
		option_main_highscores_descriptions_line_1, option_empty, option_empty,
		"", 1, true, 0, true, false);
	MENU_CREDITS->prepareMenuOption("Credits", option_empty,
		option_main_credits_descriptions_line_1, option_empty, option_empty,
		"", 1, true, 0, true, false);
	MENU_QUIT->prepareMenuOption("Quit Game", option_empty,
		option_main_quit_descriptions_line_1, option_empty, option_empty,
		"", 1, true, 0, true, false);

	/* Difficulty Settings Menu */
	menu_difficulty.prepareMenu(DIFFICULTY_NUM_OPTIONS, 6, &sprite_menu_cursor, false, 1, 32 + (16 * (screenScale_menu >= 2)), 160 + (16 * (screenScale_menu >= 2)), 0, 25, 175, 25, 15, 0, 0, true);
	if (!menusAreInitialized) {
		for (i = 0; i < DIFFICULTY_NUM_OPTIONS; i++) {
			menu_difficulty.options[i] = new MenuOption();
		}
	}
	MENU_PRESET->prepareMenuOption("Preset", option_main_preset_choices,
		option_main_preset_descriptions_line_1, option_main_preset_descriptions_line_2, option_main_preset_descriptions_line_3,
		"", 6, false, 1, true, true);
	MENU_EXTRA_LIVES->prepareMenuOption("Extra Lives", option_main_extra_lives_choices,
		option_main_extra_lives_descriptions_line_1, option_empty, option_empty,
		"", 9, true, 3, true, true);
	MENU_LIVES_INTERVAL->prepareMenuOption("Lives Interval", option_main_lives_interval_choices,
		option_main_lives_interval_descriptions_line_1, option_main_lives_interval_descriptions_line_2, option_main_lives_interval_descriptions_line_3,
		"", 8, false, 0, true, true);
	MENU_PEASANT_PENALTY->prepareMenuOption("Peasant Penalty", option_on_off,
		option_main_peasant_penalty_descriptions_line_1, option_main_peasant_penalty_descriptions_line_2, option_main_peasant_penalty_descriptions_line_3,
		"", 2, false, 0, true, true);
	MENU_KNIGHT_SPEED->prepareMenuOption("Knight Speed", option_main_knight_speed_choices,
		option_main_knight_speed_descriptions_line_1, option_empty, option_empty,
		"", 5, true, 2, true, true);
	MENU_ARROW_SPEED->prepareMenuOption("Arrow Speed", option_main_arrow_speed_choices,
		option_main_arrow_speed_descriptions_line_1, option_empty, option_empty,
		"", 5, true, 1, true, true);
	MENU_ARCHER_FREQ->prepareMenuOption("Archer Frequency", option_main_archer_freq_choices,
		option_main_archer_freq_descriptions_line_1, option_main_archer_freq_descriptions_line_2, option_main_archer_freq_descriptions_line_3,
		"", 6, false, 0, true, true);
	MENU_TREASURE_HUTS->prepareMenuOption("Treasure Huts", option_main_treasure_huts_choices,
		option_main_treasure_huts_descriptions_line_1, option_main_treasure_huts_descriptions_line_2, option_main_treasure_huts_descriptions_line_3,
		"", 3, false, 0, true, true);

	/* Cosmetic Settings Menu */
	menu_cosmetic.prepareMenu(COSMETIC_NUM_OPTIONS, 6, &sprite_menu_cursor, false, 1, 32 + (16 * (screenScale_menu >= 2)), 160 + (16 * (screenScale_menu >= 2)), 0, 25, 175, 25, 15, 0, 0, true);
	if (!menusAreInitialized) {
		for (i = 0; i < COSMETIC_NUM_OPTIONS; i++) {
			menu_cosmetic.options[i] = new MenuOption();
		}
	}
	MENU_FRAME_RATE->prepareMenuOption("Frame Rate", option_main_frame_rate_choices,
		option_main_frame_rate_descriptions_line_1, option_main_frame_rate_descriptions_line_2, option_main_frame_rate_descriptions_line_3,
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(PSP) || defined(XBOX)
		"", 8, true, 7, true, false);
#elif defined(THREEDS)
		"", 4, true, 3, true, false);
#elif defined(WII) || defined(GAMECUBE)
		"", 8, true, 6, true, false);
#else
		"", 11, true, 7, true, false);
#endif
	MENU_MUSIC->prepareMenuOption("Music", option_main_music_choices,
		option_main_music_descriptions_line_1, option_main_music_descriptions_line_2, option_main_music_descriptions_line_3,
		"", 2, false, 0, true, false);
	MENU_COMMENT_FREQ->prepareMenuOption("Commentary", option_main_comment_freq_choices,
		option_main_comment_freq_descriptions_line_1, option_main_comment_freq_descriptions_line_2, option_main_comment_freq_descriptions_line_3,
		"", 7, false, 3, true, false);
	MENU_BIG_HEAD_MODE->prepareMenuOption("Big Head Mode", option_on_off,
		option_main_big_head_mode_descriptions_line_1, option_empty, option_empty,
		"", 2, true, 1, true, false);
	MENU_SCALING->prepareMenuOption("Screen Scaling", option_main_scaling_choices,
		option_main_scaling_descriptions_line_1, option_main_scaling_descriptions_line_2, option_main_scaling_descriptions_line_3,
		"", 4, false, scalingType, true, false);

	/* Other Settings Menu */
	menu_other.prepareMenu(OTHER_NUM_OPTIONS, 6, &sprite_menu_cursor, false, 1, 32 + (16 * (screenScale_menu >= 2)), 160 + (16 * (screenScale_menu >= 2)), 0, 25, 175, 25, 15, 0, 0, true);
	if (!menusAreInitialized) {
		for (i = 0; i < OTHER_NUM_OPTIONS; i++) {
			menu_other.options[i] = new MenuOption();
		}
	}
	MENU_STARTING_LEVEL->prepareMenuOption("Starting Level", option_main_starting_level_choices,
		option_main_starting_level_descriptions_line_1, option_custom_only, option_empty,
		"", 10, true, 0, true, true);
	MENU_SHUFFLE_LEVELS->prepareMenuOption("Shuffle Levels", option_on_off,
		option_shuffle_levels_descriptions_line_1, option_shuffle_levels_descriptions_line_2, option_shuffle_levels_descriptions_line_3,
		"", 2, false, 1, true, true);
	MENU_KNIGHT_BEHAVIOR->prepareMenuOption("Knight Behavior", option_main_knight_behavior_choices,
		option_main_knight_behavior_descriptions_line_1, option_main_knight_behavior_descriptions_line_2, option_main_knight_behavior_descriptions_line_3,
		"", 2, false, 1, true, false);
	MENU_LEVEL_TRAN->prepareMenuOption("Level Transition", option_main_level_tran_choices,
		option_main_level_tran_descriptions_line_1, option_main_level_tran_descriptions_line_2, option_main_level_tran_descriptions_line_3,
		"", 2, false, 0, true, false);

	/* Cheats Menu */
	menu_cheats.prepareMenu(CHEAT_NUM_OPTIONS, 6, &sprite_menu_cursor, false, 1, 32 + (16 * (screenScale_menu >= 2)), 160 + (16 * (screenScale_menu >= 2)), 0, 25, 175, 25, 15, 0, 0, true);
	if (!menusAreInitialized) {
		for (i = 0; i < CHEAT_NUM_OPTIONS; i++) {
			menu_cheats.options[i] = new MenuOption();
		}
	}
	MENU_INF_LIVES->prepareMenuOption("Infinite Lives", option_on_off,
		option_cheats_inf_lives_descriptions_line_1, option_cheats_inf_lives_descriptions_line_2, option_cheats_inf_lives_descriptions_line_3,
		"Secret Code?!?!", 2, true, 1, true, true);
	MENU_SPEEDY_MODE->prepareMenuOption("Speedy Trogdor", option_speedy_mode_choices,
		option_cheats_speedy_mode_descriptions_line_1, option_empty, option_empty,
		"S&K Mushroom Pulley", 4, true, 0, true, true);
	MENU_NOCLIP->prepareMenuOption("Noclip", option_on_off,
		option_cheats_noclip_descriptions_line_1, option_cheats_noclip_descriptions_line_2, option_empty,
		"1994 Country", 2, true, 1, true, true);
	MENU_DEBUG_MODE->prepareMenuOption("Debug Mode", option_on_off,
		option_cheats_debug_mode_descriptions_line_1, option_cheats_debug_mode_descriptions_line_2, option_empty,
		"Class of 1981", 2, true, 1, true, true);

	/* High Scores Notebooks */
	menu_highscores_1.prepareMenuNotebook(1, 304, 216, 3);
	menu_highscores_2.prepareMenuNotebook(1, 304, 216, 3);
	menu_highscores_3.prepareMenuNotebook(1, 304, 216, 3);
	if (!menusAreInitialized) {
		for (i = 0; i < 1; i++) {
			menu_highscores_1.pages[i] = new MenuPage();
			menu_highscores_2.pages[i] = new MenuPage();
			menu_highscores_3.pages[i] = new MenuPage();
		}
	}
	menu_highscores_1.pages[0]->prepareMenuPage(1, 0, 30, 20, 1);
	menu_highscores_1.pages[0]->setTextLine(0, "YE OLDE HI-SCORES");
	menu_highscores_2.pages[0]->prepareMenuPage(8, 96, 30, 20, 0);
	menu_highscores_2.pages[0]->setTextLine(0, "");
	menu_highscores_2.pages[0]->setTextLine(1, "");
	menu_highscores_2.pages[0]->setTextLine(2, "Flash:");
	menu_highscores_2.pages[0]->setTextLine(3, "HTML5:");
	menu_highscores_2.pages[0]->setTextLine(4, "Hard:");
	menu_highscores_2.pages[0]->setTextLine(5, "Cruel:");
	menu_highscores_2.pages[0]->setTextLine(6, "Mips:");
	menu_highscores_2.pages[0]->setTextLine(7, "Custom:");
	menu_highscores_3.pages[0]->prepareMenuPage(8, 224, 30, 20, 2);
	menu_highscores_3.pages[0]->setTextLine(0, "");
	menu_highscores_3.pages[0]->setTextLine(1, "");
	updateHighScores();

	/* Credits Notebook */
	menu_credits.prepareMenuNotebook(6, 304, 216, 2);
	if (!menusAreInitialized) {
		for (i = 0; i < 6; i++) {
			menu_credits.pages[i] = new MenuPage();
		}
	}
	menu_credits.pages[0]->prepareMenuPage(10, 0, 30, 20, 1);
	menu_credits.pages[0]->setTextLine(0, "- ORIGINAL GAME -");
	menu_credits.pages[0]->setTextLine(1, "");
	menu_credits.pages[0]->setTextLine(2, "Programming: Jonathan Howe");
	menu_credits.pages[0]->setTextLine(3, "Design: Mike Chapman, Matt Chapman");
	menu_credits.pages[0]->setTextLine(4, "HTML5 Port: Aeon Softworks");
	menu_credits.pages[0]->setTextLine(5, "");
	menu_credits.pages[0]->setTextLine(6, "https://homestarrunner.com");
	menu_credits.pages[0]->setTextLine(7, "");
	menu_credits.pages[0]->setTextLine(8, "https://www.youtube.com/user");
	menu_credits.pages[0]->setTextLine(9, "/homestarrunnerdotcom");

	menu_credits.pages[1]->prepareMenuPage(8, 0, 30, 20, 1);
	menu_credits.pages[1]->setTextLine(0, "- THIS RECREATION -");
	menu_credits.pages[1]->setTextLine(1, "");
	menu_credits.pages[1]->setTextLine(2, "Mips96");
	menu_credits.pages[1]->setTextLine(3, "");
	menu_credits.pages[1]->setTextLine(4, "https://github.com/Mips96");
	menu_credits.pages[1]->setTextLine(5, "/Trogdor-Reburninated");
	menu_credits.pages[1]->setTextLine(6, "");
	menu_credits.pages[1]->setTextLine(7, "v2.0");

	menu_credits.pages[2]->prepareMenuPage(5, 0, 30, 20, 1);
	menu_credits.pages[2]->setTextLine(0, "- STINKOMAN MUSIC -");
	menu_credits.pages[2]->setTextLine(1, "");
	menu_credits.pages[2]->setTextLine(2, "Jonathan Howe");
	menu_credits.pages[2]->setTextLine(3, "");
	menu_credits.pages[2]->setTextLine(4, "U.Z. Inu");

	menu_credits.pages[3]->prepareMenuPage(7, 0, 30, 20, 1);
	menu_credits.pages[3]->setTextLine(0, "- SPECIAL THANKS -");
	menu_credits.pages[3]->setTextLine(1, "");
	menu_credits.pages[3]->setTextLine(2, "Autosave + Level Transition ideas:");
	menu_credits.pages[3]->setTextLine(3, "Jeremy Elkayam's Trogba");
	menu_credits.pages[3]->setTextLine(4, "");
	menu_credits.pages[3]->setTextLine(5, "https://jeremyelkayam.itch.io");
	menu_credits.pages[3]->setTextLine(6, "/trogba");

	menu_credits.pages[4]->prepareMenuPage(7, 0, 30, 20, 1);
	menu_credits.pages[4]->setTextLine(0, "- LIBRARIES -");
	menu_credits.pages[4]->setTextLine(1, "");
#if defined(SDL1)
	menu_credits.pages[4]->setTextLine(2, "SDL");
	menu_credits.pages[4]->setTextLine(3, "SDL_image");
	menu_credits.pages[4]->setTextLine(4, "SDL_mixer");
	menu_credits.pages[4]->setTextLine(5, "SDL_ttf");
	menu_credits.pages[4]->setTextLine(6, "SDL_gfx");
#else
	menu_credits.pages[4]->setTextLine(2, "SDL2");
	menu_credits.pages[4]->setTextLine(3, "SDL2_image");
#if defined(PSP)
	menu_credits.pages[4]->setTextLine(4, "OSLibAudio");
#else
	menu_credits.pages[4]->setTextLine(4, "SDL2_mixer");
#endif
	menu_credits.pages[4]->setTextLine(5, "SDL2_ttf");
	menu_credits.pages[4]->setTextLine(6, "");
#endif

	menu_credits.pages[5]->prepareMenuPage(9, 0, 30, 20, 1);
	menu_credits.pages[5]->setTextLine(0, "- WANT MORE? -");
	menu_credits.pages[5]->setTextLine(1, "");
	menu_credits.pages[5]->setTextLine(2, "Trogdor: Reburninated is available");
	menu_credits.pages[5]->setTextLine(3, "for a wide variety of");
	menu_credits.pages[5]->setTextLine(4, "homebrew-enabled systems, old and new.");
	menu_credits.pages[5]->setTextLine(5, "Play it everywhere!");
	menu_credits.pages[5]->setTextLine(6, "");
	menu_credits.pages[5]->setTextLine(7, "https://github.com/Mips96");
	menu_credits.pages[5]->setTextLine(8, "/Trogdor-Reburninated");

	/* Quit Menu */
	menu_quit.prepareMenu(QUIT_NUM_OPTIONS, 7, &sprite_menu_cursor, false, 1, 128 + (16 * (screenScale_menu >= 2)), 160 + (16 * (screenScale_menu >= 2)), 0, 132, 60, 25, 15, 0, 0, true);
	if (!menusAreInitialized) {
		for (i = 0; i < QUIT_NUM_OPTIONS; i++) {
			menu_quit.options[i] = new MenuOption();
		}
	}
	QUIT_BACK->prepareMenuOption("Keep playing", option_empty,
		option_quit_descriptions_line_1, option_quit_descriptions_line_2, option_quit_descriptions_line_3,
		"", 1, false, 0, true, false);
	QUIT_CONFIRM->prepareMenuOption("Quit it!", option_empty,
		option_quit_descriptions_line_1, option_quit_descriptions_line_2, option_quit_descriptions_line_3,
		"", 1, false, 0, true, false);

	/* Initializing Values */
	if (!menusAreInitialized) {
		MENU_EXTRA_LIVES->choiceIsAllowed[6] = false;
		MENU_EXTRA_LIVES->choiceIsAllowed[7] = false;
		MENU_EXTRA_LIVES->choiceIsAllowed[8] = false;
		MENU_INF_LIVES->setLocked(true);
		MENU_SPEEDY_MODE->setLocked(true);
		MENU_NOCLIP->setLocked(true);
		MENU_DEBUG_MODE->setLocked(true);
#if defined(THREEDS) || defined(PSP) || defined(WII) || defined(GAMECUBE) || defined(XBOX)
		MENU_SCALING->choiceIsAllowed[1] = false;
#endif
#if defined(THREEDS) || defined(WII) || defined(GAMECUBE) || defined(XBOX) || defined(WII_U)
		MENU_SCALING->choiceIsAllowed[2] = false;
#endif
#if defined(THREEDS) || defined(WII_U) || defined(SWITCH)
		MENU_SCALING->choiceIsAllowed[3] = false;
#endif
	}

	menu_main.updateOptionPositions();
	menu_difficulty.updateOptionPositions();
	menu_cosmetic.updateOptionPositions();
	menu_cheats.updateOptionPositions();
	menu_quit.updateOptionPositions();
	setPreset(MENU_PRESET->index);
	updateHighScores();

	menusAreInitialized = true;

	TTF_CloseFont(menuFont->font);
	TTF_CloseFont(menuFont_frozen->font);
	TTF_Quit();
}

State_Settings_General getSettingsGeneral() {
	return {
		DEFAULT_VOLUME_MUSIC,
		100
	};
}

State_Settings_Difficulty getSettingsDifficulty() {
	return {
		MENU_PRESET->index,
		MENU_EXTRA_LIVES->index,
		MENU_LIVES_INTERVAL->index,
		MENU_PEASANT_PENALTY->index,
		MENU_KNIGHT_SPEED->index,
		MENU_ARROW_SPEED->index,
		MENU_ARCHER_FREQ->index,
		MENU_TREASURE_HUTS->index
	};
}

State_Settings_Cosmetic getSettingsCosmetic() {
	return {
		MENU_FRAME_RATE->index,
		MENU_MUSIC->index,
		MENU_COMMENT_FREQ->index,
		MENU_BIG_HEAD_MODE->index,
		MENU_SCALING->index
	};
}

State_Settings_Other getSettingsOther() {
	return {
		MENU_STARTING_LEVEL->index,
		MENU_SHUFFLE_LEVELS->index,
		MENU_KNIGHT_BEHAVIOR->index,
		MENU_LEVEL_TRAN->index
	};
}

State_Settings_Cheats getSettingsCheats() {
	return {
		MENU_INF_LIVES->index,
		MENU_SPEEDY_MODE->index,
		MENU_NOCLIP->index,
		MENU_DEBUG_MODE->index
	};
}

State_Settings_Unlocks getSettingsUnlocks() {
	return {
		MENU_INF_LIVES->optionIsLocked,
		MENU_SPEEDY_MODE->optionIsLocked,
		MENU_NOCLIP->optionIsLocked,
		MENU_DEBUG_MODE->optionIsLocked
	};
}

void updateFrameRate() {
#if defined(WII) || defined(GAMECUBE) || defined(THREEDS)
	switch (MENU_FRAME_RATE->index) {
		case 1:
			frameRate = 20;
			break;
		case 2:
			frameRate = 25;
			break;
		case 3:
			frameRate = 30;
			break;
		case 4:
			frameRate = 40;
			break;
		case 5:
			frameRate = 50;
			break;
		case 6:
			frameRate = 55;
			break;
		case 7:
			frameRate = 60;
			break;
		default:
			frameRate = 16;
			break;
	}
#else
	switch (MENU_FRAME_RATE->index) {
		case 1:
			frameRate = 20;
#if defined(PSP)
			frameRateMult = static_cast<float>(ORIGINAL_FRAME_RATE) / 20; // this may seem redundant, but it's the only it'll work on PSP; using the frameRate variable just... doesn't work
#endif
			break;
		case 2:
			frameRate = 25;
#if defined(PSP)
			frameRateMult = static_cast<float>(ORIGINAL_FRAME_RATE) / 25;
#endif
			break;
		case 3:
			frameRate = 30;
#if defined(PSP)
			frameRateMult = static_cast<float>(ORIGINAL_FRAME_RATE) / 30;
#endif
			break;
		case 4:
			frameRate = 40;
#if defined(PSP)
			frameRateMult = static_cast<float>(ORIGINAL_FRAME_RATE) / 40;
#endif
			break;
		case 5:
			frameRate = 50;
#if defined(PSP)
			frameRateMult = static_cast<float>(ORIGINAL_FRAME_RATE) / 50;
#endif
			break;
		case 6:
			frameRate = 55;
#if defined(PSP)
			frameRateMult = static_cast<float>(ORIGINAL_FRAME_RATE) / 55;
#endif
			break;
		case 7:
			frameRate = 60;
#if defined(PSP)
			frameRateMult = static_cast<float>(ORIGINAL_FRAME_RATE) / 60;
#endif
			break;
		case 8:
			frameRate = 90;
			break;
		case 9:
			frameRate = 120;
			break;
		case 10:
			frameRate = 144;
			break;
		default:
			frameRate = 16;
#if defined(PSP)
			frameRateMult = static_cast<float>(ORIGINAL_FRAME_RATE) / 16;
#endif
			break;
	}
#endif
#if !defined(PSP)
	frameRateMult = static_cast<float>(ORIGINAL_FRAME_RATE) / frameRate;
#endif
	popRandVal = frameRate * 100 / ORIGINAL_FRAME_RATE;
	ticksPerFrame = (Uint32)(1000 / frameRate);
}

void setPreset(Sint8 ind) {
	switch (ind) {
		case 1:
			MENU_EXTRA_LIVES->setFrozen(true, 3);
			MENU_LIVES_INTERVAL->setFrozen(true, 0);
			MENU_PEASANT_PENALTY->setFrozen(true, 0);
			MENU_KNIGHT_SPEED->setFrozen(true, 2);
			MENU_ARROW_SPEED->setFrozen(true, 1);
			MENU_ARCHER_FREQ->setFrozen(true, 0);
			MENU_TREASURE_HUTS->setFrozen(true, 0);
			MENU_STARTING_LEVEL->setFrozen(true, 0);
			MENU_SHUFFLE_LEVELS->setFrozen(true, 1);
			MENU_INF_LIVES->setFrozen(true, 1);
			MENU_SPEEDY_MODE->setFrozen(true, 0);
			MENU_NOCLIP->setFrozen(true, 1);
			MENU_DEBUG_MODE->setFrozen(true, 1);
			break;
		case 2:
			MENU_EXTRA_LIVES->setFrozen(true, 3);
			MENU_LIVES_INTERVAL->setFrozen(true, 0);
			MENU_PEASANT_PENALTY->setFrozen(true, 1);
			MENU_KNIGHT_SPEED->setFrozen(true, 2);
			MENU_ARROW_SPEED->setFrozen(true, 1);
			MENU_ARCHER_FREQ->setFrozen(true, 0);
			MENU_TREASURE_HUTS->setFrozen(true, 1);
			MENU_STARTING_LEVEL->setFrozen(true, 0);
			MENU_SHUFFLE_LEVELS->setFrozen(true, 1);
			MENU_INF_LIVES->setFrozen(true, 1);
			MENU_SPEEDY_MODE->setFrozen(true, 0);
			MENU_NOCLIP->setFrozen(true, 1);
			MENU_DEBUG_MODE->setFrozen(true, 1);
			break;
		case 3:
			MENU_EXTRA_LIVES->setFrozen(true, 3);
			MENU_LIVES_INTERVAL->setFrozen(true, 6);
			MENU_PEASANT_PENALTY->setFrozen(true, 0);
			MENU_KNIGHT_SPEED->setFrozen(true, 3);
			MENU_ARROW_SPEED->setFrozen(true, 3);
			MENU_ARCHER_FREQ->setFrozen(true, 4);
			MENU_TREASURE_HUTS->setFrozen(true, 0);
			MENU_STARTING_LEVEL->setFrozen(true, 0);
			MENU_SHUFFLE_LEVELS->setFrozen(true, 1);
			MENU_INF_LIVES->setFrozen(true, 1);
			MENU_SPEEDY_MODE->setFrozen(true, 0);
			MENU_NOCLIP->setFrozen(true, 1);
			MENU_DEBUG_MODE->setFrozen(true, 1);
			break;
		case 4:
			MENU_EXTRA_LIVES->setFrozen(true, 3);
			MENU_LIVES_INTERVAL->setFrozen(true, 7);
			MENU_PEASANT_PENALTY->setFrozen(true, 0);
			MENU_KNIGHT_SPEED->setFrozen(true, 4);
			MENU_ARROW_SPEED->setFrozen(true, 4);
			MENU_ARCHER_FREQ->setFrozen(true, 5);
			MENU_TREASURE_HUTS->setFrozen(true, 0);
			MENU_STARTING_LEVEL->setFrozen(true, 0);
			MENU_SHUFFLE_LEVELS->setFrozen(true, 1);
			MENU_INF_LIVES->setFrozen(true, 1);
			MENU_SPEEDY_MODE->setFrozen(true, 0);
			MENU_NOCLIP->setFrozen(true, 1);
			MENU_DEBUG_MODE->setFrozen(true, 1);
			break;
		case 5:
			MENU_EXTRA_LIVES->setFrozen(true, 3);
			MENU_LIVES_INTERVAL->setFrozen(true, 1);
			MENU_PEASANT_PENALTY->setFrozen(true, 0);
			MENU_KNIGHT_SPEED->setFrozen(true, 2);
			MENU_ARROW_SPEED->setFrozen(true, 4);
			MENU_ARCHER_FREQ->setFrozen(true, 1);
			MENU_TREASURE_HUTS->setFrozen(true, 1);
			MENU_STARTING_LEVEL->setFrozen(true, 0);
			MENU_SHUFFLE_LEVELS->setFrozen(true, 0);
			MENU_INF_LIVES->setFrozen(true, 1);
			MENU_SPEEDY_MODE->setFrozen(true, 0);
			MENU_NOCLIP->setFrozen(true, 1);
			MENU_DEBUG_MODE->setFrozen(true, 1);
			break;
		default:
			MENU_EXTRA_LIVES->setFrozen(false, 0);
			MENU_LIVES_INTERVAL->setFrozen(false, 0);
			MENU_PEASANT_PENALTY->setFrozen(false, 0);
			MENU_KNIGHT_SPEED->setFrozen(false, 0);
			MENU_ARROW_SPEED->setFrozen(false, 0);
			MENU_ARCHER_FREQ->setFrozen(false, 0);
			MENU_TREASURE_HUTS->setFrozen(false, 0);
			MENU_STARTING_LEVEL->setFrozen(false, 0);
			MENU_SHUFFLE_LEVELS->setFrozen(false, 0);
			MENU_INF_LIVES->setFrozen(false, 0);
			MENU_SPEEDY_MODE->setFrozen(false, 0);
			MENU_NOCLIP->setFrozen(false, 0);
			MENU_DEBUG_MODE->setFrozen(false, 0);
			break;
	}
}

void updateHighScores() {
	menu_highscores_3.pages[0]->setTextLine(2, to_string(gameState.highscores.flash).c_str());
	menu_highscores_3.pages[0]->setTextLine(3, to_string(gameState.highscores.html5).c_str());
	menu_highscores_3.pages[0]->setTextLine(4, to_string(gameState.highscores.hard).c_str());
	menu_highscores_3.pages[0]->setTextLine(5, to_string(gameState.highscores.cruel).c_str());
	menu_highscores_3.pages[0]->setTextLine(6, to_string(gameState.highscores.mipsChoice).c_str());
	menu_highscores_3.pages[0]->setTextLine(7, to_string(gameState.highscores.custom).c_str());
}