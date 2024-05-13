#include <scene/load_menu_scene.h>

#include <ncurses_display.h>
#include <file_utils.h>
#include <saves.h>

char** saves;
int saves_count = 0;

int current_saves = 0;

void load_saves_handle_input() {
    int ch = getch();

    switch (ch) {
        case KEY_UP:
            if (current_saves > 0)
                current_saves--;
            break;
        case KEY_DOWN:

            int max = 10;
            if (saves_count < 10) {
                max = saves_count;
            }

            if (current_saves < max - 1)
                current_saves++;
            break;
        case 10:
            // Enter
            break;
        case 27:
            set_current_scene(MAIN_MENU);
            break;
        default:
            break;
    }

}

void load_saves_curses_scene() {
    saves = list_files(SAVES_FOLDER, &saves_count);

    printw(" _             _    _                    _         _____\n"
           "| |           | |  | |                  | |       / ____|\n"
           "| |       ___ | |_ | |__    ___   _   _ | |  ___ | |       ___   _ __ ___   _ __    __ _  _ __   _   _\n"
           "| |      / _ \\| __|| '_ \\  / _ \\ | | | || | / _ \\| |      / _ \\ | '_ ` _ \\ | '_ \\  / _` || '_ \\ | | | |\n"
           "| |____ |  __/| |_ | | | || (_) || |_| || ||  __/| |____ | (_) || | | | | || |_) || (_| || | | || |_| |\n"
           "|______| \\___| \\__||_| |_| \\___/  \\__,_||_| \\___| \\_____| \\___/ |_| |_| |_|| .__/  \\__,_||_| |_| \\__, |\n"
           "                                                                           | |                    __/ |\n"
           "                                                                           |_|                   |___/\n");

    printw("\n\n");


    for (int i = 0; i < 10; i++) {
        if (i >= saves_count) {
            break;
        }

        char a = 'O';
        if (i == current_saves) {
            attron(A_REVERSE);
            a = 'X';
        }

        printw("[%c] %s\n", a, saves[i]);
        attroff(A_REVERSE);
    }





}


