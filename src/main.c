#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

#include <world.h>
#include <ncurses_display.h>
#include <terminal_display.h>
#include <world_generator.h>
#include <entities.h>
#include <file_utils.h>
#include <saves.h>
#include <frame_rate.h>
#include "printSreen.h"


int main() {
    srand(time(NULL));
    initscr();
    Game_World *world = create_world(rand() % 1000);

    init_entities(world);

    base_generation(world);

    Entity *player = create_entity(PLAYER, NULL, "@");

    add_entity(player, world->rooms[0].x + 3, world->rooms[0].y + 3);

    init_curses();


    while (get_current_scene() != QUITTING) {
        //start_frame(); //useless lol :c (if using timeout());
        handle_input();

        curses_scene();

        //end_frame();
    }

    endwin();

    return 0;
}
