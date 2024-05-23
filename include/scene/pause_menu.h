#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

/**
 * Reset all fields from the pause menu
 */
void reset_pause_fields();

/**
 * Manage the input from the user
 */
void pause_handle_input();

/**
 * Display the pause menu using ncurses
 */
void pause_menu_curses();


#endif //PAUSE_MENU_H
