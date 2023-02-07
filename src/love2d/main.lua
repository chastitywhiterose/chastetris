
--dimensions for screen
width = 1280;
height = 720;

require "chastetris"

 block_size=height/grid_height;
 print("block size="..block_size);


grid_offset_x=(width-(20/2*block_size))/2;
print(grid_offset_x.."=grid_offsex_x");

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
 
 


end

--this function draws to the screen every frame
function love.draw()
 love.graphics.setColor(1, 0, 0)
 love.graphics.print("Hello World!", 400, 400)
 love.graphics.setColor(0, 1, 0)
 rect.x=100;
 love.graphics.rectangle("fill", rect.x, rect.y, rect.width, rect.height)
 love.graphics.setColor(0, 0, 1)
 rect.x=400;
 --love.graphics.rectangle("fill", rect.x, rect.y, rect.width, rect.height)
 
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
      print("Error. Something here");
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
    love.graphics.setColor(0.5, 1, 1)
    print("nil pixel error");
    print(temp_grid.array[x+y*grid_width]);
    elseif(p=='I') then
    love.graphics.setColor(0, 1, 1)
    else
    love.graphics.setColor(1, 1, 1)
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

  
  end
    
--function to handle what happens when a key is pressed.
function love.keypressed(k)
 print("key="..k)
 if k == 'escape' then
  love.event.quit()
 end
 
 if k == 'right' then
  tetris_move_right();
 end
 
 if k == 'left' then
  tetris_move_left();
 end
 
  if k == 'down' then
  tetris_move_down();
 end
 
end




