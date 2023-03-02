/*
sdl_graphics.h

this header file is meant to contain all the functions which write things to the screen
*/



/* this function is now the official welcome screen*/
void welcome_screen_chaste_font()
{

 SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));

 main_font=font_64;

 text_x=main_font.char_height*1;

 sprintf(text,"%s",gamename);
 chaste_font_draw_string(text,text_x,main_font.char_height*1);


 main_font=font_32;


 sprintf(text,"Programming: Chastity White Rose");
 chaste_font_draw_string(text,text_x,main_font.char_height*5);

 sprintf(text,"Inspiration:    River Black Rose");
 chaste_font_draw_string(text,text_x,main_font.char_height*6);

 sprintf(text,"Press Enter to Begin game.");
 chaste_font_draw_string(text,text_x,main_font.char_height*8);

 sprintf(text,"Email: chastitywhiterose@gmail.com");
 chaste_font_draw_string(text,text_x,main_font.char_height*10);

 main_font=font_16;

 sprintf(text,"https://github.com/chastitywhiterose/chastetris");
 chaste_font_draw_string(text,text_x,main_font.char_height*24);

 main_font=font_8;

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the C Programming Language.\nThe font handling is done with the font library Chastity wrote and named Chaste Font.\nSDL is used for the graphics API including rectangles and textures.\nCredit goes to Alexey Pajitnov for creating the original Tetris game which Chaste Tris is based on.");
 chaste_font_draw_string(text,text_x,main_font.char_height*52);


 SDL_UpdateWindowSurface(window); /*update the screen*/

 while(e.type != SDL_KEYUP && e.type != SDL_QUIT) /*wait until key is pressed and then released*/
 {
  SDL_PollEvent( &e );
 }

}

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

/*a function pointer that points to whichever function I currently use to draw the game stats to the screen*/
void (*stats_func)()=draw_stats_chaste_font;



 int fps_current; /*only used when I am debugging the game*/

 void draw_stats_chaste_font_centered()
 {
  main_font=font_64;

  /*text_x=main_font.char_height*1/2;*/
  text_x=32;

  chaste_font_draw_string("Chaste\n Tris",text_x,32);
 
  main_font=font_32;

  sprintf(text,"Score %d",score);
  chaste_font_draw_string(text,text_x,main_font.char_height*6);

  sprintf(text,"Lines %d",lines_cleared_total);
  chaste_font_draw_string(text,text_x,main_font.char_height*7);

  sprintf(text,"This %c",main_block.id);
  chaste_font_draw_string(text,text_x,main_font.char_height*8);

  sprintf(text,"Hold %c",hold_block.id);
  chaste_font_draw_string(text,text_x,main_font.char_height*9);


  sprintf(text,"Move %d",moves);
  chaste_font_draw_string(text,text_x,main_font.char_height*10);

  sprintf(text,"B2B %d",back_to_back);
  chaste_font_draw_string(text,text_x,main_font.char_height*11);
  
  time(&time1);
  
  seconds=time1-time0; /*subtract current time from start time to get seconds since game started*/
  
/*  
  sprintf(text,"Frame %d",frame);
  chaste_font_draw_string(text,text_x,main_font.char_height*15);
  
  if(seconds!=0)
  {
   fps_current=frame/seconds;
   sprintf(text,"FPS %d",fps_current);
   chaste_font_draw_string(text,text_x,main_font.char_height*16);
  }
*/
  
  minutes=seconds/60;
  seconds%=60;
  
  sprintf(text,"Time %d:%02d",minutes,seconds);
  chaste_font_draw_string(text,text_x,main_font.char_height*13);
  





 }
 
 
/*more global variables to be defined before game loop function*/
int block_size;
int border_size;
int grid_offset_x;


/*
sets up the variables before the game loop so that the Tetris field is in the center.
This is done because I updated the game later on. This corrects everything before the same loop starts.
*/
void screen_setup_centered()
{
 grid_offset_x=(width-(20/2*block_size))/2; /*to center of screen*/
 border_size=12;
 stats_func=draw_stats_chaste_font_centered;  /*if centered, alternate stats function is needed*/

}





/*
this is a function which is called by main after window is created. It is the game loop.
*/
void sdl_chastetris()
{
 int pixel,r,g,b;
 int x=0,y=0;
 int wall_color;


 block_size=height/grid_height;
 grid_offset_x=block_size*1; /*how far from the left size of the window the grid display is*/

 printf("block_size==%d\n",block_size);
 
 wall_color=SDL_MapRGB(surface->format,127,127,127); /*color the walls of the grid will be*/
 
 /*if the following function is called, screen is centered. Otherwise use old style.*/
 screen_setup_centered();

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
 
 /*get time before the game starts using standard library time function*/
 time(&time0);
 
  /* Loop until the user closes the window */
 while(loop)
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;

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




 /*draw the boundary walls*/

/*
 set up the rectangle structure with the needed data to square the walls
*/
 rect.x=grid_offset_x-border_size;
 rect.y=0*block_size;
 rect.w=border_size;
 rect.h=height;

 SDL_FillRect(surface,&rect,wall_color);

 rect.x=grid_offset_x+grid_width*block_size;
 SDL_FillRect(surface,&rect,wall_color);


 /*end of drawing code for grid*/

 stats_func();


 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
  next_file_input();

 keyboard();

 SDL_UpdateWindowSurface(window); /*update the screen*/


 while(sdl_time<sdl_time1)
 {
  sdl_time=SDL_GetTicks();
 }

 frame++;

 }

}






