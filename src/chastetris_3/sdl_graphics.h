/*
sdl_graphics.h

this header file is meant to contain all the functions which write things to the screen
*/

/* this function is now the official welcome screen*/
void welcome_screen_chaste_font()
{
 int scale=8;
 main_font=font_8;
 text_x=width/100;

 delay=1000/fps;

 loop=1;
 while(loop)
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;

 SDL_SetRenderDrawColor(renderer,0,0,0,255);
 SDL_RenderClear(renderer);

 scale=width/100;
 sprintf(text,"%s",gamename);

 /*chaste_font_draw_string_scaled(text,text_x,height/32,scale);*/

  chaste_palette_index=chaste_palette_index1;
  chaste_font_draw_string_scaled_special(text,text_x,height/32,scale);
  
  chaste_palette_index1++;
  if(chaste_palette_index1>=chaste_palette_length)
  {
   chaste_palette_index1=0;
  }

 scale=width/300;

 sprintf(text,"Programming: Chastity White Rose");
 chaste_font_draw_string_scaled(text,text_x,main_font.char_height*5*scale,scale);

 sprintf(text,"Inspiration:    River Black Rose");
 chaste_font_draw_string_scaled(text,text_x,main_font.char_height*6*scale,scale);


 sprintf(text,"Email: chastitywhiterose@gmail.com");
 chaste_font_draw_string_scaled(text,text_x,main_font.char_height*8*scale,scale);

 sprintf(text,"Press Enter to Begin game.");
 chaste_font_draw_string_scaled(text,text_x,height*10/16,scale);

 scale=width/400;

 sprintf(text,"https://www.patreon.com/ChastityWhiteRoseProgramming");
 
 chaste_font_draw_string_scaled(text,text_x,height*7/16,scale);

 scale=width/500;

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the\nC Programming Language. The font handling is done with the font library\nChastity wrote and named Chaste Font.\n\nSDL is used for the graphics API including rectangles and textures.\n\nCredit goes to Alexey Pajitnov for creating the original Tetris game which\nChaste Tris is based on. I also like to thank Henk Rogers for helping\nTetris become the worldwide hit that it is.");
 
 chaste_font_draw_string_scaled(text,text_x,height*12/16,scale);
 
 SDL_RenderPresent(renderer);

 /*time loop used to slow the game down so users can see it*/
 while(sdl_time<sdl_time1)
 {
  sdl_time=SDL_GetTicks();
 }

  /*test for events and only process if they exist*/
  while(SDL_PollEvent(&e))
  {
   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
    if(e.key.keysym.sym==SDLK_RETURN){loop=0;}
   }
  }
  
 }
}






 int fps_current; /*only used when I am debugging the game*/

 void draw_stats_chaste_font_centered()
 {
  int scale=8;
  main_font=font_8;

  text_x=width/320;

  scale=width*1/140;

  /*printf("Scale %d\n",scale);*/

  chaste_palette_index=chaste_palette_index1;
  chaste_font_draw_string_scaled_special("Chaste\n Tris",text_x,32,scale);
  
  chaste_palette_index1++;
  if(chaste_palette_index1>=chaste_palette_length)
  {
   chaste_palette_index1=0;
  }
 
  scale=width/360;

  sprintf(text,"Score %d",score);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*8*scale,scale);

  sprintf(text,"Lines %d",lines_cleared_total);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*9*scale,scale);

  sprintf(text,"This %c",main_block.id);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*10*scale,scale);

  sprintf(text,"Hold %c",hold_block.id);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*11*scale,scale);

  sprintf(text,"Move %d",moves);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*12*scale,scale);

  sprintf(text,"B2B %d",back_to_back);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*13*scale,scale);

  sprintf(text,"Combo %d",combo);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*14*scale,scale);

  
  time(&time1);
  
  seconds=time1-time0; /*subtract current time from start time to get seconds since game started*/
  
/* 
  if(seconds!=0)
  {
   fps_current=frame/seconds;
   sprintf(text,"FPS %d",fps_current);
   chaste_font_draw_string(text,text_x,main_font.char_height*16);
  }
*/
  
  minutes=seconds/60;
  seconds%=60;
  hours=minutes/60;
  minutes%=60;
  
  sprintf(text,"Time %d:%02d:%02d",hours,minutes,seconds);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*15*scale,scale);

  /*sprintf(text,"Frame %d",frame);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*17*scale,scale);*/

 }

/*a function pointer that points to whichever function I currently use to draw the game stats to the screen*/
void (*stats_func)()=draw_stats_chaste_font_centered;


