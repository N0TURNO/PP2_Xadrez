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

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Player.h"

typedef struct chessBoard ChessBoard;

ChessBoard *CreateChessBoard(Player *player1, Player *player2);
void InitializeBoard(ChessBoard *board);
void ResetBoard(ChessBoard *board);
void UpdateBoard(ChessBoard *board);

void UpdatePossibleMovesLists(ChessBoard *board);
void UpdatePossibleMovesList(ChessBoard *board, ChessPiece *piece);

void DeleteChessBoard(ChessBoard **board);

ChessPiece *ChessBoard_GetChessPieceAtPosition(ChessBoard *board, int x, int y);
void ChessBoard_SetChessPieceAtPosition(ChessBoard *board, int x, int y, ChessPiece *piece);

Player *GetPlayer(ChessBoard *board, ChessColor color);
void ChessBoard_SetPlayer(ChessBoard *board, Player *player, ChessColor color);

#endif // CHESSBOARD_H
