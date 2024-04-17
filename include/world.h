#ifndef WORLD_H
#define WORLD_H

#define DEFAULT_WORLD_WIDTH 10
#define DEFAULT_WORLD_HEIGHT 10

typedef enum chunk_type {
    VOID,
    EMPTY,
    DOOR,
    WALL
} Chunk_Type;

typedef struct chunk {
    Chunk_Type type;
} Chunk;

/**
 * Struct representing a room.
 * @param width The width of the room.
 * @param height The height of the room.
 * @param x The x position of the room.
 * @param y The y position of the room.
 */
typedef struct room {
    int width, height, x, y;
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
 */
typedef struct game_world {
    int seed;
    int width;
    int height;
    Chunk** chunk; // 2D array of Chunk[width][height] example:
    // <-         width       ->    ^
    // [ [0, [0, [1, [0, [2, [0, ]  |
    //    0,  1,  1,  1,  2,  1,   height
    //    0,  2,  1,  2,  2,  2,    |
    //    0], 3], 1], 3], 2], 3],   v
    Room* rooms;
    int room_capacity;
    int room_count;
} Game_World;

/**
 * Generate a new game world.
 * @param seed The seed to use for the random number generator.
 * @return A pointer to the newly created game world.
 */
Game_World* create_world(int seed);

/**
 * Add new chunks to the world. (append to the right and the bottom)
 * @param world The world to append to.
 * @param width_to_add The number of chunks to add to the width.
 * @param height_to_add  The number of chunks to add to the height.
 */
void append_world(Game_World* world, int width_to_add, int height_to_add);

/**
 * Add new chunks to the world. (append to the left and the top)
 * @param world The world to prepend to.
 * @param width_to_add The number of chunks to add to the width.
 * @param height_to_add The number of chunks to add to the height.
 */
void prepend_world(Game_World* world, int width_to_add, int height_to_add);

int can_append_room(Game_World* world, Room room);

/**
 * Append a room to the world.
 * @param world The world to append the room to.
 * @param room The room to append.
 * @return 1 if error 0 if ok.
 */
int append_room(Game_World* world, Room room);

/**
 * Create a new room with the given width and height.
 *
 * @param width The width of the room.
 * @param height The height of the room.                Example:   x = 0, y = 0 width = 3, height = 3
 * @param x the start x of the room.                        WALL WALL WALL  The room will be created in the world like this:
 * @param y the start y of the room.                        WALL EMPTY WALL
 * @return A pointer to the newly created room.             WALL DOOR WALL
 */
Room create_room(int width, int height, int x, int y);


#endif //WORLD_H