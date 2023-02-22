#include "config.h"
#include "menu.h"

void saveGameState() {
	gameState.settings = getSettings();
	saveBin = SDL_RWFromFile(SAVE_FILE, "wb");
	SDL_RWwrite(saveBin, &gameState, sizeof(gameState), 1);
	SDL_RWclose(saveBin);
}

void loadGameState() {
	saveBin = SDL_RWFromFile(SAVE_FILE, "rb");

	if (saveBin) {
		SDL_RWread(saveBin, &gameState, sizeof(gameState), 1);
		menu_difficulty.setOptionChoice(MENU_STARTING_LEVEL_INDEX, gameState.settings.startingLevel);
		menu_difficulty.setOptionChoice(MENU_EXTRA_LIVES_INDEX, gameState.settings.extraLives);
		menu_difficulty.setOptionChoice(MENU_LIVES_INTERVAL_INDEX, gameState.settings.livesInterval);
		menu_difficulty.setOptionChoice(MENU_PEASANT_PENALTY_INDEX, gameState.settings.peasantPenalty);
		menu_difficulty.setOptionChoice(MENU_TREASURE_HUTS_INDEX, gameState.settings.treasureHuts);
		menu_difficulty.setOptionChoice(MENU_ARCHER_FREQ_INDEX, gameState.settings.archerFreq);
		menu_difficulty.setOptionChoice(MENU_KNIGHT_BEHAVIOR_INDEX, gameState.settings.knightBehavior);
		menu_difficulty.setOptionChoice(MENU_KNIGHT_SPEED_INDEX, gameState.settings.knightSpeed);
		menu_cosmetic.setOptionChoice(MENU_FRAME_RATE_INDEX, gameState.settings.frameRate);
		updateFrameRate();
		menu_cosmetic.setOptionChoice(MENU_LEVEL_TRAN_INDEX, gameState.settings.levelTran);
		menu_cosmetic.setOptionChoice(MENU_MUSIC_INDEX, gameState.settings.music);
		menu_cosmetic.setOptionChoice(MENU_COMMENT_FREQ_INDEX, gameState.settings.commentFreq);
		menu_cosmetic.setOptionChoice(MENU_BIG_HEAD_MODE_INDEX, gameState.settings.bigHeadMode);
		menu_cosmetic.setOptionChoice(MENU_SCALING_INDEX, gameState.settings.scaling);
		menu_cheats.setOptionChoice(CHEAT_INF_LIVES_INDEX, gameState.settings.infLives);
		menu_cheats.setOptionChoice(CHEAT_SPEEDY_MODE_INDEX, gameState.settings.speedyMode);
		menu_cheats.setOptionChoice(CHEAT_NOCLIP_INDEX, gameState.settings.noclip);
		menu_cheats.setOptionChoice(CHEAT_DEBUG_MODE_INDEX, gameState.settings.debugMode);
		CHEAT_INF_LIVES->setLocked(gameState.settings.locked_infLives);
		CHEAT_SPEEDY_MODE->setLocked(gameState.settings.locked_speedyMode);
		CHEAT_NOCLIP->setLocked(gameState.settings.locked_noclip);
		CHEAT_DEBUG_MODE->setLocked(gameState.settings.locked_debugMode);
		MENU_EXTRA_LIVES->choiceIsAllowed[6] = !gameState.settings.locked_infLives;
		MENU_EXTRA_LIVES->choiceIsAllowed[7] = !gameState.settings.locked_infLives;
		MENU_EXTRA_LIVES->choiceIsAllowed[8] = !gameState.settings.locked_infLives;
		SDL_RWclose(saveBin);
	}
	else {
		// File does not exist, initialize default game state
		gameState.settings = getSettings();
	}
}