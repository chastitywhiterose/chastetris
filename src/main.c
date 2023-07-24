#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <raylib.h>
#include <math.h>

int width = 1280;
int height = 720;
int fullscreen=0;
int window_flags=0;

Color ray_block_color={255,255,255,255};
Color ray_border_color={127,127,127,255};

Texture2D texture; /*used when textures are used*/
//Sound sound; /*main sound played*/
//Sound sound1; /*others sounds played*/

Sound music[3]; /*array of music which can be loaded into*/
int music_index=0;
int music_on=1; /*whether music should be on*/



int radius; //used for circles sometimes

FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/


int frame=0,framelimit=1,fps=60;

time_t time0,time1;
int seconds,minutes,hours;

char gamename[256];
int blocks_used=7;

char text[0x200];
char movetext[256],move_id;

Font font;
int text_x; /*the x position of where text will go*/

#include "chastetris.h"
#include "chastetris_gamesave.h"
#include "chaste_the_rainbow.h"
#include "ray_polygon.h"

#include "ray_chastefont.h"
#include "ray_chastegraph.h"

#include "ray_chaste_opener.h"


void keyboard()
{
 if(IsKeyPressed(KEY_Z))
 {
  move_id='Z';
  sprintf(movetext,"Left Rotate");
/*  printf("%s\n",movetext);*/
  block_rotate_left_basic();
  //printf("last_move_fail==%d\n",last_move_fail);
 }
 if(IsKeyPressed(KEY_X))
 {
  move_id='X';
  sprintf(movetext,"Right Rotate");
/*  printf("%s\n",movetext);*/
  block_rotate_right_basic();
  //printf("last_move_fail==%d\n",last_move_fail);
 }

 if(IsKeyPressed(KEY_C))
 {
  move_id='C';
  sprintf(movetext,"Block Hold");
  /*printf("%s\n",movetext);*/
  block_hold();
 }

 if(IsKeyPressed(KEY_A)||IsKeyPressed(KEY_LEFT))
 {
  move_id='A';
  sprintf(movetext,"Left Move");
/*  printf("%s\n",movetext);*/
  tetris_move_left();
 }
 if(IsKeyPressed(KEY_S)||IsKeyPressed(KEY_DOWN))
 {
  move_id='S';
  sprintf(movetext,"Down Move");
/*  printf("%s\n",movetext);*/
  tetris_move_down();
 }
 
 if(IsKeyPressed(KEY_W)||IsKeyPressed(KEY_UP))
 {
  move_id='W';
  sprintf(movetext,"Up Move");
  /*printf("%s\n",movetext);*/
  tetris_move_up();
 }
 if(IsKeyPressed(KEY_D)||IsKeyPressed(KEY_RIGHT))
 {
  move_id='D';
  sprintf(movetext,"Right Move");
/*  printf("%s\n",movetext);*/
  tetris_move_right();
 }


 if(IsKeyPressed(KEY_COMMA))
 {
  /*printf("Game Loaded\n");*/
  tetris_load_state();
 }
 if(IsKeyPressed(KEY_PERIOD))
 {
  /*printf("Game Saved\n");*/
  tetris_save_state();
 }
 
 /*for printing grid array as text*/
 if(IsKeyPressed(KEY_G))
 {
  /*sprintf(movetext,"Block Hold");*/
  /*printf("%s\n",movetext);*/
  grid_print();
 }
 
 
 /*for printing grid array as text*/
 if(IsKeyPressed(KEY_M))
 {
  if(IsSoundPlaying(music[music_index]))
  {
   printf("Music is playing. It will be stopped now.\n");
   StopSound(music[music_index]);
   music_on=0;
  }
  else
  {
   printf("Music is not playing. It will be started now.\n");
   PlaySound(music[music_index]);
   music_on=1;
  }
 }
  
  /*save states*/
 if(IsKeyPressed(KEY_I))
 {
  save_gamesave();
 }
 if(IsKeyPressed(KEY_P))
 {
  load_gamesave();
 }

 if(IsKeyPressed(KEY_ZERO))
 {
  save_index=0;
  printf("State %d selected.\n",save_index);
 }
 if(IsKeyPressed(KEY_ONE))
 {
  save_index=1;
  printf("State %d selected.\n",save_index);
 }
 if(IsKeyPressed(KEY_TWO))
 {
  save_index=2;
  printf("State %d selected.\n",save_index);
 }
 if(IsKeyPressed(KEY_THREE))
 {
  save_index=3;
  printf("State %d selected.\n",save_index);
 }
  if(IsKeyPressed(KEY_FOUR))
 {
  save_index=4;
  printf("State %d selected.\n",save_index);
 }
 if(IsKeyPressed(KEY_FIVE))
 {
  save_index=5;
  printf("State %d selected.\n",save_index);
 }
 if(IsKeyPressed(KEY_SIX))
 {
  save_index=6;
  printf("State %d selected.\n",save_index);
 }
 if(IsKeyPressed(KEY_SEVEN))
 {
  save_index=7;
  printf("State %d selected.\n",save_index);
 }
 if(IsKeyPressed(KEY_EIGHT))
 {
  save_index=8;
  printf("State %d selected.\n",save_index);
 }
 if(IsKeyPressed(KEY_NINE))
 {
  save_index=9;
  printf("State %d selected.\n",save_index);
 }
 


}


