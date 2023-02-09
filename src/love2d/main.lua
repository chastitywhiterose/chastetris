
--dimensions for screen
width = 1280;
height = 720;

require "chastetris"
require "gamesave"

 block_size=height/grid_height;
 print("block size="..block_size);


grid_offset_x=math.floor( (width-(20/2*block_size)) / 2 );
print(grid_offset_x.."=grid_offsex_x");

border_size=12; --size of borders on sides of field

p=0; --temporary pixel variable

--this function runs on program startup
function love.load()



 love.window.setTitle("Chastity's Love2D Game");
 love.window.setMode( width, height)

 rect={} --make a rectangle object
 rect.x=0;
 rect.y=100;
 rect.width=100;
 rect.height=200;

--setup the game
 tetris_clear_screen();

 --tetris_grid_print();

 spawn_block();
 
 
 --set up the font
  font_size=32;
  mainFont = love.graphics.newFont("font/noto/NotoMono-Regular.ttf", font_size);
  --mainFont = love.graphics.newFont("font/noto/NotoSansMono-Regular.ttf", font_size);
  --mainFont = love.graphics.newFont("font/noto/NotoSansMono-Bold.ttf", font_size);
  love.graphics.setFont(mainFont); --make all text functions use this font
  
  last_key=' ';
  
  gamesave_init();

end --end of love.load

--this function draws to the screen every frame
function love.draw()
 love.graphics.setColor(1, 1, 1)
 love.graphics.print("Chaste Tris Love2D", font_size*1, font_size*0)
 love.graphics.print("Score="..score, font_size*1, font_size*2)
 love.graphics.print("Lines="..lines_cleared_total, font_size*1, font_size*3)
 love.graphics.print("Hold="..hold_block.id, font_size*1, font_size*4)


 love.graphics.print("Key="..last_key, font_size*1, font_size*21)


 
 --create an empty temp grid which is copy of main grid
 y=0;
 while(y<grid_height)
 do
  x=0;
  while(x<grid_width)
  do
   temp_grid.array[x+y*grid_width]=main_grid.array[x+y*grid_width];
   --print(temp_grid.array[x+y*grid_width]);
   x=x+1;
  end
  y=y+1;
 end
 
   --draw block onto temp grid at it's current location
  y=0;
  while(y<max_block_width)
  do
   x=0;
   while(x<max_block_width)
   do
    if(main_block.array[x+y*max_block_width]~=0) then
     if( temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]~=0 )then
      print("Error. Something already here");
     else
      temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]=main_block.id;
      --print(temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width].."theid");
     end
    end
    x=x+1;
   end
   y=y+1;
   end
 
  --display the tetris grid
 y=0;
 while(y<grid_height)
 do
  x=0;
  while(x<grid_width)
  do
   p=temp_grid.array[x+y*grid_width];
   --print("x="..x.." y="..y.." p="..tostring(p));
   if(p==nil)then
    love.graphics.setColor(0.5,0.5,0.5)
    print("nil pixel error");
    print(temp_grid.array[x+y*grid_width]);
    elseif(p=='I') then
    love.graphics.setColor(0, 1, 1);
    elseif(p=='T') then
    love.graphics.setColor(1, 0, 1);
    elseif(p=='Z') then
    love.graphics.setColor(1, 0, 0);
    elseif(p=='J') then
    love.graphics.setColor(0, 0, 1);
    elseif(p=='O') then
    love.graphics.setColor(1, 1, 0);
    elseif(p=='L') then
    love.graphics.setColor(1, 0.5, 0);
    elseif(p=='S') then
    love.graphics.setColor(0, 1, 0);

    else
    love.graphics.setColor(0, 0, 0);
   end
   
  love.graphics.rectangle("fill",grid_offset_x+x*block_size,y*block_size,block_size,block_size);
  --print("grid_offset_x+x="..grid_offset_x+x);
  --print("y*block_size="..y*block_size);
  --print("block_size="..block_size);

   x=x+1;
     --print("x="..x);
  end
  y=y+1;
    --print("y="..y);

 end
 
 love.graphics.setColor(0.5, 0.5, 0.5);
 love.graphics.rectangle("fill",grid_offset_x-border_size,0*block_size,border_size,height); --left border
  love.graphics.rectangle("fill",grid_offset_x+grid_width*block_size,0*block_size,border_size,height); --right border
 
-- DrawRectangle(grid_offset_x-border_size,0*block_size,border_size,height,ray_border_color);
--DrawRectangle(grid_offset_x+grid_width*block_size,0*block_size,border_size,height,ray_border_color);

  
  end
    
--function to handle what happens when a key is pressed.
function love.keypressed(k)

 --print("key="..k)
 last_key=k;


 if k == 'escape' then
  love.event.quit()
 end
 
 if k == 'right' or k=='d' then
  tetris_move_right();
 end
 
 if k == 'left' or k=='a' then
  tetris_move_left();
 end

 if k == 'up' or k=='w' then
 tetris_move_up();
 end
 
 if k == 'down' or k=='s' then
 tetris_move_down();
 end
 
 if k == 'z' then
  block_rotate_left_basic();
 end
 if k == 'x' then
  block_rotate_right_basic();
 end
 
 if k == 'c' then
  block_hold();
 end
 
 
 if k == 'i' then
  save_gamesave();
 end
 
 if k == 'p' then
  load_gamesave();
 end
 
 
end




