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

void enterCSO(CutsceneObject *csObj, int x, int y, Sint8 frame, Sint8 form, Sint8 frameTime, Sint8 vel_x, Sint8 vel_y) {
	setCSOPos(csObj, x, y);
	csObj->animFrame = frame;
	updateCSOFrame(csObj);
	csObj->animForm = form;
	updateCSOForm(csObj);
	csObj->animFrameTime = frameTime;
	csObj->animFrameCounter = 0;
	csObj->velocity_x = vel_x;
	csObj->velocity_y = vel_y;
	csObj->isVisible = true;
}

void renderCSO(CutsceneObject *csObj) {
	if (csObj->isVisible) {
		renderSprite_game(*csObj->sprite, csObj->srcrect, csObj->dstrect);
		csObj->dstrect.x += csObj->velocity_x;
		csObj->dstrect.y += csObj->velocity_y;
		if (csObj->animFrameTime > 0) {
			csObj->animFrameCounter++;
			while (csObj->animFrameCounter >= csObj->animFrameTime) {
				csObj->animFrameCounter -= csObj->animFrameTime;
				PRINT((int)csObj->animFrame);
				csObj->animFrame = (csObj->animFrame + 1) % csObj->sprite->numAnimFrames;
				updateCSOFrame(csObj);
			}
		}
	}
}

void updateCSOFrame(CutsceneObject *csObj) {
	csObj->srcrect.x = spriteFrame(*csObj->sprite, csObj->animFrame);
}

void updateCSOForm(CutsceneObject *csObj) {
	csObj->srcrect.y = spriteForm(*csObj->sprite, csObj->animForm);
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
			enterCSO(&cutscene_level_4_peasant, 21, 82, 1, 0, 0, 0, 0);
			enterCSO(&cutscene_level_4_trogdor, 246, 70, 0, 0, 0, -8, 0);
			break;
		case 448:
			enterCSO(&cutscene_level_4_peasant, 24, 81, 0, 2, 0, 0, 0);
			break;
		case 449:
			enterCSO(&cutscene_level_4_trogdor, 25, 70, 0, 1, 0, 8, 0);
			break;
		case 492:
			cutsceneIsPlaying = false;
			break;
		default:
			break;
	}
	renderText(text_11_cutscene, font_serif_white_9);
	renderCSO(&cutscene_level_4_peasant);
	renderCSO(&cutscene_level_4_trogdor);
}