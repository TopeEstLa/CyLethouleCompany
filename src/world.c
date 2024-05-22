#include <stdlib.h>
#include <stdio.h>

#include <world.h>
#include <entities.h>
#include <maths.h>
#include <constant.h>

Chunk *create_empty_chunk() {
    Chunk *chunk = malloc(sizeof(Chunk));
    if (chunk == NULL) {
        return NULL;
    }

    chunk->type = VOID;
    chunk->direction = NONE;

    return chunk;
}


Game_World *create_world(int seed) {
    Game_World *world = malloc(sizeof(Game_World));
    world->seed = seed;

    world->width = DEFAULT_WORLD_WIDTH;
    world->height = DEFAULT_WORLD_HEIGHT;

    world->chunk = malloc(sizeof(Chunk **) * DEFAULT_WORLD_WIDTH);
    if (world->chunk == NULL) {
        free(world);
        return NULL;
    }

    for (int i = 0; i < DEFAULT_WORLD_WIDTH; i++) {
        world->chunk[i] = calloc(DEFAULT_WORLD_HEIGHT, sizeof(Chunk *));
        if (world->chunk[i] == NULL) {
            printf("Failed to allocate memory for chunk\n");

            free(world->chunk);
            free(world);

            return NULL;
        }
    }

    for (int i = 0; i < DEFAULT_WORLD_WIDTH; i++) {
        for (int j = 0; j < DEFAULT_WORLD_HEIGHT; j++) {
            world->chunk[i][j] = create_empty_chunk();
            if (world->chunk[i][j] == NULL) {
                printf("Failed to allocate memory for chunk\n");

                for (int k = 0; k < DEFAULT_WORLD_WIDTH; ++k) {
                    free(world->chunk[k]);
                }

                free(world->chunk);
                free(world);

                return NULL;
            }
        }
    }

    if (MAX_ROOM == -1) {
        world->rooms = calloc(10, sizeof(Room));
    } else {
        world->rooms = calloc(MAX_ROOM, sizeof(Room));
    }
    if (world->rooms == NULL) {
        printf("Failed to allocate memory for rooms\n");
        for (int i = 0; i < DEFAULT_WORLD_WIDTH; i++) {
            free(world->chunk[i]);
        }
        free(world->chunk);
        free(world);

        return NULL;
    }

    if (MAX_ROOM == -1) {
        world->room_capacity = 10;
    } else {
        world->room_capacity = MAX_ROOM;
    }

    world->room_count = 0;
    world->prepared_rooms_count = 0;

    return world;
}

Game_World *create_world_sized(int seed, int width, int height) {
    Game_World *world = malloc(sizeof(Game_World));
    world->seed = seed;

    world->width = width;
    world->height = height;

    world->chunk = malloc(sizeof(Chunk **) * width);
    if (world->chunk == NULL) {
        printf("Failed to allocate memory for chunk\n");
        free(world);
        return NULL;
    }

    for (int i = 0; i < width; i++) {
        world->chunk[i] = calloc(height, sizeof(Chunk *));
        if (world->chunk[i] == NULL) {
            printf("Failed to allocate memory for chunk\n");

            free(world->chunk);
            free(world);

            return NULL;
        }
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            world->chunk[i][j] = create_empty_chunk();
            if (world->chunk[i][j] == NULL) {
                printf("Failed to allocate memory for chunk\n");

                for (int k = 0; k < width; ++k) {
                    free(world->chunk[k]);
                }

                free(world->chunk);
                free(world);

                return NULL;
            }
        }
    }

    world->rooms = calloc(10, sizeof(Room));
    if (world->rooms == NULL) {
        printf("Failed to allocate memory for rooms\n");

        for (int i = 0; i < width; i++) {
            free(world->chunk[i]);
        }
        free(world->chunk);
        free(world);

        return NULL;
    }

    world->room_capacity = 10;
    world->room_count = 0;
    world->prepared_rooms_count = 0;

 //   world->monsters = init_world_monster();

    return world;
}

Chunk *get_chunk(Game_World *world, int x, int y) {
    if (world == NULL || world->chunk == NULL) {
        return NULL;
    }

    if (x < 0 || x >= world->width || y < 0 || y >= world->height) {
        return NULL;
    }

    Chunk *chunk = world->chunk[x][y];

    if (chunk == NULL) {
        return NULL;
    }

    return chunk;
}


