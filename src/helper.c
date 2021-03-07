#include "helper.h"

volatile unsigned short *reg_vcount = (unsigned short *)0x04000006;

void VidSync(void) {
	while(*reg_vcount >= 160);	// wait till VDraw
	while(*reg_vcount < 160);	// wait till VBlank
}


int mmap(int x, int y) {
	// The Gameboy has a 15bit 240x160 pixel colour LCD screen
	// VRAM starts from 0x600_0000 - 0x601_7FFF (96kb)
	// Need to map x,y position to global VRAM position in memory
	return (x + y*240);
}


int rgb(int r, int g, int b) {
	// VRAM is RGB and 15bits, so first 5bits R, next 5bits G, last 5 bits B
	// Red   = 000000000011111 (0x001F)
	// Green = 000001111100000 (0x03E0)
	// Blue  = 111110000000000 (0x7C00)
	r = r & 0x1F; // Clamp the values to 5 bits
	g = g & 0x1F;
	b = b & 0x1F;
	return (r | (g << 5) | (b << 10));
}

