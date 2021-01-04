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
 * Creates a new game board and populates it with
 * two randomly positioned squares.
 * Then it draws the board.
 *
 * @param           -
 * @return          -
 */
void game_new(void);


/**
 * @brief Quit the current game.
 *
 * Deallocates all the memory the board has been allocated.
 *
 * @param           -
 * @return          -
 */
void game_quit(void);


/**
 * @brief Return the value of the specified piece (0 if empty).
 *
 * Gets value of the specified square and returns it.
 *
 * @param row       The row position.
 * @param column    The column position.
 * @return
 */
int game_get_square(int row, int column);


/**
 * @brief Slide the pieces up
 *
 * Moves all the squares up and combines matching pairs.
 * Adds a new random square to the board.
 *
 * @param           -
 * @return          -
 */
void game_slide_up(void);


/**
 * @brief Slide the pieces right
 *
 * Moves all the squares rights and combines matching pairs.
 * Adds a new random square to the board. <-- WRITE ABOUT DTAW BOARD? HMM
 *
 * @param           -
 * @return          -
 */
void game_slide_right(void);


/**
 * @brief Slide the pieces down
 *
 * Moves all the squares down and combines matching pairs.
 * Adds a new random square to the board.
 *
 * @param           -
 * @return          -
 */
void game_slide_down(void);


/**
 * @brief Slide the pieces left
 *
 * Moves all the squares to the left and combines matching pairs.
 * Adds a new random square to the board.
 *
 * @param           -
 * @return          -
 */
void game_slide_left(void);


/**
 * @brief Return true if the game is over (2048 reached or no empty squares).
 *
 * Goes through and checks the board if any square is equal to 2048,
 * there is no empty square or there is not any squares next to eachother
 * with the same value. Returns true, else false.
 *
 * @param           -
 * @return          True if the game ends, else false.
 */
bool game_is_game_over(void);

/**
 * @}
 */
