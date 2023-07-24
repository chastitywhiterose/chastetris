/*
This file is for functions which draw text for the stats of Chaste Tris or perhaps other decorations as I think of them.
*/


 
  void draw_stats_chaste_font_centered()
 {
  int scale=8;
  main_font=font_8;

  /*text_x=main_font.char_height*1/2;*/
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
 
/*a function pointer that points to whichever function I currently use to draw the game stats to the screen*/
void (*stats_func)()=draw_stats_chaste_font_centered;
 
 
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

 

