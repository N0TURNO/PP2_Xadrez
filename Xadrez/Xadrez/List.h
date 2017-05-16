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

#ifndef LIST_H
#define LIST_H

#include "ChessPiece.h"

typedef struct list List;

List* CreateList();
void DeleteList(List **list);

void List_AddPiece(List* list, ChessPiece* piece);
void List_RemovePiece(List* list, int x, int y);
void List_RemovePieceAt(List *list, int index);
ChessPiece* List_GetKing(List* list);
ChessPiece* List_GetPieceAt(List* list, int index);
ChessPiece* List_GetPieceByPosition(List *l, int x, int y);

int List_GetSize(List *l);
void List_SetPieceAt(List* list, int index, ChessPiece *piece);

#endif // LIST_H
