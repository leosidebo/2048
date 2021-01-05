#include "array.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


/* Global variables */

//Global gameboard variable.
Array *board;


/* Internal functions */



/*
    Checks if any square is equal to the inparamter.
*/
static int check_board_for_square(int square_to_check)
{
    for (int row = 0 ; row < 4 ; row++) {
        for (int col = 0 ; col < 4 ; col++) {

            if (game_get_square(row,col) == square_to_check) {

                return true;
            }
        }
    }

    return false;
}


/*
    Get a random row and col position between 0 and 3.
    Repeat untill the position chosen is empty.

    10% of the time it's a 4 else a 2.
    Add a number to the square.
*/

static void add_rand_num(void)
{
    if (check_board_for_square(0)) {

        int row, col;

        do {

            row = rand() % 4;
            col = rand() % 4;

        } while(game_get_square(row, col) != 0);

        int num_to_add = 2;

        //About a 10% chance of getting a 4.
        if (rand() % 10 == 0) {

            num_to_add = 4;
        }
        //Add the num
        array_set(board, row, col, num_to_add);
    }
}


/*
    Calculates how many spaces a number in a square will take up.
    Returns the number of spaces.
*/

static int draw_board_padding(int row, int col)
{
    int padding = 1;

    int numb = game_get_square(row,col);

    while (numb > 9)
    {
        padding++;
        numb /= 10;
    }
    return padding;
}


/*
    Draws the board.
    If the number to be added is a zero an empty space is printed instead.

    If the number is not a zero, calculate the padding left and right of the number.
    The total number of empty space between the | is 8.

    Calculate the number of spaces to the left and right of the number
    and print them together with the number.

    Print the other half of the board section,
    repeat until the board is completely drawn.
*/

static void draw_board(void)
{
    for (int row = 0; row < 4; row++) {

            int arr[4];
            int padd[4];

            printf("+--------+--------+--------+--------+\n");
            printf("|        |        |        |        |\n|");
            for (int col = 0; col < 4; col++) {

                arr[col] = game_get_square(row,col);

                //If its a zero, nothing in that square is to be printed.
                if (arr[col] == 0) {

                    printf("        |");
                } else {

                    padd[col] = draw_board_padding(row,col);

                    int rem = 8 - padd[col];
                    int right = rem / 2;
                    int left = rem - right;

                    printf("%*s%d%*s|",left,"",arr[col],right,"");
                }
            }

            printf("\n|        |        |        |        |\n");

            //Old draw board
          // printf("+--------+--------+--------+--------+\n");
            //printf("|        |        |        |        |\n");
            //printf("|%*s%d%*s|%*s%d%*s|%*s%d%*s|%*s%d%*s|\n", arr[0], arr[1], arr[2], arr[3]);
            //printf("|        |        |        |        |\n");
        }

    printf("+--------+--------+--------+--------+\n");
}


static void move_next_zero(int row, int col, int edge, int verticalDir, int horizontalDir)
{
    int relevantDirection = horizontalDir;
    int relevantAxis = col;

    if(verticalDir != 0) {
        relevantDirection = verticalDir;
        relevantAxis = row;
    }

    if ((relevantDirection == 1 && relevantAxis < edge) || (relevantDirection == -1 && relevantAxis > edge)) {

        int nextSquare = game_get_square(row + verticalDir, col + horizontalDir);
        int currentSquare = game_get_square(row, col);

        if (nextSquare == 0) {
            array_set(board, row + verticalDir, col + horizontalDir, currentSquare);
            array_set(board, row, col, 0);
            move_next_zero(row + verticalDir, col + horizontalDir, edge, verticalDir, horizontalDir);
        }
    }
}


static void check_neighbour(int row, int col, int edge, int verticalDir, int horizontalDir)
{
    int relevantDirection = horizontalDir;
    int relevantAxis = col;

    if(verticalDir != 0) {
        relevantDirection = verticalDir;
        relevantAxis = row;
    }

    if ((relevantDirection == 1 && relevantAxis < edge) || (relevantDirection == -1 && relevantAxis > edge)) {

        int nextSquare = game_get_square(row + verticalDir, col + horizontalDir);
        int currentSquare = game_get_square(row, col);
        //If both are the same and not a zero
        if (nextSquare == currentSquare && nextSquare != 0) {

            array_set(board, row + verticalDir, col + horizontalDir, 2 * currentSquare);
            array_set(board, row, col, 0);

            // This allows for a special case where 4 consecutive
            // Squares have the same number
            if ((relevantAxis == 0 && edge == 3) || (relevantAxis == 3 && edge == 0)) {
                check_neighbour(row + (verticalDir * 2), col + (horizontalDir * 2), edge, verticalDir, horizontalDir);
            }

        } else {
            check_neighbour(row + verticalDir, col + horizontalDir, edge, verticalDir, horizontalDir);
        }
    }
}


