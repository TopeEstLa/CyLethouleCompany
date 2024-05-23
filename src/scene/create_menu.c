#include <scene/create_menu.h>

#include <curses.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses_display.h>
#include <game_controller.h>

int choice = 0;
char name[20];
char seed[20];
int class_choice = 0;

void reset_create_fields() {
    choice = 0;
    for (int i = 0; i < 20; ++i) {
        name[i] = '\0';
        seed[i] = '\0';
    }
    class_choice = 0;
}

void create_handle_input() {
    int ch = getch();

    if (ch == ERR) return;

    switch (ch) {
        case 27:
            set_current_scene(MAIN_MENU);
            break;
        case KEY_UP:
            if (choice > 0) choice--;
            break;
        case KEY_DOWN:
            if (choice < 3) choice++;
            break;
        case KEY_BACKSPACE:
        case KEY_DC:
            if (choice == 0) {
                if (strlen(name) > 0) {
                    name[strlen(name) - 1] = '\0';
                }
            } else if (choice == 1) {
                if (strlen(seed) > 0) {
                    seed[strlen(seed) - 1] = '\0';
                }
            }
            break;
        case 10:
            if (choice == 2) {
                class_choice++;
                if (class_choice > 2) class_choice = 0;
            } else if (choice == 3) {
                if (strlen(name) == 0 || strlen(seed) == 0) break;
                if (is_game_loaded()) break;

                char *endptr;
                int seed_int = strtol(seed, &endptr, 10); //convert seed to int "endptr" first non-numeric character

                if (*endptr != '\0') break;

                create_game(seed_int, name, class_choice);
                set_current_scene(GAME);
            }
            break;
        default:
            break;
    }

    switch (choice) {
        case 0:
            if (ch < 'a' || ch > 'z') break;

            if (strlen(name) < 20) {
                name[strlen(name)] = ch;
                name[strlen(name) + 1] = '\0';
            }
            break;
        case 1:
            if (ch < '0' || ch > '9') break;
            if (strlen(seed) < 20) {
                seed[strlen(seed)] = ch;
                seed[strlen(seed) + 1] = '\0';
            }
            break;
    }
}

void create_menu_curses() {
    printw(" _             _    _                    _         _____\n"
           "| |           | |  | |                  | |       / ____|\n"
           "| |       ___ | |_ | |__    ___   _   _ | |  ___ | |       ___   _ __ ___   _ __    __ _  _ __   _   _\n"
           "| |      / _ \\| __|| '_ \\  / _ \\ | | | || | / _ \\| |      / _ \\ | '_ ` _ \\ | '_ \\  / _` || '_ \\ | | | |\n"
           "| |____ |  __/| |_ | | | || (_) || |_| || ||  __/| |____ | (_) || | | | | || |_) || (_| || | | || |_| |\n"
           "|______| \\___| \\__||_| |_| \\___/  \\__,_||_| \\___| \\_____| \\___/ |_| |_| |_|| .__/  \\__,_||_| |_| \\__, |\n"
           "                                                                           | |                    __/ |\n"
           "                                                                           |_|                   |___/\n");

    printw("\n\n");

    for (int i = 0; i < 4; ++i) {
        if (i == choice) {
            attron(A_REVERSE);
        }

        switch (i) {
            case 0:
                printw("Name: %s\n", name);
                break;
            case 1:
                printw("Seed: %s\n", seed);
                break;
            case 2:
                printw("Class: ");

                switch (class_choice) {
                    case 0:
                        printw("ARCHER ");
                        break;
                    case 1:
                        printw("WIZARD ");
                        break;
                    case 2:
                        printw("WARRIOR ");
                        break;
                }

                printw("USE ENTER TO CHANGE\n");
                break;
            case 3:
                printw("\n");
                printw("Start\n");
                break;
        }

        if (i == choice) {
            attroff(A_REVERSE);
        }
    }


}

