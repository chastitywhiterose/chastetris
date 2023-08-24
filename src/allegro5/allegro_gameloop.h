/*allegro gameloop*/


/* this function is now the official welcome screen*/
void welcome_screen_chaste_font()
{
 int scale=8;
 main_font=font_8;
 text_x=width/100;

 if(main_font.bitmap==NULL)
 {
  printf( "Font is blank! No text can be drawn.\n");return;
 }

 delay=1.0/fps; /*1 second divided by frames per second*/

 loop=1;
 while(loop)
 {

  al_time = al_get_time();
  al_time1 = al_time+delay;

 al_clear_to_color(al_map_rgb(0, 0, 0));


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

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the\nC Programming Language. The font handling is done with the font library\nChastity wrote and named Chaste Font.\n\nAllegro is used for the graphics API including rectangles and textures.\n\nCredit goes to Alexey Pajitnov for creating the original Tetris game which\nChaste Tris is based on. I also like to thank Henk Rogers for helping\nTetris become the worldwide hit that it is.");
 
 chaste_font_draw_string_scaled(text,text_x,height*12/16,scale);


 al_flip_display(); /*update the screen*/

  /*time loop used to slow the game down so users can see it*/
 while(al_time<al_time1)
 {
  al_time=al_get_time();
 }

  /*test for events and only process if they exist*/
  while(al_get_next_event(event_queue, &ev))
  {
   if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){loop=0;}
   if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
   {
    if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER){loop=0;}
   }
  }

 }

}






 void draw_stats_chaste_font_centered()
 {
  int scale=8;
  main_font=font_8;

  if(main_font.bitmap==NULL)
  {
   printf( "Font is blank! No text can be drawn.\n");return;
  }

   text_x=16;

  scale=width/130;

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
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*16*scale,scale);

  /*sprintf(text,"Frame %d",frame);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*17*scale,scale);*/


 }




/*
this is a function which is called by main after window is created. It is the game loop.
*/
void allegro_chastetris()
{
 int pixel,r,g,b;
 int x=0,y=0;

 ALLEGRO_COLOR rect_color;


 int block_size=height/grid_height;
 int grid_offset_x=block_size*1; /*how far from the left size of the window the grid display is*/
 int border_size;

 grid_offset_x=(width-(20/2*block_size))/2; /*to center of screen*/
 border_size=12;


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

 delay=1.0/fps; /*1 second divided by frames per second*/

 /*get time before the game starts using standard library time function*/
 time(&time0);

  /* Loop until the user closes the window */
 loop=1;
 while(loop)
 {

  al_time = al_get_time();
  al_time1 = al_time+delay;

  al_clear_to_color(al_map_rgb(0, 0, 0));

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

rect_color=al_map_rgb(r, g, b);

al_draw_filled_rectangle(grid_offset_x+x*block_size, y*block_size, grid_offset_x+(x+1)*block_size, (y+1)*block_size, rect_color);

   x+=1;
  }
  y+=1;
 }


 /*draw the boundary walls*/
 rect_color=al_map_rgb(127, 127, 127);
 al_draw_filled_rectangle(grid_offset_x-border_size, 0*block_size, grid_offset_x, height, rect_color);

 al_draw_filled_rectangle(grid_offset_x+grid_width*block_size, 0*block_size,  grid_offset_x+grid_width*block_size+border_size, height, rect_color);

 /*end of drawing code for grid*/

 draw_stats_chaste_font_centered();


 /*
 optionally save frame as file
 make comparison moves>=frame to ensure frames are only saved for successful moves.
 use moves<frame to make sure that no frames are ever saved
*/

 /*if(moves>=frame) { TakeScreenshot_frame(); } */


 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
 next_file_input();

 /*test for events and only process if they exist*/
 while(al_get_next_event(event_queue, &ev))
 {
  keyboard();
 }


 al_flip_display(); /*update the screen*/

 /*time loop used to slow the game down so users can see it*/
 while(al_time<al_time1)
 {
  al_time=al_get_time();
 }


 }

}



