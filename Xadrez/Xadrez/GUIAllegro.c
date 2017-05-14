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
#include "GUIAllegro.h"
#include "Game.h"
#include "Music.h"
#include "Menu.h"
#include "Rules.h"
#include "SaveFile.h"
#include "ChessBoard.h"
#include "PossibleMovesList.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <stdlib.h>

Images *imgs = NULL;
ALLEGRO_DISPLAY *window = NULL;

//To child thread be able to draw, it needs the target bitmap of the window,
//as it cannot be used by multiple threads simultaneously
ALLEGRO_BITMAP *targetbm = NULL;

//Event Queue
ALLEGRO_EVENT_QUEUE *graphicalEventQueue = NULL;    //Has timer(FPS)
ALLEGRO_EVENT_QUEUE *inputEventQueue = NULL;        //Hsa window(close), keyboard and mouse

const float FPS = 60;

ALLEGRO_DISPLAY* InitializeAllegroGUI(){
    //Initialize Allegro
    al_init();
    //Initialize Image Add-on
    al_init_image_addon();

    window = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    //Install mouse drivers
    al_install_mouse();
    //Install keyboard drivers
    al_install_keyboard();
    //Initialize Primitives
    al_init_primitives_addon();
    //Initialize Fonts
    al_init_font_addon();
    al_init_ttf_addon();

    //Initialize event queues
    graphicalEventQueue = al_create_event_queue();
    inputEventQueue = al_create_event_queue();

    //Set event queue to get events from window/mouse/keyboard
    al_register_event_source(inputEventQueue, al_get_display_event_source(window)); //e.g. close window
    al_register_event_source(inputEventQueue, al_get_mouse_event_source());         //Tell allegro to get events from the mouse
    al_register_event_source(inputEventQueue, al_get_keyboard_event_source());      //Tell allegro to get events from the keyboard

    LoadImages();

    InitializeAudio();

    return window;
}

void LoadImages(){
    imgs = malloc(sizeof(Images));

    //Chess Pieces
    imgs->whitePawnImg      = al_load_bitmap("resources/images/pieces/whitePawnPiece.png");
    imgs->blackPawnImg      = al_load_bitmap("resources/images/pieces/blackPawnPiece.png");
    imgs->whiteRookImg      = al_load_bitmap("resources/images/pieces/whiteRookPiece.png");
    imgs->blackRookImg      = al_load_bitmap("resources/images/pieces/blackRookPiece.png");
    imgs->whiteKnightImg    = al_load_bitmap("resources/images/pieces/whiteKnightPiece.png");
    imgs->blackKnightImg    = al_load_bitmap("resources/images/pieces/blackKnightPiece.png");
    imgs->whiteBishopImg    = al_load_bitmap("resources/images/pieces/whiteBishopPiece.png");
    imgs->blackBishopImg    = al_load_bitmap("resources/images/pieces/blackBishopPiece.png");
    imgs->whiteQueenImg     = al_load_bitmap("resources/images/pieces/whiteQueenPiece.png");
    imgs->blackQueenImg     = al_load_bitmap("resources/images/pieces/blackQueenPiece.png");
    imgs->whiteKingImg      = al_load_bitmap("resources/images/pieces/whiteKingPiece.png");
    imgs->blackKingImg      = al_load_bitmap("resources/images/pieces/blackKingPiece.png");

    //Menus
    imgs->mainMenuImg           = al_load_bitmap("resources/images/menu/MainMenu.png");
    imgs->pauseMenuImg          = al_load_bitmap("resources/images/menu/PauseMenu.png");
    imgs->pauseOptionsMenuImg   = al_load_bitmap("resources/images/menu/PauseOptionsMenu.png");
    imgs->promotionMenuImg      = al_load_bitmap("resources/images/menu/PromotionMenu.png");
    imgs->endGameMenuImg        = al_load_bitmap("resources/images/menu/EndGameMenu.png");

    //Messages
    imgs->msgBoxImg = al_load_bitmap("resources/images/messages/CheckmateMessage.png");
}

//============================================GAMEPLAY==========================================================

