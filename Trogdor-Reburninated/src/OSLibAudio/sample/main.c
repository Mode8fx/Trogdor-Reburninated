/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic Input demo -- reads from control pad and indicates button
 *          presses.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Donour Sizemore <donour@uchicago.edu>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <oslibAudio/oslib.h>

/* Define the module info section */
PSP_MODULE_INFO("OSLIBAUDIOTEST", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

void dump_threadstatus(void);

int done = 0;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread,
				     0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

int main(void)
{
	SceCtrlData pad;

	pspDebugScreenInit();
	SetupCallbacks();
	
	oslInitAudio();
	
	// Load BGM, streaming
	OSL_SOUND* bgm = oslLoadSoundFile("song.bgm", 1);
	
	// Load sound, no streaming
	OSL_SOUND* sound = oslLoadSoundFile("sound.wav", 0);

	// Play BGM on channel 0 
	oslPlaySound(bgm, 0);
	
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	bool pressedX = false;
	while(!done){
		pspDebugScreenSetXY(0, 2);

		sceCtrlReadBufferPositive(&pad, 1); 

		printf("Cross: play sound effect\n");
		printf("Triangle: Resume music\n");
		printf("Circle: Pause music\n");

		if (pad.Buttons & PSP_CTRL_CROSS)
		{			
			if (!pressedX) oslPlaySound(sound, 1);
			pressedX = true;
		}
		else
		{
			pressedX = false;
		}

		if (pad.Buttons & PSP_CTRL_SQUARE)
		{
			oslPlaySound(sound, 2);
		}

		if (pad.Buttons & PSP_CTRL_CIRCLE)
		{
			oslPauseSound(bgm, 1);
		}

		if (pad.Buttons & PSP_CTRL_TRIANGLE)
		{
			oslPauseSound(bgm, 0);
		}

	}
	
	oslDeleteSound(bgm);
	oslDeleteSound(sound);
	
	oslDeinitAudio();
	
	sceKernelExitGame();
	return 0;
}
