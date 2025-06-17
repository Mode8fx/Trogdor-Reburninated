#include "classes.h"
#include "general.h"
#include "input.h"
#include "text_objects.h"
#include "level_data.h"
#include "menu.h"
#include "config.h"

// for all "directions": 1 = up, 2 = down, 3 = left, 4 = right
const Uint8 contraArrayKey[10] = { 0, 0, 1, 1, 2, 3, 2, 3, 5, 4 }; // Up Up Down Down Left Right Left Right B A (Konami code)
const Uint8 pacmanArrayKey[11] = { 0, 0, 0, 1, 1, 1, 2, 3, 2, 3, 2 }; // Up Up Up Down Down Down Left Right Left Right Left (play Pac-Man on a Ms. Pac-Man + Galaga arcade cabinet)
const Uint8 s3kArrayKey[9] = { 2, 2, 2, 3, 3, 3, 0, 0, 0 }; // Left Left Left Right Right Right Up Up Up (Sonic & Knuckles and S3&K level select)
const Uint8 fzxArrayKey[8] = { 2, 5, 3, 0, 1, 2, 3, 4 }; // Left B Right Up Down Left Right A ((roughly) unlock everything in F-Zero X)
const Uint8 dkcArrayKey[6] = { 5, 4, 9, 9, 4, 8 }; // B A R R A L (Donkey Kong Country 50 lives code)

constexpr auto LEFT_BOUND = 17;
constexpr auto RIGHT_BOUND = 233;
constexpr auto UPPER_BOUND = 30;
constexpr auto LOWER_BOUND = 155;
constexpr auto LEFT_BOUND_TROG = -2; // LEFT_BOUND  - (39 / 2)
constexpr auto RIGHT_BOUND_TROG = 214; // RIGHT_BOUND - (39 / 2)
constexpr auto UPPER_BOUND_TROG = 7; // UPPER_BOUND - (46 / 2)
constexpr auto LOWER_BOUND_TROG = 132; // LOWER_BOUND - (46 / 2)
constexpr auto LEFT_BOUND_KNIGHT = 7; // LEFT_BOUND  - (21 / 2)
constexpr auto RIGHT_BOUND_KNIGHT = 223; // RIGHT_BOUND - (21 / 2)
constexpr auto UPPER_BOUND_KNIGHT = 18; // UPPER_BOUND - (24 / 2)
constexpr auto LOWER_BOUND_KNIGHT = 143; // LOWER_BOUND - (24 / 2)
constexpr auto LEFT_BOUND_KNIGHT_ALT = 11; // 0 + (21 / 2)
constexpr auto RIGHT_BOUND_KNIGHT_ALT = 240; // 250 - (21 / 2)
constexpr auto UPPER_BOUND_KNIGHT_ALT = 37; // 25 + (24 / 2)
constexpr auto LOWER_BOUND_KNIGHT_ALT = 168; // 180 - (24 / 2)
constexpr auto ARCHER_Y_UPPER = 20; //   30 - (20 / 2)
constexpr auto ARCHER_Y_LOWER = 145; //  155 - (20 / 2)
constexpr auto ARCHER_LEFT_X = -1; //  179 / 5000 * 250 - (20 / 2)
constexpr auto ARCHER_RIGHT_X = 231; // 4829 / 5000 * 250 - (20 / 2)

#if defined(SDL1)
inline bool SDL_HasIntersection(const SDL_Rect *A, const SDL_Rect *B) {
	return (!((A->x + A->w < B->x) || (B->x + B->w < A->x) || (A->y + A->h < B->y) || (B->y + B->h < A->y)));
}
#endif

Cottage::Cottage() {
}

Cottage::Cottage(Sint16 pos_x, Sint16 pos_y, Sint16 dir) {
	frameState.set(10);
	sprite = SpriteInstance(&sprite_cottage, 0, (dir - 1), (float)pos_x, (float)pos_y);
	sprite_fire = SpriteInstance(&sprite_cottage_fire, 0, 0, (float)sprite.dstrect.x + 5, (float)sprite.dstrect.y - 5);
	burning = false;
	burned = false;
	direction = dir;
	switch (direction) {
		case 1:
			sprite.collision = { 8 + sprite.dstrect.x, 15 + sprite.dstrect.y, 23, 12 };
			sprite_fire.collision = { 4 + sprite.dstrect.x, 1 + sprite.dstrect.y, 32, 36 };
			break;
		case 2:
			sprite.collision = { 8 + sprite.dstrect.x, 16 + sprite.dstrect.y, 23, 12 };
			sprite_fire.collision = { 3 + sprite.dstrect.x, 0 + sprite.dstrect.y, 33, 37 };
			break;
		case 3:
			sprite.collision = { 12 + sprite.dstrect.x, 14 + sprite.dstrect.y, 22, 13 };
			sprite_fire.collision = { 7 + sprite.dstrect.x, 1 + sprite.dstrect.y, 32, 36 };
			break;
		case 4:
			sprite.collision = { 7 + sprite.dstrect.x, 15 + sprite.dstrect.y, 25, 12 };
			sprite_fire.collision = { 4 + sprite.dstrect.x, 1 + sprite.dstrect.y, 32, 36 };
			break;
		default:
			sprite.collision = { 8 + sprite.dstrect.x, 16 + sprite.dstrect.y, 23, 12 };
			sprite_fire.collision = { 3 + sprite.dstrect.x, 0 + sprite.dstrect.y, 33, 37 };
			break;
	}
}

void Cottage::updateFrameState() {
	if (frameState.startingFrame(10)) {
		loadAndPlaySound(SFX_BURN_HUT);
	}
	if (frameState.frame >= 12 && frameState.frame <= 28 && frameState.atStartOfFrame) {
		sprite_fire.setFrame(((frameState.frame - 12) / 3) % 4);
		sprite_fire.setForm(direction == 3);
		if (frameState.startingFrame(26)) {
			sprite.setFrame(1);
		}
	}
	if (frameState.startingFrame(30)) {
		burned = true;
	}
	frameState.increment();
}

Knight::Knight() {
}

Knight::Knight(Sint16 pos_x, Sint16 pos_y, Sint8 dir, bool fr, float knightSpeed) {
	anim_frameState.set(1);
	move_frameState.set(1);
	moving = true;
	sprite = SpriteInstance(&sprite_knight, 0, fr, pos_x, pos_y);
	sprite.facingRight = fr;
	home_x = pos_x;
	home_y = pos_y;
	half_src_w = sprite_knight.dstrect.w / 2;
	half_src_h = sprite_knight.dstrect.h / 2 + 4;
	offset_x = 0;
	offset_y = 0;
	direction = dir;
	updateCollision();
	moveFrameCap = 60 / knightSpeed;
	offsetConst = knightSpeed * 34 / 30;
}

inline void Knight::updateCollision() {
	if (sprite.facingRight) {
		sprite.collision = { 4 + sprite.dstrect.x, 9 + sprite.dstrect.y, 9, 13 };
	} else {
		sprite.collision = { 8 + sprite.dstrect.x, 9 + sprite.dstrect.y, 9, 13 };
	}
}

void Knight::updateHome(float knightIncrement) {
	if (home_x < LEFT_BOUND_KNIGHT) {
		direction = rand() % 6;
		home_x = LEFT_BOUND_KNIGHT + 1;
	} else if (home_x > RIGHT_BOUND_KNIGHT) {
		direction = rand() % 6;
		home_x = RIGHT_BOUND_KNIGHT - 1;
	}
	if (home_y < UPPER_BOUND_KNIGHT + 50) {
		direction = rand() % 6;
		home_y = UPPER_BOUND_KNIGHT + 51;
	} else if (home_y > LOWER_BOUND_KNIGHT) {
		direction = rand() % 6;
		home_y = LOWER_BOUND_KNIGHT - 1;
	}
	switch (direction) {
		case 0:
			home_x += knightIncrement;
			break;
		case 1:
		case 2:
			home_y += knightIncrement;
			break;
		case 3:
		case 4:
			home_x -= knightIncrement;
			break;
		case 5:
			home_y -= knightIncrement;
			break;
		default:
			break;
	}
}

void Knight::updateFrameState() {
	if (anim_frameState.frame > 60) {
		anim_frameState.subtract(60);
	}
	if (anim_frameState.atStartOfFrame) {
		switch (anim_frameState.frame) {
			case 1:
			case 9:
			case 17:
			case 25:
			case 33:
			case 41:
			case 49:
			case 57:
				sprite.setFrame(0);
				break;
			case 5:
			case 29:
			case 53:
				sprite.setFrame(1);
				break;
			case 13:
			case 21:
			case 37:
			case 45:
				sprite.setFrame(3);
				break;
			default:
				break;
		}
	}
	anim_frameState.increment();
}

void Knight::move(float knightSpeed) {
	if (move_frameState.subFrame > moveFrameCap) {
		move_frameState.subtract(moveFrameCap);
	}
	if (move_frameState.subFrame * knightSpeed <= 30) {
		offset_x = move_frameState.subFrame * offsetConst;
	} else {
		offset_x = (float)68 - (move_frameState.subFrame * offsetConst);
	}
	offset_y = -offset_x;
	if (!sprite.facingRight) {
		offset_x = -offset_x;
	}

	sprite.setPosX(home_x + offset_x - half_src_w);
	sprite.setPosY(home_y + offset_y - half_src_h);
	updateCollision();
	move_frameState.increment();
}