void StartGameThreads(Game *game){
    //Create screen_refresh thread
    ALLEGRO_THREAD *thread = al_create_thread(ScreenRefreshLoop, game);

    //Save window's buffer bitmap - child and parent can't access it simultaneously
    targetbm = al_get_target_bitmap();
    al_set_target_bitmap(NULL);

    //Audio
    PlaySong("test125");

    //Start graphical thread
    al_start_thread(thread);
    //Start gameplay loop
    GameLoop(game);

    al_destroy_thread(thread);
}

//Function responsible for getting the input from the player and update the game accordingly
void GameLoop(Game *game){
    //Loop until exit the game
    while(Game_IsInGame(game)){
        //Wait for an event
        ALLEGRO_EVENT ev;
        al_wait_for_event(inputEventQueue, &ev);

        InputManager(game, ev);
    }
}

//INPUT

void InputManager(Game *game, ALLEGRO_EVENT ev){
    //If event is close display, leave game loop
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        printf("Game Ended.\n");
        Game_SetIsInGame(game, 0);
    }
    //If pressed a mouse button
    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        MouseInputManager(ev.mouse.x, ev.mouse.y, game);
    }

    //If pressed a keyboard button
    if (ev.type == ALLEGRO_EVENT_KEY_UP){
        KeyboardInputManager(game, ev.keyboard.keycode);
    }
}

int KeyboardInputManager(Game *game, int kc){
    if (Game_GetState(game) == PromotionMenu) return 0;
    if (kc == ALLEGRO_KEY_ESCAPE){
        //Open/Close Pause Menu
        if (Game_GetState(game) == PauseMenu){
            Game_SetState(game, Playing);
            return 1;
        } else if (Game_GetState(game) == Playing){
            Game_SetState(game, PauseMenu);
            return 1;
        }
    }

    return 0;
}

int MouseInputManager(int x, int y, Game *game){
    if (x >= SIDE_PANEL_POS_X){
        //TODO
        //al_resize_display(window, width, height);
        return 0;
    }
    if (Game_GetState(game) == Playing){
        //If wants to select a piece
        if (Game_GetSelectedPiece(game) == NULL){
            Game_SetSelectedPiece(game, ChessBoard_GetChessPieceAtPosition(Game_GetBoard(game),
                                                                           (x - x%SQUARE_WIDTH)/SQUARE_WIDTH,
                                                                           (y - y%SQUARE_HEIGHT)/SQUARE_HEIGHT));
            //If it's his turn
            if (Game_GetSelectedPiece(game) != NULL){
                if (ChessPiece_GetColor(Game_GetSelectedPiece(game)) != Game_GetTurn(game)){
                    Game_SetSelectedPiece(game, NULL);
                    return 0;
                }
                return 0;
            } else return 0;
        }
        //If wants to put a piece somewhere
        {
            //If can move, will move
            int rc = MovePiece(Game_GetSelectedPiece(game), (x- x%SQUARE_WIDTH)/SQUARE_WIDTH,
                               (y - y%SQUARE_HEIGHT)/SQUARE_HEIGHT, game);
            if (rc == 1){
                //Set selected piece as none
                Game_SetSelectedPiece(game, NULL);

                //Update Game
                UpdateGame(game);
                return 1;
            }
            else if (rc == 2){
                //Promotion
                Game_SetState(game, PromotionMenu);
                return 1;
            }
            //Set selected piece as none
            Game_SetSelectedPiece(game, NULL);
            return 0;
        }
    } else if (Game_GetState(game) == PauseMenu){                 //If on menu
        return PauseMenuInputManager(x, y, game);
    } else if (Game_GetState(game) == PauseOptionsMenu){
        return PauseOptionsMenuInputManager(x, y, game);
    } else if (Game_GetState(game) == EndGameMenu && !Game_IsCheckmate(game)){
        return EndGameMenuInputManager(x, y, game);
    } else if (Game_GetState(game) == MainMenu){
        return MainMenuInputManager(x, y, game);
    } else if (Game_GetState(game) == PromotionMenu){
        return PromotionMenuInputManager(x, y, game);
    }
    return 0;
}

int PauseMenuInputManager(int x, int y, Game *game){
    Button b = WhichPauseMenuButton(x,y);
    switch (b){
        case ResumeButton:
            Game_SetState(game, Playing);
            return 1;
        case RestartButton:
            RestartGame(game);
            Game_SetState(game, Playing);
            return 1;
        case OptionsButton:
            Game_SetState(game, PauseOptionsMenu);
            break;
        case ExitButton:
            StopGame(game);
            Game_SetState(game, MainMenu);
            return 1;
        default:
            break;
    }
    return 0;
}

