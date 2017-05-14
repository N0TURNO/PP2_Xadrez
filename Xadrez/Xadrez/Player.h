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

#ifndef PLAYER_H
#define PLAYER_H

#include "ChessPiece.h"
#include "List.h"

#define PLAYER_MAX_PIECES 16

typedef struct player Player;

Player *CreatePlayer();

void InitializeList(Player *player);

void DeletePlayer(Player **player);

char* Player_GetName(Player *player);
void Player_SetName(Player *player, const char* name);

List *Player_GetList(Player *player);

ChessPiece *Player_GetLastMovedPiece(Player *player);
void Player_SetLastMovedPiece(Player *player, ChessPiece *p);

ChessColor Player_GetColor(Player *player);

#endif // PLAYER_H
