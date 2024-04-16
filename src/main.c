#include <stdio.h>
#include <stdlib.h>

#include <world.h>
#include <terminal_display.h>




int main() {
    Game_World world = create_world(1234);

    Room room = create_room(5, 5, 5, 5);
    //append_room(&world, room);

    for (int i = 0; i < 10; ++i) {
        printf("Appending world\n");
        append_world(&world, 10, 10);

        printf("width: %d\n", world.width);
        printf("height: %d\n", world.height);
        printf("world->chunk %p\n", world.chunk);

        //print_all_map(&world);
    }

    print_all_map(&world);

    /**
    prepend_world(world, 1, 1);

    for (int i = 0; i < 50; ++i) {
        printf("\n");
    }
    print_all_map(world); */


    return 0;
}
