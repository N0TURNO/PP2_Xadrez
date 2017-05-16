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

#ifndef MENU_H
#define MENU_H

#include "ChessPiece.h"

typedef enum button{
    //In Game Buttons
    NoButton,
    ResumeButton, RestartButton,
    OptionsButton,
    //Main Menu Buttons
    StartNewGameButton, LoadGameButton,
    OnlineButton,
    //Pause Options Menu
    SaveGameButton,
    StopMusicButton, LoadMusicButton,
    ToggleMusicButton,

    ExitButton
}Button;

//MAIN MENU
Button WhichMainMenuButton(int x, int y);

//PAUSE MENU
Button WhichPauseMenuButton(int x, int y);

//PAUSE OPTIONS MENU
Button WhichPauseOptionsMenuButton(int x, int y);

//PROMOTION MENU
Type WhichPromotionMenuButton(int x, int y);

//END GAME MENU
Button WhichEndGameMenuButton(int x, int y);


#endif // MENU_H
