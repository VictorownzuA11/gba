#include "main.h"
#include "pieces.h"
#include "helper.h"
#include "input.h"


int main(void) {
	// Initialize variables
	int *userinput;
	
	// Write into the I/O registers, setting video display parameters.
	ioram[0] = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	ioram[1] = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)

	// Initialize the board
	InitChessPieces();
	InitChessBoard();

	// Game loop
	while(1) {
		// Only run every frame
		VidSync();

		// Get user input
		userinput = getUserInput();

	}

	// End
	return 0;
}
