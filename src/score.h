#ifndef _SCORE_H_
#define _SCORE_H_

#include "input.h"
#include "pieces.h"

extern int Board[8][8];

enum score_enum {
	bPAWN = 0,		// 0
	bBISHOP = 1,	// 1
	bKNIGHT = 2,	// 2
	bROOK = 3,		// 3
	bQUEEN = 4,		// 4
	bKING = 5,		// 5
	BOARD = 6,		// 6
	wPAWN = 7,		// 7
	wBISHOP = 8,	// 8
	wKNIGHT = 9,	// 9
	wROOK = 10,		// 10
	wQUEEN = 11,	// 11
	wKING = 12,		// 12
};


int CheckBoard(UserInput_t UserInput, int color);
int ValidMove(UserInput_t UserInput);
void UpdateScoreBoard(UserInput_t UserInput);
UserInput_t Checkmate(UserInput_t UserInput, int color);

#endif