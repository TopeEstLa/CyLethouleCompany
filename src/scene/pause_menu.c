#include <scene/pause_menu.h>

#include <ncurses_display.h>

#include <curses.h>


char *pause_options[] = {
        "Reprendre la partie",
        "Savegarder la partie",
        "Retourner au menu principal",
};
int pause_count = 3;

int pause_choice = 0;

void pause_handle_input() {
    int ch = getch();

    if (ch == ERR)
        return;

    switch (ch) {
        case KEY_UP:
            if (pause_choice > 0)
                pause_choice--;
            break;
        case KEY_DOWN:
            if (pause_choice < pause_count - 1)
                pause_choice++;
            break;
        case 10:
            switch (pause_choice) {
                case 0:
                    set_current_scene(GAME);
                    break;
                case 1:

                    break;
                case 2:
                    //unload game
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void pause_menu_curses() {
    printw(" _____             _    _   _____  ______\n"
           "|  __ \\     /\\    | |  | | / ____||  ____|\n"
           "| |__) |   /  \\   | |  | || (___  | |__\n"
           "|  ___/   / /\\ \\  | |  | | \\___ \\ |  __|\n"
           "| |      / ____ \\ | |__| | ____) || |____\n"
           "|_|     /_/    \\_\\ \\____/ |_____/ |______|\n"
           "\n"
           "");

    printw("\n\n");

    for (int i = 0; i < pause_count; i++) {
        char a = 'O';
        if (i == pause_choice) {
            attron(A_REVERSE);
            a = 'X';
        }

        printw("[%c] %s\n", a, pause_options[i]);
        attroff(A_REVERSE);
    }
}
