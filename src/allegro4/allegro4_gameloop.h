/*
allegro 4 gameloop

This file contains only the main gameloop and a few other tools
*/

/* this function is now the official welcome screen*/
void welcome_screen_chaste_font()
{
 clear_to_color(screen, makecol(0,0,0));

 main_font=font_64;

 text_x=main_font.char_height*2;

 sprintf(text,"%s","Chaste\n Tris");
 chaste_font_draw_string(text,text_x,main_font.char_height/2*1);

 main_font=font_16;

 text_x=main_font.char_width*2;


 sprintf(text,"Programming: Chastity White Rose");
 chaste_font_draw_string(text,text_x,main_font.char_height*12);

 sprintf(text,"Inspiration:    River Black Rose");
 chaste_font_draw_string(text,text_x,main_font.char_height*13);


 sprintf(text,"Email: chastitywhiterose@gmail.com");
 chaste_font_draw_string(text,text_x,main_font.char_height*15);
 
 sprintf(text,"Press Enter to Begin game.");
 chaste_font_draw_string(text,text_x,main_font.char_height*17);

 main_font=font_8;

 sprintf(text,"https://github.com/chastitywhiterose/chastetris");
 chaste_font_draw_string(text,text_x,main_font.char_height*40);

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the\nC Programming Language. The font handling is done with the font library\nChastity wrote and named Chaste Font.\nAllegro is used for the graphics API including rectangles and textures.\nCredit goes to Alexey Pajitnov for creating the original Tetris game which\nChaste Tris is based on.");
 chaste_font_draw_string(text,text_x,main_font.char_height*50);

 /* wait for a key press */
 readkey();

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
 
  chaste_checker();

  /* Loop until the user closes the window */
 loop=1;
 while(loop)
 {

/*  clear_to_color(screen, makecol(0,0,0));*/
  

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

/*al_draw_filled_rectangle(grid_offset_x+x*block_size, y*block_size, grid_offset_x+(x+1)*block_size, (y+1)*block_size, rect_color);*/

rectfill(screen,grid_offset_x+x*block_size, y*block_size, grid_offset_x+(x+1)*block_size, (y+1)*block_size, rect_color);

   x+=1;
  }
  y+=1;
 }


rect_color=makecol(255, 255, 255);

 /*draw the boundary walls*/

/*al_draw_filled_rectangle(grid_offset_x-block_size, 0*block_size, block_size, height, rect_color);*/

/*al_draw_filled_rectangle(grid_offset_x+grid_width*block_size, 0*block_size, grid_offset_x+grid_width*block_size+block_size, height, rect_color);*/


 /*end of drawing code for grid*/

/* draw_stats_chaste_font();*/


 /*
 optionally save frame as file
 make comparison moves>=frame to ensure frames are only saved for successful moves.
 use moves<frame to make sure that no frames are ever saved
*/

 /*if(moves>=frame) { TakeScreenshot_frame(); } */

 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
 if(!keypressed())
 {
   next_file_input();
 }

 if(keypressed())
 {
  key_ascii=readkey();
  keyboard();
 }
 
 rest(rest_time);


 }

}



