/*sfml_graphics.h*/

void title_screen()
{
 int scale=8;
 text_x=width/100;

 delay=1000/fps;

 loop=1;
 while(loop)
 {
  sftime=sfclock.getElapsedTime();
  mill=sftime.asMilliseconds();
  mill1=mill+delay;

  window.clear();

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

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the\nC Programming Language. The font handling is done with the font library\nChastity wrote and named Chaste Font.\n\nSFML is used for the graphics API including rectangles and textures.\n\nCredit goes to Alexey Pajitnov for creating the original Tetris game which\nChaste Tris is based on. I also like to thank Henk Rogers for helping\nTetris become the worldwide hit that it is.");
 
 chaste_font_draw_string_scaled(text,text_x,height*12/16,scale);

 window.display();

  //polling section
  
  while (window.pollEvent(event))
  {
   if(event.type == sf::Event::Closed) {loop=0;}
   if(event.type == sf::Event::KeyPressed)
   {
    if(event.key.code==sf::Keyboard::Escape){loop=0;}
    if(event.key.code==sf::Keyboard::Enter){loop=0;}
   }
  }

  /*time loop used to slow the game down so users can see it*/
  while(mill<mill1)
  {
   sftime=sfclock.getElapsedTime();
   mill=sftime.asMilliseconds();
  }

 }

}





















 int fps_current; /*only used when I am debugging the game*/

 void chastetris_draw_stats()
 {
  int scale=8;

  //printf("Drawing game stats\n");

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







/*more global variables to be defined before game loop function*/
int block_size;
int border_size;
int grid_offset_x;

/*
sets up the variables before the game loop so that the Tetris field is in the center.
This is done because I updated the game later on. This corrects everything before the game loop starts.
*/
void screen_setup_centered()
{
 grid_offset_x=(width-(20/2*block_size))/2; /*to center of screen*/
 border_size=12;
}

/*
this is a function which is called by main after window is created. It contains the game loop.
*/
void sfml_chastetris()
{
 int pixel,r,g,b;
 int x=0,y=0;


 block_size=height/grid_height;
 grid_offset_x=block_size*1; /*how far from the left size of the window the grid display is*/
 border_size=block_size;

 printf("block_size==%d\n",block_size);
  
 /*if the following function is called, screen is centered. Otherwise use old left side style.*/
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
 
 loop=1;
  /* Loop until the user closes the window */
 while(loop)
 {
  sftime=sfclock.getElapsedTime();
  mill=sftime.asMilliseconds();
  mill1=mill+delay;

  window.clear();

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


/* printf("x=%d y=%d ",x,y);
 printf("red=%d green=%d blue=%d\n",r,g,b);*/



rectangle.setFillColor(sf::Color(r,g,b));

/*set up the rectangle structure with the needed data to square the squares*/
rect.left=grid_offset_x+x*block_size;
rect.top=y*block_size;
rect.width=block_size;
rect.height=block_size;

rectangle.setPosition(sf::Vector2f(rect.left,rect.top));
rectangle.setSize(sf::Vector2f(rect.width,rect.height));
window.draw(rectangle);


   x+=1;
  }
  y+=1;
 }




 /*draw the boundary walls*/

/*
 set up the rectangle structure with the needed data to square the walls
*/

 rectangle.setFillColor(sf::Color(128,128,128));

 rect.left=grid_offset_x-border_size;
 rect.top=0*block_size;
 rect.width=border_size;
 rect.height=height;

 rectangle.setPosition(sf::Vector2f(rect.left,rect.top));
 rectangle.setSize(sf::Vector2f(rect.width,rect.height));
 window.draw(rectangle);

 rect.left=grid_offset_x+grid_width*block_size;

 rectangle.setPosition(sf::Vector2f(rect.left,rect.top));
 window.draw(rectangle);


 /*end of drawing code for grid*/

 chastetris_draw_stats();
 //draw_input();

 window.display();

 /*test for events and only process if they exist*/
  while (window.pollEvent(event))
  {
   if(event.type == sf::Event::Closed) {loop=0;}
   keyboard();
  }

 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
  next_file_input();

 /*time loop used to slow the game down so users can see it*/
 while(mill<mill1)
 {
  sftime=sfclock.getElapsedTime();
  mill=sftime.asMilliseconds();
 }


 frame++;

 }

}
