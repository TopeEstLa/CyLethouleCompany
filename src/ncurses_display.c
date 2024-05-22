#include <ncurses_display.h>

#include <curses.h>

#include <scene/main_menu.h>
#include <scene/load_menu.h>
#include <scene/create_menu.h>
#include <scene/pause_menu.h>
#include <scene/time_over_menu.h>
#include <scene/game_over_menu.h>
#include <scene/win_menu.h>
#include <scene/tutorial_menu.h>

#include <scene/game_scene.h>
#include <scene/shop_menu.h>
#include <scene/fight_shop.h>
#include <scene/fight_menu.h>

#include <locale.h>

Current_Scene current_scene = MAIN_MENU;

void set_current_scene(Current_Scene scene) {
    switch (scene) {
        case CREATE_MENU:
            reset_create_fields(); //les class abstraite me manque :cccccccc
            break;
        case PAUSE_MENU:
            reset_pause_fields();
            break;
        case MAIN_MENU:
            reset_main_fields();
            break;
        case LOAD_MENU:
            reset_load_fields();
            break;
        case GAME_OVER:
            reset_game_over_fields();
        case SHOP_MENU:
            reset_shop_fields();
            break;
        case FIGHT_SHOP:
            reset_fight_shop_fields();
            break;
        default:
            break;
    }

    current_scene = scene;

}

Current_Scene get_current_scene() {
    return current_scene;
}

void init_curses() {
    setlocale(LC_ALL, "");
    initscr();

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    timeout(600); //time to wait in MS

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
        case CREATE_MENU:
            create_handle_input();
            break;
        case PAUSE_MENU:
            pause_handle_input();
            break;
        case TUTORIAL_MENU:
            tutorial_handle_input();
            break;
        case GAME:
            handle_game_input();
            break;
        case SHOP_MENU:
            shop_handle_input();
            break;
        case FIGHT_SHOP:
            fight_shop_handle_input();
            break;
        case FIGHT_MENU:
            fight_input();
            break;
        case TIME_OVER:
            time_over_input();
        case GAME_OVER:
            game_over_input();
            break;
        case WIN:
            win_handle_input();
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
        case CREATE_MENU:
            create_menu_curses();
            break;
        case PAUSE_MENU:
            pause_menu_curses();
            break;
        case TUTORIAL_MENU:
            tutorial_menu_curses();
            break;
        case GAME:
            game_scene_curses();
            break;
        case SHOP_MENU:
            shop_menu_curses();
            break;
        case FIGHT_SHOP:
            fight_shop_menu_curses();
            break;
        case FIGHT_MENU:
            fight_menu_curses();
            break;
        case TIME_OVER:
            time_over_menu_curses();
            break;
        case GAME_OVER:
            game_over_menu_curses();
            break;
        case WIN:
            win_menu_curses();
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
                printw("%s", entity->texture);
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
            Room *room = get_room(world, x, y);
            if (room == NULL) {
                printw(" ");
                printw("  ");
                continue;
            }

            if (!room->is_visited) {
                printw(" ");
                printw("  ");
                continue;
            }

            Entity *entity = get_entity(x, y);

            if (entity != NULL) {
                printw("%s", entity->texture);
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
