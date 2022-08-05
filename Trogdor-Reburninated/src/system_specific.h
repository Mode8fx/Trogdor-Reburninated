#ifndef SYSTEM_SPECIFIC_MACROS_H
#define SYSTEM_SPECIFIC_MACROS_H

#include "include.h"

#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(ANDROID) || defined(PSP)
#define PC 0
#else
#define PC 1
#endif

#if defined(SDL1) && !defined(WII) && !defined(GAMECUBE)
extern FILE _iob[];

extern "C" FILE * __cdecl __iob_func(void);
#endif

extern void SYSTEM_SPECIFIC_OPEN();
extern void SYSTEM_SPECIFIC_CLOSE();

#if defined(PC)
#define STRCPY(dest, src) strcpy_s(dest, src);
#else
#define STRCPY(dest, src) strcpy(dest, src);
#endif

#endif