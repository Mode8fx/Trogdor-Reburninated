#ifndef MENU_H
#define MENU_H

#include "text_objects.h"

constexpr auto MAX_NUM_OPTION_CHOICES = 10;

/* @brief A single option in a menu.
* 
* @param label A pointer representing the option's label.
* @param numChoices The number of choices.
* @param choices An array of pointers; each pointer represents a possible choice.
* @param choiceIsAllowed An array of whether or not each choice should be skipped over; useful for multi-platform development when some choices shouldn't be allowed for some systems.
* @param optionIsAllowed Whether or not the option should appear in the menu at all; useful for multi-platform development when some options shouldn't be allowed for some systems.
* @param index The index of the currently-selected choice.
* @param index_init The default index.
* @param isActive Whether or not this option is currently onscreen; useful for scrollable menus.
* @param choicesWrap Whether or not navigating past the last option choice should wrap around to the first choice, and vice-versa.
* @param dstrect_label The dstrect of the label.
* @param dstrect_choice The dstrect of the current choice.
*/
class MenuOption {
	public:
		TextObject *label;
		Uint8 numChoices;
		TextObject *choices;
		bool choiceIsAllowed[MAX_NUM_OPTION_CHOICES];
		bool optionIsAllowed;
		Sint8 index;
		Sint8 index_init;
		bool isActive;
		bool choicesWrap;
		TextRect dstrect_label;
		TextRect dstrect_choice;
		MenuOption() {
		}
		void prepareMenuOption(Uint8, TextObject *, Uint8, Uint8, bool);
		void setActive(bool);
		void setChoice(Uint8, TextObject *);
		void setChoiceActive(Uint8, bool);
};

/* @brief A single menu.
* 
* @param numOptions The number of options in the menu.
* @param numOnscreen The number of options that are onscreen at any given time. If this is smaller than numOptions, then the menu is scrollable.
* @param options An array of pointers; each pointer represents an option.
* @param cursor A pointer representing the cursor SpriteInstance.
* @param cursorIndex The index of the menu cursor.
* @param scrollIndex The amount that the menu itself has scrolled; used for scrolling through a large menu where not every option can be onscreen at once.
* @param cursorIndex_onscreen The index representing the cursor's onscreen position, accounting for scrollIndex.
* @param keepIndexOnExit Whether or not the cursor position should be reset every time you enter the menu.
* @param optionsWrap Whether or not navigating past the last menu option should wrap around to the first option, and vice-versa.
* @param scrollSpacer The minimum number of options allowed to be between the cursor and the top/bottom of the list before it starts scrolling.
* @param start_x The x-position of the top-most menu option.
* @param start_y The y-position of the top-most menu option.
* @param spacer_x The amount that each subsequent menu option's x position should increase by.
* @param spacer_y The amount that each subsequent menu option's y position should increase by.
*/
class Menu {
	public:
		Uint8 numOptions;
		Uint8 numOnscreen;
		MenuOption *options;
		SpriteInstance *cursor;
		Sint8 cursorIndex;
		Sint8 scrollIndex;
		Sint8 cursorIndex_onscreen;
		bool keepIndexOnExit;
		Uint8 scrollSpacer;
		Sint16 start_x;
		Sint16 start_y;
		Sint16 spacer_x;
		Sint16 spacer_y;
		bool optionsWrap;
		Menu() {
		}
		Menu(Uint8, Uint8, SpriteInstance *, bool, Sint8, Sint16, Sint16, Sint16, Sint16, bool);
		void incrementOption();
		void decrementOption();
		void updateOptionPositions();
};

#endif