/*saves the current window as an image file and increments frame number*/
void TakeScreenshot_frame()
{
 char filename[256];
 sprintf(filename,"o/%08d.png",frame);
 printf("%s\n",filename);
 TakeScreenshot(filename);
 frame++;
}

/*
this function gets input from a previous log file and autoplays the moves from  it.
this enables tool assisted speedruns!
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
  //printf("Character==%c\n",c);

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



/*more global variables to be defined before game loop function*/
int block_size;
int border_size;
int grid_offset_x;


/*
sets up the variables before the game loop so that the Tetris field is in the center
*/
void screen_setup_centered()
{
 grid_offset_x=(width-(20/2*block_size))/2; /*to center of screen*/
 border_size=12;
 stats_func=draw_stats_chaste_font_centered;  /*if centered, alternate stats function is needed*/
}


/*
this is a function which is called by main after window is created. It is the game loop.
*/
void ray_chastetris()
{
 int pixel,r,g,b;
 int x=0,y=0;
 //int *p=main_grid.array;

 /*the original graphics style on first Steam release*/
 block_size=height/grid_height;
 grid_offset_x=block_size*1; /*how far from the left size of the window the grid display is*/
 border_size=block_size; /*set custom border width alternative to block_size*/
 
 /*if the following function is called, screen is centered. Otherwise use old style.*/
 screen_setup_centered();
 


 radius=block_size/2; //radius of circle if drawing circles instead of squares for the blocks.
 
 
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
 
/*optionally set up grid with something else instead of empty*/
//grid_init();


time(&time0); /*get time before the game starts using time function*/
 
 /*
  This section is setting up initial partial checkerboard variables for a checkerboard animation
 */
 rect_size=16;
 anim_counter=0;

 
 check_start_x1=grid_offset_x+grid_width*block_size+border_size;
 check_start_y1=0;
 
 check_start_x=check_start_x1;
 check_start_y=check_start_y1;


while(!WindowShouldClose())   /* Loop until the user closes the window */

 {
  BeginDrawing();

  ClearBackground((Color){0,0,0,255});
  
  /*do checker to part of the screen*/
  chaste_checker_part();
//  check_start_x--;
  check_start_y--;
  anim_counter++;
  if(anim_counter==rect_size*2)
  {
//   check_start_x=check_start_x1;
   check_start_y=check_start_y1;
   anim_counter=0;
  }

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

ray_block_color=(Color){r,g,b,255};

DrawRectangle(grid_offset_x+x*block_size,y*block_size,block_size,block_size,ray_block_color);
//DrawCircle( grid_offset_x+x*block_size+radius,y*block_size+radius, radius, ray_block_color);


/*draw texture modified by the color of this block on the grid*/
//DrawTexture(texture, grid_offset_x+x*block_size,y*block_size , ray_block_color);

   x+=1;
  }
  y+=1;
 }


 /*draw the boundary walls original style*/
