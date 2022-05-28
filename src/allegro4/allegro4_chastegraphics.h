/*
allegro Chaste Graphics

This file is meant to help assist me as I learn Allegro 4 and make DOS games. The idea is a simple collection of graphics demos to prove what can or cannot be done.

*/


/*
This function assumes graphics mode has already been set to 640x480 and my fonts have been loaded.
It draws a circle and a square and then labels them with text with my own personal font drawing routines
*/
void circle_and_square()
{
 int x,y;
 int rect_size; /*size of squares*/
 int radius; /*size of circle*/
 char text[0x200];

 clear_to_color(screen, makecol(0, 255, 255));

 radius=height/2;
 x=width/2;y=height/2;
 circlefill(screen, x, y, radius,makecol(255,0,255));

 rect_size=height/3;
 x=width/2-rect_size/2;y=height/2;
 rectfill(screen,x,y,x+rect_size,y+rect_size,makecol(255,255,0));   

 main_font=font_64; /*select which loaded font to use*/

 x=main_font.char_width*2;
 sprintf(text,"Circle");
 chaste_font_draw_string(text,x,main_font.char_height*2);

 main_font=font_16;
 
 x=main_font.char_width*16;
 sprintf(text,"Square");
 chaste_font_draw_string(text,x,main_font.char_height*20);


}



/*
Chaste Checker, also known originally as Chastity Checker from my BBM library,has been revived
This is an extremely fast checkerboard drawing routine.
*/
void chaste_checker()
{
 int x,y;
 int rect_size;
 int colors[2],index,index1;
 
 colors[0]=makecol(0,0,0);
 colors[1]=makecol(255,255,255);
 
 rect_size=32;
 
 index=0;
 
 y=0;
 while(y<height)
 {
  index1=index;
  x=0;
  while(x<width)
  {
   rectfill(screen,x,y,x+rect_size,y+rect_size,colors[index]);
   index^=1; 
   x+=rect_size;
  }
  index=index1^1;
 
  
  y+=rect_size;
 }
 

}
