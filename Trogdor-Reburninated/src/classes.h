#ifndef CLASSES_H
#define CLASSES_H

#include "config.h"
#include "general.h"
#include "input.h"
#include "level_data.h"
#include "media_objects_init.h"
#include "sound_logic.h"
#include "sprite_objects.h"

// for all "directions": 1 = up, 2 = down, 3 = left, 4 = right

#define LEFT_BOUND_TROG    -2 //  17 - (39 / 2)
#define RIGHT_BOUND_TROG  214 // 233 - (39 / 2)
#define UPPER_BOUND_TROG    7 //  30 - (46 / 2)
#define LOWER_BOUND_TROG  132 // 155 - (46 / 2)
#define ARCHER_Y_UPPER     20 //  30 - (20 / 2)
#define ARCHER_Y_LOWER    145 // 155 - (20 / 2)
#define ARCHER_LEFT_X      -1 //  179 / 5000 * 250 - (20 / 2)
#define ARCHER_RIGHT_X    231 // 4829 / 5000 * 250 - (20 / 2)

extern Uint16 rand_var;
extern Uint32 frameCounter_global;

#if defined(SDL1)
inline bool SDL_HasIntersection(const SDL_Rect *A, const SDL_Rect *B) {
	return (!((A->x + A->w < B->x) || (B->x + B->w < A->x) || (A->y + A->h < B->y) || (B->y + B->h < A->y)));
}
#endif

#define MAX_NUM_HUTS   6
#define MAX_NUM_ARROWS 5
#define archerR archerArray[0]
#define archerL archerArray[1]

class Cottage {
	public:
		Uint8 frameState;
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		SDL_Rect fire_srcrect;
		SDL_Rect fire_dstrect;
		bool burning;
		bool burned;
		Sint8 direction;
		SDL_Rect collision;
		Cottage(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 1) {
			frameState = 9;
			srcrect = { 0, (dir - 1) * sprite_cottage.dstrect.h, sprite_cottage.dstrect.w, sprite_cottage.dstrect.h };
			dstrect = { pos_x, pos_y, sprite_cottage.dstrect.w, sprite_cottage.dstrect.h };
			fire_srcrect = { 0, 0, sprite_cottage_fire.dstrect.w, sprite_cottage_fire.dstrect.h };
			fire_dstrect.x = dstrect.x + 5;
			fire_dstrect.y = dstrect.y - 5;
			fire_dstrect.w = sprite_cottage_fire.dstrect.w;
			fire_dstrect.h = sprite_cottage_fire.dstrect.h;
			burning = false;
			burned = false;
			direction = dir;
			switch (direction) {
				case 1:
					collision = { 8 + dstrect.x, 15 + dstrect.y, 23, 12 };
					break;
				case 2:
					collision = { 8 + dstrect.x, 16 + dstrect.y, 23, 12 };
					break;
				case 3:
					collision = { 12 + dstrect.x, 14 + dstrect.y, 22, 13 };
					break;
				case 4:
					collision = { 7 + dstrect.x, 15 + dstrect.y, 25, 12 };
					break;
				default:
					collision = { 8 + dstrect.x, 16 + dstrect.y, 23, 12 };
					break;
			}
		}
		void updateFrameState() {
			frameState++;
			if (frameState == 10) {
				Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_burn_hut, 0);
			}
			if (frameState >= 12 && frameState <= 28) {
				fire_srcrect.x = (((frameState - 12) / 3) % 4) * sprite_cottage_fire.dstrect.w; // TODO: flames should be flipped horizontally if direction == 3
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
		Sint16 x;
		Sint16 y;
		Sint8 direction;
		Knight(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 1) {
			frameState = 0;
			x = pos_x;
			y = pos_y;
			direction = dir;
		}
};

class Peasant {
	public:
		Uint8 frameState;
		Sint16 x;
		Sint16 y;
		bool active;
		Sint8 myHome;
		bool stomped;
		bool waiting;
		bool burning;
		Uint32 myStart; // TODO: no idea what this is yet
		Sint8 myStartx;
		Sint8 myStarty;
		Sint8 direction;
		Sint8 myTargetx;
		Sint8 myTargety;
		bool returning;
		Sint16 timer;
		Peasant(Sint16 pos_x = 0, Sint16 pos_y = 0) {
			frameState = 0;
			x = pos_x;
			y = pos_y;
			active = false;
			myHome = 0;
			stomped = false;
			waiting = false;
			burning = false;
			myStart = 999; // TODO: no idea what this is yet
			myStartx = 0;
			myStarty = 0;
			direction = 2;
			myTargetx = 0;
			myTargety = 0;
			returning = false;
			timer = 0;
		}
		void Squish() {
			rand_var = rand() % 1000;
			if (rand_var < 0.003) {
				Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sb2, 0);
			} else if (rand_var < 0.006) {
				Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sbsquish1, 0);
			} else if (rand_var < 0.01) {
				Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sbsquish2, 0);
			}
		}
		void Despawn() {
			active = false;
			stomped = false;
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
			collision = { 1 + facingRight, 1, 12, 3 };
		}
		void updateFrameState() {
			frameState++;
			if (frameState == 1) { // 4?
				Mix_PlayChannel(SFX_CHANNEL_GAME, sfx_arrow, 0);
			}
			if (facingRight) {
				dstrect.x += 5;
				if (dstrect.x > 250) { // not exactly the same as the original, but close enough
					clear();
				}

			} else {
				dstrect.x -= 5;
				if (dstrect.x < -8) { // not exactly the same as the original, but close enough
					clear();
				}
			}
		}
		void clear() {
			active = false;
			dstrect.x = -500;
		}
};

