#ifndef FIGHT_SHOP_H
#define FIGHT_SHOP_H

/**
 * Reset all field from the fight shop
 */
void reset_fight_shop_fields();

/**
 * Manage the input from the user
 */
void fight_shop_handle_input();

/**
 * Display the fight shop using ncurses
 */
void fight_shop_menu_curses();

#endif //FIGHT_SHOP_H
