
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
  
  gamefunc=game_title;
  --gamefunc=game_loop;


end --end of love.load

--this function draws to the screen every frame
function love.draw()
 
gamefunc(); 
  
  end
    
--function to handle what happens when a key is pressed.
function love.keypressed(k)

 --print("key="..k)
 last_key=k;

 if k == 'return' then
  gamefunc=game_loop;
 end

 if k == 'escape' then
  love.event.quit()
 end
 
  if k == 'up' or k=='w' then
  move_id='W';
  tetris_move_up();
 end
 
 if k == 'left' or k=='a' then
  move_id='A';
  tetris_move_left();
 end

 if k == 'down' or k=='s' then
  move_id='S';
  tetris_move_down();
 end
 
 if k == 'right' or k=='d' then
  move_id='D';
  tetris_move_right();
 end

 
 if k == 'z' then
  move_id='Z';
  block_rotate_left_basic();
 end
 if k == 'x' then
  move_id='X';
  block_rotate_right_basic();
 end
 
 if k == 'c' then
  move_id='C';
  block_hold();
 end
 
 
 if k == 'i' then
  save_gamesave();
 end
 
 if k == 'p' then
  load_gamesave();
 end
 
 if k == '0' then
  save_index=0;
  print("State "..save_index.." selected.");
 end
 if k == '1' then
  save_index=1;
  print("State "..save_index.." selected.");
 end
 if k == '2' then
  save_index=2;
  print("State "..save_index.." selected.");
 end
 if k == '3' then
  save_index=3;
  print("State "..save_index.." selected.");
 end
 if k == '4' then
  save_index=4;
  print("State "..save_index.." selected.");
 end
 if k == '5' then
  save_index=5;
  print("State "..save_index.." selected.");
 end
 if k == '6' then
  save_index=6;
  print("State "..save_index.." selected.");
 end
 if k == '7' then
  save_index=7;
  print("State "..save_index.." selected.");
 end
 if k == '8' then
  save_index=8;
  print("State "..save_index.." selected.");
 end
 if k == '9' then
  save_index=9;
  print("State "..save_index.." selected.");
 end
 
 if k == 'r' then
  game_loop_init();
  print("Game restarted.");
 end
 
 
end




