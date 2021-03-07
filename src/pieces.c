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
			Pieces.Piece[PAWN][x][y] = 0x1111;		// Brown
			Pieces.Piece[BISHOP][x][y] = 0x2222;	// Green
			Pieces.Piece[KNIGHT][x][y] = 0x3333;	// Yellow
			Pieces.Piece[ROOK][x][y] = 0x4444;		// Indigo
			Pieces.Piece[QUEEN][x][y] = 0x5555;		// Blue
			Pieces.Piece[KING][x][y] = 0x6666;		// Purple
		}
	}

	// Draw PAWN

	// Draw BISHOP

	//etc
}


void DrawChessBoard(void) {
	// Initialize variables
	// ranks are rows
	// files are columns
	int file, rank;	// Piece position on the chess board
	int piece = 0;	// Piece to draw

	// Loop through file and rank of the chess board
	for (rank = 0; rank < 8; rank++) {
		for (file = 0; file < 8; file++) {
			piece = 0;
			
			if (rank == 1 || rank == 6) {
				piece = PAWN;
			}

			if (rank == 0 || rank == 7) {
				switch (file) {
					case 0:
					case 7:
						piece = ROOK;
						break;
					case 1:
					case 6:
						piece = KNIGHT;
						break;
					case 2:
					case 5:
						piece = BISHOP;
						break;
					case 3:
						piece = KING;
						break;
					case 4:
						piece = QUEEN;
						break;
				}

			}

			// Draw the background of the chess board
			DrawChessPieces(rank, file, piece);
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