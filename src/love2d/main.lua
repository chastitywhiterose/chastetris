
--dimensions for screen
width = 1280;
height = 720;

require "chastetris"
require "chastegame"
require "gamesave"

 block_size=height/grid_height;
 --print("block size="..block_size);


grid_offset_x=math.floor( (width-(20/2*block_size)) / 2 );
--print(grid_offset_x.."=grid_offsex_x");

border_size=12; --size of borders on sides of field

p=0; --temporary pixel variable

--this function runs on program startup
function love.load()

 love.window.setTitle("Chastity's Love2D Game");
 love.window.setMode( width, height)

 game_loop_init(); 
 
 --set up the font
  font_size=32;
  mainFont = love.graphics.newFont("font/noto/NotoMono-Regular.ttf", font_size);
  --mainFont = love.graphics.newFont("font/noto/NotoSansMono-Regular.ttf", font_size);
  --mainFont = love.graphics.newFont("font/noto/NotoSansMono-Bold.ttf", font_size);
  love.graphics.setFont(mainFont); --make all text functions use this font
  
  last_key=' ';
  
  gamesave_init(); --create empty save state objects
  
  gamefunc=game_title; --start at title screen first
  keyfunc=game_title_keyboard;

  
  
  
  --begin input movelog reading 
  f=io.open("imovelog.txt","rb");
  if(f~=nil)
  then
   s=f:read("*all");
   f:close();
  end
  --end movelog reading
  
  if(s==nil) then
   print("No input movelog file. Keyboard only this run.");
   log_length=0;
  else
  
   print("input movelog file loaded");
   --print(s);
   print("length of movelog="..#s);
   
   log_length=#s;
  
  
   --copy the string to movelog array
   x=0;
   sx=1
   while(sx<=#s)
   do
    move_log[x]=string.sub(s,sx,sx);
    --io.write(string.sub(s,sx,sx));
    --io.write(move_log[x]);
    x=x+1;
    sx=sx+1;
   end
  
  end --end of large if statement

end --end of love.load




--this function draws to the screen every frame
function love.draw()
 gamefunc(); 
end
    
--function to handle what happens when a key is pressed.
function love.keypressed(k)
 keyfunc(k);
end




