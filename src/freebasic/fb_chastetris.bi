'include file for tetris related functions


sub block_spawn

dim x as integer
dim y as integer

'start by setting all elements of the array to 0
y=0
while(y<block_width_max)

x=0
while(x<block_width_max)
 main_block.array(x+y*block_width_max)=0
 x+=1:
wend

y+=1
wend

if block_type=0 then
main_block.array(0+1*block_width_max)=1
main_block.array(1+1*block_width_max)=1
main_block.array(2+1*block_width_max)=1
main_block.array(3+1*block_width_max)=1
main_block.id="I"
main_block.color=&H00FFFF
main_block.width_used=4
endif

if block_type=1 then
main_block.array(0+1*block_width_max)=1
main_block.array(1+1*block_width_max)=1
main_block.array(2+1*block_width_max)=1
main_block.array(1+0*block_width_max)=1
main_block.id="T"
main_block.color=&HFF00FF
main_block.width_used=3
endif

if block_type=2 then
main_block.array(0+0*block_width_max)=1
main_block.array(1+0*block_width_max)=1
main_block.array(1+1*block_width_max)=1
main_block.array(2+1*block_width_max)=1
main_block.id="Z"
main_block.color=&HFF0000
main_block.width_used=3
endif

if block_type=3 then
main_block.array(0+0*block_width_max)=1
main_block.array(0+1*block_width_max)=1
main_block.array(1+1*block_width_max)=1
main_block.array(2+1*block_width_max)=1
main_block.id="J"
main_block.color=&H0000FF
main_block.width_used=3
endif

if block_type=4 then
main_block.array(0+0*block_width_max)=1
main_block.array(0+1*block_width_max)=1
main_block.array(1+0*block_width_max)=1
main_block.array(1+1*block_width_max)=1
main_block.id="O"
main_block.color=&HFFFF00
main_block.width_used=2
endif

if block_type=5 then
main_block.array(0+1*block_width_max)=1
main_block.array(1+1*block_width_max)=1
main_block.array(2+1*block_width_max)=1
main_block.array(2+0*block_width_max)=1
main_block.id="L"
main_block.color=&HFF8000
main_block.width_used=3
endif

if block_type=6 then
main_block.array(1+0*block_width_max)=1
main_block.array(2+0*block_width_max)=1
main_block.array(0+1*block_width_max)=1
main_block.array(1+1*block_width_max)=1
main_block.id="S"
main_block.color=&H00FF00
main_block.width_used=3
endif

'set the initial spawn position
 main_block.x=(grid_width-main_block.width_used)/2
 main_block.y=0

 main_block.spawn_x=main_block.x
 main_block.spawn_y=main_block.y

end sub

'this function will print the array as text
sub block_print(block as tetris_block)
dim x as integer
dim y as integer

y=0
while(y<block_width_max)

x=0
while(x<block_width_max)
 print block.array(x+y*block_width_max);
 x+=1:
wend

print

y+=1
wend

'print "block.x =";block.x
'print "block.y =";block.y
'print "block.id =";block.id

end sub

'this function will print the array as text
sub grid_print(grid as tetris_grid)
dim x as integer
dim y as integer

y=0
while(y<grid_height)

x=0
while(x<grid_width)
 print grid.array(x+y*grid_width);
 x+=1
wend

print

y+=1
wend

'print "block.x =";block.x
'print "block.y =";block.y
'print "block.id =";block.id

end sub


'this function will print the array as text
sub grid_clear(grid as tetris_grid)
dim x as integer
dim y as integer

y=0
while(y<grid_height)

x=0
while(x<grid_width)
 grid.array(x+y*grid_width)=0
 x+=1
wend

print

y+=1
wend

end sub


sub tetris_clear_lines

 dim x as integer
 dim y as integer
 dim x1 as integer
 dim y1 as integer
 dim xcount as integer


 lines_cleared=0

 y=grid_height
 while(y>0)
  y-=1

  xcount=0
  x=0
  while(x<grid_width)
   if(main_grid.array(x+y*grid_width)<>0) then
    xcount=xcount+1
   end if
   x+=1
  wend

'  /*printf("row %d xcount %d\n",y,xcount);*/

  if(xcount=grid_width) then
   y1=y

