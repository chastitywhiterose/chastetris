/*
 file to handle polygon animations
*/

struct polygon
{
 double cx,cy;
 int sides;
 double radius;
 double radians;
 Color color;
};

struct polygon main_polygon;

void init_polygon()
{
 main_polygon.cx=width/2;
 main_polygon.cy=height/2;
 main_polygon.sides=3;
 main_polygon.radius=height/2;
 main_polygon.radians=0;
 main_polygon.color=(Color){255,255,255,255};
}


void polygon_draw()
{
 DrawPoly((Vector2){main_polygon.cx,main_polygon.cy}, main_polygon.sides, main_polygon.radius, main_polygon.radians,main_polygon.color);
}

void polygon_draw_lines()
{
 DrawPolyLines((Vector2){main_polygon.cx,main_polygon.cy}, main_polygon.sides, main_polygon.radius, main_polygon.radians,main_polygon.color);
}

