#include "pieces.h"
#include "main.h"
#include "helper.h"
#include "score.h"
#include "input.h"


Pieces_t Pieces;

void InitChessPieces(void) {
	int x, y;

	for (x = 0; x < PIECE_SIZE; x++) {
		for (y = 0; y < PIECE_SIZE; y++) {
			// FIXME: Draw actual pieces
			Pieces.Piece[bPAWN][x][y] = 0x1111;	// Brown
			Pieces.Piece[bBISHOP][x][y] = 0x2222;	// Green
			Pieces.Piece[bKNIGHT][x][y] = 0x3333;	// Yellow
			Pieces.Piece[bROOK][x][y] = 0x4444;	// Indigo
			Pieces.Piece[bQUEEN][x][y] = 0x5555;	// Blue
			Pieces.Piece[bKING][x][y] = 0x6666;	// Purple

			// FIXME: Draw actual pieces
			Pieces.Piece[wPAWN][x][y] = 0x1111;	// Brown
			Pieces.Piece[wBISHOP][x][y] = 0x2222;	// Green
			Pieces.Piece[wKNIGHT][x][y] = 0x3333;	// Yellow
			Pieces.Piece[wROOK][x][y] = 0x4444;	// Indigo
			Pieces.Piece[wQUEEN][x][y] = 0x5555;	// Blue
			Pieces.Piece[wKING][x][y] = 0x6666;	// Purple
		}
	}
}


void DrawChessPiece(int rank, int file) {
	int x, y, piece;

	piece = Board[rank][file];

	for (x = 4; x < PIECE_SIZE; x++) {
		for (y = 4; y < PIECE_SIZE; y++) {
			vram[file*BOARD_SIZE + x + (rank*BOARD_SIZE + y)*240] = Pieces.Piece[piece][x][y];
		}
	}
}


void DrawChessBoard(int rank, int file) {
	// Initialize variables
	int x, y, color = 0;

	if ((file + rank)%2 == 0) {
		color = WHITE;
	} else {
		color = BLACK;
	}

	// Color the tile at (rank, file)
	for (x = 0; x < BOARD_SIZE; x++) {
		for (y = 0; y < BOARD_SIZE; y++) {
			vram[file*BOARD_SIZE + x + (rank*BOARD_SIZE + y)*240] = color;
		}
	}
}


void ClearCursor(UserInput_t UserInput) {
	// Initialize variables
	int x, y, color = 0, prevColor = 0;

	if ((UserInput.file + UserInput.rank)%2 == 0) {
		color = WHITE;
	} else {
		color = BLACK;
	}

	if ((UserInput.prevFile + UserInput.prevRank)%2 == 0) {
		prevColor = WHITE;
	} else {
		prevColor = BLACK;
	}

	// Draw box around tile user has selected
	for (x = 0; x < BOARD_SIZE; x++) {
		for (y = 0; y < BOARD_SIZE; y++) {
			if (((x < 4) || (x >= PIECE_SIZE)) || ((y < 4) || (y >= PIECE_SIZE))) {
				vram[UserInput.prevFile*BOARD_SIZE + x + (UserInput.prevRank*BOARD_SIZE + y)*240] =  prevColor; // Red
				vram[UserInput.file*BOARD_SIZE + x + (UserInput.rank*BOARD_SIZE + y)*240] =  color; // Red
			}
		}
	}
}


void DrawCursor(UserInput_t UserInput) {
	int x, y;

	// Draw box around tile user has selected
	for (x = 0; x < BOARD_SIZE; x++) {
		for (y = 0; y < BOARD_SIZE; y++) {
			if (((x < 4) || (x >= PIECE_SIZE)) || ((y < 4) || (y >= PIECE_SIZE))) {
				if (UserInput.select) {
					vram[UserInput.prevFile*BOARD_SIZE + x + (UserInput.prevRank*BOARD_SIZE + y)*240] = 0x10; // Red
				}
				vram[UserInput.file*BOARD_SIZE + x + (UserInput.rank*BOARD_SIZE + y)*240] = 0x1F; // Red
			}
		}
	}
}