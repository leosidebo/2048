#include "array.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
/* Global variables */

//Global gameboard variable.
Array *board;


/* Internal functions */

static int random_num(int max, int min)
{
    srand(time(NULL));
    return rand() & max + min;
}

/* External functions */


// Start a new game.
void game_new(void)
{
    board = array_create(4,4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            array_set(board,i,j,0);
        }
    }

    int r_col = random_num(3,0);

    array_set(board, random_num(3,0), random_num(3,0), 4);

    if ( == 0) {
        /* code */
    }
    array_set(board, random_num(3,0), random_num(3,0), 2);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            printf("%d  ",game_get_square(i,j));
        }
        printf("\n");
    }
}

// Quit the current game.
void game_quit(void)
{
    free(board);
}

// Return the value of the specified piece (0 if empty).
int game_get_square(int row, int column)
{
    return array_get(board, row, column);
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
