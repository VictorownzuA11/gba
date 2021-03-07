#include "main.h"
#include "pieces.h"
#include "helper.h"


// Define IORAM (Input/Output RAM)
volatile unsigned char *ioram = (unsigned char *)0x04000000;


int main(void) {
	// Write into the I/O registers, setting video display parameters.
	ioram[0] = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	ioram[1] = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)

	// Initialize variables
	int rank = 0;
	int file = 0;
	int t = 0;

	InitChessPieces();
	DrawChessBoard();

	// Game loop
	while(1) {
		// Only run every frame
		VidSync();

		// Game code
		DrawChessPieces(1, 0, PAWN);
	}

	// End
	return 0;
}
