#include <scene/fight_shop_callback_menu.h>

#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <fight.h>
#include <game_controller.h>
#include <ncurses_display.h>

char* callback = NULL;

void set_callback(char* info) {
    if (callback != NULL) {
        free(callback);
    }

    callback = malloc(strlen(info) + 1);
    strcpy(callback, info);
}


void fight_shop_callback_input() {
    int ch = getch();

    if (!is_game_loaded()) return;
    Game_Data *game = get_game_data();

    if (ch == ERR) return;

    if (ch == 10) {
        start_fight(game->player, get_current_monster());
    } else if (ch == 27) {
        if (ENABLE_PAUSE_IN_FIGHT) {
            cancel_fight();
            set_current_scene(PAUSE_MENU);
        }
    }
}

void fight_shop_callback_menu_curses() {
    if (!is_game_loaded()) return;
    if (callback == NULL) return;
    printw(" _______           __      __ ______  _____   _   _  ______\n"
           "|__   __|    /\\    \\ \\    / /|  ____||  __ \\ | \\ | ||  ____|\n"
           "   | |      /  \\    \\ \\  / / | |__   | |__) ||  \\| || |__\n"
           "   | |     / /\\ \\    \\ \\/ /  |  __|  |  _  / | . ` ||  __|\n"
           "   | |    / ____ \\    \\  /   | |____ | | \\ \\ | |\\  || |____\n"
           "   |_|   /_/    \\_\\    \\/    |______||_|  \\_\\|_| \\_||______|\n"
           "\n"
           "");

    printw("\n\n");

    printw("%s\n", callback);

    printw("\n\n");

    attron(A_REVERSE);
    printw("Entrer pour commencer un combat\n");
    attroff(A_REVERSE);
}