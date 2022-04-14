/*chastity tetris*/

/*Part 1: Declaring variables and constants.*/

#define tetris_array_size 0x1000

/*main block structure*/
struct tetris_grid
{
 int array[tetris_array_size];
};

struct tetris_grid main_grid,temp_grid;

int grid_width=10,grid_height=20;

/*main block structure*/
struct tetris_block
{
 int array[16];
 int color;
 int spawn_x,spawn_y; /*where block spawns on entry*/
 int x,y; /*current location of block*/
 int width_used; /*width of block actually used*/
 int id;
};

/*details of main block*/

struct tetris_block main_block,hold_block,temp_block; /*the structures which will be the main,hold,temp block*/

int max_block_width=4; /* the max width of any tetris block*/

int hold_used=0;


int moves=0; /*number of valid moves*/
int moves_tried=0; /*number of attempted moves*/
int last_move_spin=0; /*was the last move a t spin?*/
int last_move_fail; /*did the last move fail?*/
int back_to_back=0;

int score=0;

int empty_color=0x000000;


int lines_cleared=0,lines_cleared_last=0,lines_cleared_total=0;

int block_array_i[]=
{
 0,0,0,0,
 1,1,1,1,
 0,0,0,0,
 0,0,0,0,
};

int block_array_t[]=
{
 0,1,0,0,
 1,1,1,0,
 0,0,0,0,
 0,0,0,0,
};

int block_array_z[]=
{
 1,1,0,0,
 0,1,1,0,
 0,0,0,0,
 0,0,0,0,
};

int block_array_j[]=
{
 1,0,0,0,
 1,1,1,0,
 0,0,0,0,
 0,0,0,0,
};

int block_array_o[]=
{
 1,1,0,0,
 1,1,0,0,
 0,0,0,0,
 0,0,0,0,
};

int block_array_l[]=
{
 0,0,1,0,
 1,1,1,0,
 0,0,0,0,
 0,0,0,0,
};

int block_array_s[]=
{
 0,1,1,0,
 1,1,0,0,
 0,0,0,0,
 0,0,0,0,
};

int block_type=0;

void spawn_block()
{
 int x,y;
 int *p;

 if(block_type==0)
 {
  p=block_array_i;
  main_block.color=0x00FFFF;
  main_block.width_used=4;
  main_block.id='I';
 }

 if(block_type==1)
 {
  p=block_array_t;
  main_block.color=0xFF00FF;
  main_block.width_used=3;
  main_block.id='T';
 }

 if(block_type==2)
 {
  p=block_array_z;
  main_block.color=0xFF0000;
  main_block.width_used=3;
  main_block.id='Z';
 }

 if(block_type==3)
 {
  p=block_array_j;
  main_block.color=0x0000FF;
  main_block.width_used=3;
  main_block.id='J';
 }

 if(block_type==4)
 {
  p=block_array_o;
  main_block.color=0xFFFF00;
  main_block.width_used=2;
  main_block.id='O';
 }

 if(block_type==5)
 {
  p=block_array_l;
  main_block.color=0xFF7F00;
  main_block.width_used=3;
  main_block.id='L';
 }

 if(block_type==6)
 {
  p=block_array_s;
  main_block.color=0x00FF00;
  main_block.width_used=3;
  main_block.id='S';
 }

 /*copy another new block array into the current one*/
 y=0;
 while(y<max_block_width)
 {
  x=0;
  while(x<max_block_width)
  {
   main_block.array[x+y*max_block_width]=p[x+y*max_block_width];
   x+=1;
  }
  y+=1;
 }

 main_block.x=(grid_width-main_block.width_used)/2;
 main_block.y=0;

 main_block.spawn_x=main_block.x;
 main_block.spawn_y=main_block.y;
}

