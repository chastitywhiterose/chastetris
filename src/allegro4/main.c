/* Allegro example */

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#include "allegro4_chastefont.h"

int width=640,height=480;
int driver=GFX_AUTODETECT_WINDOWED;


BITMAP *the_image;
PALETTE the_palette;
char filename[256]; /*filename that may be used at some point*/
char text[256]; /*usually used to store text that will be drawn*/


int main(void)
{
 int x,y;
 int rect_size; /*size of squares*/
 int radius; /*size of circle*/


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

   /* clear the screen to white */
   clear_to_color(screen, makecol(0, 255, 255));

   radius=height/2;
   x=width/2;y=height/2;
   circlefill(screen, x, y, radius,makecol(255,0,255));

   rect_size=height/3;
   x=width/2-rect_size/2;y=height/2;
   rectfill(screen,x,y,x+rect_size,y+rect_size,makecol(255,255,0));   
   
   /*next step is to load some fonts*/

 font_8=chaste_font_load("./font/FreeBASIC Font 8.tga");
 font_16=chaste_font_load("./font/FreeBASIC Font 16.tga");
 font_32=chaste_font_load("./font/FreeBASIC Font 32.tga");
 font_64=chaste_font_load("./font/FreeBASIC Font 64.tga");
 font_128=chaste_font_load("./font/FreeBASIC Font 128.tga");
 
 main_font=font_64; /*select which loaded font to use*/

 x=main_font.char_width*2;
 sprintf(text,"Circle");
 chaste_font_draw_string(text,x,main_font.char_height*2);

main_font=font_16;
 
 x=main_font.char_width*16;
 sprintf(text,"Square");
 chaste_font_draw_string(text,x,main_font.char_height*20);


   /* wait for a key press */
   readkey();

   return 0;
}

END_OF_MAIN()

/* gcc main.c -o main -lalleg && ./main */
