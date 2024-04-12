#include "include.h"
#include "text_objects.h"
#include "sprite_objects.h"
#include "config.h"

#ifndef MENU_H
#define MENU_H

constexpr auto MAX_NUM_OPTION_CHOICES = 23;
constexpr auto MAX_NUM_MENU_OPTIONS = 10;
constexpr auto MAX_NUM_MENU_PAGES = 7;
constexpr auto MAX_NUM_MENU_LINES = 12;

/* @brief A page of text within a menu.
* 
* @param lines An array of TextObjects representing lines of text.
* @param numLines The number of lines.
* @param start_x The x-position of each line; unused if alignType is 1.
* @param start_y The y-position of the top-most line.
* @param spacer_y The amount that each subsequent line's y position should increase by.
* @param alignType Align type for lines. 0 = left, 1 = center, 2 = right.
*/
class MenuPage {
	public:
		TextObject lines[MAX_NUM_MENU_LINES];
		Sint8 numLines;
		Sint16 start_x;
		Sint16 start_y;
		Sint16 spacer_y;
		Sint8 alignType;
		MenuPage() {}
		void prepareMenuPage(Sint8, Sint16, Sint16, Sint16, Sint8);
		void setTextLine(Sint8, const char[]);
		void render();
};

/* @brief A group of pages of text within a menu. Used for multi-screen walls of text.
* 
* @param numPages The number of pages in the notebook.
* @param index The current page index.
* @param pages An array of pointers; each pointer represents a page.
* @param pageCounter A TextObject representing the onscreen page counter.
* @param pageCounter_x The x-position of the page counter.
* @param pageCounter_y The y-position of the page counter.
* @param alignType_pageCounter Align type for the page counter. 0 = left, 1 = center, 2 = right.
*/
class MenuNotebook {
	public:
		Sint8 numPages;
		Sint8 index;
		MenuPage *pages[MAX_NUM_MENU_PAGES];
		TextObject pageCounter;
		Sint16 pageCounter_x;
		//Sint16 pageCounter_y;
		Sint8 alignType_pageCounter;
		MenuNotebook() {}
		void prepareMenuNotebook(Sint8, Sint16, Sint16, Sint8);
		void openNotebook();
		void updatePageCounterText();
		Sint8 handleInput();
		void decrementPageNum();
		void incrementPageNum();
		void renderNotebook();
};

