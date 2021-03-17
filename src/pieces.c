#include "pieces.h"
#include "main.h"
#include "helper.h"
#include "score.h"


Pieces_t Pieces;
Board_t Board;

void InitChessPieces(void) {
	int x, y;
	
	// Draw WHITE and BLACK Board
	for (x = 0; x < BOARD_SIZE; x++) {
		for (y = 0; y < BOARD_SIZE; y++) {
			Board.Board[WHITE][x][y] = 0x7FFF;
			Board.Board[BLACK][x][y] = 0x0;
		}
	}

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
				if (rank > 4) {
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
		color = WHITE;
	} else {
		color = BLACK;
	}

	// Color the tile at (rank, file)
	for (x = 0; x < BOARD_SIZE; x++) {
		for (y = 0; y < BOARD_SIZE; y++) {
			vram[file*BOARD_SIZE + x + (rank*BOARD_SIZE + y)*240] = Board.Board[color][x][y];
		}
	}
}


void MoveChessPieces(int preRank, int preFile, int rank, int file) {
	// // Clear the previous position on chess board
	// DrawChessBoard(preRank, preFile);

	// // Get the chess piece from ScoreBaord
	// Piece_t Piece;

	// Piece = GetPiece(preRank, preFile);

	// UpdateScoreBoard(Piece, rank, file);

	// // Draw the Piece's new position
	// DrawChessPiece(rank, file, Piece.type, Piece.color);
}
