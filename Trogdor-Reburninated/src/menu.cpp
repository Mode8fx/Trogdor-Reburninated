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

void MenuOption::setActive(bool active) {
	optionIsAllowed = active;
}

void MenuOption::setChoice(Uint8 choiceIndex, TextObject *textObj) {
	choices[choiceIndex] = *textObj;
	dstrect_choice = textObj->dstrect;
}

void MenuOption::setChoiceActive(Uint8 choiceIndex, bool active) {
	choiceIsAllowed[choiceIndex] = active;
}

Menu::Menu(Uint8 numOpt, Uint8 numOns, SpriteInstance *spriteIns, bool keepIndex, Sint8 space_scroll, Sint16 st_x, Sint16 st_y, Sint16 sp_x, Sint16 sp_y, bool wrap) {
	numOptions = numOpt;
	numOnscreen = min(numOns, numOptions);
	options = (MenuOption*)malloc(numOptions * sizeof(MenuOption));
	cursor = spriteIns;
	cursorIndex = 0;
	scrollIndex = 0;
	cursorIndex_onscreen = 0;
	keepIndexOnExit = keepIndex;
	optionsWrap = wrap;
	scrollSpacer = space_scroll;
	start_x = st_x;
	start_y = st_y;
	spacer_x = sp_x;
	spacer_y = sp_y;
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

void Menu::updateOptionPositions() {
	// TODO: update cursor position here
	for (i = 0; i < options[i].numChoices; i++) {
		options[i].isActive = false;
	}
	j = cursorIndex - cursorIndex_onscreen;
	for (i = j; i < i + numOnscreen; i++) {
		options[i].isActive = true;
		// TODO: update option positions here
	}
}