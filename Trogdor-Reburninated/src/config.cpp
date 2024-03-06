#include "config.h"
#include "menu.h"

void saveGameState_settings() {
	gameState.settings_general = getSettingsGeneral();
	gameState.settings_difficulty = getSettingsDifficulty();
	gameState.settings_cosmetic = getSettingsCosmetic();
	gameState.settings_other = getSettingsOther();
	gameState.settings_cheats = getSettingsCheats();
	gameState.settings_unlocks = getSettingsUnlocks();
	gameState.addon_v_2_1 = getSettings_v_2_1();
	saveGameState_all();
}

void loadGameState() {
	saveBin = SDL_RWFromFile(SAVE_FILE, "rb");

	if (saveBin) {
		SDL_RWread(saveBin, &gameState, sizeof(gameState), 1);
		SDL_RWclose(saveBin);
		fixSaveDataIntegrity();
		setOptionsFromSaveData();
	}
	else {
		// File does not exist, initialize default game state
		initializeDefaultGameState();
	}
}

void loadGameState_partial() { // used for display init (saved scaling option wouldn't load properly otherwise)
	saveBin = SDL_RWFromFile(SAVE_FILE, "rb");

	if (saveBin) {
		SDL_RWread(saveBin, &gameState, sizeof(gameState), 1);
		SDL_RWclose(saveBin);
		gameState.settings_cosmetic.scaling %= 4;
	}
	else {
		// File does not exist, use default scaling
#if defined(VITA) || defined(WII_U) || defined(SWITCH)
		gameState.settings_cosmetic.scaling = 1;
#elif defined(RG35XX) || defined(PSP)
		gameState.settings_cosmetic.scaling = 3;
#else
		gameState.settings_cosmetic.scaling = 0;
#endif
	}
}

void setOptionsFromSaveData() {
	menu_difficulty.setOptionChoice(MENU_PRESET_INDEX, gameState.settings_difficulty.preset);
	menu_difficulty.setOptionChoice(MENU_EXTRA_LIVES_INDEX, gameState.settings_difficulty.extraLives);
	menu_difficulty.setOptionChoice(MENU_LIVES_INTERVAL_INDEX, gameState.settings_difficulty.livesInterval);
	menu_difficulty.setOptionChoice(MENU_PEASANT_PENALTY_INDEX, gameState.settings_difficulty.peasantPenalty);
	menu_difficulty.setOptionChoice(MENU_KNIGHT_SPEED_INDEX, gameState.settings_difficulty.knightSpeed);
	menu_difficulty.setOptionChoice(MENU_ARROW_SPEED_INDEX, gameState.settings_difficulty.arrowSpeed);
	menu_difficulty.setOptionChoice(MENU_ARCHER_FREQ_INDEX, gameState.settings_difficulty.archerFreq);
	menu_difficulty.setOptionChoice(MENU_TREASURE_HUTS_INDEX, gameState.settings_difficulty.treasureHuts);
	menu_cosmetic.setOptionChoice(MENU_FRAME_RATE_INDEX, gameState.settings_cosmetic.frameRate);
	updateFrameRate();
	menu_cosmetic.setOptionChoice(MENU_MUSIC_INDEX, gameState.settings_cosmetic.music);
	menu_cosmetic.setOptionChoice(MENU_COMMENT_FREQ_INDEX, gameState.settings_cosmetic.commentFreq);
	menu_cosmetic.setOptionChoice(MENU_BIG_HEAD_MODE_INDEX, gameState.settings_cosmetic.bigHeadMode);
	menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, gameState.settings_cosmetic.scaling);
	menu_other.setOptionChoice(MENU_STARTING_LEVEL_INDEX, gameState.settings_other.startingLevel);
	menu_other.setOptionChoice(MENU_SHUFFLE_LEVELS_INDEX, gameState.settings_other.shuffleLevels);
	menu_other.setOptionChoice(MENU_RESPAWN_BEHAVIOR_INDEX, gameState.settings_other.respawnBehavior);
	menu_other.setOptionChoice(MENU_LEVEL_TRAN_INDEX, gameState.settings_other.levelTran);
	menu_cheats.setOptionChoice(MENU_INF_LIVES_INDEX, gameState.settings_cheats.infLives);
	menu_cheats.setOptionChoice(MENU_SPEEDY_MODE_INDEX, gameState.settings_cheats.speedyMode);
	menu_cheats.setOptionChoice(MENU_NOCLIP_INDEX, gameState.settings_cheats.noclip);
	menu_cheats.setOptionChoice(MENU_DEBUG_MODE_INDEX, gameState.settings_cheats.debugMode);
	MENU_INF_LIVES->setLocked(gameState.settings_unlocks.locked_infLives);
	MENU_EXTRA_LIVES->choiceIsAllowed[6] = !gameState.settings_unlocks.locked_infLives;
	MENU_EXTRA_LIVES->choiceIsAllowed[7] = !gameState.settings_unlocks.locked_infLives;
	MENU_EXTRA_LIVES->choiceIsAllowed[8] = !gameState.settings_unlocks.locked_infLives;
	MENU_SPEEDY_MODE->setLocked(gameState.settings_unlocks.locked_speedyMode);
	MENU_NOCLIP->setLocked(gameState.settings_unlocks.locked_noclip);
	MENU_DEBUG_MODE->setLocked(gameState.settings_unlocks.locked_debugMode);
	menu_other.setOptionChoice(MENU_KNIGHT_MOVEMENT_INDEX, gameState.addon_v_2_1.knightMovement);
	setPreset(MENU_PRESET->index);
}

