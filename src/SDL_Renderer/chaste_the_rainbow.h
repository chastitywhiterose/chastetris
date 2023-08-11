/*
Header file for creating global color palette. The main idea is to create beautiful rainbows.
*/

#define chaste_palette_max 0x1000000

/*global variables to be used to store the colors and how many there are*/
int chaste_palette[chaste_palette_max],chaste_palette_length=0,chaste_palette_index=0,chaste_palette_index1=0;

void chaste_next_color()
{
 chaste_palette_index++;
 if(chaste_palette_index>=chaste_palette_length)
 {
  chaste_palette_index=0;
 }
/* printf("chaste_palette_index=%d\n",chaste_palette_index);
 printf("color=%06X;\n",chaste_palette[chaste_palette_index]);*/
}

void chaste_prev_color()
{
 chaste_palette_index--;
 if(chaste_palette_index<=0)
 {
  chaste_palette_index=chaste_palette_length-1;
 }
 /*printf("chaste_palette_index=%d\n",chaste_palette_index);*/
}


void chaste_palette_view()
{
 int x=0;
 while(x<chaste_palette_length)
 {
  printf("chaste_palette[%d]=%06X;\n",x,chaste_palette[x]);
  x++;
 }
 printf("chaste_palette_length=%d;\n",chaste_palette_length);
}


/*
 This function attempts to make a rainbow using the integer n passed to it using degrees of red,green,blue.
 It seems that the number of colors is equal to 6*n. This means that if n is 20, you get 6*20==120;
 The max value n can be is 255 which gives 1530 colors! However my favorite is n=40 because 240 colors is really convenient for fitting under the 256 color gif limit.
*/
void chaste_palette_rainbow(int n)
{
 int x,color;
 int red=n,green=0,blue=0;
 x=0;
 while(green<n)
 {
  color=255*red/n;color*=256;color+=255*green/n;color*=256;color+=255*blue/n;chaste_palette[x]=color;
  x++;
  green++;
 }
 while(red>0)
 {
  color=255*red/n;color*=256;color+=255*green/n;color*=256;color+=255*blue/n;chaste_palette[x]=color;
  x++;
  red--; 
 }
 while(blue<n)
 {
  color=255*red/n;color*=256;color+=255*green/n;color*=256;color+=255*blue/n;chaste_palette[x]=color;
  x++;
  blue++;
 }
 while(green>0)
 {
  color=255*red/n;color*=256;color+=255*green/n;color*=256;color+=255*blue/n;chaste_palette[x]=color;
  x++;
  green--; 
 }
 while(red<n)
 {
  color=255*red/n;color*=256;color+=255*green/n;color*=256;color+=255*blue/n;chaste_palette[x]=color;
  x++;
  red++; 
 }
 while(blue>0)
 {
  color=255*red/n;color*=256;color+=255*green/n;color*=256;color+=255*blue/n;chaste_palette[x]=color;
  x++;
  blue--; 
 }
 chaste_palette_length=x;
 chaste_palette_index=0;
}

/*a function for testing how many colors are created with my rainbow function*/
void chaste_palette_rainbow_test(int n)
{
 chaste_palette_rainbow(n);
 chaste_palette_view();
}





/*
 A function to set up the global palette for my other needs according to the bpp that I have predefined to be valid.
 It basically makes a list of every color possible within a system with 1,2,4,8 bits for gray scale or 3,6,12 bits for full color
 This could be used for something in the future although I am not sure what yet!
*/
void chaste_palette_make(int bpp)
{
 int x,gray,bitcount,color,red,green,blue;

 chaste_palette_length=1<<bpp;

 /* if bpp is one of these, make the palette be grayscale. */
 if(bpp==1||bpp==2||bpp==4||bpp==8)
 {
  printf("making %d bpp grayscale palette\n",bpp);
  x=0;
  while(x<chaste_palette_length)
  {
   gray=x;
   /*convert gray into a 24 bit RGB equivalent.*/
   color=0;
   bitcount=0;
   while(bitcount<24)
   {
    color<<=bpp;
    color|=gray;
    bitcount+=bpp;
   }

   chaste_palette[x]=color;

   x++;
  }
 }

 else if(bpp==3||bpp==6||bpp==12)
 {
  printf("making %d bpp full color palette\n",bpp);

  bpp/=3;

  gray=(1<<bpp)-1;

  /*printf("graymask == %d\n",gray);*/

  x=0;
  while(x<chaste_palette_length)
  {
   color=x;
   blue=color&gray;color>>=bpp;
   green=color&gray;color>>=bpp;
   red=color&gray;color>>=bpp;

   /*printf("red=%d,green=%d,blue=%d\n",red,green,blue);*/

   /*next left shift red and green back to their proper position. blue doesn't need to be shifted.*/
    red<<=16;
    green<<=8;

    bitcount=0;
    while(bitcount<8)
    {
     color<<=bpp;
     color|=red;
     color|=green;
     color|=blue;
     bitcount+=bpp;
    }

   chaste_palette[x]=color;

   x++;
  }
 }

 else{printf("bpp of %d not supported.\n",bpp);return;}

}






/*
 Function based off what my mom called pastel colors. It cycles through yellow,cyan,magenta.

 This function attempts to make a rainbow using the integer n passed to it using degrees of red,green,blue.
 It seems that the number of colors is equal to 3*n. This means that if n is 20, you get 3*20==60;
 The max value n can be is 255 which gives 765 colors! My personal favorite is n=80 because 240 colors is really convenient for fitting under the 256 color gif limit.
*/
void chaste_palette_rainbow_pastel(int n)
{
 int x,color;
 int red=n,green=n,blue=0;
 x=0;

 while(blue<n)
 {
  color=255*red/n;color*=256;color+=255*green/n;color*=256;color+=255*blue/n;chaste_palette[x]=color;
  x++;
  blue++;
  red--;
 }
 while(red<n)
 {
  color=255*red/n;color*=256;color+=255*green/n;color*=256;color+=255*blue/n;chaste_palette[x]=color;
  x++;
  red++;
  green--;
 }
 while(green<n)
 {
  color=255*red/n;color*=256;color+=255*green/n;color*=256;color+=255*blue/n;chaste_palette[x]=color;
  x++;
  green++;
  blue--;
 }

 chaste_palette_length=x;
 chaste_palette_index=0;
}

