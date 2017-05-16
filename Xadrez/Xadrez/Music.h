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

#ifndef MUSIC_H
#define MUSIC_H

#include <allegro5/allegro_audio.h>

typedef struct songs{
    ALLEGRO_AUDIO_STREAM* song1;
    ALLEGRO_AUDIO_STREAM* song2;
    ALLEGRO_AUDIO_STREAM* userSong;

    ALLEGRO_AUDIO_STREAM* current;
}Songs;

void InitializeAudio(void);
void LoadStreams(void);
void FinalizeAudio(void);
void PlaySong(char name[]);
void StopAllAudio(void);
void ToggleMusic(void);
int LoadMusic(ALLEGRO_DISPLAY *display);

//AUDIO VALUES
#define NUMBER_OF_SONGS 3

#endif // MUSIC_H
