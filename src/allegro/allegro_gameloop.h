/*allegro gameloop*/


/* this function is now the official welcome screen*/
void welcome_screen_chaste_font()
{

 al_clear_to_color(al_map_rgb(0, 0, 0));

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

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the C Programming Language.\nThe font handling is done with the font library Chastity wrote and named Chaste Font.\nAllegro is used for the graphics API including rectangles and textures.\nCredit goes to Alexey Pajitnov for creating the original Tetris game which Chaste Tris is based on.");
 chaste_font_draw_string(text,text_x,main_font.char_height*52);

 al_flip_display(); /*update the screen*/

 loop=1;
 while(loop)
 {
  /*wait till event happens*/
  al_wait_for_event(event_queue, &ev);
  if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){loop=0;}
  if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
  {
   if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER){loop=0;}
  }
 }

}


/*this function is an Allegry port of the keyboard function from the Raylib version of Chaste Tris*/
void keyboard()
{
 int key;
 al_get_next_event(event_queue, &ev);   /*check if event happens but do not pause the program*/
 /* al_wait_for_event(event_queue, &ev);*/  /*wait until event happens*/
  if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){loop=0;}
  if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
  {


   key=ev.keyboard.keycode;

   switch(key)
   {
    case ALLEGRO_KEY_ESCAPE:
    loop=0;
    break;

    case ALLEGRO_KEY_Z:
     block_rotate_left_basic();
    break;
    case ALLEGRO_KEY_X:
     block_rotate_right_basic();
    break;
    case ALLEGRO_KEY_C:
     block_hold();
    break;


    /*the main 4 directions*/
    case ALLEGRO_KEY_UP:
    case ALLEGRO_KEY_W:
     tetris_move_up();
    break;
    case ALLEGRO_KEY_DOWN:
    case ALLEGRO_KEY_S:
     tetris_move_down();
    break;
    case ALLEGRO_KEY_LEFT:
    case ALLEGRO_KEY_A:
    tetris_move_left();
    break;
    case ALLEGRO_KEY_RIGHT:
    case ALLEGRO_KEY_D:
     tetris_move_right();
    break;


    case ALLEGRO_KEY_COMMA:
     tetris_load_state();
    break;
    case ALLEGRO_KEY_FULLSTOP:
     tetris_save_state();
    break;

   }

  }

}



/*
this function gets input from a previous log file and autoplays the moves from  it.
this is a highly experimental feature and probably won't be in the published game
*/
void next_file_input()
{
 int c;
 if(fp_input==NULL){return;}

 c=fgetc(fp_input);

 if(feof(fp_input))
 {
  printf("End of file reached.\n");
  printf("Now use keyboard input.\n");
  /*
   printf("Going back to beginning\n");
   fseek(fp_input,0,SEEK_SET);
  */

  fclose(fp_input); fp_input=NULL;  return;
 }

 else
 {
  /*printf("Character==%c\n",c);*/

  move_id=c;

  if(c=='W'){tetris_move_up();}
  if(c=='S'){tetris_move_down();}
  if(c=='A'){tetris_move_left();}
  if(c=='D'){tetris_move_right();}

  if(c=='Z'){block_rotate_left_basic();}
  if(c=='X'){block_rotate_right_basic();}
  if(c=='C'){block_hold();}
 }


 /*the following code is meant to be used for longboi mode in combination with a special input file*/
 /*move backwards to the right spot for infinite loop of longbois*/
 
 /*
  c=ftell(fp_input);
  if(c==604){fseek(fp_input,512,SEEK_SET);}
 */

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


rect_color=al_map_rgb(255, 255, 255);

 /*draw the boundary walls*/

al_draw_filled_rectangle(grid_offset_x-block_size, 0*block_size, block_size, height, rect_color);

al_draw_filled_rectangle(grid_offset_x+grid_width*block_size, 0*block_size, grid_offset_x+grid_width*block_size+block_size, height, rect_color);


 /*end of drawing code for grid*/

draw_stats_chaste_font();


 /*
 optionally save frame as file
 make comparison moves>=frame to ensure frames are only saved for successful moves.
 use moves<frame to make sure that no frames are ever saved
*/

 /*if(moves>=frame) { TakeScreenshot_frame(); } */

 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
  next_file_input();


 al_flip_display(); /*update the screen*/
 keyboard();

 }

}