void append_world(Game_World *world, int width_to_add, int height_to_add) {
    if (world == NULL || world->chunk == NULL || width_to_add <= 0 || height_to_add <= 0) {
        return;
    }

    int new_width = world->width + width_to_add;
    int new_height = world->height + height_to_add;

    Chunk ***new_chunk = (Chunk ***) realloc(world->chunk, sizeof(Chunk **) * new_width);
    if (new_chunk == NULL) {
        printf("Failed to allocate memory for new chunk\n");
        return;
    }

    for (int i = 0; i < world->width; i++) {
        Chunk **new_sub_chunk = realloc(new_chunk[i], sizeof(Chunk *) * new_height);
        if (new_sub_chunk == NULL) {
            printf("Failed to allocate memory for new sub chunk\n");
            free(new_chunk);

            return;
        }
        for (int j = world->height; j < new_height; j++) {
            new_sub_chunk[j] = create_empty_chunk();

            if (new_sub_chunk[j] == NULL) {
                printf("Failed to allocate memory for new sub chunk\n");

                free(new_sub_chunk);
                free(new_chunk);
                return;
            }

        }
        new_chunk[i] = new_sub_chunk;
    }

    for (int i = world->width; i < new_width; i++) {
        new_chunk[i] = calloc(new_height, sizeof(Chunk *));
        if (new_chunk[i] == NULL) {
            printf("Failed to allocate memory for new chunk\n");

            free(new_chunk);
            return;
        }

        for (int j = 0; j < new_height; j++) {
            new_chunk[i][j] = create_empty_chunk();

            if (new_chunk[i][j] == NULL) {
                printf("Failed to allocate memory for new sub chunk\n");

                free(new_chunk);

                return;
            }
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

    Chunk ***new_chunk = (Chunk ***) malloc(sizeof(Chunk **) * new_width);
    if (new_chunk == NULL) {
        printf("Failed to allocate memory for new chunk\n");
        free(new_chunk);
        return;
    }

    for (int i = 0; i < new_width; i++) {
        new_chunk[i] = calloc(new_height, sizeof(Chunk *));
        if (new_chunk[i] == NULL) {
            printf("Failed to allocate memory for new sub chunk\n");
            free(new_chunk);
            return;
        }
    }

    for (int i = 0; i < new_width; i++) {
        for (int j = 0; j < new_height; j++) {
            new_chunk[i][j] = create_empty_chunk();
            if (new_chunk[i][j] == NULL) {
                printf("Failed to allocate memory for new sub chunk\n");
                free(new_chunk);
                return;
            }
        }
    }

    for (int i = 0; i < world->width; i++) {
        for (int j = 0; j < world->height; ++j) {
            int new_x_index = i + width_to_add;
            int new_y_index = j + height_to_add;
            Chunk *chunk = world->chunk[i][j];
            new_chunk[new_x_index][new_y_index] = chunk;
        }
    }

    for (int i = 0; i < world->room_count; i++) {
        Room *room = world->rooms[i];
        room->x += width_to_add;
        room->y += height_to_add;
        room->cuboid.x1 += width_to_add;
        room->cuboid.y1 += height_to_add;
        room->cuboid.x2 += width_to_add;
        world->rooms[i] = room;
    }

    for (int i = 0; i < world->room_count; i++) {
        Room *room = world->rooms[i];
        for (int j = 0; j < 4; j++) {
            Door *door = room->doors[j];
            if (door->x == -1 && door->y == -1) {
                continue;
            }
            door->x += width_to_add;
            door->y += height_to_add;
            room->doors[j] = door;
        }
        world->rooms[i] = room;
    }


    for (int i = 0; i < world->width; i++) {
        free(world->chunk[i]);
    }

    free(world->chunk);

    prepend_entity(width_to_add, height_to_add);

    world->width = new_width;
    world->height = new_height;
    world->chunk = new_chunk;
}

int can_append_room(Game_World *world, Room *room) {
    if (world == NULL) {
        return -2;
    }

    if (room->x < 0 || room->y < 0 || room->width <= 0 || room->height <= 0) {
        return -2;
    }

    int width_to_check = room->x + room->width; //>= world->width ? world->width : room.x + room.width;
    int height_to_check = room->y + room->height;// >= world->height ? world->height : room.y + room.height;

    if (width_to_check >= world->width) {
        width_to_check = world->width;
    }

    if (height_to_check >= world->height) {
        height_to_check = world->height;
    }

    for (int i = room->x; i < width_to_check; i++) {
        for (int j = room->y; j < height_to_check; j++) {
            Chunk *chunk = get_chunk(world, i, j);

            if (chunk == NULL) {
                return -2;
            }

            if (chunk->type != VOID) {
                for (int k = 0; k < world->room_count; ++k) {
                    Room *room_to_check = world->rooms[k];
                    if (in_room(room_to_check, i, j)) {
                        return k;
                    }
                }
            }
        }
    }

    return -1;
}

int append_room(Game_World *world, Room *room) {
    if (world == NULL) {
        return -1;
    }

    if (can_append_room(world, room) != -1) {
        return -1;
    }

    if (world->room_count >= world->room_capacity) {
        world->room_capacity *= 2;
        Room **new_rooms = realloc(world->rooms, sizeof(Room *) * world->room_capacity);
        if (!new_rooms) {
            return -1;
        }

        world->rooms = new_rooms;
    }

    int width_need = room->x + room->width; //room.x + room.width;
    int height_need = room->y + room->height; //room.y + room.height; //I think it to much to add
    if (width_need >= world->width || height_need >= world->height) {
        append_world(world, room->width + (room->width / 2), room->height + (room->height / 2));
    }

    for (int i = room->x; i < room->x + room->width; i++) {
        for (int j = room->y; j < room->y + room->height; j++) {
            world->chunk[i][j]->type = EMPTY;
        }
    }

    for (int i = room->x; i < room->x + room->width; ++i) {
        Chunk *chunk = world->chunk[i][room->y];
        chunk->type = WALL;
        chunk->direction = NORTH;

        Chunk *chunk2 = world->chunk[i][room->y + room->height - 1];
        chunk2->type = WALL;
        chunk2->direction = SOUTH;
    }

    for (int i = room->y; i < room->y + room->height; ++i) {
        Chunk *chunk = world->chunk[room->x][i];
        chunk->type = WALL;
        chunk->direction = WEST;

        Chunk *chunk2 = world->chunk[room->x + room->width - 1][i];
        chunk2->type = WALL;
        chunk2->direction = EAST;
    }

    world->chunk[room->x][room->y]->direction = NORTH_WEST;
    world->chunk[room->x + room->width - 1][room->y]->direction = NORTH_EAST;
    world->chunk[room->x][room->y + room->height - 1]->direction = SOUTH_WEST;
    world->chunk[room->x + room->width - 1][room->y + room->height - 1]->direction = SOUTH_EAST;

    for (int i = 0; i < 4; i++) {
        Door *door = room->doors[i];
        if (door->x == -1 && door->y == -1) continue;

        if (!door->is_used) {
            world->prepared_rooms_count++;
        }
        world->chunk[door->x][door->y]->type = DOOR;
    }

    world->rooms[world->room_count] = room;
    world->room_count++;

    return world->room_count - 1;
}

Room *create_room(int width, int height, int x, int y) {
    Room *room = malloc(sizeof(Room));

    room->width = width;
    room->height = height;
    room->x = x;
    room->y = y;

    Cuboid cuboid = {x, y,
                     x + width, y + height};

    room->cuboid = cuboid;

    room->doors = malloc(4 * sizeof(Door *));
    if (room->doors == NULL) {
        free(room);
        return NULL;
    }

    for (int i = 0; i < 4; i++) {
        Door *door = malloc(sizeof(Door));
        if (door == NULL) {
            free(room->doors);
            free(room);
            return NULL;
        }

        door->x = -1;
        door->y = -1;
        door->is_used = false;
        room->doors[i] = door;
    }

    room->start_door = -1;

    room->is_visited = false;

    return room;
}

bool in_room(Room *room, int x, int y) {
    return x >= room->x && x < room->x + room->width && y >= room->y && y < room->y + room->height;
}

Room *get_room(Game_World *world, int x, int y) {
    if (world == NULL) {
        return NULL;
    }

    if (world->chunk[x][y]->type == VOID) {
        return NULL;
    }

    for (int i = 0; i < world->room_count; i++) {
        Room *room = world->rooms[i];
        if (in_room(room, x, y)) {
            return room;
        }
    }

    return NULL;
}

bool any_door_not_used(Game_World *world) {
    if (world == NULL) {
        return false;
    }

    for (int i = 0; i < world->room_count; i++) {
        Room *room = world->rooms[i];
        for (int j = 0; j < 4; j++) {
            Door *door = room->doors[j];
            if (door->x == -1 && door->y == -1) {
                continue;
            }

            if (!door->is_used) {
                return true;
            }
        }
    }

    return false;
}

int count_visited_rooms(Game_World *world) {
    if (world == NULL) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < world->room_count; i++) {
        Room *room = world->rooms[i];
        if (room->is_visited) {
            count++;
        }
    }

    return count;
}