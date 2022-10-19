#ifndef MENU_H
#define MENU_H

#include "text_objects.h"
#include "input.h"

constexpr auto MAX_NUM_OPTION_CHOICES = 10;

/* @brief A single option in a menu.
* 
* @param label A TextObject representing the option's label.
* @param labelPtr A pointer to a string for the label.
* @param choice A TextObject representing the option's current choice.
* @param choicePtr A pointer to an array of strings for the choice.
* @param description_1 A TextObject representing the top line of the option's current description.
* @param description_2 A TextObject representing the middle line of the option's current description.
* @param description_3 A TextObject representing the bottom line of the option's current description.
* @param descPtr A pointer to an array of strings for the choice description(s). If the size is 1, all choices use the same description.
* @param altDescPtr A pointer to a string for the alt description, to be used if optionIsLocked is set to true.
* @param numChoices The number of choices.
* @param choiceIsAllowed An array of whether or not each choice should be skipped over; useful for multi-platform development when some choices shouldn't be allowed for some systems.
* @param index The index of the currently-selected choice.
* @param index_init The default index.
* @param isActive Whether or not this option is currently onscreen; useful for scrollable menus.
* @param choicesWrap Whether or not navigating past the last option choice should wrap around to the first choice, and vice-versa.
* @param optionIsLocked If the option is locked, its choices do not appear, its index cannot change, and the alt description is used in place of the normal description.
*/
class MenuOption {
	public:
		TextObject label;
		const char *labelPtr;
		TextObject choice;
		const char **choicePtr;
		TextObject description_1;
		TextObject description_2;
		TextObject description_3;
		const char ***descPtr;
		const char *altDescPtr;
		Uint8 numChoices;
		bool choiceIsAllowed[MAX_NUM_OPTION_CHOICES];
		Sint8 index;
		Sint8 index_init;
		bool isActive;
		bool choicesWrap;
		bool optionIsLocked;
		MenuOption() {
		}
		void prepareMenuOption(const char [], const char *[], const char **[], const char [], Uint8, Uint8, bool, bool);
		void updateLabel();
		void updateChoice();
		void updateDescription();
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
* @param scrollSpacer The minimum number of options allowed to be between the cursor and the top/bottom of the list before it starts scrolling.
* @param start_x_label The x-position of the top-most menu option's label.
* @param start_x_choice The x-position of the top-most menu option's choice.
* @param spacer_x The amount that each subsequent menu option's x position should increase by.
* @param start_y The y-position of the top-most menu option.
* @param spacer_y The amount that each subsequent menu option's y position should increase by.
* @param alignType_label Align type for options labels. 0 = left, 1 = center, 2 = right.
* @param alignType_choice Align type for options choices. 0 = left, 1 = center, 2 = right.
* @param optionsWrap Whether or not navigating past the last menu option should wrap around to the first option, and vice-versa.
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
		Sint16 start_x_label;
		Sint16 start_x_choice;
		Sint16 spacer_x;
		Sint16 start_y;
		Sint16 spacer_y;
		Sint8 alignType_label;
		Sint8 alignType_choice;
		bool optionsWrap;
		Menu() {
		}
		Menu(Uint8, Uint8, SpriteInstance *, bool, Sint8, Sint16, Sint16, Sint16, Sint16, Sint16, Sint8, Sint8, bool);
		void handleControls();
		void incrementOption();
		void decrementOption();
		void incrementCurrOptionChoice();
		void decrementCurrOptionChoice();
		void updateOptionPositions();
		void updateCurrOptionChoicePositions();
		void updateCurrOptionChoiceDescription();
		void openMenu();
};

#endif