/*
a function which draws the text of the input
this is meant for showing players how the game is played just by looking at the video
I thought it would be helpful for my Twitch stream viewers
*/
void draw_input()
{
 int scale=8;
 main_font=font_8;

 text_x=width*22/32;
 scale=width/400;

 switch(move_id)
 {
  case 'W':
   strcpy(text,"W/Up");
  break;
  case 'A':
   strcpy(text,"A/Left");
  break;
  case 'S':
   strcpy(text,"S/Down");
  break;
  case 'D':
   strcpy(text,"D/Right");
  break;

  case 'Z':
   strcpy(text,"Z/Rotate Left");
  break;
  case 'X':
   strcpy(text,"X/Rotate Right");
  break;
  case 'C':
   strcpy(text,"C/Hold Block");
  break;

  case 'I':
   strcpy(text,"I/Game Save");
  break;
  case 'P':
   if(state[save_index].exist)
   {
    strcpy(text,"P/Game Load");
   }
   else
   {
    strcpy(text,"P pressed\nbut there\nis no game state\nto load.");
   }
  break;

  case '0':
   strcpy(text,"State 0\nselected.");
  break;
  case '1':
   strcpy(text,"State 1\nselected.");
  break;
  case '2':
   strcpy(text,"State 2\nselected.");
  break;
  case '3':
   strcpy(text,"State 3\nselected.");
  break;
  case '4':
   strcpy(text,"State 4\nselected.");
  break;
  case '5':
   strcpy(text,"State 5\nselected.");
  break;
  case '6':
   strcpy(text,"State 6\nselected.");
  break;
  case '7':
   strcpy(text,"State 7\nselected.");
  break;
  case '8':
   strcpy(text,"State 8\nselected.");
  break;
  case '9':
   strcpy(text,"State 9\nselected.");
  break;


  default:
   strcpy(text,"");
 }

 chaste_font_draw_string_scaled(text,text_x,height*1/16,scale);

}

 
 
/*more global variables to be defined before game loop function*/
int border_size;




/*
this is a function which is called by main after window is created. It contains the game loop.
*/
void sdl_chastetris()
{
 /*int pixel,r,g,b;*/
 int x=0,y=0;

 /*setup the grid display*/
 block_size=height/grid_height;
 grid_offset_x=(width-(20/2*block_size))/2; /*formula for grid to center of screen*/
 border_size=block_size;

 printf("block_size==%d\n",block_size);
  
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

 /*
  an optional step before the game loop but a very awesome one
  initialize the spinning polygon that will be drawn each frame
 */

 init_polygon();
 main_polygon.radius=height*11/64;
 main_polygon.sides=4;
 main_polygon.step=1;

 main_polygon.cx=width*11/64;
 main_polygon.cy=height*50/64;

 
 loop=1;
  /* Loop until the user closes the window */
 while(loop)
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;

  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);

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
     if(temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]!=0)
     {
      printf("Error: Block in Way\n");

      /*because a collision has occurred. We will restore everything back to the way it was before block was moved.*/

      break;
     }
     else
     {
      main_color=main_block.color;
      /*main_color=chaste_palette[block_color_index[block_type]];*/
      temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]=main_color;
     }
    }
    x+=1;
   }
   y+=1;
  }



/*display the tetris grid*/
show_grid();

/*show the polygon just for fun*/
chaste_polygon_draw_star();
/*chaste_polygon_draw_star_lines();*/
main_polygon.radians+=PI/180;


 /*draw the boundary walls*/

/*
 set up the rectangle structure with the needed data to square the walls
*/

 SDL_SetRenderDrawColor(renderer,128,128,128,255);

 rect.x=grid_offset_x-border_size;
 rect.y=0*block_size;
 rect.w=border_size;
 rect.h=height;

SDL_RenderFillRect(renderer,&rect);

 rect.x=grid_offset_x+grid_width*block_size;
SDL_RenderFillRect(renderer,&rect);


 /*end of drawing code for grid*/

 stats_func();
 draw_input();


 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
  next_file_input();

 /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }

 SDL_RenderPresent(renderer);

 /*time loop used to slow the game down so users can see it*/
 while(sdl_time<sdl_time1)
 {
  sdl_time=SDL_GetTicks();
 }

 frame++;

 if(music_is_on)
 {
  if(!Mix_Playing(0)) /*if music is no longer playing*/
  {
   song_index=(song_index+1)%songs; /*go to next song*/
   chaste_audio_play(music[song_index]); /*start the music at the current song index*/
  }
 }

 x=0;
 while(x<7)
 {
  block_color_index[x]=(block_color_index[x]+1)%chaste_palette_length;
  x++;
 }

 }

}