void Knight::move_alt(float knightIncrement_alt, float knightIncrement_alt_2, float knightSpeed) {
	if (move_frameState.subFrame > moveFrameCap) {
		move_frameState.subtract(moveFrameCap);
	}
	if (move_frameState.subFrame * knightSpeed <= 30) {
		offset_x = knightIncrement_alt;
		offset_y = -knightIncrement_alt;
	} else {
		offset_x = -knightIncrement_alt_2;
		offset_y = 0;
	}
	if (!sprite.facingRight) {
		offset_x = -offset_x;
	}
	switch (direction) {
		case 0:
			offset_y = -offset_y;
			float_i = offset_x;
			offset_x = offset_y;
			offset_y = float_i;
			break;
		case 1:
			offset_x = -offset_x;
			offset_y = -offset_y;
			break;
		case 2:
			offset_x = -offset_x;
			float_i = offset_x;
			offset_x = offset_y;
			offset_y = float_i;
			break;
		default:
			break;
	};

	home_x += offset_x;
	home_y += offset_y;

	if (home_x < LEFT_BOUND_KNIGHT_ALT) {
		direction = rand() % 4;
		home_x = LEFT_BOUND_KNIGHT_ALT;
	}
	else if (home_x > RIGHT_BOUND_KNIGHT_ALT) {
		direction = rand() % 4;
		home_x = RIGHT_BOUND_KNIGHT_ALT;
	}
	if (home_y < UPPER_BOUND_KNIGHT_ALT) {
		direction = rand() % 4;
		home_y = UPPER_BOUND_KNIGHT_ALT;
	}
	else if (home_y > LOWER_BOUND_KNIGHT_ALT) {
		direction = rand() % 4;
		home_y = LOWER_BOUND_KNIGHT_ALT;
	}

	sprite.setPosX(home_x - half_src_w);
	sprite.setPosY(home_y - half_src_h);
	updateCollision();
	move_frameState.increment();
}

Peasant::Peasant() {
	frameState.set(1);
	sprite = SpriteInstance(&sprite_peasant, 0, 0, 0, 0);
	sprite.isActive = false;
	myHome = 0;
	stomped = false;
	waiting = false;
	burning = false;
	myStartx = 0;
	myStarty = 0;
	direction = 2;
	myTargetx = 0;
	myTargety = 0;
	returning = false;
	timer = 0;
	sprite.collision = { 8 + sprite.dstrect.x, 5 + sprite.dstrect.y, 8, 19 };
}

void Peasant::updateFrameState() {
	if (frameState.atStartOfFrame) {
		switch (frameState.frame) {
			case 1:
				sprite.setFrame(0);
				sprite.setForm(0);
				break;
			case 4:
				sprite.setFrame(1);
				break;
			case 8:
				sprite.setFrame(0);
				sprite.setForm(3);
				loadAndPlaySound(SFX_SQUISH);
				rand_var = rand() % 1000;
				if (rand_var < 3 * SB_VOICE_MULT) {
					loadAndPlaySound(SFX_SB2);
				} else if (rand_var < 6 * SB_VOICE_MULT) {
					loadAndPlaySound(SFX_SBSQUISH1);
				} else if (rand_var < 10 * SB_VOICE_MULT) {
					loadAndPlaySound(SFX_SBSQUISH2);
				}
				break;
			case 25:
				sprite.isActive = false;
				stomped = false;
				sprite.setPosX(-300);
				break;
			case 26:
				sprite.setFrame(0);
				sprite.setForm(1);
				break;
			case 27:
				sprite.setFrame(1);
				break;
			default:
				break;
		}
	}
	switch (frameState.frame) {
		case 6:
			if (frameState.atEndOfFrame) {
				frameState.set(1);
			} else {
				frameState.increment();
			}
			break;
		case 27:
			if (frameState.atEndOfFrame) {
				frameState.set(26);
			} else {
				frameState.increment();
			}
			break;
		default:
			frameState.increment();
			break;
	}
}

Archer::Archer() {
}

Archer::Archer(Sint16 pos_x, Sint16 pos_y, bool fr) {
	frameState.set(1);
	sprite = SpriteInstance(&sprite_archer, 0, fr, pos_x, pos_y);
	sprite.facingRight = fr;
	sprite.isActive = false;
}

void Archer::updateFrameState() {
	if (frameState.atStartOfFrame) {
		switch (frameState.frame) {
			case 14:
				sprite.setFrame(1);
				break;
			case 20:
				sprite.setFrame(0);
				// shoot arrow; this is handled by GameManager
				break;
			case 23:
				sprite.setPosY(-300);
				sprite.isActive = false;
			default:
				break;
		}
	}
	frameState.increment();
}

Arrow::Arrow() {
}

Arrow::Arrow(Sint16 pos_x, Sint16 pos_y, bool fr) {
	frameState.set(1);
	sprite = SpriteInstance(&sprite_arrow, 0, fr, pos_x, pos_y);
	sprite.facingRight = fr;
	sprite.isActive = false;
	sprite.collision = { 1 + sprite.facingRight + sprite.dstrect.x, 1 + sprite.dstrect.y, 12, 3 };
}

void Arrow::updateFrameState(Sint8 arrowSpeed) {
	if (frameState.startingFrame(1)) { // 4?
		loadAndPlaySound(SFX_ARROW);
	}
	if (sprite.facingRight) {
		sprite.addPosX(arrowSpeed);
		if (sprite.dstrect.x > gameWidth) { // not exactly the same as the original, but close enough
			clear();
		}
		sprite.collision.x = 2 + sprite.dstrect.x;
		sprite.collision.y = 1 + sprite.dstrect.y;

	} else {
		sprite.addPosX((float)-arrowSpeed);
		if (sprite.dstrect.x < -8) { // not exactly the same as the original, but close enough
			clear();
		}
		sprite.collision.x = 1 + sprite.dstrect.x;
		sprite.collision.y = 1 + sprite.dstrect.y;
	}
	frameState.increment();
}

void Arrow::clear() {
	sprite.isActive = false;
	sprite.setPosX(-500);
}

Loot::Loot() {
	Loot(0, 0);
}

Loot::Loot(Sint16 pos_x, Sint16 pos_y) {
	sprite = SpriteInstance(&sprite_loot, 0, 0, pos_x, pos_y);
	sprite.isActive = false;
}

Trogdor::Trogdor() {
}

Trogdor::Trogdor(bool bigHead, Sint8 speedyMode) {
	frameState.set(1);
	if (bigHead) {
		sprite = SpriteInstance(&sprite_trogdor_bighead, 0, 1, 0, 0);
		sprite_death = SpriteInstance(&sprite_trogdor_dead, 0, 1);
		sprite_end_of_level = SpriteInstance(&sprite_end_of_level_trogdor, 0, 1);
	} else {
		sprite = SpriteInstance(&sprite_trogdor, 0, 1, 0, 0);
		sprite_death = SpriteInstance(&sprite_trogdor_dead, 0, 0);
		sprite_end_of_level = SpriteInstance(&sprite_end_of_level_trogdor, 0, 0);
	}
	sprite.facingRight = true;
	spawnPos_x = (float)(2780.0 / 5000 * gameWidth) - (sprite.spriteObj->dstrect.w / 2);
	spawnPos_y = (float)(2360.0 / 3600 * gameHeight) - (sprite.spriteObj->dstrect.h / 2);
	sprite.setPosX(spawnPos_x);
	sprite.setPosY(spawnPos_y);
	sprite.collision = { 11 + sprite.dstrect.x, 11 + sprite.dstrect.y, 18, 24 };
	fire_frameState.set(1);
	sprite_fire = SpriteInstance(&sprite_trogdor_fire, 0, sprite.facingRight, (float)(sprite.dstrect.x) - 24 + (sprite.facingRight * 62), (float)(sprite.dstrect.y) + 10);
	invince = 0;
	sprite.isActive = true;
	x_offset = 0;
	y_offset = 0;
	moveSpeed = 3 + speedyMode;
	frameStateFlag = 0;
	hutCollisionRect = { sprite.dstrect.x, sprite.dstrect.y, sprite.spriteObj->sub[1][0].w, sprite.spriteObj->sub[1][0].h}; // sprite.dstrect, NOT collision; to fix height comparison being inconsistent
}

void Trogdor::updateFrameState() {
	if (frameState.atStartOfFrame) {
		switch (frameState.frame) {
			case 20: // sworded
				sprite_death.setFrame(0);
				sprite_death.setPosX((float)sprite.dstrect.x + ((sprite.spriteObj->dstrect.w - sprite_death.spriteObj->dstrect.w) / 2));
				sprite_death.setPosY((float)sprite.dstrect.y + (sprite.spriteObj->dstrect.h - sprite_death.spriteObj->dstrect.h) - 7);
				break;
			case 50: // arrowed
				sprite_death.setFrame(1);
				sprite_death.setPosX((float)sprite.dstrect.x + ((sprite.spriteObj->dstrect.w - sprite_death.spriteObj->dstrect.w) / 2));
				sprite_death.setPosY((float)sprite.dstrect.y + (sprite.spriteObj->dstrect.h - sprite_death.spriteObj->dstrect.h) - 7);
				break;
			case 34:
			case 38:
			case 42:
			case 64:
			case 68:
			case 72:
				sprite.isActive = false;
				break;
			case 36:
			case 40:
			case 66:
			case 70:
				sprite.isActive = true;
				break;
			case 48:
			case 78:
				sprite.isActive = true;
				frameState.set(0); // 0 is intentional
				break;
			default:
				break;
		}
	}
	switch (frameState.frame) {
		case 22:
		case 52:
			if (frameState.atEndOfFrame) loadAndPlaySound(SFX_DEATH);
			frameState.increment();
			break;
		case 48:
		case 78:
			break;
		default:
			frameState.increment();
			break;
	}
}

