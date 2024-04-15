#include <stdio.h>
#include <world.h>


void print_map(Game_World *world) {
    for (int i = 0; i < WORLD_HEIGHT; i++) {
        for (int j = 0; j < WORLD_WIDTH; j++) {
            if (world->rooms[j][i] == NULL) continue;

            Room *room = world->rooms[j][i];
            for (int z = 0; z < room->width; z++) {
                Room_Chunk* chunk = room->chunks[z][i];
                printf(chunk->type == WALL ? "#" : "/");
            }
            printf(" ");
        }
        printf("\n");
    }
}

int main() {
    Game_World *world = create_world(1234);

    int origin_x = WORLD_HEIGHT / 2;
    int origin_y = WORLD_WIDTH / 2;

    Room *room = generate_room(1234);
    world->rooms[origin_x][origin_y] = room;
    room->chunks[5][9]->type = DOOR;

    Room *room2 = generate_room(1234);
    world->rooms[origin_x + 1][origin_y] = room2;

    print_map(world);

    return 0;
}
