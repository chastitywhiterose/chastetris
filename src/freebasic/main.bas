'fbc main.bas && ./main

type tetris_grid
array(200) as integer
end type

dim shared grid_width as integer
dim shared grid_height as integer

dim shared main_grid as tetris_grid
dim shared temp_grid as tetris_grid

grid_width=10
grid_height=20

type tetris_block
x as integer
y as integer
spawn_x as integer
spawn_y as integer
array(16) as integer
width_used as integer
color as integer
id as string
end type

dim shared block_width_max as integer
block_width_max=4

dim shared blocks_used as integer
blocks_used=7

dim shared main_block as tetris_block
dim shared temp_block as tetris_block

dim shared last_move_fail as integer
last_move_fail=0

dim shared last_move_spin as integer
last_move_spin=0

dim shared moves_tried as integer
moves_tried=0

dim shared lines_cleared as integer
lines_cleared=0

dim shared lines_cleared_last as integer
lines_cleared_last=0

dim shared lines_cleared_total as integer
lines_cleared_total=0

dim shared back_to_back as integer
back_to_back=0

dim shared score as integer
score=0


dim shared moves as integer
moves=0

dim shared block_type as integer
block_type=0


#include "fb_chastetris.bi"









block_type=0
block_spawn



'tetris_key_action

dim shared game_run as integer
game_run=1

dim x as integer
dim y as integer

while game_run=1

cls
'block_print main_block

temp_grid=main_grid

'copy the block onto the temp grid
 y=0
 while(y<block_width_max)
  x=0
  while(x<block_width_max)
   if(main_block.array(x+y*block_width_max)<>0) then
    if( pixel_on_grid(main_block.x+x,main_block.y+y)<>0 ) then
     ? "Error: Block in Way on Move Check.\n"
     else
     temp_grid.array(main_block.x+x+(main_block.y+y)*grid_width)=1
    end if
   end if
    x+=1
  wend
  y+=1
 wend
 
 'end of copy section

grid_print(temp_grid)

tetris_key_wait


if key=Chr$(27) then
 print "Escape Pressed. Game will exit"
 game_run=0
end if

if key="x" then
 print "Rotate Right"
 block_rotate_right_basic
end if
if key="z" then
 print "Rotate Left"
 block_rotate_left_basic
end if

if key="w" then
 print "Move Up"
 tetris_move_up
end if

if key="a" then
 print "Move Left"
 tetris_move_left
end if

if key="s" then
 print "Move Down"
 tetris_move_down
end if

if key="d" then
 print "Move Right"
 tetris_move_right
end if

wend

' Keep the window open until the user presses a key
'sleep


'fbc -lang qb main.bas && main