void Trogdor::resetPos(bool giveInvince) {
	sprite.facingRight = true;
	sprite.setFrameAndForm(0, sprite.facingRight);
	sprite.setPosX(spawnPos_x);
	sprite.setPosY(spawnPos_y);
	sprite.collision = { 11 + sprite.dstrect.x, 11 + sprite.dstrect.y, 18, 24 };
	if (giveInvince) {
		invince = 36;
	}
}

void Trogdor::updateBreathLoc() {
	if (sprite.facingRight) {
		sprite_fire.setPosX((float)sprite.dstrect.x + 38);
		sprite_fire.setPosY((float)sprite.dstrect.y + 10);
	} else {
		sprite_fire.setPosX((float)sprite.dstrect.x - 24);
		sprite_fire.setPosY((float)sprite.dstrect.y + 10);
	}
}

void Trogdor::invinceCheck() {
	if (invince > 0) {
		invince -= frameRateMult;
		if ((Uint8)invince % 3 == 0) {
			sprite.isActive = false;
		} else {
			sprite.isActive = true;
		}
		if (invince <= 0) {
			sprite.isActive = true;
		}
	}
}

MenuManager::MenuManager() {
	contraIndex = 0;
	pacmanIndex = 0;
	s3kIndex = 0;
	fzxIndex = 0;
	dkcIndex = 0;
	page = 1;
	if (gameHiResMult < 2) {
		maxPageNum = MAX_PAGE_NUM_LOWRES;
	} else {
		maxPageNum = MAX_PAGE_NUM_HIRES;
	}
	cursor = SpriteInstance(&sprite_cursor, 0, 0);
	cursor.dstrect.x = (int)((double)text_3_continue_1.dstrect.x / gameHiResMult) - (cursor.dstrect.w * 2);
}

bool MenuManager::handleCheat(Uint8 menuIndex, const Uint8 *cheatArrayKey, Uint8 cheatLen, Sint8 &cheatIndex, SoundEffect *sfx, Sint8 indexAtUnlock) {
	if (menu_cheats.options[menuIndex]->optionIsLocked) {
		if (keyInputs != 0) {
			if (keyInputs == (1 << (cheatArrayKey[cheatIndex]))) {
				cheatIndex++;
				if ((Uint32)cheatIndex == cheatLen) {
					unlockCheat(menuIndex, indexAtUnlock);
					// this was originally played upon starting the game, but I'm changing it; it's much clearer this way, especially since the controls are different for each system
					loadAndPlaySound(sfx);
					return true;
				}
			} else {
				cheatIndex = 0;
			}
		}
	}
	return false;
}

void MenuManager::unlockCheat(Uint8 menuIndex, Sint8 indexAtUnlock) {
	menu_cheats.options[menuIndex]->setLocked(false);
	menu_cheats.setOptionChoice(menuIndex, indexAtUnlock);
	if (menuIndex == 0) {
		MENU_EXTRA_LIVES->choiceIsAllowed[6] = true;
		MENU_EXTRA_LIVES->choiceIsAllowed[7] = true;
		MENU_EXTRA_LIVES->choiceIsAllowed[8] = true;
	}
	setPreset(MENU_PRESET->index);
	saveGameState_settings();
}

void MenuManager::typeStuff() {
	if (handleCheat(0, contraArrayKey, 10, contraIndex, SFX_SFX2, 1)
		|| handleCheat(1, s3kArrayKey, 9, s3kIndex, SFX_SPEEDINCREASED, 0)
		|| handleCheat(2, dkcArrayKey, 6, dkcIndex, SFX_SBDOOJ_SHORT, 1)
		|| handleCheat(3, pacmanArrayKey, 11, pacmanIndex, SFX_GOLDGET, 1)
		) {
		contraIndex = 0;
		pacmanIndex = 0;
		s3kIndex = 0;
		fzxIndex = 0;
		dkcIndex = 0;
	}
}

void MenuManager::handlePageChange() {
	if (keyPressed(INPUT_LEFT)) {
		page--;
		if (page < 1) page = maxPageNum;
		updateText(&text_3_page, "(" + to_string(page) + "/" + to_string(maxPageNum) + ")");
	} else if (keyPressed(INPUT_RIGHT)) {
		page++;
		if (page > maxPageNum) page = 1;
		updateText(&text_3_page, "(" + to_string(page) + "/" + to_string(maxPageNum) + ")");
	}
}

GameManager::GameManager() {
}

GameManager::GameManager(MenuManager mm) {
	initialized = true;
	forceMusicStart = true;

	if (MM.continueHighlighted) {
		preset = gameState.autosave.difficulty.preset;
		mans = gameState.autosave.mans;
		score = gameState.autosave.score;
		level = gameState.autosave.level;
		treasureHutFound = gameState.autosave.treasureHutFound;
		treasureHutLevel = gameState.autosave.treasureHutLevel;
		shuffleLevels = gameState.autosave.shuffleLevels;
		livesIntervalSetting = gameState.autosave.difficulty.livesInterval;
		peasantPenalty = gameState.autosave.difficulty.peasantPenalty;
		knightSpeedSetting = gameState.autosave.difficulty.knightSpeed;
		arrowSpeedSetting = gameState.autosave.difficulty.arrowSpeed;
		archerFrequencySetting = gameState.autosave.difficulty.archerFreq;
		treasureHutSetting = gameState.autosave.difficulty.treasureHuts;
		infiniteLives = gameState.autosave.cheats.infLives;
		speedyMode = gameState.autosave.cheats.speedyMode;
		noclip = gameState.autosave.cheats.noclip;
		debugMode = gameState.autosave.cheats.debugMode;
		randomSeed = gameState.autosave.randomSeed;
	} else {
		preset = MENU_PRESET->index;
		level = 1;
		infiniteLives = MENU_INF_LIVES->isValue(0);
		if (infiniteLives) {
			mans = 99;
		} else if (preset == 0) {
			switch (MENU_EXTRA_LIVES->index) {
				case 6:
					mans = 10;
					break;
				case 7:
					mans = 20;
					break;
				case 8:
					mans = 30;
					break;
				default:
					mans = MENU_EXTRA_LIVES->index;
					break;
			}
		} else {
			mans = 3;
		}
		speedyMode = MENU_SPEEDY_MODE->index;
		noclip = MENU_NOCLIP->isValue(0);
		debugMode = MENU_DEBUG_MODE->isValue(0);
		switch (preset) {
			case 0:
				level = MENU_STARTING_LEVEL->index * 10 + 1;
				livesIntervalSetting = MENU_LIVES_INTERVAL->index;
				peasantPenalty = MENU_PEASANT_PENALTY->isValue(0);
				knightSpeedSetting = MENU_KNIGHT_SPEED->index;
				arrowSpeedSetting = MENU_ARROW_SPEED->index;
				archerFrequencySetting = MENU_ARCHER_FREQ->index;
				treasureHutSetting = MENU_TREASURE_HUTS->index;
				shuffleLevels = MENU_SHUFFLE_LEVELS->isValue(0);
				break;
			case 1:
				livesIntervalSetting = 0;
				peasantPenalty = true;
				knightSpeedSetting = 2;
				arrowSpeedSetting = 1;
				archerFrequencySetting = 0;
				treasureHutSetting = 0;
				shuffleLevels = false;
				break;
			case 2:
				livesIntervalSetting = 0;
				peasantPenalty = false;
				knightSpeedSetting = 2;
				arrowSpeedSetting = 1;
				archerFrequencySetting = 0;
				treasureHutSetting = 1;
				shuffleLevels = false;
				break;
			case 3:
				livesIntervalSetting = 6;
				peasantPenalty = true;
				knightSpeedSetting = 3;
				arrowSpeedSetting = 3;
				archerFrequencySetting = 4;
				treasureHutSetting = 0;
				shuffleLevels = false;
				break;
			case 4:
				livesIntervalSetting = 7;
				peasantPenalty = true;
				knightSpeedSetting = 4;
				arrowSpeedSetting = 4;
				archerFrequencySetting = 5;
				treasureHutSetting = 0;
				shuffleLevels = false;
				break;
			case 5:
				livesIntervalSetting = 1;
				peasantPenalty = true;
				knightSpeedSetting = 2;
				arrowSpeedSetting = 4;
				archerFrequencySetting = 1;
				treasureHutSetting = 1;
				shuffleLevels = true;
				break;
			case 6:
				livesIntervalSetting = 4;
				peasantPenalty = true;
				knightSpeedSetting = 2;
				arrowSpeedSetting = 1;
				archerFrequencySetting = 0;
				treasureHutSetting = 1;
				shuffleLevels = true;
				break;
			default:
				break;
		}
		score = 0;
		treasureHutFound = false;
		treasureHutLevel = -1;
		randomSeed = SDL_GetTicks();
	}

	srand(randomSeed);
	for (i = 0; i < 33; i++) {
		levelIndices[i] = i;
	}
	if (shuffleLevels) {
		for (i = 32; i > 0; i--) {
			j = rand() % (i + 1);
			k = levelIndices[i];
			levelIndices[i] = levelIndices[j];
			levelIndices[j] = k;
		}
	}
	knightSpeed = (float)(0.7 + (knightSpeedSetting * 0.15));
	updateKnightIncrement();
	switch (arrowSpeedSetting) {
		case 0:
			arrowSpeed = 3;
			break;
		case 2:
			arrowSpeed = 10;
			break;
		case 3:
			arrowSpeed = 15;
			break;
		case 4:
			arrowSpeed = 25;
			break;
		default:
			arrowSpeed = 5;
			break;
	}
	peasantometer = 0;
	paused = false;
	startDown = false;
	manually_paused = 0;
	gameOver = false;
	setBurnination(0);
	archerFrequency = 0;
	burnRate = 0;
	player = Trogdor(IS_BIG_HEAD_MODE, speedyMode);
	player.sprite.facingRight = true;
	switch (MENU_LIVES_INTERVAL->index) {
		case 0:
			extraMansBreak = 300;
			maxExtraMans = 10000;
			break;
		case 1:
			extraMansBreak = 500;
			maxExtraMans = 10000;
			break;
		case 2:
			extraMansBreak = 1000;
			maxExtraMans = 10000;
			break;
		case 3:
			extraMansBreak = 500;
			maxExtraMans = 1;
			break;
		case 4:
			extraMansBreak = 500;
			maxExtraMans = 2;
			break;
		case 5:
			extraMansBreak = 1000;
			maxExtraMans = 1;
			break;
		case 6:
			extraMansBreak = 1000;
			maxExtraMans = 2;
			break;
		default:
			extraMansBreak = 10000;
			maxExtraMans = 0;
			break;
	}
	extraMansCounter = (score / extraMansBreak) + 1;
	arched = false;
	dm_frameState.set(1);
	sprite_dm = SpriteInstance(&sprite_death_message, 0, 0);
	sprite_dm.isActive = false;
	b_frameState.set(1);
	sprite_bt = SpriteInstance(&sprite_burninate_text, 0, 0);
	sprite_bf = SpriteInstance(&sprite_burninate_fire, 0, 0);
	sprite_bf.setPosX((float)OBJ_FRAME_TO_MID_SCREEN_X(gameWidth, sprite_burninate_fire));
	sprite_bf.setPosY((float)sprite_bt.dstrect.y - sprite_bf.spriteObj->dstrect.h + 6); // + 4?
	b_visible = false;
	sprite_bmFull = SpriteInstance(&sprite_burnination_meter_full, 0, 0);
	sprite_pm_on = SpriteInstance(&sprite_peasantometer_icon, 1, 0);
	sprite_pm_off = SpriteInstance(&sprite_peasantometer_icon, 0, 0);
	kick_frameState.set(1);
	numHuts = 0;
	inTreasureHut = false;
	treasureHutIndex = 0;
	store_x = 0;
	store_y = 0;
	treasureHut_timer = 0;
}

