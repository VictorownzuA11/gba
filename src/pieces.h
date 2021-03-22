#ifndef _PIECES_H_
#define _PIECES_H_

#include "input.h"
#include "score.h"

// Board and Piece Dimensions
#define PIECE_SIZE 16
#define BOARD_SIZE 20

// Board colors
#define WHITE 0x7FFF
#define BLACK 0x0


typedef struct Pieces_t {
	// Pawn
	// Bishop
	// Knight
	// Rook
	// Queen
	// King
	int Piece[13][PIECE_SIZE][PIECE_SIZE];
} Pieces_t;


void InitChessPieces(void);
void InitChessBoard(void);
void DrawChessBoard(int rank, int file);
void DrawChessPiece(int rank, int file);
void ClearCursor(UserInput_t UserInput);
void DrawCursor(UserInput_t UserInput);

#endif