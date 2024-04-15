#include <world.h>
#include <stdlib.h>

Game_World* create_world(int seed) {
    Game_World* world = malloc(sizeof(Game_World));
    world->seed = seed;
    world->rooms = malloc(sizeof(Room**) * WORLD_WIDTH);
    for (int i = 0; i < WORLD_WIDTH; i++) {
        world->rooms[i] = calloc(WORLD_HEIGHT, sizeof(Room*));
    }

    return world;
}

Room* generate_room(int seed) {
    Room* room = create_room(10, 10); //temporary for testing
    for (int i = 0; i < room->width; i++) {
        for (int j = 0; j < room->height; j++) {
            room->chunks[i][j].type = EMPTY;
        }
    }

    for (int i = 0; i < room->width; i++) {
        room->chunks[i][0].type = WALL;
        room->chunks[i][room->height - 1].type = WALL;
    }

    for (int i = 0; i < room->height; i++) {
        room->chunks[0][i].type = WALL;
        room->chunks[room->width - 1][i].type = WALL;
    }

    return room;
}

Room* create_room(int width, int height) {
    Room* room = malloc(sizeof(Room));
    room->width = width;
    room->height = height;
    room->chunks = malloc(sizeof(Room_Chunk*) * width);
    for (int i = 0; i < width; i++) {
        room->chunks[i] = malloc(sizeof(Room_Chunk) * height);
    }

    return room;
}