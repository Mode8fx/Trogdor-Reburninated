#ifndef CUTSCENES_H
#define CUTSCENES_H

#include "sprite_objects.h"

struct CutsceneObject {
	SpriteObject *sprite;
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	bool isVisible = false;
};

extern void InitializeCutsceneObjects();
extern void prepareCSO(CutsceneObject *, SpriteObject *);
extern void enterCSO(CutsceneObject *, int, int, Sint8, Sint8);
extern void renderCSO(CutsceneObject);
extern void setCSOFrame(CutsceneObject *, Sint8);
extern void setCSOForm(CutsceneObject *, Sint8);
extern void setCSOPos(CutsceneObject *, int, int);
extern void cutscene_level_4();

extern bool cutsceneIsPlaying;
extern Sint16 frameState;

#endif