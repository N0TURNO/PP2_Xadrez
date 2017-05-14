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

#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include "Game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

ALLEGRO_FILECHOOSER* CreateFileChooser(char option);

int LoadGame(Game *game, ALLEGRO_DISPLAY *display);
int OpenAndReadFile(Game *game, const char *filepath);

int SaveGame(Game *game, ALLEGRO_DISPLAY *display);
int CreateAndWriteToFile(Game *game, const char* filepath);

#endif // SAVE_FILE_H