int PauseOptionsMenuInputManager(int x, int y, Game *game){
    Button b = WhichPauseOptionsMenuButton(x,y);
    switch (b){
        case LoadGameButton:
            //Create and show filechooser (load)
            if(LoadGame(game, window)) Game_SetState(game, PauseMenu);
            return 1;
        case SaveGameButton:
            //Create and show filechooser (save)
            SaveGame(game, window);
            return 1;
        case StopMusicButton:
            StopAllAudio();
            return 1;
        case ToggleMusicButton:
            ToggleMusic();
            return 1;
        case LoadMusicButton:
            //Create and show filechooser (load)
            //or have a list of possible songs
            //initialization of audio checks music folder
            //and add all of them beforehand
            LoadMusic(window);
            return 1;
        case ExitButton:
            Game_SetState(game, PauseMenu);
            return 1;
        default:
            break;
    }
    return 0;
}

int PromotionMenuInputManager(int x, int y, Game *game){
    Type t = WhichPromotionMenuButton(x, y);
    if (t != Pawn){
        ChessPiece* piece = Game_GetSelectedPiece(game);
        //Do Promotion Stuff
        Game_SetSelectedPiece(game, Promotion(piece, game, t));
        //Update last moved piece
        Player_SetLastMovedPiece(GetPlayer(Game_GetBoard(game), Game_GetTurn(game)), piece);
        //Set selected piece as none
        Game_SetSelectedPiece(game, NULL);

        //Update Game
        UpdateGame(game);
        Game_SetState(game, Playing);

        return 1;
    }
    return 0;
}

int EndGameMenuInputManager(int x, int y, Game *game){
    Button b = WhichEndGameMenuButton(x, y);
    switch(b){
        case RestartButton:
            //Reset Values
            RestartGame(game);
            Game_SetState(game, Playing);
            return 1;
        case ExitButton:
            StopGame(game);
            Game_SetState(game, MainMenu);;
            return 1;
        default: return 0;
    }
    return 0;
}

int MainMenuInputManager(int x, int y, Game *game){
    Button b = WhichMainMenuButton(x, y);
    switch(b){
        case StartNewGameButton:
            StartGame(game);
            //If created board successfully, plays
            if (Game_GetBoard(game) != NULL)
                Game_SetState(game, Playing);
            return 1;
        case LoadGameButton:
            if (LoadGame(game, window))
                Game_SetState(game, Playing);
            break;
        case OnlineButton:
            break;
        case OptionsButton:
            break;
        case ExitButton:
            Game_SetIsInGame(game, 0);
            return 1;
        default: break;
    }
    return 0;
}



//============================================DRAW==========================================================

