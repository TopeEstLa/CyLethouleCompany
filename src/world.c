#include <world.h>
#include <stdlib.h>
#include <stdio.h>

Game_World *create_world(int seed) {
    Game_World *world = malloc(sizeof(Game_World));
    world->seed = seed;

    world->width = WORLD_WIDTH;
    world->height = WORLD_HEIGHT;

    world->chunk = malloc(sizeof(Chunk *) * WORLD_WIDTH);
    if (world->chunk == NULL) {
        free(world);
        return NULL;
    }

    for (int i = 0; i < WORLD_WIDTH; i++) {
        world->chunk[i] = calloc(WORLD_HEIGHT, sizeof(Chunk));
        if (world->chunk[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(world->chunk[j]);
            }
            free(world->chunk);
            free(world);
            return NULL;
        }
    }

    for (int i = 0; i < WORLD_WIDTH; i++) { //void world
        for (int j = 0; j < WORLD_HEIGHT; j++) {
            world->chunk[i][j].type = VOID;
        }
    }

    world->rooms = malloc(sizeof(Room) * 10);
    world->room_capacity = 10;
    world->room_count = 0;

    return world;
}


void append_world(Game_World *world, int width_to_add, int height_to_add) {
    if (world == NULL) {
        return;
    }

    if (world->chunk == NULL) {
        return;
    }

    if (width_to_add <= 0 || height_to_add <= 0) {
        return;
    }

    int new_width = world->width + width_to_add;
    int new_height = world->height + height_to_add;

    Chunk **new_chunk = realloc(world->chunk, sizeof(Chunk *) * new_width);

    if (new_chunk == NULL) {
        return;
    }

    for (int i = world->width; i < new_width; i++) {
        new_chunk[i] = calloc(new_height, sizeof(Chunk));
        if (new_chunk[i] == NULL) {
            for (int j = world->width; j < i; j++) {
                free(new_chunk[j]);
            }
            free(new_chunk);
            return;
        }
    }

    for (int i = world->width; i < new_width; i++) {
        for (int j = 0; j < new_height; j++) {
            new_chunk[i][j].type = VOID;
        }
    }

    for (int i = 0; i < world->width; ++i) {
        for (int j = world->height; j < new_height; ++j) {
            new_chunk[i][j].type = VOID;
        }
    }

    world->width = new_width;
    world->height = new_height;
    world->chunk = new_chunk;
}

void prepend_world(Game_World* world, int width_to_add, int height_to_add) { //probably not optimal (copying all the chunks)
    if (world == NULL) {
        return;
    }

    if (world->chunk == NULL) {
        return;
    }

    if (width_to_add <= 0 || height_to_add <= 0) {
        return;
    }

    int new_width = world->width + width_to_add;
    int new_height = world->height + height_to_add;

    Chunk** new_chunk = malloc(sizeof(Chunk*) * new_width);

    if (new_chunk == NULL) {
        return;
    }

    for (int i = 0; i < new_width; i++) {
        new_chunk[i] = calloc(new_height, sizeof(Chunk));
        if (new_chunk[i] == NULL) {
            for (int j = world->width; j < i; j++) {
                free(new_chunk[j]);
            }
            free(new_chunk);
            return;
        }
    }

    for (int i = 0; i < world->width; i++) {
        for (int j = 0; j < world->height; ++j) {
            int new_x_index = i + width_to_add;
            int new_y_index = j + height_to_add;
            Chunk chunk = world->chunk[i][j];
            new_chunk[new_x_index][new_y_index] = chunk;
        }
    }

    for (int i = 0; i < width_to_add; i++) {
        for (int j = 0; j < height_to_add; j++) {
            new_chunk[i][j].type = VOID;
        }
    }

    world->width = new_width;
    world->height = new_height;
    world->chunk = new_chunk;
}

void append_room(Game_World *world, Room *room, int x, int y) { //add free on old ?

}

Room *create_room(int width, int height) {
    Room *room = malloc(sizeof(Room));

    room->width = width;
    room->height = height;

    return room;
}