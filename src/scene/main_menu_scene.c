#include <scene/main_menu_scene.h>

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
            // Enter
            break;
        default:
            break;
    }
}

void main_curses_scene() {
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