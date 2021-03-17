#include "helper.h"

// Define IORAM (Input/Output RAM)
volatile unsigned char *ioram = (unsigned char *)0x04000000;

// Define the count for VBlank
volatile unsigned short *reg_vcount = (unsigned short *)0x04000006;

// Define the Key Input register
volatile unsigned short *reg_keyinput = (unsigned short *)0x04000130;

// Define the start VRAM (Video RAM)
volatile unsigned short *vram = (unsigned short *)0x06000000;

// Define OAM (Object Attribute Memory)
volatile unsigned short *oam = (unsigned short *)0x07000000;


void VidSync(void) {
	while(*reg_vcount >= 160);	// wait till VDraw
	while(*reg_vcount < 160);	// wait till VBlank
}
