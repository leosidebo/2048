#include "array.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


/* Global variables */


// Global gameboard variable.
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
    Checks if an empty square exists, if not then it does nothing.

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

        // About a 10% chance of getting a 4.
        if (rand() % 10 == 0) {

            num_to_add = 4;
        }
        // Add the num
        array_set(board, row, col, num_to_add);
    }
}


/*
    Move algoritm for both vertical and horizontal movment.

    Get the direction the square are moving in.
    Up and left is 1. Down and right is -1.
    Get the relevantAxis the squares are moving on.
    Col for left and right. Row for up and down.

    If the relevantAxis positon has not gone past the edge it's moving towards.
    Then get the currentSquare and nextSquare and
    check if the nextSquare is empty.
    If it is, swap places with the current and next square.

    Then call the funtion again untill the square is on the edge position
    or the next square is not a zero.
*/

static void move_next_zero(int row, int col, int edge, int verticalDir, int horizontalDir)
{
    // Gets the directon and axis the squares are to move at.
    int relevantDirection = horizontalDir;
    int relevantAxis = col;

    if(verticalDir != 0) {
        relevantDirection = verticalDir;
        relevantAxis = row;
    }
    // Checks if the axis its moving the squares on has not gone past the edge it's moving towards.
    if ((relevantDirection == 1 && relevantAxis < edge) || (relevantDirection == -1 && relevantAxis > edge)) {

        int nextSquare = game_get_square(row + verticalDir, col + horizontalDir);
        int currentSquare = game_get_square(row, col);

        // If the square next to the current is empty then swap places.
        if (nextSquare == 0) {
            array_set(board, row + verticalDir, col + horizontalDir, currentSquare);
            array_set(board, row, col, 0);
            move_next_zero(row + verticalDir, col + horizontalDir, edge, verticalDir, horizontalDir);
        }
    }
}


/*
    Pair checking algoritm for both vertical and horizontal checking.

    Get the direction the square are moving in.
    Up and left is 1. Down and right is -1.
    Get the relevantAxis the squares are moving on.
    Col for left and right. Row for up and down.

    If the relevantAxis positon has not gone past the edge it's moving towards.
    Then get the currentSquare and nextSquare.
    Check if both squares are equal and not a zero.
    If it is, set the nextSquare to itself times two and the currentSquare to 0.

    If there are four consecutive squares with the same number in a row,
    it skips a square with a moddifed function call.

    Then call the funtion again untill all the appropriate square pairs
    have been combined.
*/

static void check_neighbour(int row, int col, int edge, int verticalDir, int horizontalDir)
{
    // Get the directon and axis in which to check the square.
    int relevantDirection = horizontalDir;
    int relevantAxis = col;

    if(verticalDir != 0) {
        relevantDirection = verticalDir;
        relevantAxis = row;
    }
    // Checks if the axis it's checking the squares on has not gone past the edge.
    if ((relevantDirection == 1 && relevantAxis > edge) || (relevantDirection == -1 && relevantAxis < edge)) {

        int nextSquare = game_get_square(row + (verticalDir * -1), col + (horizontalDir * -1));
        int currentSquare = game_get_square(row, col);

        // If both are the same and not a zero
        if (nextSquare == currentSquare && nextSquare != 0) {

            // Set the next square to itself times 2
            // and the current square to 0.
            array_set(board, row + (verticalDir * -1), col + (horizontalDir * -1), 0);
            array_set(board, row, col, 2 * currentSquare);

            // This allows for a special case where 4 consecutive
            // squares have the same number.
            // Then call the function again with a moddifed direction.
            if ((relevantAxis == 0 && edge == 3) || (relevantAxis == 3 && edge == 0)) {
                check_neighbour(row + (verticalDir * -2), col + (horizontalDir * -2), edge, verticalDir, horizontalDir);
            }

        }
        // Call the function again with a changed direction.
        check_neighbour(row + (verticalDir * -1), col + (horizontalDir * -1), edge, verticalDir, horizontalDir);
    }
}


