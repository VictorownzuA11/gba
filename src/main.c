#include "main.h"
#include "pieces.h"
#include "helper.h"
#include "score.h"
#include "input.h"


int main(void) {
	// Initialize selection box
	UserInput_t UserInput;
	UserInput.rank = 7;
	UserInput.file = 0;
	UserInput.prevRank = 0;
	UserInput.prevFile = 0;
	UserInput.select = 0;
	
	// Write into the I/O registers, setting video display parameters.
	ioram[0] = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	ioram[1] = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)

	// Initialize the board
	InitChessPieces();
	InitChessBoard();
	DrawCursor(UserInput);

	// Game loop
	while(1) {
		// Only run every frame
		VidSync();
		KeyPoll();

		ClearCursor(UserInput);

		if (wasKeyPressed(KEY_LEFT) && (UserInput.file > 0)) {
			UserInput.file--;
		} else if (wasKeyPressed(KEY_RIGHT) && (UserInput.file < 7)) {
			UserInput.file++;
		} else if (wasKeyPressed(KEY_UP) && (UserInput.rank > 0)) {
			UserInput.rank--;
		} else if (wasKeyPressed(KEY_DOWN) && (UserInput.rank < 7)) {
			UserInput.rank++;
		} else if (wasKeyPressed(KEY_A) && (UserInput.select == 0) && checkBoard(UserInput, WHITE)) {
			UserInput.select = 1;
			UserInput.prevFile = UserInput.file;
			UserInput.prevRank = UserInput.rank;
		} else if (wasKeyPressed(KEY_B) && (UserInput.select == 1)) {
			UserInput.select = 0;
			UserInput.file = UserInput.prevFile;
			UserInput.rank = UserInput.prevRank;
		} else if (wasKeyPressed(KEY_A) && (UserInput.select == 1)) {
			//MoveChessPieces(UserInput);

			UserInput.prevFile = UserInput.file;
			UserInput.prevRank = UserInput.rank;
		}

		DrawCursor(UserInput);
	}

	// End
	return 0;
}
