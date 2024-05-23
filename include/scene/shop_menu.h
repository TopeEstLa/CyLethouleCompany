#ifndef SHOP_MENU_H
#define SHOP_MENU_H

/**
 * Reset all fields from the shop menu
 */
void reset_shop_fields();

/**
 * Manage the input from the user
 */
void shop_handle_input();

/**
 * Display the shop menu using ncurses
 */
void shop_menu_curses();

#endif //SHOP_MENU_H
