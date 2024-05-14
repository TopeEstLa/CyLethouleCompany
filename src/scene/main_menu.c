#include <scene/main_menu.h>

#include <ncurses_display.h>

char *menu_options[] = {
        "Charger une partie",
        "Commencer une nouvelle partie",
        "Tutoriel",
        "Quitter le jeu",
};
int options_count = 4;

int current_choice = 0;

void main_handle_input() {
    int ch = getch();

    if (ch == ERR)
        return;

    switch (ch) {
        case KEY_UP:
            if (current_choice > 0)
                current_choice--;
            break;
        case KEY_DOWN:
            if (current_choice < options_count - 1)
                current_choice++;
            break;
        case 10:
            switch (current_choice) {
                case 0:
                    set_current_scene(LOAD_MENU);
                    break;
                case 1:
                    //set_current_scene(GAME);
                    break;
                case 2:
                    break;
                case 3:
                    set_current_scene(QUITTING);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void main_menu_curses() {
    printw(" _             _    _                    _         _____\n"
           "| |           | |  | |                  | |       / ____|\n"
           "| |       ___ | |_ | |__    ___   _   _ | |  ___ | |       ___   _ __ ___   _ __    __ _  _ __   _   _\n"
           "| |      / _ \\| __|| '_ \\  / _ \\ | | | || | / _ \\| |      / _ \\ | '_ ` _ \\ | '_ \\  / _` || '_ \\ | | | |\n"
           "| |____ |  __/| |_ | | | || (_) || |_| || ||  __/| |____ | (_) || | | | | || |_) || (_| || | | || |_| |\n"
           "|______| \\___| \\__||_| |_| \\___/  \\__,_||_| \\___| \\_____| \\___/ |_| |_| |_|| .__/  \\__,_||_| |_| \\__, |\n"
           "                                                                           | |                    __/ |\n"
           "                                                                           |_|                   |___/\n");

    printw("\n\n");

    for (int i = 0; i < options_count; i++) {
        char a = 'O';
        if (i == current_choice) {
            attron(A_REVERSE);
            a = 'X';
        }

        printw("[%c] %s\n", a, menu_options[i]);
        attroff(A_REVERSE);
    }
}