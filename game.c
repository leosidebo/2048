#include "array.h"
#include <stdlib.h>

/* Global variables */

//Global gameboard variable.
Array *board;


/* Internal functions */

static int random_num(int max, int min)
{
    srand(time(NULL));
    return = rand() & max + min;
}

/* External functions */


// Start a new game.
void game_new(void)
{
    board = array_create(4,4);
    array_set()
}

// Quit the current game.
void game_quit(void)
{
    free(board);
}

// Return the value of the specified piece (0 if empty).
int game_get_square(int row, int column)
{

}

// Slide all pieces up, right, down, or left.
void game_slide_up(void)
{

}
void game_slide_right(void)
{

}
void game_slide_down(void)
{

}
void game_slide_left(void)
{

}

// Return true if the game is over (2048 reached or no empty squares).
bool game_is_game_over(void)
{

}
