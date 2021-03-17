#ifndef _SCORE_H_
#define _SCORE_H_

#include "pieces.h"

Piece_t GetPiece(int preRank, int preFile);
void UpdateScoreBoard(Piece_t Piece, int rank, int file);

#endif