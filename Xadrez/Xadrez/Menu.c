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

#include "Menu.h"
#include "GUIAllegro.h"

//Values specific for their images

Button WhichEndGameMenuButton(int x, int y){
    if ((x >= 120 + 49) && (x <= 120 + 190) && (y >= 120 + 111) && (y <= 120 + 132))
        return RestartButton;
    if ((x >= 120 + 83) && (x <= 120 + 156) && (y >= 120 + 164) && (y <= 120 + 185))
        return ExitButton;

    return NoButton;
}

Button WhichPauseMenuButton(int x, int y){
    if ((x >= 120 + 57) && (x <= 120 + 183) && (y >= 120 + 57) && (y <= 120 + 78))
        return ResumeButton;
    if ((x >= 120 + 49) && (x <= 120 + 190) && (y >= 120 + 105) && (y <= 120 + 126))
        return RestartButton;
    if ((x >= 120 + 56) && (x <= 120 + 186) && (y >= 120 + 153) && (y <= 120 + 174))
        return OptionsButton;
    if ((x >= 120 + 83) && (x <= 120 + 156) && (y >= 120 + 201) && (y <= 120 + 222))
        return ExitButton;

    return NoButton;
}

Button WhichMainMenuButton(int x, int y){
    if ((x >= 139) && (x <= 339) && (y >= 213) && (y <= 235))
        return StartNewGameButton;
    if ((x >= 176) && (x <= 307) && (y >= 252) && (y <= 272))
        return LoadGameButton;
    if ((x >= 199) && (x <= 280) && (y >= 280) && (y <= 310))
        return OnlineButton;
    if ((x >= 192) && (x <= 289) && (y >= 320) && (y <= 342))
        return OptionsButton;
    if ((x >= 211) && (x <= 267) && (y >= 353) && (y <= 375))
        return ExitButton;

    return NoButton;
}

Type WhichPromotionMenuButton(int x, int y){
   if ((x >= 120 + 72) && (x <= 120 + 169) && (y >= 120 + 59) && (y <= 120 + 76))
        return Queen;
    if ((x >= 120 + 76) && (x <= 120 + 163) && (y >= 120 + 98) && (y <= 120 + 115))
        return Rook;
    if ((x >= 120 + 61) && (x <= 120 + 179) && (y >= 120 + 139) && (y <= 120 + 156))
        return Bishop;
    if ((x >= 120 + 61) && (x <= 120 + 177) && (y >= 120 + 180) && (y <= 120 + 197))
        return Knight;

    return Pawn;
}

Button WhichPauseOptionsMenuButton(int x, int y){
    if ((x >= 10) && (x <= 180) && (y >= 168) && (y <= 190))
        return LoadGameButton;
    if ((x >= 10) && (x <= 182) && (y >= 261) && (y <= 283))
        return SaveGameButton;
    if ((x >= 284) && (x <= 470) && (y >= 168) && (y <= 190))
        return StopMusicButton;
    if ((x >= 259) && (x <= 470) && (y >= 213) && (y <= 235))
        return ToggleMusicButton;
    if ((x >= 286) && (x <= 473) && (y >= 261) && (y <= 283))
        return LoadMusicButton;
    if ((x >= 197) && (x <= 269) && (y >= 414) && (y <= 436))
        return ExitButton;

    return NoButton;
}
