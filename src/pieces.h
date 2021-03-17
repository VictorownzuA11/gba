#ifndef _PIECES_H_
#define _PIECES_H_


#define PIECE_SIZE 16
#define BOARD_SIZE 20


enum colors_enum {
	WHITE,		// 0
	BLACK,		// 1
	COLOR_CNT	// 2
};


enum pieces_enum {
	PAWN,		// 0
	BISHOP,		// 1
	KNIGHT,		// 2
	ROOK,		// 3
	QUEEN,		// 4
	KING,		// 5
	PIECE_CNT	// 6
};


typedef struct Piece_t {
	int type, color;
} Piece_t;


typedef struct Board_t {
	int Board[COLOR_CNT][BOARD_SIZE][BOARD_SIZE];
} Board_t;


typedef struct Pieces_t {
	// Pawn
	// Bishop
	// Knight
	// Rook
	// Queen
	// King
	int Piece[COLOR_CNT][PIECE_CNT][PIECE_SIZE][PIECE_SIZE];
} Pieces_t;


void InitChessPieces(void);
void InitChessBoard(void);
void DrawChessBoard(int rank, int file);
void DrawChessPiece(int rank, int file, int piece, int color);
void MoveChessPieces(int preRank, int preFile, int rank, int file);

#endif