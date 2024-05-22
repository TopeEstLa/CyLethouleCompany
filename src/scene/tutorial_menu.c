#include <scene/tutorial_menu.h>

#include <curses.h>

#include <ncurses_display.h>

void tutorial_handle_input() {
    int ch = getch();

    switch (ch) {
        case 27:
            set_current_scene(MAIN_MENU);
            break;
        default:
            break;
    }
}

void tutorial_menu_curses() {
    printw(" _             _    _                    _         _____\n"
           "| |           | |  | |                  | |       / ____|\n"
           "| |       ___ | |_ | |__    ___   _   _ | |  ___ | |       ___   _ __ ___   _ __    __ _  _ __   _   _\n"
           "| |      / _ \\| __|| '_ \\  / _ \\ | | | || | / _ \\| |      / _ \\ | '_ ` _ \\ | '_ \\  / _` || '_ \\ | | | |\n"
           "| |____ |  __/| |_ | | | || (_) || |_| || ||  __/| |____ | (_) || | | | | || |_) || (_| || | | || |_| |\n"
           "|______| \\___| \\__||_| |_| \\___/  \\__,_||_| \\___| \\_____| \\___/ |_| |_| |_|| .__/  \\__,_||_| |_| \\__, |\n"
           "                                                                           | |                    __/ |\n"
           "                                                                           |_|                   |___/\n");
    printw("\n\n");



    attron(A_REVERSE);
    printw("Echap pour retourner au menu principal");
    attroff(A_REVERSE);
}
