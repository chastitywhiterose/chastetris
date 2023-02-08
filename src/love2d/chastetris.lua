--grid object
main_grid={};
main_grid.array={};

temp_grid={};
temp_grid.array={};



--dimensions of the grid
grid_width=10;
grid_height=20;

--main block object
main_block={};
main_block.array={};
main_block.color=0;
main_block.spawn_x=0;
main_block.spawn_y=0;
main_block.x=0;
main_block.y=0;
main_block.width_used=4;
main_block.id=0;


--temp block object
temp_block={};
temp_block.array={};
temp_block.color=0;
temp_block.spawn_x=0;
temp_block.spawn_y=0;
temp_block.x=0;
temp_block.y=0;
temp_block.width_used=4;
temp_block.id=0;

max_block_width=4; --max width of a tetris block is 4


block_type=0;
blocks_used=7;

--additional game variables required
moves=0;
lines_cleared=0;
lines_cleared_last=0;
lines_cleared_total=0;


function tetris_clear_block()

 y=0;
 while(y<max_block_width)
 do
  x=0;
  while(x<max_block_width)
  do
   main_block.array[x+y*max_block_width]=0;
   x=x+1;
  end
  y=y+1;
 end

end


function tetris_clear_screen()

 y=0;
 while(y<grid_height)
 do
  x=0;
  while(x<grid_width)
  do
   main_grid.array[x+y*grid_width]=0;
   x=x+1;
  end
  y=y+1;
 end

end



function tetris_grid_print()

 y=0;
 while(y<grid_height)
 do
  x=0;
  while(x<grid_width)
  do
   io.write(tostring(main_grid.array[x+y*grid_width]));
   x=x+1;
  end
  io.write("\n");
  y=y+1;
 end

end



function spawn_block()

 tetris_clear_block();

 if(block_type==0)then
  main_block.id='I';
  main_block.width_used=4;
  main_block.array[0+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[2+1*max_block_width]=1;
  main_block.array[3+1*max_block_width]=1;
 end
 
 if(block_type==1)then
  main_block.id='T';
  main_block.width_used=3;
  main_block.array[0+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[2+1*max_block_width]=1;
  main_block.array[1+0*max_block_width]=1;
 end

 if(block_type==2)then
  main_block.id='Z';
  main_block.width_used=3;
  main_block.array[0+0*max_block_width]=1;
  main_block.array[1+0*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[2+1*max_block_width]=1;
 end

 if(block_type==3)then
  main_block.id='J';
  main_block.width_used=3;
  main_block.array[0+0*max_block_width]=1;
  main_block.array[0+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[2+1*max_block_width]=1;
 end
 
  if(block_type==4)then
  main_block.id='O';
  main_block.width_used=3;
  main_block.array[0+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[2+1*max_block_width]=1;
 end
 
  if(block_type==5)then
  main_block.id='L';
  main_block.width_used=3;
  main_block.array[0+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[2+1*max_block_width]=1;
 end
 
  if(block_type==6)then
  main_block.id='S';
  main_block.width_used=3;
  main_block.array[0+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[2+1*max_block_width]=1;
 end
 
 main_block.x=math.floor((grid_width-main_block.width_used)/2);
 main_block.y=0;

 main_block.spawn_x=main_block.x;
 main_block.spawn_y=main_block.y;

end



function pixel_on_grid(x,y)

 if(x<0) then
  print("Error: Negative X");
  return 1;
 end;
 if(y<0)then
  print("Error: Negative Y");
  return 1;
 end
 if(x>=grid_width)then
  print("Error: X too high.");
  return 1;
 end;
 if(y>=grid_height)then
  print("Error: Y too high.");
  return 1;
 end;
 --if none of the above, return the value at this location
 return main_grid.array[x+y*grid_width];

end





function tetris_check_move()

 y=0;
 while(y<max_block_width)
 do
  x=0;
  while(x<max_block_width)
  do
   if(main_block.array[x+y*max_block_width]~=0)
   then
    if( pixel_on_grid(main_block.x+x,main_block.y+y)~=0 )
    then
     print("Error: Block in Way on Move Check.");
     return 1;
    end
   end
    x=x+1;
  end
  y=y+1;
 end

 moves=moves+1;
 return 0;

end







function tetris_move_right()

 temp_block.x=main_block.x;
 main_block.x=main_block.x+1;
 last_move_fail=tetris_check_move();
 if(last_move_fail==0)
 then
  print("move right succeeded");
  moves=moves+1;
 else
  print("move right error");
  main_block.x=temp_block.x;
 end

end



function tetris_move_left()

 temp_block.x=main_block.x;
 main_block.x=main_block.x-1;
 last_move_fail=tetris_check_move();
 if(last_move_fail==0)
 then
  print("move left succeeded");
  moves=moves+1;
 else
  print("move left error");
  main_block.x=temp_block.x;
 end

end

function tetris_move_up()

 temp_block.y=main_block.y;
 main_block.y=main_block.y-1;
 last_move_fail=tetris_check_move();
 if(last_move_fail==0)
 then
  print("move up succeeded");
 else
  print("move up error");
  main_block.y=temp_block.y;
 end

end


function tetris_move_down()

 temp_block.y=main_block.y;
 main_block.y=main_block.y+1;
 last_move_fail=tetris_check_move();
 if(last_move_fail==0)
 then
  print("move down succeeded");
 else
  --print("move down error");
  main_block.y=temp_block.y;
  tetris_set_block(); --set the block now that hit bottom
  moves=moves+1;
 end

end

--this function controls whether or not the block index changes.
function tetris_next_block()

 --optionally increment block type for different block next time.
 block_type=(block_type+1)%blocks_used;

end







function tetris_set_block()




  --/*draw block onto grid at it's current location*/
  y=0;
  while(y<max_block_width)
  do
   x=0;
   while(x<max_block_width)
   do
    if(main_block.array[x+y*max_block_width]~=0)
    then
      main_grid.array[main_block.x+x+(main_block.y+y)*grid_width]=main_block.id; 
    end
    x=x+1;
   end
   y=y+1;
  end



 --tetris_clear_lines();

 if(lines_cleared_last>0)
 then
  --tetris_fall_lines();
 end

 tetris_next_block();
 spawn_block();


end
