/*
 Chastity font
 
 This file has some functions for loading and drawing my custom bitmap fonts and defines a font structure that I created which makes use of Raylib textures.
 */

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
struct chaste_font main_font,font_8,font_16,font_32,font_64,font_128,font_pico8;

/*function to load a font and return a structure with the needed data to draw later*/
struct chaste_font chaste_font_load(char *s)
{
 struct chaste_font new_font;
 printf("This function tries to load a font\n");

 new_font.texture=LoadTexture(s);
 /*by default,font size is detected by original image height*/
 new_font.char_width=new_font.texture.width/95; /*there are 95 characters in my font files*/
 new_font.char_height=new_font.texture.height;

 if(new_font.char_height==0)
 {
  printf("Something went horribly wrong loading the font from file:\n%s\n",s);
 }
 else
 {
  printf("Font loaded correctly\n");
  printf("Size of loaded font is %dx%d\n",new_font.char_width,new_font.char_height);
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
   cx+=main_font.char_width;
  }
  i++;
 }
}


















/*
 This function successfully draws a string of characters from the current loaded main font 
 arguments are: character pointer, character x pos, character y pos, integer scale
 
 It makes use of DrawTexturePro which is quite a complicated function capable of scaling as well as rotating textures.
 Rotation makes no sense when outputting text which is meant to be readable.
 But the scaling abilities of this function mean that it can multiply the font size by whatever you give it.
 Therefore, an 8x8 character font such as the smallest one I have created can literally be scaled to any multiple of 8. So a scale of 3 would result in each character being 24x24.
*/
void chaste_font_draw_string_scaled(char *s,int cx,int cy,int scale)
{
 float rotation=0; /*this should always be zero*/

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
   Rectangle rect_dest={ cx, cy, main_font.char_width*scale,main_font.char_height*scale };
   Vector2 origin = {0,0};
   DrawTexturePro(main_font.texture, rect_source, rect_dest, origin,rotation, WHITE);
   cx+=main_font.char_width*scale;
  }
  i++;
 }
}