void GameManager::resetAllSrcRects() {
	for (i = 0; i < MAX_NUM_HUTS; i++) {
		hutArray[i].sprite.updateCurrSprite();
		hutArray[i].sprite_fire.updateCurrSprite();
	}
	for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
		knightArray[i].sprite.updateCurrSprite();
	}
	for (i = 0; i < MAX_NUM_PEASANTS; i++) {
		peasantArray[i].sprite.updateCurrSprite();
	}
	for (i = 0; i < 2; i++) {
		archerArray[i].sprite.updateCurrSprite();
	}
	for (i = 0; i < MAX_NUM_ARROWS; i++) {
		arrowArrayL[i].sprite.updateCurrSprite();
		arrowArrayR[i].sprite.updateCurrSprite();
	}
	for (i = 0; i < MAX_NUM_LOOT; i++) {
		lootArray[i].sprite.updateCurrSprite();
	}
	player.sprite.updateCurrSprite();
	player.sprite_fire.updateCurrSprite();
	player.sprite_death.updateCurrSprite();
	player.sprite_end_of_level.updateCurrSprite();
	sprite_dm.updateCurrSprite();
	sprite_bt.updateCurrSprite();
	sprite_bf.updateCurrSprite();
	sprite_bmFull.updateCurrSprite();
	sprite_pm_on.updateCurrSprite();
	sprite_pm_off.updateCurrSprite();
}

void GameManager::setArcherFrequency() {
	switch (archerFrequencySetting) {
		case 0:
			if (level > 25) {
				archerFrequency = 400; // 4
			} else if (level > 20) {
				archerFrequency = 200; // 2
			} else if (level > 15) {
				archerFrequency = 80; // 0.8
			} else if (level > 10) {
				archerFrequency = 60; // 0.6
			} else if (level > 5) {
				archerFrequency = 40; // 0.4
			} else {
				archerFrequency = 20; // 0.2
			}
			break;
		case 1: // scale from (level 1 = 20) to (level 31 = 400)
			archerFrequency = (Uint16)ceil((12.6666 * level) + (7.3333));
			break;
		case 2:
			archerFrequency = 40;
			break;
		case 3:
			archerFrequency = 150;
			break;
		case 4:
			archerFrequency = 300;
			break;
		default:
			archerFrequency = 600;
			break;
	}
}

void GameManager::setBurnRate() {
	if (level > 25) {
		burnRate = (float)1.3 * frameRateMult;
	} else if (level > 20) {
		burnRate = (float)1.2 * frameRateMult;
	} else if (level > 15) {
		burnRate = (float)1.1 * frameRateMult;
	} else if (level > 10) {
		burnRate = frameRateMult;
	} else if (level > 5) {
		burnRate = (float)0.9 * frameRateMult;
	} else {
		burnRate = (float)0.7 * frameRateMult;
	}
}

void GameManager::updateKnightIncrement() {
	knightIncrement = knightSpeed * frameRateMult;
	knightIncrement_alt = knightIncrement * float(1.7082); // sqrt(1313/2)*knightIncrement/15 = 1.7082*knightIncrement to match max speed of old movement
	knightIncrement_alt_2 = knightIncrement * float(1.1411); // sqrt(293)*knightIncrement/15 = 1.1411*knightIncrement to match min speed of old movement
}

void GameManager::setMusic() {
	switch (MENU_MUSIC->index) {
		case 1:
			switch (level) {
				case 4:
				case 8:
				case 12:
				case 16:
				case 20:
				case 24:
				case 30:
				case 34:
				case 38:
				case 42:
				case 46:
					playMusic(MUSIC_STINKOMAN_BOSS, true, DEFAULT_VOLUME_MUSIC);
					break;
				default:
					if (level >= 47 && level <= 48) {
						if (level == 46 || forceMusicStart) {
							playMusic(MUSIC_STINKOMAN_MIDPOINT, true, DEFAULT_VOLUME_MUSIC);
						}
					} else if (level >= 49 && level <= 50) {
						if (level == 49 || forceMusicStart) {
							playMusic(MUSIC_STINKOMAN_HOMESTRETCH, true, DEFAULT_VOLUME_MUSIC);
						}
					} else if (level >= 91 && level <= 95) {
						if (level == 91 || forceMusicStart) {
							playMusic(MUSIC_STINKOMAN_LAST_10, true, DEFAULT_VOLUME_MUSIC);
						}
					} else if (level >= 96 && level <= 97) {
						if (level == 96 || forceMusicStart) {
							playMusic(MUSIC_STINKOMAN_HOMESTRETCH, true, DEFAULT_VOLUME_MUSIC);
						}
					} else if (level >= 98 && level <= 100) {
						if (level == 98 || forceMusicStart) {
							playMusic(MUSIC_STINKOMAN_FINAL_BOSS, true, DEFAULT_VOLUME_MUSIC);
						}
					} else {
						switch (levels[levelIndex][0]) {
							case 1:
								playMusic(MUSIC_STINKOMAN_DAY, true, DEFAULT_VOLUME_MUSIC);
								break;
							case 2:
								playMusic(MUSIC_STINKOMAN_EVENING, true, DEFAULT_VOLUME_MUSIC);
								break;
							case 3:
								playMusic(MUSIC_STINKOMAN_NIGHT, true, DEFAULT_VOLUME_MUSIC);
								break;
							case 4:
								playMusic(MUSIC_STINKOMAN_DAWN, true, DEFAULT_VOLUME_MUSIC);
								break;
							default:
								break;
						}
					}
					break;
			}
			break;
		default:
			break;
	}
}

