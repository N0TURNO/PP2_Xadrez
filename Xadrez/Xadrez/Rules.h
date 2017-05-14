/*
This file is part of ChessGame C.

    ChessGame C is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ChessGame C is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ChessGame C.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RULES_H
#define RULES_H

#include "Game.h"


int MovePiece(ChessPiece *piece, int newX, int newY, Game *game);

int IsValidMove(ChessPiece *piece, int newX, int newY, ChessBoard *board);
int IsValidPawnMove(ChessPiece *piece, int newX, int newY, ChessBoard *board);
int IsValidRookMove(ChessPiece *piece, int newX, int newY, ChessBoard *board);
int IsValidKnightMove(ChessPiece *piece, int newX, int newY, ChessBoard *board);
int IsValidBishopMove(ChessPiece *piece, int newX, int newY, ChessBoard *board);
int IsValidQueenMove(ChessPiece *piece, int newX, int newY, ChessBoard *board);
int IsValidKingMove(ChessPiece *piece, int newX, int newY, ChessBoard *board);

ChessPiece *Promotion(ChessPiece *piece, Game *game, Type t);

int IsValidMoveAndKingNotInCheck(ChessPiece *piece, int newX, int newY, ChessBoard *board);
int WillLetKingInCheck(ChessPiece *piece, int newX, int newY, ChessBoard *board);
int IsKingInCheck(ChessBoard *board, ChessColor color);
int Checkmate(ChessPiece *king, ChessBoard *board);

void KillPiece(ChessBoard *board, int x, int y, ChessColor color);

typedef enum movetype{
    None, Normal, Attack,
    EnPassant,
    Castling,
    PromotionMove
}MoveType;

#endif // RULES_H
