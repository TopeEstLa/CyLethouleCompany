#include <stdio.h>
#include <stdlib.h>

#include <world.h>
#include <terminal_display.h>




int main() {
    Game_World *world = create_world(1234);


    world->chunk[0][0].type = WALL;
    world->chunk[8][9].type = WALL;
    world->chunk[9][9].type = WALL;

    print_all_map(world);

    append_world(world, 1, 1);

    for (int i = 0; i < 50; ++i) {
        printf("\n");
    }
    print_all_map(world);

    prepend_world(world, 1, 1);

    for (int i = 0; i < 50; ++i) {
        printf("\n");
    }
    print_all_map(world);


    return 0;
}
