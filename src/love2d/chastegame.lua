function game_title()

love.graphics.print("Chaste Tris Love2D", font_size*13, font_size*0)

love.graphics.print("Welcome to the Lua port of Chaste Tris. This game has been\nmodified from the C and Raylib version to fit within the Love2D\nframework. It is not a replacement for the original but is\ndesigned to bring the game to Lua users who enjoy Tetris.", font_size*1, font_size*2)

love.graphics.print("Chastity White Rose is the programmer of all code.\nFor questions email her at:\nchastitywhiterose@gmail.com", font_size*1, font_size*8)

love.graphics.print("Press Enter to begin the game.\nand may the horse be with you!", font_size*1, font_size*12)

love.graphics.print("Controls: Z,X,C, WASD/arrow keys", font_size*1, font_size*15)

end

--this keyboard function is called only during the title screen to allow starting the game or exiting
function game_title_keyboard(k)

 if k == 'escape' then
  love.event.quit(); --end the program
 end

 if k == 'return' then
  keyfunc=game_loop_keyboard;
  gamefunc=game_loop;
 end

end


--used to start and restart the game
function game_loop_init()
 --setup the game
 tetris_clear_screen();
 --tetris_grid_print();

 score=0; 
 lines_cleared_total=0;
 back_to_back=0;
 moves=0;
 
 move_id='none';
 
 --optionally delete movelog on game restart
 --move_log={};
 
 block_type=0;
 hold_used=0;
 hold_block.id='none';
 spawn_block();
 
end

function game_loop()

love.graphics.setColor(1, 1, 1);
 love.graphics.print("Chaste Tris Love2D", font_size*1, font_size*0);
 love.graphics.print("Score="..score, font_size*1, font_size*2);
 love.graphics.print("Lines="..lines_cleared_total, font_size*1, font_size*3);
 love.graphics.print("Hold="..hold_block.id, font_size*1, font_size*4);
 love.graphics.print("BTB="..back_to_back, font_size*1, font_size*5);
 love.graphics.print("Moves="..moves, font_size*1, font_size*6);

 love.graphics.print("move id="..move_id, font_size*1, font_size*20);
 love.graphics.print("Key="..last_key, font_size*1, font_size*21);


 
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
 
 --comment this out to disable replay from imovelog
 game_autoplay();

end



--this keyboard function is called during the game loop
function game_loop_keyboard(k)

 --print("key="..k)
 last_key=k;

 if k == 'escape' then

  --begin output movelog writing 
  f=io.open("omovelog.txt","wb");
 
  --write the movelog to a file
  x=0;
  while(x<moves)
  do
  --io.write(move_log[x]);
  f:write(move_log[x]);
  x=x+1;
  end
  
  f:close();
  --end movelog writing
 
  love.event.quit(); --end the program
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





--a function which will play the next thing from the input movelog if it was loaded at the beginning of the program.
function game_autoplay()

 if(moves<log_length)
 then
 
  c=move_log[moves];
  
  if(c==nil)
  then
   print("nil value");
   return; --if a nil value ever happens, we cannot proceed
  end 
  
  move_id=c;
 
  if(c=='W')then tetris_move_up(); end
  if(c=='S')then tetris_move_down(); end
  if(c=='A')then tetris_move_left(); end
  if(c=='D')then tetris_move_right(); end

  if(c=='Z')then block_rotate_left_basic(); end
  if(c=='X')then block_rotate_right_basic(); end
  if(c=='C')then block_hold(); end

 end
 
end
