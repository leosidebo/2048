#include "array.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
/* Global variables */

//Global gameboard variable.
Array *board;


/* Internal functions */

static void add_rand_num()
{
    int row, col;
    //Get a random EMPTY tile/square
    do {

         row = rand() % 3;

         col = rand() % 3;

    } while(game_get_square(row, col) != 0);

    int num_to_add = 2;

    //About 10% chance of getting a 4 according to the internet.
    if (rand() % 10 == 0) {

        num_to_add = 4;
    }
    //Add the num
    array_set(board, row, col, num_to_add);
}

/* External functions */


// Start a new game.
void game_new(void)
{
    srand(time(NULL));

    //Create board and zero all the tiles/squares.
    board = array_create(4,4);

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            array_set(board,i,j,0);
        }
    }

    add_rand_num();
    add_rand_num();

    //FOR TESTING ONLY
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            printf("%d  ",game_get_square(i,j));
        }
        printf("\n");
    }
}

// Quit the current game.
//Free the allocated memory.
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
    //Go through the array and if;
    //                                            2048 = !win!
    //                        no "zero" tiles/squares = !lose!
    //                  1 <= "zero" tiles/squares = !continue!
}
