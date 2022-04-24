/*chastity font*/




/*
font structure
this isn't currently used in code yet
*/
struct chaste_font
{
 int char_width; /*width of a char*/
 int char_height; /*height of a char*/


};



Texture2D texture_font_8; /*this font is global because it will be reused a lot*/

int fsize=8; /*size in both width and height for each character*/

void chaste_font_load()
{
 printf("This function tries to load a font\n");
 texture_font_8=LoadTexture("./font/bitmap/FreeBASIC Font 64.png");

 fsize=texture_font_8.height; /*font size is detected by original image height*/
 printf("Size of loaded font is %d\n",fsize);

}




/*
 this function successfully draws a character from the loaded font
 arguments are: character, character x pos, character y pos
*/
void chaste_font_draw_char(int c,int cx,int cy)
{
 int x,y;
 //printf("The character to print is '%c'\n",c);


 x=(c-' ')*fsize;
 y=0*fsize;
 //printf("X=%d Y=%d\n",x,y);

 Rectangle rect_source = {x,y,fsize,fsize};
 Vector2 pos = {cx,cy}; /*coordinates of where char will be drawn*/


DrawTextureRec(texture_font_8, rect_source, pos, (Color){255,255,255,255});

}



/*
 this function successfully draws a string of characters from the loaded font
 arguments are: character pointer, character x pos, character y pos
*/
void chaste_font_draw_string(char *s,int cx,int cy)
{
 int x,y,i,c,cx_start=cx;
 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=fsize;}
  else
  {
   x=(c-' ')*fsize;
   y=0*fsize;
   Rectangle rect_source = {x,y,fsize,fsize};
   Vector2 pos = {cx,cy}; /*coordinates of where char will be drawn*/
   DrawTextureRec(texture_font_8, rect_source, pos, (Color){255,255,255,255});
   cx+=fsize;
  }
  i++;
 }
}




