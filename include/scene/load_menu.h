#ifndef LOAD_MENU_H
#define LOAD_MENU_H

//Les class abstraite me manque :cccccccccc

/**
 * Reset all field from the load menu
 */
void reset_load_fields();

/**
 * Manage the input from the user
 */
void load_saves_handle_input();

/**
 * Display the load menu using ncurses
 */
void load_saves_menu_curses();

#endif //LOAD_MENU_H
