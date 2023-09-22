/*! \file oslib.h
    \brief Main Oldschool Library file.
*/

/** OSLib version */

// This is a modified version of OSLib MOD that only has WAV and BGM audio

#define OSL_VERSION "MOD 1.1.2"

#ifndef _OSLIB_H_
#define _OSLIB_H_

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <psputility.h>
#include <pspgu.h>
#include <pspgum.h>
#include <psppower.h>
#include <pspiofilemgr.h>
#include <psphprm.h>

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define oslFatalError printf
#define oslHandleLoadNoFailError printf

#define oslAbs(x)					(((x)<0)?(-(x)):(x))
#define oslMin(x, y)				(((x)<(y))?(x):(y))
#define oslMax(x, y)				(((x)>(y))?(x):(y))
#define oslMinMax(x, min, max)		((x) < (max) ? ((x) > (min) ? (x) : (min)) : (max))

#include "VirtualFile.h"
#include "audio.h"
#include "bgm.h"

#endif
