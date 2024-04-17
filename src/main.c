#include <stdio.h>
#include <stdlib.h>

#include <world.h>
#include <terminal_display.h>




int main() {
    Game_World* world = create_world(1234);

    Room room = create_room(5, 5, 5, 5);
    printf("%d\n", append_room(world, room));

    print_all_map(world);

    Room room2 = create_room(5, 5, 9, 5);
    printf("%d\n", append_room(world, room2));

    Room room3 = create_room(5, 5, 15, 5);
    printf("%d\n", append_room(world, room3));

    print_all_map(world);

    return 0;
}
