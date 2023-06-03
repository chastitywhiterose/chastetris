/*
 Chastity font SDL texture version
 
 This file is a clone of my font library that uses textures instead of surfaces.
 The functions and struct have the same names as the surface version so that it can be used as a drop in replacement depending on whether I am using a renderer or not.
*/


/*
texture font structure
*/
struct chaste_font
{
 int char_width; /*width of a char*/
 int char_height; /*height of a char*/
 SDL_Surface *surface; /*the surface of the image of loaded font*/
 SDL_Texture *texture; /*the texture of this font which will be loaded from surface*/
};



/*global fonts that will be reused many times*/
struct chaste_font main_font,font_8,font_16,font_32,font_64,font_128,font_pico8;

/*function to load a font and return a structure with the needed data to draw later*/
struct chaste_font chaste_font_load(char *s)
{
 int w,h;
 struct chaste_font new_font;
 SDL_Surface *temp_surface;
 printf("Loading font: %s\n",s);

 /*load bitmap to temporary surface*/
 temp_surface=SDL_LoadBMP(s);

 /*convert to BGRA32 pixel format for easy handling for later functions*/
 new_font.surface=SDL_ConvertSurfaceFormat(temp_surface, SDL_PIXELFORMAT_BGRA32, 0);
 SDL_FreeSurface(temp_surface);

 if(new_font.surface==NULL){printf( "SDL could not load image! SDL_Error: %s\n",SDL_GetError());return new_font;}
 new_font.texture=SDL_CreateTextureFromSurface(renderer,new_font.surface);
 if(new_font.texture==NULL){printf( "SDL could not load texture from surface! SDL_Error: %s\n",SDL_GetError());return new_font;}
 else
 {
  SDL_QueryTexture(new_font.texture,NULL,NULL,&w,&h);
  printf("texture width==%d height==%d\n",w,h);
 }
 
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

   /*SDL_BlitSurface(main_font.surface,&rect_source,surface,&rect_dest);*/
   if(SDL_RenderCopy(renderer,main_font.texture,&rect_source,&rect_dest)){printf( "RenderCopy Error SDL_Error: %s\n",SDL_GetError());}
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

   if(SDL_RenderCopy(renderer,main_font.texture,&rect_source,&rect_dest)){printf( "RenderCopy Error SDL_Error: %s\n",SDL_GetError());}
   cx+=main_font.char_width*scale;
  }
  i++;
 }
}


void chaste_font_free(struct chaste_font font)
{
 SDL_FreeSurface(font.surface);
 SDL_DestroyTexture(font.texture);
}





/*
this uses direct pixel access of the source font surface to draw only when the source pixel is not black. But this one is "special" because it can optionally change the color for each scaled pixel!
*/
void chaste_font_draw_string_scaled_special(char *s,int cx,int cy,int scale)
{
 int x,y,i,c,cx_start=cx;
 Uint32 *ssp; /*ssp is short for Source Surface Pointer*/
 int sx,sy,sx2,sy2,dx,dy; /*x,y coordinates for both source and destination*/
 Uint32 pixel,r,g,b; /*pixel that will be read from*/
 int source_surface_width;
 SDL_Rect rect_source,rect_dest;

 source_surface_width=main_font.surface->w;

 /*SDL_LockSurface(main_font.surface);*/
 ssp=(Uint32*)main_font.surface->pixels;
  
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

 
   /*Now for the ultra complicated stuff that only Chastity can read and understand!*/
   sx2=rect_source.x+rect_source.w;
   sy2=rect_source.y+rect_source.h;
   
   dx=cx;
   dy=cy;
   
   sy=rect_source.y;
   while(sy<sy2)
   {
    dx=cx;
    sx=rect_source.x;
    while(sx<sx2)
    {
     pixel=ssp[sx+sy*source_surface_width];

      pixel&=0xFFFFFF;
     
     /*printf("pixel 0x%06X %d,%d\n",pixel,sx,sy);*/
     if(pixel!=0) /*only if source pixel is nonzero(not black) draw square to destination*/
     {
      /*set up the rectangle to draw to*/
      rect_dest.x=dx;
      rect_dest.y=dy;
      rect_dest.w=scale;
      rect_dest.h=scale;
      
      pixel=chaste_palette[chaste_palette_index];
      
      r=(pixel&0xFF0000)>>16;
      g=(pixel&0x00FF00)>>8;
      b=(pixel&0x0000FF);
      
      SDL_SetRenderDrawColor(renderer,r,g,b,255);
      SDL_RenderFillRect(renderer,&rect_dest);
      
      chaste_next_color();
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
 /*SDL_UnlockSurface(main_font.surface);*/
}


