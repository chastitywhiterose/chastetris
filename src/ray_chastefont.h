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
 Image image; /*image that will be loaded*/
 Texture2D texture; /*the texture of the image of loaded font*/
};

/*global fonts that will be reused many times*/
struct chaste_font main_font,font_8,font_16,font_32,font_64,font_128,font_pico8;

/*function to load a font and return a structure with the needed data to draw later*/
struct chaste_font chaste_font_load(char *s)
{
 struct chaste_font new_font;
 printf("This function tries to load a font\n");
 
 /*load the file into an image*/
 new_font.image=LoadImage(s);

 /*load the image into a texture*/
 new_font.texture=LoadTextureFromImage(new_font.image);
 
 /*new_font.texture=LoadTexture(s);*/
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





/*rectangle structure meant to replace the one in SDL*/
struct chaste_rect
{
 int x,y,w,h;
};





/*
this uses direct pixel access of the source font surface to draw only when the source pixel is not black. But this one is "special" because it can optionally change the color for each scaled pixel!
*/
void chaste_font_draw_string_scaled_special(char *s,int cx,int cy,int scale)
{
 int x,y,i,c,cx_start=cx;
 int sx,sy,sx2,sy2,dx,dy; /*x,y coordinates for both source and destination*/
 Color color;
 uint32_t pixel,r,g,b; /*pixel that will be read from*/
 struct chaste_rect rect_source,rect_dest;
  
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
     color=GetImageColor(main_font.image,sx,sy);
     pixel=color.r<<16;
     pixel=pixel|color.g<<8;
     pixel=pixel|color.b;
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

      color=(Color){r,g,b,255};
      DrawRectangle(rect_dest.x,rect_dest.y,rect_dest.w,rect_dest.h,color);
      
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

}
