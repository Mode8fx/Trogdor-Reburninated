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
	displayRefreshRate = DM.refresh_rate;
#elif defined(THREEDS)
	displayRefreshRate = 30;
#else
	displayRefreshRate = 60;
#endif
#if defined(ANDROID)
	SDL_SetHint(SDL_HINT_ORIENTATIONS, "Landscape");
#endif
	appSrcRect = { 0, 0, appWidth, appHeight };
	ticksPerFrameDefault = 1000.0F / frameRate;
	ticksPerFrame = ticksPerFrameDefault;
	ticksPerFrameInt = (Uint32)ticksPerFrame;
	setWidthHeightMults();

	/* Set Window/Renderer */


#if defined(SDL1)
	SDL_WM_SetCaption("Trogdor: Reburninated", NULL);
#if defined(PC)
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
	windowScreen = SDL_SetVideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
#elif defined(THREEDS)
	windowScreen = SDL_SetVideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT, 24, 0);
#else
	windowScreen = SDL_SetVideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT, 24, SDL_DOUBLEBUF);
#endif
#else
#if defined(PSP)
	window = SDL_CreateWindow("Trogdor: Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, DEFAULT_WIDTH, DEFAULT_HEIGHT);
#elif defined(THREEDS)
	window = SDL_CreateWindow("Trogdor: Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_RenderSetLogicalSize(renderer, DEFAULT_WIDTH, DEFAULT_HEIGHT);
#elif defined(PC)
	window = SDL_CreateWindow("Trogdor: Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, DEFAULT_WIDTH, DEFAULT_HEIGHT);
#else
	window = SDL_CreateWindow("Trogdor: Reburninated", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, DEFAULT_WIDTH, DEFAULT_HEIGHT);
#endif
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
#endif
#if defined(ANDROID)
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
#endif
	setScaling();
}

void InitializeSound() {
#if defined(PSP)
	oslInitAudio();
#elif defined(XBOX)
#else
	if (Mix_OpenAudio(AUDIO_SAMPLE_RATE, AUDIO_TROG_FORMAT, 2, 2048) < 0) {
#if !defined(SDL1)
		SDL_Log("Unable to initialize SDL_Mixer: %s", Mix_GetError());
#endif
	}
	setVolume_music(gameState.settings_general.bgmVolume);
	Mix_AllocateChannels(NUM_SOUND_CHANNELS);
	Mix_Volume(SFX_CHANNEL_GAME, (int)(gameState.settings_general.sfxVolume * 128.0 / 100));
	Mix_Volume(SFX_CHANNEL_STRONG_BAD, (int)(gameState.settings_general.sfxVolume * 128.0 / 100));
#endif
}

void InitializeController() {
#if defined(SDL1) // also applies to PSP SDL1
	SDL_JoystickEventState(SDL_ENABLE);
	for (i = 0; i < 8; i++) {
		if (i < SDL_NumJoysticks()) {
			joysticks[i] = SDL_JoystickOpen(i);
		}
	}
	SDL_JoystickEventState(SDL_ENABLE);
#elif defined(PSP)
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	for (i = 0; i < 8; i++) {
		if (i < SDL_NumJoysticks()) {
			joysticks[i] = SDL_JoystickOpen(i);
		}
	}
#else
	for (i = 0; i < 8; i++) {
		if (SDL_IsGameController(i)) {
			controllers[i] = SDL_GameControllerOpen(i);
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
	outputRect = gameToWindowDstRect;
#if !defined(SDL1)
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_RenderFillRect(renderer, &outputRect);
#else
	SDL_BlitSurface(transparentScreen, NULL, windowScreen, &outputRect);
#endif
}

void closeController() {
#if defined(PSP) || defined(SDL1)
	for (char i = 0; i < 8; i++) {
		if (joysticks[i] != NULL) {
			SDL_JoystickClose(joysticks[i]);
		}
	}
#else
	for (char i = 0; i < 8; i++) {
		if (controllers[i] != NULL) {
			SDL_GameControllerClose(controllers[i]);
		}
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
	Mix_HaltMusic();
	//Mix_FreeMusic(bgm);
	Mix_CloseAudio();
#if !(defined(WII) || defined(GAMECUBE))
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