void GameManager::levelInit() {
	srand(randomSeed + level);
	setBurnination(0);
	if (preset == 6) {
		knightSpeed = (float)(0.9 + ((rand() % 25) * 0.025)); // normal range: 0.7~1.3; this is 0.9~1.5
		updateKnightIncrement();
		arrowSpeed = 5 + (rand() % 26); // normal range: 3~25; this is 5~30
		archerFrequency = 20 + ((rand() % 39) * 10); // normal range: 20~400
	} else {
		setArcherFrequency();
	}
	setBurnRate();
	if (level == 1) {
		levelIndex = 0;
	} else {
		levelIndex = ((level - 2) % 32 + 2) - 1;
	}
	levelIndex = levelIndices[levelIndex];
	set_level_background(levels[levelIndex][0]);
	numHuts = 0;
	for (i = 0; i < MAX_NUM_HUTS; i++) {
		j = (i * 3) + 2;
		if (levels[levelIndex][j] > 0) {
			hutArray[i] = Cottage(
				(Sint16)(gameWidth * (((double)levels[levelIndex][j + 1] + 2466) / 5000.0) - 21.5) + 8,
				(Sint16)(gameHeight * (((double)levels[levelIndex][j + 2] + 2183) / 3600.0) - 18.5) - 11,
				levels[levelIndex][j]
			);
			numHuts++;
		} else {
			hutArray[i] = Cottage(0, 0, 0);
			hutArray[i].burned = true;
		}
	}
	for (i = 0; i < MAX_NUM_ARROWS; i++) {
		arrowArrayL[i] = Arrow(0, 0, false);
	}
	for (i = 0; i < MAX_NUM_ARROWS; i++) {
		arrowArrayR[i] = Arrow(0, 0, true);
	}
	for (i = 0; i < MAX_NUM_PEASANTS; i++) {
		peasantArray[i] = Peasant();
	}
	lootArray[0] = Loot((Sint16)(gameWidth * 0.144), (Sint16)(gameHeight * 0.661));
	lootArray[1] = Loot((Sint16)(gameWidth * 0.292), (Sint16)(gameHeight * 0.522));
	lootArray[2] = Loot((Sint16)(gameWidth * 0.284), (Sint16)(gameHeight * 0.806));
	lootArray[3] = Loot((Sint16)(gameWidth * 0.416), (Sint16)(gameHeight * 0.644));
	lootArray[4] = Loot((Sint16)(gameWidth * 0.548), (Sint16)(gameHeight * 0.522));
	lootArray[5] = Loot((Sint16)(gameWidth * 0.548), (Sint16)(gameHeight * 0.783));
	lootArray[6] = Loot((Sint16)(gameWidth * 0.688), (Sint16)(gameHeight * 0.644));
	archerArray[0] = Archer(ARCHER_LEFT_X, 0, true);   // archerR (on the left, facing right)
	archerArray[1] = Archer(ARCHER_RIGHT_X, 0, false); // archerL (on the right, facing left)
	if (MENU_KNIGHT_MOVEMENT->isValue(0)) {
		knightArray[0] = Knight(61, 111, 1, false, knightSpeed);
		knightArray[1] = Knight(163, 40, 1, true, knightSpeed);
	} else {
		knightArray[0] = Knight(61, 111, rand() % 4, false, knightSpeed);
		knightArray[1] = Knight(163, 40, rand() % 4, true, knightSpeed);
	}
	peasantometer = 0;
	player.resetPos(false);
	treasureHutFound = false;
	inTreasureHut = false;
	treasureHutIndex = levels[levelIndex][1];
	setMusic();
	forceMusicStart = false;
}

void GameManager::set_level_background(Sint16 bg_index) {
	switch (bg_index) {
		case 1:
			sprite_level_background = &sprite_level_background_1;
			break;
		case 2:
			sprite_level_background = &sprite_level_background_2;
			break;
		case 3:
			sprite_level_background = &sprite_level_background_3;
			break;
		case 4:
			sprite_level_background = &sprite_level_background_4;
			break;
		case 5:
			sprite_level_background = &sprite_level_background_th;
			break;
		default:
			sprite_level_background = &sprite_level_background_1;
			break;
	}
}

void GameManager::getPlayerInput() {
	player.x_offset = 0;
	player.y_offset = 0;
	player.frameStateFlag = 0;
	if (keyHeld(INPUT_UP)) {
		player.frameStateFlag |= 1;
		player.y_offset = -player.moveSpeed;
	}
	if (keyHeld(INPUT_DOWN)) {
		player.frameStateFlag |= 1;
		player.y_offset = player.moveSpeed;
	}
	if (keyHeld(INPUT_LEFT)) {
		if (!player.sprite.facingRight) {
			player.frameStateFlag |= 1;
		} else {
			player.frameStateFlag |= 2;
			player.sprite.facingRight = false;
		}
		player.x_offset = -player.moveSpeed;
	}
	if (keyHeld(INPUT_RIGHT)) {
		if (player.sprite.facingRight) {
			player.frameStateFlag |= 1;
		} else {
			player.frameStateFlag |= 2;
			player.sprite.facingRight = true;
		}
		player.x_offset = player.moveSpeed;
	}
	if (!inTreasureHut) {
		playerMove(&player, player.x_offset, player.y_offset);
	} else {
		playerMove_treasureHut(&player, player.x_offset, player.y_offset);
	}
	if (keyPressed(INPUT_START)) {
		startDown = true;
	}
	if (startDown && !keyHeld(INPUT_START)) {
		startDown = false;
		manually_paused = frameCounter_global;
		setVolume_music(DEFAULT_VOLUME_MUSIC / 3);
		sdl1_createTransparentScreen();
	}
	if (keyHeld(INPUT_L) && kick_frameState.frame == 1) {
		kick_frameState.set(4);
	}
}

inline void GameManager::trogdor_add_x_delta(Sint8 dx) {
	player.sprite.addPosX(dx);
	player.sprite.collision.x = 11 + player.sprite.dstrect.x;
}

inline void GameManager::trogdor_add_y_delta(Sint8 dy) {
	player.sprite.addPosY(dy);
	player.sprite.collision.y = 11 + player.sprite.dstrect.y;
}

inline void GameManager::handle_treasure_hut_entry(Trogdor *trog, Sint8 delta_x, Sint8 delta_y) {
	// Technically, the original treasure_button collision is different from the hut fire collision used here, but it's both negligible and inconsistent between huts (seems like a bug), so I'm not gonna bother
	if (treasureHutIndex && !treasureHutFound && !hutArray[treasureHutIndex - 1].burned && SDL_HasIntersection(&trog->sprite.dstrect, &hutArray[treasureHutIndex - 1].sprite.collision)
		&& (treasureHutSetting == 1 || (treasureHutSetting == 0 && (treasureHutLevel == -1 || treasureHutLevel == levelIndex)))) {
		inTreasureHut = true;
		treasureHutLevel = levelIndex;
		for (i = 0; i < MAX_NUM_LOOT; i++) {
			lootArray[i].sprite.isActive = true;
		}
		store_x = player.sprite.dstrect.x - delta_x; // The delta is to prevent respawning inside hut after exiting (this probably wouldn't happen, but just in case)
		store_y = player.sprite.dstrect.y - delta_y;
	}
}

void GameManager::handle_treasure_hut() {
	treasureHut_timer -= frameRateMult;
	getPlayerInput();
	testLootHit();
	if (treasureHut_timer <= 0) {
		inTreasureHut = false;
	}
}

void GameManager::playerMove(Trogdor *trog, Sint8 delta_x, Sint8 delta_y) {
	// X movement
	if (delta_x != 0) {
		trogdor_add_x_delta(delta_x);
		handle_treasure_hut_entry(trog, delta_x, delta_y);
		// Collision
		if (trog->sprite.dstrect.x < LEFT_BOUND_TROG || trog->sprite.dstrect.x > RIGHT_BOUND_TROG) {
			trogdor_add_x_delta(-delta_x);
		} else if (!noclip) {
			trog->hutCollisionRect.x = trog->sprite.dstrect.x;
			trog->hutCollisionRect.y = trog->sprite.dstrect.y;
			for (i = 0; i < MAX_NUM_HUTS; i++) {
				if (hutArray[i].direction > 0 && !hutArray[i].burned
					&& (SDL_HasIntersection(&trog->hutCollisionRect, &hutArray[i].sprite.collision))) {
					trogdor_add_x_delta(-delta_x);
					break;
				}
			}
		}
	}
	// Y movement
	if (delta_y != 0) {
		trogdor_add_y_delta(delta_y);
		handle_treasure_hut_entry(trog, delta_x, delta_y);
		// Collision
		if (trog->sprite.dstrect.y < UPPER_BOUND_TROG || trog->sprite.dstrect.y > LOWER_BOUND_TROG) {
			trogdor_add_y_delta(-delta_y);
		} else if (!noclip) {
			trog->hutCollisionRect.x = trog->sprite.dstrect.x;
			trog->hutCollisionRect.y = trog->sprite.dstrect.y;
			for (i = 0; i < MAX_NUM_HUTS; i++) {
				if (hutArray[i].direction > 0 && !hutArray[i].burned
					&& (SDL_HasIntersection(&trog->hutCollisionRect, &hutArray[i].sprite.collision))) {
					trogdor_add_y_delta(-delta_y);
					break;
				}
			}
		}
	}
	// Animate sprite
	if (trog->frameStateFlag & 2) {
		trog->frameState.set(0);
		trog->sprite.setFrame(0);
		trog->sprite.setForm(trog->sprite.facingRight);
	} else if (trog->frameStateFlag & 1) {
		trog->frameState.increment();
		trog->frameState.mod(8);
		trog->sprite.setFrame(trog->frameState.frame / 2);
	}
	if (burnination > 0) {
		trog->updateBreathLoc();
		// Animate sprite
		if (trog->frameStateFlag & 2) {
			trog->fire_frameState.set(0);
			trog->sprite_fire.setFrame(0);
			trog->sprite_fire.setForm(trog->sprite.facingRight);
		} else {
			trog->fire_frameState.increment();
			trog->fire_frameState.mod(12);
			trog->sprite_fire.setFrame(trog->fire_frameState.frame / 3);
		}
	}
}