void initializeDefaultGameState() {
	gameState.settings_general = getSettingsGeneral();
	gameState.settings_difficulty = getSettingsDifficulty();
	gameState.settings_cosmetic = getSettingsCosmetic();
	gameState.settings_other = getSettingsOther();
	gameState.settings_cheats = getSettingsCheats();
	gameState.settings_unlocks = getSettingsUnlocks();
	gameState.addon_v_2_1 = getSettings_v_2_1();
	gameState.autosave = { -1, 0, 0, 0, 0, false, gameState.settings_difficulty, gameState.settings_other.shuffleLevels, gameState.settings_cheats };
	gameState.highscores = { 0, 0, 0, 0, 0, 0 };
	updateFrameRate();
}

void fixSaveDataIntegrity() {
	gameState.settings_difficulty.preset %= MENU_PRESET->numChoices;
	gameState.settings_difficulty.extraLives %= MENU_EXTRA_LIVES->numChoices;
	gameState.settings_difficulty.livesInterval %= MENU_LIVES_INTERVAL->numChoices;
	gameState.settings_difficulty.peasantPenalty %= MENU_PEASANT_PENALTY->numChoices;
	gameState.settings_difficulty.knightSpeed %= MENU_KNIGHT_SPEED->numChoices;
	gameState.settings_difficulty.arrowSpeed %= MENU_ARROW_SPEED->numChoices;
	gameState.settings_difficulty.archerFreq %= MENU_ARCHER_FREQ->numChoices;
	gameState.settings_difficulty.treasureHuts %= MENU_TREASURE_HUTS->numChoices;
	gameState.settings_cosmetic.frameRate %= MENU_FRAME_RATE->numChoices;
	gameState.settings_cosmetic.music %= MENU_MUSIC->numChoices;
	gameState.settings_cosmetic.commentFreq %= MENU_COMMENT_FREQ->numChoices;
	gameState.settings_cosmetic.bigHeadMode %= MENU_BIG_HEAD_MODE->numChoices;
	gameState.settings_cosmetic.scaling %= MENU_SCALING->numChoices;
	gameState.settings_other.startingLevel %= MENU_STARTING_LEVEL->numChoices;
	gameState.settings_other.shuffleLevels %= MENU_SHUFFLE_LEVELS->numChoices;
	gameState.settings_other.respawnBehavior %= MENU_RESPAWN_BEHAVIOR->numChoices;
	gameState.settings_other.levelTran %= MENU_LEVEL_TRAN->numChoices;
	gameState.settings_cheats.infLives %= MENU_INF_LIVES->numChoices;
	gameState.settings_cheats.speedyMode %= MENU_SPEEDY_MODE->numChoices;
	gameState.settings_cheats.noclip %= MENU_NOCLIP->numChoices;
	gameState.settings_cheats.debugMode %= MENU_DEBUG_MODE->numChoices;
	MENU_PRESET->index %= MENU_PRESET->numChoices;
	gameState.addon_v_2_1.knightMovement %= MENU_KNIGHT_MOVEMENT->numChoices;
}

void saveGameState_all() {
	saveBin = SDL_RWFromFile(SAVE_FILE, "wb");
	if (saveBin) {
		SDL_RWwrite(saveBin, &gameState, sizeof(gameState), 1);
		SDL_RWclose(saveBin);
	}
}