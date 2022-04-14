#include <ncurses.h>
#include <string.h>


FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/

int frame=0,framelimit=1,fps=60;

char gamename[256];
int blocks_used=7;

char text[0x200];
char movetext[256],move_id;

#include "ncurses_chastetris.h"


/*
this function gets input from a previous log file and autoplays the moves from  it.
this is a highly experimental feature and probably won't be in the published game
*/
int next_file_input()
{
 int c;
 if(fp_input==NULL){return 0;}

 c=fgetc(fp_input);

 if(feof(fp_input))
 {
  /*
   printf("End of file reached.\n");
   printf("Now use keyboard input.\n");
  */

  /*
   printf("Going back to beginning\n");
   fseek(fp_input,0,SEEK_SET);
  */

  fclose(fp_input); fp_input=NULL;  return 0;

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

  return c;
 }

}



int main(int argc, char **argv)
{	
 int key=0,x,y;


 /*process command line arguments*/
 x=1;
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


 /*the name of the game depends on the blocks_used variable*/
 if(blocks_used==1)
 { 
  sprintf(gamename,"Long Boi");
 }
 else
 {
  sprintf(gamename,"Chaste Tris");
 }


 /*open the file to record moves*/
 sprintf(filename,"omovelog.txt");
 fp=fopen(filename,"wb+");
 if(fp==NULL){printf("Failed to create file \"%s\".\n",filename); return 1;}

 /*open the input file if it exists*/
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


 printf("This is a program using the ncurses library.\n");


 initscr(); /* Start curses mode */
 raw(); /*disable line buffering*/
 noecho(); /*disable echoing characters type automatically*/
 keypad(stdscr, TRUE); /*enable the arrow keys*/

 /*printw("Hello World!\n");*/	/* Print Hello World		  */

 spawn_block(); /*spawn the first block before game loop*/

 /*before game loop, empty the grid*/
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

 /*next line begins game loops*/
 while(key!=27) /*while key not equal to Esc key AKA 27.*/
 {

  clear(); /*clear the screen before drawing anything*/

  /*this section draws the tetris grid using only text*/

 /*make backup of entire grid*/
  temp_grid=main_grid;

  /*copy block onto temp grid at it's current location*/
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
/*      printf("Error: Block in Way\n");*/

      printw("Error: Block in Way\n");

      /*because a collision has occurred. We will restore everything back to the way it was before block was moved.*/

      break;
     }
     else
     {
      temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]=main_block.id;
     }
    }
    x+=1;
   }
   y+=1;
  }

/*display the tetris grid*/

  /*draw top border*/
  x=0;
  while(x<grid_width+2)
  {
   printw("-"); 
   x+=1;
  }
  printw("\n"); 

 /*draw the inside of the grid itself*/
 y=0;
 while(y<grid_height)
 {
  printw("|"); 
  x=0;
  while(x<grid_width)
  {
   if(temp_grid.array[x+y*grid_width]==0)
   {
    printw(" "); 
   }
   else{printw("%c",temp_grid.array[x+y*grid_width]);}
   x+=1;
  }
  printw("|"); 
  printw("\n");
  y+=1;
 }

  /*draw bottom border*/
  x=0;
  while(x<grid_width+2)
  {
   printw("-"); 
   x+=1;
  }
  printw("\n"); 



/* end of grid drawing section*/


 /*section for drawing text info for the game*/
 x=40;y=0;
 move(y,x);
 printw("%s\n",gamename);

 y++;
 mvprintw(y,x,"key==%d '%c'\n",key,key);

 y++;
 mvprintw(y,x,"%s\n",text);

 y++;
 mvprintw(y,x,"Score: %d",score);

 y++;
 mvprintw(y,x,"Lines: %d",lines_cleared_total);

 y++;
 mvprintw(y,x,"This: %c",main_block.id);

 y++;
 mvprintw(y,x,"Hold: %c",hold_block.id);

 y++;
 mvprintw(y,x,"Move: %d",moves);

 y++;
 mvprintw(y,x,"Back to Back: %d",back_to_back);

 x=22;y=0;
 move(y,x);


  refresh();			/* update the screen */



  /*keyboard section*/



  key=next_file_input();

  if(key==0)
  {
   key=getch(); /*Wait for user input */   
  }




  if(key==258){key='s';}
  if(key==259){key='w';}
  if(key==260){key='a';}
  if(key==261){key='d';}


  if(key=='z'){move_id='Z';strcpy(text,"Left Rotate");block_rotate_left_basic();}
  if(key=='x'){move_id='X';strcpy(text,"Right Rotate");block_rotate_right_basic();}
  if(key=='c'){move_id='C';strcpy(text,"Hold Block");block_hold();}

  if(key=='w'){move_id='W';strcpy(text,"Move Up");tetris_move_up();}
  if(key=='a'){move_id='A';strcpy(text,"Move Left");tetris_move_left();}
  if(key=='s'){move_id='S';strcpy(text,"Move Down");tetris_move_down();}
  if(key=='d'){move_id='D';strcpy(text,"Move Right");tetris_move_right();}

 }

 endwin();			/* End curses mode		  */


/*before ending program, also close the files if they are still open.*/

if(fp!=NULL){fclose(fp);}
if(fp_input!=NULL){fclose(fp_input);}

 return 0;
}

/*
 This is the keyboard input ncurses example. It can be compiled and run like this.

 gcc -Wall -ansi -pedantic main.c -o main -lncurses && ./main


It is meant to serve as a prototype for eventually integrating it with my Chaste Tris game when making the ncurses version.
*/

