#include "config.h"
#include "menu.h"

void saveGameState_settings() {
	gameState.settings_general = getSettingsGeneral();
	gameState.settings_difficulty = getSettingsDifficulty();
	gameState.settings_cosmetic = getSettingsCosmetic();
	gameState.settings_other = getSettingsOther();
	gameState.settings_cheats = getSettingsCheats();
	gameState.settings_unlocks = getSettingsUnlocks();
	saveBin = SDL_RWFromFile(SAVE_FILE, "wb");
	SDL_RWwrite(saveBin, &gameState, sizeof(gameState), 1);
	SDL_RWclose(saveBin);
}

void loadGameState() {
	saveBin = SDL_RWFromFile(SAVE_FILE, "rb");

	if (saveBin) {
		SDL_RWread(saveBin, &gameState, sizeof(gameState), 1);
		SDL_RWclose(saveBin);
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
		menu_other.setOptionChoice(MENU_KNIGHT_BEHAVIOR_INDEX, gameState.settings_other.knightBehavior);
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
		setPreset(MENU_PRESET->index);
	}
	else {
		// File does not exist, initialize default game state
		gameState.settings_general = getSettingsGeneral();
		gameState.settings_difficulty = getSettingsDifficulty();
		gameState.settings_cosmetic = getSettingsCosmetic();
		gameState.settings_other = getSettingsOther();
		gameState.settings_cheats = getSettingsCheats();
		gameState.settings_unlocks = getSettingsUnlocks();
		gameState.autosave = { -1, 0, 0, 0, 0, gameState.settings_difficulty, gameState.settings_cheats };
	}
}