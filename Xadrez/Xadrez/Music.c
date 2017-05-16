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
#define ROWS 64.0
#define TEMPO 150.0
#define FRAME_TIME ((ROWS/4)/(TEMPO/60))

#include "Music.h"

#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

Songs *songs;

void InitializeAudio(void){
    al_init_acodec_addon();
    al_install_audio();
    al_reserve_samples(NUMBER_OF_SONGS);
    LoadStreams();
    al_set_mixer_playing(al_get_default_mixer(), 1);
}

void LoadSong1(void){
    //Load file
    ALLEGRO_AUDIO_STREAM *song1stream = NULL;
    song1stream = al_load_audio_stream("resources/music/test125.wav", 4, 1024);
    //Set loop timestamps
    float loop_start = FRAME_TIME*3, loop_end = FRAME_TIME*18;
    al_set_audio_stream_loop_secs(song1stream, loop_start, loop_end);

    al_set_audio_stream_playmode(song1stream, ALLEGRO_PLAYMODE_LOOP);
    songs->song1 = song1stream;
}
void LoadSong2(void){
    //Load file
    ALLEGRO_AUDIO_STREAM *song2stream = NULL;
    song2stream = al_load_audio_stream("resources/music/test126.wav", 4, 1024);
    //Set loop timestamps
    float loop_start = FRAME_TIME*2, loop_end = FRAME_TIME*22;
    al_set_audio_stream_loop_secs(song2stream, loop_start, loop_end);

    al_set_audio_stream_playmode(song2stream, ALLEGRO_PLAYMODE_LOOP);
    songs->song2 = song2stream;
}

void LoadUserSong(const char *path){
    //Load file
    ALLEGRO_AUDIO_STREAM *userSongStream = NULL;
    userSongStream = al_load_audio_stream(path, 4, 1024);

    al_set_audio_stream_playmode(userSongStream, ALLEGRO_PLAYMODE_LOOP);
    if (userSongStream == NULL) return;
    songs->userSong = userSongStream;
}

void LoadStreams(void){
    songs = malloc(sizeof(Songs));
    songs->current = NULL;
    songs->userSong = NULL;

    LoadSong1();
    LoadSong2();
}

void FinalizeAudio(void){
    if (songs->current != NULL){
        al_drain_audio_stream(songs->current);
    }
    al_destroy_audio_stream(songs->song1);
    al_destroy_audio_stream(songs->song2);
    if (songs->userSong != NULL)
        al_destroy_audio_stream(songs->userSong);

    free(songs);
}

void PlaySong(char name[]){
    if (strcmp(name, "test125") == 0){
        if (songs->current != songs->song1){
            if (songs->current != NULL){
                al_seek_audio_stream_secs(songs->current, 0.0);
                al_set_audio_stream_playing(songs->current, 0);
                al_detach_audio_stream(songs->current);
                al_drain_audio_stream(songs->current);
            }
            al_attach_audio_stream_to_mixer(songs->song1, al_get_default_mixer());
            songs->current = songs->song1;
        }
    }
    else if (strcmp(name, "test126") == 0){
        if (songs->current != songs->song2){
            if (songs->current != NULL){
                al_seek_audio_stream_secs(songs->current, 0.0);
                al_set_audio_stream_playing(songs->current, 0);
                al_detach_audio_stream(songs->current);
                al_drain_audio_stream(songs->current);
            }
            al_attach_audio_stream_to_mixer(songs->song2, al_get_default_mixer());
            songs->current = songs->song2;
        }
    }
    else if (strcmp(name, "user_song") == 0){
        if (songs->current != songs->userSong){
            if (songs->current != NULL){
                al_seek_audio_stream_secs(songs->current, 0.0);
                al_set_audio_stream_playing(songs->current, 0);
                al_detach_audio_stream(songs->current);
                al_drain_audio_stream(songs->current);
            }
            al_attach_audio_stream_to_mixer(songs->userSong, al_get_default_mixer());
            songs->current = songs->userSong;
        }
    }

    al_seek_audio_stream_secs(songs->current, 0.0);
    if (!al_get_audio_stream_playing(songs->current))
        al_set_audio_stream_playing(songs->current, 1);
}

void ToggleMusic(void){
    if (songs->userSong == NULL){
        if (songs->current == NULL)
            PlaySong("test125");
        else if (songs->current == songs->song1)
            PlaySong("test126");
        else if (songs->current == songs->song2)
            PlaySong("test125");
        return;
    }

    srand(time(NULL));

    int r = rand()%3;
    if (r == 0)
        if (songs->current != songs->song1)
            PlaySong("test125");
        else PlaySong("test126");
    else if (r == 1)
        if (songs->current != songs->song2)
            PlaySong("test126");
        else PlaySong("user_song");
    else{
        if (songs->current != songs->userSong)
            PlaySong("user_song");
        else PlaySong("test125");
    }
}

void StopAllAudio(void){
    al_set_mixer_playing(al_get_default_mixer(), 0);
    songs->current = NULL;
}

int LoadMusic(ALLEGRO_DISPLAY *display){
    ALLEGRO_FILECHOOSER* fc = NULL;
    fc = al_create_native_file_dialog("resources/music/", "Load Music", "*.*", ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
    if (fc == NULL) return 0;

    al_show_native_file_dialog(display, fc);

    //Get Path
    const char *path = NULL;
    if (al_get_native_file_dialog_count(fc) > 0){
        path = al_get_native_file_dialog_path(fc, 0);
    } else return 0;
    if (path == NULL){
        al_destroy_native_file_dialog(fc);
        return 0;
    }

    //Load
    LoadUserSong(path);
    //Play
    PlaySong("user_song");

    al_destroy_native_file_dialog(fc);

    return 1;
}
