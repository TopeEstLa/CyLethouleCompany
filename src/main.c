#include <stdio.h>
#include <stdlib.h>

#include <world.h>
#include <world_generator.h>
#include <terminal_display.h>

int main() {
    Game_World* world = create_world(34584545);

    base_generation(world);

    print_all_map(world);

    return 0;
}
