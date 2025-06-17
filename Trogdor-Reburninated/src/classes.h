#include "include.h"
#include "sprite_objects.h"
#include "sound_logic.h"
#include "window.h"

#ifndef CLASSES_H
#define CLASSES_H

constexpr auto MAX_NUM_HUTS = 6;
constexpr auto MAX_NUM_ARROWS = 5;
#define archerR archerArray[0]
#define archerL archerArray[1]
constexpr auto MAX_NUM_KNIGHTS = 2;
constexpr auto MAX_NUM_PEASANTS = 7;
constexpr auto MAX_NUM_LOOT = 7;

#define SB_VOICE_MULT ((float)MENU_COMMENT_FREQ->index / 3)

#if defined(SDL1)
inline bool SDL_HasIntersection(const SDL_Rect *A, const SDL_Rect *B);
#endif

// FrameState class is in general.h

class Cottage {
	public:
		FrameState frameState;
		SpriteInstance sprite;
		SpriteInstance sprite_fire;
		bool burning;
		bool burned;
		Sint16 direction;
		Cottage();
		Cottage(Sint16, Sint16, Sint16);
		void updateFrameState();
};

class Knight {
	public:
		FrameState anim_frameState;
		FrameState move_frameState;
		bool moving;    // used in toggleKnightMotion()
		SpriteInstance sprite;
		Sint16 half_src_w;
		Sint16 half_src_h;
		Sint8 direction;
		float home_x;   // the parent (x,y) coordinates
		float home_y;   // the parent (x,y) coordinates
		float offset_x; // the offset relative to home
		float offset_y; // the offset relative to home
		float moveFrameCap;
		float offsetConst;
		Knight();
		Knight(Sint16, Sint16, Sint8, bool, float);
		inline void updateCollision();
		void updateHome(float);
		void updateFrameState();
		void move(float);
		void move_alt(float, float, float);
};

class Peasant {
	public:
		FrameState frameState;
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
		float timer;
		Peasant();
		void updateFrameState();
};

class Archer {
	public:
		FrameState frameState;
		SpriteInstance sprite; // facing right == on the left; facing left == on the right
		Archer();
		Archer(Sint16, Sint16, bool);
		void updateFrameState();
};

class Arrow {
	public:
		FrameState frameState;
		SpriteInstance sprite;
		Arrow();
		Arrow(Sint16, Sint16, bool);
		void updateFrameState(Sint8);
		void clear();
};

class Loot {
	public:
		SpriteInstance sprite;
		Loot();
		Loot(Sint16, Sint16);
};

class Trogdor {
	public:
		FrameState frameState;
		SpriteInstance sprite;
		FrameState fire_frameState;
		SpriteInstance sprite_fire;
		SpriteInstance sprite_death;
		SpriteInstance sprite_end_of_level;
		float spawnPos_x;
		float spawnPos_y;
		float invince;        // remaining invincibility time (after respawn)
		Sint8 x_offset;       // used for movement
		Sint8 y_offset;       // used for movement
		Sint8 moveSpeed;      // used for movement
		Uint8 frameStateFlag; // used for movement
		SDL_Rect hutCollisionRect; // used for collision with huts
		Trogdor();
		Trogdor(bool, Sint8);
		void updateFrameState();
		void resetPos(bool);
		void updateBreathLoc();
		void invinceCheck();
};

class MenuManager {
	public:
		Sint8 contraIndex; // the current index of the Infinite/30 Lives cheat input
		Sint8 pacmanIndex; // the current index of the Debug Mode cheat input
		Sint8 s3kIndex;    // the current index of the Big Head cheat input
		Sint8 fzxIndex;    // the current index of the Start on Level 81 cheat input
		Sint8 dkcIndex;    // the current index of the Noclip cheat input
		Sint8 page;        // the current page number
		Sint8 maxPageNum;  // maxPageNum
		bool continueHighlighted; // the cursor index on the Continue screen
		SpriteInstance cursor;
		MenuManager();
		bool handleCheat(Uint8, const Uint8 *, Uint8, Sint8 &, SoundEffect *, Sint8);
		void unlockCheat(Uint8, Sint8);
		void typeStuff();
		void handlePageChange();
};

