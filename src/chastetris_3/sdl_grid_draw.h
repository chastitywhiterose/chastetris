/*sdl_grid_draw.h*/

int block_size;
int grid_offset_x;

void show_grid_fill_rect()
{
 int pixel,r,g,b;
 int x=0,y=0;

 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   pixel=temp_grid.array[x+y*grid_width];
   r=(pixel&0xFF0000)>>16;
   g=(pixel&0x00FF00)>>8;
   b=(pixel&0x0000FF);


/* printf("x=%d y=%d ",x,y);
 printf("red=%d green=%d blue=%d\n",r,g,b);*/


/*rect_color=SDL_MapRGB(surface->format,r,g,b);*/

 SDL_SetRenderDrawColor(renderer,r,g,b,255);


/*set up the rectangle structure with the needed data to square the squares*/
rect.x=grid_offset_x+x*block_size;
rect.y=y*block_size;
rect.w=block_size;
rect.h=block_size;

SDL_RenderFillRect(renderer,&rect);


   x+=1;
  }
  y+=1;
 }
}

void show_grid_draw_rect()
{
 int pixel,r,g,b;
 int x=0,y=0;

 int rmod=1; /*the rectangle modifier. 1 is usually best*/

 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   pixel=temp_grid.array[x+y*grid_width];
   r=(pixel&0xFF0000)>>16;
   g=(pixel&0x00FF00)>>8;
   b=(pixel&0x0000FF);

 SDL_SetRenderDrawColor(renderer,r,g,b,255);

/*set up the rectangle structure with the needed data to square the squares*/
rect.x=grid_offset_x+x*block_size+rmod;
rect.y=y*block_size+rmod;
rect.w=block_size-rmod;
rect.h=block_size-rmod;

SDL_RenderDrawRect(renderer,&rect);


   x+=1;
  }
  y+=1;
 }
}





/*
 a function pointer that points to the current function used for drawing the tetris grid
*/
void (*show_grid)()=show_grid_fill_rect;
