#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <world.h>
#include <terminal_display.h>
#include <world_generator.h>

int main() {
    srand(time(NULL));
    Game_World *world = create_world(rand() % 1000);

    base_generation(world);

    print_all_map(world);

    /**
    int try = 0;
    int last_seed = 0;
    while (1) {
        srand(time(NULL));
        int seed = rand() % 1000;
        seed = try * 1000 + seed;


        if (last_seed == seed) {
            continue;
        }

        Game_World *world = create_world(seed);

        printf("Try: %d\n", try);
        printf("Seed: %d\n", seed);

        //Game_World* world = create_world(1000);

        base_generation(world);

        if (world->room_count != 5) {
            print_all_map(world);
        }

        assert(world->room_count == 5);

        free(world->chunk);
        free(world->rooms);
        free(world);

        printf("Test passed for try: %d\n", try);
        try++;
        last_seed = seed;
    } */

    return 0;
}
