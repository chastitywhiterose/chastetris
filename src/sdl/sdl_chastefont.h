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
 SDL_Surface *temp_surface;
 printf("Loading font: %s\n",s);

 /*load bitmap to temporary surface*/
 temp_surface=SDL_LoadBMP(s);

 /*convert to same surface as screen for faster blitting*/
 new_font.surface=SDL_ConvertSurface(temp_surface, surface->format, 0);
 
 /*free the temp surface*/
 SDL_FreeSurface(temp_surface); 

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
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height*scale;}
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






/*
 The scaled version of my font drawing function that uses direct pixel access
 For the sake of efficiency, it does not check to see if the source(main_font.surface) and destination(screen)
 are of the same type. My font library has been updated to make sure they are when loading the font from the file.
 This makes SDL_GetRGB and SDL_MapRGB useless and they have been removed to speed up things by removing function calls.
 
 You may wonder why I wrote such an odd function.
 This is because it can draw text at any color instead of only blitting the source to the destination.
 It accepts a color argument after the scale and does not actually use SDL_BlitSurface or SDL_BlitScaled to do any of the work.
 This is entirely my code because I understand how to access the pixels directly.
 This allows for portability to any graphics/media library.
 But SDL is rather superior to other libraries because it allows me to access the pixels the way I want.
*/

void chaste_font_draw_string_scaled_color(char *s,int cx,int cy,int scale,int color)
{
 int x,y,i,c,cx_start=cx;
 Uint32 *ssp; /*ssp is short for Source Surface Pointer*/
 Uint32 *dsp; /*dsp is short for Destination Surface Pointer*/
 int sx,sy,sx2,sy2,dx,dy; /*x,y coordinates for both source and destination*/
 Uint32 pixel; /*pixel that will be read from*/
 int source_surface_width;
 SDL_Rect rect_source,rect_dest;

 source_surface_width=main_font.surface->w;

 SDL_LockSurface(main_font.surface);
 SDL_LockSurface(surface);
 
 ssp=(Uint32*)main_font.surface->pixels;
 dsp=(Uint32*)surface->pixels;
  
 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height*scale;}
  else
  {
   x=(c-' ')*main_font.char_width;
   y=0*main_font.char_height;

   /*set up source rectangle where this character will be copied from*/
   rect_source.x=x;
   rect_source.y=y;
   rect_source.w=main_font.char_width;
   rect_source.h=main_font.char_height;

   /*set up destination rectangle where this character will be drawn to*/
   rect_dest.x=cx;
   rect_dest.y=cy;
   
   /*Now for the ultra complicated stuff that only Chastity can read and understand!*/
   sx2=rect_source.x+rect_source.w;
   sy2=rect_source.y+rect_source.h;
   
   dx=rect_dest.x;
   dy=rect_dest.y;
   
   sy=rect_source.y;
   while(sy<sy2)
   {
    dx=rect_dest.x;
    sx=rect_source.x;
    while(sx<sx2)
    {
     pixel=ssp[sx+sy*source_surface_width];
 
     if(pixel!=0) /*only if source pixel is nonzero(not black) draw square to destination*/
     {
      int tx,ty,tx2,ty2; /*temp variables only for the square*/
      ty2=dy+scale;
      
      /*draw a square of width/height equal to scale*/      
      ty=dy;
      while(ty<ty2)
      {
       tx=dx;
       tx2=dx+scale;
       while(tx<tx2)
       {
        dsp[tx+ty*width]=color;
        tx++;
       }
       ty++;
      }
      /*end of rectangle*/
     }
     sx++;
     dx+=scale;
    }
    sy++;
    dy+=scale;
   }
   /*End of really complicated section*/
   cx+=main_font.char_width*scale;
  }
  i++;
 }
 SDL_UnlockSurface(main_font.surface);
 SDL_UnlockSurface(surface);
}

