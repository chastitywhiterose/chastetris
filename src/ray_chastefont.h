/*chastity font*/




/*
font structure

In the raylib code, this uses a Texture2D. In another graphics library it may be different if ported.
*/
struct chaste_font
{
 int char_width; /*width of a char*/
 int char_height; /*height of a char*/
 Texture2D texture; /*the texture of the image of loaded font*/
};

/*global fonts that will be reused many times*/
struct chaste_font main_font,font_8,font_16,font_32,font_64,font_128;

/*function to load a font and return a structure with the needed data to draw later*/
struct chaste_font chaste_font_load(char *s)
{
 struct chaste_font new_font;
 printf("This function tries to load a font\n");

 new_font.texture=LoadTexture(s);
 /*by default,font size is detected by original image height*/
 new_font.char_width=new_font.texture.height;
 new_font.char_height=new_font.texture.height;

 if(new_font.char_height==0)
 {
  printf("Something went horribly wrong loading the font from file:\n%s\n",s);
 }
 else
 {
  printf("Font loaded correctly\n");
  printf("Size of loaded font is %d\n",new_font.char_height);
 }


 return new_font;
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
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height;}
  else
  {
   x=(c-' ')*main_font.char_width;
   y=0*main_font.char_height;
   Rectangle rect_source = {x,y,main_font.char_width,main_font.char_height};
   Vector2 pos = {cx,cy}; /*coordinates of where char will be drawn*/
   DrawTextureRec(main_font.texture, rect_source, pos, (Color){255,255,255,255});
   cx+=main_font.char_width;;
  }
  i++;
 }
}




