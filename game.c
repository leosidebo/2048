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

        row = rand() % 4;
        col = rand() % 4;

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

static void move_horizontal_next_zero(int row, int col, int edge, int direction)
{
    if ((direction == 1 && col < edge) || (direction == -1 && col > edge)) {

        if (game_get_square(row,col + direction) == 0) {

            array_set(board, row, col + direction, game_get_square(row,col));
            array_set(board, row, col, 0);
        }

        move_horizontal_next_zero(row, col + direction, edge, direction);
    }
}

static void check_neighbour(int row, int col, int edge, int direction)
{
    if ((direction == 1 && col < edge) || (direction == -1 && col > edge)) {

        if (game_get_square(row,col + direction) == game_get_square(row,col) 
            && game_get_square(row,col + direction) != 0) {

            array_set(board, row, col + direction, 2 * game_get_square(row,col));
            array_set(board, row, col, 0);
                
            // This allows for a special case where 4 consecutive 
            // tiles have the same number    
            if (col == 0) {
                check_neighbour(row,col + (direction * 2), edge, direction);
            }

        } else {
            check_neighbour(row,col + direction, edge, direction);
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
    int edge = 3;
    int direction = 1;

    //check if empty then move there.
    for (int row = 0 ; row <= 3 ; row++) {
        for (int col = 3 ; col >= 0 ; col--) {
            check_neighbour(row, col, edge, direction);
            move_horizontal_next_zero(row, col, edge, direction);
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
    int edge = 0;
    int direction = -1;

    //check if empty then move there.
    for (int row = 3 ; row >= 0 ; row--) {
        for (int col = 3 ; col >= 0 ; col--) {
            check_neighbour(row, col, edge, direction);
            move_horizontal_next_zero(row, col, edge, direction);
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
