/*allegro_input.h*/

/*
this function is an Allegro port of the keyboard function from the Raylib version of Chaste Tris
you must poll for events with al_get_next_event and then only call this function if it returns true
*/
void keyboard()
{
 int key;

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
    move_id='Z';
    block_rotate_left_basic();
   break;
   case ALLEGRO_KEY_X:
    move_id='X';
    block_rotate_right_basic();
   break;
   case ALLEGRO_KEY_C:
    move_id='C';
    block_hold();
   break;


   /*the main 4 directions*/
   case ALLEGRO_KEY_UP:
   case ALLEGRO_KEY_W:
    move_id='W';
    tetris_move_up();
   break;
   case ALLEGRO_KEY_DOWN:
   case ALLEGRO_KEY_S:
    move_id='S';
    tetris_move_down();
   break;
   case ALLEGRO_KEY_LEFT:
   case ALLEGRO_KEY_A:
    move_id='A';
    tetris_move_left();
   break;
   case ALLEGRO_KEY_RIGHT:
   case ALLEGRO_KEY_D:
    move_id='D';
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
