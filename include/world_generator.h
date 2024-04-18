
#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <world.h>

#define MAX_ROOM_WIDTH 10
#define MAX_ROOM_HEIGHT 10

#define MIN_ROOM_WIDTH 5
#define MIN_ROOM_HEIGHT 5

void base_generation(Game_World* world);

void generate_room(Game_World* world, Room starting_room, int recursion_depth);

#endif //WORLD_GENERATOR_H
