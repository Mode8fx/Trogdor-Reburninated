#if defined(WII) || defined(GAMECUBE)

#include <gccore.h>
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fat.h>

#ifndef GOOMBASEND_H
#define GOOMBASEND_H

//from my tests 50us seems to be the lowest
//safe si transfer delay in between calls
#define SI_TRANS_DELAY 50

extern u8 *resbuf, *cmdbuf;

extern volatile u32 transval;
extern void transcb(s32, u32);

extern volatile u32 resval;
extern void acb(s32, u32);

extern unsigned int docrc(u32, u32);
extern unsigned int calckey(unsigned int);
extern void doreset();
extern void getstatus();
extern u32 recv();
extern void send(u32);
extern void prepare_rom();
extern u8 wait_for_gba();
extern u8 send_rom();
#endif

#endif