/*
This file is for functions which draw text for the stats of Chaste Tris or perhaps other decorations as I think of them.
*/

/*
this function draws the stats of the game such as the lines and score using my chaste font routines
it's in a separate function so that I can switch it out with another function when I feel like it
This is the original launch version which draws the stats on the right ride of the screen while the grid is on the left.
*/
void draw_stats_chaste_font()
{
 text_x=main_font.char_height*7;


 chaste_font_draw_string(gamename,text_x,main_font.char_height*1);

 sprintf(text,"Score %d",score);
 chaste_font_draw_string(text,text_x,main_font.char_height*3);

 sprintf(text,"Lines %d",lines_cleared_total);
 chaste_font_draw_string(text,text_x,main_font.char_height*4);

  sprintf(text,"This %c",main_block.id);
  chaste_font_draw_string(text,text_x,main_font.char_height*5);

  sprintf(text,"Hold %c",hold_block.id);
  chaste_font_draw_string(text,text_x,main_font.char_height*6);


  sprintf(text,"Move %d",moves);
  chaste_font_draw_string(text,text_x,main_font.char_height*7);

  sprintf(text,"B2B %d",back_to_back);
  chaste_font_draw_string(text,text_x,main_font.char_height*8);
  
  
  time(&time1);
  
  seconds=time1-time0;
  minutes=seconds/60;
  seconds%=60;
  
  sprintf(text,"Time %d:%02d",minutes,seconds);
  chaste_font_draw_string(text,text_x,main_font.char_height*9);


}


/*a function pointer that points to whichever function I currently use to draw the game stats to the screen*/
void (*stats_func)()=draw_stats_chaste_font;



 
 
 
 void draw_stats_chaste_font_centered()
 {
  int scale=8;
  main_font=font_64;

  //text_x=main_font.char_height*1/2;
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
  
  seconds=time1-time0;
  minutes=seconds/60;
  seconds%=60;
  hours=minutes/60;
  minutes%=60;
  
  sprintf(text,"Time %d:%02d:%02d",hours,minutes,seconds);
  chaste_font_draw_string(text,text_x,main_font.char_height*13);
  
  main_font=font_8;
  
    /*rainbow title section*/
  chaste_palette_index=chaste_palette_index1;
  chaste_font_draw_string_scaled_special("Chaste\n Tris",text_x,32,scale);
  
  chaste_palette_index1++;
  if(chaste_palette_index1>=chaste_palette_length)
  {
   chaste_palette_index1=0;
  }
  /*end of rainbow title section*/

 }
 
 
int rect_size=16; /*global variable to determine size of checkerboard squares*/
 
 /*
Chaste Checker, also known originally as Chastity Checker from my BBM library,has been revived
This is an extremely fast checkerboard drawing routine.
*/
void chaste_checker()
{
 int x,y;

 Color colors[2];
 int index,index1;
 
 colors[0]=(Color){0,0,0,255};
 colors[1]=(Color){255,255,255,255};

 index=0;
 
 y=0;
 while(y<height)
 {
  index1=index;
  x=0;
  while(x<width)
  {
   DrawRectangle(x,y,rect_size,rect_size,colors[index]);
   index^=1; 
   x+=rect_size;
  }
  index=index1^1;
   
  y+=rect_size;
  }
 }
 
/*only Chastity knows what these do*/
int anim_counter=0;
int check_start_x=0,check_start_y=0;
int check_start_x1=0,check_start_y1=0;
 
  /*
Chaste Checker, also known originally as Chastity Checker from my BBM library,has been revived
This is an extremely fast checkerboard drawing routine.
*/
void chaste_checker_part()
{
 int x,y;

 Color colors[2];
 int index,index1;
 
 colors[0]=(Color){0,0,0,255};
 colors[1]=(Color){255,255,255,255};

 index=0;
 
 y=check_start_y;
 while(y<height)
 {
  index1=index;
  x=check_start_x;
  while(x<width)
  {
   DrawRectangle(x,y,rect_size,rect_size,colors[index]);
   index^=1; 
   x+=rect_size;
  }
  index=index1^1;
   
  y+=rect_size;
  }
 }

 

