#include <stdlib.h>
#include <stdio.h>

#include <world.h>
#include <math.h>

Game_World *create_world(int seed) {
    Game_World *world = malloc(sizeof(Game_World));
    world->seed = seed;

    world->width = DEFAULT_WORLD_WIDTH;
    world->height = DEFAULT_WORLD_HEIGHT;

    world->chunk = malloc(sizeof(Chunk *) * DEFAULT_WORLD_WIDTH);
    if (world->chunk == NULL) {
        return world;
    }

    for (int i = 0; i < DEFAULT_WORLD_WIDTH; i++) {
        world->chunk[i] = calloc(DEFAULT_WORLD_HEIGHT, sizeof(Chunk));
        if (world->chunk[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(world->chunk[j]);
            }
            free(world->chunk);
            printf("Failed to allocate memory for chunk\n");
            return world;
        }
    }

    for (int i = 0; i < DEFAULT_WORLD_WIDTH; i++) {
        for (int j = 0; j < DEFAULT_WORLD_HEIGHT; j++) {
            world->chunk[i][j].type = VOID;
        }
    }

    world->rooms = calloc(10, sizeof(Room));
    if (world->rooms == NULL) {
        for (int i = 0; i < DEFAULT_WORLD_WIDTH; i++) {
            free(world->chunk[i]);
        }
        free(world->chunk);
        printf("Failed to allocate memory for rooms\n");
        return world;
    }

    world->room_capacity = 10;
    world->room_count = 0;

    return world;
}


void append_world(Game_World *world, int width_to_add, int height_to_add) {
    if (world == NULL || world->chunk == NULL || width_to_add <= 0 || height_to_add <= 0) {
        return;
    }

    int new_width = world->width + width_to_add;
    int new_height = world->height + height_to_add;

    Chunk **new_chunk = (Chunk **) realloc(world->chunk, sizeof(Chunk *) * new_width);
    if (new_chunk == NULL) {
        printf("Failed to allocate memory for new chunk\n");
        return;
    }

    for (int i = 0; i < world->width; i++) {
        Chunk *new_sub_chunk = realloc(new_chunk[i], sizeof(Chunk) * new_height);
        if (new_sub_chunk == NULL) {
            printf("Failed to allocate memory for new sub chunk\n");
            for (int j = 0; j < i; j++) {
                free(new_chunk[j]);
            }
            free(new_chunk);
            return;
        }
        for (int j = world->height; j < new_height; j++) {
            new_sub_chunk[j].type = VOID;
        }
        new_chunk[i] = new_sub_chunk;
    }

    for (int i = world->width; i < new_width; i++) {
        new_chunk[i] = calloc(new_height, sizeof(Chunk));
        if (new_chunk[i] == NULL) {
            printf("Failed to allocate memory for new chunk\n");
            for (int j = world->width; j < i; j++) {
                free(new_chunk[j]);
            }
            free(new_chunk);
            return;
        }
        for (int j = 0; j < new_height; j++) {
            new_chunk[i][j].type = VOID;
        }
    }

    world->width = new_width;
    world->height = new_height;
    world->chunk = new_chunk;
}

void prepend_world(Game_World *world, int width_to_add, int height_to_add) {
    if (world == NULL || world->chunk == NULL || width_to_add <= 0 || height_to_add <= 0) {
        return;
    }

    int new_width = world->width + width_to_add;
    int new_height = world->height + height_to_add;

    Chunk **new_chunk = (Chunk **) malloc(sizeof(Chunk *) * new_width);
    if (new_chunk == NULL) {
        printf("Failed to allocate memory for new chunk\n");
        return;
    }

    for (int i = 0; i < new_width; i++) {
        new_chunk[i] = calloc(new_height, sizeof(Chunk));
        if (new_chunk[i] == NULL) {
            printf("Failed to allocate memory for new sub chunk\n");
            for (int j = 0; j < i; j++) {
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

    for (int i = 0; i < world->width; i++) {
        free(world->chunk[i]);
    }
    free(world->chunk);

    world->width = new_width;
    world->height = new_height;
    world->chunk = new_chunk;
}

int can_append_room(Game_World *world, Room room) {
    if (world == NULL) {
        return 1;
    }

    if (room.x < 0 || room.y < 0 || room.width <= 0 || room.height <= 0) {
        return 1;
    }

    int width_to_check = room.x + room.width >= world->width ? world->width : room.x + room.width;
    int height_to_check = room.y + room.height >= world->height ? world->height : room.y + room.height;

    for (int i = room.x; i < width_to_check; i++) {
        for (int j = room.y; j < height_to_check; j++) {
            for (int k = 0; k < world->room_count; k++) {
                Room current_room = world->rooms[k];
                if (in_cuboid(current_room.cuboid, i, j)) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int append_room(Game_World *world, Room room) {
    if (world == NULL) {
        return 1;
    }

    if (can_append_room(world, room)) {
        return 1;
    }

    if (world->room_count >= world->room_capacity) {
        world->room_capacity *= 2;
        Room *new_rooms = realloc(world->rooms, sizeof(Room) * world->room_capacity);
        if (!new_rooms) {
            return 1;
        }

        world->rooms = new_rooms;
    }

    int width_to_add = room.x + room.width;
    int height_to_add = room.y + room.height; //I think it to much to add
    if (width_to_add >= world->width || height_to_add >= world->height) {
        append_world(world, width_to_add, height_to_add);
    }

    //Set chunks to room
    for (int i = room.x; i < room.x + room.width; i++) {
        for (int j = room.y; j < room.y + room.height; j++) {
            world->chunk[i][j].type = EMPTY;
        }
    }

    //Set walls
    for (int i = room.x; i < room.x + room.width; ++i) {
        world->chunk[i][room.y].type = WALL;
        world->chunk[i][room.y + room.height - 1].type = WALL;
    }

    for (int i = room.y; i < room.y + room.height; ++i) {
        world->chunk[room.x][i].type = WALL;
        world->chunk[room.x + room.width - 1][i].type = WALL;
    }

    world->rooms[world->room_count] = room;
    world->room_count++;

    return 0;
}

Room create_room(int width, int height, int x, int y) {
    Room room = {0};

    room.width = width;
    room.height = height;
    room.x = x;
    room.y = y;

    Cuboid cuboid = {x, y, x + width, y + height};

    room.cuboid = cuboid;

    return room;
}