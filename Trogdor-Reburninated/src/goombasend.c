/*
 * Copyright (C) 2016 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

/*
 * This program has been modified from its original version for
 * use within Trogdor: Reburninated by Mode8fx. It has also been
 * split into an additional header file, goombasend.h
 */

#if defined(WII) || defined(GAMECUBE)

#include "goombasend.h"
#include "demo_gba.h"

void transcb(s32 chan, u32 ret) {
	transval = 1;
}

void acb(s32 res, u32 val) {
	resval = val;
}

unsigned int docrc(u32 crc, u32 val) {
	int i_gba;
	for(i_gba = 0; i_gba < 0x20; i_gba++) {
		if ((crc^val)&1) {
			crc>>=1;
			crc^=0xa1c1;
		} else
			crc>>=1;
		val>>=1;
	}
	return crc;
}

unsigned int calckey(unsigned int size) {
	unsigned int ret = 0;
	size=(size-0x200) >> 3;
	int res1 = (size&0x3F80) << 1;
	res1 |= (size&0x4000) << 2;
	res1 |= (size&0x7F);
	res1 |= 0x380000;
	int res2 = res1;
	res1 = res2 >> 0x10;
	int res3 = res2 >> 8;
	res3 += res1;
	res3 += res2;
	res3 <<= 24;
	res3 |= res2;
	res3 |= 0x80808080;

	if ((res3&0x200) == 0) {
		ret |= (((res3)&0xFF)^0x4B)<<24;
		ret |= (((res3>>8)&0xFF)^0x61)<<16;
		ret |= (((res3>>16)&0xFF)^0x77)<<8;
		ret |= (((res3>>24)&0xFF)^0x61);
	} else {
		ret |= (((res3)&0xFF)^0x73)<<24;
		ret |= (((res3>>8)&0xFF)^0x65)<<16;
		ret |= (((res3>>16)&0xFF)^0x64)<<8;
		ret |= (((res3>>24)&0xFF)^0x6F);
	}
	return ret;
}

void doreset() {
	cmdbuf[0] = 0xFF; //reset
	transval = 0;
	SI_Transfer(1,cmdbuf,1,resbuf,3,transcb,SI_TRANS_DELAY);
	while(transval == 0) ;
}

void getstatus() {
	cmdbuf[0] = 0; //status
	transval = 0;
	SI_Transfer(1,cmdbuf,1,resbuf,3,transcb,SI_TRANS_DELAY);
	while(transval == 0);
}

u32 recv() {
	memset(resbuf,0,32);
	cmdbuf[0]=0x14; //read
	transval = 0;
	SI_Transfer(1,cmdbuf,1,resbuf,5,transcb,SI_TRANS_DELAY);
	while(transval == 0) ;
	return *(vu32*)resbuf;
}

void send(u32 msg) {
	cmdbuf[0]=0x15;cmdbuf[1]=(msg>>0)&0xFF;cmdbuf[2]=(msg>>8)&0xFF;
	cmdbuf[3]=(msg>>16)&0xFF;cmdbuf[4]=(msg>>24)&0xFF;
	transval = 0;
	resbuf[0] = 0;
	SI_Transfer(1,cmdbuf,5,resbuf,1,transcb,SI_TRANS_DELAY);
	while(transval == 0) ;
}

void prepare_rom() {
	cmdbuf = memalign(32, 32);
	resbuf = memalign(32, 32);
	resval = 0;
	//SI_GetTypeAsync(1, acb);
}

u8 wait_for_gba() {
	//waiting for GBA in port 2...
	SI_GetTypeAsync(1, acb);
	if (resval) {
		if (resval == 0x80 || resval & 8) {
			resval = 0;
			SI_GetTypeAsync(1, acb);
		}
		else if (SI_GBA)
			return 0;
	}
	return 1;
}

u8 send_rom() {
	//GBA Found! Waiting for BIOS
	resbuf[2]=0;
	while(!(resbuf[2]&0x10)) {
		doreset();
		getstatus();
	}
	//GBA Ready, sending rom
	unsigned int sendsize = ((demo_gba_size+7)&~7);
	unsigned int ourkey = calckey(sendsize);
	//printf("Our Key: %08x\n", ourkey);
	//get current sessionkey
	u32 sessionkeyraw = recv();
	u32 sessionkey = __builtin_bswap32(sessionkeyraw^0x7365646F);
	//send over our own key
	send(__builtin_bswap32(ourkey));
	unsigned int fcrc = 0x15a0;
	//send over gba header
	int i_gba;
	for(i_gba = 0; i_gba < 0xC0; i_gba+=4)
		send(__builtin_bswap32(*(vu32*)(demo_gba+i_gba)));
	//send rom
	u32 enc;
	for (i_gba = 0xC0; i_gba < sendsize; i_gba += 4) {
		enc = ((demo_gba[i_gba + 3] << 24) | (demo_gba[i_gba + 2] << 16) | (demo_gba[i_gba + 1] << 8) | (demo_gba[i_gba]));
		fcrc = docrc(fcrc, enc);
		sessionkey = (sessionkey * 0x6177614B) + 1;
		enc ^= sessionkey;
		enc ^= ((~(i_gba + (0x20 << 20))) + 1);
		enc ^= 0x20796220;
		send(enc);
	}
	fcrc |= (sendsize<<16);
	//ROM done!
	//send over CRC
	sessionkey = (sessionkey*0x6177614B)+1;
	fcrc^=sessionkey;
	fcrc^=((~(i_gba+(0x20<<20)))+1);
	fcrc^=0x20796220;
	send(fcrc);
	//get crc back (unused)
	recv();
	return 0;
}
#endif
