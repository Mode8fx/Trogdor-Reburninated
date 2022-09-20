#include "cutscenes.h"

CutsceneObject cutscene_level_4_peasant;
CutsceneObject cutscene_level_4_trogdor;
CutsceneObject cutscene_level_4_trogdor_fire;
CutsceneObject cutscene_level_4_knight_1;
CutsceneObject cutscene_level_4_knight_2;

SpriteObject *spritePtr;

void InitializeCutsceneObjects() {
	prepareCSO(&cutscene_level_4_peasant, &sprite_peasant);
	prepareCSO(&cutscene_level_4_trogdor, &sprite_trogdor);
	prepareCSO(&cutscene_level_4_trogdor_fire, &sprite_trogdor_fire);
	prepareCSO(&cutscene_level_4_knight_1, &sprite_knight);
	prepareCSO(&cutscene_level_4_knight_2, &sprite_knight);
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
	updateCSOFrame(csObj, frame);
	updateCSOForm(csObj, form);
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
				updateCSOFrame(csObj, (csObj->animFrame + 1) % csObj->sprite->numAnimFrames);
			}
		}
	}
}

void updateCSOFrame(CutsceneObject *csObj, Sint8 frame) {
	csObj->animFrame = frame;
	csObj->srcrect.x = spriteFrame(*csObj->sprite, csObj->animFrame);
}

void updateCSOForm(CutsceneObject *csObj, Sint8 form) {
	csObj->animForm = form;
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
		case 427:
			enterCSO(&cutscene_level_4_knight_1, 241, 75, 0, 0, 4, -7, 0);
			break;
		case 431:
			enterCSO(&cutscene_level_4_knight_2, 240, 86, 1, 0, 4, -7, 0);
			break;
		case 448:
			enterCSO(&cutscene_level_4_peasant, 24, 81, 0, 2, 0, 0, 0);
			break;
		case 449:
			enterCSO(&cutscene_level_4_trogdor, 25, 70, 0, 1, 0, 8, 0);
			enterCSO(&cutscene_level_4_trogdor_fire, 63, 78, 0, 1, 0, 8, 0);
			updateCSOFrame(&cutscene_level_4_knight_1, 0);
			updateCSOFrame(&cutscene_level_4_knight_2, 0);
			break;
		case 450:
			enterCSO(&cutscene_level_4_knight_1, 101, 75, 4, 1, 4, 8, 0);
			enterCSO(&cutscene_level_4_knight_2, 130, 86, 4, 1, 4, 8, 0);
			break;
		case 453:
			updateCSOFrame(&cutscene_level_4_knight_1, 5);
			cutscene_level_4_knight_1.animFrameCounter = 0;
			updateCSOFrame(&cutscene_level_4_knight_2, 5);
			cutscene_level_4_knight_2.animFrameCounter = 0;
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
	renderCSO(&cutscene_level_4_trogdor_fire);
	renderCSO(&cutscene_level_4_knight_1);
	renderCSO(&cutscene_level_4_knight_2);
}