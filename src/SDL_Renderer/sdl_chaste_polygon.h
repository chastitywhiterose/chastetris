/*sdl_chaste_polygon.h*/

struct polygon
{
 double cx,cy;
 int sides;
 double radius;
 double radians;
 SDL_Color color;
 int step; /*used only in star polygons of 5 or more sides*/
};

struct polygon main_polygon;



void init_polygon()
{
 main_polygon.cx=width/2;
 main_polygon.cy=height/2;
 main_polygon.sides=3;
 main_polygon.step=2;
 main_polygon.radius=height/2;
 main_polygon.radians=0;

 main_polygon.color.r=255;
 main_polygon.color.g=255;
 main_polygon.color.b=255;
 main_polygon.color.a=255;

}


/*
 this function created because the standard round function did not exist in C until 1999 standard.
 I only use 1989 standard. It is sometimes helpful to round to neared integer when the data type requires it.
 Original source here: https://en.cppreference.com/w/c/numeric/math/round
*/
double chaste_round(double x)
{
 return x<0 ? ceil(x - 0.5) : floor(x + 0.5);
}




/*Define PI the same as M_PI in math.h*/
 #define PI 3.14159265358979323846f

/*these point arrays are temporary and not included in the polygon structure*/
int polygon_xpoints[0x1000],polygon_ypoints[0x1000];


/*
function to get the points of a regular polygon and load them into the above arrays of x and y points
*/
void chaste_polygon_points()
{
 double angle,x,y;
 int i=0;
 while(i<main_polygon.sides)
 {
  angle=2*PI*i/main_polygon.sides+main_polygon.radians;
  x=main_polygon.cx+sin(angle)*main_polygon.radius;
  y=main_polygon.cy-cos(angle)*main_polygon.radius;
  polygon_xpoints[i]=chaste_round(x);
  polygon_ypoints[i]=chaste_round(y);
  i++;
 }
}


/* large array for any possible combination of vertices to make many triangles*/
SDL_Vertex vertices[0x1000];


/*
 this function doesn't draw anything but instead modifies the colors of the vertices to make
 really awesome looking polygons if called before the drawing loop
*/
void chaste_triangle_color_rgb()
{
 vertices[0].color.r=255;
 vertices[0].color.g=0;
 vertices[0].color.b=0;
 vertices[1].color.r=0;
 vertices[1].color.g=255;
 vertices[1].color.b=0;
 vertices[2].color.r=0;
 vertices[2].color.g=0;
 vertices[2].color.b=255;
}

SDL_Color temp_color;

/*this first function draws a series of triangles to make a convex regular polygon*/
void chaste_polygon_draw()
{
 int i,i1;
 chaste_polygon_points();
 
 vertices[0].color=main_polygon.color;
 vertices[1].color=main_polygon.color;
 vertices[2].color=main_polygon.color;
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+1)%main_polygon.sides;
  
  /*for each part of this loop,construct a triangle*/
  vertices[0].position.x=polygon_xpoints[i];
  vertices[0].position.y=polygon_ypoints[i];
  vertices[1].position.x=polygon_xpoints[i1];
  vertices[1].position.y=polygon_ypoints[i1];
  vertices[2].position.x=main_polygon.cx;
  vertices[2].position.y=main_polygon.cy;
  
  SDL_RenderGeometry(renderer,NULL,vertices,3,NULL,0);
  
  i++;
 }
 
}







/*
 this first function draws a series of triangles to make any kind of regular polygon
 this includes star polygons by taking into account the step value between points.
*/
void chaste_polygon_draw_star()
{
 int i,i1;
 chaste_polygon_points();
 
 vertices[0].color=main_polygon.color;
 vertices[1].color=main_polygon.color;
 vertices[2].color=main_polygon.color;
 
 /*chaste_triangle_color_rgb();*/
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+main_polygon.step)%main_polygon.sides;
  
  /*for each part of this loop,construct a triangle*/
  vertices[0].position.x=polygon_xpoints[i];
  vertices[0].position.y=polygon_ypoints[i];
  vertices[1].position.x=polygon_xpoints[i1];
  vertices[1].position.y=polygon_ypoints[i1];
  vertices[2].position.x=main_polygon.cx;
  vertices[2].position.y=main_polygon.cy;
  
  SDL_RenderGeometry(renderer,NULL,vertices,3,NULL,0);

  /*swap colors around to show off*/  
/*  temp_color=vertices[0].color;
  vertices[0].color=vertices[1].color;
  vertices[1].color=vertices[2].color;
  vertices[2].color=temp_color;*/
  i++;
 }
 
}




/*
 this first function draws a series of lines to make an outline of any regular polygon
 this includes star polygons by taking into account the step value between points.
*/
void chaste_polygon_draw_lines()
{
 int i,i1;
 chaste_polygon_points();
 SDL_SetRenderDrawColor(renderer,main_polygon.color.r,main_polygon.color.g,main_polygon.color.b,255);
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+1)%main_polygon.sides;
  SDL_RenderDrawLine(renderer,polygon_xpoints[i], polygon_ypoints[i], polygon_xpoints[i1], polygon_ypoints[i1]);
  i++;
 }
}



/*
 this first function draws a series of lines to make an outline of any regular polygon
 this includes star polygons by taking into account the step value between points.
*/
void chaste_polygon_draw_star_lines()
{
 int i,i1;
 chaste_polygon_points();
 SDL_SetRenderDrawColor(renderer,main_polygon.color.r,main_polygon.color.g,main_polygon.color.b,255);
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+main_polygon.step)%main_polygon.sides;
  SDL_RenderDrawLine(renderer,polygon_xpoints[i], polygon_ypoints[i], polygon_xpoints[i1], polygon_ypoints[i1]);
  i++;
 }
}