class GameManager {
	public:
		bool initialized;                       // whether or not a game has ever been initialized
		bool forceMusicStart;                   // whether or not music should be forced to play (this is needed for levels that shouldn't restart music upon init)
		bool infiniteLives;                     // infinite lives cheat
		Sint16 mans;                            // lives
		Uint32 score;                           // score
		Sint8 peasantometer;                    // # of peasants burned for burnination meter
		bool paused;                            // game is paused through any means (clearing a level, dying, etc.)
		bool startDown;                         // bool used for pausing
		bool manually_paused;                   // game is paused by the player
		bool gameOver;                          // game is over
		Uint8 level;                            // current level
		Uint8 levelIndex;                       // current level index (determined by level)
		float burnination;                      // amount of time left in burnination state
		Uint16 archerFrequency;                 // frequency at which archers appear
		Sint8 archerFrequencySetting;           // setting for archer frequency
		Sint8 arrowSpeedSetting;                // arrow speed setting
		Sint8 arrowSpeed;                       // speed of arrows
		float burnRate;                         // rate at which the burnination meter decreases
		Arrow arrowArrayL[MAX_NUM_ARROWS];      // array of Arrow objects (facing left, firing from right to left)
		Arrow arrowArrayR[MAX_NUM_ARROWS];      // array of Arrow objects (facing right, firing from left to right)
		Cottage hutArray[MAX_NUM_HUTS];         // array of Cottage objects
		Uint8 numHuts;                          // the number of huts
		Peasant peasantArray[MAX_NUM_PEASANTS]; // array of Peasant objects
		Knight knightArray[MAX_NUM_KNIGHTS];    // array of Knight objects
		Archer archerArray[2];                  // array of Archer objects
		Trogdor player;                         // the player
		Sint8 knightSpeedSetting;               // knight speed setting
		float knightSpeed;                      // knight speed
		float knightIncrement;                  // knight movement speed
		float knightIncrement_alt;              // knight movement speed (alt behavior)
		float knightIncrement_alt_2;            // knight movement speed (alt behavior, 0.8x speed)
		Sint8 livesIntervalSetting;             // setting for lives interval
		Uint16 extraMansBreak;                  // # of points for an extra life
		Uint16 extraMansCounter;                // how many extra lives have been earned so far + 1
		Uint16 maxExtraMans;                    // how many extra lives are allowed to be earned
		bool arched;                            // previous death was to arrow
		SpriteInstance sprite_dm;               // Death Message ("SWORDED!", "ARROWED!")
		FrameState dm_frameState;               // Death Message ("SWORDED!", "ARROWED!")
		FrameState b_frameState;                // BURNINATE! Message
		SpriteInstance sprite_bt;               // BURNINATE! Message Text
		SpriteInstance sprite_bf;               // BURNINATE! Message Fire
		bool b_visible;                         // BURNINATE! Message
		SpriteInstance sprite_bmFull;           // burnination meter
		SpriteInstance sprite_pm_on;            // peasantometer (on)
		SpriteInstance sprite_pm_off;           // peasantometer (off)
		FrameState kick_frameState;             // kick the machine
		bool treasureHutFound;                  // treasure hut has been found in this level
		bool inTreasureHut;                     // player is currently in treasure hut
		Sint16 treasureHutIndex;                // index of hut that contains treasure (0 = no treasure hut)
		Sint8 treasureHutLevel;                 // the level index of the first treasure hut you entered; default is 0
		Sint16 store_x;                         // old player X position (used for treasure huts)
		Sint16 store_y;                         // old player Y position (used for treasure huts)
		float treasureHut_timer;                // remaining time in treasure hut
		Loot lootArray[MAX_NUM_LOOT];           // array of Loot objects
		//float sbVoiceMult;                    // a multiplier for how often Strong Bad talks
		//bool bigHeadMode;                     // big head mode
		Sint8 speedyMode;                       // speedy mode
		bool debugMode;                         // debug mode
		bool noclip;                            // noclip cheat to walk through cottages
		bool peasantPenalty;                    // peasant penalty setting is enabled
		Sint8 treasureHutSetting;               // treasure hut setting
		Sint8 preset;                           // difficulty preset
		bool shuffleLevels;                     // the setting for shuffelling levels
		Uint8 levelIndices[33];                 // used for "Shuffle Levels" setting
		Uint32 randomSeed;                      // random seed used for several things; saved for level shuffling
		GameManager();
		GameManager(MenuManager);
		void resetAllSrcRects();
		void setArcherFrequency();
		void setBurnRate();
		void updateKnightIncrement();
		void setMusic();
		void levelInit();
		void set_level_background(Sint16);
		void getPlayerInput();
		inline void trogdor_add_x_delta(Sint8);
		inline void trogdor_add_y_delta(Sint8);
		inline void handle_treasure_hut_entry(Trogdor *, Sint8, Sint8);
		void handle_treasure_hut();
		// This has to be part of GM and not Trogdor since it references GM (and GameManager references Trogdor, so it would be circular)
		void playerMove(Trogdor *, Sint8, Sint8);
		void playerMove_treasureHut(Trogdor *, Sint8, Sint8);
		void popArchers();
		void updateArchersAndArrows();
		void updateKnightHome();
		void updateKnightOffsetAndMove();
		void testKnightHit();
		void arrowHitEventHandler();
		inline void toggleKnightMotion(bool);
		bool testWon();
		void updateScore(Uint16);
		inline void updateMans(Sint8);
		void setMans(Sint8);
		void updateLevel(Sint8);
		void clearArrows();
		void testBurnHut();
		void updateBurnmeter();
		inline void peasant_set_x_delta(Sint16);
		inline void peasant_set_y_delta(Sint16);
		inline void peasant_add_x_delta(Sint8);
		inline void peasant_add_y_delta(Sint8);
		void popPeasants();
		void peasantEatTest();
		void peasantTimerClick();
		void testBurnPeasant();
		void dm_updateFrameState();
		void b_updateFrameState();
		void kick_updateFrameState();
		void burninationIncreaseCheat();
		void burninationDecreaseCheat();
		void handleDebugCheat();
		void testLootHit();
		void renderAndAnimateCottages();
		void renderArchers();
		void renderArrows();
		void renderLoot();
		void renderKnights();
		void renderPeasants();
		void renderTrogdor();
		void setBurnination(float);
		void renderTopBar();
		void saveGameState_autosave();
};

extern MenuManager MM;
extern GameManager GM;

#endif