#include "pieces.h"
#include "main.h"
#include "helper.h"
#include "score.h"
#include "input.h"


Pieces_t Pieces;

void InitChessPieces(void) {
	int x, y;
	/*
	for (x = 0; x < PIECE_SIZE; x++) {
		for (y = 0; y < PIECE_SIZE; y++) {
			// FIXME: Draw actual pieces
			if (y > x) { // BLACK
				Pieces.Piece[bPAWN][x][y] = bpawnp[PIECE_SIZE*x + y];	// Brown
				Pieces.Piece[bBISHOP][x][y] = 0x2222;	// Green
				Pieces.Piece[bKNIGHT][x][y] = 0x3333;	// Yellow
				Pieces.Piece[bROOK][x][y] = 0x4444;	// Indigo
				Pieces.Piece[bQUEEN][x][y] = 0x5555;	// Blue
				Pieces.Piece[bKING][x][y] = 0x6666;	// Purple
			}

			// FIXME: Draw actual pieces
			if (!(y > x)) { // WHITE
				Pieces.Piece[wPAWN][x][y] = 0x1111;	// Brown
				Pieces.Piece[wBISHOP][x][y] = 0x2222;	// Green
				Pieces.Piece[wKNIGHT][x][y] = 0x3333;	// Yellow
				Pieces.Piece[wROOK][x][y] = 0x4444;	// Indigo
				Pieces.Piece[wQUEEN][x][y] = 0x5555;	// Blue
				Pieces.Piece[wKING][x][y] = 0x6666;	// Purple
			}
		}
	}*/
	for (x = 0; x < PIECE_SIZE; x++) {
		for (y = 0; y < PIECE_SIZE; y++) {
			// FIXME: Draw actual pieces
			Pieces.Piece[bPAWN][x][y] = bpawnp[PIECE_SIZE*y + x];
			Pieces.Piece[wPAWN][x][y] = bpawnp[PIECE_SIZE*y + x] ^ WHITE;
			Pieces.Piece[bROOK][x][y] = brookp[PIECE_SIZE*y + x];
			Pieces.Piece[wROOK][x][y] = brookp[PIECE_SIZE*y + x] ^ WHITE;
			Pieces.Piece[bKNIGHT][x][y] = bknightp[PIECE_SIZE*y + x];
			Pieces.Piece[wKNIGHT][x][y] = bknightp[PIECE_SIZE*y + x] ^ WHITE;
			Pieces.Piece[bBISHOP][x][y] = bbishopp[PIECE_SIZE*y + x];
			Pieces.Piece[wBISHOP][x][y] = bbishopp[PIECE_SIZE*y + x] ^ WHITE;
			Pieces.Piece[bQUEEN][x][y] = bqueenp[PIECE_SIZE*y + x];
			Pieces.Piece[wQUEEN][x][y] = bqueenp[PIECE_SIZE*y + x] ^ WHITE;
			Pieces.Piece[bKING][x][y] = bkingp[PIECE_SIZE*y + x];
			Pieces.Piece[wKING][x][y] = bkingp[PIECE_SIZE*y + x] ^ WHITE;
		}
	}
	
}


void DrawChessPiece(int rank, int file) {
	int x, y, piece;

	piece = Board[rank][file];

	for (x = 0; x < PIECE_SIZE; x++) {
		for (y = 0; y < PIECE_SIZE; y++) {
			if ((piece < BOARD)){ //&& (y > x)) {
				// BLACK
				vram[file*BOARD_SIZE + x + 2 + (rank*BOARD_SIZE + y + 2)*240] = Pieces.Piece[piece][x][y];
			}
			
			if ((piece > BOARD)){ // && (!(y > x))) {
				// BLACK
				vram[file*BOARD_SIZE + x + 2 + (rank*BOARD_SIZE + y + 2)*240] = Pieces.Piece[piece][x][y];
			}
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
			if (((x < 2) || (x >= PIECE_SIZE + 2)) || ((y < 2) || (y >= PIECE_SIZE + 2))) {
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
			if (((x < 2) || (x >= PIECE_SIZE + 2)) || ((y < 2) || (y >= PIECE_SIZE + 2))) {
				if (UserInput.select) {
					vram[UserInput.prevFile*BOARD_SIZE + x + (UserInput.prevRank*BOARD_SIZE + y)*240] = 0x10; // Red
				}
				vram[UserInput.file*BOARD_SIZE + x + (UserInput.rank*BOARD_SIZE + y)*240] = 0x1F; // Red
			}
		}
	}
}