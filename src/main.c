#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <sys/time.h>

#include <world.h>
#include <ncurses_display.h>
#include <terminal_display.h>
#include <world_generator.h>
#include <entities.h>
#include <file_utils.h>
#include <saves.h>
#include <game.h>
#include "printScreen.h"


int main() {
    init_curses();
    srand(time(NULL));
    init_game(rand() % 100, "Player", WARRIOR);

    Game *game = get_game();

    while (1) {
        //clear();
        int ch = getch();

        Entity *player = game->player->entity;

        if (ch != ERR) {
            switch (ch) {
                case KEY_UP:
                    move_entity(player, player->x, player->y - 1);
                    break;
                case KEY_DOWN:
                    move_entity(player, player->x, player->y + 1);
                    break;
                case KEY_LEFT:
                    move_entity(player, player->x - 1, player->y);
                    break;
                case KEY_RIGHT:
                    move_entity(player, player->x + 1, player->y);
                    break;
                default:
                    break;
            }
        }

        curses_all_map(game->world);
    }

    /*while (get_current_scene() != QUITTING) {
        //start_frame(); //useless lol :c (if using timeout());
        handle_input();

        //curses_scene();

        //end_frame();
    }*/

    endwin();

    return 0;
}