class Trogdor {
	public:
		Uint8 frameState;
		SDL_Rect srcrect;
		SDL_Rect dstrect;
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
			spawnPos_x = (Sint16)(2780.0 / 5000 * GAME_WIDTH) - (srcrect.w / 2);
			spawnPos_y = (Sint16)(2360.0 / 3600 * GAME_HEIGHT) - (srcrect.h / 2);
			dstrect = { spawnPos_x, spawnPos_y, sprite_trogdor.dstrect.w, sprite_trogdor.dstrect.h };
			collision = { 11 + dstrect.x, 11 + dstrect.y, 18, 24 };
			invince = 0;
			visible = true;
			srcrect.x = 0;
			srcrect.y = srcrect.h;
			x_offset = 0;
			y_offset = 0;
			moveSpeed = 3;
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

#define SET_BURNINATION(num)                                                                                         \
	burnination = num;                                                                                               \
	sprite_burnination_meter_full.srcrect.w = (int)(sprite_burnination_meter_empty.dstrect.w * burnination / 100.0); \
	sprite_burnination_meter_full.dstrect.w = sprite_burnination_meter_full.srcrect.w;

class GameManager {
	public:
		Sint8 mans;                     // lives
		Uint32 score;                   // score
		Sint8 peasantometer;            // # of peasants burned for burnination meter
		bool paused;                    // game is paused through any means (clearing a level, dying, etc.)
		bool startDown;                 // bool used for pausing
		bool manually_paused;           // game is paused by the player
		bool gameOver;                  // game is over
		Uint8 level;                    // current level
		Uint8 levelIndex;               // current level index (determined by level)
		double burnination;             // amount of time left in burnination state
		double archerFrequency;         // frequency at which archers appear
		double burnRate;                // rate at which the burnination meter decreases
		Arrow arrowArrayL[5];           // array of Arrow objects (facing left, firing from right to left)
		Arrow arrowArrayR[5];           // array of Arrow objects (facing right, firing from left to right)
		Cottage hutArray[6];            // array of Cottage objects
		Peasant peasantArray[7];        // array of Peasant objects
		Knight knightArray[2];          // array of Knight objects
		Archer archerArray[2];          // array of Archer objects
		Trogdor player;                 // the player
		GameManager() {
		}
		GameManager(Sint8 init_mans) {
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
			switch (levels[levelIndex][0]) {
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
				default:
					sprite_level_background = &sprite_level_background_1;
					break;
			}
			for (i = 0; i < MAX_NUM_HUTS; i++) {
				j = (i * 3) + 2;
				if (levels[levelIndex][j] > 0) {
					hutArray[i] = Cottage(
						OBJ_TO_SCREEN_AT_FRACTION_X(sprite_cottage, (levels[levelIndex][j + 1] + 2466) / 5000.0) + 8,
						OBJ_TO_SCREEN_AT_FRACTION_Y(sprite_cottage, (levels[levelIndex][j + 2] + 2183) / 3600.0) - 11,
						levels[levelIndex][j]
					);
					PRINT("COTTAGE INFO:");
					PRINT((int)hutArray[i].direction);
					PRINT((int)hutArray[i].dstrect.x);
					PRINT((int)hutArray[i].dstrect.y);
				} else {
					hutArray[i] = Cottage(0, 0, 0);
					hutArray[i].burned = true;
				}
			}
			// level data should be stored in a binary file
			for (i = 0; i < LEN(arrowArrayL); i++) {
				arrowArrayL[i] = Arrow(0, 0, false);
			}
			for (i = 0; i < LEN(arrowArrayR); i++) {
				arrowArrayR[i] = Arrow(0, 0, true);
			}
			for (i = 0; i < LEN(peasantArray); i++) {
				peasantArray[i] = Peasant(0, 1);
			}
			for (i = 0; i < LEN(knightArray); i++) {
				knightArray[i] = Knight(0, 0, 1);
			}
			archerArray[0] = Archer(ARCHER_LEFT_X, 0, true);   // archerR (on the left, facing right)
			archerArray[1] = Archer(ARCHER_RIGHT_X, 0, false); // archerL (on the right, facing left)
			peasantometer = 0;
			player.dstrect.x = player.spawnPos_x;
			player.dstrect.y = player.spawnPos_y;
			player.collision = { 11 + player.dstrect.x, 11 + player.dstrect.y, 18, 24 };
			player.facingRight = true;
		}
		void getPlayerInput() {
			player.x_offset = 0;
			player.y_offset = 0;
			player.frameStateFlag = 0;
			if (KEY_HELD(INPUT_UP)) {
				player.frameStateFlag |= 1;
				player.y_offset = -player.moveSpeed;
			}
			if (KEY_HELD(INPUT_DOWN)) {
				player.frameStateFlag |= 1;
				player.y_offset = player.moveSpeed;
			}
			if (KEY_HELD(INPUT_LEFT)) {
				if (!player.facingRight) {
					player.frameStateFlag |= 1;
				} else {
					player.frameStateFlag |= 2;
					player.facingRight = false;
				}
				player.x_offset = -player.moveSpeed;
			}
			if (KEY_HELD(INPUT_RIGHT)) {
				if (player.facingRight) {
					player.frameStateFlag |= 1;
				} else {
					player.frameStateFlag |= 2;
					player.facingRight = true;
				}
				player.x_offset = player.moveSpeed;
			}
			playerMove(&player, player.x_offset, player.y_offset);
			if (KEY_HELD(INPUT_START)) {
				startDown = true;
			}
			if (startDown && !KEY_HELD(INPUT_START)) {
				startDown = false;
				manually_paused = frameCounter_global;
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
		// This has to be part of GM and not Trogdor since it references GM (and GameManager references Trogdor, so it would be circular)
		void playerMove(Trogdor *trog, Sint8 delta_x, Sint8 delta_y) {
			// TODO: Pretty much everything in this function
			// X movement
			if (delta_x != 0) {
				trogdor_add_x_delta(delta_x);
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
		}
		void popArchers() {
			rand_var = rand() % 10000;
			if (rand_var < archerFrequency || KEY_PRESSED(INPUT_Y)) { // TODO: Remove KEY_PRESSED
				PRINT(rand_var);
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
							arrowArrayL[i].dstrect.x = archerL.dstrect.x + (archerL.dstrect.w / 2) - (arrowArrayR[i].dstrect.w / 2);
							arrowArrayL[i].dstrect.y = archerL.dstrect.y + (archerL.dstrect.h / 2) - (arrowArrayR[i].dstrect.h / 2);
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
		void updateKnight() {
			// TODO: All of this
		}
		void testBurnHut() {
			for (i = 0; i < MAX_NUM_HUTS; i++) {
				if (!hutArray[i].burning && KEY_PRESSED(INPUT_SELECT)) { // TODO: replace KEY_PRESSED(INPUT_SELECT) with breath.hitTest(hutArray[i])
					hutArray[i].burning = true;
					rand_var = rand() % 1000;
					if (rand_var < 0.05) {
						Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_sbdooj, 0);
					}
				}
			}
		}
		void burninationIncreaseTest() {
			if (peasantometer < 9) {
				peasantometer++;
			} else {
				peasantometer = 10;
				SET_BURNINATION(burnination + 1);
				if (burnination > 100) {
					SET_BURNINATION(100);
				}
			}
		}
		void burninationDecreaseTest() {
			if (peasantometer < 10) {
				peasantometer--;
				if (peasantometer < 0) {
					peasantometer = 0;
				}
			} else {
				SET_BURNINATION(burnination - 1);
				if (burnination <= 0) {
					SET_BURNINATION(0);
					peasantometer = 0;
				}
			}
		}
};

#define RENDER_AND_ANIMATE_UPPER_COTTAGES()                                                                               \
	for (i = 0; i < MAX_NUM_HUTS; i++) {                                                                                  \
		if (GM.hutArray[i].direction > 0 && GM.hutArray[i].dstrect.y < GM.player.dstrect.y + 9) {                         \
			if (GM.hutArray[i].burning && !GM.hutArray[i].burned) {                                                       \
				GM.hutArray[i].updateFrameState();                                                                        \
			}                                                                                                             \
			RENDER_SPRITE_USING_RECTS(sprite_cottage, GM.hutArray[i].srcrect, GM.hutArray[i].dstrect);                    \
			if (GM.hutArray[i].frameState >= 12 && GM.hutArray[i].frameState <= 28) {                                     \
				RENDER_SPRITE_USING_RECTS(sprite_cottage_fire, GM.hutArray[i].fire_srcrect, GM.hutArray[i].fire_dstrect); \
			}                                                                                                             \
		}                                                                                                                 \
	}

#define RENDER_AND_ANIMATE_LOWER_COTTAGES()                                                                               \
	for (i = 0; i < MAX_NUM_HUTS; i++) {                                                                                  \
		if (GM.hutArray[i].direction > 0 && GM.hutArray[i].dstrect.y >= GM.player.dstrect.y + 9) {                        \
			if (GM.hutArray[i].burning && !GM.hutArray[i].burned) {                                                       \
				GM.hutArray[i].updateFrameState();                                                                        \
			}                                                                                                             \
			RENDER_SPRITE_USING_RECTS(sprite_cottage, GM.hutArray[i].srcrect, GM.hutArray[i].dstrect);                    \
			if (GM.hutArray[i].frameState >= 12 && GM.hutArray[i].frameState <= 28) {                                     \
				RENDER_SPRITE_USING_RECTS(sprite_cottage_fire, GM.hutArray[i].fire_srcrect, GM.hutArray[i].fire_dstrect); \
			}                                                                                                             \
		}                                                                                                                 \
	}

#define RENDER_ARCHERS()                                                                  \
	if (GM.archerR.active) {                                                              \
		RENDER_SPRITE_USING_RECTS(sprite_archer, GM.archerR.srcrect, GM.archerR.dstrect); \
	}                                                                                     \
	if (GM.archerL.active) {                                                              \
		RENDER_SPRITE_USING_RECTS(sprite_archer, GM.archerL.srcrect, GM.archerL.dstrect); \
	}

#define RENDER_ARROWS()                                                                                    \
	for (i = 0; i < MAX_NUM_ARROWS; i++) {                                                                 \
		if (GM.arrowArrayR[i].active) {                                                                    \
			RENDER_SPRITE_USING_RECTS(sprite_arrow, GM.arrowArrayR[i].srcrect, GM.arrowArrayR[i].dstrect); \
		}                                                                                                  \
		if (GM.arrowArrayL[i].active) {                                                                    \
			RENDER_SPRITE_USING_RECTS(sprite_arrow, GM.arrowArrayL[i].srcrect, GM.arrowArrayL[i].dstrect); \
		}                                                                                                  \
	}

#endif