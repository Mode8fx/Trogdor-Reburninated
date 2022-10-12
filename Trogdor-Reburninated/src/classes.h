#ifndef CLASSES_H
#define CLASSES_H

#include "config.h"
#include "input.h"
#include "level_data.h"

// for all "directions": 1 = up, 2 = down, 3 = left, 4 = right

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

extern Uint32 frameCounter_global;
extern Uint8 contraArrayKey[10];
extern Uint8 pacmanArrayKey[11];
extern Uint8 s3kArrayKey[9];
extern Uint8 fzxArrayKey[8];

#if defined(SDL1)
inline bool SDL_HasIntersection(const SDL_Rect *A, const SDL_Rect *B) {
	return (!((A->x + A->w < B->x) || (B->x + B->w < A->x) || (A->y + A->h < B->y) || (B->y + B->h < A->y)));
}
#endif

constexpr auto MAX_NUM_HUTS = 6;
constexpr auto MAX_NUM_ARROWS = 5;
#define archerR archerArray[0]
#define archerL archerArray[1]
constexpr auto MAX_NUM_KNIGHTS = 2;
constexpr auto MAX_NUM_PEASANTS = 7;
constexpr auto MAX_NUM_LOOT = 7;

class Cottage {
	public:
		Uint8 frameState;
		SpriteInstance sprite;
		SpriteInstance sprite_fire;
		bool burning;
		bool burned;
		Sint16 direction;
		Cottage(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint16 dir = 1) {
			frameState = 9;
			sprite = SpriteInstance(&sprite_cottage, 0, (dir - 1));
			sprite.dstrect = { pos_x, pos_y, (Uint16)sprite_cottage.frame_w, (Uint16)sprite_cottage.frame_h };
			sprite_fire = SpriteInstance(&sprite_cottage_fire, 0, 0);
			sprite_fire.dstrect = { sprite.dstrect.x + 5, sprite.dstrect.y - 5, (Uint16)sprite_cottage_fire.frame_w, (Uint16)sprite_cottage_fire.frame_h };
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
		void updateFrameState() {
			frameState++;
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
		}
};

class Knight {
	public:
		Uint8 frameState;
		bool moving;      // used in toggleKnightMotion()
		SpriteInstance sprite;
		Sint16 half_src_w;
		Sint16 half_src_h;
		Sint8 direction;
		Sint16 home_x;    // the parent (x,y) coordinates
		Sint16 home_y;    // the parent (x,y) coordinates
		Sint16 offset_x;  // the offset relative to home
		Sint16 offset_y;  // the offset relative to home
		Knight(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 1, bool fr = true) {
			frameState = 0;
			moving = true;
			sprite = SpriteInstance(&sprite_knight, 0, fr);
			sprite.facingRight = fr;
			home_x = pos_x;
			home_y = pos_y;
			half_src_w = sprite_knight.frame_w / 2;
			half_src_h = sprite_knight.frame_h / 2 + 4;
			sprite.dstrect = { home_x, home_y, (Uint16)sprite_knight.frame_w, (Uint16)sprite_knight.frame_h };
			offset_x = 0;
			offset_y = 0;
			direction = dir;
			updateCollision();
		}
		inline void updateCollision() {
			if (sprite.facingRight) {
				sprite.collision = { 4 + sprite.dstrect.x, 9 + sprite.dstrect.y, 9, 13 };
			} else {
				sprite.collision = { 8 + sprite.dstrect.x, 9 + sprite.dstrect.y, 9, 13 };
			}
		}
		void updateHome(Sint8 knightIncrement) {
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
		void updateFrameStateAndMove() {
			frameState++;
			if (frameState > 60) { // a while loop isn't necessary; it'll never go that far above 60
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
			if (frameState <= 30) {
				offset_x = frameState * 34 / 30;
			} else {
				offset_x = 68 - (frameState * 34 / 30);
			}
			offset_y = -offset_x;
			if (!sprite.facingRight) {
				offset_x *= -1;
			}

			sprite.dstrect.x = home_x + offset_x - half_src_w;
			sprite.dstrect.y = home_y + offset_y - half_src_h;
			updateCollision();
		}
};

class Peasant {
	public:
		Uint8 frameState;
		SpriteInstance sprite;
		Sint8 myHome;
		bool stomped;
		bool waiting;
		bool burning;
		Sint16 myStartx;
		Sint16 myStarty;
		Sint16 direction;
		Sint16 myTargetx;
		Sint16 myTargety;
		bool returning;
		Sint16 timer;
		Peasant() {
			frameState = 0;
			sprite = SpriteInstance(&sprite_peasant, 0, 0);
			sprite.dstrect = { 0, 0, (Uint16)sprite_peasant.frame_w, (Uint16)sprite_peasant.frame_h };
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
		void updateFrameState(Uint8 sbVoiceMult) {
			frameState++;
			switch (frameState) {
				case 1:
					sprite.setFrame(0);
					sprite.setForm(0);
					break;
				case 4:
					sprite.setFrame(1);
					break;
				case 6:
					frameState = 0;
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
					break;
				case 25:
					sprite.isActive = false;
					stomped = false;
					sprite.dstrect.x = -300;
					break;
				case 26:
					sprite.setFrame(0);
					sprite.setForm(1);
					break;
				case 27:
					sprite.setFrame(1);
					frameState = 25;
					break;
				default:
					break;
			}
		}
};

class Archer {
	public:
		Uint8 frameState;
		SpriteInstance sprite; // facing right == on the left; facing left == on the right
		Archer(Sint16 pos_x = 0, Sint16 pos_y = 0, bool fr = true) {
			frameState = 0;
			sprite = SpriteInstance(&sprite_archer, 0, fr);
			sprite.facingRight = fr;
			sprite.dstrect = { pos_x, pos_y, (Uint16)sprite_archer.frame_w, (Uint16)sprite_archer.frame_h };
			sprite.isActive = false;
		}
		void updateFrameState() {
			frameState++;
			switch (frameState) {
				case 14:
					sprite.setFrame(1);
					break;
				case 20:
					sprite.setFrame(0);
					// shoot arrow; this is handled by GameManager
					break;
				case 23:
					sprite.dstrect.y = -300;
					sprite.isActive = false;
				default:
					break;
			}
		}
};

class Arrow {
	public:
		Uint8 frameState;
		SpriteInstance sprite;
		Arrow(Sint16 pos_x = 0, Sint16 pos_y = 0, bool fr = true) {
			frameState = 0;
			sprite = SpriteInstance(&sprite_arrow, 0, fr);
			sprite.facingRight = fr;
			sprite.dstrect = { pos_x, pos_y, (Uint16)sprite_arrow.frame_w, (Uint16)sprite_arrow.frame_h };
			sprite.isActive = false;
			sprite.collision = { 1 + sprite.facingRight + sprite.dstrect.x, 1 + sprite.dstrect.y, 12, 3 };
		}
		void updateFrameState() {
			frameState++;
			if (frameState == 1) { // 4?
				loadAndPlaySound(SFX_ARROW);
			}
			if (sprite.facingRight) {
				sprite.dstrect.x += 5;
				if (sprite.dstrect.x > gameWidth) { // not exactly the same as the original, but close enough
					clear();
				}
				sprite.collision.x = 2 + sprite.dstrect.x;
				sprite.collision.y = 1 + sprite.dstrect.y;

			} else {
				sprite.dstrect.x -= 5;
				if (sprite.dstrect.x < -8) { // not exactly the same as the original, but close enough
					clear();
				}
				sprite.collision.x = 1 + sprite.dstrect.x;
				sprite.collision.y = 1 + sprite.dstrect.y;
			}
		}
		void clear() {
			sprite.isActive = false;
			sprite.dstrect.x = -500;
		}
};

class Loot {
	public:
		SpriteInstance sprite;
		Loot() {
			Loot(0, 0);
		}
		Loot(Sint16 x_pos, Sint16 y_pos) {
			sprite = SpriteInstance(&sprite_loot, 0, 0);
			sprite.dstrect = { x_pos, y_pos, (Uint16)sprite_loot.frame_w, (Uint16)sprite_loot.frame_h };
			sprite.isActive = false;
		}
};

class Trogdor {
	public:
		Uint8 frameState;
		SpriteInstance sprite;
		Uint8 fire_frameState;
		SpriteInstance sprite_fire;
		SpriteInstance sprite_death;
		Sint16 spawnPos_x;
		Sint16 spawnPos_y;
		Sint8 invince;        // remaining invincibility time (after respawn)
		Sint8 x_offset;       // used for movement
		Sint8 y_offset;       // used for movement
		Sint8 moveSpeed;      // used for movement
		Uint8 frameStateFlag; // used for movement
		Trogdor() {
			frameState = 0;
			sprite = SpriteInstance(&sprite_trogdor, 0, 1);
			sprite.facingRight = true;
			spawnPos_x = (Sint16)(2780.0 / 5000 * gameWidth) - (sprite_trogdor.frame_w / 2);
			spawnPos_y = (Sint16)(2360.0 / 3600 * gameHeight) - (sprite_trogdor.frame_h / 2);
			sprite.dstrect = { spawnPos_x, spawnPos_y, (Uint16)sprite_trogdor.frame_w, (Uint16)sprite_trogdor.frame_h };
			sprite.collision = { 11 + sprite.dstrect.x, 11 + sprite.dstrect.y, 18, 24 };
			fire_frameState = 0;
			sprite_fire = SpriteInstance(&sprite_trogdor_fire, 0, sprite.facingRight);
			sprite_fire.dstrect = { sprite.dstrect.x - 24 + (sprite.facingRight * 62), sprite.dstrect.y + 10, (Uint16)sprite_trogdor_fire.frame_w, (Uint16)sprite_trogdor_fire.frame_h };
			sprite_death = SpriteInstance(&sprite_trogdor_dead, 0, 0);
			sprite_death.dstrect = { sprite.dstrect.x + ((sprite.dstrect.w + sprite_trogdor_dead.frame_w) / 2), sprite.dstrect.y + (sprite.dstrect.h - sprite_trogdor_dead.frame_h), (Uint16)sprite_trogdor_dead.frame_w, (Uint16)sprite_trogdor_dead.frame_h };
			invince = 0;
			sprite.isActive = true;
			x_offset = 0;
			y_offset = 0;
			moveSpeed = 3;
			frameStateFlag = 0;
		}
		void updateFrameState() {
			frameState++;
			switch (frameState) {
				case 20: // sworded
					sprite_death.setFrame(0);
					sprite_death.dstrect.x = sprite.dstrect.x + ((sprite.dstrect.w - sprite_trogdor_dead.frame_w) / 2);
					sprite_death.dstrect.y = sprite.dstrect.y + (sprite.dstrect.h - sprite_trogdor_dead.frame_h);
					break;
				case 50: // arrowed
					sprite_death.setFrame(1);
					sprite_death.dstrect.x = sprite.dstrect.x + ((sprite.dstrect.w - sprite_trogdor_dead.frame_w) / 2);
					sprite_death.dstrect.y = sprite.dstrect.y + (sprite.dstrect.h - sprite_trogdor_dead.frame_h);
					break;
				case 22:
				case 52:
					loadAndPlaySound(SFX_DEATH);
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
					frameState = 0;
					break;
			}
		}
		void resetPos(bool giveInvince) {
			sprite.facingRight = true;
			sprite.setFrameAndForm(0, sprite.facingRight);
			sprite.dstrect = { spawnPos_x, spawnPos_y, (Uint16)sprite_trogdor.frame_w, (Uint16)sprite_trogdor.frame_h };
			sprite.collision = { 11 + sprite.dstrect.x, 11 + sprite.dstrect.y, 18, 24 };
			if (giveInvince) {
				invince = 36;
			}
		}
		void updateBreathLoc() {
			sprite_fire.dstrect.x = sprite.dstrect.x - 24 + (sprite.facingRight * 62);
			sprite_fire.dstrect.y = sprite.dstrect.y + 10;
		}
		void invinceCheck() {
			if (invince >= 1) {
				invince--;
				if (invince % 3 == 0) {
					sprite.isActive = false;
				} else {
					sprite.isActive = true;
				}
				if (invince == 0) {
					sprite.isActive = true;
				}
			}
		}
};

#define HANDLE_CHEAT(cheatIsActive, cheatArrayKey, cheatIndex, sfx) \
	if (!cheatIsActive) {                                           \
		if (keyInputs != 0) {                                       \
			if (keyInputs == (1 << (cheatArrayKey[cheatIndex]))) {  \
				cheatIndex++;                                       \
				if (cheatIndex == LEN(cheatArrayKey)) {             \
					loadAndPlaySound(sfx); /* this was originally played upon starting the game, but I'm changing it; it's much clearer this way, especially since the controls are different for each system */ \
					cheatIsActive = true;                           \
				}                                                   \
			} else {                                                \
				cheatIndex = 0;                                     \
			}                                                       \
		}                                                           \
	}

class MenuManager {
	public:
		bool contraActive; // 30 Lives cheat is enabled
		Sint8 contraIndex; // the current index of the 30 Lives cheat input
		bool pacmanActive; // Debug Mode cheat is enabled
		Sint8 pacmanIndex; // the current index of the Debug Mode cheat input
		bool s3kActive;    // Talkative Strong Bad cheat is enabled
		Sint8 s3kIndex;    // the current index of the Talkative Strong Bad cheat
		bool fzxActive;    // Quiet Strong Bad cheat is enabled
		Sint8 fzxIndex;    // the current index of the Quiet Strong Bad input
		Sint8 page;        // the current page number
		Sint8 maxPageNum;  // maxPageNum
		MenuManager() {
			contraActive = false;
			contraIndex = 0;
			pacmanActive = false;
			pacmanIndex = 0;
			s3kActive = false;
			s3kIndex = 0;
			fzxActive = false;
			fzxIndex = 0;
			page = 1;
			if (gameHiResMult < 2) {
				maxPageNum = 5;
			} else {
				maxPageNum = 4;
			}
		}
		void typeStuff() {
			HANDLE_CHEAT(contraActive, contraArrayKey, contraIndex, SFX_SFX2);
			HANDLE_CHEAT(pacmanActive, pacmanArrayKey, pacmanIndex, SFX_GOLDGET);
			HANDLE_CHEAT(s3kActive, s3kArrayKey, s3kIndex, SFX_SBBEST);
			HANDLE_CHEAT(fzxActive, fzxArrayKey, fzxIndex, SFX_SHUTUP);
		}
		void handlePageChange() {
			if (keyPressed(INPUT_LEFT)) {
				page--;
				if (page < 1) page = maxPageNum;
				updateText(&text_3_page, "("+to_string(page)+"/"+to_string(maxPageNum)+")");
			} else if (keyPressed(INPUT_RIGHT)) {
				page++;
				if (page > maxPageNum) page = 1;
				updateText(&text_3_page, "("+to_string(page)+"/"+to_string(maxPageNum)+")");
			}
		}
};

class GameManager {
	public:
		Sint16 mans;                            // lives
		Uint32 score;                           // score
		Sint8 peasantometer;                    // # of peasants burned for burnination meter
		bool paused;                            // game is paused through any means (clearing a level, dying, etc.)
		bool startDown;                         // bool used for pausing
		bool manually_paused;                   // game is paused by the player
		bool gameOver;                          // game is over
		Uint8 level;                            // current level
		Uint8 levelIndex;                       // current level index (determined by level)
		double burnination;                     // amount of time left in burnination state
		double archerFrequency;                 // frequency at which archers appear
		double burnRate;                        // rate at which the burnination meter decreases
		Arrow arrowArrayL[MAX_NUM_ARROWS];      // array of Arrow objects (facing left, firing from right to left)
		Arrow arrowArrayR[MAX_NUM_ARROWS];      // array of Arrow objects (facing right, firing from left to right)
		Cottage hutArray[MAX_NUM_HUTS];         // array of Cottage objects
		Uint8 numHuts;                          // the number of huts
		Peasant peasantArray[MAX_NUM_PEASANTS]; // array of Peasant objects
		Knight knightArray[MAX_NUM_KNIGHTS];    // array of Knight objects
		Archer archerArray[2];                  // array of Archer objects
		Trogdor player;                         // the player
		Sint8 knightIncrement;                  // knight movement speed
		Uint16 extraMansBreak;                  // # of points for an extra life
		Uint16 extraMansCounter;                // how many extra lives have been earned so far
		bool arched;                            // previous death was to arrow
		SpriteInstance sprite_dm;               // Death Message ("SWORDED!", "ARROWED!")
		Uint8 dm_frameState;                    // Death Message ("SWORDED!", "ARROWED!")
		Uint8 b_frameState;                     // BURNINATE! Message
		SpriteInstance sprite_bf;               // BURNINATE! Message Fire
		bool b_visible;                         // BURNINATE! Message
		SpriteInstance sprite_bmFull;           // burnination meter
		SpriteInstance sprite_pm_on;            // peasantometer (on)
		SpriteInstance sprite_pm_off;           // peasantometer (off)
		Uint8 kick_frameState;                  // kick the machine
		bool treasureHutFound;                  // treasure hut has been found in this level
		bool inTreasureHut;                     // player is currently in treasure hut
		Sint16 treasureHutIndex;                // index of hut that contains treasure (0 = no treasure hut)
		Sint16 storex;                          // old player X position (used for treasure huts)
		Sint16 storey;                          // old player Y position (used for treasure huts)
		Sint16 treasureHut_timer;               // remaining time in treasure hut
		Loot lootArray[MAX_NUM_LOOT];           // array of Loot objects
		Uint8 sbVoiceMult;                      // a multiplier for how often Strong Bad talks
		GameManager() {
		}
		GameManager(MenuManager mm) {
			srand(SDL_GetTicks());
			if (mm.contraActive) mans = 30;
			else mans = 3;
			score = 0;
			peasantometer = 0;
			paused = false;
			startDown = false;
			manually_paused = 0;
			gameOver = false;
			level = 1;
			levelIndex = 1;
			setBurnination(0);
			archerFrequency = 0;
			burnRate = 0;
			player = Trogdor();
			player.sprite.facingRight = true;
			knightIncrement = 1;
			extraMansBreak = 300;
			extraMansCounter = 1;
			arched = false;
			dm_frameState = 0;
			sprite_dm = SpriteInstance(&sprite_death_message, 0, 0);
			sprite_dm.isActive = false;
			b_frameState = 0;
			sprite_bf = SpriteInstance(&sprite_burninate_fire, 0, 0);
			sprite_bf.dstrect = { OBJ_FRAME_TO_MID_SCREEN_X(gameWidth, sprite_burninate_fire), sprite_burninate_text.dstrect.y - sprite_burninate_fire.frame_h + 4, (Uint16)sprite_burninate_fire.frame_w, (Uint16)sprite_burninate_fire.frame_h };
			b_visible = false;
			sprite_bmFull = SpriteInstance(&sprite_burnination_meter_full, 0, 0);
			sprite_pm_on = SpriteInstance(&sprite_peasantometer_icon, 1, 0);
			sprite_pm_off = SpriteInstance(&sprite_peasantometer_icon, 0, 0);
			kick_frameState = 0;
			numHuts = 0;
			treasureHutFound = false;
			inTreasureHut = false;
			treasureHutIndex = 0;
			storex = 0;
			storey = 0;
			treasureHut_timer = 0;
			if (mm.fzxActive) sbVoiceMult = 0;
			else if (mm.s3kActive) sbVoiceMult = 2;
			else sbVoiceMult = 1;
		}
		void resetAllSrcRects() {
			for (i = 0; i < MAX_NUM_HUTS; i++) {
				hutArray[i].sprite.updateCurrSprite();
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
			sprite_dm.updateCurrSprite();
			sprite_bf.updateCurrSprite();
			sprite_bmFull.updateCurrSprite();
			sprite_pm_on.updateCurrSprite();
			sprite_pm_off.updateCurrSprite();
		}
		void levelInit() {
			setBurnination(0);
			if (level > 25) {
				archerFrequency = 400; // 4
				burnRate = 1.3;
			} else if (level > 20) {
				archerFrequency = 200; // 2
				burnRate = 1.2;
			} else if (level > 15) {
				archerFrequency = 80; // 0.8
				burnRate = 1.1;
			} else if (level > 10) {
				archerFrequency = 60; // 0.6
				burnRate = 1;
			} else if (level > 5) {
				archerFrequency = 40; // 0.4
				burnRate = 0.9;
			} else {
				archerFrequency = 20; // 0.2
				burnRate = 0.7;
			}
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
		}
		void set_level_background(Sint16 bg_index) {
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
		void getPlayerInput() {
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
				if (keyPressed(INPUT_START)) {
					startDown = true;
				}
				if (startDown && !keyHeld(INPUT_START)) {
					startDown = false;
					manually_paused = frameCounter_global;
#if (defined(WII) || defined(GAMECUBE))
					transparentScreen = SDL_CreateRGBSurface(0, gameHiResWidth, gameHiResHeight, 24, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
					SDL_FillRect(transparentScreen, NULL, 0x000000C8);
#elif defined(SDL1) && (SDL_BYTEORDER == SDL_BIG_ENDIAN)
					transparentScreen = SDL_CreateRGBSurface(0, gameHiResWidth, gameHiResHeight, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
					SDL_FillRect(transparentScreen, NULL, 0x000000C8);
#elif defined(SDL1)
					transparentScreen = SDL_CreateRGBSurface(0, gameHiResWidth, gameHiResHeight, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
					SDL_FillRect(transparentScreen, NULL, 0xC8000000);
#endif
				}
			} else {
				playerMove_treasureHut(&player, player.x_offset, player.y_offset);
			}
			if (keyHeld(INPUT_L) && kick_frameState == 0) {
				kick_frameState = 3;
			}
		}
		inline void trogdor_add_x_delta(Sint8 dx) {
			player.sprite.dstrect.x += dx;
			player.sprite.collision.x = 11 + player.sprite.dstrect.x;
		}
		inline void trogdor_add_y_delta(Sint8 dy) {
			player.sprite.dstrect.y += dy;
			player.sprite.collision.y = 11 + player.sprite.dstrect.y;
		}
		inline void handle_treasure_hut_entry(Trogdor *trog, Sint8 delta_x, Sint8 delta_y) {
			// Technically, the original treasure_button collision is different from the hut fire collision used here, but it's both negligible and inconsistent between huts (seems like a bug), so I'm not gonna bother
			if (treasureHutIndex && !treasureHutFound && !hutArray[treasureHutIndex - 1].burned && SDL_HasIntersection(&trog->sprite.dstrect, &hutArray[treasureHutIndex - 1].sprite.collision)) {
				inTreasureHut = true;
				for (i = 0; i < MAX_NUM_LOOT; i++) {
					lootArray[i].sprite.isActive = true;
				}
				storex = player.sprite.dstrect.x - delta_x; // The delta is to prevent respawning inside hut after exitting (this probably wouldn't happen, but just in case)
				storey = player.sprite.dstrect.y - delta_y;
			}
		}
		void handle_treasure_hut() {
			treasureHut_timer--;
			getPlayerInput();
			testLootHit();
			if (treasureHut_timer <= 0) {
				inTreasureHut = false;
			}
		}
		// This has to be part of GM and not Trogdor since it references GM (and GameManager references Trogdor, so it would be circular)
		void playerMove(Trogdor *trog, Sint8 delta_x, Sint8 delta_y) {
			// X movement
			if (delta_x != 0) {
				trogdor_add_x_delta(delta_x);
				handle_treasure_hut_entry(trog, delta_x, delta_y);
				// Collision
				if (trog->sprite.dstrect.x < LEFT_BOUND_TROG || trog->sprite.dstrect.x > RIGHT_BOUND_TROG) {
					trogdor_add_x_delta(-delta_x);
				}
				for (i = 0; i < MAX_NUM_HUTS; i++) {
					if (hutArray[i].direction > 0 && !hutArray[i].burned
						&& SDL_HasIntersection(&trog->sprite.dstrect, &hutArray[i].sprite.collision)) { // &trog->sprite->dstrect, NOT &trog->collision
						trogdor_add_x_delta(-delta_x);
						break;
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
				}
				for (i = 0; i < MAX_NUM_HUTS; i++) {
					if (hutArray[i].direction > 0 && !hutArray[i].burned
						&& SDL_HasIntersection(&trog->sprite.dstrect, &hutArray[i].sprite.collision)) { // &trog->sprite->dstrect, NOT &trog->collision
						trogdor_add_y_delta(-delta_y);
						break;
					}
				}
			}
			// Animate sprite
			if (trog->frameStateFlag & 2) {
				trog->frameState = 0;
				trog->sprite.setFrame(0);
				trog->sprite.setForm(trog->sprite.facingRight);
			} else if (trog->frameStateFlag & 1) {
				trog->frameState = (++trog->frameState % 8);
				trog->sprite.setFrame(trog->frameState / 2);
			}
			if (burnination > 0) {
				trog->updateBreathLoc();
				// Animate sprite
				if (trog->frameStateFlag & 2) {
					trog->fire_frameState = 0;
					trog->sprite_fire.setFrame(0);
					trog->sprite_fire.setForm(trog->sprite.facingRight);
				} else {
					trog->fire_frameState = (++trog->fire_frameState % 12);
					trog->sprite_fire.setFrame(trog->fire_frameState / 3);
				}
			}
		}
		void playerMove_treasureHut(Trogdor* trog, Sint8 delta_x, Sint8 delta_y) {
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
				trog->frameState = 0;
				trog->sprite.setFrame(0);
				trog->sprite.setForm(trog->sprite.facingRight);
			} else if (trog->frameStateFlag & 1) {
				trog->frameState = (++trog->frameState % 8);
				trog->sprite.setFrame((trog->frameState / 2));
			}
			if (burnination > 0) {
				trog->updateBreathLoc();
				// Animate sprite
				if (trog->frameStateFlag & 2) {
					trog->fire_frameState = 0;
					trog->sprite_fire.setFrame(0);
					trog->sprite_fire.setForm(trog->sprite.facingRight);
				} else {
					trog->fire_frameState = (++trog->fire_frameState % 12);
					trog->sprite_fire.setFrame(trog->fire_frameState / 3);
				}
			}
		}
		void popArchers() {
			rand_var = rand() % 10000;
			if (rand_var < archerFrequency) {
				if (rand_var % 2 == 0) {
					if (!archerR.sprite.isActive) {
						archerR.sprite.isActive = true;
						archerR.sprite.dstrect.y = rand() % (ARCHER_Y_LOWER - ARCHER_Y_UPPER + 1) + ARCHER_Y_UPPER;
						archerR.frameState = 4;
					}
				} else {
					if (!archerL.sprite.isActive) {
						archerL.sprite.isActive = true;
						archerL.sprite.dstrect.y = rand() % (ARCHER_Y_LOWER - ARCHER_Y_UPPER + 1) + ARCHER_Y_UPPER;
						archerL.frameState = 4;
					}
				}
			}
		}
		void updateArchersAndArrows() {
			if (archerR.sprite.isActive) {
				archerR.updateFrameState();
				if (archerR.frameState == 20) {
					for (i = 0; i < MAX_NUM_ARROWS; i++) {
						if (!arrowArrayR[i].sprite.isActive) {
							arrowArrayR[i].frameState = 0;
							arrowArrayR[i].sprite.isActive = true;
							arrowArrayR[i].sprite.dstrect.x = archerR.sprite.dstrect.x + (archerR.sprite.dstrect.w / 2) - (arrowArrayR[i].sprite.dstrect.w / 2);
							arrowArrayR[i].sprite.dstrect.y = archerR.sprite.dstrect.y + (archerR.sprite.dstrect.h / 2) - (arrowArrayR[i].sprite.dstrect.h / 2);
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
							arrowArrayL[i].frameState = 0;
							arrowArrayL[i].sprite.isActive = true;
							arrowArrayL[i].sprite.dstrect.x = archerL.sprite.dstrect.x + (archerL.sprite.dstrect.w / 2) - (arrowArrayL[i].sprite.dstrect.w / 2);
							arrowArrayL[i].sprite.dstrect.y = archerL.sprite.dstrect.y + (archerL.sprite.dstrect.h / 2) - (arrowArrayL[i].sprite.dstrect.h / 2);
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
		void updateKnightHome() {
			for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
				knightArray[i].updateHome(knightIncrement);
			}
		}
		void updateKnightOffsetAndMove() {
			for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
				if (knightArray[i].moving) {
					knightArray[i].updateFrameStateAndMove();
				}
			}
		}
		void testKnightHit() {
			if (!player.invince) {
				for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
					if (SDL_HasIntersection(&player.sprite.dstrect, &knightArray[i].sprite.collision)) {
						paused = true;
						toggleKnightMotion(false);
						clearArrows();
						dm_frameState = 3; // 28 for arrow
					}
				}
			}
		}
		void arrowHitEventHandler() {
			if (!player.invince) { // (burnination == 0 && !paused) has already been checked
				for (i = 0; i < MAX_NUM_ARROWS; i++) {
					if (arrowArrayL[i].sprite.isActive && SDL_HasIntersection(&player.sprite.collision, &arrowArrayL[i].sprite.collision)) {
						paused = true;
						// the original game does NOT pause knights when you are arrowed
						clearArrows();
						dm_frameState = 28;
						break;
					}
					if (arrowArrayR[i].sprite.isActive && SDL_HasIntersection(&player.sprite.collision, &arrowArrayR[i].sprite.collision)) {
						paused = true;
						// the original game does NOT pause knights when you are arrowed
						clearArrows();
						dm_frameState = 28;
						break;
					}
				}
			}
		}
		inline void toggleKnightMotion(bool hasMotion) {
			for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
				knightArray[i].moving = hasMotion;
				if (hasMotion) {
					knightArray[i].frameState = 0;
				}
			}
		}
		inline bool testWon() {
			for (i = 0; i < MAX_NUM_HUTS; i++) {
				if (!hutArray[i].burned) {
					return false;
					break;
				}
			}
			return true;
		}
		inline void updateScore(Uint16 increment) {
			uint_i = score;
			score += increment;
			if ((uint_i < (Uint32)(extraMansBreak * extraMansCounter)) && (score >= (Uint32)(extraMansBreak * extraMansCounter))) {
				updateMans(1);
				extraMansCounter++;
			}
			updateText(&text_4_score_val, to_string(score));
		}
		inline void updateMans(Sint8 increment) {
			mans += increment;
			updateText(&text_4_mans_val, to_string(mans));
		}
		inline void setMans(Sint8 val) {
			mans = val;
			updateText(&text_4_mans_val, to_string(mans));
		}
		inline void updateLevel(Sint8 increment) {
			level += increment;
			updateText(&text_4_level_val, to_string(level));
		}
		void clearArrows() {
			for (i = 0; i < MAX_NUM_ARROWS; i++) {
				arrowArrayR[i].clear();
				arrowArrayL[i].clear();
			}
		}
		void testBurnHut() {
			for (i = 0; i < MAX_NUM_HUTS; i++) {
				if (!hutArray[i].burning && SDL_HasIntersection(&player.sprite_fire.dstrect, &hutArray[i].sprite_fire.collision)) {
					hutArray[i].burning = true;
					if ((rand() % 100) < 5 * sbVoiceMult) {
						loadAndPlaySound(SFX_SBDOOJ);
					}
				}
			}
		}
		inline void updateBurnmeter() {
			setBurnination(burnination - burnRate);
			if (burnination <= 0) {
				setBurnination(0);
				peasantometer = 0;
			}
		}
		inline void peasant_set_x_delta(Sint16 new_x) {
			peasantArray[i].sprite.dstrect.x = new_x;
			peasantArray[i].sprite.collision.x = 8 + peasantArray[i].sprite.dstrect.x;
		}
		inline void peasant_set_y_delta(Sint16 new_y) {
			peasantArray[i].sprite.dstrect.y = new_y;
			peasantArray[i].sprite.collision.y = 5 + peasantArray[i].sprite.dstrect.y;
		}
		inline void peasant_add_x_delta(Sint8 dx) {
			peasantArray[i].sprite.dstrect.x += dx;
			peasantArray[i].sprite.collision.x = 8 + peasantArray[i].sprite.dstrect.x;
		}
		inline void peasant_add_y_delta(Sint8 dy) {
			peasantArray[i].sprite.dstrect.y += dy;
			peasantArray[i].sprite.collision.y = 5 + peasantArray[i].sprite.dstrect.y;
		}
		void popPeasants() {
			if ((rand() % 100) < 4) {
				for (i = 0; i < MAX_NUM_PEASANTS; i++) {
					if (!peasantArray[i].sprite.isActive) {
						peasantArray[i].sprite.isActive = true;
						peasantArray[i].frameState = 0;
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
		void peasantEatTest() {
			for (i = 0; i < MAX_NUM_PEASANTS; i++) {
				if (peasantArray[i].sprite.isActive && !peasantArray[i].stomped && SDL_HasIntersection(&player.sprite.collision, &peasantArray[i].sprite.collision)) {
					peasantArray[i].stomped = true;
					peasantArray[i].frameState = 7;
					updateScore(2);
					if (peasantometer < 9) {
						peasantometer++;
					} else {
						peasantometer = 10;
						b_frameState = 3;
					}
				}
			}
		}
		void peasantTimerClick() {
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
							} else if (peasantometer > 0) {
								peasantometer--;
							}
							peasantArray[i].burning = false;
							//peasantArray[i].dstrect.x = -300;
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
		void testBurnPeasant() {
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
					peasantArray[i].frameState = 25;
				}
			}
		}
		void dm_updateFrameState() { // death message
			dm_frameState++;
			switch (dm_frameState) {
				case 4:
					sprite_dm.setFrame(0);
					sprite_dm.setForm(0);
					sprite_dm.isActive = true;
					player.frameState = 19;
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
					}
					break;
				case 27:
				case 52:
					sprite_dm.isActive = false;
					player.frameState = 0;
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
					dm_frameState = 0;
					break;
				case 29:
					sprite_dm.setFrame(1);
					sprite_dm.setForm(0);
					sprite_dm.isActive = true;
					player.frameState = 49;
					paused = true;
					arched = true;
					break;
				case 31:
					if (mans > 0 && (rand() % 100) < 20 * sbVoiceMult) {
						loadAndPlaySound(SFX_SBARCH);
					}
					break;
			}
			if (dm_frameState < 28) {
				sprite_dm.setForm((((dm_frameState - 4) / 2) % 5));
			} else {
				sprite_dm.setForm((((dm_frameState - 29) / 2) % 5));
			}
		}
		void b_updateFrameState() { // burninate message
			b_frameState++;
			// hardcoded is messier, but faster
			switch (b_frameState) {
				case 4:
					sprite_bf.setFrame(0);
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
					sprite_bf.setForm(5);
					break;
				case 10:
					sprite_bf.setForm(6);
					break;
				case 11:
					sprite_bf.setFrame(1);
					sprite_bf.setForm(0);
					break;
				case 12:
					sprite_bf.setForm(1);
					break;
				case 13:
					sprite_bf.setForm(2);
					break;
				case 14:
					sprite_bf.setForm(3);
					break;
				case 16:
					sprite_bf.setForm(4);
					break;
				case 17:
					sprite_bf.setForm(5);
					break;
				case 18:
					sprite_bf.setForm(6);
					b_visible = false;
					paused = false;
					peasantometer = 10;
					setBurnination(100);
					player.updateBreathLoc();
					b_frameState = 0;
					break;
				default:
					break;
			}
		}
		void kick_updateFrameState() {
			kick_frameState++;
			switch (kick_frameState) {
				case 4:
					loadAndPlaySound(SFX_KICK);
					break;
				case 9:
					loadAndPlaySound(SFX_TROGADOR);
					break;
				case 29:
					kick_frameState = 0;
					break;
			}
		}
		void burninationIncreaseCheat() {
			if (peasantometer < 9) {
				peasantometer++;
			} else {
				peasantometer = 10;
				b_frameState = 3;
			}
		}
		void burninationDecreaseCheat() {
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
		void handleDebugCheat() {
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
			}
			if (keyPressed(INPUT_R) && level < 100) {
				updateLevel(1);
			}
		}
		void testLootHit() {
			for (i = 0; i < MAX_NUM_LOOT; i++) {
				if (lootArray[i].sprite.isActive && SDL_HasIntersection(&player.sprite.dstrect, &lootArray[i].sprite.dstrect)) {
					updateScore(50);
					loadAndPlaySound(SFX_GOLDGET);
					lootArray[i].sprite.isActive = false;
				}
			}
		}
		void renderAndAnimateCottages() {
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
		void renderArchers() {
			if (archerR.sprite.isActive) {
				archerR.sprite.renderSprite_game();
			}
			if (archerL.sprite.isActive) {
				archerL.sprite.renderSprite_game();
			}
		}
		void renderArrows() {
			for (i = 0; i < MAX_NUM_ARROWS; i++) {
				if (arrowArrayR[i].sprite.isActive) {
					arrowArrayR[i].sprite.renderSprite_game();
				}
				if (arrowArrayL[i].sprite.isActive) {
					arrowArrayL[i].sprite.renderSprite_game();
				}
			}
		}
		void renderLoot() {
			for (i = 0; i < MAX_NUM_LOOT; i++) {
				if (lootArray[i].sprite.isActive) {
					lootArray[i].sprite.renderSprite_game();
				}
			}
		}
		void renderKnights() {
			for (i = 0; i < MAX_NUM_KNIGHTS; i++) {
				knightArray[i].sprite.renderSprite_game();
			}
		}
		void renderPeasants() {
			for (i = 0; i < MAX_NUM_PEASANTS; i++) {
				if (peasantArray[i].sprite.isActive) {
					if (!manually_paused && (!peasantArray[i].waiting || peasantArray[i].stomped)) {
						peasantArray[i].updateFrameState(sbVoiceMult);
					}
					peasantArray[i].sprite.renderSprite_game();
				}
			}
		}
		void renderTrogdor() {
			if (player.sprite.isActive) {
				if (player.frameState >= 19) {
					player.sprite_death.renderSprite_game();
				} else {
					player.sprite.renderSprite_game();
				}
			}
		}
		void setBurnination(double num) {
			burnination = num;
			sprite_bmFull.srcrect.w = (int)(sprite_burnination_meter_empty.dstrect.w * burnination / 100.0);
			sprite_burnination_meter_full.dstrect.w = sprite_bmFull.srcrect.w;
		}
		void renderTopBar() {
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
};

#endif