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

#include "SaveFile.h"
#include "Game.h"
#include "PossibleMovesList.h"

#include <allegro5/allegro_native_dialog.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
The file will have all of a state's information.
Each file can only keep 1 game state.
The structure of the file will be:
fixed-length fields, fixed-length records
as such:

game_state(1*char)|game_turn(1*char)|
game_selected_piece_position_x(1*char)|
game_selected_piece_position_y(1*char)|
game_isCheckmate(1*char)|game_isCheck(1*char)|
game_last_moved_black_position_x(1*char)|
game_last_moved_black_position_y(1*char)|
game_last_moved_white_position_x(1*char)|
game_last_moved_white_position_y(1*char)|

player_name(15*char)|
Then there will have space for 16 pieces, even
if there aren't 16 pieces in the player's list,
where each piece has:

piece_type(1*char)|piece_position_x(1*char)|
piece_position_y(1*char)|piece_number_of_moves(1*int)|

The color of the piece will be the color of it's
player, so there's no need to store it.
The position of each piece will be in char, as there's
no need to store 32 bits for a int with max value of 3 bits.

So each piece will have (3*char + 1*int) size.
Then each player will have
(16*char + 16*(piece_size)) size.
*/

ALLEGRO_FILECHOOSER* CreateFileChooser(char option){
    system("mkdir savedata");   //If savedata directory doesn't exist, create it
    ALLEGRO_FILECHOOSER* fc = NULL;

    if(option == 'L')
        fc = al_create_native_file_dialog("savedata/", "Load Game",
                                          "*.sav", ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
    else fc = al_create_native_file_dialog("savedata/", "Save Game",
                                           "*.sav", ALLEGRO_FILECHOOSER_SAVE);

    return fc;
}

int LoadGame(Game *game, ALLEGRO_DISPLAY *display){
    //Create File Chooser
    ALLEGRO_FILECHOOSER* fc = CreateFileChooser('L');
    if (fc == NULL) return 0;

    al_show_native_file_dialog(display, fc);

    //Get Path
    const char *path;
    if (al_get_native_file_dialog_count(fc) > 0){
        path = al_get_native_file_dialog_path(fc, 0);
    } else return 0;
    if (path == NULL) return 0;

    ChessBoard* board = Game_GetBoard(game);
    //If board has't been created yet (call from MainMenu)
    if (board == NULL){
        //Create Board/Players
        Game_SetBoard(game, CreateChessBoard(CreatePlayer(White, "tempA"),
                        CreatePlayer(Black, "tempB")));

        board = Game_GetBoard(game);
        if (board == NULL) return 0;

        //Initialize List of each Player
        InitializeList(GetPlayer(board, White));
        InitializeList(GetPlayer(board, Black));
    }

    //Open file at path, read it and change the game's information
    if (!OpenAndReadFile(game, path)) return 0;
    //Update board
    UpdateBoard(board);

    //Generate Possible Moves
    UpdatePossibleMovesLists(board);

    al_destroy_native_file_dialog(fc);

    return 1;
}

int OpenAndReadFile(Game *game, const char *filepath){
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL) return 0;

    int i;

    //Temporary variables
    char temp;
    char selectedPieceX, selectedPieceY;
    char lastMovedWhitePieceX, lastMovedWhitePieceY;
    char lastMovedBlackPieceX, lastMovedBlackPieceY;

    rewind(fp);

    //Game State
    fread(&temp, sizeof(char), 1, fp);
    Game_SetState(game, temp - '0');

    //Game Turn
    fread(&temp, sizeof(char), 1, fp);
    if (temp == 'W') Game_SetTurn(game, White);
    else Game_SetTurn(game, Black);

    //Game Selected Piece Position
    fread(&selectedPieceX, sizeof(char), 1, fp);
    fread(&selectedPieceY, sizeof(char), 1, fp);

    //Game isCheckmate
    fread(&temp, sizeof(char), 1, fp);
    Game_SetIsCheckmate(game, temp - '0');

    //Game isCheck
    fread(&temp, sizeof(char), 1, fp);
    Game_SetIsCheck(game, temp - '0');

    //PLAYERS
    //Player 1
    Player *player = GetPlayer(Game_GetBoard(game), White);
    List *playerList = Player_GetList(player);
    //Name
    fread((Player_GetName(player)), sizeof(char), 15, fp);
    //Pieces
    for (i = 0; i < PLAYER_MAX_PIECES; i++){
        ChessPiece *currentPiece = List_GetPieceAt(playerList, i);
        //Type. If it's 'A', there's no piece to be read at i
        fread(&temp, sizeof(char), 1, fp);
        //If current game doesn't have a piece at i, create it
        if (currentPiece == NULL && temp != 'A')
            List_SetPieceAt(playerList, i, CreateChessPiece(0, 0, White, Pawn));
        //Put type
        if (temp != 'A') ChessPiece_SetType(currentPiece, GetTypeByChar(temp));

        //Piece Position X
        fread(&temp, sizeof(char), 1, fp);
        if (temp != 'A') ChessPiece_SetPosition(currentPiece, temp - '0', -1);
        //Piece Position Y
        fread(&temp, sizeof(char), 1, fp);
        if (temp != 'A') ChessPiece_SetPosition(currentPiece, -1, temp - '0');

        //Piece Number Of Moves
        int a;
        fread(&a, sizeof(int), 1, fp);
        if (a != -1) ChessPiece_SetNumberOfMoves(currentPiece, a);

        //If current game has a piece at i, but game being loaded doesn't
        if (temp == 'A') List_RemovePieceAt(playerList, i);
    }
    //Last Moved White Piece
    fread(&(lastMovedWhitePieceX), sizeof(char), 1, fp);
    fread(&(lastMovedWhitePieceY), sizeof(char), 1, fp);

    //Player 2
    player = GetPlayer(Game_GetBoard(game), Black);
    playerList = Player_GetList(player);
    //Name
    fread((Player_GetName(player)), sizeof(char), 15, fp);
    //Pieces
    for (i = 0; i < PLAYER_MAX_PIECES; i++){
        ChessPiece *currentPiece = List_GetPieceAt(playerList, i);
        //Type. If it's 'A', there's no piece to be read at i
        fread(&temp, sizeof(char), 1, fp);
        //If current game doesn't have a piece at i, create it
        if (currentPiece == NULL && temp != 'A')
            List_SetPieceAt(playerList, i, CreateChessPiece(0, 0, Black, Pawn));
        //Put type
        if (temp != 'A') ChessPiece_SetType(currentPiece, GetTypeByChar(temp));

        //Piece Position X
        fread(&temp, sizeof(char), 1, fp);
        if (temp != 'A') ChessPiece_SetPosition(currentPiece, temp - '0', -1);
        //Piece Position Y
        fread(&temp, sizeof(char), 1, fp);
        if (temp != 'A') ChessPiece_SetPosition(currentPiece, -1, temp - '0');

        //Piece Number Of Moves
        int a;
        fread(&a, sizeof(int), 1, fp);
        if (a != -1) ChessPiece_SetNumberOfMoves(currentPiece, a);

        //If current game has a piece at i, but game being loaded doesn't
        if (temp == 'A') List_RemovePieceAt(playerList, i);
    }
    //Last Moved Black Piece
    fread(&(lastMovedBlackPieceX), sizeof(char), 1, fp);
    fread(&(lastMovedBlackPieceY), sizeof(char), 1, fp);

    //Set selected piece
    if (selectedPieceX < 'A'){
        playerList = Player_GetList(GetPlayer(Game_GetBoard(game), White));
        Game_SetSelectedPiece(game, List_GetPieceByPosition(playerList, (selectedPieceX - '0'), (selectedPieceY - '0')));
        if (Game_GetSelectedPiece(game) == NULL){
            playerList = Player_GetList(GetPlayer(Game_GetBoard(game), Black));
            Game_SetSelectedPiece(game, List_GetPieceByPosition(playerList, (selectedPieceX - '0'), (selectedPieceY - '0')));
        }
    }

    //Set last moved white piece
    if (lastMovedWhitePieceX < 'A'){
        playerList = Player_GetList(GetPlayer(Game_GetBoard(game), White));
        Player_SetLastMovedPiece(GetPlayer(Game_GetBoard(game), White),
                                 List_GetPieceByPosition(playerList, (lastMovedWhitePieceX - '0'), (lastMovedWhitePieceY - '0')));
    } else Player_SetLastMovedPiece(GetPlayer(Game_GetBoard(game), White), NULL);
    //Set last moved black piece
    if (lastMovedBlackPieceX < 'A'){
        playerList = Player_GetList(GetPlayer(Game_GetBoard(game), Black));
        Player_SetLastMovedPiece(GetPlayer(Game_GetBoard(game), Black),
                                 List_GetPieceByPosition(playerList, (lastMovedBlackPieceX - '0'), (lastMovedBlackPieceY - '0')));
    } else Player_SetLastMovedPiece(GetPlayer(Game_GetBoard(game), Black), NULL);

    fclose(fp);

    return 1;
}

