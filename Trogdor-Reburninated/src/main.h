#ifndef MAIN_H
#define MAIN_H

#include "media_objects_init.h"

#define DESTROY_ALL()                                                                         \
	/* Destroy Everything and Quit Game */                                                    \
	/* Textures */                                                                            \
	/* Text Objects and Fonts */                                                              \
	DESTROY_AND_CLOSE_FONT(font_serif_brown_6, textChars_font_serif_brown_6);                 \
	DESTROY_AND_CLOSE_FONT(font_serif_brown_8, textChars_font_serif_brown_8);                 \
	DESTROY_AND_CLOSE_FONT(font_serif_gray_6, textChars_font_serif_gray_6);                   \
	DESTROY_AND_CLOSE_FONT(font_serif_gray_12, textChars_font_serif_gray_12);                 \
	DESTROY_AND_CLOSE_FONT(font_serif_orange_6, textChars_font_serif_orange_6);               \
	DESTROY_AND_CLOSE_FONT(font_serif_red_6, textChars_font_serif_red_6);                     \
	DESTROY_AND_CLOSE_FONT(font_serif_red_8, textChars_font_serif_red_8);                     \
	DESTROY_AND_CLOSE_FONT(font_serif_red_12, textChars_font_serif_red_12);                   \
	DESTROY_AND_CLOSE_FONT(font_serif_white_6, textChars_font_serif_white_6);                 \
	DESTROY_AND_CLOSE_FONT(font_serif_white_9, textChars_font_serif_white_9);                 \
	DESTROY_AND_CLOSE_FONT(font_serif_white_10, textChars_font_serif_white_10);               \
	DESTROY_AND_CLOSE_FONT(font_serif_white_14, textChars_font_serif_white_14);               \
	DESTROY_AND_CLOSE_FONT(font_nokia_12, textChars_font_nokia_12);                           \
	DESTROY_AND_CLOSE_FONT(font_serif_2_bold_black_23, textChars_font_serif_2_bold_black_23); \
	DESTROY_AND_CLOSE_FONT(font_serif_2_bold_red_23, textChars_font_serif_2_bold_red_23);     \
	DESTROY_AND_CLOSE_FONT(font_serif_2_red_6, textChars_font_serif_2_red_6);                 \
	DESTROY_AND_CLOSE_FONT(font_serif_2_red_13, textChars_font_serif_2_red_13);               \
	TTF_Quit();                                                                               \
	/* Sound */                                                                               \
	if (soundSettings.musicIndex != 0) {                             \
		Mix_FreeMusic(bgm);                                          \
	}                                                                \
	Mix_FreeChunk(sfx_trogador);                                     \
	Mix_CloseAudio();                                                \
	MIX_QUIT();                                                      \
	/* Controller */                                                 \
	CLOSE_CONTROLLER();                                              \
	/* Renderer and Window */                                        \
	DESTROY_DISPLAY();                                               \
	SDL_Quit();                                                      \
	SYSTEM_SPECIFIC_CLOSE();

#define DESTROY_AND_CLOSE_FONT(font, textChars) \
	for (i = 0; i < LEN(textChars); i++) {      \
		DESTROY_SPRITE(textChars[i]);           \
	}                                           \
	TTF_CloseFont(font);

#if !defined(WII) && !defined(GAMECUBE)
#define MIX_QUIT() Mix_Quit();
#else
#define MIX_QUIT()
#endif

#if !defined(SDL1)
#define DESTROY_SPRITE(sprite) \
	SDL_DestroyTexture(sprite.texture);
#define DESTROY_SPRITE_FRAME(frame) \
	SDL_DestroyTexture(frame);
#define CLOSE_CONTROLLER() \
	if (controller != NULL) {                \
		SDL_GameControllerClose(controller); \
	}
#define DESTROY_DISPLAY()          \
	SDL_DestroyRenderer(renderer); \
	SDL_DestroyWindow(window);
#else
#define DESTROY_SPRITE(sprite) \
	SDL_FreeSurface(sprite.surface);
#define DESTROY_SPRITE_FRAME(frame) \
	SDL_FreeSurface(frame);
#define CLOSE_CONTROLLER() \
	if (SDL_JoystickOpened(0)) {     \
		SDL_JoystickClose(joystick); \
	}
#define DESTROY_DISPLAY() \
	SDL_FreeSurface(screen);
#endif

#endif