void chastetris_info()
{
 printf("Welcome to the game \"%s\" by Chastity White Rose\n",gamename);
 printf("Email: chastitywhiterose@gmail.com for any questions!\n\n");

 printf("This game was written in the C programming language by Chastity White Rose.\nThe inspiration came from a talk with River Black Rose. There are two versions.\n");
 printf("\"Long Boi\" containing only I blocks and\n\"Chaste Tris\" when all 7 Tetrominoes are present\n");
 printf("And of course this game is heavily inspired by Tetris created by Alexey Pajitnov in 1984\n\n");

 printf("Because I love playing Tetris, I used all my programming skills to make a simple game that I can play with a few features that I wish other Tetris games had.\n");
 printf("There is infinite time to place the blocks because there is no gravity.\n");

 printf("Additionally, you can press the '.' key to save the game at any time and then press ',' to reload to the previously saved state.\n");
 printf("This means my game is the only Tetris game that lets you go back in time to fix mistakes!\n\n");
}





/*Part 2: Functions that modify the block data or Tetris grid itself. */

/*
Functions for each operation that moves the current block.
*/



int pixel_on_grid(int x,int y)
{
 if(x<0){/*printf("Error: Negative X\n");*/return 1;}
 if(y<0){/*printf("Error: Negative Y\n");*/return 1;}
 if(x>=grid_width){/*printf("Error: X too high.\n");*/return 1;}
 if(y>=grid_height){/*printf("Error: Y too high.\n");*/return 1;}
 else{return main_grid.array[x+y*grid_width];}
}

/*
checks whether or not the block collides with anything on the current field
*/
int tetris_check_move()
{
 int x,y;
 moves_tried++; /*move attempted*/

 y=0;
 while(y<max_block_width)
 {
  x=0;
  while(x<max_block_width)
  {
   if(main_block.array[x+y*max_block_width]!=0)
   {
    if( pixel_on_grid(main_block.x+x,main_block.y+y)!=0 )
    {
     /*printf("Error: Block in Way on Move Check.\n");*/
     return 1; /*return failure*/
    }
   }
    x+=1;
  }
  y+=1;
 }

 moves++; /*move successful*/
 return 0;

}


void tetris_clear_screen()
{
 int x,y;
 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   main_grid.array[x+y*grid_width]=empty_color;
   x+=1;
  }
  y+=1;
 }
}


void tetris_clear_lines()
{
 int x,y,xcount,x1,y1;

 lines_cleared=0;

 y=grid_height;
 while(y>0)
 {
  y-=1;

  xcount=0;
  x=0;
  while(x<grid_width)
  {
   if(main_grid.array[x+y*grid_width]!=empty_color){xcount++;}
   x+=1;
  }

  /*printf("row %d xcount %d\n",y,xcount);*/

  if(xcount==grid_width)
  {
   y1=y;

   /*printf("row %d line clear attempt.\n",y);*/

   x1=0;
   while(x1<grid_width)
   {
    main_grid.array[x1+y1*grid_width]=empty_color;

    x1++;
   }
   
  
   lines_cleared++;
  }

 }


 lines_cleared_total+=lines_cleared;

 /*printf("this line clear: %d\n",lines_cleared);
 printf("total lines cleared: %d\n",lines_cleared_total);*/

 /*scoring section*/
 if(lines_cleared==1)
 {
  if(last_move_spin==1)
  {
   if(back_to_back>0){score+=1200;}
   else{score+=800;}
   back_to_back++;
  }
  else
  {
   score+=100;back_to_back=0;
  }
 }
 if(lines_cleared==2)
 {
  if(last_move_spin==1)
  {
   if(back_to_back>0){score+=1800;}
   else{score+=1200;}
   back_to_back++;
   //PlaySound(sound);
  }
  else
  {
   score+=300;back_to_back=0;
  }
 }
 if(lines_cleared==3){score+=500;back_to_back=0;}
 if(lines_cleared==4)
 {
  if(back_to_back>0){score+=1200;}
  else{score+=800;}
  back_to_back++;
  //PlaySound(sound1);
 }

 if(lines_cleared!=0)
 {
  lines_cleared_last=lines_cleared;
  //PlaySound(sound); //play sound whenever a line is cleared
 }

}


/*lines fall down to previously cleared line spaces*/

