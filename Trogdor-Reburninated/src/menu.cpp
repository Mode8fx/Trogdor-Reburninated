#include "menu.h"

void MenuOption::prepareMenuOption(Uint8 numOptions, TextObject *textObj, Uint8 numCh, Uint8 start, bool wrap) {
	label = textObj;
	numChoices = numCh;
	if (numChoices > 0) {
		choices = (TextObject*)malloc(numChoices * sizeof(TextObject));
	}
	for (i = 0; i < numChoices; i++) {
		choiceIsAllowed[i] = true;
	}
	optionIsAllowed = true;
	index = start;
	index_init = start;
	isActive = true;
	choicesWrap = wrap;
	dstrect_label = textObj->dstrect;
}

void MenuOption::prepareChoice(Uint8 choiceIndex, TextObject *textObj) {
	choices[choiceIndex] = *textObj;
	dstrect_choice = textObj->dstrect;
}

void MenuOption::setActive(bool active) {
	optionIsAllowed = active;
}

void MenuOption::setChoiceActive(Uint8 choiceIndex, bool active) {
	choiceIsAllowed[choiceIndex] = active;
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

void Menu::incrementCurrOptionChoice() {
	if (options[cursorIndex].index < options[cursorIndex].numChoices - 1) {
		options[cursorIndex].index++;
		updateCurrOptionChoicePositions();
	} else if (options[cursorIndex].choicesWrap) {
		options[cursorIndex].index = 0;
		updateCurrOptionChoicePositions();
	}
}

void Menu::decrementCurrOptionChoice() {
	if (options[cursorIndex].index > 0) {
		options[cursorIndex].index--;
		updateCurrOptionChoicePositions();
	} else if (options[cursorIndex].choicesWrap) {
		options[cursorIndex].index = options[cursorIndex].numChoices - 1;
		updateCurrOptionChoicePositions();
	}
}

void Menu::updateOptionPositions() {
	for (i = 0; i < options[i].numChoices; i++) {
		options[i].isActive = false;
	}
	j = cursorIndex - cursorIndex_onscreen;
	for (i = j; i < j + numOnscreen; i++) {
		options[i].isActive = true;
		options[i].dstrect_label.w = options[i].label->dstrect.w;
		options[i].dstrect_label.h = options[i].label->dstrect.h;
		switch (alignType_label) {
			case 0:
				options[i].dstrect_label.x = start_x_label + (spacer_x * (i - j));
				break;
			case 1:
				options[i].dstrect_label.x = start_x_label + (spacer_x * (i - j)) - (options[i].dstrect_label.w / 2);
				break;
			default:
				options[i].dstrect_label.x = start_x_label + (spacer_x * (i - j)) - options[i].dstrect_label.w;
				break;
		}
		options[i].dstrect_label.y = start_y + (spacer_y * (i - j));
		updateCurrOptionChoicePositions();
	}
	cursor->dstrect.x = options[cursorIndex_onscreen].dstrect_label.x - (cursor->dstrect.w * 2);
	cursor->dstrect.y = options[cursorIndex_onscreen].dstrect_label.y + ((options[cursorIndex_onscreen].dstrect_label.h - cursor->dstrect.h) / 2);
}

void Menu::updateCurrOptionChoicePositions() {
	options[cursorIndex].dstrect_choice.w = options[cursorIndex].choices[options[cursorIndex].index].dstrect.w;
	options[cursorIndex].dstrect_choice.h = options[cursorIndex].choices[options[cursorIndex].index].dstrect.h;
	switch (alignType_choice) {
		case 0:
			options[cursorIndex].dstrect_choice.x = start_x_choice + (spacer_x * (i - j));
			break;
		case 1:
			options[cursorIndex].dstrect_choice.x = start_x_choice + (spacer_x * (i - j)) - (options[cursorIndex].dstrect_choice.w / 2);
			break;
		case 2:
			options[cursorIndex].dstrect_choice.x = start_x_choice + (spacer_x * (i - j)) - options[cursorIndex].dstrect_choice.w;
			break;
	}
	options[cursorIndex].dstrect_choice.y = start_y + (spacer_y * (i - j));
}

void Menu::openMenu() {
	if (!keepIndexOnExit) {
		cursorIndex = 0;
		scrollIndex = 0;
		cursorIndex_onscreen = 0;
	}
	updateOptionPositions();
}