#include "on_open_and_close.h"
#include "config.h"
#include "window.h"
#include "sound_logic.h"
#include "input.h"
#include "general.h"
#include "sprite_objects.h"
#include "media_objects_init.h"

void InitializeDisplay() {
#if !defined(SDL1)
	SDL_GetCurrentDisplayMode(0, &DM);
#endif
	videoSettings.widthSetting = DEFAULT_WIDTH;
	videoSettings.heightSetting = DEFAULT_HEIGHT;
#if defined(ANDROID)
	SDL_SetHint(SDL_HINT_ORIENTATIONS, "Landscape");
#endif
	appWidth = 320;
	appHeight = 240;
	appSrcRect = { 0, 0, appWidth, appHeight };
	frameRate = DEFAULT_FRAME_RATE;
	ticksPerFrame = (Uint32)(1000 / frameRate);
	setWidthHeightMults();

	/* Set Window/Renderer */
#if defined(PSP)
	window = SDL_CreateWindow("Trogdor: Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, videoSettings.widthSetting, videoSettings.heightSetting, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#elif defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(XBOX)
	window = SDL_CreateWindow("Trogdor: Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, videoSettings.widthSetting, videoSettings.heightSetting, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#elif defined(WII) || defined(GAMECUBE) || defined(THREEDS)
	SDL_WM_SetCaption("Trogdor: Reburninated", NULL);
	windowScreen = SDL_SetVideoMode(videoSettings.widthSetting, videoSettings.heightSetting, 24, SDL_DOUBLEBUF);
#elif defined(SDL1)
	SDL_WM_SetCaption("Trogdor: Reburninated", NULL);
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
	windowScreen = SDL_SetVideoMode(videoSettings.widthSetting, videoSettings.heightSetting, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
#else
	window = SDL_CreateWindow("Trogdor: Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, videoSettings.widthSetting, videoSettings.heightSetting, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#endif
	setScaling();
}

void InitializeSound() {
#if defined(PSP)
	oslInitAudio();
#elif defined(XBOX)
#else
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
#if !defined(SDL1) && !defined(ANDROID)
		SDL_Log(Mix_GetError());
#endif
	}
	Mix_VolumeMusic((int)(soundSettings.bgmVolume * 128.0 / 100));
	Mix_AllocateChannels(NUM_SOUND_CHANNELS);
	Mix_Volume(SFX_CHANNEL_GAME, (int)(soundSettings.sfxVolume * 128.0 / 100));
	Mix_Volume(SFX_CHANNEL_STRONG_BAD, (int)(soundSettings.sfxVolume * 128.0 / 100));
#endif
}

void InitializeController() {
#if defined(SDL1) // also applies to PSP SDL1
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
#elif defined(PSP)
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	joystick = SDL_JoystickOpen(0);
#else
	for (i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			break;
		}
	}
#endif
}

void renderBackground() {
	outputRect = sprite_level_background->dstrect;
	outputRect.x = (Sint16)(outputRect.x * screenScale) + gameToWindowDstRect.x;
	outputRect.y = (Sint16)(outputRect.y * screenScale) + gameToWindowDstRect.y;
	outputRect.w = (int)(outputRect.w * screenScale);
	outputRect.h = (int)(outputRect.h * screenScale);
#if !defined(SDL1)
	SDL_RenderCopy(renderer, sprite_level_background->sub[0][0].texture, NULL, &outputRect);
#else
	SDL_BlitSurface(sprite_level_background->sub[0][0].surface, NULL, windowScreen, &outputRect);
#endif
}

void renderTransparentForeground() {
#if !defined(THREEDS)
	outputRect = gameToWindowDstRect;
#if !defined(SDL1)
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_RenderFillRect(renderer, &outputRect);
#else
	SDL_BlitSurface(transparentScreen, NULL, windowScreen, &outputRect);
#endif
#endif
}

void closeController() {
#if defined(PSP)
	SDL_JoystickClose(joystick);
#elif defined(SDL1)
	if (SDL_JoystickOpened(0)) {
		SDL_JoystickClose(joystick);
	}
#else
	if (controller != NULL) {
		SDL_GameControllerClose(controller);
	}
#endif
}

void destroyDisplay() {
#if !defined(SDL1)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
#else
	SDL_FreeSurface(windowScreen);
#endif
}

void DestroyAll() {
	/* Surfaces */
	destroyAllSprites();
	/* Text Chars */
	destroyAllTextChars();
	/* Sound */
	for (i = 0; i < NUM_SOUND_EFFECTS_SFX; i++) {
		if (sfxArr[i]->chunk != NULL) {
#if defined(PSP)
			oslDeleteSound(sfxArr[i]->chunk);
#elif defined(XBOX)
#else
			Mix_FreeChunk(sfxArr[i]->chunk);
#endif
		}
	}
	for (i = 0; i < NUM_SOUND_EFFECTS_STRONG_BAD; i++) {
		if (sfxArr_strongBad[i]->chunk != NULL) {
#if defined(PSP)
			oslDeleteSound(sfxArr_strongBad[i]->chunk);
#elif defined(XBOX)
#else
			Mix_FreeChunk(sfxArr_strongBad[i]->chunk);
#endif
		}
	}
#if defined(PSP)
	if (bgm != NULL) {
		oslDeleteSound(bgm);
	}
	oslDeinitAudio();
#elif defined(XBOX)
#else
	stopMusic();
	//Mix_FreeMusic(bgm);
	Mix_CloseAudio();
#if !defined(WII) && !defined(GAMECUBE)
	Mix_Quit();
#endif
#endif
	/* Controller */
	closeController();
	/* Renderer/Screen and Window */
	destroyDisplay();
	SDL_Quit();
	systemSpecificClose();
}