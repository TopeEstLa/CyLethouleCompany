#ifndef MAIN_MENU_H
#define MAIN_MENU_H

//Les class abstraite me manque :cccccccccc

/**
 * Reset all field from the main menu
 */
void reset_main_fields();

/**
 * Manage the input from the user
 */
void main_handle_input();

/**
 * Display the main menu using ncurses
 */
void main_menu_curses();

#endif //MAIN_MENU_H
