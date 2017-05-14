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

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "PossibleMovesList.h"

typedef enum chessColor{
    White, Black
} ChessColor;

typedef enum type{
    Pawn,
    Rook, Knight, Bishop,
    Queen, King
}Type;

typedef struct chessPiece ChessPiece;

ChessPiece *CreateChessPiece(int x, int y, ChessColor color, Type type);

Type GetTypeByChar(char t);
char GetCharByType(Type t);

void DeletePiece(ChessPiece **piece);

int ChessPiece_GetX(ChessPiece *piece);
int ChessPiece_GetY(ChessPiece *piece);
void ChessPiece_SetPosition(ChessPiece *piece, int x, int y);

int ChessPiece_GetType(ChessPiece *piece);
void ChessPiece_SetType(ChessPiece *piece, Type t);

ChessColor ChessPiece_GetColor(ChessPiece *piece);

int ChessPiece_GetNumberOfMoves(ChessPiece *piece);
void ChessPiece_AddNumberOfMoves(ChessPiece *piece, int inc);
void ChessPiece_SetNumberOfMoves(ChessPiece *piece, int n);

PossibleMovesList *ChessPiece_GetPossibleMovesList(ChessPiece *piece);

#endif // CHESSPIECE_H
