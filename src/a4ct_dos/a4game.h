/*
allegro 4 gameloop

This file contains only the main gameloop and a few other tools
*/

/* this function is now the official welcome screen*/
void welcome_screen_chaste_font()
{
 int fontsize=8;
 int color=makecol(255,255,255);
 clear_to_color(screen, makecol(0,0,0));


 text_x=fontsize*1;

 sprintf(text,"%s","Chaste\n Tris");

 textout_ex(screen, font, text, text_x,fontsize*1, color,-1);



 text_x=fontsize*2;


 sprintf(text,"Programming: Chastity White Rose");
 textout_ex(screen, font, text, text_x,fontsize*12, color,-1);

 sprintf(text,"Inspiration:    River Black Rose");
 textout_ex(screen, font, text, text_x,fontsize*13, color,-1);


 sprintf(text,"Email: chastitywhiterose@gmail.com");

 textout_ex(screen, font, text, text_x,fontsize*15, color,-1);
 
 sprintf(text,"Press Enter to Begin game.");

 textout_ex(screen, font, text, text_x,fontsize*17, color,-1);

 sprintf(text,"https://github.com/chastitywhiterose/chastetris");

 textout_ex(screen, font, text, text_x,fontsize*20, color,-1);

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the\nC Programming Language. The font handling is done with the font library\nChastity wrote and named Chaste Font.\nAllegro is used for the graphics API including rectangles and textures.\nCredit goes to Alexey Pajitnov for creating the original Tetris game which\nChaste Tris is based on.");

 textout_ex(screen, font, text, text_x,fontsize*25, color,-1);

 /* wait for a key press */
 readkey();

}




/*
this function draws the stats of the game such as the lines and score using my chaste font routines
it's in a separate function so that I can switch it out with another function when I feel like it
*/
void draw_stats_chaste_font()
{
 int color=makecol(255,255,255);
 int fontsize=8;

 text_x=fontsize*1;



 textout_ex(screen, font, gamename, text_x,fontsize*1, color,-1);


 sprintf(text,"Score:%d",score);
 textout_ex(screen, font, text, text_x,fontsize*3, color,-1);

 sprintf(text,"Lines:%d",lines_cleared_total);
 textout_ex(screen, font, text, text_x,fontsize*4, color,-1);

  sprintf(text,"This:%c",main_block.id);
  textout_ex(screen, font, text, text_x,fontsize*5, color,-1);


  sprintf(text,"Hold:%c",hold_block.id);
  textout_ex(screen, font, text, text_x,fontsize*6, color,-1);

  sprintf(text,"Move:%d",moves);
 textout_ex(screen, font, text, text_x,fontsize*7, color,-1);

  sprintf(text,"B2B:%d",back_to_back);
 textout_ex(screen, font, text, text_x,fontsize*8, color,-1);

}




/*
this is a function which is called by main after window is created. It is the game loop.
*/
void allegro4_chastetris()
{
 int pixel,r,g,b;
 int x=0,y=0;

 int rect_color;


 int block_size=height/grid_height;
 int grid_offset_x=block_size*1; /*how far from the left size of the window the grid display is*/
 int border_size=8; /*set custom border width alternative to block_size*/
 
 grid_offset_x=(width-(20/2*block_size))/2;

 printf("block_size==%d\n",block_size);

 chastetris_info();

 spawn_block();


 /*first empty the grid*/
 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   main_grid.array[x+y*grid_width]=empty_color;
   x+=1;
  }
  y+=1;
 }
 

  /* Loop until the user closes the window */
 loop=1;
 while(loop)
 {

/*  chaste_checker();*/
 clear_to_color(screen, makecol(0,0,0));

  

 /*make backup of entire grid*/
  temp_grid=main_grid;

  /*draw block onto temp grid at it's current location*/
  y=0;
  while(y<max_block_width)
  {
   x=0;
   while(x<max_block_width)
   {
    if(main_block.array[x+y*max_block_width]!=0)
    {
     if( temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]!=0 )
     {
      printf("Error: Block in Way\n");

      /*because a collision has occurred. We will restore everything back to the way it was before block was moved.*/

      break;
     }
     else
     {
      temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]=main_block.color;
     }
    }
    x+=1;
   }
   y+=1;
  }



/*display the tetris grid*/

 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   pixel=temp_grid.array[x+y*grid_width];
   r=(pixel&0xFF0000)>>16;
   g=(pixel&0x00FF00)>>8;
   b=(pixel&0x0000FF);

/*
 printf("x=%d y=%d ",x,y);
 printf("red=%d green=%d blue=%d\n",r,g,b);
*/

rect_color=makecol(r, g, b);

 rectfill(screen,grid_offset_x+x*block_size, y*block_size, grid_offset_x+(x+1)*block_size-1, (y+1)*block_size-1, rect_color);

   x+=1;
  }
  y+=1;
 }


rect_color=makecol(127, 127, 127);

 /*draw the boundary walls using block_size as the width. This was the first method.*/

/*rectfill(screen,grid_offset_x-block_size, 0*block_size, grid_offset_x-1, height-1, rect_color);
rectfill(screen,grid_offset_x+grid_width*block_size, 0*block_size, grid_offset_x+grid_width*block_size+block_size-1, height-1, rect_color);*/

/*rect_color=makecol(0, 0, 255);*/

 /*draw the boundary walls using border_size as the width. This was the second method. It allows more space for text*/
rectfill(screen,grid_offset_x-border_size, 0*block_size, grid_offset_x-1, height-1, rect_color);
rectfill(screen,grid_offset_x+grid_width*block_size, 0*block_size, grid_offset_x+grid_width*block_size+border_size-1, height-1, rect_color);



 /*end of drawing code for grid*/

 draw_stats_chaste_font();


 /*
 optionally save frame as file
 make comparison moves>=frame to ensure frames are only saved for successful moves.
 use moves<frame to make sure that no frames are ever saved
*/

 /*if(moves>=frame) { TakeScreenshot_frame(); } */

  /*wait for keypress and act accordingly*/
  key_ascii=readkey();
  keyboard();

 }

}



