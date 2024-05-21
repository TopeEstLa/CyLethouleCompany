
#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <world.h>

#define MAX_ROOM_WIDTH 10
#define MAX_ROOM_HEIGHT 10

#define MIN_ROOM_WIDTH 5
#define MIN_ROOM_HEIGHT 5

#define MAX_ROOM -1 //MIN 5 -1 for infinite

typedef enum {
    TOP = 0,
    BOTTOM = 1,
    LEFT = 2,
    RIGHT = 3
} Door_Face;

/**
 * Generate the first room and the rooms around it.
 * @param world
 */
void base_generation(Game_World *world);

/**
 * Generate the rooms around the starting room.
 * @param world
 * @param starting_room
 * @param recursion_depth
 */
void generate_rooms(Game_World *world, Room* starting_room, int recursion_depth);

/**
 * Generate a room from a door of a starting_room.
 * @param world
 * @param starting_room
 * @param door
 * @param recursion_depth
 */
void generate_room(Game_World *world, Room* starting_room, int door, int recursion_depth);

/**
 * Resize a room to avoid conflict with another room.
 * @param room
 * @param conflictRoom
 * @param door_face
 * @param door
 * @return The resized room.
 */
Room* resize_room(Room* room, Room* conflictRoom, int door_face, Door* door);

/**
 * Check if a room is valid.
 * @param room
 * @return
 */
int is_room_valid(Room* room);

#endif //WORLD_GENERATOR_H
