
#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <world.h>

#define MAX_ROOM_WIDTH 10
#define MAX_ROOM_HEIGHT 10

#define MIN_ROOM_WIDTH 5
#define MIN_ROOM_HEIGHT 5

typedef enum {
    TOP = 0,
    BOTTOM = 1,
    LEFT = 2,
    RIGHT = 3
} Door_Face;

void base_generation(Game_World *world);

void generate_rooms(Game_World *world, Room starting_room, int recursion_depth);

void generate_room(Game_World *world, Room starting_room, int door, int recursion_depth);

Room resize_room(Room room, Room conflictRoom, int door_face, Pair* door);

int is_room_valid(Room room);

#endif //WORLD_GENERATOR_H
