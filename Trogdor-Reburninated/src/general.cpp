#include "general.h"

#if defined(SDL1) && !defined(WII) && !defined(GAMECUBE) && !defined(PSP) && !defined(THREEDS)
FILE _iob[] = { *stdin, *stdout, *stderr };

FILE * __cdecl __iob_func(void) {
	return _iob;
}
#endif

void applyColorKey(SDL_Surface *surface) {
#if !defined(SDL1)
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));
#else
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));
#endif
}

void systemSpecificOpen() {
#if defined(WII_U)
	/* Set SD Card Mount Path */
	WHBMountSdCard();
	WHBGetSdCardMountPath();
	string sdPathStr = "/wiiu/apps/Trogdor-RB";
	const char *sdPathStart = WHBGetSdCardMountPath();
	sdPathStr = sdPathStart + sdPathStr;
	const char *sdPath = sdPathStr.c_str();
	chdir(sdPath);
#elif defined(VITA)
	/* Disable rear touch pad */
	SDL_setenv("VITA_DISABLE_TOUCH_BACK", "1", 1);
#elif defined(SWITCH)
	/* Set SD Card mount path */
	chdir("/switch/Trogdor-RB");
#elif defined(WII) || defined(GAMECUBE)
	/* Initialize SD Card */
	fatInitDefault();
	/* Initialize Controller */
	PAD_Init();
#elif defined(XBOX)
	XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
#endif
}

void systemSpecificClose() {
#if defined(WII_U)
	/* Unmount SD Card */
	WHBUnmountSdCard();
#elif defined(VITA)
	sceKernelExitProcess(0);
#elif defined(WII) || defined(GAMECUBE)
	exit(EXIT_SUCCESS);
#elif defined(PSP)
	sceKernelExitGame();
#endif
}