void GameManager::playerMove_treasureHut(Trogdor *trog, Sint8 delta_x, Sint8 delta_y) {
	// X movement
	if (delta_x != 0) {
		trogdor_add_x_delta(delta_x);
		// Collision
		if (trog->sprite.dstrect.x < LEFT_BOUND_TROG || trog->sprite.dstrect.x > RIGHT_BOUND_TROG) {
			trogdor_add_x_delta(-delta_x);
		}
	}
	// Y movement
	if (delta_y != 0) {
		trogdor_add_y_delta(delta_y);
		// Collision
		if (trog->sprite.dstrect.y < UPPER_BOUND_TROG || trog->sprite.dstrect.y > LOWER_BOUND_TROG) {
			trogdor_add_y_delta(-delta_y);
		}
	}
	// Animate sprite
	if (trog->frameStateFlag & 2) {
		trog->frameState.set(0);
		trog->sprite.setFrame(0);
		trog->sprite.setForm(trog->sprite.facingRight);
	} else if (trog->frameStateFlag & 1) {
		trog->frameState.increment();
		trog->frameState.mod(8);
		trog->sprite.setFrame((trog->frameState.frame / 2));
	}
	if (burnination > 0) {
		trog->updateBreathLoc();
		// Animate sprite
		if (trog->frameStateFlag & 2) {
			trog->fire_frameState.set(0);
			trog->sprite_fire.setFrame(0);
			trog->sprite_fire.setForm(trog->sprite.facingRight);
		} else {
			trog->fire_frameState.increment();
			trog->fire_frameState.mod(12);
			trog->sprite_fire.setFrame(trog->fire_frameState.frame / 3);
		}
	}
}

void GameManager::popArchers() {
	rand_var = rand() % 10000;
	if ((rand_var < archerFrequency) && (rand() % popRandVal < 100)) {
		if (rand_var % 2 == 0) {
			if (!archerR.sprite.isActive) {
				archerR.sprite.isActive = true;
				archerR.sprite.setPosY((float)(rand() % (ARCHER_Y_LOWER - ARCHER_Y_UPPER + 1) + ARCHER_Y_UPPER));
				archerR.frameState.set(5);
			}
		} else {
			if (!archerL.sprite.isActive) {
				archerL.sprite.isActive = true;
				archerL.sprite.setPosY((float)(rand() % (ARCHER_Y_LOWER - ARCHER_Y_UPPER + 1) + ARCHER_Y_UPPER));
				archerL.frameState.set(5);
			}
		}
	}
}

void GameManager::updateArchersAndArrows() {
	if (archerR.sprite.isActive) {
		archerR.updateFrameState();
		if (archerR.frameState.startingFrame(20)) {
			for (i = 0; i < MAX_NUM_ARROWS; i++) {
				if (!arrowArrayR[i].sprite.isActive) {
					arrowArrayR[i].frameState.set(1);
					arrowArrayR[i].sprite.isActive = true;
					arrowArrayR[i].sprite.setPosX((float)archerR.sprite.dstrect.x + (archerR.sprite.spriteObj->dstrect.w / 2) - (arrowArrayR[i].sprite.spriteObj->dstrect.w / 2));
					arrowArrayR[i].sprite.setPosY((float)archerR.sprite.dstrect.y + (archerR.sprite.spriteObj->dstrect.h / 2) - (arrowArrayR[i].sprite.spriteObj->dstrect.h / 2));
					break;
				}
			}
		}
	}
	if (archerL.sprite.isActive) {
		archerL.updateFrameState();
		if (archerL.frameState.startingFrame(20)) {
			for (i = 0; i < MAX_NUM_ARROWS; i++) {
				if (!arrowArrayL[i].sprite.isActive) {
					arrowArrayL[i].frameState.set(1);
					arrowArrayL[i].sprite.isActive = true;
					arrowArrayL[i].sprite.setPosX((float)archerL.sprite.dstrect.x + (archerL.sprite.dstrect.w / 2) - (arrowArrayL[i].sprite.dstrect.w / 2));
					arrowArrayL[i].sprite.setPosY((float)archerL.sprite.dstrect.y + (archerL.sprite.dstrect.h / 2) - (arrowArrayL[i].sprite.dstrect.h / 2));
					break;
				}
			}
		}
	}
	for (i = 0; i < MAX_NUM_ARROWS; i++) {
		if (arrowArrayR[i].sprite.isActive) {
			arrowArrayR[i].updateFrameState(arrowSpeed);
		}
		if (arrowArrayL[i].sprite.isActive) {
			arrowArrayL[i].updateFrameState(arrowSpeed);
		}
	}
}

void GameManager::updateKnightHome() {
	if (MENU_KNIGHT_MOVEMENT->isValue(0)) {
		for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
			knightArray[i].updateHome(knightIncrement);
		}
	}
}

void GameManager::updateKnightOffsetAndMove() {
	if (MENU_KNIGHT_MOVEMENT->isValue(0)) {
		for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
			if (knightArray[i].moving) {
				knightArray[i].updateFrameState();
				knightArray[i].move(knightSpeed);
			}
		}
	} else {
		for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
			if (knightArray[i].moving) {
				knightArray[i].updateFrameState();
				knightArray[i].move_alt(knightIncrement_alt, knightIncrement_alt_2, knightSpeed);
			}
		}
	}
}

void GameManager::testKnightHit() {
	if (player.invince <= 0) {
		for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
			if (SDL_HasIntersection(&player.sprite.dstrect, &knightArray[i].sprite.collision)) {
				paused = true;
				toggleKnightMotion(false);
				clearArrows();
				dm_frameState.set(4); // 29 for arrow
			}
		}
	}
}

void GameManager::arrowHitEventHandler() {
	if (player.invince <= 0) { // (burnination == 0 && !paused) has already been checked
		for (i = 0; i < MAX_NUM_ARROWS; i++) {
			if (arrowArrayL[i].sprite.isActive && SDL_HasIntersection(&player.sprite.collision, &arrowArrayL[i].sprite.collision)) {
				paused = true;
				// the original game does NOT pause knights when you are arrowed
				clearArrows();
				dm_frameState.set(29);
				break;
			}
			if (arrowArrayR[i].sprite.isActive && SDL_HasIntersection(&player.sprite.collision, &arrowArrayR[i].sprite.collision)) {
				paused = true;
				// the original game does NOT pause knights when you are arrowed
				clearArrows();
				dm_frameState.set(29);
				break;
			}
		}
	}
}

inline void GameManager::toggleKnightMotion(bool hasMotion) {
	if (MENU_RESPAWN_BEHAVIOR->isValue(0)) {
		for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
			knightArray[i].moving = hasMotion;
			if (hasMotion) {
				knightArray[i].anim_frameState.set(1);
				knightArray[i].move_frameState.set(1);
			}
		}
	}
}

bool GameManager::testWon() {
	for (i = 0; i < MAX_NUM_HUTS; i++) {
		if (!hutArray[i].burned) {
			return false;
			break;
		}
	}
	return true;
}

void GameManager::updateScore(Uint16 increment) {
	uint_i = score;
	score += increment;
	if ((uint_i < (Uint32)(extraMansBreak * extraMansCounter)) && (score >= (Uint32)(extraMansBreak * extraMansCounter)) && (extraMansCounter <= maxExtraMans)) {
		updateMans(1);
		extraMansCounter++;
	}
	updateText(&text_4_score_val, to_string(score));
}

inline void GameManager::updateMans(Sint8 increment) {
	if (!infiniteLives) {
		mans += increment;
		updateText(&text_4_mans_val, to_string(mans));
	}
}

void GameManager::setMans(Sint8 val) {
	mans = val;
	updateText(&text_4_mans_val, to_string(mans));
}

void GameManager::updateLevel(Sint8 increment) {
	level += increment;
	updateText(&text_4_level_val, to_string(level));
}

void GameManager::clearArrows() {
	for (i = 0; i < MAX_NUM_ARROWS; i++) {
		arrowArrayR[i].clear();
		arrowArrayL[i].clear();
	}
}

void GameManager::testBurnHut() {
	for (i = 0; i < MAX_NUM_HUTS; i++) {
		if (!hutArray[i].burning && SDL_HasIntersection(&player.sprite_fire.dstrect, &hutArray[i].sprite_fire.collision)) {
			hutArray[i].burning = true;
			if ((rand() % 100) < 5 * SB_VOICE_MULT) {
				loadAndPlaySound(SFX_SBDOOJ);
			}
		}
	}
}

void GameManager::updateBurnmeter() {
	setBurnination(burnination - burnRate);
	if (burnination <= 0) {
		setBurnination(0);
		peasantometer = 0;
	}
}

inline void GameManager::peasant_set_x_delta(Sint16 new_x) {
	peasantArray[i].sprite.setPosX(new_x);
	peasantArray[i].sprite.collision.x = 8 + peasantArray[i].sprite.dstrect.x;
}

inline void GameManager::peasant_set_y_delta(Sint16 new_y) {
	peasantArray[i].sprite.setPosY(new_y);
	peasantArray[i].sprite.collision.y = 5 + peasantArray[i].sprite.dstrect.y;
}

inline void GameManager::peasant_add_x_delta(Sint8 dx) {
	peasantArray[i].sprite.addPosX(dx);
	peasantArray[i].sprite.collision.x = 8 + peasantArray[i].sprite.dstrect.x;
}

inline void GameManager::peasant_add_y_delta(Sint8 dy) {
	peasantArray[i].sprite.addPosY(dy);
	peasantArray[i].sprite.collision.y = 5 + peasantArray[i].sprite.dstrect.y;
}

