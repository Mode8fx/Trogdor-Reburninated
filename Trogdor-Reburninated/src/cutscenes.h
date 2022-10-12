#ifndef CUTSCENES_H
#define CUTSCENES_H

#include "sprite_objects.h"

struct CutsceneObject {
	SpriteObject *sprite;
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	double x_actual;
	double y_actual;
	bool isVisible = false;
	double velocity_x;
	double velocity_y;
	Sint8 animFrame;
	Sint8 animForm;
	Sint8 animFrameTime;
	Uint8 animFrameCounter;
	Sint8 animFormTime;
	Uint8 animFormCounter;
};

extern void InitializeCutsceneObjects();
extern void prepareCSO(CutsceneObject *, SpriteObject *);
extern void enterCSO(CutsceneObject *, int, int, Sint8, Sint8, Sint8, Sint8, double, double);
extern void renderCSO(CutsceneObject *);
extern void updateCSOFrame(CutsceneObject *, Sint8);
extern void updateCSOForm(CutsceneObject *, Sint8);
extern void setCSOPos(CutsceneObject *, int, int);
extern void cutscene_level_beaten();
extern void cutscene_level_4();
extern void cutscene_level_8();
extern void cutscene_level_12();
extern void cutscene_level_16();
extern void cutscene_level_20();
extern void cutscene_level_24();
extern void cutscene_level_30();
extern void cutscene_level_34();
extern void cutscene_level_38();
extern void cutscene_level_42();
extern void cutscene_level_46();
extern void cutscene_level_46_arrow_helper(CutsceneObject *, Sint16);
extern void cutscene_level_50();
extern void cutscene_level_100();

extern bool cutsceneIsPlaying;
extern Sint16 g_frameState;

#endif