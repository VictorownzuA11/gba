#ifndef _PIECES_H_
#define _PIECES_H_

typedef struct Pieces_t {
	// Board
	// Pawn
	// Bishop
	// Knight
	// Rook
	// Queen
	// King
	int Piece[8][20][20];
} Pieces_t;

enum pieces_enum {
	WHITE,	// 0
	BLACK,	// 1
	PAWN,	// 2
	BISHOP,	// 3
	KNIGHT,	// 4
	ROOK,	// 5
	QUEEN,	// 6
	KING	// 7
};

void InitChessPieces(void);
void DrawChessBoard(void);
void DrawChessPieces(int rank, int file, int piece);

#endif