/* External functions */


// Start a new game.
void game_new(void)
{
    srand(time(NULL));

    //Create board and zero all the squares.
    board = array_create(4,4);

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
    int edge = 0;
    int verticalDir = -1;
    int horizontalDir = 0;

    //check if empty then move there.
    for (int col = 0 ; col <= 3 ; col++) {
        for(int row = 0; row <= 3; row++) {
            move_next_zero(row, col, edge, verticalDir, horizontalDir);
        }
        
        check_neighbour(3, col, edge, verticalDir, horizontalDir);
        
        for(int row = 0; row <= 3; row++) {
            // move_next_zero(row, col, edge, verticalDir, horizontalDir);
        }
    }

    add_rand_num();
    draw_board();
}

void game_slide_right(void)
{
    int edge = 3;
    int verticalDir = 0;
    int horizontalDir = 1;

    //check if empty then move there.
    for (int row = 0 ; row <= 3 ; row++) {
        for(int col = 3; col >= 0; col--) {
            move_next_zero(row, col, edge, verticalDir, horizontalDir);
        }

        check_neighbour(row, 0, edge, verticalDir, horizontalDir);

        for(int col = 0; col <= 3; col++) {
            // move_next_zero(row, col, edge, verticalDir, horizontalDir);
        }
    }

    add_rand_num();
    draw_board();
}

void game_slide_down(void)
{
    int edge = 3;
    int verticalDir = 1;
    int horizontalDir = 0;

    //check if empty then move there.
    for (int col = 3 ; col >= 0 ; col--) {
        for(int row = 3; row >= 0; row--) {
            move_next_zero(row, col, edge, verticalDir, horizontalDir);
        }

        check_neighbour(0, col, edge, verticalDir, horizontalDir);

        for(int row = 3; row >= 0; row--) {
            // move_next_zero(row, col, edge, verticalDir, horizontalDir);
        }
    }

    add_rand_num();
    draw_board();
}

void game_slide_left(void)
{
    int edge = 0;
    int verticalDir = 0;
    int horizontalDir = -1;

    //check if empty then move there.
    for (int row = 3 ; row >= 0 ; row--) {
        for(int col = 0; col <= 3; col++) {
            move_next_zero(row, col, edge, verticalDir, horizontalDir);
        }

        check_neighbour(row, 3, edge, verticalDir, horizontalDir);
        
        for(int col = 3; col >= 0; col--) {
            // move_next_zero(row, col, edge, verticalDir, horizontalDir);
        }
    }

    add_rand_num();
    draw_board();
}


/*
    (false, game continues)
    (true, game ends)

    Checks if any square is equal to 2048.
    Returns true if a square is equal to 2048.

    Checks if any square has a square equal to itself next or below.
    Chceks if any square has a pair next to it.
    If either is true, return false.

    Else, return true.
*/

bool game_is_game_over(void)
{

    //Return true if one of the squares are 2048.
    if (check_board_for_square(2048)) {
        return true;
    }

    if (game_get_square(0,0) == 0) {
        return false;
    }

    //Checks all squares except 3,3.
    for (int row = 0 ; row <= 2 ; row++) {
        for (int col = 0 ; col <= 2 ; col++) {

            int current_sq = game_get_square(row,col);

            int next_right_sq = game_get_square(row,col+1);

            int next_below_sq = game_get_square(row+1,col);
            //Checks the square next to it and below it.
            //If its the same or a 0, the game continues.
            if (current_sq == next_right_sq || next_right_sq == 0) {

                return false;
            }
            if (current_sq == next_below_sq || next_below_sq == 0 ) {

                return false;
            }
        }
    }

    //Checks the last square 3,3.
    if (game_get_square(2,3) == game_get_square(3,3) || game_get_square(3,3) == 0) {

        return false;
    }


    return true;
}