//DrawRectangle(grid_offset_x-block_size,0*block_size,block_size,height,ray_border_color);
//DrawRectangle(grid_offset_x+grid_width*block_size,0*block_size,block_size,height,ray_border_color);

 /*draw the boundary walls centered style*/
DrawRectangle(grid_offset_x-border_size,0*block_size,border_size,height,ray_border_color);
DrawRectangle(grid_offset_x+grid_width*block_size,0*block_size,border_size,height,ray_border_color);


 /*end of drawing code for grid*/


/*printf("last_move_spin==%d\n",last_move_spin);*/


  stats_func();
  
  //polygon_draw();
  //polygon_draw_lines();
  
  
  //chaste_polygon_draw();
  chaste_polygon_draw_star();
  
  main_polygon.radians+=PI/180;


  EndDrawing();

  keyboard();
  
  /*if music has stopped playing then go to next track*/
  if(music_on && !IsSoundPlaying(music[music_index]))
  {
   music_index=(music_index+1)%3;
   PlaySound(music[music_index]);
  }


 
 /*
 optionally save frame as file
 make comparison moves>=frame to ensure frames are only saved for successful moves.
 use moves<frame to make sure that no frames are ever saved
*/

 //if(moves>=frame) { TakeScreenshot_frame(); } 


 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
 next_file_input();




    
 }

 //UnloadFont(font); /*unload the font*/
 CloseWindow();
 
}



/* this function is now the official welcome screen*/
void welcome_screen_chaste_font()
{
 int scale=8;
 main_font=font_8;
 text_x=width/100;

 music_index=0; 
 PlaySound(music[music_index]);


/*before the game actually runs, optionally display a start screen*/
while(!WindowShouldClose()) /*loop runs until key pressed*/
{
 if(IsKeyPressed(KEY_ENTER)){break;}
 if(IsKeyPressed(KEY_M))
 {
  if(IsSoundPlaying(music[music_index]))
  {
   printf("Music is playing. It will be stopped now.\n");
   StopSound(music[music_index]);
  }
  else
  {
   printf("Music is not playing. It will be started now.\n");
   PlaySound(music[music_index]);
  }
 }
 
 BeginDrawing();
 ClearBackground((Color){0,0,0,255});

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

//https://store.steampowered.com/app/1986120/Chaste_Tris/

 sprintf(text,"https://store.steampowered.com/app/1986120/Chaste_Tris/");
 chaste_font_draw_string_scaled(text,text_x,height*8/16,scale);


 scale=width/500;

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the\nC Programming Language. The font handling is done with the font library\nChastity wrote and named Chaste Font.\n\nRaylib is used for the graphics API including rectangles and textures.\n\nCredit goes to Alexey Pajitnov for creating the original Tetris game which\nChaste Tris is based on. I also like to thank Henk Rogers for helping\nTetris become the worldwide hit that it is.");
 
 chaste_font_draw_string_scaled(text,text_x,height*12/16,scale);


 EndDrawing();
}

 StopSound(music[music_index]); //stop title music before game begins

}


/* this function is now the official title screen*/
void title_screen_chaste_font()
{

/*before the game actually runs, optionally display a start screen*/
while(!WindowShouldClose()) /*loop runs until key pressed*/
{
 if(IsKeyPressed(KEY_ENTER)){break;}
 BeginDrawing();
 ClearBackground((Color){0,0,0,255});

 main_font=font_128;

 text_x=main_font.char_height*2;

 sprintf(text,"Chaste\n Tris");
 chaste_font_draw_string(text,text_x,main_font.char_height*1);


 EndDrawing();
}

}



