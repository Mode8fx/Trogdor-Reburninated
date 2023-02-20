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
constexpr auto ARCHER_Y_UPPER = 20; //   30 - (20 / 2)
constexpr auto ARCHER_Y_LOWER = 145; //  155 - (20 / 2)
constexpr auto ARCHER_LEFT_X = -1; //  179 / 5000 * 250 - (20 / 2)
constexpr auto ARCHER_RIGHT_X = 231; // 4829 / 5000 * 250 - (20 / 2)

#if defined(SDL1)
inline bool SDL_HasIntersection(const SDL_Rect *A, const SDL_Rect *B) {
	return (!((A->x + A->w < B->x) || (B->x + B->w < A->x) || (A->y + A->h < B->y) || (B->y + B->h < A->y)));
}
#endif

Cottage::Cottage(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint16 dir = 1) {
	SET_FRAMESTATE(10);
	sprite = SpriteInstance(&sprite_cottage, 0, (dir - 1), pos_x, pos_y);
	sprite_fire = SpriteInstance(&sprite_cottage_fire, 0, 0, (double)sprite.dstrect.x + 5, (double)sprite.dstrect.y - 5);
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
	if (frameState == 10) {
		loadAndPlaySound(SFX_BURN_HUT);
	}
	if (frameState >= 12 && frameState <= 28) {
		sprite_fire.setFrame(((frameState - 12) / 3) % 4);
		sprite_fire.setForm(direction == 3);
		if (frameState == 26) {
			sprite.setFrame(1);
		}
	}
	if (frameState == 30) {
		burned = true;
	}
	INCREMENT_FRAMESTATE();
}

Knight::Knight(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 1, bool fr = true) {
	SET_FRAMESTATE(1);
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
}

inline void Knight::updateCollision() {
	if (sprite.facingRight) {
		sprite.collision = { 4 + sprite.dstrect.x, 9 + sprite.dstrect.y, 9, 13 };
	} else {
		sprite.collision = { 8 + sprite.dstrect.x, 9 + sprite.dstrect.y, 9, 13 };
	}
}

