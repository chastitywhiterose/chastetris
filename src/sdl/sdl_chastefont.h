/*chastity font SDL version*/


/*
font structure

In the raylib code, this uses a Texture2D. In another graphics library it may be different if ported.
In the SDL version, a surface is used.
*/
struct chaste_font
{
 int char_width; /*width of a char*/
 int char_height; /*height of a char*/
 SDL_Surface *surface; /*the surface of the image of loaded font*/
};



/*global fonts that will be reused many times*/
struct chaste_font main_font,font_8,font_16,font_32,font_64,font_128,font_pico8;

/*function to load a font and return a structure with the needed data to draw later*/
struct chaste_font chaste_font_load(char *s)
{
 struct chaste_font new_font;
 printf("Loading font: %s\n",s);

 new_font.surface=SDL_LoadBMP(s);

 if(new_font.surface==NULL){printf( "SDL could not load image! SDL_Error: %s\n",SDL_GetError());return new_font;}

 /*
  by default,font height is detected by original image height
  but the font width is the width of the image divided by 95
  because there are exactly 95 characters in the font format that I created.
 */
 new_font.char_width=new_font.surface->w/95; /*there are 95 characters in my font files*/
 new_font.char_height=new_font.surface->h;

 if(new_font.char_height==0)
 {
  printf("Something went horribly wrong loading the font from file:\n%s\n",s);
 }
 else
 {
  /*printf("Font loaded correctly\n");*/
  printf("Size of loaded font is %d,%d\n",new_font.char_width,new_font.char_height);
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
 SDL_Rect rect_source,rect_dest;
 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height;}
  else
  {
   x=(c-' ')*main_font.char_width;
   y=0*main_font.char_height;

   rect_source.x=x;
   rect_source.y=y;
   rect_source.w=main_font.char_width;
   rect_source.h=main_font.char_height;

   rect_dest=rect_source;
   rect_dest.x=cx;
   rect_dest.y=cy;

   SDL_BlitSurface(main_font.surface,&rect_source,surface,&rect_dest);
   cx+=main_font.char_width;
  }
  i++;
 }
}





/*
 This function successfully draws a string of characters from the current loaded main font 
 arguments are: character pointer, character x pos, character y pos, integer scale
 
 It makes use of SDL_BlitScaled which is a function capable of scaling images.
 The scaling abilities of this function mean that it can multiply the font size by whatever you give it.
 Therefore, an 8x8 character font such as the smallest one I have created can literally be scaled to any multiple of 8. So a scale of 3 would result in each character being 24x24.
 
 HOWEVER: it is important that the source bitmap must be 32 bit RGB mode and not indexed or grayscale.
 Otherwise the SDL_GetError() result is:
 "Error: Blit combination not supported"
 
*/
void chaste_font_draw_string_scaled(char *s,int cx,int cy,int scale)
{
 int x,y,i,c,cx_start=cx;
 SDL_Rect rect_source,rect_dest;
 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height;}
  else
  {
   x=(c-' ')*main_font.char_width;
   y=0*main_font.char_height;

   rect_source.x=x;
   rect_source.y=y;
   rect_source.w=main_font.char_width;
   rect_source.h=main_font.char_height;

   rect_dest=rect_source;
   rect_dest.x=cx;
   rect_dest.y=cy;
   rect_dest.w=main_font.char_width*scale;
   rect_dest.h=main_font.char_height*scale;

   if(SDL_BlitScaled(main_font.surface,&rect_source,surface,&rect_dest)){printf("Error: %s\n",SDL_GetError());}
   cx+=main_font.char_width*scale;
  }
  i++;
 }
}







