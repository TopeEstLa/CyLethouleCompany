#include <scene/game_over_menu.h>

#include <curses.h>

#include <ncurses_display.h>
#include <game_controller.h>

char *game_options[] = {
        "Réapparaitre",
        "Retour au menu principal",
};
int pt_choice = 0;

void reset_game_over_fields() {
    pt_choice = 0;
}

void game_over_input() {
    int ch = getch();

    if (ch == ERR)
        return;

    switch (ch) {
        case KEY_UP:
            if (pt_choice > 0)
                pt_choice--;
            break;
        case KEY_DOWN:
            if (pt_choice < 1)
                pt_choice++;
            break;
        case 10:
            switch (pt_choice) {
                case 0:
                    set_current_scene(GAME);
                    break;
                case 1:
                    unload_game();
                    set_current_scene(MAIN_MENU);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void game_over_menu_curses() {
    printw(" _             _    _                    _         _____\n"
           "| |           | |  | |                  | |       / ____|\n"
           "| |       ___ | |_ | |__    ___   _   _ | |  ___ | |       ___   _ __ ___   _ __    __ _  _ __   _   _\n"
           "| |      / _ \\| __|| '_ \\  / _ \\ | | | || | / _ \\| |      / _ \\ | '_ ` _ \\ | '_ \\  / _` || '_ \\ | | | |\n"
           "| |____ |  __/| |_ | | | || (_) || |_| || ||  __/| |____ | (_) || | | | | || |_) || (_| || | | || |_| |\n"
           "|______| \\___| \\__||_| |_| \\___/  \\__,_||_| \\___| \\_____| \\___/ |_| |_| |_|| .__/  \\__,_||_| |_| \\__, |\n"
           "                                                                           | |                    __/ |\n"
           "                                                                           |_|                   |___/\n");

    printw("\n\n");

    for (int i = 0; i < 2; i++) {
        char a = 'O';
        if (i == pt_choice) {
            attron(A_REVERSE);
            a = 'X';
        }

        printw("[%c] %s\n", a, game_options[i]);
        attroff(A_REVERSE);
    }
}