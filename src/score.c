#include "score.h"
#include "pieces.h"
#include "input.h"
#include "string.h"

int Board[8][8];

int StartBoard[8][8] = {
	{bROOK, bKNIGHT, bBISHOP, bQUEEN, bKING, bBISHOP, bKNIGHT, bROOK},
	{bPAWN, bPAWN,   bPAWN,   bPAWN,  bPAWN, bPAWN,   bPAWN,   bPAWN},
	{BOARD, BOARD,   BOARD,   BOARD,  BOARD, BOARD,   BOARD,   BOARD},
	{BOARD, BOARD,   BOARD,   BOARD,  BOARD, BOARD,   BOARD,   BOARD},
	{BOARD, BOARD,   BOARD,   BOARD,  BOARD, BOARD,   BOARD,   BOARD},
	{BOARD, BOARD,   BOARD,   BOARD,  BOARD, BOARD,   BOARD,   BOARD},
	{wPAWN, wPAWN,   wPAWN,   wPAWN,  wPAWN, wPAWN,   wPAWN,   wPAWN},
	{wROOK, wKNIGHT, wBISHOP, wQUEEN, wKING, wBISHOP, wKNIGHT, wROOK},
};

int FirstPawn[2][8];

int StartFirstPawn[2][8] = {
	0
};


void InitChessBoard(void) {
	// Initialize variables
	// ranks are rows
	// files are columns
	int file, rank;	// Piece position on the chess board

	// Initialize the board state to start board
	memcpy(*Board, *StartBoard, sizeof Board);

	memcpy(FirstPawn, *StartFirstPawn, sizeof FirstPawn);

	// Loop through file and rank of the chess board
	for (rank = 0; rank < 8; rank++) {
		for (file = 0; file < 8; file++) {
			// Draw the board
			DrawChessBoard(rank, file);

			if (Board[rank][file] != BOARD) {
				DrawChessPiece(rank, file);
			}
		}
	}
}


int CheckBoard(UserInput_t UserInput, int color) {
	if (color == BLACK) {
		// Check that selected piece is valid
		if (Board[UserInput.rank][UserInput.file] < BOARD) {
			return 1;
		} else {
			return 0;
		}
	} else {
		if (Board[UserInput.rank][UserInput.file] > BOARD) {
			return 1;
		} else {
			return 0;
		}
	}
}


