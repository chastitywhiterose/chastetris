/*
allegro Chaste Graphics

This file is meant to help assist me as I learn Allegro 4 and make DOS games. The idea is a simple collection of graphics demos to prove what can or cannot be done.

*/

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
 
 rect_size=8;
 
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
 
 readkey();
}
