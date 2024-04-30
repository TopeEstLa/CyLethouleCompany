#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <world.h>
#include <world_generator.h>
#include <terminal_display.h>

int main() {
    srand(time(NULL));
    //Game_World* world = create_world(rand() % 1000);
    Game_World* world = create_world(1000);

    base_generation(world);

    print_all_map(world);


    return 0;
}