//Function responsible for updating the screen every 1/FPS second
void *ScreenRefreshLoop(ALLEGRO_THREAD *thread, void *data){
    //Get window's main bitmap, set it to be used by this thread
    al_set_target_bitmap(targetbm);
    //Cast void *data
    Game *game = (Game*)data;

    //Timer triggers an event to registered event_queue every 1.0/FPS of a second
    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    al_register_event_source(graphicalEventQueue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    //Timer for misc (e.g. checkmate message time on screen)
    ALLEGRO_TIMER *miscTimer = al_create_timer(1.0);

    //Loop until exit the game
    while(Game_IsInGame(game)){
        //Wait for an event
        ALLEGRO_EVENT ev;
        al_wait_for_event(graphicalEventQueue, &ev);

        if (Game_GetState(game) == Playing || Game_GetState(game) == EndGameMenu){
            //Messages using misc timer
            if ((Game_IsCheckmate(game)) || (Game_IsCheck(game))){            //If there's a message to be shown
                if (al_get_timer_started(miscTimer)){           //If it's already being shown
                    if (al_get_timer_count(miscTimer) >= 1){    //If reached target time
                        //Stop timer and reset it's count
                        al_stop_timer(miscTimer);
                        al_set_timer_count(miscTimer, 0);
                        if (Game_IsCheckmate(game)){
                            Game_SetIsCheckmate(game, 0);
                            DrawBoardWindow(game);      //To erase checkmate message
                        }
                        else Game_SetIsCheck(game, 0);
                    }
                }
                else{                                           //If it's not being shown yet
                    if (Game_IsCheck(game)){
                        //Check message remains on-screen for 1 second
                        //After one second, it'll increase miscTimer's count by one
                        al_set_timer_speed(miscTimer, 1.0);
                    } else{
                        DrawBoardWindow(game);
                        //Checkmate message remains on-screen for 3 seconds
                        //After 3 seconds, it'll increase miscTimer's count by one
                        al_set_timer_speed(miscTimer, 3.0);
                    }
                    al_start_timer(miscTimer);
                }
            }
        }
        //FPS Timer event, update screen
        if (ev.type == ALLEGRO_EVENT_TIMER){
            Redraw(game);
        }
    }

    al_destroy_timer(timer);
    al_destroy_timer(miscTimer);

    return NULL;
}

void Redraw(Game *game){
    //Game
    DrawGameWindow(game);
    if (Game_IsCheckmate(game)){
        DrawCheckmateMessage(game);
    }
    if (Game_IsCheck(game)){
        DrawCheckMessage(game);
    }

    //Side Panel - TODO
    //DrawSidePanelWindow(game);

    //Refresh
    al_flip_display();
}

void DrawGameWindow(Game *game){
    switch (Game_GetState(game)){
        case MainMenu:
            DrawMainMenu();
            break;
        case Playing:
            DrawBoardWindow(game);
            break;
        case PauseMenu:
            //If the PauseMenu was called from PauseOptionsMenu,
            //draw board before the pause menu
            //Create previous state variable?
            DrawBoardWindow(game);
            DrawPauseMenu();
            break;
        case EndGameMenu:
            if (!Game_IsCheckmate(game))
                DrawEndGameMenu(game);
            break;
        case PromotionMenu:
            DrawPromotionMenu();
            break;
        case PauseOptionsMenu:
            DrawBoardWindow(game);
            DrawPauseOptionsMenu();
            break;
        default: return;
    }
}

void DrawBoardWindow(Game *game){
    int i;
    for (i = 0; i<8; i++){
        int j;
        for (j = 0; j<8; j++){
            DrawSquare(Game_GetBoard(game), j*SQUARE_WIDTH, i*SQUARE_HEIGHT);
        }
    }
    //If there's a selected piece, draw the selection mark and
    //the possible moves
    ChessPiece *piece = Game_GetSelectedPiece(game);
    if (piece != NULL){
        DrawSelectionMark(ChessPiece_GetX(piece) * SQUARE_WIDTH,
                          ChessPiece_GetY(piece) * SQUARE_HEIGHT);
        ShowPossibleMoves(piece, Game_GetBoard(game));
    }
}

void DrawPieceWindow(ChessPiece *piece){
    if (piece == NULL) return;
    ChessColor color = ChessPiece_GetColor(piece);
    switch (ChessPiece_GetType(piece)){
        case Pawn:
            if (color == White)
                al_draw_bitmap(imgs->whitePawnImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            else
                al_draw_bitmap(imgs->blackPawnImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            break;
        case Rook:
            if (color == White)
                al_draw_bitmap(imgs->whiteRookImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            else
                al_draw_bitmap(imgs->blackRookImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            break;
        case Knight:
            if (color == White)
                al_draw_bitmap(imgs->whiteKnightImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            else
                al_draw_bitmap(imgs->blackKnightImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            break;
        case Bishop:
            if (color == White)
                al_draw_bitmap(imgs->whiteBishopImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            else
                al_draw_bitmap(imgs->blackBishopImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            break;
        case Queen:
            if (color == White)
                al_draw_bitmap(imgs->whiteQueenImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            else
                al_draw_bitmap(imgs->blackQueenImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            break;
        case King:
            if (color == White)
                al_draw_bitmap(imgs->whiteKingImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            else
                al_draw_bitmap(imgs->blackKingImg, (ChessPiece_GetX(piece))*SQUARE_WIDTH,
                               (ChessPiece_GetY(piece))*SQUARE_HEIGHT, 0);
            break;
    }
}

//SQUARES

void ToggleSelectionMark(Game *game, int x, int y){
    if (Game_GetSelectedPiece(game) == NULL){
        //Unmark it
        DrawSquare(Game_GetBoard(game), x, y);
    }
    else{
        //Mark it
        DrawSelectionMark(x, y);
    }
}

void DrawSelectionMark(int x, int y){
    al_draw_rectangle(x+1, y+1, (x+SQUARE_WIDTH)-1, (y+SQUARE_HEIGHT)-1, al_color_name("blue") , 2);
}

void DrawSquare(ChessBoard *board, int x, int y){
    ALLEGRO_COLOR color = GetColorAtPosition(x/SQUARE_WIDTH, y/SQUARE_HEIGHT);

    al_draw_filled_rectangle(x, y, (x+SQUARE_WIDTH), (y+SQUARE_HEIGHT), color);
    //If there's piece there, draw the piece again
    ChessPiece *piece = ChessBoard_GetChessPieceAtPosition(board, x/SQUARE_WIDTH, y/SQUARE_HEIGHT);
    if (piece != NULL){
        DrawPieceWindow(piece);
    }
}

ALLEGRO_COLOR GetColorAtPosition(int x, int y){
    if (x%2 == 0){
        if (y%2 == 0) return al_color_name("white");
        else return al_color_name("black");
    } else {
        if (y%2 == 0) return al_color_name("black");
        else return al_color_name("white");
    }
}

//POSSIBLE MOVES

void ShowPossibleMoves(ChessPiece *piece, ChessBoard *board){
    if (piece == NULL) return;

    PossibleMovesList *movesList = ChessPiece_GetPossibleMovesList(piece);
    if (PossibleMovesList_IsEmpty(movesList)) return;

    PossibleMovesNode *paux = PossibleMovesList_GetFirst(movesList);
    while(paux != NULL){
        DrawSquarePossibleMove(board, PossibleMovesNode_GetX(paux), PossibleMovesNode_GetY(paux));
        if (paux == PossibleMovesList_GetLast(movesList)) return;
        paux = PossibleMovesNode_GetNextNode(paux);
    }
}

void ErasePossibleMoves(ChessPiece *piece, ChessBoard *board){
    if (piece == NULL) return;

    PossibleMovesList *movesList = ChessPiece_GetPossibleMovesList(piece);

    PossibleMovesNode *paux = PossibleMovesList_GetFirst(movesList);
    while(paux != NULL){
        DrawSquare(board, PossibleMovesNode_GetX(paux), PossibleMovesNode_GetY(paux));
        if (paux == PossibleMovesList_GetLast(movesList)) return;
        paux = PossibleMovesNode_GetNextNode(paux);
    }
}

void DrawSquarePossibleMove(ChessBoard *board, int x, int y){
    if (x%2 == 0){
        if (y%2 == 0){
            al_draw_filled_rectangle(x*SQUARE_WIDTH, y*SQUARE_HEIGHT,
                                     x*SQUARE_WIDTH+SQUARE_WIDTH,
                                     y*SQUARE_HEIGHT+SQUARE_HEIGHT,
                                     al_color_name("lightblue"));
        }
        else{
            al_draw_filled_rectangle(x*SQUARE_WIDTH, y*SQUARE_HEIGHT,
                                     x*SQUARE_WIDTH+SQUARE_WIDTH,
                                     y*SQUARE_HEIGHT+SQUARE_HEIGHT,
                                     al_color_name("darkblue"));
        }
    } else {
        if (y%2 == 0){
            al_draw_filled_rectangle(x*SQUARE_WIDTH, y*SQUARE_HEIGHT,
                                     x*SQUARE_WIDTH+SQUARE_WIDTH,
                                     y*SQUARE_HEIGHT+SQUARE_HEIGHT,
                                     al_color_name("darkblue"));
        }
        else{
            al_draw_filled_rectangle(x*SQUARE_WIDTH, y*SQUARE_HEIGHT,
                                     x*SQUARE_WIDTH+SQUARE_WIDTH,
                                     y*SQUARE_HEIGHT+SQUARE_HEIGHT,
                                     al_color_name("lightblue"));
        }
    }
    DrawPieceWindow(ChessBoard_GetChessPieceAtPosition(board, x, y));
}

//MENU

void DrawPauseMenu(){
    al_draw_bitmap(imgs->pauseMenuImg, 120, 120, 0);
}

void DrawPauseOptionsMenu(){
    al_draw_bitmap(imgs->pauseOptionsMenuImg, 0, 0, 0);
}

void DrawPromotionMenu(){
    al_draw_bitmap(imgs->promotionMenuImg, 120, 120, 0);
}

void DrawEndGameMenu(Game *game){
    al_draw_bitmap(imgs->endGameMenuImg, 120, 120, 0);
}

void DrawMainMenu(){
    al_draw_bitmap(imgs->mainMenuImg, 0, 0, 0);
}

//CHECK

void DrawCheckMessage(Game *game){
    int fontSize = 44;
    ALLEGRO_FONT *font = al_load_font("resources/fonts/airstrike.ttf", fontSize, 0);

    //Box
    al_draw_bitmap(imgs->msgBoxImg, 0, 180, 0);
    //Mesage
    al_draw_textf(font, al_map_rgb(255, 0, 0), BOARD_WIDTH/2 + BOARD_POS_X, BOARD_HEIGHT/2 - 20 + BOARD_POS_Y,
                  ALLEGRO_ALIGN_CENTRE, "%s King In Check", ColorToString(Game_GetTurn(game)));

    al_destroy_font(font);
}

void DrawCheckmateMessage(Game *game){
    int fontSize = 44;
    ALLEGRO_FONT *font = al_load_font("resources/fonts/airstrike.ttf", fontSize, 0);

    //Box
    al_draw_bitmap(imgs->msgBoxImg, 0, 180, 0);
    //Mesage
    al_draw_text(font, al_map_rgb(0, 0, 255), BOARD_WIDTH/2 + BOARD_POS_X, 200, ALLEGRO_ALIGN_CENTRE,
                 "Checkmate!");
    al_draw_textf(font, al_map_rgb(0, 0, 255), BOARD_WIDTH/2 + BOARD_POS_X, 244, ALLEGRO_ALIGN_CENTRE,
                  "%s won!", Player_GetName(GetPlayer(Game_GetBoard(game), !Game_GetTurn(game))));

    al_destroy_font(font);
}

char* ColorToString(ChessColor color){
    if (color == White) return "White";
    else return "Black";
}

//SIDE PANEL - TODO

/*void DrawSidePanelWindow(Game *game){
    int fontSize = 20;
    ALLEGRO_FONT *font = al_load_font("resources/fonts/airstrike.ttf", fontSize, 0);

    //Background
    ALLEGRO_COLOR color = al_color_name("white");
    al_draw_filled_rectangle(SIDE_PANEL_POS_X, SIDE_PANEL_POS_Y,
                             SIDE_PANEL_POS_X + SIDE_PANEL_WIDTH,
                             SIDE_PANEL_POS_Y + SIDE_PANEL_HEIGHT, color);
    al_draw_rectangle(SIDE_PANEL_POS_X+2, SIDE_PANEL_POS_Y+2,
                        SIDE_PANEL_POS_X + SIDE_PANEL_WIDTH,
                        SIDE_PANEL_POS_Y + SIDE_PANEL_HEIGHT,
                        al_color_name("red") , 5);

    //Players
    if (game->turn == White) color = al_map_rgb(0, 0, 255);     //Blue
    else color = al_map_rgb(0,0,0);                             //Black

    //Player1
    al_draw_textf(font, color, 560, 300, ALLEGRO_ALIGN_CENTRE,
                  "%s", Game_GetBoard(game)->player1->name);

    if (game->turn == Black) color = al_map_rgb(0, 0, 255);     //Blue
    else color = al_map_rgb(0,0,0);                             //Black

    //Player2
    al_draw_textf(font, color, 560, 100, ALLEGRO_ALIGN_CENTRE,
                  "%s", Game_GetBoard(game)->player2->name);

    al_destroy_font(font);
}*/

//FINALIZE

void FinalizeAllegroGUI(ALLEGRO_DISPLAY *window){
    free(imgs);

    al_destroy_event_queue(graphicalEventQueue);
    al_destroy_event_queue(inputEventQueue);

    FinalizeAudio();

    al_destroy_display(window);
}
