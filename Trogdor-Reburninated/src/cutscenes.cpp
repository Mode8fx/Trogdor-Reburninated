#include "cutscenes.h"

CutsceneObject cutscene_level_4_peasant;
CutsceneObject cutscene_level_4_trogdor;

SpriteObject *spritePtr;

void InitializeCutsceneObjects() {
	prepareCSO(&cutscene_level_4_peasant, &sprite_peasant);
	prepareCSO(&cutscene_level_4_trogdor, &sprite_trogdor);
}

void prepareCSO(CutsceneObject *csObj, SpriteObject *spriteObj) {
	csObj->sprite = spriteObj;
	csObj->srcrect.w = csObj->sprite->frame_w;
	csObj->srcrect.h = csObj->sprite->frame_h;
	csObj->dstrect.w = csObj->sprite->frame_w;
	csObj->dstrect.h = csObj->sprite->frame_h;
}

void enterCSO(CutsceneObject *csObj, int x, int y, Sint8 frame, Sint8 form) {
	setCSOPos(csObj, x, y);
	csObj->srcrect.x = spriteFrame(*csObj->sprite, frame);
	csObj->srcrect.y = spriteForm(*csObj->sprite, form);
	csObj->isVisible = true;
}

void renderCSO(CutsceneObject csObj) {
	if (csObj.isVisible) {
		renderSprite_game(*csObj.sprite, csObj.srcrect, csObj.dstrect);
	}
}

void setCSOFrame(CutsceneObject *csObj, Sint8 frame) {
	csObj->srcrect.x = spriteFrame(*csObj->sprite, frame);
}

void setCSOForm(CutsceneObject *csObj, Sint8 form) {
	csObj->srcrect.y = spriteForm(*csObj->sprite, form);
}

void setCSOPos(CutsceneObject *csObj, int x, int y) {
	csObj->dstrect.x = x;
	csObj->dstrect.y = y;
}

void cutscene_level_4() {
	switch (frameState) {
		case 420:
			cutsceneIsPlaying = true;
			loadAndPlaySound(SFX_CUTSCENE);
			enterCSO(&cutscene_level_4_peasant, 21, 82, 1, 0);
			break;
		case 448:
			enterCSO(&cutscene_level_4_peasant, 24, 81, 0, 2);
			break;
		case 492:
			cutsceneIsPlaying = false;
			break;
		default:
			break;
	}
	renderText(text_11_cutscene, font_serif_white_9);
	renderCSO(cutscene_level_4_peasant);
}