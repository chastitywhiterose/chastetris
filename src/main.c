#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

const int width = 1280;
const int height = 720;

Color ray_block_color={255,255,255,255};

Texture2D texture; /*used when textures are used*/
Sound sound; /*main sound played*/
Sound sound1; /*others sounds played*/



int radius; //used for circles sometimes

FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/


int frame=0,framelimit=1,fps=60;

char gamename[256];
int blocks_used=7;

char text[0x200];
char movetext[256],move_id;

Font font;
int fontsize=height/12;
int text_x; /*the x position of where text will go*/

#include "ray_chastetris.h"

void keyboard()
{
 if(IsKeyPressed(KEY_Z))
 {
  move_id='Z';
  sprintf(movetext,"Left Rotate");
  printf("%s\n",movetext);
  block_rotate_left_basic();
  //printf("last_move_fail==%d\n",last_move_fail);
 }
 if(IsKeyPressed(KEY_X))
 {
  move_id='X';
  sprintf(movetext,"Right Rotate");
  printf("%s\n",movetext);
  block_rotate_right_basic();
  //printf("last_move_fail==%d\n",last_move_fail);
 }

 if(IsKeyPressed(KEY_C))
 {
  move_id='C';
  sprintf(movetext,"Block Hold");
  printf("%s\n",movetext);
  block_hold();
 }

 if(IsKeyPressed(KEY_A)||IsKeyPressed(KEY_LEFT))
 {
  move_id='A';
  sprintf(movetext,"Left Move");
  printf("%s\n",movetext);
  tetris_move_left();
 }
 if(IsKeyPressed(KEY_S)||IsKeyPressed(KEY_DOWN))
 {
  move_id='S';
  sprintf(movetext,"Down Move");
  printf("%s\n",movetext);
  tetris_move_down();
 }
 
 if(IsKeyPressed(KEY_W)||IsKeyPressed(KEY_UP))
 {
  move_id='W';
  sprintf(movetext,"Up Move");
  printf("%s\n",movetext);
  tetris_move_up();
 }
 if(IsKeyPressed(KEY_D)||IsKeyPressed(KEY_RIGHT))
 {
  move_id='D';
  sprintf(movetext,"Right Move");
  printf("%s\n",movetext);
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




/*
this is a function which is called by main after window is created. It is the game loop.
*/
void ray_chastetris()
{
 int pixel,r,g,b;
 int x=0,y=0;
 //int *p=main_grid.array;

 int block_size=height/grid_height;
 int grid_offset_x=block_size*1; /*how far from the left size of the window the grid display is*/

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

 
  /* Loop until the user closes the window */

while(!WindowShouldClose())
 {
  BeginDrawing();

  ClearBackground((Color){0,0,0,255});

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


 /*draw the boundary walls*/

DrawRectangle(grid_offset_x-block_size,0*block_size,block_size,height,(Color){255,255,255,255});
DrawRectangle(grid_offset_x+grid_width*block_size,0*block_size,block_size,height,(Color){255,255,255,255});

 /*end of drawing code for grid*/


/*printf("last_move_spin==%d\n",last_move_spin);*/



/*some text drawing*/
 

  DrawText(gamename,text_x,0,fontsize*2, (Color){255,255,255,255});


  //DrawText(movetext,fontsize*14,height-fontsize*6,fontsize, (Color){255,255,255,255});



  DrawText("Chastity White Rose",text_x,fontsize*10,fontsize, (Color){255,255,255,255});
  DrawText("River Black Rose",text_x,fontsize*11,fontsize, (Color){255,255,255,255});

  sprintf(text,"Score: %d",score);
  DrawText(text,text_x,fontsize*3,fontsize, (Color){255,255,255,255});

  sprintf(text,"Lines: %d",lines_cleared_total);
  DrawText(text,text_x,fontsize*4,fontsize, (Color){255,255,255,255});

  sprintf(text,"This: %c",main_block.id);
  DrawText(text,text_x,fontsize*5,fontsize, (Color){255,255,255,255});

  sprintf(text,"Hold: %c",hold_block.id);
  DrawText(text,text_x,fontsize*6,fontsize, (Color){255,255,255,255});

  sprintf(text,"Move: %d",moves);
  DrawText(text,text_x,fontsize*7,fontsize, (Color){255,255,255,255});

  sprintf(text,"Back to Back: %d",back_to_back);
  DrawText(text,text_x,fontsize*8,fontsize, (Color){255,255,255,255});

  /*DrawTexture(texture, width/2 - texture.width/2, height/2 - texture.height/2, WHITE);*/

  EndDrawing();

  keyboard();


 
 /*
 optionally save frame as file
 make comparison moves>=frame to ensure frames are only saved for successful moves.
 use moves<frame to make sure that no frames are ever saved
*/

 //if(moves>=frame) { TakeScreenshot_frame(); } 

 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
 next_file_input();




    
 }

 UnloadFont(font); /*unload the font*/
 CloseWindow();
 
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
 
  x++;
 }

 InitWindow(width,height,"Chastity's Game");
 SetTargetFPS(60);

 //texture=LoadTexture("textures/star_face.png");

 InitAudioDevice();      // Initialize audio device

 //sound = LoadSound("./audio/respectfully.mp3"); //load the audio
 //sound1 = LoadSound("./audio/deluxe_spa_package.mp3"); //load the audio

 //PlaySound(sound);

 /*open the file to record moves*/
 sprintf(filename,"omovelog.txt");
 fp=fopen(filename,"wb+");
 if(fp==NULL){printf("Failed to create file \"%s\".\n",filename); return 1;}

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

 /*the name of the game depends on the blocks_used variable*/
 if(blocks_used==1)
 { 
  sprintf(gamename,"Long Boi");
 }
 else
 {
  sprintf(gamename,"Chaste Tris");
 }

/*load a font before any text is drawn*/
//Font font = LoadFontEx("./font/Hack-Regular.ttf", 32, 0, 250);

font = LoadFont("./font/Hack-Regular.ttf");

fontsize=height/12; /*customize font size based on screen height*/
text_x=fontsize*1; /*position of text for intro screen*/

/*before the game actually runs, optionally display a start screen*/
while(!WindowShouldClose()) /*loop runs until key pressed*/
{
 if(IsKeyPressed(KEY_ENTER)){break;}
 BeginDrawing();

 ClearBackground((Color){0,0,0,255});

 sprintf(text,"Welcome to %s",gamename);
 DrawText(text,text_x,fontsize*0,fontsize, (Color){255,255,255,255});

//DrawTextEx(font, text, (Vector2){ text_x, fontsize*0 }, fontsize, 2, (Color){255,0,255,255});



 DrawText("Programming: Chastity White Rose",text_x,fontsize*2,fontsize, (Color){255,255,255,255});
 DrawText("Inspiration: River Black Rose",text_x,fontsize*3,fontsize, (Color){255,255,255,255});

 DrawText("Press Enter to Begin game.",text_x,fontsize*5,fontsize, (Color){255,255,255,255});

 DrawText("https://github.com/chastitywhiterose/chastetris",text_x,fontsize*8,40, (Color){255,255,255,255});

// DrawText("Email: chastitywhiterose@gmail.com",text_x,fontsize*9,40, (Color){255,255,255,255});

 DrawTextEx(font, "Email: chastitywhiterose@gmail.com", (Vector2){ text_x,fontsize*9}, fontsize, 2, (Color){255,255,255,255});

 EndDrawing();
}
/*optionally, close the window and end program after start screen*/
 //CloseWindow(); return 0;


text_x=fontsize*8; /*position of text for game loop*/

 ray_chastetris();

 if(fp!=NULL){fclose(fp);}
 if(fp_input!=NULL){fclose(fp_input);}

 //UnloadSound(sound);     // Unload sound data
 //UnloadSound(sound1);     // Unload sound data

 

 return 0;
}

/*
raylib_linux:
	gcc -Wall -std=c99 -pedantic main.c -o main -lraylib -lOpenGL -lm -lpthread -ldl -lrt -lX11 && ./main
raylib_windows:
	gcc -Wall -std=c99 -pedantic main.c -o main -I/usr/local/include -L/usr/local/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread -static && ./main
	strip main.exe
*/

