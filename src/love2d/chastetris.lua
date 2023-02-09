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


--hold block object
hold_block={}; --just create empty object here.
hold_block.array={}; --another function will provide its values on first call
hold_block.id='none';


max_block_width=4; --max width of a tetris block is 4
hold_used=0; --whether a block is held for later use

block_type=0;
blocks_used=7;

--additional game variables required
moves=0;
last_move_spin=0;
lines_cleared=0;
lines_cleared_last=0;
lines_cleared_total=0;
score=0;
back_to_back=0;


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
  main_block.width_used=2;
  main_block.array[0+0*max_block_width]=1;
  main_block.array[0+1*max_block_width]=1;
  main_block.array[1+0*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
 end
 
  if(block_type==5)then
  main_block.id='L';
  main_block.width_used=3;
  main_block.array[0+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[2+1*max_block_width]=1;
  main_block.array[2+0*max_block_width]=1;
 end
 
  if(block_type==6)then
  main_block.id='S';
  main_block.width_used=3;
  main_block.array[0+1*max_block_width]=1;
  main_block.array[1+1*max_block_width]=1;
  main_block.array[1+0*max_block_width]=1;
  main_block.array[2+0*max_block_width]=1;
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
  --print("move right succeeded");
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
  --print("move left succeeded");
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
  --print("move up succeeded");
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
  --print("move down succeeded");
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



 tetris_clear_lines();

 if(lines_cleared_last>0)
 then
  tetris_fall_lines();
 end

 tetris_next_block();
 spawn_block();


end





function block_rotate_right_fancy_t()

 if(main_block.id~='T')
 then
  print("Block is not T. No action will be taken.");return;
 end


 temp_block.x=main_block.x;
 temp_block.y=main_block.y;

 main_block.x=temp_block.x-1;
 main_block.y=temp_block.y+1;
 last_move_fail=tetris_check_move();
 if(last_move_fail~=0)
 then
  print("First fancy T Block spin attempt failed.");
  
  main_block.x=temp_block.x-1;
  main_block.y=temp_block.y+2;
  last_move_fail=tetris_check_move();
  if(last_move_fail~=0)
  then
   print("Second fancy T Block spin attempt failed.");
  end

 end

end







function block_rotate_right_basic()

 --copy the block array to a temp block array
 y=0;
 while(y<max_block_width)
 do
  x=0;
  while(x<max_block_width)
  do
   temp_block.array[x+y*max_block_width]=main_block.array[x+y*max_block_width];
   x=x+1;
  end
  y=y+1;
 end

 --copy it from top to bottom to right to left(my own genius rotation trick)
 --same as in the left rotation function but x,y and x1,y1 are swapped in the assignment

 x1=main_block.width_used;
 y=0;
 while(y<main_block.width_used)
 do
  x1=x1-1;
  y1=0;
  x=0;
  while(x<main_block.width_used)
  do
   main_block.array[x1+y1*max_block_width]=temp_block.array[x+y*max_block_width];
   x=x+1;
   y1=y1+1;
  end
  y=y+1;
 end

 --if rotation caused collision, restore to the backup before rotate.
 last_move_fail=tetris_check_move();
 if(last_move_fail~=0)
 then
  --if basic rotation failed, try fancier
  block_rotate_right_fancy_t();
 end
 if(last_move_fail~=0)
 then
 
  --if rotate still failed, revert block to before rotation*/
   y=0;
  while(y<max_block_width)
  do
   x=0;
   while(x<max_block_width)
   do
    main_block.array[x+y*max_block_width]=temp_block.array[x+y*max_block_width];
    x=x+1;
   end
   y=y+1;
  end
  
  --also restore coordinates if fancy spin functions modified them
  main_block.x=temp_block.x;
  main_block.y=temp_block.y;
  
 else
  last_move_spin=1;
 end

end






function block_rotate_left_fancy_t()

 if(main_block.id~='T')
 then
  print("Block is not T. No action will be taken.");return;
 end


 temp_block.x=main_block.x;
 temp_block.y=main_block.y;

 main_block.x=temp_block.x+1;
 main_block.y=temp_block.y+1;
 last_move_fail=tetris_check_move();
 if(last_move_fail~=0)
 then
  print("First fancy T Block spin attempt failed.");
  
  main_block.x=temp_block.x+1;
  main_block.y=temp_block.y+2;
  last_move_fail=tetris_check_move();
  if(last_move_fail~=0)
  then
   print("Second fancy T Block spin attempt failed.");
  end

 end

end




function block_rotate_left_basic()

 --copy the block array to a temp block array
 y=0;
 while(y<max_block_width)
 do
  x=0;
  while(x<max_block_width)
  do
   temp_block.array[x+y*max_block_width]=main_block.array[x+y*max_block_width];
   x=x+1;
  end
  y=y+1;
 end

 --copy it from top to bottom to right to left(my own genius rotation trick)
 --same as in the right rotation function but x,y and x1,y1 are swapped in the assignment

 x1=main_block.width_used;
 y=0;
 while(y<main_block.width_used)
 do
  x1=x1-1;
  y1=0;
  x=0;
  while(x<main_block.width_used)
  do
   main_block.array[x+y*max_block_width]=temp_block.array[x1+y1*max_block_width];
   x=x+1;
   y1=y1+1;
  end
  y=y+1;
 end

 --if rotation caused collision, restore to the backup before rotate.
 last_move_fail=tetris_check_move();
 if(last_move_fail~=0)
 then
  --if basic rotation failed, try fancier
  block_rotate_left_fancy_t();
 end
 if(last_move_fail~=0)
 then
 
  --if rotate still failed, revert block to before rotation*/
   y=0;
  while(y<max_block_width)
  do
   x=0;
   while(x<max_block_width)
   do
    main_block.array[x+y*max_block_width]=temp_block.array[x+y*max_block_width];
    x=x+1;
   end
   y=y+1;
  end
  
  --also restore coordinates if fancy spin functions modified them
  main_block.x=temp_block.x;
  main_block.y=temp_block.y;
  
 else
  last_move_spin=1;
 end

end







--this function has to be longer in Lua because Lua objects are copied by reference rather than value like C structs
function block_hold()

 if(hold_used==0) --just store block if nothing there
 then
  print("hold block used first time.");
  
 --copy the block array to hold block array
  y=0;
  while(y<max_block_width)
  do
   x=0;
   while(x<max_block_width)
   do
    hold_block.array[x+y*max_block_width]=main_block.array[x+y*max_block_width];
    x=x+1;
   end
   y=y+1;
  end
  
  --copy all relevant values
  hold_block.spawn_x=main_block.spawn_x;
  hold_block.spawn_y=main_block.spawn_y;
  hold_block.width_used=main_block.width_used;
  hold_block.id=main_block.id;
  
  tetris_next_block();
  spawn_block();
  hold_used=1;
 
 else
 
  print("Swap with previous hold block.");
  
  --swap the block arrays with my standard x,y double loop
  y=0;
  while(y<max_block_width)
  do
   x=0;
   while(x<max_block_width)
   do
    temp_block.array[x+y*max_block_width]=hold_block.array[x+y*max_block_width];
    hold_block.array[x+y*max_block_width]=main_block.array[x+y*max_block_width];
    main_block.array[x+y*max_block_width]=temp_block.array[x+y*max_block_width];
    x=x+1;
   end
   y=y+1;
  end
  
  temp_block.spawn_x=hold_block.spawn_x;
  temp_block.spawn_y=hold_block.spawn_y;
  temp_block.width_used=hold_block.width_used;
  temp_block.id=hold_block.id;
  
  hold_block.spawn_x=main_block.spawn_x;
  hold_block.spawn_y=main_block.spawn_y;
  hold_block.width_used=main_block.width_used;
  hold_block.id=main_block.id;
  
  main_block.spawn_x=temp_block.spawn_x;
  main_block.spawn_y=temp_block.spawn_y;
  main_block.width_used=temp_block.width_used;
  main_block.id=temp_block.id;

  --set main back to what it's spawn place would be in standard tetris games
  main_block.x=main_block.spawn_x;
  main_block.y=main_block.spawn_y;
 end

end













--the function to clear the lines
function tetris_clear_lines()

 lines_cleared=0;

 y=grid_height;
 while(y>0)
 do
  y=y-1;

  xcount=0;
  x=0;
  while(x<grid_width)
  do
   if(main_grid.array[x+y*grid_width]~=0)
   then
    xcount=xcount+1;
   end
   x=x+1;
  end

  --print("row %d xcount %d\n",y,xcount);

  if(xcount==grid_width)
  then
   y1=y;

   --print("row %d line clear attempt.\n",y);

   x1=0;
   while(x1<grid_width)
   do
    main_grid.array[x1+y1*grid_width]=0;

    x1=x1+1;
   end
   
  
   lines_cleared=lines_cleared+1;
  end

 end


 lines_cleared_total=lines_cleared_total+lines_cleared;

 print("this line clear: %d\n",lines_cleared);
 print("total lines cleared: %d\n",lines_cleared_total);

 --/*scoring section*/
 if(lines_cleared==1)
 then
  if(last_move_spin==1)
  then
   if(back_to_back>0)
   then
    score=score+1200;
   else
   score=score+800;
   end
   back_to_back=back_to_back+1;
  
  else
   score=score+100;back_to_back=0;
  end
 end
 
 if(lines_cleared==2)
 then
  if(last_move_spin==1)
  then
   if(back_to_back>0)
   then
    score=score+1800;
   else
    score=score+1200;
   end
   back_to_back=back_to_back+1;
  else
  
   score=score+300;back_to_back=0;
  end
 end
 
 if(lines_cleared==3)
 then
  if(last_move_spin==1)
  then
   if(back_to_back>0)
   then
    score=score+2400;
   else
    score=score+1600;
   end
   back_to_back=back_to_back+1;
  
  else
   score=score+500;back_to_back=0;
   end
 end
 
 if(lines_cleared==4)
 then
  if(back_to_back>0)
  then
   score=score+1200;
  else
   score=score+800;
  end
  back_to_back=back_to_back+1;
 end

 if(lines_cleared~=0)
 then
  lines_cleared_last=lines_cleared;
 end

end




--lines fall down to previously cleared line spaces

function tetris_fall_lines()

 --print("Time to make lines fall");

 y=grid_height;
 while(y>0)
 do
  y=y-1;

  xcount=0;
  x=0;
  while(x<grid_width)
  do
   if(main_grid.array[x+y*grid_width]~=0)
   then
    xcount=xcount+1;
   end
   x=x+1;
  end

  --print("row "..y.." xcount "..xcount);

  if(xcount==0)
  then
   -- print("row %d is empty\n",y);

   --/*find first non empty row above empty row*/
   y1=y;
   while(y1>0)
   do
    y1=y1-1;
    xcount=0;
    x=0;
    while(x<grid_width)
    do
     if(main_grid.array[x+y1*grid_width]~=0)
     then
      xcount=xcount+1;
     end
     x=x+1;
    end
    if(xcount>0)
    then
     -- printf("row %d is not empty. Will copy to row %d.\n",y1,y);

     x=0;
     while(x<grid_width)
     do
      main_grid.array[x+y*grid_width]=main_grid.array[x+y1*grid_width];
      main_grid.array[x+y1*grid_width]=0;
      x=x+1;
     end
     break;
     
    end
    
   end

  end

 end

end