'   /*printf("row %d line clear attempt.\n",y);*/

   x1=0
   while(x1<grid_width)
    main_grid.array(x1+y1*grid_width)=0
    x1=x1+1
   wend
   
  
   lines_cleared=lines_cleared+1
  end if

 wend


 lines_cleared_total+=lines_cleared

' /*printf("this line clear: %d\n",lines_cleared);
' printf("total lines cleared: %d\n",lines_cleared_total);*/

 if lines_cleared=1 then
  if last_move_spin=1 then
   if back_to_back>0 then
    score+=1200
   else
    score+=800
   end if
   back_to_back=back_to_back+1
  end if
  else
   score+=100
   back_to_back=0  
 end if
 
 if lines_cleared=2 then
  if last_move_spin=1 then
   if back_to_back>0 then
    score+=1800
   else
    score+=1200
    back_to_back=back_to_back+1
  end if
  end if
  else
   score+=300
   back_to_back=0
 end if
 
 if lines_cleared=3 then
  score+=500
  back_to_back=0
 end if
  
 if lines_cleared=4 then
  if back_to_back>0 then
   score+=1200
  else
  score+=800
  back_to_back=back_to_back+1
 end if
 end if


 if lines_cleared<>0 then
  lines_cleared_last=lines_cleared
 end if
 
end sub




sub tetris_fall_lines

 dim x as integer
 dim y as integer
 dim x1 as integer
 dim y1 as integer
 dim xcount as integer

 y=grid_height
 while(y>0)
 
  y-=1

  xcount=0
  x=0
  while(x<grid_width)
  
   if main_grid.array(x+y*grid_width)<>0 then
    xcount=xcount+1
   end if
   x+=1
  wend

  if xcount=0 then

   y1=y
   while(y1>0)
   
    y1=y1-1
    xcount=0
    x=0
    while(x<grid_width)
     if main_grid.array(x+y1*grid_width)<>0 then
     xcount=xcount+1
     end if
     x+=1
    wend
    if(xcount>0) then
     x=0
     while(x<grid_width)
      main_grid.array(x+y*grid_width)=main_grid.array(x+y1*grid_width)
      main_grid.array(x+y1*grid_width)=0
      x=x+1
     wend
     exit while
    end if
   wend

  end if

 wend

end sub


sub tetris_next_block
 block_type=block_type+1
 block_type=block_type mod blocks_used
end sub


sub tetris_set_block
 dim x as integer
 dim y as integer

  y=0
  while(y<block_width_max)
  x=0
  while(x<block_width_max)
   if main_block.array(x+y*block_width_max)<>0 then
     main_grid.array(main_block.x+x+(main_block.y+y)*grid_width)=1 
   end if
   x+=1
  wend
  y+=1
 wend

 tetris_clear_lines()

 if lines_cleared_last>0 then
  tetris_fall_lines()
 end if


 tetris_next_block
 block_spawn

end sub


function pixel_on_grid(x as integer,y as integer) as integer
 if x<0 then
  ? "Error: Negative X\n"
  return 1
 end if
 if y<0 then
  ? "Error: Negative Y\n"
  return 1
  end if
 if x>=grid_width then
  ? "Error: X too high.\n"
  return 1
 end if
 if y>=grid_height then
  ? "Error: Y too high.\n"
  return 1
  end if
 return main_grid.array(x+y*grid_width)
end function



function tetris_check_move() as integer
 dim x as integer
 dim y as integer
 moves_tried=moves_tried+1

 y=0
 while(y<block_width_max)
 
  x=0
  while(x<block_width_max)
   if(main_block.array(x+y*block_width_max)<>0) then
    if( pixel_on_grid(main_block.x+x,main_block.y+y)<>0 ) then
     ? "Error: Block in Way on Move Check.\n"
     return 1
    end if
   end if
    x+=1
  wend
  y+=1
 wend

 moves=moves+1
 return 0

end function



'basic (non SRS) rotation system
sub block_rotate_right_basic
 dim x as integer
 dim y as integer
 dim x1 as integer
 dim y1 as integer

 temp_block=main_block

 x1=main_block.width_used
 y=0
 while(y<main_block.width_used)
 
  x1=x1-1
  y1=0
  x=0
  while(x<main_block.width_used)
   main_block.array(x1+y1*block_width_max)=temp_block.array(x+y*block_width_max)
   x=x+1
   y1=y1+1
  wend
  y=y+1
 wend

 last_move_fail=tetris_check_move()
 if(last_move_fail=1) then
  main_block=temp_block
 else
  last_move_spin=1
 end if

