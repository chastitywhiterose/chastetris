/* Allegro example */

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

int width=640,height=480;
int driver=GFX_AUTODETECT_WINDOWED;

#include "allegro4_chastefont.h"
#include "allegro4_chastegraphics.h"

int loop=1; /*determine whether the game is running or not*/
char gamename[256];
int blocks_used=7;

char text[0x200]; /*where text is stored before being written*/
int text_x; /*the x position of where text will go*/
int move_id;

FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/
int frame=0,fps;

#include "chastetris.h"
#include "allegro4_keyboard.h"
#include "allegro4_gameloop.h"

int main(void)
{
 /* you should always do this at the start of Allegro programs */
 if (allegro_init() != 0)
      return 1;

   /* set up the keyboard handler */
   install_keyboard();
   
   set_color_depth(32);

   /* set a graphics mode */
   if(set_gfx_mode(driver,width,height,0,0)!=0)
   {
    allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
    return 1;
   }

   /* set the color palette */
   /*set_palette(desktop_palette);*/

   /* clear the screen to black */
   clear_to_color(screen, makecol(0,0,0));
   
   clear_to_color(screen, makecol(0,255,0)); /*green*/
   
   /*
    Now that the graphics mode is set and the background color chosen, it's important to open the input and output files.
    If they are not open, weird crashes happen because fputc is called on most keypresses expecting to write to omovelog.txt .
   */

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

 font_8=chaste_font_load("./font/FreeBASIC Font 8.tga");
 font_16=chaste_font_load("./font/FreeBASIC Font 16.tga");
 font_32=chaste_font_load("./font/FreeBASIC Font 32.tga");
 font_64=chaste_font_load("./font/FreeBASIC Font 64.tga");
 font_128=chaste_font_load("./font/FreeBASIC Font 128.tga");
 
/*   circle_and_square();*/
   
   /*chaste_checker();*/

/*
  main_font=font_64;
  sprintf(text,"%d",height/24);
  chaste_font_draw_string(text,0,main_font.char_height*2);
*/


allegro4_chastetris();

   /* wait for a key press */
   /*readkey();*/
   

   return 0;
}

END_OF_MAIN()

/* gcc main.c -o main -lalleg && ./main */
