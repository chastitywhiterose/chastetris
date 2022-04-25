/*sdl_input.h*/


/*this function is an SDL port of the keyboard function from the Raylib version of Chaste Tris*/
void keyboard()
{
 int key;
 SDL_PollEvent( &e );
  if( e.type == SDL_QUIT ){loop=0; printf("X clicked! This program will close!\n");}
  if (e.type == SDL_KEYDOWN)
  {


   key=e.key.keysym.sym;

   switch(key)
   {
    case SDLK_ESCAPE:
    loop=0;
    break;

    case SDLK_z:
     block_rotate_left_basic();
    break;
    case SDLK_x:
     block_rotate_right_basic();
    break;
    case SDLK_c:
     block_hold();
    break;


    /*the main 4 directions*/
    case SDLK_KP_8:
    case SDLK_UP:
    case SDLK_w:
     tetris_move_up();
    break;
    case SDLK_KP_2:
    case SDLK_DOWN:
    case SDLK_s:
     tetris_move_down();
    break;
    case SDLK_KP_4:
    case SDLK_LEFT:
    case SDLK_a:
    tetris_move_left();
    break;
    case SDLK_KP_6:
    case SDLK_RIGHT:
    case SDLK_d:
     tetris_move_right();
    break;


    case SDLK_COMMA:
     tetris_load_state();
    break;
    case SDLK_PERIOD:
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