void GameManager::popPeasants() {
	if (((rand() % 100) < 4) && (rand() % popRandVal) < 100) {
		for (i = 0; i < MAX_NUM_PEASANTS; i++) {
			if (!peasantArray[i].sprite.isActive) {
				peasantArray[i].sprite.isActive = true;
				peasantArray[i].frameState.set(1);
				j = rand() % numHuts; // j = hutChoice
				peasantArray[i].myHome = j;
				peasantArray[i].returning = false;
				peasantArray[i].burning = false; // this wasn't in the original game, and caused a bug where a squished burning peasant will, upon respawning, immediately burn its cottage
				peasantArray[i].waiting = false;
				peasantArray[i].stomped = false;
				peasantArray[i].direction = hutArray[j].direction;
				switch (peasantArray[i].direction) {
					case 1: // UP
						peasant_set_x_delta(hutArray[j].sprite.dstrect.x + 9);
						peasant_set_y_delta(hutArray[j].sprite.dstrect.y - 6);
						peasantArray[i].myTargetx = peasantArray[i].sprite.dstrect.x;
						peasantArray[i].myTargety = peasantArray[i].sprite.dstrect.y - ((rand() % (peasantArray[i].sprite.dstrect.y - UPPER_BOUND + 6)) + 6);
						break;
					case 2: // DOWN
						peasant_set_x_delta(hutArray[j].sprite.dstrect.x + 7);
						peasant_set_y_delta(hutArray[j].sprite.dstrect.y + 20);
						peasantArray[i].myTargetx = peasantArray[i].sprite.dstrect.x;
						peasantArray[i].myTargety = peasantArray[i].sprite.dstrect.y + ((rand() % (LOWER_BOUND - peasantArray[i].sprite.dstrect.y - 4)) + 4);
						break;
					case 3: // LEFT
						peasant_set_x_delta(hutArray[j].sprite.dstrect.x + 3);
						peasant_set_y_delta(hutArray[j].sprite.dstrect.y + 18);
						peasantArray[i].myTargetx = peasantArray[i].sprite.dstrect.x - ((rand() % (peasantArray[i].sprite.dstrect.x - LEFT_BOUND - 9)) + 9);
						peasantArray[i].myTargety = peasantArray[i].sprite.dstrect.y;
						break;
					case 4: // RIGHT
						peasant_set_x_delta(hutArray[j].sprite.dstrect.x + 16);
						peasant_set_y_delta(hutArray[j].sprite.dstrect.y + 18);
						peasantArray[i].myTargetx = peasantArray[i].sprite.dstrect.x + ((rand() % (RIGHT_BOUND - peasantArray[i].sprite.dstrect.x + 11)) + 11);
						peasantArray[i].myTargety = peasantArray[i].sprite.dstrect.y;
						break;
					default:
						break;
				}
				peasantArray[i].myStartx = peasantArray[i].sprite.dstrect.x;
				peasantArray[i].myStarty = peasantArray[i].sprite.dstrect.y;
				break;
			}
		}
	}
}

void GameManager::peasantEatTest() {
	for (i = 0; i < MAX_NUM_PEASANTS; i++) {
		if (peasantArray[i].sprite.isActive && !peasantArray[i].stomped && SDL_HasIntersection(&player.sprite.collision, &peasantArray[i].sprite.collision)) {
			peasantArray[i].stomped = true;
			peasantArray[i].frameState.set(8);
			updateScore(2);
			if (peasantometer < 9) {
				peasantometer++;
			} else {
				peasantometer = 10;
				b_frameState.set(4);
			}
		}
	}
}

void GameManager::peasantTimerClick() {
	for (i = 0; i < MAX_NUM_PEASANTS; i++) {
		if (peasantArray[i].sprite.isActive && !peasantArray[i].waiting && !peasantArray[i].stomped) {
			switch (peasantArray[i].direction) {
				case 1: // UP
					j = 0;  // x_offset
					k = -1; // y_offset
					break;
				case 2: // DOWN
					j = 0;
					k = 1;
					break;
				case 3: // LEFT
					j = -1;
					k = 0;
					break;
				case 4: // RIGHT
					j = 1;
					k = 0;
					break;
				default:
					break;
			}
			if (peasantArray[i].burning) {
				j *= 2;
				k *= 2;
				peasantArray[i].returning = true;
				peasantArray[i].waiting = false;
			}
			if (peasantArray[i].returning) {
				if ((j >= 1 && peasantArray[i].sprite.dstrect.x >= peasantArray[i].myStartx)
					|| (j <= -1 && peasantArray[i].sprite.dstrect.x <= peasantArray[i].myStartx)
					|| (k >= 1 && peasantArray[i].sprite.dstrect.y >= peasantArray[i].myStarty)
					|| (k <= -1 && peasantArray[i].sprite.dstrect.y <= peasantArray[i].myStarty)) {
					peasant_add_x_delta(-j);
					peasant_add_y_delta(-k);
				} else {
					peasantArray[i].sprite.isActive = false;
					peasantArray[i].returning = false;
					// if (peasantArray[i].burning && !hutArray[peasantArray[i].myHome].burning) { // redundant check
					if (peasantArray[i].burning) {
						hutArray[peasantArray[i].myHome].burning = true;
						// if (peasantometer > 0 && !peasantArray[i].burning) { // I added the burning check; this looks like an oversight in the original game (though it's very rare that it would actually affect the player)
					} else if (peasantometer > 0 && peasantPenalty) {
						peasantometer--;
					}
					peasantArray[i].burning = false;
					//peasantArray[i].setPosX(-300);
				}
			} else if ((j >= 1 && peasantArray[i].sprite.dstrect.x <= peasantArray[i].myTargetx)
				|| (j <= -1 && peasantArray[i].sprite.dstrect.x >= peasantArray[i].myTargetx)
				|| (k >= 1 && peasantArray[i].sprite.dstrect.y <= peasantArray[i].myTargety)
				|| (k <= -1 && peasantArray[i].sprite.dstrect.y >= peasantArray[i].myTargety)) {
				peasant_add_x_delta(j);
				peasant_add_y_delta(k);
			} else {
				peasantArray[i].waiting = true;
				peasantArray[i].timer = ((float)60 / level) + 24;
			}
		}
		if (peasantArray[i].sprite.isActive && peasantArray[i].waiting) {
			peasantArray[i].timer -= frameRateMult;
			if (peasantArray[i].timer < 0) {
				peasantArray[i].waiting = false;
				peasantArray[i].returning = true;
			}
		}
	}
}

void GameManager::testBurnPeasant() {
	for (i = 0; i < MAX_NUM_PEASANTS; i++) {
		if (!peasantArray[i].burning && !peasantArray[i].stomped && peasantArray[i].sprite.isActive && SDL_HasIntersection(&player.sprite_fire.dstrect, &peasantArray[i].sprite.collision)) {
			loadAndPlaySound(SFX_PEASANTSCREAM);
			if ((rand() % 100) < 40 * SB_VOICE_MULT) {
				if ((rand() % 100) > 50) {
					loadAndPlaySound(SFX_SB6);
				} else {
					loadAndPlaySound(SFX_SB7); // This shows as SB6 in the decompiler, but I know this voice clip isn't unused... I hope the decompiler hasn't been wrong about other things
				}
			}
			peasantArray[i].returning = true;
			peasantArray[i].waiting = false;
			peasantArray[i].timer = false;
			peasantArray[i].burning = true;
			peasantArray[i].frameState.set(26);
		}
	}
}

void GameManager::dm_updateFrameState() { // death message
	if (dm_frameState.atStartOfFrame) {
		switch (dm_frameState.frame) {
			case 4:
				sprite_dm.setFrame(0);
				sprite_dm.setForm(0);
				sprite_dm.isActive = true;
				player.frameState.set(20);
				paused = true;
				arched = false;
				break;
			case 6:
				if (mans > 0) {
					if (peasantometer == 9) {
						if (SB_VOICE_MULT > 0) {
							loadAndPlaySound(SFX_SB3);
						}
					} else if ((rand() % 100) < 20 * SB_VOICE_MULT) {
						loadAndPlaySound(SFX_SBWORST);
					}
				} else {
					fadeMusic(1200);
				}
				sprite_dm.setForm(1);
				break;
			case 27:
			case 52:
				sprite_dm.isActive = false;
				player.frameState.set(1);
				updateMans(-1);
				saveGameState_autosave();
				peasantometer = 0;
				if (mans < 0) {
					setMans(0);
					gameOver = true;
					if (!(infiniteLives || speedyMode || noclip || debugMode)) {
						switch (preset) {
							case 1:
								gameState.highscores.flash = max(score, gameState.highscores.flash);
								break;
							case 2:
								gameState.highscores.html5 = max(score, gameState.highscores.html5);
								break;
							case 3:
								gameState.highscores.hard = max(score, gameState.highscores.hard);
								break;
							case 4:
								gameState.highscores.cruel = max(score, gameState.highscores.cruel);
								break;
							case 5:
								gameState.highscores.mipsChoice = max(score, gameState.highscores.mipsChoice);
								break;
							case 6:
								gameState.addon_v_2_1.chance = max(score, gameState.addon_v_2_1.chance);
								break;
							default:
								gameState.highscores.custom = max(score, gameState.highscores.custom);
								break;
						}
					}
					saveGameState_all();
				} else {
					player.resetPos(true);
					paused = false;
					toggleKnightMotion(true);
				}
				break;
			case 29:
				sprite_dm.setFrame(1);
				sprite_dm.setForm(0);
				sprite_dm.isActive = true;
				player.frameState.set(50);
				paused = true;
				arched = true;
				break;
			case 31:
				if (mans > 0 && (rand() % 100) < 20 * SB_VOICE_MULT) {
					loadAndPlaySound(SFX_SBARCH);
				}
				sprite_dm.setForm(1);
				break;
			default:
				if (dm_frameState.frame < 28) {
					sprite_dm.setForm((((dm_frameState.frame - 4) / 2) % 5));
				} else {
					sprite_dm.setForm((((dm_frameState.frame - 29) / 2) % 5));
				}
				break;
		}
	}
	if (dm_frameState.atEndOfFrame) {
		if (dm_frameState.frame == 27 || dm_frameState.frame == 52) {
			dm_frameState.set(1);
		}
	}
	if (dm_frameState.frame >= 4) {
		dm_frameState.increment();
	}
}

