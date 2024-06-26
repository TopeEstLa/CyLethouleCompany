#ifndef WORLD_H
#define WORLD_H

#include <maths.h>
#include <stdbool.h>

#define DEFAULT_WORLD_WIDTH 30
#define DEFAULT_WORLD_HEIGHT 30

/**
 * Different states of a chunk. (
 */
typedef enum chunk_type {
    VOID, //PLAYER CAN'T GO THERE
    EMPTY, //PLACE WHERE PLAYER CAN WALK
    DOOR,
    WALL
} Chunk_Type;

/**
 * Enum to represent the direction of a chunk.
 */
typedef enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NORTH_EAST,
    NORTH_WEST,
    SOUTH_EAST,
    SOUTH_WEST,
    NONE
} Direction;

/**
 * A struct representing a chunk, chunk is a section in the world
 */
typedef struct chunk {
    Chunk_Type type;
    Direction direction;
} Chunk;

/**
 * A struct representing a door.
 * @param x The x position of the door.
 * @param y The y position of the door.
 * @param is_used If the door is used for generating a room.
 */
typedef struct door {
    int x, y;
    bool is_used;
} Door;


/**
 * Struct representing a room.
 * @param width The width of the room.
 * @param height The height of the room.
 * @param x The x position of the room.
 * @param y The y position of the room.
 * @param start_door The index of the door where the room was generated.
 * @param is_visited If the room was visited by the player.
 * @param doors An array of pairs representing the doors locations.
 */
typedef struct room {
    int width, height, x, y;
    int start_door;
    bool is_visited;
    Door **doors; //Max 4 door by room (N, E, S, W)
} Room;

/**
 * Struct representing the game world.
 * @param seed The seed used to generate the world.
 * @param width The current width of the world.
 * @param height The current height of the world.
 * @param chunk A 2D array of chunks representing the world (in terminal 1 chunk = 1 char | in SquidEngine 1 chunk = 4 pixel).
 * @param rooms An ArrayList like of rooms in the world.
 * @param room_capacity The current capacity of the rooms array.
 * @param room_count The current number of rooms in the world.
 * @param prepared_rooms_count The number of rooms prepared to be appended to the world.
 */
typedef struct game_world {
    int seed;
    int width;
    int height;
    Chunk ***chunk; // 2D array of Chunk*[width][height] example:
    // <-         width       ->    ^
    // [ [0, [0, [1, [0, [2, [0, ]  |
    //    0,  1,  1,  1,  2,  1,   height
    //    0,  2,  1,  2,  2,  2,    |
    //    0], 3], 1], 3], 2], 3],   v
    Room **rooms;
    int room_capacity;
    int room_count;
    int prepared_rooms_count;
} Game_World;

/**
 * Generate a new game world.
 * @param seed The seed to use for the random number generator.
 * @return A pointer to the newly created game world.
 */
Game_World *create_world(int seed);

/**
 * Generate a new game world with the given width and height.
 * @param seed
 * @param width
 * @param height
 * @return
 */
Game_World *create_world_sized(int seed, int width, int height);

/**
 * Get the chunk at the given position.
 * @param world
 * @param x
 * @param y
 * @return
 */
Chunk *get_chunk(Game_World *world, int x, int y);

/**
 * Add new chunks to the world. (append to the right and the bottom)
 * @param world The world to append to.
 * @param width_to_add The number of chunks to add to the width.
 * @param height_to_add  The number of chunks to add to the height.
 */
void append_world(Game_World *world, int width_to_add, int height_to_add);

/**
 * Add new chunks to the world. (append to the left and the top)
 * @param world The world to prepend to.
 * @param width_to_add The number of chunks to add to the width.
 * @param height_to_add The number of chunks to add to the height.
 */
void prepend_world(Game_World *world, int width_to_add, int height_to_add);

/**
 * Check if a room can be appended to the world (not crossing another room).
 * @param world The world to check.
 * @param room The room to check.
 * @return if conflicting return room id, -1 otherwise or -2 if wtf issue.
 */
int can_append_room(Game_World *world, Room *room);

/**
 * Append a room to the world.
 * @param world The world to append the room to.
 * @param room The room to append.
 * @return room index if the room was appended, -1 otherwise.
 */
int append_room(Game_World *world, Room *room);

/**
 * Check if coordinates are in a room.
 * @param room
 * @param x
 * @param y
 * @return
 */
bool in_room(Room *room, int x, int y);

/**
 * Create a new room with the given width and height.
 *
 * @param width The width of the room.
 * @param height The height of the room.                Example:   x = 0, y = 0 width = 3, height = 3
 * @param x the start x of the room.                        WALL WALL WALL  The room will be created in the world like this:
 * @param y the start y of the room.                        WALL EMPTY WALL
 * @return A pointer to the newly created room.             WALL DOOR WALL
 */
Room *create_room(int width, int height, int x, int y);

/**
 * Get the room at the given position.
 * @param world
 * @param x
 * @param y
 * @return
 */
Room *get_room(Game_World *world, int x, int y);

/**
 * Check all door of all room and return true if any door is not used.
 * @param world The world to check.
 * @return true if any door is not used, false otherwise.
 */
bool any_door_not_used(Game_World *world);

/**
 * Count the number of visited rooms in the world.
 * @param world The world to count the visited rooms in.
 * @return The number of visited rooms.
 */
int count_visited_rooms(Game_World *world);


#endif //WORLD_H
