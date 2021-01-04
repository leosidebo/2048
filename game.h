#include <stdbool.h>


/**
 * @defgroup        game_h  OU2
 * @author          Leo S   |   Nils L
 * @author          Leo     |   dv20nls
 * @author          Leo     |   nili0132
 * @date            2021-01-06
 *
 * @brief Contains declarations for game.c
 *
 * Contains declarations for some functions defined in game.c
 *
 *@{
 */


/**
 * @brief Start a new game.
 *
 *
 *
 * @param           -
 * @return          -
 */
void game_new(void);


/**
 * @brief Quit the current game.
 *
 *
 *
 * @param           -
 * @return          -
 */
void game_quit(void);


/**
 * @brief Return the value of the specified piece (0 if empty).
 *
 *
 *
 * @param           -
 * @return          -
 */
int game_get_square(int row, int column);


/**
 * @brief Slide the pieces up
 *
 *
 *
 * @param           -
 * @return          -
 */
void game_slide_up(void);


/**
 * @brief Slide the pieces right
 *
 *
 *
 * @param           -
 * @return          -
 */
void game_slide_right(void);


/**
 * @brief Slide the pieces down
 *
 *
 *
 * @param           -
 * @return          -
 */
void game_slide_down(void);


/**
 * @brief Slide the pieces left
 *
 *
 *
 * @param           -
 * @return          -
 */
void game_slide_left(void);


/**
 * @brief Return true if the game is over (2048 reached or no empty squares).
 *
 *
 *
 * @param           -
 * @return          -
 */
bool game_is_game_over(void);

/**
 * @}
 */
