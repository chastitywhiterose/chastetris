/*
sdl_graphics.h

this header file is meant to contain all the functions which write things to the screen
*/



/*
this function draws the stats of the game such as the lines and score using my chaste font routines
it's in a separate function so that I can switch it out with another function when I feel like it
*/
void draw_stats_chaste_font()
{
 text_x=main_font.char_height*7;


 chaste_font_draw_string(gamename,text_x,main_font.char_height*1);

 sprintf(text,"Score: %d",score);
 chaste_font_draw_string(text,text_x,main_font.char_height*3);

 sprintf(text,"Lines: %d",lines_cleared_total);
 chaste_font_draw_string(text,text_x,main_font.char_height*4);

  sprintf(text,"This: %c",main_block.id);
  chaste_font_draw_string(text,text_x,main_font.char_height*5);

  sprintf(text,"Hold: %c",hold_block.id);
  chaste_font_draw_string(text,text_x,main_font.char_height*6);


  sprintf(text,"Move: %d",moves);
  chaste_font_draw_string(text,text_x,main_font.char_height*7);

  sprintf(text,"B2B: %d",back_to_back);
  chaste_font_draw_string(text,text_x,main_font.char_height*8);

}




/*
this is a function which is called by main after window is created. It is the game loop.
*/
void sdl_chastetris()
{
 int pixel,r,g,b;
 int x=0,y=0;


 int block_size=height/grid_height;
 int grid_offset_x=block_size*1; /*how far from the left size of the window the grid display is*/

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


 delay=1000/fps; 
  /* Loop until the user closes the window */
 while(loop)
 {

  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));

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

rect_color=SDL_MapRGB(surface->format,r,g,b);

/*set up the rectangle structure with the needed data to square the squares*/
rect.x=grid_offset_x+x*block_size;
rect.y=y*block_size;
rect.w=block_size;
rect.h=block_size;
SDL_FillRect(surface,&rect,rect_color);


   x+=1;
  }
  y+=1;
 }


rect_color=SDL_MapRGB(surface->format,255,255,255);

 /*draw the boundary walls*/

/*set up the rectangle structure with the needed data to square the squares*/
rect.x=grid_offset_x-block_size;
rect.y=0*block_size;
rect.w=block_size;
rect.h=height;
SDL_FillRect(surface,&rect,rect_color);

rect.x=grid_offset_x+grid_width*block_size;
SDL_FillRect(surface,&rect,rect_color);


 /*end of drawing code for grid*/

draw_stats_chaste_font();




  keyboard();


 
 /*
 optionally save frame as file
 make comparison moves>=frame to ensure frames are only saved for successful moves.
 use moves<frame to make sure that no frames are ever saved
*/

 /*if(moves>=frame) { TakeScreenshot_frame(); } */

 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
 next_file_input();


  time = SDL_GetTicks();
  time1 = time+delay;
  while(time<time1)
  {
   time=SDL_GetTicks();
  }

  SDL_UpdateWindowSurface(window);

 }

}

