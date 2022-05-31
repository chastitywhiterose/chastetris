/*
 Chaste Tris DOS version
 Using Allegro 4

 This version is heavily modified from the Linux version I first made
 with Allegro 4. The 640x480 resolution was used in it but sadly did not
 work properly when using it under DOS.

 Instead it selects a GFX_SAFE mode and everything has
 been redesigned with this view in mind.
 For some reason, this is 320x200.

 Additionally all file input/output has been removed. It was too
 slow for a DOS environment. Now there are no timers at all.
 Things only happen when a key is pressed.

 Also, my own font routines are not included.
 The functions built into Allegro are faster.

*/

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

int width,height; /*will be set later*/

#include "a4graph.h"

int loop=1; /*determine whether the game is running or not*/
char gamename[256];
int blocks_used=7;

char text[0x200]; /*where text is stored before being written*/
int text_x; /*the x position of where text will go*/
int move_id;

char filename[256]; /*name of move log file*/
int frame=0,fps=60,rest_time;

#include "ct.h"
#include "a4keyb.h"
#include "a4game.h"

int main(void)
{
 /* you should always do this at the start of Allegro programs */
 if (allegro_init() != 0)
      return 1;

   /* set up the keyboard handler */
   install_keyboard();
   
   /*set_color_depth(32);*/

   printf("Attempting to open a graphics mode.");

   /* set a graphics mode */
   if(set_gfx_mode(GFX_SAFE,0,0,0,0)!=0)
   {
    allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
    return 1;
   }

width=screen->w;
height=screen->h;

/* set the color palette */
/*   set_palette(desktop_palette);*/


 /*the name of the game depends on the blocks_used variable*/
 if(blocks_used==1)
 { 
  sprintf(gamename,"Long Boi");
 }
 else
 {
  sprintf(gamename,"Chaste Tris");
 }

   
 
   
/*   chaste_checker();*/

/*
  main_font=font_64;
  sprintf(text,"%d",height/24);
  chaste_font_draw_string(text,0,main_font.char_height*2);
*/

/*welcome_screen_chaste_font();*/
allegro4_chastetris();

/*
Set screen back to text more before ending program.
*/
set_gfx_mode(GFX_TEXT,0,0,0,0);

/* printf("width=%d\n",width);
 printf("height=%d\n",height);*/

 printf("Thank you for playing Chaste Tris for DOS");

 return 0;
}

END_OF_MAIN()

/* gcc main.c -o main -lalleg && ./main */
