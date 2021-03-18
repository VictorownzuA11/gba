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
			Pieces.Piece[WHITE][PAWN][x][y] = 0x1111;	// Brown
			Pieces.Piece[WHITE][BISHOP][x][y] = 0x2222;	// Green
			Pieces.Piece[WHITE][KNIGHT][x][y] = 0x3333;	// Yellow
			Pieces.Piece[WHITE][ROOK][x][y] = 0x4444;	// Indigo
			Pieces.Piece[WHITE][QUEEN][x][y] = 0x5555;	// Blue
			Pieces.Piece[WHITE][KING][x][y] = 0x6666;	// Purple

			// FIXME: Draw actual pieces
			Pieces.Piece[BLACK][PAWN][x][y] = 0x1111;	// Brown
			Pieces.Piece[BLACK][BISHOP][x][y] = 0x2222;	// Green
			Pieces.Piece[BLACK][KNIGHT][x][y] = 0x3333;	// Yellow
			Pieces.Piece[BLACK][ROOK][x][y] = 0x4444;	// Indigo
			Pieces.Piece[BLACK][QUEEN][x][y] = 0x5555;	// Blue
			Pieces.Piece[BLACK][KING][x][y] = 0x6666;	// Purple
		}
	}
}


void InitChessBoard(void) {
	// Initialize variables
	// ranks are rows
	// files are columns
	int file, rank;	// Piece position on the chess board
	int piece;		// Piece to draw
	int color;		// Color of the piece

	// Loop through file and rank of the chess board
	for (rank = 0; rank < 8; rank++) {
		for (file = 0; file < 8; file++) {
			// Draw the board
			DrawChessBoard(rank, file);
			
			// Initialize the piece
			piece = PIECE_CNT;

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

			if (piece != PIECE_CNT) {
				if (rank < 4) {
					color = WHITE;
				} else {
					color = BLACK;
				}

				DrawChessPiece(rank, file, piece, color);
			}
		}
	}
}


void DrawChessPiece(int rank, int file, int piece, int color) {
	int x, y;

	for (x = 4; x < PIECE_SIZE; x++) {
		for (y = 4; y < PIECE_SIZE; y++) {
			vram[file*BOARD_SIZE + x + (rank*BOARD_SIZE + y)*240] = Pieces.Piece[color][piece][x][y];
		}
	}
}


void DrawChessBoard(int rank, int file) {
	// Initialize variables
	int x, y, color = 0;

	if ((file + rank)%2 == 0) {
		color = 0x7FFF;
	} else {
		color = 0x0;
	}

	// Color the tile at (rank, file)
	for (x = 0; x < BOARD_SIZE; x++) {
		for (y = 0; y < BOARD_SIZE; y++) {
			vram[file*BOARD_SIZE + x + (rank*BOARD_SIZE + y)*240] = color;
		}
	}
}


void MoveChessPieces(UserInput_t UserInput) {
	// Clear the previous position on chess board
	DrawChessBoard(UserInput.prevRank, UserInput.prevFile);

	// Get the chess piece from ScoreBaord
	Piece_t Piece;

	Piece.type = ROOK;
	Piece.color = WHITE;

	//Piece = GetPiece(UserInput.prevRank, UserInput.prevFile);

	//UpdateScoreBoard(Piece, UserInput.rank, UserInput.file);

	// Draw the Piece's new position
	DrawChessPiece(UserInput.rank, UserInput.file, Piece.type, Piece.color);
}


void ClearCursor(UserInput_t UserInput) {
	// Initialize variables
	int x, y, color = 0, prevColor = 0;

	if ((UserInput.file + UserInput.rank)%2 == 0) {
		color = 0x7FFF;
	} else {
		color = 0x0;
	}

	if ((UserInput.prevFile + UserInput.prevRank)%2 == 0) {
		prevColor = 0x7FFF;
	} else {
		prevColor = 0x0;
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