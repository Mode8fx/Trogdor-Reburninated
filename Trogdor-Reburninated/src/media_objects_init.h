#include "config.h"
#include "sprite_objects.h"
#include "text_objects.h"
#include "sound_logic.h"

#ifndef MEDIA_OBJECTS_INIT_H
#define MEDIA_OBJECTS_INIT_H

extern void InitializeFontsAndText();
extern void InitializeText_HomeScreen();
extern void InitializeText_Cutscenes();
extern void InitializeText_PauseScreen();
extern void InitializeText_OptionsMenu(FontObject *);
extern void InitializeMusic();
extern void InitializeSFX();
extern void InitializeSpritesPart1();
extern void InitializeSpritesPart2();
extern void exceptMissingFile(const char *);
extern void destroySprite(SpriteObject);
extern void destroyAllSprites();
extern void destroyTextChars(TextCharObject, Uint8);
extern void destroyAllTextChars();
extern void closeAllFonts();
extern void quickErrorTextRender_1(const char *, double);
extern void quickErrorTextRender_2(const char *, double);
extern void HandleErrorText(const char *);

#endif