#ifndef FIGHT_SHOP_CALLBACK_MENU_H
#define FIGHT_SHOP_CALLBACK_MENU_H

/**
 * Set displayed information.
 * @param info
 */
void set_callback(char* info);

/**
 * Handle the input from the user.
 */
void fight_shop_callback_input();

/**
 * Display the shop callback menu using ncurses.
 */
void fight_shop_callback_menu_curses();

#endif //FIGHT_SHOP_CALLBACK_MENU_H