end sub





'basic (non SRS) rotation system
sub block_rotate_left_basic
 dim x as integer
 dim y as integer
 dim x1 as integer
 dim y1 as integer

 temp_block=main_block

 x1=main_block.width_used
 y=0
 while(y<main_block.width_used)
 
  x1=x1-1
  y1=0
  x=0
  while(x<main_block.width_used)
   main_block.array(x+y*block_width_max)=temp_block.array(x1+y1*block_width_max)
   x=x+1
   y1=y1+1
  wend
  y=y+1
 wend

 last_move_fail=tetris_check_move()
 if(last_move_fail=1) then
  main_block=temp_block
 else
  last_move_spin=1
 end if

end sub


'code to select extended key based on dialect
#if __FB_LANG__ = "qb"
#define EXTCHAR Chr$(0)
#else
#define EXTCHAR Chr(255)
#endif

'this function is of extreme importance
'it waits until a key is pressed
dim shared key as string

sub tetris_key_wait

key=Inkey$

while key=""

key=Inkey$

'print "waiting for keypress"

wend

'print "key was entered"

end sub

'this function does different actions based on which key was pressed after the above function was called
sub tetris_key_action
 Select Case key
 Case "A" To "Z", "a" To "z": Print "Letter: " & key
 Case "1" To "9":             Print "Number: " & key
 Case Chr$(32): Print "Space"
 Case Chr$(13): Print "Enter"
 Case Chr$(27): Print "Escape"
 Case Chr$(9): Print "Tab"
 Case Chr$(8): Print "Backspace"
 Case Chr$(32) To Chr$(127)
 Print "Printable character: " & key
 Case EXTCHAR & "G": Print "Up Left / Home"
 Case EXTCHAR & "H": Print "Up"
 Case EXTCHAR & "I": Print "Up Right / PgUp"
 Case EXTCHAR & "K": Print "Left"
 Case EXTCHAR & "L": Print "Center"
 Case EXTCHAR & "M": Print "Right"
 Case EXTCHAR & "O": Print "Down Left / End"
 Case EXTCHAR & "P": Print "Down"
 Case EXTCHAR & "Q": Print "Down Right / PgDn"
 Case EXTCHAR & "R": Print "Insert"
 Case EXTCHAR & "S": Print "Delete"


        Case EXTCHAR & "k": Print "Close window / Alt-F4"

        Case EXTCHAR & Chr$(59) To EXTCHAR & Chr$(68)
            Print "Function key: F" & Asc(key, 2) - 58

        Case EXTCHAR & Chr$(133) To EXTCHAR & Chr$(134)
            Print "Function key: F" & Asc(key, 2) - 122

        Case Else
            If Len(key) = 2 Then
                Print Using "Extended character: chr$(###, ###)"; Asc(key, 1); Asc(key, 2)
            ElseIf Len(key) = 1 Then
                Print Using "Character chr$(###)"; Asc(key)
            End If

    End Select

end sub




sub tetris_move_down
 temp_block=main_block
 main_block.y+=1
 last_move_fail=tetris_check_move
 if(last_move_fail<>0) then
  main_block=temp_block
  tetris_set_block
  moves=moves+1
 end if
 last_move_fail=0
end sub


sub tetris_move_up
 temp_block=main_block
 main_block.y-=1
 last_move_fail=tetris_check_move
 if(last_move_fail=0) then
  last_move_spin=0
 else
  main_block=temp_block
 end if
end sub

sub tetris_move_right
 temp_block=main_block
 main_block.x+=1
 last_move_fail=tetris_check_move
 if(last_move_fail=0) then
  last_move_spin=0
 else
  main_block=temp_block
 end if
end sub

sub tetris_move_left
 temp_block=main_block
 main_block.x-=1
 last_move_fail=tetris_check_move
 if(last_move_fail=0) then
  last_move_spin=0
 else
  main_block=temp_block
 end if
end sub