int main(int argc, char **argv)
{

 /*process command line arguments*/
 int x=1;
 while(x<argc)
 {
  printf("argv[%i]=%s\n",x,argv[x]);

  if(strcmp(argv[x],"-longboi")==0)
  {
   printf("Long Boi mode activated! Only the I blocks will spawn!\n");
   blocks_used=1;
  }
  
  if(strcmp(argv[x],"-tgirl")==0)
  {
   printf("T Girl mode activated! Only the T blocks will spawn!\n");
   block_type=1;
   blocks_used=1;
  }
 
  x++;
 }

 /*optionally set dimensions for fullscreen*/
 if(1)
 {
  width=1920;height=1080;
  fullscreen=1;
 }

 InitWindow(width,height,"Chastity's Game");
 SetTargetFPS(60);

 if(fullscreen!=0)
 {
  window_flags=FLAG_WINDOW_UNDECORATED; /*window without title bar*/
  SetWindowState(window_flags);
 }

 InitAudioDevice();      // Initialize audio device

 //sound = LoadSound("./audio/respectfully.mp3"); //load the audio
 //sound1 = LoadSound("./audio/deluxe_spa_package.mp3"); //load the audio

 /*load all music before game starts*/
 music[0]=LoadSound("./music/Tetris_Gift_from_Moscow_OC_ReMix.mp3"); //load the main music("./music/music_title.mp3");
 music[1]=LoadSound("./music/Tetris_T-Spin_OC_ReMix.mp3"); //load the main music
 music[2]=LoadSound("./music/Chrono_Trigger_Protector_in_Green_OC_ReMix.mp3"); //load the main music


  sprintf(gamename,"Chaste Tris");

 /*
  call the function to load my custom bitmap font.
  it returns a "chaste_font" structure which is stored in global variable main_font
 */

 font_8=chaste_font_load("./font/FreeBASIC Font 8.png");

 chaste_palette_rainbow(40);
 /*chaste_palette_view();*/

//title_screen_chaste_font();
welcome_screen_chaste_font();

/*
optionally, close the window and end program after start screen
this is great when testing something that hasn't been debugged
*/
 //CloseWindow(); return 0;




 sprintf(filename,"imovelog.txt");
 fp_input=fopen(filename,"rb+");
 if(fp_input==NULL)
 {
  printf("Failed to open input file \"%s\".\n",filename);
  printf("This is not an error. It just means input is keyboard only. \"%s\".\n",filename);
 }
 else
 {
  printf("input file \"%s\" is opened.\n",filename);
  printf("Will read commands from this file before keyboard. \"%s\".\n",filename);
 }
 main_font=font_64; /*font should be size 64 before game loop*/

/*savestate initialization*/
x=0;
while(x<10)
{
 state[x].exist=0; /*save states should not exist at beginning of game*/
 x++;
}

 
 init_polygon(); /*setup the polygon initial variables*/
 /*change a few polygon things for this game*/
 main_polygon.radius=height/6;
 main_polygon.cx=width*3/16;
 main_polygon.cy=height*13/16;
 main_polygon.sides=5;
 main_polygon.step=2;

 music_index=1; 
 PlaySound(music[music_index]); //start playing music just before game begins

 ray_chastetris();
 
 /*
  After the game ends, we will attempt to save the movelog to a file.
  Keeping the movelog in memory and only writing at the end speeds up the program and simplifies things.
 */
 
  /*open the file to record moves*/
 sprintf(filename,"omovelog.txt");
 fp=fopen(filename,"wb+");
 if(fp==NULL){printf("Failed to create file \"%s\".\n",filename);}
 else
 {
  x=0;
  while(x<moves)
  {
   /*printf("%d %c\n",x,move_log[x]);*/
   fputc(move_log[x],fp);
   x++;
  }
 }

 if(fp!=NULL){fclose(fp);}
 if(fp_input!=NULL){fclose(fp_input);}

 //UnloadSound(sound);     // Unload sound data
 //UnloadSound(sound1);     // Unload sound data

 
 
 //clock_time1 = clock();
  //printf("Game ran for %d\n", (float) (clock_time1-clock_time) /CLOCKS_PER_SEC );
  
  time(&time1);
  printf("Game ran for %ld Seconds.\n",time1-time0);

 return 0;
}

/*
raylib_linux:
	gcc -Wall -std=c99 -pedantic main.c -o main -lraylib -lOpenGL -lm -lpthread -ldl -lrt -lX11 && ./main
raylib_windows:
	gcc -Wall -std=c99 -pedantic main.c -o main -I/usr/local/include -L/usr/local/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread -static && ./main
	strip main.exe
*/

