save_index=0;

state={};

function gamesave_init()

 x=0;
 while(x<10)
 do
 print("Creating state "..x);
 state[x]={};
 state[x].exist=0; --save states should not exist at beginning of game
 x=x+1;
 end

end




function save_gamesave()

 --state[save_index].grid=main_grid;

 --create empty grid and array for that grid 
 state[save_index].grid={};
 state[save_index].grid.array={};
 
 --copy the entire main grid
 y=0;
 while(y<grid_height)
 do
  x=0;
  while(x<grid_width)
  do
   state[save_index].grid.array[x+y*grid_width]=main_grid.array[x+y*grid_width];
   x=x+1;
  end
  y=y+1;
 end

  --create empty objects for both the main and hold blocks
  state[save_index].main_block={};
  state[save_index].main_block.array={};
  state[save_index].hold_block={};
  state[save_index].hold_block.array={};
  
  --save the block arrays with my standard x,y double loop
  y=0;
  while(y<max_block_width)
  do
   x=0;
   while(x<max_block_width)
   do
    state[save_index].main_block.array[x+y*max_block_width]=main_block.array[x+y*max_block_width];
    state[save_index].hold_block.array[x+y*max_block_width]=hold_block.array[x+y*max_block_width];
    x=x+1;
   end
   y=y+1;
  end
  
  --save additional parts of main and hold blocks
  state[save_index].main_block.x=main_block.x;
  state[save_index].main_block.y=main_block.y;
  state[save_index].main_block.spawn_x=main_block.spawn_x;
  state[save_index].main_block.spawn_y=main_block.spawn_y;
  state[save_index].main_block.width_used=main_block.width_used;
  state[save_index].main_block.id=main_block.id;
  
  state[save_index].hold_block.x=hold_block.x;
  state[save_index].hold_block.y=hold_block.y;
  state[save_index].hold_block.spawn_x=hold_block.spawn_x;
  state[save_index].hold_block.spawn_y=hold_block.spawn_y;
  state[save_index].hold_block.width_used=hold_block.width_used;
  state[save_index].hold_block.id=hold_block.id;


 state[save_index].block_type=block_type;

 state[save_index].moves=moves;

 state[save_index].hold_exist=hold_used;
 state[save_index].score=score;
 state[save_index].lines=lines_cleared_total;
 state[save_index].btb=back_to_back;

 --state[save_index].logpos=ftell(fp); /*save position in the move log file*/
 print("state "..save_index.." saved");
 
 state[save_index].exist=1;

end





function load_gamesave()

 if(state[save_index].exist==0)
 then
  print("state "..save_index.." has not be saved yet! Nothing to load!");
  return;
 end
 
 --copy the entire saved grid back to main grid
 y=0;
 while(y<grid_height)
 do
  x=0;
  while(x<grid_width)
  do
   main_grid.array[x+y*grid_width]=state[save_index].grid.array[x+y*grid_width];
   x=x+1;
  end
  y=y+1;
 end

 --main_block=state[save_index].main_block;
 --hold_block=state[save_index].hold_block;

  --love the block arrays with my standard x,y double loop
  y=0;
  while(y<max_block_width)
  do
   x=0;
   while(x<max_block_width)
   do
    main_block.array[x+y*max_block_width]=state[save_index].main_block.array[x+y*max_block_width];
    hold_block.array[x+y*max_block_width]=state[save_index].hold_block.array[x+y*max_block_width];
    x=x+1;
   end
   y=y+1;
  end


  --load additional parts of main and hold blocks
  main_block.x=state[save_index].main_block.x;
  main_block.y=state[save_index].main_block.y;
  main_block.spawn_x=state[save_index].main_block.spawn_x;
  main_block.spawn_y=state[save_index].main_block.spawn_y;
  main_block.width_used=state[save_index].main_block.width_used;
  main_block.id=state[save_index].main_block.id;
  
  hold_block.x=state[save_index].hold_block.x;
  hold_block.y=state[save_index].hold_block.y;
  hold_block.spawn_x=state[save_index].hold_block.spawn_x;
  hold_block.spawn_y=state[save_index].hold_block.spawn_y;
  hold_block.width_used=state[save_index].hold_block.width_used;
  hold_block.id=state[save_index].hold_block.id;

 block_type=state[save_index].block_type;

 moves=state[save_index].moves;

 hold_used=state[save_index].hold_exist;
 
 score=state[save_index].score;
 lines_cleared_total=state[save_index].lines;
 back_to_back=state[save_index].btb;
 
 --fseek(fp,state[save_index].logpos,SEEK_SET);

 print("state "..save_index.." loaded");

end