void tetris_fall_lines()
{
 int x,y,xcount,y1;

/* printf("Time to make lines fall\n");*/

 y=grid_height;
 while(y>0)
 {
  y-=1;

  xcount=0;
  x=0;
  while(x<grid_width)
  {
   if(main_grid.array[x+y*grid_width]!=empty_color){xcount++;}
   x+=1;
  }

  /*printf("row %d xcount %d\n",y,xcount);*/

  if(xcount==0)
  {
   /* printf("row %d is empty\n",y);*/

   /*find first non empty row above empty row*/

   y1=y;
   while(y1>0)
   {
    y1--;
    xcount=0;
    x=0;
    while(x<grid_width)
    {
     if(main_grid.array[x+y1*grid_width]!=empty_color){xcount++;}
     x+=1;
    }
    if(xcount>0)
    {
/*     printf("row %d is not empty. Will copy to row %d.\n",y1,y);*/

     x=0;

     x=0;
     while(x<grid_width)
     {
      main_grid.array[x+y*grid_width]=main_grid.array[x+y1*grid_width];
      main_grid.array[x+y1*grid_width]=empty_color;
      x++;
     }
     break;
    }
   }

  }

 }

}

/*this function controls whether or not the block index changes.*/
void tetris_next_block()
{
 /*optionally increment block type for different block next time.*/
 block_type++;  block_type%=blocks_used;
}


void tetris_set_block()
{
 int x,y;


  /*draw block onto grid at it's current location*/
  y=0;
  while(y<max_block_width)
  {
   x=0;
   while(x<max_block_width)
   {
    if(main_block.array[x+y*max_block_width]!=0)
    {
      main_grid.array[main_block.x+x+(main_block.y+y)*grid_width]=main_block.color; 
    }
    x+=1;
   }
   y+=1;
  }



 tetris_clear_lines();

 if(lines_cleared_last>0){tetris_fall_lines();}


 tetris_next_block();
 spawn_block();


}

/*all things about moving down*/
void tetris_move_down()
{
 /*make backup of block location*/

 temp_block=main_block;


 main_block.y+=1;

 last_move_fail=tetris_check_move();
 if(last_move_fail)
 {
  main_block=temp_block;
  /*printf("Block is finished\n");*/
  tetris_set_block();
  moves++; /*moves normally wouldn't be incremented because move check fails but setting a block is actually a valid move.*/
 }
 else
 {
  //move was successful
 }

 last_move_fail=0; /*because moving down is always a valid operation, the fail variable should be set to 0*/

 fputc(move_id,fp); /*moving down is always a valid move either for setting a block or moving it down*/
}


/*all things about moving up*/
void tetris_move_up()
{
 temp_block=main_block;
 main_block.y-=1;
 last_move_fail=tetris_check_move();
 if(!last_move_fail)
 {
  last_move_spin=0;
  fputc(move_id,fp);
 }
 else
 {
  main_block=temp_block;
 }
}


/*all things about moving right*/
void tetris_move_right()
{
 temp_block=main_block;
 main_block.x+=1;
 last_move_fail=tetris_check_move();
 if(!last_move_fail)
 {
  last_move_spin=0;
  fputc(move_id,fp);
 }
 else
 {
  main_block=temp_block;
 }
}

/*all things about moving left*/
void tetris_move_left()
{
 temp_block=main_block;
 main_block.x-=1;
 last_move_fail=tetris_check_move();
 if(!last_move_fail)
 {
  last_move_spin=0;
  fputc(move_id,fp);
 }
 else
 {
  main_block=temp_block;
 }
}


