#include <terminal_ncurses_display.h>

#include <curses.h>

#include <scene/main_menu_scene.h>

Current_Scene current_scene = MAIN_MENU;

void init_curses() {
    current_scene = MAIN_MENU;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    curs_set(0);
}

void handle_input() {
    switch (current_scene) {
        case MAIN_MENU:
            main_handle_input();
            break;
        default:
            break;
    }
}

void curses_scene() {
    clear();
    switch (current_scene) {
        case MAIN_MENU:
            main_curses_scene();
            break;
        default:
            break;
    }

    refresh();
}

void curses_all_map(Game_World *world) {
    if (world == NULL) {
        return;
    }

    clear();

    for (int y = 0; y < world->height; y++) {
        for (int x = 0; x < world->width; x++) {
            Entity *entity = get_entity(x, y);

            if (entity != NULL) {
                printw("%c", entity->texture);
                printw("  ");
                continue;
            }

            switch (world->chunk[x][y]->type) {
                case DOOR:
                    printw("D");
                    printw("  ");
                    break;
                case WALL:
                    printw("|");
                    printw("  ");
                    break;
                case VOID:
                    printw(" ");
                    printw("  ");
                    break;
                case EMPTY:
                    printw(" ");
                    printw("  ");
                    break;
                default:
                    printw("?");
                    printw("  ");
                    break;
            }
        }
        printw("\n");
    }

    refresh();
}
