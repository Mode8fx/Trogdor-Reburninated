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

#if defined(SDL1)
inline bool SDL_HasIntersection(const SDL_Rect *A, const SDL_Rect *B);
#endif

class Cottage {
	public:
		Uint8 frameState;
		SpriteInstance sprite;
		SpriteInstance sprite_fire;
		bool burning;
		bool burned;
		Sint16 direction;
		Cottage(Sint16, Sint16, Sint16);
		void updateFrameState();
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
		Knight(Sint16, Sint16, Sint8, bool);
		inline void updateCollision();
		void updateHome(Sint8);
		void updateFrameStateAndMove();
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
		Peasant();
		void updateFrameState(double);
};

class Archer {
	public:
		Uint8 frameState;
		SpriteInstance sprite; // facing right == on the left; facing left == on the right
		Archer(Sint16, Sint16, bool);
		void updateFrameState();
};

class Arrow {
	public:
		Uint8 frameState;
		SpriteInstance sprite;
		Arrow(Sint16, Sint16, bool);
		void updateFrameState();
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
		Uint8 frameState;
		SpriteInstance sprite;
		Uint8 fire_frameState;
		SpriteInstance sprite_fire;
		SpriteInstance sprite_death;
		SpriteInstance sprite_end_of_level;
		double spawnPos_x;
		double spawnPos_y;
		Sint8 invince;        // remaining invincibility time (after respawn)
		Sint8 x_offset;       // used for movement
		Sint8 y_offset;       // used for movement
		Sint8 moveSpeed;      // used for movement
		Uint8 frameStateFlag; // used for movement
		Trogdor(bool);
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
		MenuManager();
		bool handleCheat(Uint8, const Uint8 *, Uint8, Sint8 &, SoundEffect *);
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
		double burnination;                     // amount of time left in burnination state
		Uint16 archerFrequency;                 // frequency at which archers appear
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
		Uint16 extraMansCounter;                // how many extra lives have been earned so far + 1
		Uint16 maxExtraMans;                    // how many extra lives are allowed to be earned
		bool arched;                            // previous death was to arrow
		SpriteInstance sprite_dm;               // Death Message ("SWORDED!", "ARROWED!")
		Uint8 dm_frameState;                    // Death Message ("SWORDED!", "ARROWED!")
		Uint8 b_frameState;                     // BURNINATE! Message
		SpriteInstance sprite_bt;               // BURNINATE! Message Text
		SpriteInstance sprite_bf;               // BURNINATE! Message Fire
		bool b_visible;                         // BURNINATE! Message
		SpriteInstance sprite_bmFull;           // burnination meter
		SpriteInstance sprite_pm_on;            // peasantometer (on)
		SpriteInstance sprite_pm_off;           // peasantometer (off)
		Uint8 kick_frameState;                  // kick the machine
		bool treasureHutFound;                  // treasure hut has been found in this level
		bool inTreasureHut;                     // player is currently in treasure hut
		Sint16 treasureHutIndex;                // index of hut that contains treasure (0 = no treasure hut)
		Sint8 treasureHutLevel;                 // the level index of the first treasure hut you entered; default is 0
		Sint16 store_x;                         // old player X position (used for treasure huts)
		Sint16 store_y;                         // old player Y position (used for treasure huts)
		Sint16 treasureHut_timer;               // remaining time in treasure hut
		Loot lootArray[MAX_NUM_LOOT];           // array of Loot objects
		double sbVoiceMult;                     // a multiplier for how often Strong Bad talks
		bool bigHeadMode;                       // big head mode
		bool debugMode;                         // debug mode
		bool noclip;                            // noclip cheat to walk through cottages
		GameManager();
		GameManager(MenuManager);
		void resetAllSrcRects();
		void setArcherFrequency();
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
		void setBurnination(double);
		void renderTopBar();
};

extern MenuManager MM;
extern GameManager GM;

#endif