/*
SDL Chaste Tris 3

This is version 3 of Chaste Tris.

Version 1 used only software surfaces.
Version 2 used the modern hardware renderer
Version 3 has all the features of version 2 but also includes music and possible future updates!

For more information see the SDL wiki here:
https://wiki.libsdl.org/SDL2/CategoryRender
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <SDL.h>
#include <SDL_mixer.h>

/*
most variables in the program are global. Unless I create temporary variables in other functions.
*/
int width=1280,height=720;
int loop=1;
int Window_Flags=0;
SDL_Window *window = NULL;
/*SDL_Surface *surface;*/
SDL_Renderer *renderer = NULL;
SDL_Event e;
SDL_Rect rect;

int rect_color;

int fps=60; /*frames per second*/

int frame=0,lastframe=0,delay,framelimit=1; /*only used for animation demos*/
time_t time0,time1;
int seconds,minutes,hours; /*to keep track of time*/
int sdl_time,sdl_time1;

char gamename[256];
int blocks_used=7;

char text[0x200];
char movetext[256],move_id;
int text_x; /*the x position of where text will go*/

FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/

int songs=3,song_index=0,music_is_on=0;
char *music_files[]=
{
 "music/Tetris_Gift_from_Moscow_OC_ReMix.mp3",
 "music/Tetris_T-Spin_OC_ReMix.mp3",
 "music/Chrono_Trigger_Protector_in_Green_OC_ReMix.mp3"
};

Mix_Chunk *music[3]; /*chunks the music is loaded into*/

#include "sdl_chaste_music.h"

#include "chastetris.h"
#include "chastetris_gamesave.h"
#include "chaste_the_rainbow.h"
#include "sdl_chastefont_texture.h"
#include "sdl_grid_draw.h"
#include "sdl_input.h"
#include "sdl_chaste_polygon.h"
#include "sdl_graphics.h"

/*variables for SDL_mixture features*/





int main(int argc, char **argv)
{

 /*process command line arguments*/
 int x=1,y;
 while(x<argc)
 {
  printf("argv[%i]=%s\n",x,argv[x]);

  if(strcmp(argv[x],"-longboi")==0)
  {
   printf("Long Boi mode activated! Only the I blocks will spawn!\n");
   blocks_used=1;
  }
  
  if(strcmp(argv[x],"-tgirl")==0)
  {
   printf("T Girl mode activated! Only the T blocks will spawn!\n");
   block_type=1;
   blocks_used=1;
  }

  if(strcmp(argv[x],"-fullscreen")==0)
  {
   width=1920;height=1080;
   Window_Flags=SDL_WINDOW_FULLSCREEN_DESKTOP;
  }

  if( strcmp(argv[x],"-fps")==0 )
  {
   printf("Default fps is %d\n",fps);
   return 1;
  }

  if( strncmp(argv[x],"-fps=",5)==0 )
  {
   printf("Changing fps:\n");
   y=sscanf(argv[x]+5,"%d",&fps);
   if(y)
   {
    printf("fps is now set to %d\n",fps);
   }
  }

  x++;
 }

 if(SDL_Init(SDL_INIT_VIDEO)){printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;}
 window=SDL_CreateWindow( "SDL Chaste Tris",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,Window_Flags);
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 renderer = SDL_CreateRenderer(window,-1,0);
 if(renderer==NULL){printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 
 /*printf("Testing\n");return 0;*/


/*
 To play music, we need to initialize all audio.
 This is the section to handle it. First all the music is loaded. Then the mix_test or game is played.
 At the end, the music is freed and shut down.
*/

chaste_audio_init(); /*get the audio device ready*/

 /*load all songs*/
 x=0;
 while(x<songs)
 {
  music[x]=chaste_audio_load(music_files[x]);
  x++;
 }

 sprintf(filename,"imovelog.txt");
 fp_input=fopen(filename,"rb+");
 if(fp_input==NULL)
 {
  printf("Failed to open input file \"%s\".\n",filename);
  printf("This is not an error. It just means input is keyboard only. \"%s\".\n",filename);
 }
 else
 {
  printf("input file \"%s\" is opened.\n",filename);
  printf("Will read commands from this file before keyboard. \"%s\".\n",filename);
 }

 sprintf(gamename,"Chaste Tris");

 font_8=chaste_font_load("./font/FreeBASIC Font 8.bmp");
 main_font=font_8;

 chaste_palette_rainbow(40);
 /*chaste_palette_rainbow_pastel(80);*/
 /*chaste_palette_view();*/

 welcome_screen_chaste_font();

 /*start music when the game begins*/
 song_index=1;
 chaste_audio_play(music[song_index]);
 music_is_on=1;

 sdl_chastetris();
 
  /*
  After the game ends, we will attempt to save the movelog to a file.
  Keeping the movelog in memory and only writing at the end speeds up the program and simplifies things.
 */
 
  /*open the file to record moves*/
 sprintf(filename,"omovelog.txt");
 fp=fopen(filename,"wb+");
 if(fp==NULL){printf("Failed to create file \"%s\".\n",filename);}
 else
 {
  x=0;
  while(x<moves)
  {
   /*printf("%d %c\n",x,move_log[x]);*/
   fputc(move_log[x],fp);
   x++;
  }
 }

 if(fp!=NULL){fclose(fp);}
 if(fp_input!=NULL){fclose(fp_input);}

 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);

  /*unload and free the music*/
 x=0;
 while(x<songs)
 {
  if(music[x]!=NULL)
  {
   Mix_FreeChunk(music[x]);
   music[x]=NULL;
  }
  x++;
 }
 
  if (audio_open)
  {
   Mix_CloseAudio();
   audio_open = 0;
  }
  /*end of music closing section*/

 SDL_Quit();

 chaste_font_free(font_8);

 return 0;
}

