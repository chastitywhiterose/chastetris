#include <SFML/Graphics.hpp>

int width=1280,height=720;
int loop=1;
int frame=0,lastframe=0,fps=60,delay,framelimit=1; /*only used for animation demos*/
time_t time0,time1;
int seconds,minutes,hours; /*to keep track of time*/
int mill,mill1; /*milliseconds*/

char gamename[256];
int blocks_used=7;

char text[0x200];
char movetext[256],move_id;
int text_x; /*the x position of where text will go*/

FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/

sf::RenderWindow window;
sf::Event event;
sf::Clock sfclock;
sf::Time sftime;
sf::RectangleShape rectangle;
sf::IntRect rect;

#include "chastetris.h"
#include "chastetris_gamesave.h"
#include "chaste_the_rainbow.h"
#include "sfml_chastefont.h"
#include "sfml_input.h"
#include "sfml_graphics.h"


int main()
{
 int x;

 /*high definition*/
 if(0){width=1920;height=1080;}

 window.create(sf::VideoMode(width,height),"SFML Chaste Tris");
 window.setKeyRepeatEnabled(false);

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

 sprintf(gamename,"Chaste Tris");
 main_font=chaste_font_load("./font/FreeBASIC Font 8.png");
 chaste_palette_rainbow(40);
 title_screen();
 sfml_chastetris();
 window.close();

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

 return 0;
}

