#include "include.h"
#include "sprite_objects.h"

#ifndef CUTSCENES_H
#define CUTSCENES_H

extern bool cutsceneIsPlaying;
extern Uint8 sound_channel_level_beaten;

extern void InitializeCutsceneObjects();
extern void InitializeCutsceneObjects_trogdor();
extern void cutscene_level_beaten();
extern void cutscene_game_over();
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
extern void cutscene_level_46_arrow_helper(SpriteInstance *, Sint16);
extern void cutscene_level_50();
extern void cutscene_level_100();
extern void playCutscene(Uint8, Sint16, bool);

#endif