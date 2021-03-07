#include "pieces.h"
#include "main.h"


// Define the start VRAM (Video RAM)
volatile unsigned short *vram = (unsigned short *)0x06000000;

// Define OAM (Object Attribute Memory)
volatile unsigned char *oam = (unsigned char *)0x07000000;

Pieces_t Pieces;

void InitChessPieces(void) {
	int x, y;
	
	// Draw WHITE and BLACK Board
	for (x = 0; x < 20; x++) {
		for (y = 0; y < 20; y++) {
			Pieces.Piece[WHITE][x][y] = 0x7FFF;
			Pieces.Piece[BLACK][x][y] = 0x0;

			// FIXME: Draw actual pieces
			Pieces.Piece[PAWN][x][y] = 0x2222;
			Pieces.Piece[BISHOP][x][y] = 0x6666;
		}
	}

	// Draw PAWN

	// Draw BISHOP

	//etc
}


void DrawChessBoard(void) {
	// Initialize variables
	int file, rank;	// x,y co-ordiantes of chessboard

	// Loop through file and rank of the chess board
	for (file = 0; file < 8; file++) {
		for (rank = 0; rank < 8; rank++) {
			// Draw the background of the chess board
			DrawChessPieces(rank, file, 0);
		}
	}
}


void DrawChessPieces(int rank, int file, int piece) {
	// Initialize variables
	int x, y;
	
	if (piece == 0) {
		if ((file + rank)%2 == 0) {
			piece = WHITE;
		} else {
			piece = BLACK;
		}
	}

	// Color the tile at (rank, file)
	for (x = 0; x < 20; x++) {
		for (y = 0; y < 20; y++) {
			vram[file*20 + x + (rank*20 + y)*240] = Pieces.Piece[piece][x][y];
		}
	}
}
