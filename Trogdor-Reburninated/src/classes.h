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

#define MAX_NUM_HUTS 6

extern Uint16 rand_var;

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
		}
		void updateFrameState() {
			frameState++;
			if (frameState == 10) {
				Mix_PlayChannel(SFX_CHANNEL_STRONG_BAD, sfx_burn_hut, 0);
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
		Sint16 x;
		Sint16 y;
		bool active;
		Sint8 direction;
		Archer(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 3) {
			frameState = 0;
			x = pos_x;
			y = pos_y;
			active = false;
			direction = dir;
		}
};

class Arrow {
	public:
		//Uint8 frameState;
		Sint16 x;
		Sint16 y;
		bool active;
		Sint8 direction;
		Arrow(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 3) {
			//frameState = 0;
			x = pos_x;
			y = pos_y;
			active = false;
			direction = dir;
		}
};

#define UPDATE_PLAYER_SPRITE_X() \
	sprite->srcrect.x = (frameState / 2) * sprite->srcrect.w;

#define UPDATE_PLAYER_SPRITE_Y() \
	sprite->srcrect.y = facingRight * sprite->srcrect.h;

class Trogdor {
	public:
		Uint8 frameState;
		bool facingRight;
		// Trogdor is 43x47
		SDL_Rect hitboxRect;
		Sint16 spawnPos_x;
		Sint16 spawnPos_y;
		SpriteObject *sprite; // includes position via dstrect
		Sint8 x_offset;       // used for movement
		Sint8 y_offset;       // used for movement
		Sint8 moveSpeed;      // used for movement
		Uint8 frameStateFlag; // used for movement
		Trogdor() {
		}
		Trogdor(SpriteObject &s) {
			frameState = 0;
			facingRight = true;
			hitboxRect = { 13, 11, 18, 25 }; // TODO: this should change depending on frame...
			spawnPos_x = (Sint16)(2780.0 / 5000 * GAME_WIDTH);
			spawnPos_y = (Sint16)(2360.0 / 3600 * GAME_HEIGHT);
			sprite = &s;
			UPDATE_PLAYER_SPRITE_X();
			UPDATE_PLAYER_SPRITE_Y();
			x_offset = 0;
			y_offset = 0;
			moveSpeed = 3;
		}
		void move(Sint8 delta_x, Sint8 delta_y) {
			// TODO: Pretty much everything in this function
			if (frameStateFlag & 2) {
				sprite->dstrect.x += delta_x;
				sprite->dstrect.y += delta_y;
				frameState = 0;
				UPDATE_PLAYER_SPRITE_X();
				UPDATE_PLAYER_SPRITE_Y();
			} else if (frameStateFlag & 1) {
				sprite->dstrect.x += delta_x;
				sprite->dstrect.y += delta_y;
				frameState = (++frameState % 8);
				UPDATE_PLAYER_SPRITE_X();
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
		bool manually_paused;           // game is paused by the player
		bool gameOver;                  // game is over
		Uint8 level;                    // current level
		Uint8 levelIndex;               // current level index (determined by level)
		double burnination;             // amount of time left in burnination state
		double archerFrequency;         // frequency at which archers appear
		double burnRate;                // rate at which the burnination meter decreases
		Sint8 invince;                  // remaining invincibility time (after respawn)
		Arrow arrowArrayL[5];           // array of Arrow objects (firing from right to left)
		Arrow arrowArrayR[5];           // array of Arrow objects (firing from left to right)
		Cottage hutArray[6];            // array of Cottage objects
		Peasant peasantArray[7];        // array of Peasant objects
		Knight knightArray[2];          // array of Knight objects
		Trogdor player;                 // the player
		GameManager() {
		}
		GameManager(SpriteObject &s_trogdor, Sint8 init_mans) {
			mans = init_mans;
			score = 0;
			peasantometer = 0;
			paused = false;
			manually_paused = false;
			gameOver = false;
			level = 1;
			levelIndex = 1;
			SET_BURNINATION(0);
			archerFrequency = 0;
			burnRate = 0;
			invince = 0;
			player = Trogdor(s_trogdor);
			player.facingRight = true;
		}
		void levelInit() {
			SET_BURNINATION(0);
			if (level > 25) {
				archerFrequency = 4;
				burnRate = 1.3;
			} else if (level > 20) {
				archerFrequency = 2;
				burnRate = 1.2;
			} else if (level > 15) {
				archerFrequency = 0.8;
				burnRate = 1.1;
			} else if (level > 10) {
				archerFrequency = 0.6;
				burnRate = 1;
			} else if (level > 5) {
				archerFrequency = 0.4;
				burnRate = 0.9;
			} else {
				archerFrequency = 0.2;
				burnRate = 0.7;
			}
			invince = 0;
			// TODO: load level ((level - 2) % 32 + 2) here
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
						OBJ_TO_SCREEN_AT_FRACTION_X(sprite_cottage, (levels[levelIndex][j + 1] + 2466) / 5000.0),
						OBJ_TO_SCREEN_AT_FRACTION_Y(sprite_cottage, (levels[levelIndex][j + 2] + 2183) / 3600.0),
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
				arrowArrayL[i] = Arrow(0, 0, 3);
			}
			for (i = 0; i < LEN(arrowArrayR); i++) {
				arrowArrayR[i] = Arrow(0, 0, 4);
			}
			for (i = 0; i < LEN(peasantArray); i++) {
				peasantArray[i] = Peasant(0, 1);
			}
			for (i = 0; i < LEN(knightArray); i++) {
				knightArray[i] = Knight(0, 0, 1);
			}
			peasantometer = 0;
			player.sprite->dstrect.x = player.spawnPos_x;
			player.sprite->dstrect.y = player.spawnPos_y;
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
			player.move(player.x_offset, player.y_offset);
			// TODO: Handle pausing here
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
			SET_BURNINATION(burnination + 1);
			if (burnination > 100) {
				SET_BURNINATION(100);
			}
		}
		void burninationDecreaseTest() {
			SET_BURNINATION(burnination - 1);
			if (burnination < 0) {
				SET_BURNINATION(0);
			}
		}
};

#define RENDER_AND_ANIMATE_COTTAGES()                                                                                     \
	for (i = 0; i < MAX_NUM_HUTS; i++) {                                                                                  \
		if (GM.hutArray[i].direction > 0) {                                                                               \
			if (GM.hutArray[i].burning && !GM.hutArray[i].burned) {                                                       \
				GM.hutArray[i].updateFrameState();                                                                        \
			}                                                                                                             \
			RENDER_SPRITE_USING_RECTS(sprite_cottage, GM.hutArray[i].srcrect, GM.hutArray[i].dstrect);                    \
			if (GM.hutArray[i].frameState >= 12 && GM.hutArray[i].frameState <= 28) {                                     \
				RENDER_SPRITE_USING_RECTS(sprite_cottage_fire, GM.hutArray[i].fire_srcrect, GM.hutArray[i].fire_dstrect); \
			}                                                                                                             \
		}                                                                                                                 \
	}

#endif