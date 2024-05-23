#ifndef CREATE_MENU_H
#define CREATE_MENU_H

/**
 * Reset all field from the create menu
 */
void reset_create_fields();

/**
 * Manage the input from the user
 */
void create_handle_input();

/**
 * Display the create menu using ncurses
 */
void create_menu_curses();

#endif //CREATE_MENU_H
