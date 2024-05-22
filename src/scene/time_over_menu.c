#include <scene/time_over_menu.h>

#include <curses.h>

#include <ncurses_display.h>
#include <game_controller.h>

void time_over_input() {
    int ch = getch();

    if (ch == ERR) return;

    if (ch == 10) {
        unload_game();
        set_current_scene(MAIN_MENU);
    }
}

void time_over_menu_curses() {
    printw(" _______  ______  __  __  _____    _____          ______   _____   ____   _    _  _       ______\n"
           "|__   __||  ____||  \\/  ||  __ \\  / ____|        |  ____| / ____| / __ \\ | |  | || |     |  ____|\n"
           "   | |   | |__   | \\  / || |__) || (___   ______ | |__   | |     | |  | || |  | || |     | |__\n"
           "   | |   |  __|  | |\\/| ||  ___/  \\___ \\ |______||  __|  | |     | |  | || |  | || |     |  __|\n"
           "   | |   | |____ | |  | || |      ____) |        | |____ | |____ | |__| || |__| || |____ | |____\n"
           "   |_|   |______||_|  |_||_|     |_____/         |______| \\_____| \\____/  \\____/ |______||______|\n"
           "\n"
           "");

    printw("\n\n");

    printw("Vous êtes mort \n");
    printw("Le quota n'a pas été remplis dans les délaie le vaisseau est donc parti sans vous\n");
    printw("\n\n");

    attron(A_REVERSE);
    printw("Retour au menu principal.\n");
    attroff(A_REVERSE);
}
