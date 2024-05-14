#include <ncurses_display.h>

#include <curses.h>

#include <frame_rate.h>

#include <scene/main_menu.h>
#include <scene/load_menu.h>

Current_Scene current_scene = MAIN_MENU;

void set_current_scene(Current_Scene scene) {
    current_scene = scene;
}

Current_Scene get_current_scene() {
    return current_scene;
}

void init_curses() {
    current_scene = MAIN_MENU;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    timeout(600);

    curs_set(0);
}

void handle_input() {
    switch (current_scene) {
        case MAIN_MENU:
            main_handle_input();
            break;
        case LOAD_MENU:
            load_saves_handle_input();
            break;
        default:
            break;
    }
}

void curses_scene() {
    clear();
    switch (current_scene) {
        case MAIN_MENU:
            main_menu_curses();
            break;
        case LOAD_MENU:
            load_saves_menu_curses();
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

void curses_visited_map(Game_World *world) {
    if (world == NULL) {
        return;
    }

    clear();

    for (int y = 0; y < world->height; y++) {
        for (int x = 0; x < world->width; x++) {
            Room room = get_room(world, x, y);
            if ((room.x != -1 && room.y != -1) && !room.is_visited) {
                printw(" ");
                printw("  ");
                continue;
            }

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
