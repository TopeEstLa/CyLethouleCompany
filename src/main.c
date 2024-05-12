#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include <world.h>
#include <terminal_ncurses_display.h>
#include <terminal_display.h>
#include <world_generator.h>
#include <entities.h>


int main() {
    srand(time(NULL));
    Game_World *world = create_world(rand() % 1000);

    init_entities(world);

    base_generation(world);

    Entity* player = create_entity(PLAYER, NULL, '@');

    add_entity(player, world->rooms[0].x + 3, world->rooms[0].y + 3);

    init_curses();


    int shouldQuit = 0;
    while (shouldQuit == 0) {
        handle_input();
        curses_scene();
    }

    return 0;
}