int ValidMove(UserInput_t UserInput) {
	int piece, destination;
	int dRank, dFile, dirRank, dirFile;
	int playerColor, destinationColor;

	// The piece that is trying to move
	piece = Board[UserInput.prevRank][UserInput.prevFile];
	
	// The destination of the piece
	destination = Board[UserInput.rank][UserInput.file];

	// Determine the color of the player
	if (piece < BOARD) {
		playerColor = 0; // Black
	} else {
		playerColor = 1; // White
	}

	// Determine the color of the destination
	if (destination < BOARD) {
		destinationColor = 0; // Black
	} else if (destination > BOARD) {
		destinationColor = 1; // White
	} else {
		destinationColor = 0xF; // Board
	}

	// FAIL: Trying to move ontop of their own piece
	if (playerColor == destinationColor) {
		return 0;
	}

	// Distance the piece moves
	if (playerColor == 0) {
		dRank = UserInput.rank - UserInput.prevRank;	// Black
	} else {
		dRank = UserInput.prevRank - UserInput.rank;	// White
	}

	dFile = UserInput.file - UserInput.prevFile;

	// NULL move, exit
	if ((dRank == 0) && (dFile == 0)) {
		return 0;
	}

	// Determine the direction of the move
	if (dRank < 0) {
		dirRank = -1;
	} else {
		dirRank = 1;
	}

	if (playerColor == 1) {
		dirRank *= -1;
	}

	if (dFile < 0) {
		dirFile = -1;
	} else {
		dirFile = 1;
	}

	// PAWN
	if ((piece == bPAWN) || (piece == wPAWN)) {
		// No En Passant, see: https://en.wikipedia.org/wiki/En_passant

		// TRUE: Attacking a piece
		if ((destination != BOARD) && (dRank== 1) && (dFile*dirFile == 1)) {
			return 1;
		}

		// Pawns can't move diagonally.
		if (dFile == 0) {
			// TRUE: Move 1 space forward
			if ((dRank == 1) && (destination == BOARD)) {
				return 1;
			}

			// TRUE: Move 2 spaces forward on first move of PAWN
			if ((dRank == 2) && (!FirstPawn[playerColor][UserInput.file])) {
				FirstPawn[playerColor][UserInput.file] = 1;
				return 1;
			}
		}
		
		// All other cases
		return 0;
	}

	// BISHOP
	if ((piece == bBISHOP) || (piece == wBISHOP)) {
		// FAIL: Bishops must move diagonally
		if (!(dRank == dFile*dirFile)) {
			return 0;
		}

		// TRUE: move only 1 space
		if (dFile*dirFile == 1) {
			return 1;
		}

		// Check that no pieces are blocking the move
		for (int i = 1; i <= ((dFile*dirFile) - 1); i++) {
			if (Board[UserInput.prevRank + (i*dirRank)][UserInput.prevFile + (i*dirFile)] != BOARD) {
				return 0;
			}
		}

		// Only valid moves are left
		return 1;
	}

	// KNIGHT
	if ((piece == bKNIGHT) || (piece == wKNIGHT)) {
		// Can only move 2 spaces in Rank or File at once
		if ((dRank > 2) || (dFile*dirFile > 2)) {
			return 0;
		}

		// Ensure that moves are in a L
		if (!(((dRank) == 2*(dFile*dirFile)) || (2*(dRank) == (dFile*dirFile)))) {
			return 0;
		}

		// Else all other moces are valid
		return 1;
	}

	// ROOK
	if ((piece == bROOK) || (piece == wROOK)) {
		// Can only move vertical or horizontal
		if ((dRank > 0) && (dFile*dirFile > 0)) {
			return 0;
		}

		// Moving Vertical
		if (dRank > 0) {
			// TRUE: move only 1 space
			if (dRank == 1) {
				return 1;
			}

			for (int i = 1; i <= (dRank - 1); i++) {
				if (Board[UserInput.prevRank + (i*dirRank)][UserInput.prevFile] != BOARD) {
					return 0;
				}
			}

		} else {
			// TRUE: move only 1 space
			if (dFile*dirFile == 1) {
				return 1;
			}

			for (int i = 1; i <= (dFile*dirFile - 1); i++) {
				if (Board[UserInput.prevRank][UserInput.prevFile + (i*dirFile)] != BOARD) {
					return 0;
				}
			}
		}

		// Only valid moves are left
		return 1;
	}

	// QUEEN
	if ((piece == bQUEEN) || (piece == wQUEEN)) {
		// Moving Diagonally
		if ((dRank == dFile*dirFile)) {
			// TRUE: move only 1 space
			if (dFile*dirFile == 1) {
				return 1;
			}

			// Check that no pieces are blocking the move
			for (int i = 1; i <= ((dFile*dirFile) - 1); i++) {
				if (Board[UserInput.prevRank + (i*dirRank)][UserInput.prevFile + (i*dirFile)] != BOARD) {
					return 0;
				}
			}

			// Only valid moves are left
			return 1;
		}

		// Can only move vertical or horizontal
		if ((dRank > 0) && (dFile*dirFile > 0)) {
			return 0;
		}

		// Moving Vertical
		if (dRank > 0) {
			// TRUE: move only 1 space
			if (dRank == 1) {
				return 1;
			}

			for (int i = 1; i <= (dRank - 1); i++) {
				if (Board[UserInput.prevRank + (i*dirRank)][UserInput.prevFile] != BOARD) {
					return 0;
				}
			}

		} else {
			// TRUE: move only 1 space
			if (dFile*dirFile == 1) {
				return 1;
			}

			for (int i = 1; i <= (dFile*dirFile - 1); i++) {
				if (Board[UserInput.prevRank][UserInput.prevFile + (i*dirFile)] != BOARD) {
					return 0;
				}
			}
		}

		// Only valid moves are left
		return 1;
	}

	// KING
	if ((piece == bKING) || (piece == wKING)) {
		// King tries to move more than 1 space
		if ((dRank < 2) && (dRank > -2) && (dFile*dirFile <= 1)) {
			return 1;
		}

		// Else all other moves are invalid
		return 0;
	}

	return 0;
}


void UpdateScoreBoard(UserInput_t UserInput) {
	// Store piece
	int piece = Board[UserInput.prevRank][UserInput.prevFile];

	// Check Pawn Promotion
	if ((piece == bPAWN) && (UserInput.rank == 7)) {
		piece = bQUEEN;
	} else if ((piece == wPAWN) && (UserInput.rank == 0)) {
		piece = wQUEEN;
	}

	// Update the piece's location
	Board[UserInput.rank][UserInput.file] = piece;

	// Clear piece's old loction
	Board[UserInput.prevRank][UserInput.prevFile] = BOARD;

	// Clear the chess board if a piece is there
	if (Board[UserInput.rank][UserInput.file] != BOARD) {
		 DrawChessBoard(UserInput.rank, UserInput.file);
	}

	// Clear old piece place on the board
	DrawChessBoard(UserInput.prevRank, UserInput.prevFile);

	// Draw the piece in the new location
	DrawChessPiece(UserInput.rank, UserInput.file);
}


UserInput_t IsCheck(UserInput_t UserInput) {
	// Initialize variables
	int piece;
	int check = 0;

	// Need a temp variable to store all the moves
	UserInput_t TempInput = UserInput;
	
	// Loop through the entire board
	for (int prevRank = 0; prevRank < 8; prevRank++) {
		for (int prevFile = 0; prevFile < 8; prevFile++) {
			piece = Board[prevRank][prevFile];

			// Find every WHITE piece
			if (piece > BOARD) {
				// Update TempInput to the current positon
				TempInput.prevRank = prevRank;
				TempInput.prevFile = prevFile;

				// Loop thorugh all possible places the piece can move
				for (int rank = 0; rank < 8; rank++) {
					for (int file = 0; file < 8; file++) {
						TempInput.rank = rank;
						TempInput.file = file;

						// Check for Check on BlackKing
						if (ValidMove(TempInput) && (Board[rank][file] == bKING)) {
							check++;
						}
					}
				}
			}
		}
	}

	
	return UserInput;
}