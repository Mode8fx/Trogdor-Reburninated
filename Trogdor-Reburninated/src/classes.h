#ifndef CLASSES_H
#define CLASSES_H

#include "config.h"
#include "general.h"
#include "window.h"
#include "input.h"
#include "level_data.h"
#include "media_objects_init.h"
#include "sound_logic.h"
#include "sprite_objects.h"

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

extern Uint16 rand_var;
extern Uint32 frameCounter_global;
extern Uint8 contraArrayKey[10];

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
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		SDL_Rect fire_srcrect;
		SDL_Rect fire_dstrect;
		bool burning;
		bool burned;
		Sint16 direction;
		SDL_Rect collision;
		SDL_Rect fire_collision;
		Cottage(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint16 dir = 1) {
			frameState = 9;
			srcrect = { 0, (dir - 1) * sprite_cottage.dstrect.h, sprite_cottage.dstrect.w, sprite_cottage.dstrect.h };
			dstrect = { pos_x, pos_y, sprite_cottage.dstrect.w, sprite_cottage.dstrect.h };
			fire_srcrect = { 0, 0, sprite_cottage_fire.dstrect.w, sprite_cottage_fire.dstrect.h };
			fire_dstrect = { dstrect.x + 5, dstrect.y - 5, sprite_cottage_fire.dstrect.w, sprite_cottage_fire.dstrect.h };
			burning = false;
			burned = false;
			direction = dir;
			switch (direction) {
				case 1:
					collision = { 8 + dstrect.x, 15 + dstrect.y, 23, 12 };
					fire_collision = { 4 + dstrect.x, 1 + dstrect.y, 32, 36 };
					break;
				case 2:
					collision = { 8 + dstrect.x, 16 + dstrect.y, 23, 12 };
					fire_collision = { 3 + dstrect.x, 0 + dstrect.y, 33, 37 };
					break;
				case 3:
					collision = { 12 + dstrect.x, 14 + dstrect.y, 22, 13 };
					fire_collision = { 7 + dstrect.x, 1 + dstrect.y, 32, 36 };
					break;
				case 4:
					collision = { 7 + dstrect.x, 15 + dstrect.y, 25, 12 };
					fire_collision = { 4 + dstrect.x, 1 + dstrect.y, 32, 36 };
					break;
				default:
					collision = { 8 + dstrect.x, 16 + dstrect.y, 23, 12 };
					fire_collision = { 3 + dstrect.x, 0 + dstrect.y, 33, 37 };
					break;
			}
		}
		void updateFrameState() {
			frameState++;
			if (frameState == 10) {
				loadAndPlaySound(SFX_BURN_HUT);
			}
			if (frameState >= 12 && frameState <= 28) {
				fire_srcrect.x = (((frameState - 12) / 3) % 4) * sprite_cottage_fire.dstrect.w;
				fire_srcrect.y = ((direction == 3) * sprite_cottage_fire.dstrect.h);
				if (frameState == 26) {
					srcrect.x = dstrect.w;
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
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		Sint8 direction;
		bool facingRight;
		Sint16 home_x;    // the parent (x,y) coordinates
		Sint16 home_y;    // the parent (x,y) coordinates
		Sint16 offset_x;  // the offset relative to home
		Sint16 offset_y;  // the offset relative to home
		SDL_Rect collision;
		Knight(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 1, bool fr = true) {
			frameState = 0;
			moving = true;
			facingRight = fr;
			home_x = pos_x;
			home_y = pos_y;
			srcrect = { 0, facingRight * sprite_knight.dstrect.h, sprite_knight.dstrect.w, sprite_knight.dstrect.h };
			dstrect = { home_x, home_y, sprite_knight.dstrect.w, sprite_knight.dstrect.h };
			offset_x = 0;
			offset_y = 0;
			direction = dir;
			updateCollision();
		}
		inline void updateCollision() {
			if (facingRight) {
				collision = { 4 + dstrect.x, 9 + dstrect.y, 9, 13 };
			} else {
				collision = { 8 + dstrect.x, 9 + dstrect.y, 9, 13 };
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
					srcrect.x = 0;
					break;
				case 5:
				case 29:
				case 53:
					srcrect.x = sprite_knight.dstrect.w;
					break;
				case 13:
				case 21:
				case 37:
				case 45:
					srcrect.x = 2 * sprite_knight.dstrect.w;
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
			if (!facingRight) {
				offset_x *= -1;
			}

			dstrect.x = home_x + offset_x;
			dstrect.y = home_y + offset_y;
			updateCollision();
		}
};

class Peasant {
	public:
		Uint8 frameState;
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		bool active;
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
		SDL_Rect collision;
		Peasant() {
			frameState = 0;
			srcrect = { 0, 0, sprite_peasant.dstrect.w, sprite_peasant.dstrect.h };
			dstrect = { 0, 0, sprite_peasant.dstrect.w, sprite_peasant.dstrect.h };
			active = false;
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
			collision = { 8 + dstrect.x, 5 + dstrect.y, 8, 19 };
		}
		void updateFrameState() {
			frameState++;
			switch (frameState) {
				case 1:
					srcrect.x = 0;
					srcrect.y = 0;
					break;
				case 4:
					srcrect.x = sprite_peasant.dstrect.w;
					break;
				case 6:
					frameState = 0;
					break;
				case 8:
					srcrect.x = 0;
					srcrect.y = 2 * sprite_peasant.dstrect.h;
					loadAndPlaySound(SFX_SQUISH);
					rand_var = rand() % 100000;
					if (rand_var < 3) {
						loadAndPlaySound(SFX_SB2);
					} else if (rand_var < 6) {
						loadAndPlaySound(SFX_SBSQUISH1);
					} else if (rand_var < 10) {
						loadAndPlaySound(SFX_SBSQUISH2);
					}
					break;
				case 25:
					active = false;
					stomped = false;
					dstrect.x = -300;
					break;
				case 26:
					srcrect.x = 0;
					srcrect.y = sprite_peasant.dstrect.h;
					break;
				case 27:
					srcrect.x = sprite_peasant.dstrect.w;
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
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		bool active;
		bool facingRight; // facing right == on the left; facing left == on the right
		Archer(Sint16 pos_x = 0, Sint16 pos_y = 0, bool fr = true) {
			frameState = 0;
			facingRight = fr;
			srcrect = { 0, facingRight * sprite_archer.dstrect.h, sprite_archer.dstrect.w, sprite_archer.dstrect.h };
			dstrect = { pos_x, pos_y, sprite_archer.dstrect.w, sprite_archer.dstrect.h };
			active = false;
		}
		void updateFrameState() {
			frameState++;
			switch (frameState) {
				case 14:
					srcrect.x = dstrect.w;
					break;
				case 20:
					srcrect.x = 0;
					// shoot arrow; this is handled by GameManager
					break;
				case 23:
					dstrect.y = -300;
					active = false;
				default:
					break;
			}
		}
};

class Arrow {
	public:
		Uint8 frameState;
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		bool active;
		bool facingRight;
		SDL_Rect collision;
		Arrow(Sint16 pos_x = 0, Sint16 pos_y = 0, bool fr = true) {
			frameState = 0;
			facingRight = fr;
			srcrect = { 0, facingRight * sprite_arrow.dstrect.h, sprite_arrow.dstrect.w, sprite_arrow.dstrect.h };
			dstrect = { pos_x, pos_y, sprite_arrow.dstrect.w, sprite_arrow.dstrect.h };
			active = false;
			collision = { 1 + facingRight + dstrect.x, 1 + dstrect.y, 12, 3 };
		}
		void updateFrameState() {
			frameState++;
			if (frameState == 1) { // 4?
				loadAndPlaySound(SFX_ARROW);
			}
			if (facingRight) {
				dstrect.x += 5;
				if (dstrect.x > 250) { // not exactly the same as the original, but close enough
					clear();
				}
				collision.x = 2 + dstrect.x;
				collision.y = 1 + dstrect.y;

			} else {
				dstrect.x -= 5;
				if (dstrect.x < -8) { // not exactly the same as the original, but close enough
					clear();
				}
				collision.x = 1 + dstrect.x;
				collision.y = 1 + dstrect.y;
			}
		}
		void clear() {
			active = false;
			dstrect.x = -500;
		}
};

class Loot {
	public:
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		bool active;
		Loot() {
		}
		Loot(Sint16 x_pos, Sint16 y_pos) {
			srcrect = { 0, 0, sprite_loot.dstrect.w, sprite_loot.dstrect.h };
			dstrect = { x_pos, y_pos, sprite_loot.dstrect.w, sprite_loot.dstrect.h };
			active = false;
		}
};

class Trogdor {
	public:
		Uint8 frameState;
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		Uint8 fire_frameState;
		SDL_Rect fire_srcrect;
		SDL_Rect fire_dstrect;
		SDL_Rect death_srcrect;
		SDL_Rect death_dstrect;
		bool facingRight;
		SDL_Rect collision;
		Sint16 spawnPos_x;
		Sint16 spawnPos_y;
		Sint8 invince;        // remaining invincibility time (after respawn)
		bool visible;         // sprite is visible (used with invince)
		Sint8 x_offset;       // used for movement
		Sint8 y_offset;       // used for movement
		Sint8 moveSpeed;      // used for movement
		Uint8 frameStateFlag; // used for movement
		Trogdor() {
			frameState = 0;
			facingRight = true;
			srcrect = { 0, facingRight * sprite_trogdor.dstrect.h, sprite_trogdor.dstrect.w, sprite_trogdor.dstrect.h };
			spawnPos_x = (Sint16)(2780.0 / 5000 * gameWidth) - (srcrect.w / 2);
			spawnPos_y = (Sint16)(2360.0 / 3600 * gameHeight) - (srcrect.h / 2);
			dstrect = { spawnPos_x, spawnPos_y, sprite_trogdor.dstrect.w, sprite_trogdor.dstrect.h };
			collision = { 11 + dstrect.x, 11 + dstrect.y, 18, 24 };
			fire_frameState = 0;
			fire_srcrect = { 0, facingRight * sprite_trogdor_fire.dstrect.h, sprite_trogdor_fire.dstrect.w, sprite_trogdor_fire.dstrect.h };
			fire_dstrect = { dstrect.x - 24 + (facingRight * 62), dstrect.y + 10, sprite_trogdor_fire.dstrect.w, sprite_trogdor_fire.dstrect.h };
			death_srcrect = { 0, 0, sprite_trogdor_dead.dstrect.w, sprite_trogdor_dead.dstrect.h };
			death_dstrect = { dstrect.x + ((dstrect.w + sprite_trogdor_dead.dstrect.w) / 2), dstrect.y + (dstrect.h - sprite_trogdor_dead.dstrect.h), sprite_trogdor_dead.dstrect.w, sprite_trogdor_dead.dstrect.h };
			invince = 0;
			visible = true;
			srcrect.x = 0;
			srcrect.y = srcrect.h;
			x_offset = 0;
			y_offset = 0;
			moveSpeed = 3;
			frameStateFlag = 0;
		}
		void updateFrameState() {
			frameState++;
			switch (frameState) {
				case 20: // sworded
					death_srcrect.x = 0;
					death_dstrect.x = dstrect.x + ((dstrect.w - sprite_trogdor_dead.dstrect.w) / 2);
					death_dstrect.y = dstrect.y + (dstrect.h - sprite_trogdor_dead.dstrect.h);
					break;
				case 50: // arrowed
					death_srcrect.x = sprite_trogdor_dead.srcrect.w;
					death_dstrect.x = dstrect.x + ((dstrect.w - sprite_trogdor_dead.dstrect.w) / 2);
					death_dstrect.y = dstrect.y + (dstrect.h - sprite_trogdor_dead.dstrect.h);
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
					visible = false;
					break;
				case 36:
				case 40:
				case 66:
				case 70:
					visible = true;
					break;
				case 48:
				case 78:
					visible = true;
					frameState = 0;
					break;
			}
		}
		void resetPos(bool giveInvince) {
			facingRight = true;
			srcrect = { 0, facingRight * sprite_trogdor.dstrect.h, sprite_trogdor.dstrect.w, sprite_trogdor.dstrect.h };
			dstrect = { spawnPos_x, spawnPos_y, sprite_trogdor.dstrect.w, sprite_trogdor.dstrect.h };
			collision = { 11 + dstrect.x, 11 + dstrect.y, 18, 24 };
			if (giveInvince) {
				invince = 36;
			}
		}
		void updateBreathLoc() {
			fire_dstrect.x = dstrect.x - 24 + (facingRight * 62);
			fire_dstrect.y = dstrect.y + 10;
		}
		void invinceCheck() {
			if (invince >= 1) {
				invince--;
				if (invince % 3 == 0) {
					visible = false;
				} else {
					visible = true;
				}
				if (invince == 0) {
					visible = true;
				}
			}
		}
};

class MenuManager {
	public:
		bool contraActive; // Konami code (Contra cheat) is enabled
		Sint8 contraIndex; // the current index of the Konami code input
		Sint8 page;        // the current page number
		MenuManager() {
			contraActive = false;
			contraIndex = 0;
			page = 1;
		}
		void typeStuff() {
			if (!contraActive) {
				if (keyInputs != 0) {
					if (keyInputs == (1 << (contraArrayKey[contraIndex]))) {
						contraIndex++;
						if (contraIndex == LEN(contraArrayKey)) {
							contraActive = true;
						}
					} else {
						contraIndex = 0;
					}
				}
			}
		}
		void handlePageChange() {
			if (keyPressed(INPUT_LEFT)) {
				page--;
				if (page < 1) page = 3;
				updateText(&text_3_page, "("+to_string(page)+"/3)");
			} else if (keyPressed(INPUT_RIGHT)) {
				page++;
				if (page > 3) page = 1;
				updateText(&text_3_page, "(" + to_string(page) + "/3)");
			}
		}
};

#define SET_BURNINATION(num)                                                                                         \
	burnination = num;                                                                                               \
	sprite_burnination_meter_full.srcrect.w = (int)(sprite_burnination_meter_empty.dstrect.w * burnination / 100.0); \
	sprite_burnination_meter_full.dstrect.w = sprite_burnination_meter_full.srcrect.w;

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
		Uint8 dm_frameState;                    // Death Message ("SWORDED!", "ARROWED!")
		SDL_Rect dm_srcrect;                    // Death Message ("SWORDED!", "ARROWED!")
		SDL_Rect dm_dstrect;                    // Death Message ("SWORDED!", "ARROWED!")
		bool dm_visible;                        // Death Message ("SWORDED!", "ARROWED!")
		Uint8 b_frameState;                     // BURNINATE! Message
		SDL_Rect bt_srcrect;                    // BURNINATE! Message Text
		SDL_Rect bt_dstrect;                    // BURNINATE! Message Text
		SDL_Rect bf_srcrect;                    // BURNINATE! Message Fire
		SDL_Rect bf_dstrect;                    // BURNINATE! Message Fire
		bool b_visible;                         // BURNINATE! Message
		Uint8 kick_frameState;                  // kick the machine
		bool treasureHutFound;                  // treasure hut has been found in this level
		bool inTreasureHut;                     // player is currently in treasure hut
		Sint16 treasureHutIndex;                // index of hut that contains treasure (0 = no treasure hut)
		Sint16 storex;                          // old player X position (used for treasure huts)
		Sint16 storey;                          // old player Y position (used for treasure huts)
		Sint16 treasureHut_timer;               // remaining time in treasure hut
		Loot lootArray[MAX_NUM_LOOT];           // array of Loot objects
		GameManager() {
		}
		GameManager(Sint8 init_mans) {
			srand(SDL_GetTicks());
			mans = init_mans;
			score = 0;
			peasantometer = 0;
			paused = false;
			startDown = false;
			manually_paused = false;
			gameOver = false;
			level = 1;
			levelIndex = 1;
			SET_BURNINATION(0);
			archerFrequency = 0;
			burnRate = 0;
			player = Trogdor();
			player.facingRight = true;
			knightIncrement = 1;
			extraMansBreak = 300;
			extraMansCounter = 0;
			arched = false;
			dm_frameState = 0;
			dm_srcrect = { 0, 0, sprite_death_message.dstrect.w, sprite_death_message.dstrect.h };
			dm_dstrect = { OBJ_TO_MID_SCREEN_X(gameWidth, sprite_death_message), OBJ_TO_MID_SCREEN_Y(gameHeight, sprite_death_message), sprite_death_message.dstrect.w, sprite_death_message.dstrect.h };
			dm_visible = false;
			b_frameState = 0;
			bt_srcrect = { 0, 0, sprite_burninate_text.dstrect.w, sprite_burninate_text.dstrect.h };
			bt_dstrect = { OBJ_TO_MID_SCREEN_X(gameWidth, sprite_burninate_text), OBJ_TO_MID_SCREEN_Y(gameHeight, sprite_burninate_text), sprite_burninate_text.dstrect.w, sprite_burninate_text.dstrect.h };
			bf_srcrect = { 0, 0, sprite_burninate_fire.dstrect.w, sprite_burninate_fire.dstrect.h };
			bf_dstrect = { OBJ_TO_MID_SCREEN_X(gameWidth, sprite_burninate_fire), bt_dstrect.y - bf_srcrect.h + 4, sprite_burninate_fire.dstrect.w, sprite_burninate_fire.dstrect.h };
			b_visible = false;
			kick_frameState = 0;
			numHuts = 0;
			treasureHutFound = false;
			inTreasureHut = false;
			treasureHutIndex = 0;
			storex = 0;
			storey = 0;
			treasureHut_timer = 0;
		}
		void levelInit() {
			SET_BURNINATION(0);
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
						(Sint16)OBJ_TO_SCREEN_AT_FRACTION_X(gameWidth, sprite_cottage, (levels[levelIndex][j + 1] + 2466) / 5000.0) + 8,
						(Sint16)OBJ_TO_SCREEN_AT_FRACTION_Y(gameHeight, sprite_cottage, (levels[levelIndex][j + 2] + 2183) / 3600.0) - 11,
						levels[levelIndex][j]
					);
					numHuts++;
					//PRINT("COTTAGE INFO:");
					//PRINT((int)hutArray[i].direction);
					//PRINT((int)hutArray[i].dstrect.x);
					//PRINT((int)hutArray[i].dstrect.y);
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
				if (!player.facingRight) {
					player.frameStateFlag |= 1;
				} else {
					player.frameStateFlag |= 2;
					player.facingRight = false;
				}
				player.x_offset = -player.moveSpeed;
			}
			if (keyHeld(INPUT_RIGHT)) {
				if (player.facingRight) {
					player.frameStateFlag |= 1;
				} else {
					player.frameStateFlag |= 2;
					player.facingRight = true;
				}
				player.x_offset = player.moveSpeed;
			}
			if (!inTreasureHut) {
				playerMove(&player, player.x_offset, player.y_offset);
				if (keyHeld(INPUT_START)) {
					startDown = true;
				}
				if (startDown && !keyHeld(INPUT_START)) {
					startDown = false;
					manually_paused = frameCounter_global;
				}
			} else {
				playerMove_treasureHut(&player, player.x_offset, player.y_offset);
			}
			if (keyHeld(INPUT_L) && kick_frameState == 0) {
				kick_frameState = 3;
			}
		}
		inline void trogdor_add_x_delta(Sint8 dx) {
			player.dstrect.x += dx;
			player.collision.x = 11 + player.dstrect.x;
		}
		inline void trogdor_add_y_delta(Sint8 dy) {
			player.dstrect.y += dy;
			player.collision.y = 11 + player.dstrect.y;
		}
		inline void handle_treasure_hut_entry(Trogdor* trog, Sint8 delta_x, Sint8 delta_y) {
			// Technically, the original treasure_button collision is different from the hut fire collision used here, but it's both negligible and inconsistent between huts (seems like a bug), so I'm not gonna bother
			if (treasureHutIndex && !treasureHutFound && !hutArray[treasureHutIndex - 1].burned && SDL_HasIntersection(&trog->dstrect, &hutArray[treasureHutIndex - 1].collision)) {
				inTreasureHut = true;
				for (i = 0; i < MAX_NUM_LOOT; i++) {
					lootArray[i].active = true;
				}
				storex = player.dstrect.x - delta_x; // The delta is to prevent respawning inside hut after exitting (this probably wouldn't happen, but just in case)
				storey = player.dstrect.y - delta_y;
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
				if (trog->dstrect.x < LEFT_BOUND_TROG || trog->dstrect.x > RIGHT_BOUND_TROG) {
					trogdor_add_x_delta(-delta_x);
				}
				for (i = 0; i < MAX_NUM_HUTS; i++) {
					if (hutArray[i].direction > 0 && !hutArray[i].burned
						&& SDL_HasIntersection(&trog->dstrect, &hutArray[i].collision)) { // &trog->sprite->dstrect, NOT &trog->collision
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
				if (trog->dstrect.y < UPPER_BOUND_TROG || trog->dstrect.y > LOWER_BOUND_TROG) {
					trogdor_add_y_delta(-delta_y);
				}
				for (i = 0; i < MAX_NUM_HUTS; i++) {
					if (hutArray[i].direction > 0 && !hutArray[i].burned
						&& SDL_HasIntersection(&trog->dstrect, &hutArray[i].collision)) { // &trog->sprite->dstrect, NOT &trog->collision
						trogdor_add_y_delta(-delta_y);
						break;
					}
				}
			}
			// Animate sprite
			if (trog->frameStateFlag & 2) {
				trog->frameState = 0;
				trog->srcrect.x = 0;
				trog->srcrect.y = trog->facingRight * trog->srcrect.h;
			} else if (trog->frameStateFlag & 1) {
				trog->frameState = (++trog->frameState % 8);
				trog->srcrect.x = (trog->frameState / 2) * trog->srcrect.w;
			}
			if (burnination > 0) {
				trog->updateBreathLoc();
				// Animate sprite
				if (trog->frameStateFlag & 2) {
					trog->fire_frameState = 0;
					trog->fire_srcrect.x = 0;
					trog->fire_srcrect.y = trog->facingRight * trog->fire_srcrect.h;
				} else {
					trog->fire_frameState = (++trog->fire_frameState % 12);
					trog->fire_srcrect.x = (trog->fire_frameState / 3) * trog->fire_srcrect.w;
				}
			}
		}
		void playerMove_treasureHut(Trogdor* trog, Sint8 delta_x, Sint8 delta_y) {
			// X movement
			if (delta_x != 0) {
				trogdor_add_x_delta(delta_x);
				// Collision
				if (trog->dstrect.x < LEFT_BOUND_TROG || trog->dstrect.x > RIGHT_BOUND_TROG) {
					trogdor_add_x_delta(-delta_x);
				}
			}
			// Y movement
			if (delta_y != 0) {
				trogdor_add_y_delta(delta_y);
				// Collision
				if (trog->dstrect.y < UPPER_BOUND_TROG || trog->dstrect.y > LOWER_BOUND_TROG) {
					trogdor_add_y_delta(-delta_y);
				}
			}
			// Animate sprite
			if (trog->frameStateFlag & 2) {
				trog->frameState = 0;
				trog->srcrect.x = 0;
				trog->srcrect.y = trog->facingRight * trog->srcrect.h;
			} else if (trog->frameStateFlag & 1) {
				trog->frameState = (++trog->frameState % 8);
				trog->srcrect.x = (trog->frameState / 2) * trog->srcrect.w;
			}
			if (burnination > 0) {
				trog->updateBreathLoc();
				// Animate sprite
				if (trog->frameStateFlag & 2) {
					trog->fire_frameState = 0;
					trog->fire_srcrect.x = 0;
					trog->fire_srcrect.y = trog->facingRight * trog->fire_srcrect.h;
				} else {
					trog->fire_frameState = (++trog->fire_frameState % 12);
					trog->fire_srcrect.x = (trog->fire_frameState / 3) * trog->fire_srcrect.w;
				}
			}
		}
		void popArchers() {
			rand_var = rand() % 10000;
			if (rand_var < archerFrequency) {
				if (rand_var % 2 == 0) {
					if (!archerR.active) {
						archerR.active = true;
						archerR.dstrect.y = rand() % (ARCHER_Y_LOWER - ARCHER_Y_UPPER + 1) + ARCHER_Y_UPPER;
						archerR.frameState = 4;
					}
				} else {
					if (!archerL.active) {
						archerL.active = true;
						archerL.dstrect.y = rand() % (ARCHER_Y_LOWER - ARCHER_Y_UPPER + 1) + ARCHER_Y_UPPER;
						archerL.frameState = 4;
					}
				}
			}
		}
		void updateArchersAndArrows() {
			if (archerR.active) {
				archerR.updateFrameState();
				if (archerR.frameState == 20) {
					for (i = 0; i < MAX_NUM_ARROWS; i++) {
						if (!arrowArrayR[i].active) {
							arrowArrayR[i].frameState = 0;
							arrowArrayR[i].active = true;
							arrowArrayR[i].dstrect.x = archerR.dstrect.x + (archerR.dstrect.w / 2) - (arrowArrayR[i].dstrect.w / 2);
							arrowArrayR[i].dstrect.y = archerR.dstrect.y + (archerR.dstrect.h / 2) - (arrowArrayR[i].dstrect.h / 2);
							break;
						}
					}
				}
			}
			if (archerL.active) {
				archerL.updateFrameState();
				if (archerL.frameState == 20) {
					for (i = 0; i < MAX_NUM_ARROWS; i++) {
						if (!arrowArrayL[i].active) {
							arrowArrayL[i].frameState = 0;
							arrowArrayL[i].active = true;
							arrowArrayL[i].dstrect.x = archerL.dstrect.x + (archerL.dstrect.w / 2) - (arrowArrayL[i].dstrect.w / 2);
							arrowArrayL[i].dstrect.y = archerL.dstrect.y + (archerL.dstrect.h / 2) - (arrowArrayL[i].dstrect.h / 2);
							break;
						}
					}
				}
			}
			for (i = 0; i < MAX_NUM_ARROWS; i++) {
				if (arrowArrayR[i].active) {
					arrowArrayR[i].updateFrameState();
				}
				if (arrowArrayL[i].active) {
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
					if (SDL_HasIntersection(&player.dstrect, &knightArray[i].collision)) {
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
					if (arrowArrayL[i].active && SDL_HasIntersection(&player.collision, &arrowArrayL[i].collision)) {
						paused = true;
						// the original game does NOT pause knights when you are arrowed
						clearArrows();
						dm_frameState = 28;
						break;
					}
					if (arrowArrayR[i].active && SDL_HasIntersection(&player.collision, &arrowArrayR[i].collision)) {
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
				if (!hutArray[i].burning && SDL_HasIntersection(&player.fire_dstrect, &hutArray[i].fire_collision)) {
					hutArray[i].burning = true;
					rand_var = rand() % 10000;
					if (rand_var < 500) {
						loadAndPlaySound(SFX_SBDOOJ);
					}
				}
			}
		}
		inline void updateBurnmeter() {
			SET_BURNINATION(burnination - burnRate);
			if (burnination <= 0) {
				SET_BURNINATION(0);
				peasantometer = 0;
			}
		}
		inline void peasant_set_x_delta(Sint16 new_x) {
			peasantArray[i].dstrect.x = new_x;
			peasantArray[i].collision.x = 8 + peasantArray[i].dstrect.x;
		}
		inline void peasant_set_y_delta(Sint16 new_y) {
			peasantArray[i].dstrect.y = new_y;
			peasantArray[i].collision.y = 5 + peasantArray[i].dstrect.y;
		}
		inline void peasant_add_x_delta(Sint8 dx) {
			peasantArray[i].dstrect.x += dx;
			peasantArray[i].collision.x = 8 + peasantArray[i].dstrect.x;
		}
		inline void peasant_add_y_delta(Sint8 dy) {
			peasantArray[i].dstrect.y += dy;
			peasantArray[i].collision.y = 5 + peasantArray[i].dstrect.y;
		}
		void popPeasants() {
			if ((rand() % 100) < 4) {
				for (i = 0; i < MAX_NUM_PEASANTS; i++) {
					if (!peasantArray[i].active) {
						peasantArray[i].active = true;
						peasantArray[i].frameState = 0;
						j = rand() % numHuts; // j = hutChoice
						peasantArray[i].myHome = j;
						peasantArray[i].returning = false;
						peasantArray[i].waiting = false;
						peasantArray[i].stomped = false;
						peasantArray[i].direction = hutArray[j].direction;
						switch (peasantArray[i].direction) {
							case 1: // UP
								peasant_set_x_delta(hutArray[j].dstrect.x + 9);
								peasant_set_y_delta(hutArray[j].dstrect.y - 6);
								peasantArray[i].myTargetx = peasantArray[i].dstrect.x;
								peasantArray[i].myTargety = peasantArray[i].dstrect.y - ((rand() % (peasantArray[i].dstrect.y - UPPER_BOUND + 6)) + 6);
								break;
							case 2: // DOWN
								peasant_set_x_delta(hutArray[j].dstrect.x + 7);
								peasant_set_y_delta(hutArray[j].dstrect.y + 20);
								peasantArray[i].myTargetx = peasantArray[i].dstrect.x;
								peasantArray[i].myTargety = peasantArray[i].dstrect.y + ((rand() % (LOWER_BOUND - peasantArray[i].dstrect.y - 4)) + 4);
								break;
							case 3: // LEFT
								peasant_set_x_delta(hutArray[j].dstrect.x + 3);
								peasant_set_y_delta(hutArray[j].dstrect.y + 18);
								peasantArray[i].myTargetx = peasantArray[i].dstrect.x - ((rand() % (peasantArray[i].dstrect.x - LEFT_BOUND - 9)) + 9);
								peasantArray[i].myTargety = peasantArray[i].dstrect.y;
								break;
							case 4: // RIGHT
								peasant_set_x_delta(hutArray[j].dstrect.x + 16);
								peasant_set_y_delta(hutArray[j].dstrect.y + 18);
								peasantArray[i].myTargetx = peasantArray[i].dstrect.x + ((rand() % (RIGHT_BOUND - peasantArray[i].dstrect.x + 11)) + 11);
								peasantArray[i].myTargety = peasantArray[i].dstrect.y;
								break;
							default:
								break;
						}
						peasantArray[i].myStartx = peasantArray[i].dstrect.x;
						peasantArray[i].myStarty = peasantArray[i].dstrect.y;
						break;
					}
				}
			}
		}
		void peasantEatTest() {
			for (i = 0; i < MAX_NUM_PEASANTS; i++) {
				if (peasantArray[i].active && !peasantArray[i].stomped && SDL_HasIntersection(&player.collision, &peasantArray[i].collision)) {
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
				if (peasantArray[i].active && !peasantArray[i].waiting && !peasantArray[i].stomped) {
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
						if ((j >= 1 && peasantArray[i].dstrect.x >= peasantArray[i].myStartx)
							|| (j <= -1 && peasantArray[i].dstrect.x <= peasantArray[i].myStartx)
							|| (k >= 1 && peasantArray[i].dstrect.y >= peasantArray[i].myStarty)
							|| (k <= -1 && peasantArray[i].dstrect.y <= peasantArray[i].myStarty)) {
							peasant_add_x_delta(-j);
							peasant_add_y_delta(-k);
						} else {
							peasantArray[i].active = false;
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
					} else if ((j >= 1 && peasantArray[i].dstrect.x <= peasantArray[i].myTargetx)
						|| (j <= -1 && peasantArray[i].dstrect.x >= peasantArray[i].myTargetx)
						|| (k >= 1 && peasantArray[i].dstrect.y <= peasantArray[i].myTargety)
						|| (k <= -1 && peasantArray[i].dstrect.y >= peasantArray[i].myTargety)) {
						peasant_add_x_delta(j);
						peasant_add_y_delta(k);
					} else {
						peasantArray[i].waiting = true;
						peasantArray[i].timer = (60 / level) + 24;
					}
				}
				if (peasantArray[i].active && peasantArray[i].waiting) {
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
				if (!peasantArray[i].burning && !peasantArray[i].stomped && peasantArray[i].active && SDL_HasIntersection(&player.fire_dstrect, &peasantArray[i].collision)) {
					loadAndPlaySound(SFX_PEASANTSCREAM);
					if ((rand() % 100) < 40) {
						if ((rand() % 100) > 50) {
							loadAndPlaySound(SFX_SB6);
						} else {
							loadAndPlaySound(SFX_SB6); // These two are the same... I feel like this one is supposed to be SFX_SB7? It's completely unused, and it would fit here
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
					dm_srcrect.x = 0;
					//dm_srcrect.y = 0;
					dm_visible = true;
					player.frameState = 19;
					paused = true;
					arched = false;
					break;
				case 6:
					if (mans > 0) {
						if (peasantometer == 9) {
							loadAndPlaySound(SFX_SB3);
						} else if ((rand() % 100) < 20) {
							loadAndPlaySound(SFX_SBWORST);
						}
					}
					break;
				case 27:
				case 52:
					dm_visible = false;
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
					dm_srcrect.x = sprite_death_message.dstrect.w;
					//dm_srcrect.y = 0;
					dm_visible = true;
					player.frameState = 49;
					paused = true;
					arched = true;
					break;
				case 31:
					if (mans > 0 && (rand() % 100) < 20) {
						loadAndPlaySound(SFX_SBARCH);
					}
					break;
			}
			if (dm_frameState < 28) {
				dm_srcrect.y = (((dm_frameState -  4) / 2) % 5) * dm_dstrect.h;
			} else {
				dm_srcrect.y = (((dm_frameState - 29) / 2) % 5) * dm_dstrect.h;
			}
		}
		void b_updateFrameState() { // burninate message
			b_frameState++;
			// hardcoded is messier, but faster
			switch (b_frameState) {
				case 4:
					bf_srcrect.y = 0;
					rand_var = rand() % 100;
					if (rand_var < 10) {
						if (rand_var < 50) {
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
					bf_srcrect.y = bf_srcrect.h;
					break;
				case 6:
					bf_srcrect.y = bf_srcrect.h * 2;
					break;
				case 7:
				case 15:
					bf_srcrect.y = bf_srcrect.h * 3;
					break;
				case 8:
					bf_srcrect.y = bf_srcrect.h * 4;
					break;
				case 9:
					bf_srcrect.y = bf_srcrect.h * 5;
					break;
				case 10:
					bf_srcrect.y = bf_srcrect.h * 6;
					break;
				case 11:
					bf_srcrect.y = bf_srcrect.h * 7;
					break;
				case 12:
					bf_srcrect.y = bf_srcrect.h * 8;
					break;
				case 13:
					bf_srcrect.y = bf_srcrect.h * 9;
					break;
				case 14:
					bf_srcrect.y = bf_srcrect.h * 10;
					break;
				case 16:
					bf_srcrect.y = bf_srcrect.h * 11;
					break;
				case 18:
					bf_srcrect.y = bf_srcrect.h * 12;
					b_visible = false;
					paused = false;
					peasantometer = 10;
					SET_BURNINATION(100);
					player.updateBreathLoc();
					b_frameState = 0;
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
		void burninationIncreaseTest() {
			if (peasantometer < 9) {
				peasantometer++;
			} else {
				peasantometer = 10;
				b_frameState = 3;
			}
		}
		void burninationDecreaseTest() {
			if (peasantometer < 10) {
				peasantometer--;
				if (peasantometer < 0) {
					peasantometer = 0;
				}
			} else {
				SET_BURNINATION(burnination - 2);
				if (burnination <= 0) {
					SET_BURNINATION(0);
					peasantometer = 0;
				}
			}
		}
		void testLootHit() {
			for (i = 0; i < MAX_NUM_LOOT; i++) {
				if (lootArray[i].active && SDL_HasIntersection(&player.dstrect, &lootArray[i].dstrect)) {
					updateScore(50);
					loadAndPlaySound(SFX_GOLDGET);
					lootArray[i].active = false;
				}
			}
		}
};

#define RENDER_AND_ANIMATE_COTTAGES()                                                                                     \
	for (i = 0; i < MAX_NUM_HUTS; i++) {                                                                                  \
		if (GM.hutArray[i].direction > 0) {                                                                               \
			if (GM.hutArray[i].burning && !GM.hutArray[i].burned) {                                                       \
				GM.hutArray[i].updateFrameState();                                                                        \
			}                                                                                                             \
			renderSpriteUsingRects(sprite_cottage, GM.hutArray[i].srcrect, GM.hutArray[i].dstrect);                    \
			if (GM.hutArray[i].frameState >= 12 && GM.hutArray[i].frameState <= 28) {                                     \
				renderSpriteUsingRects(sprite_cottage_fire, GM.hutArray[i].fire_srcrect, GM.hutArray[i].fire_dstrect); \
			}                                                                                                             \
		}                                                                                                                 \
	}

#define RENDER_AND_ANIMATE_UPPER_COTTAGES()                                                                               \
	for (i = 0; i < MAX_NUM_HUTS; i++) {                                                                                  \
		if (GM.hutArray[i].direction > 0 && GM.hutArray[i].dstrect.y < GM.player.dstrect.y + 9) {                         \
			if (GM.hutArray[i].burning && !GM.hutArray[i].burned) {                                                       \
				GM.hutArray[i].updateFrameState();                                                                        \
			}                                                                                                             \
			renderSpriteUsingRects(sprite_cottage, GM.hutArray[i].srcrect, GM.hutArray[i].dstrect);                    \
			if (GM.hutArray[i].frameState >= 12 && GM.hutArray[i].frameState <= 28) {                                     \
				renderSpriteUsingRects(sprite_cottage_fire, GM.hutArray[i].fire_srcrect, GM.hutArray[i].fire_dstrect); \
			}                                                                                                             \
		}                                                                                                                 \
	}

#define RENDER_AND_ANIMATE_LOWER_COTTAGES()                                                                               \
	for (i = 0; i < MAX_NUM_HUTS; i++) {                                                                                  \
		if (GM.hutArray[i].direction > 0 && GM.hutArray[i].dstrect.y >= GM.player.dstrect.y + 9) {                        \
			if (GM.hutArray[i].burning && !GM.hutArray[i].burned) {                                                       \
				GM.hutArray[i].updateFrameState();                                                                        \
			}                                                                                                             \
			renderSpriteUsingRects(sprite_cottage, GM.hutArray[i].srcrect, GM.hutArray[i].dstrect);                    \
			if (GM.hutArray[i].frameState >= 12 && GM.hutArray[i].frameState <= 28) {                                     \
				renderSpriteUsingRects(sprite_cottage_fire, GM.hutArray[i].fire_srcrect, GM.hutArray[i].fire_dstrect); \
			}                                                                                                             \
		}                                                                                                                 \
	}

#define RENDER_ARCHERS()                                                                  \
	if (GM.archerR.active) {                                                              \
		renderSpriteUsingRects(sprite_archer, GM.archerR.srcrect, GM.archerR.dstrect); \
	}                                                                                     \
	if (GM.archerL.active) {                                                              \
		renderSpriteUsingRects(sprite_archer, GM.archerL.srcrect, GM.archerL.dstrect); \
	}

#define RENDER_ARROWS()                                                                                    \
	for (i = 0; i < MAX_NUM_ARROWS; i++) {                                                                 \
		if (GM.arrowArrayR[i].active) {                                                                    \
			renderSpriteUsingRects(sprite_arrow, GM.arrowArrayR[i].srcrect, GM.arrowArrayR[i].dstrect); \
		}                                                                                                  \
		if (GM.arrowArrayL[i].active) {                                                                    \
			renderSpriteUsingRects(sprite_arrow, GM.arrowArrayL[i].srcrect, GM.arrowArrayL[i].dstrect); \
		}                                                                                                  \
	}

#define RENDER_LOOT()                                                                                 \
	for (i = 0; i < MAX_NUM_LOOT; i++) {                                                              \
		if (GM.lootArray[i].active) {                                                                 \
			renderSpriteUsingRects(sprite_loot, GM.lootArray[i].srcrect, GM.lootArray[i].dstrect); \
		}                                                                                             \
	}

#define RENDER_KNIGHTS()                                                                                \
	for (i = 0; i < MAX_NUM_KNIGHTS; i++) {                                                             \
		renderSpriteUsingRects(sprite_knight, GM.knightArray[i].srcrect, GM.knightArray[i].dstrect); \
	}

#define RENDER_PEASANTS()                                                                                      \
	for (i = 0; i < MAX_NUM_PEASANTS; i++) {                                                                   \
		if (GM.peasantArray[i].active) {                                                                       \
			if (!GM.manually_paused && (!GM.peasantArray[i].waiting || GM.peasantArray[i].stomped)) {          \
				GM.peasantArray[i].updateFrameState();                                                         \
			}                                                                                                  \
			renderSpriteUsingRects(sprite_peasant, GM.peasantArray[i].srcrect, GM.peasantArray[i].dstrect); \
		}                                                                                                      \
	}

#define RENDER_TROGDOR()                                                                                      \
	if (GM.player.visible) {                                                                                  \
		if (GM.player.frameState >= 19) {                                                                     \
			renderSpriteUsingRects(sprite_trogdor_dead, GM.player.death_srcrect, GM.player.death_dstrect); \
		} else {                                                                                              \
			renderSpriteUsingRects(sprite_trogdor, GM.player.srcrect, GM.player.dstrect);                  \
		}                                                                                                     \
	}

#define RENDER_TOP_BAR()                                                                        \
	renderText(text_4_score, textChars_font_serif_2_red_6);                                    \
	renderText(text_4_score_val, textChars_font_serif_red_6);                                  \
	renderText(text_4_mans, textChars_font_serif_2_red_6);                                     \
	renderText(text_4_mans_val, textChars_font_serif_red_6);                                   \
	renderText(text_4_level, textChars_font_serif_2_red_6);                                    \
	renderText(text_4_level_val, textChars_font_serif_red_6);                                  \
	/* render peasantometer/burnination meter (depending on their values) */                    \
	if (GM.burnination > 0) {                                                                   \
		renderSprite(sprite_burnination_meter_empty);                                          \
		renderSprite(sprite_burnination_meter_full);                                           \
	} else {                                                                                    \
		sprite_peasantometer_icon.dstrect.x = sprite_peasantometer_icon_init_x;                 \
		sprite_peasantometer_icon.srcrect.x = sprite_peasantometer_icon.srcrect.w;              \
		for (i = 0; i < 10; i++) {                                                              \
			if (GM.peasantometer == i) {                                                        \
				sprite_peasantometer_icon.srcrect.x = 0;                                        \
			}                                                                                   \
			renderSprite(sprite_peasantometer_icon);                                           \
			sprite_peasantometer_icon.dstrect.x += (int)(sprite_peasantometer_icon.dstrect.w * 1.5); \
		}                                                                                       \
	}

#endif