/* @brief A single option in a menu.
* 
* @param label A TextObject representing the option's label.
* @param labelPtr A pointer to a string for the label.
* @param choice A TextObject representing the option's current choice.
* @param choicePtr A pointer to an array of strings for the choice.
* @param description_1 A TextObject representing the top line of the option's current description.
* @param description_2 A TextObject representing the middle line of the option's current description.
* @param description_3 A TextObject representing the bottom line of the option's current description.
* @param descPtr_1 A pointer to an array of strings for the top line of the choice description(s). If the size is 1, all choices use the same description.
* @param descPtr_2 A pointer to an array of strings for the middle line of the choice description(s). If the size is 1, all choices use the same description.
* @param descPtr_3 A pointer to an array of strings for the bottom line of the choice description(s). If the size is 1, all choices use the same description.
* @param altDescPtr A pointer to a string for the alt description, to be used if optionIsLocked is set to true.
* @param numChoices The number of choices.
* @param oneDescription Whether or not one description is shared among all choices.
* @param choiceIsAllowed An array of whether or not each choice should be skipped over; useful for multi-platform development when some choices shouldn't be allowed for some systems.
* @param index The index of the currently-selected choice.
* @param index_init The default index.
* @param choicesWrap Whether or not navigating past the last option choice should wrap around to the first choice, and vice-versa.
* @param optionCanFreeze Whether or not an option can be frozen.
* @param optionIsFrozen If the option is frozen, its index cannot change, and its text is grayed out.
* @param optionIsLocked If the option is locked, then in addition to being frozen, its choices do not appear and the alt description is used in place of the normal description.
*/
class MenuOption {
	public:
		TextObject label;
		std::string labelPtr;
		TextObject choice;
		std::vector<std::string> choicePtr;
		TextObject description_1;
		TextObject description_2;
		TextObject description_3;
		std::vector<std::string> descPtr_1;
		std::vector<std::string> descPtr_2;
		std::vector<std::string> descPtr_3;
		std::string altDescPtr;
		Uint8 numChoices;
		bool oneDescription;
		bool choiceIsAllowed[MAX_NUM_OPTION_CHOICES];
		Sint8 index;
		Sint8 index_init;
		bool choicesWrap;
		bool optionCanFreeze;
		bool optionIsFrozen;
		bool optionIsLocked;
		MenuOption() {
		}
		void prepareMenuOption(std::string, const std::vector<std::string>, const std::vector<std::string>, const std::vector<std::string>, const std::vector<std::string>, std::string, Uint8, bool, Sint8, bool, bool);
		void setFrozen(bool, Sint8);
		void setLocked(bool);
		void initLabel();
		void updateLabel();
		void initChoicesAndDescriptions();
		void updateChoice(Sint8);
		void updateDescription(Sint8);
		void setDescriptionToIndex(Uint8);
		void render(bool);
		bool isValue(Uint8);
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
* @param topOnscreenIndex The index of the topmost visible option.
* @param bottomOnscreenIndex The index of the bottommost visible option.
* @param start_x_label The x-position of the top-most menu option's label.
* @param start_x_choice The x-position of the top-most menu option's choice.
* @param spacer_x The amount that each subsequent menu option's x position should increase by.
* @param start_y_option The y-position of the top-most menu option.
* @param start_y_desc The y-position of the top line of a 3-line description.
* @param spacer_y_option The amount that each subsequent menu option's y position should increase by.
* @param spacer_y_desc The amount that each subsequent description line's y position should increase by.
* @param alignType_label Align type for options labels. 0 = left, 1 = center, 2 = right.
* @param alignType_choice Align type for options choices. 0 = left, 1 = center, 2 = right.
* @param optionsWrap Whether or not navigating past the last menu option should wrap around to the first option, and vice-versa.
*/
class Menu {
	public:
		Uint8 numOptions;
		Uint8 numOnscreen;
		MenuOption *options[MAX_NUM_MENU_OPTIONS];
		SpriteInstance cursor;
		Sint8 cursorIndex;
		Sint8 scrollIndex;
		Sint8 cursorIndex_onscreen;
		bool keepIndexOnExit;
		Uint8 scrollSpacer;
		Sint8 topOnscreenIndex;
		Sint8 bottomOnscreenIndex;
		Sint16 start_x_label;
		Sint16 start_x_choice;
		Sint16 spacer_x;
		Sint16 start_y_option;
		Sint16 start_y_desc;
		Sint16 spacer_y_option;
		Sint16 spacer_y_desc;
		Sint8 alignType_label;
		Sint8 alignType_choice;
		bool optionsWrap;
		Menu() {
		}
		void prepareMenu(Uint8, Uint8, SpriteObject *, bool, Sint8, Sint16, Sint16, Sint16, Sint16, Sint16, Sint16, Sint16, Sint8, Sint8, bool);
		Sint8 handleInput(Uint8);
		void incrementOption();
		void decrementOption();
		void incrementCurrOptionChoice();
		void decrementCurrOptionChoice();
		void setOptionChoice(Sint8, Sint8);
		void updateOptionPositions();
		void updateOptionChoicePosition(Sint8);
		void updateOptionDescPosition(Sint8);
		void openMenu();
		void renderMenu();
};

extern Menu menu_main;
constexpr auto MENU_DIFFICULTY_INDEX = 0;
constexpr auto MENU_OTHER_INDEX = 1;
constexpr auto MENU_COSMETIC_INDEX = 2;
constexpr auto MENU_CHEATS_INDEX = 3;
constexpr auto MENU_RESET_SETTINGS_INDEX = 4;
constexpr auto MENU_HIGHSCORES_INDEX = 5;
#if defined(WII) || defined(GAMECUBE)
constexpr auto MENU_GBA_DEMO_INDEX = 6;
constexpr auto MENU_SOUND_INDEX = 7;
constexpr auto MENU_CREDITS_INDEX = 8;
constexpr auto MENU_QUIT_INDEX = 9;
constexpr auto MENU_NUM_OPTIONS = 10;
#else
constexpr auto MENU_SOUND_INDEX = 6;
constexpr auto MENU_CREDITS_INDEX = 7;
constexpr auto MENU_QUIT_INDEX = 8;
constexpr auto MENU_NUM_OPTIONS = 9;
#endif
#define MENU_DIFFICULTY     menu_main.options[MENU_DIFFICULTY_INDEX]
#define MENU_OTHER          menu_main.options[MENU_OTHER_INDEX]
#define MENU_COSMETIC       menu_main.options[MENU_COSMETIC_INDEX]
#define MENU_CHEATS         menu_main.options[MENU_CHEATS_INDEX]
#define MENU_RESET_SETTINGS menu_main.options[MENU_RESET_SETTINGS_INDEX]
#define MENU_HIGHSCORES     menu_main.options[MENU_HIGHSCORES_INDEX]
#if defined(WII) || defined(GAMECUBE)
#define MENU_GBA_DEMO       menu_main.options[MENU_GBA_DEMO_INDEX]
#endif
#define MENU_SOUND          menu_main.options[MENU_SOUND_INDEX]
#define MENU_CREDITS        menu_main.options[MENU_CREDITS_INDEX]
#define MENU_QUIT           menu_main.options[MENU_QUIT_INDEX]

extern Menu menu_difficulty;
constexpr auto MENU_PRESET_INDEX = 0;
constexpr auto MENU_EXTRA_LIVES_INDEX = 1;
constexpr auto MENU_LIVES_INTERVAL_INDEX = 2;
constexpr auto MENU_PEASANT_PENALTY_INDEX = 3;
constexpr auto MENU_KNIGHT_SPEED_INDEX = 4;
constexpr auto MENU_ARROW_SPEED_INDEX = 5;
constexpr auto MENU_ARCHER_FREQ_INDEX = 6;
constexpr auto MENU_TREASURE_HUTS_INDEX = 7;
constexpr auto DIFFICULTY_NUM_OPTIONS = 8;
#define MENU_PRESET          menu_difficulty.options[MENU_PRESET_INDEX]
#define MENU_EXTRA_LIVES     menu_difficulty.options[MENU_EXTRA_LIVES_INDEX]
#define MENU_LIVES_INTERVAL  menu_difficulty.options[MENU_LIVES_INTERVAL_INDEX]
#define MENU_PEASANT_PENALTY menu_difficulty.options[MENU_PEASANT_PENALTY_INDEX]
#define MENU_KNIGHT_SPEED    menu_difficulty.options[MENU_KNIGHT_SPEED_INDEX]
#define MENU_ARROW_SPEED     menu_difficulty.options[MENU_ARROW_SPEED_INDEX]
#define MENU_ARCHER_FREQ     menu_difficulty.options[MENU_ARCHER_FREQ_INDEX]
#define MENU_TREASURE_HUTS   menu_difficulty.options[MENU_TREASURE_HUTS_INDEX]

extern Menu menu_cosmetic;
constexpr auto MENU_FRAME_RATE_INDEX = 0;
constexpr auto MENU_MUSIC_INDEX = 1;
constexpr auto MENU_COMMENT_FREQ_INDEX = 2;
constexpr auto MENU_BIG_HEAD_MODE_INDEX = 3;
constexpr auto MENU_SCALING_INDEX = 4;
constexpr auto COSMETIC_NUM_OPTIONS = 5;
#define MENU_FRAME_RATE    menu_cosmetic.options[MENU_FRAME_RATE_INDEX]
#define MENU_MUSIC         menu_cosmetic.options[MENU_MUSIC_INDEX]
#define MENU_COMMENT_FREQ  menu_cosmetic.options[MENU_COMMENT_FREQ_INDEX]
#define MENU_BIG_HEAD_MODE menu_cosmetic.options[MENU_BIG_HEAD_MODE_INDEX]
#define MENU_SCALING       menu_cosmetic.options[MENU_SCALING_INDEX]
#define IS_BIG_HEAD_MODE   MENU_BIG_HEAD_MODE->isValue(0)

extern Menu menu_other;
constexpr auto MENU_STARTING_LEVEL_INDEX = 0;
constexpr auto MENU_SHUFFLE_LEVELS_INDEX = 1;
constexpr auto MENU_KNIGHT_MOVEMENT_INDEX = 2;
constexpr auto MENU_RESPAWN_BEHAVIOR_INDEX = 3;
constexpr auto MENU_LEVEL_TRAN_INDEX = 4;
constexpr auto OTHER_NUM_OPTIONS = 5;
#define MENU_STARTING_LEVEL   menu_other.options[MENU_STARTING_LEVEL_INDEX]
#define MENU_SHUFFLE_LEVELS   menu_other.options[MENU_SHUFFLE_LEVELS_INDEX]
#define MENU_KNIGHT_MOVEMENT  menu_other.options[MENU_KNIGHT_MOVEMENT_INDEX]
#define MENU_RESPAWN_BEHAVIOR menu_other.options[MENU_RESPAWN_BEHAVIOR_INDEX]
#define MENU_LEVEL_TRAN       menu_other.options[MENU_LEVEL_TRAN_INDEX]

extern Menu menu_cheats;
constexpr auto MENU_INF_LIVES_INDEX = 0;
constexpr auto MENU_SPEEDY_MODE_INDEX = 1;
constexpr auto MENU_NOCLIP_INDEX = 2;
constexpr auto MENU_DEBUG_MODE_INDEX = 3;
constexpr auto CHEAT_NUM_OPTIONS = 4;
#define MENU_INF_LIVES   menu_cheats.options[MENU_INF_LIVES_INDEX]
#define MENU_SPEEDY_MODE menu_cheats.options[MENU_SPEEDY_MODE_INDEX]
#define MENU_NOCLIP      menu_cheats.options[MENU_NOCLIP_INDEX]
#define MENU_DEBUG_MODE  menu_cheats.options[MENU_DEBUG_MODE_INDEX]

extern MenuNotebook menu_highscores_1;
extern MenuNotebook menu_highscores_2;
extern MenuNotebook menu_highscores_3;

extern Menu menu_sound;
constexpr auto MENU_CUTSCENE_TEST_INDEX = 0;
constexpr auto MENU_MUSIC_TEST_INDEX = 1;
constexpr auto MENU_SFX_TEST_INDEX = 2;
constexpr auto MENU_VOICE_TEST_INDEX = 3;
constexpr auto SOUND_NUM_OPTIONS = 4;
#define MENU_CUTSCENE_TEST menu_sound.options[MENU_CUTSCENE_TEST_INDEX]
#define MENU_MUSIC_TEST  menu_sound.options[MENU_MUSIC_TEST_INDEX]
#define MENU_SFX_TEST    menu_sound.options[MENU_SFX_TEST_INDEX]
#define MENU_VOICE_TEST menu_sound.options[MENU_VOICE_TEST_INDEX]

extern MenuNotebook menu_credits;

extern MenuNotebook menu_gba_demo;

extern Menu menu_quit;
constexpr auto QUIT_BACK_INDEX = 0;
constexpr auto QUIT_CONFIRM_INDEX = 1;
constexpr auto QUIT_NUM_OPTIONS = 2;
#define QUIT_BACK    menu_quit.options[QUIT_BACK_INDEX]
#define QUIT_CONFIRM menu_quit.options[QUIT_CONFIRM_INDEX]

extern State_Settings_General getSettingsGeneral();
extern State_Settings_Difficulty getSettingsDifficulty();
extern State_Settings_Cosmetic getSettingsCosmetic();
extern State_Settings_Other getSettingsOther();
extern State_Settings_Cheats getSettingsCheats();
extern State_Settings_Unlocks getSettingsUnlocks();
extern State_Addon_v_2_1 getSettings_v_2_1();
extern void updateFrameRate();
extern void setPreset(Sint8);
extern void updateHighScores();

#endif