/* External functions */


// Start a new game.
void game_new(void)
{
    srand(time(NULL));

    // Set the board.
    board = array_create(4,4);

    add_rand_num();
    add_rand_num();
}

// Quit the current game.
// Free the allocated memory.
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
    int movementEdge = 0;
    int checkEdge = 3;
    int verticalDir = -1;
    int horizontalDir = 0;

    // check if empty then move there.
    for (int col = 0 ; col <= 3 ; col++) {
        for(int row = 0; row <= 3; row++) {
            move_next_zero(row, col, movementEdge, verticalDir, horizontalDir);
        }
        // Checks there are any pairs next to eachother and combines them.
        check_neighbour(0, col, checkEdge, verticalDir, horizontalDir);

        for(int row = 0; row <= 3; row++) {
            move_next_zero(row, col, movementEdge, verticalDir, horizontalDir);
        }
    }

    add_rand_num();
}

void game_slide_right(void)
{
    int movementEdge = 3;
    int checkEdge = 0;
    int verticalDir = 0;
    int horizontalDir = 1;

    // check if empty then move there.
    for (int row = 0 ; row <= 3 ; row++) {
        for(int col = 3; col >= 0; col--) {
            move_next_zero(row, col, movementEdge, verticalDir, horizontalDir);
        }
        // Checks there are any pairs next to eachother and combines them.
        check_neighbour(row, 3, checkEdge, verticalDir, horizontalDir);

        // Check if empty then move there
        for(int col = 0; col <= 3; col++) {
            move_next_zero(row, col, movementEdge, verticalDir, horizontalDir);
        }
    }

    add_rand_num();
}

void game_slide_down(void)
{
    int movementEdge = 3;
    int checkEdge = 0;
    int verticalDir = 1;
    int horizontalDir = 0;

    // check if empty then move there.
    for (int col = 3 ; col >= 0 ; col--) {
        for(int row = 3; row >= 0; row--) {
            move_next_zero(row, col, movementEdge, verticalDir, horizontalDir);
        }
        // Checks there are any pairs next to eachother and combines them.
        check_neighbour(3, col, checkEdge, verticalDir, horizontalDir);

        for(int row = 3; row >= 0; row--) {
            move_next_zero(row, col, movementEdge, verticalDir, horizontalDir);
        }
    }

    add_rand_num();
}

void game_slide_left(void)
{
    int movementEdge = 0;
    int checkEdge = 3;
    int verticalDir = 0;
    int horizontalDir = -1;

    // check if empty then move there.
    for (int row = 3 ; row >= 0 ; row--) {
        for(int col = 0; col <= 3; col++) {
            move_next_zero(row, col, movementEdge, verticalDir, horizontalDir);
        }
        // Checks there are any pairs next to eachother and combines them.
        check_neighbour(row, 0, checkEdge, verticalDir, horizontalDir);

        for(int col = 3; col >= 0; col--) {
            move_next_zero(row, col, movementEdge, verticalDir, horizontalDir);
        }
    }

    add_rand_num();
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
    // Return true if one of the squares are 2048.
    if (check_board_for_square(2048)) {
        return true;
    }

    if (game_get_square(0,0) == 0) {
        return false;
    }

    // Checks all squares except 3,3.
    for (int row = 0 ; row <= 2 ; row++) {
        for (int col = 0 ; col <= 2 ; col++) {

            int current_sq = game_get_square(row,col);

            int next_right_sq = game_get_square(row,col+1);

            int next_below_sq = game_get_square(row+1,col);

            // Checks the square next to it and below it.
            // If its the same or a 0, the game continues.
            if (current_sq == next_right_sq || next_right_sq == 0) {

                return false;
            }
            if (current_sq == next_below_sq || next_below_sq == 0 ) {

                return false;
            }
        }
    }

    // Checks the last square 3,3.
    if (game_get_square(2,3) == game_get_square(3,3) || game_get_square(3,3) == 0) {

        return false;
    }

    return true;
}
