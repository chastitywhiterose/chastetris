/*
This file is for the handling of multiple game states for Chaste Tris
*/

int save_index=0;

/*a big structure to hold all relevant data that should be saved or loaded*/
struct gamesave
{
 int exist;
 int block_type;
 int moves;
 int hold_exist;
 int score;
 int lines;
 int combo;
 int btb;
 int logpos;
 struct tetris_block main_block,hold_block; /* to save the main and hold blocks */
 struct tetris_grid grid;
};

struct gamesave state[10];


/*
 a special function which saves all the important data in the game. This allows reloading to a previous position when I make a mistake.
*/
void save_gamesave()
{
 state[save_index].grid=main_grid;

 state[save_index].main_block=main_block;
 state[save_index].hold_block=hold_block;

 state[save_index].block_type=block_type;

 state[save_index].moves=moves;

 state[save_index].hold_exist=hold_used;
 state[save_index].score=score;
 state[save_index].lines=lines_cleared_total;
 state[save_index].btb=back_to_back;
 state[save_index].combo=combo;

 printf("State %d saved\n",save_index);
 
 state[save_index].exist=1;
}

/*
 a special function which loads the data previously saved. This allows reloading to a previous position when I make a mistake.
*/
void load_gamesave()
{
 if(!state[save_index].exist)
 {
  printf("State %d has not be saved yet! Nothing to load!\n",save_index);
  return;
 }
 
 main_grid=state[save_index].grid;

 main_block=state[save_index].main_block;
 hold_block=state[save_index].hold_block;

 block_type=state[save_index].block_type;

 moves=state[save_index].moves;

 hold_used=state[save_index].hold_exist;
 
 score=state[save_index].score;
 lines_cleared_total=state[save_index].lines;
 back_to_back=state[save_index].btb;
 combo=state[save_index].combo;

 printf("State %d loaded\n",save_index);
}

