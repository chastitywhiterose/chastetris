/*allegro4 keyboard

This file contains the function which manages all keyboard input for the Allegro 4 version of Chaste Tris
*/

int key_ascii,key_scan;
void keyboard()
{
 key_scan=key_ascii>>8;
 key_ascii&=0xFF;

 main_font=font_32;
 
 /*clear_to_color(screen, makecol(0,0,0));*/

/*
 sprintf(text,"key_ascii=%d",key_ascii);
 chaste_font_draw_string(text,0,main_font.char_height*2);

 sprintf(text,"key_scan=%d",key_scan);
 chaste_font_draw_string(text,0,main_font.char_height*4);
 */
 
/* if(key_ascii==27){loop=0;}*/
 
   switch(key_scan)
   {
    case KEY_ESC:
    loop=0;
    break;

    case KEY_Z:
     block_rotate_left_basic();
    break;
    case KEY_X:
     block_rotate_right_basic();
    break;
    case KEY_C:
     block_hold();
    break;

    /*the main 4 directions*/
    case KEY_UP:
    case KEY_W:
     tetris_move_up();
    break;
    case KEY_DOWN:
    case KEY_S:
     tetris_move_down();
    break;
    case KEY_LEFT:
    case KEY_A:
    tetris_move_left();
    break;
    case KEY_RIGHT:
    case KEY_D:
     tetris_move_right();
    break;

    case KEY_COMMA:
     tetris_load_state();
    break;
    case KEY_STOP:
     tetris_save_state();
    break;

   }
 
 
}



int end_of_input_file=0;

/*
this function gets input from a previous log file and autoplays the moves from  it.
I included it in this file because it is merely an alternate form of keyboard input.
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
  end_of_input_file=1;
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