/*basic (non SRS) rotation system*/
void block_rotate_right_basic()
{
 int x=0,y=0,x1=0,y1=0;

 temp_block=main_block;

 /*copy it from top to bottom to right to left(my own genius rotation trick)*/
 /*same as in the left rotation function but x,y and x1,y1 are swapped in the assignment*/

 x1=main_block.width_used;
 y=0;
 while(y<main_block.width_used)
 {
  x1--;
  y1=0;
  x=0;
  while(x<main_block.width_used)
  {
   main_block.array[x1+y1*max_block_width]=temp_block.array[x+y*max_block_width];
   x+=1;
   y1++;
  }
  y+=1;
 }

 /*if rotation caused collision, restore to the backup before rotate.*/
 last_move_fail=tetris_check_move();
 if(last_move_fail)
 {
  main_block=temp_block;
 }
 else
 {
  last_move_spin=1;
  fputc(move_id,fp);
 }

}


/*basic (non SRS) rotation system*/
void block_rotate_left_basic()
{
 int x=0,y=0,x1=0,y1=0;
temp_block=main_block;

 /*copy it from top to bottom to right to left(my own genius rotation trick)*/
/*same as in the right rotation function but x,y and x1,y1 are swapped in the assignment*/

 x1=main_block.width_used;
 y=0;
 while(y<main_block.width_used)
 {
  x1--;
  y1=0;
  x=0;
  while(x<main_block.width_used)
  {
   main_block.array[x+y*max_block_width]=temp_block.array[x1+y1*max_block_width];
   x+=1;
   y1++;
  }
  y+=1;
 }

 /*if rotation caused collision, restore to the backup before rotate.*/
 last_move_fail=tetris_check_move();
 if(last_move_fail)
 {
  main_block=temp_block;
 }
 else
 {
  last_move_spin=1;
  fputc(move_id,fp);
 }

}



void block_hold()
{
 if(hold_used==0) /*just store block if nothing there*/
 {
  /*printf("hold block used first time.\n");*/
  hold_block=main_block;
  tetris_next_block();
  spawn_block();
  hold_used=1;
 }
 else
 {
  /*printf("Swap with previous hold block.\n");*/
  temp_block=hold_block;
  hold_block=main_block;
  main_block=temp_block;
  main_block.x=main_block.spawn_x;
  main_block.y=main_block.spawn_y;
 }
 fputc(move_id,fp);
}

struct tetris_grid save_grid;
int saved_moves; /*number of valid moves*/
int saved_frame;  /*current animation frame*/
int saved_back_to_back; /*back to back score bonus*/

int move_log_position;

int saved_block_type;

int saved_block_array[16],saved_main_block_width,saved_block_color,saved_block_id,saved_main_block_x,saved_block_y; /*to store all details of main block*/

int saved_hold_block_array[16],saved_hold_block_width,saved_hold_block_color,saved_hold_block_id,saved_hold_main_block_x,saved_hold_block_y; /*to store all details of main block*/
int saved_hold_used;

int saved_score;
int saved_lines_cleared_total;

int save_exist=0;

struct tetris_block save_main_block,save_hold_block;

/*
 a special function which saves all the important data in the game. This allows reloading to a previous position when I make a mistake.
*/
void tetris_save_state()
{
 save_grid=main_grid;

 save_main_block=main_block;
 save_hold_block=hold_block;

 saved_block_type=block_type;

 saved_moves=moves;
 saved_frame=frame;
 saved_hold_used=hold_used;
 saved_score=score;
 saved_lines_cleared_total=lines_cleared_total;
 saved_back_to_back=back_to_back;

 move_log_position=ftell(fp); /*save position in the move log file*/

 printf("Game Saved at move %d\n",moves);
 save_exist=1;
}


/*
 a special function which loads the data previously saved. This allows reloading to a previous position when I make a mistake.
*/
void tetris_load_state()
{

 if(save_exist==0)
 {
  printf("No save exists yet.\n");
  return;
 }

 main_grid=save_grid;

 main_block=save_main_block;
 hold_block=save_hold_block;

 block_type=saved_block_type;

 moves=saved_moves;
 frame=saved_frame;
 hold_used=saved_hold_used;
 score=saved_score;
 lines_cleared_total=saved_lines_cleared_total;
 back_to_back=saved_back_to_back;

 fseek(fp,move_log_position,SEEK_SET);

 printf("Game Loaded at move %d\n",moves);

}




