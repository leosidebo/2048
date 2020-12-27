#include "array.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
/* Global variables */

//Global gameboard variable.
Array *board;


/* Internal functions */

static void initialize_board(void) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            array_set(board, i, j, 0);
        }
    }
}

static void add_rand_num(void)
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


static void draw_board(void) {
    // Preliminär version av ritningen
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            printf("%d  ",game_get_square(i,j));
        }
        printf("\n");
    }
}

static void move_right_next_zero(int row, int col)
{
    if (col < 3) {

        if (game_get_square(row,col+1) == 0) {

            array_set(board, row, col+1, game_get_square(row,col));
            array_set(board, row, col, 0);
        }

        move_right_next_zero(row,col+1);
    }
}

static void check_neighbour(int row, int col)
{
    if (col < 3) {

        if (game_get_square(row,col+1) == game_get_square(row,col) && game_get_square(row,col+1) != 0) {

            array_set(board, row, col+1, 2 * game_get_square(row,col));
            array_set(board, row, col, 0);
                
            // This allows for a special case where 4 consecutive 
            // tiles have the same number    
            if (col == 0) {
                check_neighbour(row,col+2);
            }

        } else {
            check_neighbour(row,col+1);
        }
    }
}


/* External functions */


// Start a new game.
void game_new(void)
{
    srand(time(NULL));

    //Create board and zero all the tiles/squares.
    board = array_create(4,4);
    initialize_board();

    add_rand_num();
    add_rand_num();

    draw_board();
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
    //check if empty then move there.
    for (int row = 0 ; row <= 3 ; row++) {
        for (int col = 2 ; col >= 0 ; col--) {
            move_right_next_zero(row,col);
            check_neighbour(row,col);
        }
    }

    printf("\n");
    add_rand_num();
    draw_board();
}

void game_slide_down(void)
{

}

void game_slide_left(void)
{
    for (int i = 0 ; i <= 3 ; i++) {
        for (int j = 3 ; j >= 1 ; j--) {
            //slide_into_dm(i,j);

             if(game_get_square(i,j) == game_get_square(i,j-1) && game_get_square(i,j) != 0)
             {
                 array_set(board , i, j-1, 2 * game_get_square(i,j));
                 array_set(board , i, j, 0);
             } else if (game_get_square(i,j-1) == 0 && game_get_square(i,j) != 0){

                array_set(board , i, j-1, game_get_square(i, j));
                array_set(board , i, j, 0);
            }

        }
    }

    printf("\n");
    add_rand_num();
    draw_board();

}

// Return true if the game is over (2048 reached or no empty squares).
bool game_is_game_over(void)
{
    return 0;
    //Go through the array and if;
    //                                            2048 = !win!
    //                        no "zero" tiles/squares = !lose!
    //                  1 <= "zero" tiles/squares = !continue!
}
