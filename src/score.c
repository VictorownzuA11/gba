#include "score.h"
#include "pieces.h"
#include "input.h"


int Board[8][8] = {
	{bROOK, bKNIGHT, bBISHOP, bQUEEN, bKING, bBISHOP, bKNIGHT, bROOK},
	{bPAWN, bPAWN,   bPAWN,   bPAWN,  bPAWN, bPAWN,   bPAWN,   bPAWN},
	{BOARD, BOARD,   BOARD,   BOARD,  BOARD, BOARD,   BOARD,   BOARD},
	{BOARD, BOARD,   BOARD,   BOARD,  BOARD, BOARD,   BOARD,   BOARD},
	{BOARD, BOARD,   BOARD,   BOARD,  BOARD, BOARD,   BOARD,   BOARD},
	{BOARD, BOARD,   BOARD,   BOARD,  BOARD, BOARD,   BOARD,   BOARD},
	{wPAWN, wPAWN,   wPAWN,   wPAWN,  wPAWN, wPAWN,   wPAWN,   wPAWN},
	{wROOK, wKNIGHT, wBISHOP, wQUEEN, wKING, wBISHOP, wKNIGHT, wROOK},
};


int checkBoard(UserInput_t UserInput, int color) {
	if (color == BLACK) {
		if (Board[UserInput.rank][UserInput.file] < 0) {
			return 1;
		} else {
			return 0;
		}
	} else {
		if (Board[UserInput.rank][UserInput.file] > 0) {
			return 1;
		} else {
			return 0;
		}
	}
}


int ValidMove(void) {
	return 0;
}


void UpdateScoreBoard(Piece_t Piece, int rank, int file) {
	
}