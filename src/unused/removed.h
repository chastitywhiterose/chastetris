/*
this header contains old functions which are no longer part of chaste_tris. There is nothing wrong with any of them but they don't fit the vision I have for what I want the game to be and I also want to reduce code size to make maintaining it easier
*/

/*
this function draws the stats of the game such as the lines and score using the built in raylib font
it's in a separate function so that I can switch it out with another function when I feel like it
*/
void draw_stats()
{

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

}







void welcome_screen()
{

/*load a font before any text is drawn*/

//font = LoadFont("./font/Hack-Regular.ttf");

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


 DrawText("Programming: Chastity White Rose",text_x,fontsize*2,fontsize, (Color){255,255,255,255});
 DrawText("Inspiration: River Black Rose",text_x,fontsize*3,fontsize, (Color){255,255,255,255});

 DrawText("Press Enter to Begin game.",text_x,fontsize*5,fontsize, (Color){255,255,255,255});

 DrawText("https://github.com/chastitywhiterose/chastetris",text_x,fontsize*8,40, (Color){255,255,255,255});

 DrawText("Email: chastitywhiterose@gmail.com",text_x,fontsize*9,40, (Color){255,255,255,255});

 EndDrawing();
}

}

/* this function is meant to load fonts from images and display them as a welcome screen*/
void welcome_screen_chaste_font_hello()
{

/*before the game actually runs, optionally display a start screen*/
while(!WindowShouldClose()) /*loop runs until key pressed*/
{
 if(IsKeyPressed(KEY_ENTER)){break;}
 BeginDrawing();
 ClearBackground((Color){255,0,0,255});
 chaste_font_draw_string("Hello World!\nI am:\n\nChastity\nWhite\nRose",100,100);
 EndDrawing();
}

}







/*
 this function successfully draws a character from the loaded font
 arguments are: character, character x pos, character y pos
*/
void chaste_font_draw_char(int c,int cx,int cy)
{
 int x,y;
 //printf("The character to print is '%c'\n",c);

 x=(c-' ')*main_font.char_width;
 y=0*main_font.char_height;
 //printf("X=%d Y=%d\n",x,y);

 Rectangle rect_source = {x,y,main_font.char_width,main_font.char_height};
 Vector2 pos = {cx,cy}; /*coordinates of where char will be drawn*/


DrawTextureRec(main_font.texture, rect_source, pos, (Color){255,255,255,255});

}


