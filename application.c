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

void app_run(void)
{
    game_new();
    int input;

    do {
        print_menu();
        scanf("%d", &input);

        if(input == 1) {
            game_slide_up();
        } 
        else if(input == 2) {
            game_slide_right();
        }
        else if(input == 3) {
            game_slide_down();
        }
        else if(input == 4) {
            game_slide_left();
        }
    } while(input != 0);

    game_quit();
}
