#include "menu.h"
#include "input.h"
#include "general.h"
#include "window.h"
#include "include_fonts.h"

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

void MenuOption::prepareMenuOption(std::string label_ptr, const std::vector<std::string> choice_ptr, const std::vector<std::string> desc_ptr_1, const std::vector<std::string> desc_ptr_2, const std::vector<std::string> desc_ptr_3, std::string altDesc_ptr, Uint8 numCh, bool oneDesc, Sint8 start, bool wrap, bool canFreeze) {
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
	if (choicePtr.size() != 0) {
		for (counter = 0; counter < numChoices; counter++) {
			if (optionCanFreeze) setText(choicePtr[counter], &choice, menuFont_frozen);
			setText(choicePtr[counter], &choice, menuFont);
		}
	}
	if (descPtr_1.size() != 0) {
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
		if (choicePtr.size() != 0) {
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
		if (descPtr_1.size() != 0) {
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

// menuType: 0 is normal, 1 is difficulty menu, 2 is quit menu
Sint8 Menu::handleInput(Uint8 menuType) {
	if (keyPressed(INPUT_UP)) {
		decrementOption();
	}
	if (keyPressed(INPUT_DOWN)) {
		incrementOption();
	}
	if (keyPressed(INPUT_LEFT) && !(CURR_OPTION->optionIsFrozen || CURR_OPTION->optionIsLocked || (menuType == 2))) {
		decrementCurrOptionChoice();
		if ((menuType == 1) && cursorIndex == 0) {
			setPreset(CURR_OPTION->index);
		}
	}
	if (keyPressed(INPUT_RIGHT) && !(CURR_OPTION->optionIsFrozen || CURR_OPTION->optionIsLocked || (menuType == 2))) {
		incrementCurrOptionChoice();
		if ((menuType == 1) && cursorIndex == 0) {
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

#define option_on_off { "On", "Off" }
#define option_empty { "" }
#define option_custom_only { "(Custom preset only.)" }
#define option_main_starting_level_choices { "1", "11", "21", "31", "41", "51", "61", "71", "81", "91" }
#define option_main_starting_level_descriptions_line_1 { "The level that the game starts on." }
#define option_main_level_order_choices { "Original", "Shuffled" }
#define option_shuffle_levels_descriptions_line_1 { "Shuffle the level order so it's", "Play using the original level order." }
#define option_shuffle_levels_descriptions_line_2 { "different every time you play.", "" }
#define option_shuffle_levels_descriptions_line_3 { "(Custom / Mode 8 / Chance presets only.)", "" }
#define option_main_preset_choices { "Custom", "Flash", "HTML5", "Hard", "Cruel", "Mode 8", "Chance" }
#define option_main_preset_descriptions_line_1 { "Make your own rules!", "Default settings. Same as", "Settings from the HTML5 port.", "Fewer extra lives, faster", "No extra lives, tons of danger.", "They invented it just for this game!", "Knight/arrow speed and archer freq. are" }
#define option_main_preset_descriptions_line_2 { "Cheats and level select", "the original Flash game.", "No peasant penalty, all treasure huts.", "and more abundant enemies.", "Do you has what it takes?", "Fewer extra lives, crazy fast arrows,", "shuffled every level, and levels are" }
#define option_main_preset_descriptions_line_3 { "are also allowed.", "", "", "For Trogdor pros.", "", "all treasure huts, shuffled levels.", "shuffled! Who knows what could happen?" }
#define option_main_extra_lives_choices { "0", "1", "2", "3", "4", "5", "10", "20", "30" }
#define option_main_extra_lives_descriptions_line_1 { "The number of extra lives you start with." }
#define option_main_lives_interval_choices { "Every 300 points", "Every 500 points", "Every 1000 points", "500 points only", "500 and 1000 only", "1000 points only", "1000 and 2000 only", "None" }
#define option_main_lives_interval_descriptions_line_1 { "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "Get an extra life", "No extra lives." }
#define option_main_lives_interval_descriptions_line_2 { "every 300 points.", "every 500 points.", "every 1000 points.", "at 500 points.", "at 500 and 1000 points.", "at 1000 points.", "at 1000 and 2000 points.", "" }
#define option_main_lives_interval_descriptions_line_3 { "", "", "", "", "", "", "", "" }
#define option_main_music_choices { "Off", "Stinkoman 20X6"}
#define option_main_music_descriptions_line_1 { "Don't play music in-game.", "Play music from Stinkoman 20X6." }
#define option_main_music_descriptions_line_2 { "", "The song changes depending on the level." }
#define option_main_music_descriptions_line_3 { "", "" }
#define option_main_peasant_penalty_descriptions_line_1 { "The peasant meter decreases", "No penalty for escaped peasants." }
#define option_main_peasant_penalty_descriptions_line_2 { "every time a peasant escapes.", "" }
#define option_main_peasant_penalty_descriptions_line_3 { "", "" }
#define option_main_treasure_huts_choices { "Original", "New", "Off" }
#define option_main_treasure_huts_descriptions_line_1 { "After you enter a treasure hut, you cannot", "You can enter all treasure huts.", "Treasure huts are disabled."}
#define option_main_treasure_huts_descriptions_line_2 { "enter huts from other level layouts.", "Same behavior as the HTML5 port.", ""}
#define option_main_treasure_huts_descriptions_line_3 { "Same behavior as the original game.", "", ""}
#define option_main_archer_freq_choices { "Original", "New", "Low", "Medium", "High", "Non-stop" }
#define option_main_archer_freq_descriptions_line_1 { "Archers appear more in later levels.", "Archers appear more in later levels.", "Archers do not appear often.", "Archers appear semi-often.", "Archers appear very often.", "Archers appear non-stop!"}
#define option_main_archer_freq_descriptions_line_2 { "Same behavior as the original game.", "New scaling that's more evenly", "", "", "", ""}
#define option_main_archer_freq_descriptions_line_3 { "", "distributed between levels.", "", "", "", ""}
#define option_main_knight_movement_choices { "Original", "New" }
#define option_main_knight_movement_descriptions_line_1 { "Knights are more predictable", "Knights cover more ground and stay" }
#define option_main_knight_movement_descriptions_line_2 { "and can wander offscreen.", "onscreen. Slightly more challenging." }
#define option_main_knight_movement_descriptions_line_3 { "Similar to the original game.", "Similar to the HTML5 port." }
#define option_main_respawn_behavior_choices { "Original", "New" }
#define option_main_respawn_behavior_descriptions_line_1 { "Knights briefly pause and change", "Knights do not change their" }
#define option_main_respawn_behavior_descriptions_line_2 { "position after you die.", "movement after you die." }
#define option_main_respawn_behavior_descriptions_line_3 { "Same behavior as the original game.", "Same behavior as the HTML5 port." }
#define option_main_knight_speed_choices { "Very Slow", "Slow", "Normal", "Fast", "Very Fast" }
#define option_main_knight_speed_descriptions_line_1 { "Change how quickly knights move." }
#define option_main_arrow_speed_choices { "Slow", "Normal", "Fast", "Very Fast", "Insane" }
#define option_main_arrow_speed_descriptions_line_1 { "Change how quickly arrows move." }
#if defined(THREEDS)
#define option_main_frame_rate_choices { "16 FPS (original)", "20 FPS", "25 FPS", "30 FPS", "", "", "", "", "", "", "" }
#else
#define option_main_frame_rate_choices { "16 FPS (original)", "20 FPS", "25 FPS", "30 FPS", "40 FPS", "50 FPS", "55 FPS", "60 FPS", "90 FPS", "120 FPS", "144 FPS" }
#endif
#define option_main_frame_rate_descriptions_line_1 { "Higher frame rate, smoother gameplay." }
#define option_main_frame_rate_descriptions_line_2 { "(Original Flash game is 16 FPS)" }
#define option_main_frame_rate_descriptions_line_3 { "" }
#define option_main_level_tran_choices { "Original", "Button Press" }
#define option_main_level_tran_descriptions_line_1 { "After beating a level, the next", "After beating a level, press " + INPUT_CONFIRM }
#define option_main_level_tran_descriptions_line_2 { "level will load automatically.", "or " + INPUT_PAUSE + " to load the next level." }
#define option_main_level_tran_descriptions_line_3 { "", "" }
#define option_main_comment_freq_choices { "Off", "Very Low", "Low", "Normal", "High", "Very High", "Let's-Player" }
#define option_main_comment_freq_descriptions_line_1 { "Strong Bad does not talk.", "Strong Bad rarely talks.", "Strong Bad talks less than usual.", "Strong Bad talks as often", "Strong Bad talks a bit more often.", "Strong Bad talks much more often.", "Strong Bad won't shut up!" }
#define option_main_comment_freq_descriptions_line_2 { "", "", "", "as he did in the original game.", "", "", "(He talks twice as much as usual.)"}
#define option_main_comment_freq_descriptions_line_3 { "", "", "", "", "", "", "" }
#if defined(RG35XX) || defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII) || defined(GAMECUBE) || defined(THREEDS) || defined(XBOX)
#define press_confirm_to_apply "(Press " + INPUT_CONFIRM + " to apply, may take a few seconds)"
#else
#define press_confirm_to_apply "(Press " + INPUT_CONFIRM + " to apply)"
#endif
#if defined(THREEDS)
#define option_main_scaling_choices { "N/A", "N/A", "N/A", "N/A" }
#define option_main_scaling_descriptions_line_1 { "(Unused)", "(Unused)", "(Unused)", "(Unused)" }
#define option_main_scaling_descriptions_line_2 { "", "", "", "" }
#define option_main_scaling_descriptions_line_3 { "", "", "", "" }
#elif defined(PSP)
#define option_main_scaling_choices { "Pixel-Perfect", "", "Full", "Full Game" }
#define option_main_scaling_descriptions_line_1 { "Scale so that everything uses integer", "", "Scale everything so that", "Scale the game to fill the screen." }
#define option_main_scaling_descriptions_line_2 { "scaling. Accurate, but small.", "", "the overlay fills the screen.", "The overlay will be cut off." }
#define option_main_scaling_descriptions_line_3 { press_confirm_to_apply, "", press_confirm_to_apply, press_confirm_to_apply }
#elif (RG35XX) || defined(WII) || defined(GAMECUBE) || defined(XBOX)
#define option_main_scaling_choices { "Pixel-Perfect", "", "", "Full Game" }
#define option_main_scaling_descriptions_line_1 { "Scale so that everything uses integer", "", "", "Scale the game to fill the screen." }
#define option_main_scaling_descriptions_line_2 { "scaling. The most accurate.", "", "", "The overlay will be cut off." }
#define option_main_scaling_descriptions_line_3 { press_confirm_to_apply, "", "", press_confirm_to_apply }
#elif defined(WII_U)
#define option_main_scaling_choices { "Pixel-Perfect", "Pixel-Perfect Game", "", "" }
#define option_main_scaling_descriptions_line_1 { "Scale so that everything uses integer", "Scale the game to be as big as possible", "", "" }
#define option_main_scaling_descriptions_line_2 { "scaling. Accurate, but small.", "with integer scaling. The most accurate.", "", "" }
#define option_main_scaling_descriptions_line_3 { press_confirm_to_apply, press_confirm_to_apply, "", "" }
#elif defined(SWITCH)
#define option_main_scaling_choices { "Pixel-Perfect", "Pixel-Perfect Game", "Full", "" }
#define option_main_scaling_descriptions_line_1 { "Scale so that everything uses integer", "Scale the game to be as big as possible", "Scale everything so that", "" }
#define option_main_scaling_descriptions_line_2 { "scaling. Accurate, but possibly small.", "with integer scaling. The most accurate.", "the overlay fills the screen.", "" }
#define option_main_scaling_descriptions_line_3 { press_confirm_to_apply, press_confirm_to_apply, press_confirm_to_apply, "" }
#else
#define option_main_scaling_choices { "Pixel-Perfect", "Pixel-Perfect Game", "Full", "Full Game" }
#define option_main_scaling_descriptions_line_1 { "Scale so that everything uses integer", "Scale the game to be as big as possible", "Scale everything so that", "Scale the game to fill the screen." }
#define option_main_scaling_descriptions_line_2 { "scaling. Accurate, but possibly small.", "with integer scaling. The most accurate.", "the overlay fills the screen.", "The overlay will be cut off." }
#define option_main_scaling_descriptions_line_3 { press_confirm_to_apply, press_confirm_to_apply, press_confirm_to_apply, press_confirm_to_apply }
#endif
#define option_main_difficulty_descriptions_line_1 { "Change settings related to" }
#define option_main_difficulty_descriptions_line_2 { "game difficulty." }
#define option_main_cosmetic_descriptions_line_1 { "Change settings related to" }
#define option_main_cosmetic_descriptions_line_2 { "game audio and video." }
#define option_main_other_descriptions_line_1 { "Change miscellaneous settings." }
#define option_main_cheats_descriptions_line_1 { "Toggle secret cheats." }
#define option_main_cheats_descriptions_line_2 { "Follow the hints!" }
#define option_main_highscores_descriptions_line_1 { "View your high scores." }
#if defined(WII) || defined(GAMECUBE)
#define option_main_gba_demo_descriptions_line_1 { "Transfer a demo of TroGBA" }
#define option_main_gba_demo_descriptions_line_2 { "to your Game Boy Advance." }
#endif
#define option_main_sound_descriptions_line_1 { "Listen to some number one jams." }
#define option_main_credits_descriptions_line_1 { "View the credits." }
#define option_main_reset_settings_descriptions_line_1 { "Reset all settings to default." }
#define option_main_quit_descriptions_line_1 { "Quit the game." }
#define option_cheats_inf_lives_descriptions_line_1 { "Infinite lives, play forever!" }
#define option_cheats_inf_lives_descriptions_line_2 { "Unlocking this cheat also unlocks" }
#define option_cheats_inf_lives_descriptions_line_3 { "more starting lives options." }
#define option_speedy_mode_choices { "Off", "Fast", "Faster", "Fastest" }
#define option_cheats_speedy_mode_descriptions_line_1 { "Trogdor moves much faster!" }
#define option_cheats_debug_mode_descriptions_line_1 { "Enable Debug Mode." }
#define option_cheats_debug_mode_descriptions_line_2 { "Press buttons to do things." }
#define option_main_big_head_mode_descriptions_line_1 { "Give Trogdor a more husky head." }
#define option_cheats_noclip_descriptions_line_1 { "Remove the game's difficulty" }
#define option_cheats_noclip_descriptions_line_2 { "by walking through cottages." }
#define option_number_choices { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23" } // I know, this is bad
#if defined(RG35XX) || defined(WII_U) || defined(VITA) || defined(PSP) || defined(WII) || defined(GAMECUBE) || defined(THREEDS) || defined(XBOX)
#if defined(WII_U)
#define console_quit_line_1 "WHY ARE YOU STILL USING A WII U?!"
#elif defined(VITA)
#define console_quit_line_1 "WHY ARE YOU STILL USING A VITA?!"
#elif defined(PSP)
#define console_quit_line_1 "WHY ARE YOU STILL USING A PSP?!"
#elif defined(WII)
#define console_quit_line_1 "WHY ARE YOU STILL USING A WII?!"
#elif defined(GAMECUBE)
#define console_quit_line_1 "WHY ARE YOU STILL USING A GAMECUBE?!"
#elif defined(THREEDS)
#define console_quit_line_1 "WHY ARE YOU STILL USING A 3DS?!"
#elif defined(XBOX)
#define console_quit_line_1 "WHY ARE YOU STILL USING AN XBOX?!"
#else
#define console_quit_line_1 "WHY ARE YOU STILL USING WINDOWS 98?!"
#endif
#define console_quit_line_2 "WHAT IS WRONG WITH YOU?! STOP BUYING"
#define console_quit_line_3 "CONSOLES FROM THRIFT STORES, MAN!"
#else
#if defined(SWITCH)
#define console_quit_line_1 "Switch over? Virus equals very yes?"
#elif defined(ANDROID)
#define console_quit_line_1 "Android over? Virus equals very yes?"
#else
#define console_quit_line_1 "Computer over? Virus equals very yes?"
#endif
#define console_quit_line_2 ""
#define console_quit_line_3 ""
#endif
#define option_quit_descriptions_line_1 { "Hey Player, I really like your", "Strong Bad's gonna get the", "Are you sure you want to quit this", "Don't leave yet -- There's a", "If you leave now, how will you", "Click \"Keep playing\" to email strong bad", console_quit_line_1 }
#define option_quit_descriptions_line_2 { "\"quitting to play a different game\"", "high score, man, 50,000.", "great game?", "peasant around that corner!", "get ye flask?", "", console_quit_line_2 }
#define option_quit_descriptions_line_3 { "costume.", "", "", "", "", "", console_quit_line_3 }

void InitializeMenus() {
	TTF_Init();
	// if the menu font would end up being the same as font_serif_white_6_mult, just use that instead of initializing an exclusive font
	if (font_serif_white_6_mult.size == getDesiredFontSize(&font_serif_white_8)) {
		menuFont = &font_serif_white_6_mult;
	} else {
		menuFont = &font_serif_white_8;
	}
	setFont(menuFont, serif_v01_ttf, serif_v01_ttf_len, 8, 5, TTF_STYLE_NORMAL, color_white, true);
	menuFont_frozen = &font_serif_gray_8;
	setFont(&font_serif_gray_8, serif_v01_ttf, serif_v01_ttf_len, 8, 5, TTF_STYLE_NORMAL, color_gray, true);

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
#if defined(WII) || defined(GAMECUBE)
	MENU_GBA_DEMO->prepareMenuOption("Send GBA Demo", option_empty,
		option_main_gba_demo_descriptions_line_1, option_main_gba_demo_descriptions_line_2, option_empty,
		"", 1, true, 0, true, false);
#endif
	MENU_SOUND->prepareMenuOption("Sound Test", option_empty,
		option_main_sound_descriptions_line_1, option_empty, option_empty,
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
		"", 7, false, 1, true, true);
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
#if defined(RG35XX) || defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(PSP) || defined(WII) || defined(GAMECUBE) || defined(XBOX)
		"", 8, true, 7, true, false);
#elif defined(THREEDS)
		"", 4, true, 3, true, false);
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
	MENU_KNIGHT_MOVEMENT->prepareMenuOption("Knight Movement", option_main_knight_movement_choices,
		option_main_knight_movement_descriptions_line_1, option_main_knight_movement_descriptions_line_2, option_main_knight_movement_descriptions_line_3,
		"", 2, false, 1, true, false);
	MENU_RESPAWN_BEHAVIOR->prepareMenuOption("Respawn Behavior", option_main_respawn_behavior_choices,
		option_main_respawn_behavior_descriptions_line_1, option_main_respawn_behavior_descriptions_line_2, option_main_respawn_behavior_descriptions_line_3,
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
		menu_highscores_1.pages[0] = new MenuPage();
		menu_highscores_2.pages[0] = new MenuPage();
		menu_highscores_3.pages[0] = new MenuPage();
	}
	menu_highscores_1.pages[0]->prepareMenuPage(1, 0, 30, 20, 1);
	menu_highscores_1.pages[0]->setTextLine(0, "YE OLDE HI-SCORES");
	menu_highscores_2.pages[0]->prepareMenuPage(9, 96, 30, 20, 0);
	menu_highscores_2.pages[0]->setTextLine(0, "");
	menu_highscores_2.pages[0]->setTextLine(1, "");
	menu_highscores_2.pages[0]->setTextLine(2, "Flash:");
	menu_highscores_2.pages[0]->setTextLine(3, "HTML5:");
	menu_highscores_2.pages[0]->setTextLine(4, "Hard:");
	menu_highscores_2.pages[0]->setTextLine(5, "Cruel:");
	menu_highscores_2.pages[0]->setTextLine(6, "Mode 8:");
	menu_highscores_2.pages[0]->setTextLine(7, "Chance:");
	menu_highscores_2.pages[0]->setTextLine(8, "Custom:");
	menu_highscores_3.pages[0]->prepareMenuPage(9, 224, 30, 20, 2);
	menu_highscores_3.pages[0]->setTextLine(0, "");
	menu_highscores_3.pages[0]->setTextLine(1, "");
	updateHighScores();

#if defined(WII) || defined(GAMECUBE)
	/* GBA Demo Notebook */
	menu_gba_demo.prepareMenuNotebook(4, 304, 216, 3);
	if (!menusAreInitialized) {
		for (i = 0; i < menu_gba_demo.numPages; i++) {
			menu_gba_demo.pages[i] = new MenuPage();
		}
	}
	menu_gba_demo.pages[0]->prepareMenuPage(12, 0, 30, 16, 1);
	menu_gba_demo.pages[0]->setTextLine(0, "TROGDOR ON GBA");
	menu_gba_demo.pages[0]->setTextLine(1, "");
	menu_gba_demo.pages[0]->setTextLine(2, "Transfer a demo of Trogba to your");
	menu_gba_demo.pages[0]->setTextLine(3, "Game Boy Advance!");
	menu_gba_demo.pages[0]->setTextLine(4, "The full version has audio, better");
	menu_gba_demo.pages[0]->setTextLine(5, "graphics, and more gameplay options,");
	menu_gba_demo.pages[0]->setTextLine(6, "including the threat of the deadly");
	menu_gba_demo.pages[0]->setTextLine(7, "Troghammer from Trogdor: The Board Game.");
	menu_gba_demo.pages[0]->setTextLine(8, "And it's free!");
	menu_gba_demo.pages[0]->setTextLine(9, "https://jeremyelkayam.itch.io/trogba");
	menu_gba_demo.pages[0]->setTextLine(10, "");
#if defined(WII)
	menu_gba_demo.pages[0]->setTextLine(11, "(Or press 2 to play the demo right now)");
#else
	menu_gba_demo.pages[0]->setTextLine(11, "(Or press A to play the demo right now)");
#endif

	menu_gba_demo.pages[1]->prepareMenuPage(6, 0, 30, 20, 1);
	menu_gba_demo.pages[1]->setTextLine(0, "TROGDOR ON GBA");
	menu_gba_demo.pages[1]->setTextLine(1, "");
	menu_gba_demo.pages[1]->setTextLine(2, "Ready to transfer...");
	menu_gba_demo.pages[1]->setTextLine(3, "Plug your GBA into the second Gamecube");
	menu_gba_demo.pages[1]->setTextLine(4, "controller port, remove the game");
	menu_gba_demo.pages[1]->setTextLine(5, "cartridge, and turn it on.");

	menu_gba_demo.pages[2]->prepareMenuPage(6, 0, 30, 20, 1);
	menu_gba_demo.pages[2]->setTextLine(0, "TROGDOR ON GBA");
	menu_gba_demo.pages[2]->setTextLine(1, "");
	menu_gba_demo.pages[2]->setTextLine(2, "Transferring...");
	menu_gba_demo.pages[2]->setTextLine(3, "");
	menu_gba_demo.pages[2]->setTextLine(4, "Do not turn off the GBA");
	menu_gba_demo.pages[2]->setTextLine(5, "or unplug the link cable.");

	menu_gba_demo.pages[3]->prepareMenuPage(5, 0, 30, 20, 1);
	menu_gba_demo.pages[3]->setTextLine(0, "TROGDOR ON GBA");
	menu_gba_demo.pages[3]->setTextLine(1, "");
	menu_gba_demo.pages[3]->setTextLine(2, "It's over!");
	menu_gba_demo.pages[3]->setTextLine(3, "");
	menu_gba_demo.pages[3]->setTextLine(4, "Transfer complete.");
#endif

	/* Sound Test Menu */
	menu_sound.prepareMenu(SOUND_NUM_OPTIONS, 6, &sprite_menu_cursor, false, 1, 32 + (16 * (screenScale_menu >= 2)), 160 + (16 * (screenScale_menu >= 2)), 0, 25, 175, 25, 15, 0, 0, true);
	if (!menusAreInitialized) {
		for (i = 0; i < SOUND_NUM_OPTIONS; i++) {
			menu_sound.options[i] = new MenuOption();
		}
	}
	MENU_MUSIC_TEST->prepareMenuOption("Music", option_number_choices,
		option_main_sound_descriptions_line_1, option_empty, option_empty,
		"", 13, true, 0, true, false);
	MENU_SFX_TEST->prepareMenuOption("SFX", option_number_choices,
		option_main_sound_descriptions_line_1, option_empty, option_empty,
		"", 13, true, 0, true, false);
	MENU_VOICE_TEST->prepareMenuOption("Voice", option_number_choices,
		option_main_sound_descriptions_line_1, option_empty, option_empty,
		"", 23, true, 0, true, false);

	/* Credits Notebook */
#if defined(WII) || defined(GAMECUBE)
	menu_credits.prepareMenuNotebook(7, 304, 216, 2);
#else
	menu_credits.prepareMenuNotebook(6, 304, 216, 2);
#endif
	if (!menusAreInitialized) {
		for (i = 0; i < menu_credits.numPages; i++) {
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
	menu_credits.pages[1]->setTextLine(2, "Mode8fx");
	menu_credits.pages[1]->setTextLine(3, "");
	menu_credits.pages[1]->setTextLine(4, "https://github.com/Mode8fx");
	menu_credits.pages[1]->setTextLine(5, "/Trogdor-Reburninated");
	menu_credits.pages[1]->setTextLine(6, "");
#if defined(GAMECUBE)
	menu_credits.pages[1]->setTextLine(7, "v2.1-beta");
#else
	menu_credits.pages[1]->setTextLine(7, "v2.1");
#endif

	menu_credits.pages[2]->prepareMenuPage(5, 0, 30, 20, 1);
	menu_credits.pages[2]->setTextLine(0, "- STINKOMAN MUSIC -");
	menu_credits.pages[2]->setTextLine(1, "");
	menu_credits.pages[2]->setTextLine(2, "Jonathan Howe");
	menu_credits.pages[2]->setTextLine(3, "");
	menu_credits.pages[2]->setTextLine(4, "U.Z. Inu");
	j = 3;

#if defined(WII) || defined(GAMECUBE)
	menu_credits.pages[j]->prepareMenuPage(9, 0, 30, 20, 1);
	menu_credits.pages[j]->setTextLine(0, "- GBA DEMO -");
	menu_credits.pages[j]->setTextLine(1, "");
	menu_credits.pages[j]->setTextLine(2, "Original GBA Version + Demo:");
	menu_credits.pages[j]->setTextLine(3, "Jeremy Elkayam's Trogba");
	menu_credits.pages[j]->setTextLine(4, "https://jeremyelkayam.itch.io/trogba");
	menu_credits.pages[j]->setTextLine(5, "");
	menu_credits.pages[j]->setTextLine(6, "GBA Transfer Code:");
	menu_credits.pages[j]->setTextLine(7, "FIX94's GoombaSend");
	menu_credits.pages[j]->setTextLine(8, "https://github.com/FIX94/GoombaSend");
	j++;
#endif

	menu_credits.pages[j]->prepareMenuPage(5, 0, 30, 20, 1);
	menu_credits.pages[j]->setTextLine(0, "- SPECIAL THANKS -");
	menu_credits.pages[j]->setTextLine(1, "");
	menu_credits.pages[j]->setTextLine(2, "Autosave + Level Transition ideas:");
	menu_credits.pages[j]->setTextLine(3, "Jeremy Elkayam's Trogba");
	menu_credits.pages[j]->setTextLine(4, "https://jeremyelkayam.itch.io/trogba");
	j++;

	menu_credits.pages[j]->prepareMenuPage(7, 0, 30, 20, 1);
	menu_credits.pages[j]->setTextLine(0, "- LIBRARIES -");
	menu_credits.pages[j]->setTextLine(1, "");
#if defined(SDL1)
	menu_credits.pages[j]->setTextLine(2, "SDL");
	menu_credits.pages[j]->setTextLine(3, "SDL_image");
	menu_credits.pages[j]->setTextLine(4, "SDL_mixer");
	menu_credits.pages[j]->setTextLine(5, "SDL_ttf");
	menu_credits.pages[j]->setTextLine(6, "");
#else
	menu_credits.pages[j]->setTextLine(2, "SDL2");
	menu_credits.pages[j]->setTextLine(3, "SDL2_image");
#if defined(PSP)
	menu_credits.pages[j]->setTextLine(4, "OSLibAudio");
#else
	menu_credits.pages[j]->setTextLine(4, "SDL2_mixer");
#endif
	menu_credits.pages[j]->setTextLine(5, "SDL2_ttf");
	menu_credits.pages[j]->setTextLine(6, "");
#endif
	j++;

	menu_credits.pages[j]->prepareMenuPage(9, 0, 30, 20, 1);
	menu_credits.pages[j]->setTextLine(0, "- WANT MORE? -");
	menu_credits.pages[j]->setTextLine(1, "");
	menu_credits.pages[j]->setTextLine(2, "Trogdor: Reburninated is available");
	menu_credits.pages[j]->setTextLine(3, "for a wide variety of");
	menu_credits.pages[j]->setTextLine(4, "homebrew-enabled systems, old and new.");
	menu_credits.pages[j]->setTextLine(5, "Play it everywhere!");
	menu_credits.pages[j]->setTextLine(6, "");
	menu_credits.pages[j]->setTextLine(7, "https://github.com/Mode8fx");
	menu_credits.pages[j]->setTextLine(8, "/Trogdor-Reburninated");

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
#if defined(RG35XX) || defined(THREEDS) || defined(PSP) || defined(WII) || defined(GAMECUBE) || defined(XBOX)
		MENU_SCALING->choiceIsAllowed[1] = false;
#endif
#if defined(RG35XX) || defined(THREEDS) || defined(WII) || defined(GAMECUBE) || defined(XBOX) || defined(WII_U)
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
		MENU_RESPAWN_BEHAVIOR->index,
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

State_Addon_v_2_1 getSettings_v_2_1() {
	return {
		MENU_KNIGHT_MOVEMENT->index,
	};
}

void updateFrameRate() {
	switch (MENU_FRAME_RATE->index) {
		case 1:
			frameRate = 20;
#if defined(PSP)
			frameRateMult = static_cast<float>(ORIGINAL_FRAME_RATE) / 20; // this may seem redundant, but it's the only way it'll work on PSP; using the frameRate variable just... doesn't work
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
		case 6:
			MENU_EXTRA_LIVES->setFrozen(true, 3);
			MENU_LIVES_INTERVAL->setFrozen(true, 4);
			MENU_PEASANT_PENALTY->setFrozen(true, 0);
			MENU_KNIGHT_SPEED->setFrozen(true, 2);
			MENU_ARROW_SPEED->setFrozen(true, 1);
			MENU_ARCHER_FREQ->setFrozen(true, 0);
			MENU_TREASURE_HUTS->setFrozen(true, 0);
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
	menu_highscores_3.pages[0]->setTextLine(7, to_string(gameState.addon_v_2_1.chance).c_str());
	menu_highscores_3.pages[0]->setTextLine(8, to_string(gameState.highscores.custom).c_str());
}