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

#include "Game.h"
#include "Player.h"
#include "GUIAllegro.h"
#include "Rules.h"
#include "PossibleMovesList.h"

#include <stdio.h>

struct game{
    ChessBoard *board;
    ChessPiece *selectedPiece;

    ChessColor turn;
    State state;

    //Booleans
    int isInGame;
    int isCheckmate;
    int isCheck;
};

Game *CreateGame(){
    Game *game = malloc(sizeof(Game));
    if (game == NULL) return NULL;

    game->selectedPiece = NULL;
    game->state         = MainMenu;
    game->board         = NULL;

    return game;
}

//Starts a new game, initializing board and players
void StartGame(Game *game){
    //Initialize game variables
    game->turn          = White;
    game->selectedPiece = NULL;
    game->isInGame      = 1;
    game->isCheck       = 0;
    game->isCheckmate   = 0;

    //Get names
    char name1[15], name2[15];
    printf("Player 1: ");
    fgets(name1, 15, stdin);
    ClearSTDIN(name1);
    printf("Player 2: ");
    fgets(name2, 15, stdin);
    ClearSTDIN(name2);

    //Create Board/Players
    game->board = CreateChessBoard(CreatePlayer(White, name1),
                                   CreatePlayer(Black, name2));
    if (game->board == NULL) return;

    //Initialize List of each Player
    InitializeList(GetPlayer(game->board, White));
    InitializeList(GetPlayer(game->board, Black));

    //Initialize Board
    InitializeBoard(game->board);

    //Generate Possible Moves
    UpdatePossibleMovesLists(game->board);
}

void RestartGame(Game *game){
    if (game == NULL) return;

    game->turn          = White;
    game->selectedPiece = NULL;
    game->isInGame      = 1;
    game->isCheckmate   = 0;
    game->isCheck       = 0;

    //Original Players
    Player *whitePlayer = GetPlayer(game->board, White);
    Player *blackPlayer = GetPlayer(game->board, Black);

    //Players
    char name[15];

    //WHITE
    strcpy(name, Player_GetName(whitePlayer));
    ChessBoard_SetPlayer(game->board, CreatePlayer(White, name), White);

    //If couldn't create new white player, get original back
    if (GetPlayer(game->board, White) == NULL){
        ChessBoard_SetPlayer(game->board, whitePlayer, White);
        return;
    }

    //BLACK
    strcpy(name, Player_GetName(blackPlayer));
    ChessBoard_SetPlayer(game->board, CreatePlayer(Black, name), Black);

    //If couldn't create new black player, get original back
    //from both white and black
    if (GetPlayer(game->board, Black) == NULL){
        //Delete White Player that was successfully created
        Player *to_delete = GetPlayer(game->board, White);
        DeletePlayer(&(to_delete));

        ChessBoard_SetPlayer(game->board, whitePlayer, White);
        ChessBoard_SetPlayer(game->board, blackPlayer, White);
        return;
    }

    InitializeList(GetPlayer(game->board, White));
    InitializeList(GetPlayer(game->board, Black));

    //Board
    UpdateBoard(game->board);

    //Free originals
    DeletePlayer(&whitePlayer);
    DeletePlayer(&blackPlayer);

    //Generate Possible Moves
    UpdatePossibleMovesLists(game->board);
}

void UpdateGame(Game *game){
    ChangePlayer(game);

    //Generate Possible Moves
    UpdatePossibleMovesLists(game->board);

    if (Checkmate(List_GetKing(Player_GetList(GetPlayer(game->board, game->turn))), game->board)){
        printf("Checkmate. %s won.\n", Player_GetName(GetPlayer(game->board, !game->turn)));

        game->isCheckmate   = 1;
        game->state         = EndGameMenu;
    }
    else if (IsKingInCheck(game->board, game->turn)){
        printf("King in Check\n");
        game->isCheck = 1;
    }
}

void Play(Game *game){
    //Check memory
    if (game == NULL) return;

    //Initialize Game
    game->isInGame      = 1;
    game->isCheck       = 0;
    game->isCheckmate   = 0;
    game->turn          = White;



    //Game
    StartGameThreads(game);
}

//Doesn't delete game, but board and players
void StopGame(Game *game){
    if (game != NULL)
        DeleteChessBoard(&(game->board));
}

void DeleteGame(Game **game){
    if (game != NULL){
        DeleteChessBoard(&((*game)->board));
        free(*game);
        *game = NULL;
    }
}

void ClearSTDIN(char *s){
    //If filled array, remove '\n' and end
    if (s[strlen(s)-1] == '\n'){
        s[strlen(s)-1] = '\0';
        return;
    }
    //Else get all chars left to clear it
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}



int Game_IsCheck(Game *game){
    if (game == NULL) return 0;

    return game->isCheck;
}
void Game_SetIsCheck(Game *game, int a){
    if (game == NULL) return;

    game->isCheck = a;
}

int Game_IsCheckmate(Game *game){
    if (game == NULL) return 0;

    return game->isCheckmate;
}
void Game_SetIsCheckmate(Game *game, int a){
    if (game == NULL) return;

    game->isCheckmate = a;
}

int Game_IsInGame(Game *game){
    if (game == NULL) return 0;

    return game->isInGame;
}
void Game_SetIsInGame(Game *game, int a){
    if (game == NULL) return;

    game->isInGame = a;
}

ChessColor Game_GetTurn(Game *game){
    if (game == NULL) return White;

    return game->turn;
}
void Game_SetTurn(Game *game, ChessColor t){
    if (game == NULL) return;

    game->turn = t;
}
void ChangePlayer(Game *game){
    game->turn = !game->turn;
}

State Game_GetState(Game *game){
    if (game == NULL) return MainMenu;

    return game->state;
}
void Game_SetState(Game *game, State s){
    if (game == NULL) return;

    game->state = s;
}

ChessPiece *Game_GetSelectedPiece(Game *game){
    if (game == NULL) return NULL;

    return game->selectedPiece;
}
void Game_SetSelectedPiece(Game *game, ChessPiece *piece){
    if (game == NULL) return;

    game->selectedPiece = piece;
}

ChessBoard* Game_GetBoard(Game *game){
    if (game == NULL) return NULL;

    return game->board;
}
void Game_SetBoard(Game *game, ChessBoard *board){
    if (game == NULL) return;

    game->board = board;
}
