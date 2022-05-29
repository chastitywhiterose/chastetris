/*chastity font*/

/*this file has been converted from the Raylib font library written by Chastity White Rose*/


/*
font structure

In the raylib code, this uses a Texture2D. In Allegro 4 it uses a BITMAP.
*/
struct chaste_font
{
 int char_width; /*width of a char*/
 int char_height; /*height of a char*/
 BITMAP *bitmap; /*the bitmap of the image of loaded font*/
 PALETTE palette; /*each bitmap has an associated palette*/
};

/*global fonts that will be reused many times*/
struct chaste_font main_font,font_8,font_16,font_32,font_64,font_128;

/*function to load a font and return a structure with the needed data to draw later*/
struct chaste_font chaste_font_load(char *s)
{
 struct chaste_font new_font;
 printf("Loading font '%s'\n",s);

 new_font.bitmap=load_bitmap(s, new_font.palette);

 if(new_font.bitmap==NULL){printf( "Allegro could not load image %s\n",s);return new_font;}

 /* by default,font size is detected by original image height */
 new_font.char_width=new_font.bitmap->h;
 new_font.char_height=new_font.bitmap->h;

 if(new_font.char_height==0)
 {
  printf("Something went horribly wrong loading the font from file:\n%s\n",s);
 }
 else
 {
  printf("Font loaded correctly\n");
  printf("Size of loaded font is %d\n",new_font.char_height);
/*
  printf("Width of loaded image is %d\n",al_get_bitmap_width(new_font.bitmap));
  printf("Height of loaded image is %d\n",al_get_bitmap_height(new_font.bitmap));
*/
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
   /*printf("char '%c' at %d,%d\n",c,cx,cy);*/
   blit(main_font.bitmap, screen, x,y, cx,cy, main_font.char_width, main_font.char_height);
   cx+=main_font.char_width;
  }
  i++;
 }

}




