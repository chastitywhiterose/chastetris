/*chastity font*/




/*
font structure

In the raylib code, this uses a Texture2D. In another graphics library it may be different if ported.
*/
struct chaste_font
{
 int char_width; /*width of a char*/
 int char_height; /*height of a char*/
 ALLEGRO_BITMAP *bitmap; /*the bitmap of the image of loaded font*/
};

/*global fonts that will be reused many times*/
struct chaste_font main_font,font_8,font_16,font_32,font_64,font_128;

/*function to load a font and return a structure with the needed data to draw later*/
struct chaste_font chaste_font_load(char *s)
{
 struct chaste_font new_font;
 printf("Loading font '%s'\n",s);

 new_font.bitmap=al_load_bitmap(s);

 if(new_font.bitmap==NULL){printf( "Allegro could not load image %s\n",s);return new_font;}

 /*by default,font size is detected by original image height*/
 new_font.char_width=al_get_bitmap_height(new_font.bitmap);
 new_font.char_height=al_get_bitmap_height(new_font.bitmap);

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
   al_draw_bitmap_region(main_font.bitmap,x,y,main_font.char_width,main_font.char_height,cx,cy,0);
   cx+=main_font.char_width;
  }
  i++;
 }
}




/*can draw a scaled version of the main font*/
void chaste_font_draw_string_scaled(char *s,int cx,int cy,int scale)
{
 int x,y,i,c,cx_start=cx;
 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height*scale;}
  else
  {
   x=(c-' ')*main_font.char_width;
   y=0*main_font.char_height;

al_draw_scaled_bitmap(main_font.bitmap,x,y,main_font.char_width,main_font.char_height,cx,cy,main_font.char_width*scale,main_font.char_height*scale,0);

   cx+=main_font.char_width*scale;
  }
  i++;
 }
}


























/*
this uses direct pixel access of the source font surface to draw only when the source pixel is not black. But this one is "special" because it can optionally change the color for each scaled pixel!
*/
void chaste_font_draw_string_scaled_special(char *s,int cx,int cy,int scale)
{
 int x,y,i,c,cx_start=cx;
 int sx,sy,sx2,sy2,dx,dy; /*x,y coordinates for both source and destination*/
 ALLEGRO_COLOR color; /*color read from source image*/
 unsigned int pixel; /*32 bit pixel*/
 unsigned char r,g,b; /*color components*/

 /*lock bitmap for reading only. speeds things up*/
 al_lock_bitmap(main_font.bitmap,ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
  
 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height*scale;}
  else
  {
   x=(c-' ')*main_font.char_width;
   y=0*main_font.char_height;
 
   sx2=x+main_font.char_width;
   sy2=y+main_font.char_height;
   
   dx=cx;
   dy=cy;
   
   sy=y;
   while(sy<sy2)
   {
    dx=cx;
    sx=x;
    while(sx<sx2)
    {

     color=al_get_pixel(main_font.bitmap, sx, sy);
     al_unmap_rgb(color,&r,&g,&b);
     pixel=(r<<16)|(g<<8)|b;
     
     /*pixel&=0xFFFFFF;*/
     
     if(pixel!=0) /*only if source pixel is nonzero(not black) draw square to destination*/
     {
      /*printf("pixel 0x%06X %d,%d\n",pixel,sx,sy);*/

      pixel=chaste_palette[chaste_palette_index];
      
      r=(pixel&0xFF0000)>>16;
      g=(pixel&0x00FF00)>>8;
      b=(pixel&0x0000FF);
      
      color=al_map_rgb(r, g, b);

      al_draw_filled_rectangle(dx,dy,dx+scale,dy+scale,color);
      
      chaste_next_color();
     }
     
     sx++;
     dx+=scale;
    }
    sy++;
    dy+=scale;
   }
   cx+=main_font.char_width*scale;
  }
  i++;
 }
 al_unlock_bitmap(main_font.bitmap);
}