int SaveGame(Game *game, ALLEGRO_DISPLAY *display){
    //Create File Chooser
    ALLEGRO_FILECHOOSER* fc = CreateFileChooser('S');
    if (fc == NULL) return 0;

    al_show_native_file_dialog(display, fc);

    //Get Path
    const char *path;
    if (al_get_native_file_dialog_count(fc) > 0){
        path = al_get_native_file_dialog_path(fc, 0);
    } else return 0;
    if (path == NULL) return 0;

    //If file doesn't end with .sav, put it
    int pathlen = strlen(path);
    if (!((path[pathlen-4] == '.') && (path[pathlen-3] == 's') &&
         (path[pathlen-2] == 'a') && (path[pathlen-1] == 'v'))){
        path = strcat((char*)path, ".sav");
    }

    //Create file at path, and write game's current information
    if (!CreateAndWriteToFile(game, path)) return 0;

    al_destroy_native_file_dialog(fc);

    return 1;
}

int CreateAndWriteToFile(Game *game, const char* filepath){
    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL) return 0;

    int i;
    //Read
    rewind(fp);

    char temp;
    //Game State
    temp = Game_GetState(game) + '0';
    fwrite(&temp, sizeof(char), 1, fp);

    //Game Turn
    if (Game_GetTurn(game) == White) temp = 'W';
    else temp = 'B';
    fwrite(&temp, sizeof(char), 1, fp);

    //Game Selected Piece Position
    if (Game_GetSelectedPiece(game) != NULL){
        temp = ChessPiece_GetX(Game_GetSelectedPiece(game)) + '0';
        fwrite(&(temp), sizeof(char), 1, fp);
        temp = ChessPiece_GetY(Game_GetSelectedPiece(game)) + '0';
        fwrite(&(temp), sizeof(char), 1, fp);
    } else {
        temp = 'A';
        fwrite(&(temp), sizeof(char), 1, fp);
        fwrite(&(temp), sizeof(char), 1, fp);
    }

    //Game isCheckmate
    temp = Game_IsCheckmate(game) + '0';
    fwrite(&(temp), sizeof(char), 1, fp);

    //Game isCheck
    temp = Game_IsCheck(game) + '0';
    fwrite(&(temp), sizeof(char), 1, fp);

    //PLAYERS
    //Player 1
    Player *player = GetPlayer(Game_GetBoard(game), White);
    List *playerList = Player_GetList(player);
    //Name
    fwrite((Player_GetName(player)), sizeof(char), 15, fp);
    //Pieces
    for (i = 0; i < PLAYER_MAX_PIECES; i++){
        if (List_GetPieceAt(playerList, i) != NULL){
            ChessPiece* currentPiece = List_GetPieceAt(playerList, i);
            temp = GetCharByType(ChessPiece_GetType(currentPiece));
            fwrite(&(temp), sizeof(char), 1, fp);

            temp = ChessPiece_GetX(currentPiece) + '0';
            fwrite(&(temp), sizeof(char), 1, fp);

            temp = ChessPiece_GetY(currentPiece) + '0';
            fwrite(&(temp), sizeof(char), 1, fp);

            int a = ChessPiece_GetNumberOfMoves(currentPiece);
            fwrite(&(a), sizeof(int), 1, fp);
        } else{
            temp = 'A';
            fwrite(&(temp), sizeof(char), 1, fp);
            fwrite(&(temp), sizeof(char), 1, fp);
            fwrite(&(temp), sizeof(char), 1, fp);
            int a = -1;
            fwrite(&(a), sizeof(int), 1, fp);
        }
    }
    //Last Moved White Piece
    if (Player_GetLastMovedPiece(player) != NULL){
        temp = ChessPiece_GetX(Player_GetLastMovedPiece(player)) + '0';
        fwrite(&(temp), sizeof(char), 1, fp);

        temp = ChessPiece_GetY(Player_GetLastMovedPiece(player)) + '0';
        fwrite(&(temp), sizeof(char), 1, fp);
    } else{
        temp = 'A';
        fwrite(&(temp), sizeof(char), 1, fp);
        fwrite(&(temp), sizeof(char), 1, fp);
    }

    //Player 2
    player = GetPlayer(Game_GetBoard(game), Black);
    playerList = Player_GetList(player);
    //Name
    fwrite((Player_GetName(player)), sizeof(char), 15, fp);
    //Pieces
    for (i = 0; i < PLAYER_MAX_PIECES; i++){
        if (List_GetPieceAt(playerList, i) != NULL){
            ChessPiece* currentPiece = List_GetPieceAt(playerList, i);
            temp = GetCharByType(ChessPiece_GetType(currentPiece));
            fwrite(&(temp), sizeof(char), 1, fp);

            temp = ChessPiece_GetX(currentPiece) + '0';
            fwrite(&(temp), sizeof(char), 1, fp);

            temp = ChessPiece_GetY(currentPiece) + '0';
            fwrite(&(temp), sizeof(char), 1, fp);

            int a = ChessPiece_GetNumberOfMoves(currentPiece);
            fwrite(&(a), sizeof(int), 1, fp);
        } else{
            temp = 'A';
            fwrite(&(temp), sizeof(char), 1, fp);
            fwrite(&(temp), sizeof(char), 1, fp);
            fwrite(&(temp), sizeof(char), 1, fp);
            int a = -1;
            fwrite(&(a), sizeof(int), 1, fp);
        }
    }
    //Last Moved Black Piece
    if (Player_GetLastMovedPiece(player) != NULL){
        temp = ChessPiece_GetX(Player_GetLastMovedPiece(player)) + '0';
        fwrite(&(temp), sizeof(char), 1, fp);

        temp = ChessPiece_GetY(Player_GetLastMovedPiece(player)) + '0';
        fwrite(&(temp), sizeof(char), 1, fp);
    } else{
        temp = 'A';
        fwrite(&(temp), sizeof(char), 1, fp);
        fwrite(&(temp), sizeof(char), 1, fp);
    }

    //Flush and close file
    fclose(fp);

    return 1;
}
