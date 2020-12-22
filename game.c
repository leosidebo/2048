#include "array.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
/* Global variables */

//Global gameboard variable.
Array *board;


/* Internal functions */

static int r_num(int max, int min)
{
    return rand() % max + min;
}

/* External functions */


// Start a new game.
void game_new(void)
{
    srand(time(NULL));

    //Create board and zero it.
    board = array_create(4,4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            array_set(board,i,j,0);
        }
    }

    //Get a random position, set a 2 or 4 on the board there.
    int r_row = r_num(3,0), r_col = r_num(3,0);
    array_set(board, r_row, r_col, 4/r_num(2,1));

     r_row = r_num(3,0);
     r_col = r_num(3,0);
     //If the new random position is not empty(Set previously)
     //generate a new one.

     //While loop kanske? För att det inte ska vara på samma POS
     //Är chansen stor nog? hmmm
    if (game_get_square(r_row, r_col) != 0) {
        r_row = r_num(3,0);
        r_col = r_num(3,0);
    }
    //Set the num
    array_set(board, r_row, r_col, 4/r_num(2,1));


    //FOR TESTING ONLY
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
    array_destroy(board);
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
