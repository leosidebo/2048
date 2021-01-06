#include "application.h"
#include "game.h"


void print_menu(void) {
    printf("SELECT ACTION\n");
    printf("0: quit\n");
    printf("1: slide up\n");
    printf("2: slide right\n");
    printf("3: slide down\n");
    printf("4: slide left\n");
    printf("? ");
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
        }

    printf("+--------+--------+--------+--------+\n");
}


void app_run(void)
{
    game_new();

    int input = 1;

    do {
        if (input > 0 && input < 5) {
            draw_board();
        }

        print_menu();

        scanf("%d", &input);

        if(input == 1) {

            printf("Sliding up ...\n");

            game_slide_up();
        }
        else if(input == 2) {

            printf("Sliding right ...\n");

            game_slide_right();
        }
        else if(input == 3) {

            printf("Sliding down ...\n");

            game_slide_down();
        }
        else if(input == 4) {

            printf("Sliding left ...\n");

            game_slide_left();
        }
    //If the game is not over and the user has not quit, continue.
    } while(input != 0 && !game_is_game_over());

    printf("Quitting game ...\n");
    draw_board();
    game_quit();
}