void Knight::updateHome(double knightIncrement) {
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

void Knight::updateFrameStateAndMove() {
	if (frameState > 60) { // a while loop isn't necessary; it'll never go that far above 60
		frameState_double -= 60;
		frameState -= 60;
	}
	switch (frameState) {
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
	if (frameState_double <= 30) {
		offset_x = frameState_double * 34 / 30;
	} else {
		offset_x = 68.0 - (frameState_double * 34 / 30);
	}
	offset_y = -offset_x;
	if (!sprite.facingRight) {
		offset_x *= -1;
	}

	sprite.setPosX(home_x + offset_x - half_src_w);
	sprite.setPosY(home_y + offset_y - half_src_h);
	updateCollision();
	INCREMENT_FRAMESTATE();
}

Peasant::Peasant() {
	SET_FRAMESTATE(1);
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

void Peasant::updateFrameState(double sbVoiceMult) {
	switch (frameState) {
		case 1:
			sprite.setFrame(0);
			sprite.setForm(0);
			INCREMENT_FRAMESTATE();
			break;
		case 4:
			sprite.setFrame(1);
			INCREMENT_FRAMESTATE();
			break;
		case 6:
			SET_FRAMESTATE(1);
			break;
		case 8:
			sprite.setFrame(0);
			sprite.setForm(3);
			loadAndPlaySound(SFX_SQUISH);
			rand_var = rand() % 1000;
			if (rand_var < 3 * sbVoiceMult) {
				loadAndPlaySound(SFX_SB2);
			} else if (rand_var < 6 * sbVoiceMult) {
				loadAndPlaySound(SFX_SBSQUISH1);
			} else if (rand_var < 10 * sbVoiceMult) {
				loadAndPlaySound(SFX_SBSQUISH2);
			}
			INCREMENT_FRAMESTATE();
			break;
		case 25:
			sprite.isActive = false;
			stomped = false;
			sprite.setPosX(-300);
			INCREMENT_FRAMESTATE();
			break;
		case 26:
			sprite.setFrame(0);
			sprite.setForm(1);
			INCREMENT_FRAMESTATE();
			break;
		case 27:
			sprite.setFrame(1);
			SET_FRAMESTATE(26);
			break;
		default:
			INCREMENT_FRAMESTATE();
			break;
	}
}

Archer::Archer(Sint16 pos_x = 0, Sint16 pos_y = 0, bool fr = true) {
	SET_FRAMESTATE(1);
	sprite = SpriteInstance(&sprite_archer, 0, fr, pos_x, pos_y);
	sprite.facingRight = fr;
	sprite.isActive = false;
}

void Archer::updateFrameState() {
	switch (frameState) {
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
	INCREMENT_FRAMESTATE();
}

Arrow::Arrow(Sint16 pos_x = 0, Sint16 pos_y = 0, bool fr = true) {
	SET_FRAMESTATE(1);
	sprite = SpriteInstance(&sprite_arrow, 0, fr, pos_x, pos_y);
	sprite.facingRight = fr;
	sprite.isActive = false;
	sprite.collision = { 1 + sprite.facingRight + sprite.dstrect.x, 1 + sprite.dstrect.y, 12, 3 };
}

void Arrow::updateFrameState() {
	if (frameState == 1) { // 4?
		loadAndPlaySound(SFX_ARROW);
	}
	if (sprite.facingRight) {
		sprite.addPosX(5);
		if (sprite.dstrect.x > gameWidth) { // not exactly the same as the original, but close enough
			clear();
		}
		sprite.collision.x = 2 + sprite.dstrect.x;
		sprite.collision.y = 1 + sprite.dstrect.y;

	} else {
		sprite.addPosX(-5);
		if (sprite.dstrect.x < -8) { // not exactly the same as the original, but close enough
			clear();
		}
		sprite.collision.x = 1 + sprite.dstrect.x;
		sprite.collision.y = 1 + sprite.dstrect.y;
	}
	INCREMENT_FRAMESTATE();
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

Trogdor::Trogdor(bool bigHead = false) {
	SET_FRAMESTATE(1);
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
	spawnPos_x = (2780.0 / 5000 * gameWidth) - (sprite.spriteObj->dstrect.w / 2);
	spawnPos_y = (2360.0 / 3600 * gameHeight) - (sprite.spriteObj->dstrect.h / 2);
	sprite.setPosX(spawnPos_x);
	sprite.setPosY(spawnPos_y);
	sprite.collision = { 11 + sprite.dstrect.x, 11 + sprite.dstrect.y, 18, 24 };
	SET_FRAMESTATE_SPECIAL(fire_frameState, fire_frameState_double, 1);
	sprite_fire = SpriteInstance(&sprite_trogdor_fire, 0, sprite.facingRight, (double)sprite.dstrect.x - 24 + ((double)sprite.facingRight * 62), (double)sprite.dstrect.y + 10);
	invince = 0;
	sprite.isActive = true;
	x_offset = 0;
	y_offset = 0;
	moveSpeed = 3;
	frameStateFlag = 0;
}

void Trogdor::updateFrameState() {
	switch (frameState) {
		case 20: // sworded
			sprite_death.setFrame(0);
			sprite_death.setPosX(sprite.dstrect.x + ((sprite.spriteObj->dstrect.w - sprite_death.spriteObj->dstrect.w) / 2));
			sprite_death.setPosY(sprite.dstrect.y + (sprite.spriteObj->dstrect.h - sprite_death.spriteObj->dstrect.h) - 7);
			INCREMENT_FRAMESTATE();
			break;
		case 50: // arrowed
			sprite_death.setFrame(1);
			sprite_death.setPosX(sprite.dstrect.x + ((sprite.spriteObj->dstrect.w - sprite_death.spriteObj->dstrect.w) / 2));
			sprite_death.setPosY(sprite.dstrect.y + (sprite.spriteObj->dstrect.h - sprite_death.spriteObj->dstrect.h) - 7);
			INCREMENT_FRAMESTATE();
			break;
		case 22:
		case 52:
			loadAndPlaySound(SFX_DEATH);
			INCREMENT_FRAMESTATE();
			break;
		case 34:
		case 38:
		case 42:
		case 64:
		case 68:
		case 72:
			sprite.isActive = false;
			INCREMENT_FRAMESTATE();
			break;
		case 36:
		case 40:
		case 66:
		case 70:
			sprite.isActive = true;
			INCREMENT_FRAMESTATE();
			break;
		case 48:
		case 78:
			sprite.isActive = true;
			SET_FRAMESTATE(1);
			break;
		default:
			INCREMENT_FRAMESTATE();
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
		sprite_fire.setPosX((double)sprite.dstrect.x + 38);
		sprite_fire.setPosY((double)sprite.dstrect.y + 10);
	} else {
		sprite_fire.setPosX((double)sprite.dstrect.x - 24);
		sprite_fire.setPosY((double)sprite.dstrect.y + 10);
	}
}

void Trogdor::invinceCheck() {
	if (invince > 0) {
		invince -= FRAME_RATE_MULT;
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
}

bool MenuManager::handleCheat(Uint8 menuIndex, const Uint8 *cheatArrayKey, Uint8 cheatLen, Sint8 &cheatIndex, SoundEffect *sfx) {
	if (menu_cheats.options[menuIndex]->optionIsLocked) {
		if (keyInputs != 0) {
			if (keyInputs == (1 << (cheatArrayKey[cheatIndex]))) {
				cheatIndex++;
				if ((Uint32)cheatIndex == cheatLen) {
					menu_cheats.options[menuIndex]->setLocked(false);
					menu_cheats.setOptionChoice(menuIndex, 0);
					if (menuIndex == 0) {
						MENU_EXTRA_LIVES->choiceIsAllowed[6] = true;
						MENU_EXTRA_LIVES->choiceIsAllowed[7] = true;
						MENU_EXTRA_LIVES->choiceIsAllowed[8] = true;
					}
					// this was originally played upon starting the game, but I'm changing it; it's much clearer this way, especially since the controls are different for each system
					loadAndPlaySound(sfx);
					saveGameState();
					return true;
				}
			} else {
				cheatIndex = 0;
			}
		}
	}
	return false;
}

void MenuManager::typeStuff() {
	if (handleCheat(0, contraArrayKey, 10, contraIndex, SFX_SFX2)
		|| handleCheat(1, pacmanArrayKey, 11, pacmanIndex, SFX_GOLDGET)
		|| handleCheat(2, s3kArrayKey, 9, s3kIndex, SFX_HUSKYHEAD)
		//|| handleCheat(3, fzxArrayKey, 8, fzxIndex, SFX_SBKERREK)
		|| handleCheat(3, dkcArrayKey, 6, dkcIndex, SFX_SBDOOJ)
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
	srand(SDL_GetTicks());
	initialized = true;
	forceMusicStart = true;
	infiniteLives = CHEAT_INF_LIVES->isValue(0);
	if (infiniteLives) {
		mans = 99;
	} else {
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
	}
	score = 0;
	peasantometer = 0;
	paused = false;
	startDown = false;
	manually_paused = 0;
	gameOver = false;
	//if (mm.fzxActive) level = 81;
	//else level = 1;
	level = MENU_STARTING_LEVEL->index * 10 + 1;
	//levelIndex = 1; // set via levelInit()
	setBurnination(0);
	archerFrequency = 0;
	burnRate = 0;
	bigHeadMode = CHEAT_BIG_HEAD_MODE->isValue(0);
	player = Trogdor(bigHeadMode);
	player.sprite.facingRight = true;
	knightIncrement = FRAME_RATE_MULT;
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
	extraMansCounter = 1;
	arched = false;
	SET_FRAMESTATE_SPECIAL(dm_frameState, dm_frameState_double, 1);
	sprite_dm = SpriteInstance(&sprite_death_message, 0, 0);
	sprite_dm.isActive = false;
	SET_FRAMESTATE_SPECIAL(b_frameState, b_frameState_double, 1);
	sprite_bt = SpriteInstance(&sprite_burninate_text, 0, 0);
	sprite_bf = SpriteInstance(&sprite_burninate_fire, 0, 0);
	sprite_bf.setPosX(OBJ_FRAME_TO_MID_SCREEN_X(gameWidth, sprite_burninate_fire));
	sprite_bf.setPosY((double)sprite_bt.dstrect.y - sprite_bf.spriteObj->dstrect.h + 6); // + 4?
	b_visible = false;
	sprite_bmFull = SpriteInstance(&sprite_burnination_meter_full, 0, 0);
	sprite_pm_on = SpriteInstance(&sprite_peasantometer_icon, 1, 0);
	sprite_pm_off = SpriteInstance(&sprite_peasantometer_icon, 0, 0);
	SET_FRAMESTATE_SPECIAL(kick_frameState, kick_frameState_double, 1);
	numHuts = 0;
	treasureHutFound = false;
	inTreasureHut = false;
	treasureHutIndex = 0;
	treasureHutLevel = -1;
	store_x = 0;
	store_y = 0;
	treasureHut_timer = 0;
	switch (MENU_COMMENT_FREQ->index) {
		case 0:
			sbVoiceMult = 0;
			break;
		case 1:
			sbVoiceMult = 0.3333;
			break;
		case 2:
			sbVoiceMult = 0.6666;
			break;
		case 3:
			sbVoiceMult = 1;
			break;
		case 4:
			sbVoiceMult = 1.3333;
			break;
		case 5:
			sbVoiceMult = 1.6666;
			break;
		default:
			sbVoiceMult = 2;
			break;
	}
	debugMode = CHEAT_DEBUG_MODE->isValue(0);
	noclip = CHEAT_NOCLIP->isValue(0);
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
	switch (MENU_ARCHER_FREQ->index) {
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
		burnRate = 1.3 * FRAME_RATE_MULT;
	} else if (level > 20) {
		burnRate = 1.2 * FRAME_RATE_MULT;
	} else if (level > 15) {
		burnRate = 1.1 * FRAME_RATE_MULT;
	} else if (level > 10) {
		burnRate = 1 * FRAME_RATE_MULT;
	} else if (level > 5) {
		burnRate = 0.9 * FRAME_RATE_MULT;
	} else {
		burnRate = 0.7 * FRAME_RATE_MULT;
	}
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
	setBurnination(0);
	setArcherFrequency();
	setBurnRate();
	if (level == 1) {
		levelIndex = 0;
	} else {
		levelIndex = ((level - 2) % 32 + 2) - 1;
	}
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
	knightArray[0] = Knight(61, 111, 1, false);
	knightArray[1] = Knight(163, 40, 1, true);
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
	if (keyHeld(INPUT_L) && kick_frameState == 1) {
		SET_FRAMESTATE_SPECIAL(kick_frameState, kick_frameState_double, 4);
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
		&& (MENU_TREASURE_HUTS->index == 0 || (MENU_TREASURE_HUTS->index == 1 && (treasureHutLevel == -1 || treasureHutLevel == levelIndex)))) {
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
	treasureHut_timer--;
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
			for (i = 0; i < MAX_NUM_HUTS; i++) {
				if (hutArray[i].direction > 0 && !hutArray[i].burned
					&& SDL_HasIntersection(&trog->sprite.dstrect, &hutArray[i].sprite.collision)) { // &trog->sprite->dstrect, NOT &trog->collision
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
			for (i = 0; i < MAX_NUM_HUTS; i++) {
				if (hutArray[i].direction > 0 && !hutArray[i].burned
					&& SDL_HasIntersection(&trog->sprite.dstrect, &hutArray[i].sprite.collision)) { // &trog->sprite->dstrect, NOT &trog->collision
					trogdor_add_y_delta(-delta_y);
					break;
				}
			}
		}
	}
	// Animate sprite
	if (trog->frameStateFlag & 2) {
		SET_FRAMESTATE_SPECIAL(trog->frameState, trog->frameState_double, 0);
		trog->sprite.setFrame(0);
		trog->sprite.setForm(trog->sprite.facingRight);
	} else if (trog->frameStateFlag & 1) {
		INCREMENT_FRAMESTATE_SPECIAL(trog->frameState, trog->frameState_double);
		if (trog->frameState_double >= 8) {
			trog->frameState_double -= 8;
			trog->frameState -= 8;
		}
		trog->sprite.setFrame(trog->frameState / 2);
	}
	if (burnination > 0) {
		trog->updateBreathLoc();
		// Animate sprite
		if (trog->frameStateFlag & 2) {
			SET_FRAMESTATE_SPECIAL(trog->fire_frameState, trog->fire_frameState_double, 0);
			trog->sprite_fire.setFrame(0);
			trog->sprite_fire.setForm(trog->sprite.facingRight);
		} else {
			INCREMENT_FRAMESTATE_SPECIAL(trog->fire_frameState, trog->fire_frameState_double);
			if (trog->fire_frameState_double >= 12) {
				trog->fire_frameState_double -= 12;
				trog->fire_frameState -= 12;
			}
			trog->sprite_fire.setFrame(trog->fire_frameState / 3);
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
		SET_FRAMESTATE_SPECIAL(trog->frameState, trog->frameState_double, 0);
		trog->sprite.setFrame(0);
		trog->sprite.setForm(trog->sprite.facingRight);
	} else if (trog->frameStateFlag & 1) {
		INCREMENT_FRAMESTATE_SPECIAL(trog->frameState, trog->frameState_double);
		if (trog->frameState_double >= 8) {
			trog->frameState_double -= 8;
			trog->frameState -= 8;
		}
		trog->sprite.setFrame((trog->frameState / 2));
	}
	if (burnination > 0) {
		trog->updateBreathLoc();
		// Animate sprite
		if (trog->frameStateFlag & 2) {
			SET_FRAMESTATE_SPECIAL(trog->fire_frameState, trog->fire_frameState_double, 0);
			trog->sprite_fire.setFrame(0);
			trog->sprite_fire.setForm(trog->sprite.facingRight);
		} else {
			INCREMENT_FRAMESTATE_SPECIAL(trog->fire_frameState, trog->fire_frameState_double);
			if (trog->fire_frameState_double >= 12) {
				trog->fire_frameState_double -= 12;
				trog->fire_frameState -= 12;
			}
			trog->sprite_fire.setFrame(trog->fire_frameState / 3);
		}
	}
}

void GameManager::popArchers() {
	rand_var = rand() % 10000;
	if (rand_var < archerFrequency) {
		rand_var = rand() % ARCHER_RAND_VAL; // account for variable framerate
		if (rand_var < 100) {
			if (rand_var % 2 == 0) {
				if (!archerR.sprite.isActive) {
					archerR.sprite.isActive = true;
					archerR.sprite.setPosY(rand() % (ARCHER_Y_LOWER - ARCHER_Y_UPPER + 1) + ARCHER_Y_UPPER);
					SET_FRAMESTATE_FOR_OBJ(archerR, 5);
				}
			} else {
				if (!archerL.sprite.isActive) {
					archerL.sprite.isActive = true;
					archerL.sprite.setPosY(rand() % (ARCHER_Y_LOWER - ARCHER_Y_UPPER + 1) + ARCHER_Y_UPPER);
					SET_FRAMESTATE_FOR_OBJ(archerL, 5);
				}
			}
		}
	}
}

void GameManager::updateArchersAndArrows() {
	if (archerR.sprite.isActive) {
		archerR.updateFrameState();
		if (archerR.frameState == 20) {
			for (i = 0; i < MAX_NUM_ARROWS; i++) {
				if (!arrowArrayR[i].sprite.isActive) {
					SET_FRAMESTATE_FOR_OBJ(arrowArrayR[i], 1);
					arrowArrayR[i].sprite.isActive = true;
					arrowArrayR[i].sprite.setPosX((double)archerR.sprite.dstrect.x + (archerR.sprite.spriteObj->dstrect.w / 2) - (arrowArrayR[i].sprite.spriteObj->dstrect.w / 2));
					arrowArrayR[i].sprite.setPosY((double)archerR.sprite.dstrect.y + (archerR.sprite.spriteObj->dstrect.h / 2) - (arrowArrayR[i].sprite.spriteObj->dstrect.h / 2));
					break;
				}
			}
		}
	}
	if (archerL.sprite.isActive) {
		archerL.updateFrameState();
		if (archerL.frameState == 20) {
			for (i = 0; i < MAX_NUM_ARROWS; i++) {
				if (!arrowArrayL[i].sprite.isActive) {
					SET_FRAMESTATE_FOR_OBJ(arrowArrayL[i], 1);
					arrowArrayL[i].sprite.isActive = true;
					arrowArrayL[i].sprite.setPosX((double)archerL.sprite.dstrect.x + (archerL.sprite.dstrect.w / 2) - (arrowArrayL[i].sprite.dstrect.w / 2));
					arrowArrayL[i].sprite.setPosY((double)archerL.sprite.dstrect.y + (archerL.sprite.dstrect.h / 2) - (arrowArrayL[i].sprite.dstrect.h / 2));
					break;
				}
			}
		}
	}
	for (i = 0; i < MAX_NUM_ARROWS; i++) {
		if (arrowArrayR[i].sprite.isActive) {
			arrowArrayR[i].updateFrameState();
		}
		if (arrowArrayL[i].sprite.isActive) {
			arrowArrayL[i].updateFrameState();
		}
	}
}

void GameManager::updateKnightHome() {
	for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
		knightArray[i].updateHome(knightIncrement);
	}
}

void GameManager::updateKnightOffsetAndMove() {
	for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
		if (knightArray[i].moving) {
			knightArray[i].updateFrameStateAndMove();
		}
	}
}

void GameManager::testKnightHit() {
	if (!player.invince) {
		for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
			if (SDL_HasIntersection(&player.sprite.dstrect, &knightArray[i].sprite.collision)) {
				paused = true;
				toggleKnightMotion(false);
				clearArrows();
				SET_FRAMESTATE_SPECIAL(dm_frameState, dm_frameState_double, 4); // 29 for arrow
			}
		}
	}
}

void GameManager::arrowHitEventHandler() {
	if (!player.invince) { // (burnination == 0 && !paused) has already been checked
		for (i = 0; i < MAX_NUM_ARROWS; i++) {
			if (arrowArrayL[i].sprite.isActive && SDL_HasIntersection(&player.sprite.collision, &arrowArrayL[i].sprite.collision)) {
				paused = true;
				// the original game does NOT pause knights when you are arrowed
				clearArrows();
				SET_FRAMESTATE_SPECIAL(dm_frameState, dm_frameState_double, 29);
				break;
			}
			if (arrowArrayR[i].sprite.isActive && SDL_HasIntersection(&player.sprite.collision, &arrowArrayR[i].sprite.collision)) {
				paused = true;
				// the original game does NOT pause knights when you are arrowed
				clearArrows();
				SET_FRAMESTATE_SPECIAL(dm_frameState, dm_frameState_double, 29);
				break;
			}
		}
	}
}

inline void GameManager::toggleKnightMotion(bool hasMotion) {
	if (MENU_KNIGHT_BEHAVIOR->isValue(0)) {
		for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
			knightArray[i].moving = hasMotion;
			if (hasMotion) {
				SET_FRAMESTATE_FOR_OBJ(knightArray[i], 1);
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
			if ((rand() % 100) < 5 * sbVoiceMult) {
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
	if ((rand() % 100) < 4) {
		for (i = 0; i < MAX_NUM_PEASANTS; i++) {
			if (!peasantArray[i].sprite.isActive) {
				peasantArray[i].sprite.isActive = true;
				SET_FRAMESTATE_FOR_OBJ(peasantArray[i], 1);
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
			SET_FRAMESTATE_FOR_OBJ(peasantArray[i], 8);
			updateScore(2);
			if (peasantometer < 9) {
				peasantometer++;
			} else {
				peasantometer = 10;
				SET_FRAMESTATE_SPECIAL(b_frameState, b_frameState_double, 4);
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
					} else if (peasantometer > 0 && MENU_PEASANT_PENALTY->isValue(0)) {
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
				peasantArray[i].timer = (60 / level) + 24;
			}
		}
		if (peasantArray[i].sprite.isActive && peasantArray[i].waiting) {
			peasantArray[i].timer--;
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
			if ((rand() % 100) < 40 * sbVoiceMult) {
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
			SET_FRAMESTATE_FOR_OBJ(peasantArray[i], 26);
		}
	}
}

void GameManager::dm_updateFrameState() { // death message
	switch (dm_frameState) {
		case 4:
			sprite_dm.setFrame(0);
			sprite_dm.setForm(0);
			sprite_dm.isActive = true;
			SET_FRAMESTATE_FOR_OBJ(player, 20);
			paused = true;
			arched = false;
			break;
		case 6:
			if (mans > 0) {
				if (peasantometer == 9) {
					if (sbVoiceMult > 0) {
						loadAndPlaySound(SFX_SB3);
					}
				} else if ((rand() % 100) < 20 * sbVoiceMult) {
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
			SET_FRAMESTATE_FOR_OBJ(player, 1);
			updateMans(-1);
			peasantometer = 0;
			if (mans < 0) {
				setMans(0);
				gameOver = true;
			} else {
				player.resetPos(true);
				paused = false;
				toggleKnightMotion(true);
			}
			SET_FRAMESTATE_SPECIAL(dm_frameState, dm_frameState_double, 1);
			break;
		case 29:
			sprite_dm.setFrame(1);
			sprite_dm.setForm(0);
			sprite_dm.isActive = true;
			SET_FRAMESTATE_FOR_OBJ(player, 50);
			paused = true;
			arched = true;
			break;
		case 31:
			if (mans > 0 && (rand() % 100) < 20 * sbVoiceMult) {
				loadAndPlaySound(SFX_SBARCH);
			}
			sprite_dm.setForm(1);
			break;
		default:
			if (dm_frameState < 28) {
				sprite_dm.setForm((((dm_frameState - 4) / 2) % 5));
			} else {
				sprite_dm.setForm((((dm_frameState - 29) / 2) % 5));
			}
			break;
	}
	if (dm_frameState >= 4) {
		INCREMENT_FRAMESTATE_SPECIAL(dm_frameState, dm_frameState_double);
	}
}

void GameManager::b_updateFrameState() { // burninate message
	// hardcoded is messier, but faster
	switch (b_frameState) {
		case 4:
			sprite_bf.setForm(0);
			rand_var = rand() % 100;
			if (rand_var < 10 * sbVoiceMult) {
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
			SET_FRAMESTATE_SPECIAL(b_frameState, b_frameState_double, 1);
			break;
		default:
			break;
	}
	if (b_frameState >= 4) {
		INCREMENT_FRAMESTATE_SPECIAL(b_frameState, b_frameState_double);
	}
}

void GameManager::kick_updateFrameState() {
	switch (kick_frameState) {
		case 4:
			loadAndPlaySound(SFX_KICK);
			INCREMENT_FRAMESTATE_SPECIAL(kick_frameState, kick_frameState_double);
			break;
		case 9:
			loadAndPlaySound(SFX_TROGADOR);
			INCREMENT_FRAMESTATE_SPECIAL(kick_frameState, kick_frameState_double);
			break;
		case 29:
			SET_FRAMESTATE_SPECIAL(kick_frameState, kick_frameState_double, 1);
			break;
		default:
			INCREMENT_FRAMESTATE_SPECIAL(kick_frameState, kick_frameState_double);
			break;
	}
}

void GameManager::burninationIncreaseCheat() {
	if (peasantometer < 9) {
		peasantometer++;
	} else {
		peasantometer = 10;
		SET_FRAMESTATE_SPECIAL(b_frameState, b_frameState_double, 4);
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
#if defined(WII_U) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(THREEDS)
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
			if (hutArray[i].frameState >= 12 && hutArray[i].frameState <= 28) {
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
				peasantArray[i].updateFrameState(sbVoiceMult);
			}
			peasantArray[i].sprite.renderSprite_game();
		}
	}
}

void GameManager::renderTrogdor() {
	if (player.sprite.isActive) {
		if (player.frameState >= 19) {
			player.sprite_death.renderSprite_game();
		} else {
			player.sprite.renderSprite_game();
		}
	}
}

void GameManager::setBurnination(double num) {
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