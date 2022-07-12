#ifndef SYSTEM_SPECIFIC_MACROS_H
#define SYSTEM_SPECIFIC_MACROS_H

#if defined(SDL1) && !defined(WII) && !defined(GAMECUBE)
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void) {
	return _iob;
}
#endif

#if defined(WII_U)
/* Set SD Card Mount Path */
#define SYSTEM_SPECIFIC_OPEN()                           \
	if (!WHBMountSdCard()) {                             \
		return 0;                                        \
	}                                                    \
	if (WHBGetSdCardMountPath() == NULL) {               \
		return 0;                                        \
	}                                                    \
	string sdPathStr = "/wiiu/apps/TrogdorRB"; \
	const char *sdPathStart = WHBGetSdCardMountPath();   \
	sdPathStr = sdPathStart + sdPathStr;                 \
	const char *sdPath = sdPathStr.c_str();              \
	chdir(sdPath);
/* Unmount SD Card */
#define SYSTEM_SPECIFIC_CLOSE() WHBUnmountSdCard();
#define STRCPY(dest, src) strcpy(dest, src);
#elif defined(VITA)
/* Disable rear touch pad */
#define SYSTEM_SPECIFIC_OPEN() SDL_setenv("VITA_DISABLE_TOUCH_BACK", "1", 1);
#define SYSTEM_SPECIFIC_CLOSE() sceKernelExitProcess(0);
#define STRCPY(dest, src) strcpy(dest, src);
#elif defined(SWITCH)
/* Set SD Card mount path */
#define SYSTEM_SPECIFIC_OPEN() chdir("/switch/TrogdorRB");
#define SYSTEM_SPECIFIC_CLOSE()
#define STRCPY(dest, src) strcpy(dest, src);
#elif defined(WII) || defined(GAMECUBE)
#define SYSTEM_SPECIFIC_OPEN() fatInitDefault();
#define SYSTEM_SPECIFIC_CLOSE() exit(EXIT_SUCCESS);
#define STRCPY(dest, src) strcpy(dest, src);
#elif defined(ANDROID)
#define SYSTEM_SPECIFIC_OPEN()
#define SYSTEM_SPECIFIC_CLOSE()
#define STRCPY(dest, src) strcpy(dest, src);
#elif defined(PSP)
#define SYSTEM_SPECIFIC_OPEN()
#define SYSTEM_SPECIFIC_CLOSE() sceKernelExitGame();
#define STRCPY(dest, src) strcpy(dest, src);
#else
#define SYSTEM_SPECIFIC_OPEN()
#define SYSTEM_SPECIFIC_CLOSE()
#define STRCPY(dest, src) strcpy_s(dest, src);
#endif

#endif