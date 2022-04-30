/*
 This is a small project called "Game Base".
 The idea is to first have a working program that compiles and creates a window when run.
*/

/*include the standard headers*/
#include <stdio.h>

/*include the required Allegro headers*/
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

/*variables defining the image/screen*/
ALLEGRO_DISPLAY *display=NULL;
const int width=1280,height=720;
ALLEGRO_BITMAP *screenbitmap;

/*variables defining the event loop*/
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT ev;
int loop;

char gamename[256];
int blocks_used=7;

char text[0x200]; /*where text is stored before being written*/
int text_x; /*the x position of where text will go*/
int move_id;

FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/

int frame=0;

#include "chastetris.h"
#include "allegro_chastefont.h"
#include "allegro_gameloop.h"

/*the main function initializes all the Allegro stuff*/
int main(int argc, char **argv)
{
 /*Must always call this to initialize allegro.*/
 if(!al_init()) {  fprintf(stderr, "failed to initialize allegro!\n");  return -1; }

 /*load the image addon, for saving to files*/
 if(!al_init_image_addon()) {  fprintf(stderr, "failed to initialize image addon!\n");  return -1; }

 /*To use keyboard presses*/
 if(!al_install_keyboard()) { fprintf(stderr, "failed to initialize the keyboard!\n");  return -1; }

 event_queue = al_create_event_queue(); /*Set up events from keyboard and the display.*/
 if(!event_queue)
 {
  fprintf(stderr, "failed to create event_queue!\n");
  return -1;
 }
 al_register_event_source(event_queue, al_get_keyboard_event_source());

 if(!al_init_primitives_addon()) /*For drawing shapes*/
 {
  fprintf(stderr, "failed to initialize allegro_primitives!\n");
  return -1;
 }

 al_set_new_window_title("Chastity's Game using Allegro");

 display=al_create_display(width,height);
 if(!display){fprintf(stderr,"failed to create display!\n");return -1;}

 /*this next line is required to end the program by clicking the X*/
 al_register_event_source(event_queue, al_get_display_event_source(display));


/*opening the input and output files*/

/*open the file to record moves*/
 sprintf(filename,"omovelog.txt");
 fp=fopen(filename,"wb+");
 if(fp==NULL){printf("Failed to create file \"%s\".\n",filename); return 1;}

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

 /*the name of the game depends on the blocks_used variable*/
 if(blocks_used==1)
 { 
  sprintf(gamename,"Long Boi");
 }
 else
 {
  sprintf(gamename,"Chaste Tris");
 }


/*next step is to load some fonts*/

 font_8=chaste_font_load("./font/FreeBASIC Font 8.png");
 font_16=chaste_font_load("./font/FreeBASIC Font 16.png");
 font_32=chaste_font_load("./font/FreeBASIC Font 32.png");
 font_64=chaste_font_load("./font/FreeBASIC Font 64.png");




 screenbitmap=al_get_backbuffer(display);
 al_set_target_bitmap(screenbitmap);

 /*display the welcome screen*/

 welcome_screen_chaste_font();

 main_font=font_64; /*make the correct font for game loop*/

 /*next, begin the game*/
 allegro_chastetris();

 al_destroy_display(display);
 al_destroy_event_queue(event_queue);

 return 0;
}
/*

This program can be compiled under Linux with:

gcc -Wall -ansi -pedantic main.c -o main -lallegro -lallegro_primitives -lallegro_image && ./main

It makes use of the main Allegro library as well as these addons.

 allegro_primitives: for drawing triangles
 allegro_image: for saving the output to image files

For more information on Allegro:
https://liballeg.org/

*/
