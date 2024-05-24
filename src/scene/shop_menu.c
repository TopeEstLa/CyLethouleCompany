#include <curses.h>

#include <shop.h>
#include <game_controller.h>
#include <ncurses_display.h>

int shop_choice = 0;

void reset_shop_fields() {
    shop_choice = 0;
}

void shop_handle_input() {
    int ch = getch();

    if (ch == ERR) return;

    if (!is_game_loaded()) {
        set_current_scene(MAIN_MENU);
        return;
    }

    Player *player = get_game_data()->player;
    int item_count = player->inventory->index;

    switch (ch) {
        case KEY_UP:
            if (shop_choice > 0) {
                shop_choice--;
            }
            break;
        case KEY_DOWN:
            if (shop_choice < item_count + 1) {
                shop_choice++;
            }
            break;
        case 10:
            if (shop_choice == item_count) {
                sell_inventory(player);
            } else if (shop_choice == item_count + 1) {
                set_current_scene(GAME);
            } else {
                sell_item(player, shop_choice);
            }

            set_current_scene(GAME);
            break;
        case 27:
            set_current_scene(GAME);
            break;
    }
}

void shop_menu_curses() {
    if (!is_game_loaded()) {
        set_current_scene(MAIN_MENU);
        return;
    }

    Player *player = get_game_data()->player;

    printw("__      __ ______  _   _  _____   _____   ______\n"
           "\\ \\    / /|  ____|| \\ | ||  __ \\ |  __ \\ |  ____|\n"
           " \\ \\  / / | |__   |  \\| || |  | || |__) || |__\n"
           "  \\ \\/ /  |  __|  | . ` || |  | ||  _  / |  __|\n"
           "   \\  /   | |____ | |\\  || |__| || | \\ \\ | |____\n"
           "    \\/    |______||_| \\_||_____/ |_|  \\_\\|______|\n"
           "\n"
           "");

    printw("\n\n");

    int item_count = player->inventory->index;
    for (int i = 0; i < item_count + 2; ++i) { //2 for sell all & return
        char sel = 'O';
        if (i == shop_choice) {
            attron(A_REVERSE);
            sel = 'X';
        }

        if (i < item_count) {
            Item_Stack *item_stack = player->inventory->items[i];

            printw("[%c] %s %s : %d$\n", sel, item_stack->texture, item_stack->name, item_stack->price);
        } else {
            if (i == item_count) {
                printw("[%c] Vendre tout (%d$)\n", sel, estimate_inventory_value(player));
            } else {
                printw("[%c] Retour\n", sel);
            }
        }

        if (i == shop_choice) {
            attroff(A_REVERSE);
        }
    }
}