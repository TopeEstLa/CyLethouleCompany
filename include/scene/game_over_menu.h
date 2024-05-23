#ifndef GAME_OVER_MENU_H
#define GAME_OVER_MENU_H

/**
 * Reset all the fields of the game over menu.
 */
void reset_game_over_fields();

/**
 * Handle the input from the user.
 */
void game_over_input();

/**
 * Display the game over menu using ncurses.
 */
void game_over_menu_curses();

#endif //GAME_OVER_MENU_H
