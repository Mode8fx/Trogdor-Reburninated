#ifndef CLASSES_H
#define CLASSES_H

#include "config.h"
#include "general.h"
#include "input.h"
#include "media_objects_init.h"
#include "sound_logic.h"
#include "sprite_objects.h"

// for all "directions": 0 = up, 1 = down, 2 = left, 3 = right

class Cottage {
	public:
		Uint8 frameState;
		Sint16 x;
		Sint16 y;
		bool burning;
		bool burned;
		Sint8 direction;
		Cottage(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 0) {
			frameState = 0;
			x = pos_x;
			y = pos_y;
			burning = false;
			burned = false;
			direction = dir;
		}
};

class Knight {
	public:
		Uint8 frameState;
		Sint16 x;
		Sint16 y;
		Sint8 direction;
		Knight(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 0) {
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
			direction = 1;
			myTargetx = 0;
			myTargety = 0;
			returning = false;
			timer = 0;
		}
		void Squish() {
			Uint16 rand_var = rand() % 1000;
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
		Archer(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 2) {
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
		Arrow(Sint16 pos_x = 0, Sint16 pos_y = 0, Sint8 dir = 2) {
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
		double burnination;             // amount of time left in burnination state
		double archerFrequency;         // frequency at which archers appear
		double burnRate;                // rate at which the burnination meter decreases
		Sint8 invince;                  // remaining invincibility time (after respawn)
		Arrow arrowArrayL[5];           // array of Arrow objects (firing from right to left)
		Arrow arrowArrayR[5];           // array of Arrow objects (firing from left to right)
		Cottage hutArray[10];           // array of Cottage objects
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
			// level data should be stored in a binary file
			for (i = 0; i < LEN(arrowArrayL); i++) {
				arrowArrayL[i] = Arrow(0, 0, 2);
			}
			for (i = 0; i < LEN(arrowArrayR); i++) {
				arrowArrayR[i] = Arrow(0, 0, 3);
			}
			for (i = 0; i < LEN(hutArray); i++) {
				hutArray[i] = Cottage(0, 0, 2); // TODO: Get cottage data from level here
			}
			for (i = 0; i < LEN(peasantArray); i++) {
				peasantArray[i] = Peasant(0, 0);
			}
			for (i = 0; i < LEN(knightArray); i++) {
				knightArray[i] = Knight(0, 0, 0);
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

#endif