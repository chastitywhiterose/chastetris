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

 sprintf(text,"key_ascii=%d",key_ascii);
 chaste_font_draw_string(text,0,main_font.char_height*2);

 sprintf(text,"key_scan=%d",key_scan);
 chaste_font_draw_string(text,0,main_font.char_height*4);
 
 if(key_ascii==27){loop=0;}
 
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
