#ifndef _SCORE_H_
#define _SCORE_H_

#include "input.h"
#include "pieces.h"

extern int Board;

enum score_enum {
	bPAWN = -1,		// 1
	bBISHOP = -2,	// 2
	bKNIGHT = -3,	// 3
	bROOK = -4,		// 4
	bQUEEN = -5,	// 5
	bKING = -6,		// 6
	BOARD = 0,		// 0
	wPAWN = 1,		// 1
	wBISHOP = 2,	// 2
	wKNIGHT = 3,	// 3
	wROOK = 4,		// 4
	wQUEEN = 5,		// 5
	wKING = 6,		// 6
};


int checkBoard(UserInput_t UserInput, int color);
int ValidMove(void);
void UpdateScoreBoard(Piece_t Piece, int rank, int file);

#endif