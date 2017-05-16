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

#ifndef GUIALLEGRO_H
#define GUIALLEGRO_H

#include "allegro5/allegro.h"
#include "Game.h"
#include "ChessPiece.h"

typedef struct images{
    //Chess Pieces
    ALLEGRO_BITMAP *whitePawnImg;
    ALLEGRO_BITMAP *blackPawnImg;
    ALLEGRO_BITMAP *whiteRookImg;
    ALLEGRO_BITMAP *blackRookImg;
    ALLEGRO_BITMAP *whiteKnightImg;
    ALLEGRO_BITMAP *blackKnightImg;
    ALLEGRO_BITMAP *whiteBishopImg;
    ALLEGRO_BITMAP *blackBishopImg;
    ALLEGRO_BITMAP *whiteQueenImg;
    ALLEGRO_BITMAP *blackQueenImg;
    ALLEGRO_BITMAP *whiteKingImg;
    ALLEGRO_BITMAP *blackKingImg;

    //Menus
    ALLEGRO_BITMAP *mainMenuImg;
    ALLEGRO_BITMAP *pauseMenuImg;
    ALLEGRO_BITMAP *pauseOptionsMenuImg;
    ALLEGRO_BITMAP *promotionMenuImg;
    ALLEGRO_BITMAP *endGameMenuImg;

    //Messages
    ALLEGRO_BITMAP *msgBoxImg;
}Images;


ALLEGRO_DISPLAY* InitializeAllegroGUI();
void LoadImages();

void DrawGameWindow(Game *game);
void DrawBoardWindow(Game *game);
void DrawPieceWindow(ChessPiece *piece);
void ShowPossibleMoves(ChessPiece *piece, ChessBoard *board);
void ErasePossibleMoves(ChessPiece *piece, ChessBoard *board);

void FinalizeAllegroGUI(ALLEGRO_DISPLAY *window);

void InputManager(Game *game, ALLEGRO_EVENT ev);
int MouseInputManager(int x, int y, Game *game);
int KeyboardInputManager(Game *game, int kc);

Type PromotionAllegro();

void DrawSquare(ChessBoard *board, int x, int y);
void DrawSelectionMark(int x, int y);
void DrawSquarePossibleMove(ChessBoard *board, int x, int y);

void ToggleSelectionMark(Game *game, int x, int y);
ALLEGRO_COLOR GetColorAtPosition(int x, int y);

void DrawPauseMenu();
void DrawPauseOptionsMenu();
void DrawPromotionMenu();
void DrawEndGameMenu(Game *game);
void DrawMainMenu();

int PauseMenuInputManager(int x, int y, Game *game);
int PauseOptionsMenuInputManager(int x, int y, Game *game);
int PromotionMenuInputManager(int x, int y, Game *game);
int EndGameMenuInputManager(int x, int y, Game *game);
int MainMenuInputManager(int x, int y, Game *game);

char* ColorToString(ChessColor color);

void DrawCheckMessage(Game *game);
void DrawCheckmateMessage(Game *game);

void StartGameThreads(Game *game);
void *ScreenRefreshLoop(ALLEGRO_THREAD *thread, void *data);
void GameLoop(Game *game);
void Redraw(Game *game);

//GUI Values

//Screen
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 480

//Board
#define BOARD_HEIGHT 480
#define BOARD_WIDTH 480
#define BOARD_POS_X 0
#define BOARD_POS_Y 0

#define SQUARE_HEIGHT 60
#define SQUARE_WIDTH 60


//MENU POSITION
//TODO - define them and use them in Menu.c


//SIDE PANEL
#define SIDE_PANEL_POS_X 480
#define SIDE_PANEL_WIDTH 160
#define SIDE_PANEL_POS_Y 0
#define SIDE_PANEL_HEIGHT 480

#define SIDE_PANEL_PLAYER1_NAME_POS_X 560
#define SIDE_PANEL_PLAYER1_NAME_POS_Y 300
#define SIDE_PANEL_PLAYER2_NAME_POS_X 560
#define SIDE_PANEL_PLAYER2_NAME_POS_Y 100

#endif // GUIALLEGRO_H
