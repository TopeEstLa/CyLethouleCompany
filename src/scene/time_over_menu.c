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
    printw(" _             _    _                    _         _____\n"
           "| |           | |  | |                  | |       / ____|\n"
           "| |       ___ | |_ | |__    ___   _   _ | |  ___ | |       ___   _ __ ___   _ __    __ _  _ __   _   _\n"
           "| |      / _ \\| __|| '_ \\  / _ \\ | | | || | / _ \\| |      / _ \\ | '_ ` _ \\ | '_ \\  / _` || '_ \\ | | | |\n"
           "| |____ |  __/| |_ | | | || (_) || |_| || ||  __/| |____ | (_) || | | | | || |_) || (_| || | | || |_| |\n"
           "|______| \\___| \\__||_| |_| \\___/  \\__,_||_| \\___| \\_____| \\___/ |_| |_| |_|| .__/  \\__,_||_| |_| \\__, |\n"
           "                                                                           | |                    __/ |\n"
           "                                                                           |_|                   |___/\n");

    printw("\n\n");

    printw("Vous êtes mort \n");
    printw("Le quota n'a pas été remplis dans les délaie le vaisseau est donc parti sans vous\n");
    printw("\n\n");

    attron(A_REVERSE);
    printw("Retour au menu principal.\n");
    attroff(A_REVERSE);
}