void GameManager::b_updateFrameState() { // burninate message
	// hardcoded is messier, but faster
	if (b_frameState.atStartOfFrame) {
		switch (b_frameState.frame) {
			case 4:
				sprite_bf.setForm(0);
				rand_var = rand() % 100;
				if (rand_var < 10 * SB_VOICE_MULT) {
					if (rand_var < 5) { // the original game used 50 instead of 5, leaving SFX_SB5 unused
						loadAndPlaySound(SFX_SB4);
					} else {
						loadAndPlaySound(SFX_SB5);
					}
				}
				b_visible = true;
				loadAndPlaySound(SFX_BURNINATE);
				//player.visible = true;
				paused = true;
				break;
			case 5:
			case 17:
				sprite_bf.setForm(1);
				break;
			case 6:
				sprite_bf.setForm(2);
				break;
			case 7:
			case 15:
				sprite_bf.setForm(3);
				break;
			case 8:
				sprite_bf.setForm(4);
				break;
			case 9:
			case 13:
				sprite_bf.setForm(5);
				break;
			case 10:
				sprite_bf.setForm(6);
				break;
			case 11:
				sprite_bf.setForm(7);
				break;
			case 12:
				sprite_bf.setForm(8);
				break;
			case 14:
				sprite_bf.setForm(9);
				break;
			case 16:
				sprite_bf.setForm(10);
				break;
			case 18:
				sprite_bf.setForm(11);
				b_visible = false;
				paused = false;
				peasantometer = 10;
				setBurnination(100);
				player.updateBreathLoc();
				break;
			default:
				break;
		}
	}
	if (b_frameState.endingFrame(18)) {
		b_frameState.set(1);
	}
	if (b_frameState.frame >= 4) {
		b_frameState.increment();
	}
}

void GameManager::kick_updateFrameState() {
	switch (kick_frameState.frame) {
		case 4:
			if (kick_frameState.atStartOfFrame) loadAndPlaySound(SFX_KICK);
			kick_frameState.increment();
			break;
		case 9:
			if (kick_frameState.atStartOfFrame) loadAndPlaySound(SFX_TROGADOR);
			kick_frameState.increment();
			break;
		case 29:
			if (kick_frameState.atEndOfFrame) {
				kick_frameState.set(1);
			} else {
				kick_frameState.increment();
			}
			break;
		default:
			kick_frameState.increment();
			break;
	}
}

void GameManager::burninationIncreaseCheat() {
	if (peasantometer < 9) {
		peasantometer++;
	} else {
		peasantometer = 10;
		b_frameState.set(4);
	}
}

void GameManager::burninationDecreaseCheat() {
	if (peasantometer < 10) {
		peasantometer--;
		if (peasantometer < 0) {
			peasantometer = 0;
		}
	} else {
		setBurnination(burnination - 2);
		if (burnination <= 0) {
			setBurnination(0);
			peasantometer = 0;
		}
	}
}

void GameManager::handleDebugCheat() {
#if defined(NINTENDO_LAYOUT)
	if (keyPressed(INPUT_A)) {
		burninationIncreaseCheat();
	}
	if (keyPressed(INPUT_B)) {
		burninationDecreaseCheat();
	}
#else
	if (keyPressed(INPUT_B)) {
		burninationIncreaseCheat();
	}
	if (keyPressed(INPUT_A)) {
		burninationDecreaseCheat();
	}
#endif
	if (keyPressed(INPUT_L) && level > 1) {
		updateLevel(-1);
		forceMusicStart = true;
	}
	if (keyPressed(INPUT_R) && level < 100) {
		updateLevel(1);
		forceMusicStart = true;
	}
}

void GameManager::testLootHit() {
	for (i = 0; i < MAX_NUM_LOOT; i++) {
		if (lootArray[i].sprite.isActive && SDL_HasIntersection(&player.sprite.dstrect, &lootArray[i].sprite.dstrect)) {
			updateScore(50);
			loadAndPlaySound(SFX_GOLDGET);
			lootArray[i].sprite.isActive = false;
		}
	}
}

void GameManager::renderAndAnimateCottages() {
	for (i = 0; i < MAX_NUM_HUTS; i++) {
		if (hutArray[i].direction > 0) {
			if (hutArray[i].burning && !hutArray[i].burned) {
				hutArray[i].updateFrameState();
			}
			hutArray[i].sprite.renderSprite_game();
			if (hutArray[i].frameState.frame >= 12 && hutArray[i].frameState.frame <= 28) {
				hutArray[i].sprite_fire.renderSprite_game();
			}
		}
	}
}

void GameManager::renderArchers() {
	if (archerR.sprite.isActive) {
		archerR.sprite.renderSprite_game();
	}
	if (archerL.sprite.isActive) {
		archerL.sprite.renderSprite_game();
	}
}

void GameManager::renderArrows() {
	for (i = 0; i < MAX_NUM_ARROWS; i++) {
		if (arrowArrayR[i].sprite.isActive) {
			arrowArrayR[i].sprite.renderSprite_game();
		}
		if (arrowArrayL[i].sprite.isActive) {
			arrowArrayL[i].sprite.renderSprite_game();
		}
	}
}

void GameManager::renderLoot() {
	for (i = 0; i < MAX_NUM_LOOT; i++) {
		if (lootArray[i].sprite.isActive) {
			lootArray[i].sprite.renderSprite_game();
		}
	}
}

void GameManager::renderKnights() {
	for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
		knightArray[i].sprite.renderSprite_game();
	}
}

void GameManager::renderPeasants() {
	for (i = 0; i < MAX_NUM_PEASANTS; i++) {
		if (peasantArray[i].sprite.isActive) {
			if (!manually_paused && (!peasantArray[i].waiting || peasantArray[i].stomped)) {
				peasantArray[i].updateFrameState();
			}
			peasantArray[i].sprite.renderSprite_game();
		}
	}
}

void GameManager::renderTrogdor() {
	if (player.sprite.isActive) {
		if (player.frameState.frame >= 19) {
			player.sprite_death.renderSprite_game();
		} else {
			player.sprite.renderSprite_game();
		}
	}
}

void GameManager::setBurnination(float num) {
	burnination = num;
	sprite_bmFull.srcrect.w = (int)(sprite_burnination_meter_empty_ins.srcrect.w * burnination / 100.0);
	sprite_bmFull.dstrect.w = (int)(sprite_burnination_meter_empty_ins.dstrect.w * burnination / 100.0);
}

void GameManager::renderTopBar() {
	renderText(text_4_score, font_serif_2_red_6);
	renderText(text_4_score_val, font_serif_red_6);
	renderText(text_4_mans, font_serif_2_red_6);
	renderText(text_4_mans_val, font_serif_red_6);
	renderText(text_4_level, font_serif_2_red_6);
	renderText(text_4_level_val, font_serif_red_6);
	// Render peasantometer/burnination meter (depending on their values)
	if (burnination > 0) {
		sprite_burnination_meter_empty_ins.renderSprite_game();
		sprite_bmFull.renderSprite_game();
	} else {
		sprite_pm_on.dstrect.x = sprite_peasantometer_icon_init_x;
		sprite_pm_off.dstrect.x = sprite_peasantometer_icon_init_x;
		for (i = 0; i < 10; i++) {
			if (i < peasantometer) {
				sprite_pm_on.renderSprite_game();
				sprite_pm_on.dstrect.x += sprite_peasantometer_icon_step;
			} else {
				sprite_pm_off.renderSprite_game();
			}
			sprite_pm_off.dstrect.x += sprite_peasantometer_icon_step;
		}
	}
}

void GameManager::saveGameState_autosave() {
	gameState.autosave.mans = mans;
	gameState.autosave.score = score;
	gameState.autosave.level = level;
	gameState.autosave.treasureHutFound = treasureHutFound;
	gameState.autosave.treasureHutLevel = treasureHutLevel;
	gameState.autosave.randomSeed = randomSeed;
	gameState.autosave.difficulty = { preset, MENU_EXTRA_LIVES->index, livesIntervalSetting, peasantPenalty, knightSpeedSetting, arrowSpeedSetting, archerFrequencySetting, treasureHutSetting };
	gameState.autosave.shuffleLevels = shuffleLevels;
	gameState.autosave.cheats = { infiniteLives, speedyMode, noclip, debugMode };
	saveGameState_all();
}