#ifndef WORLD_H
#define WORLD_H

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 10

typedef enum chunk_type {
    EMPTY,
    DOOR,
    WALL
} Chunk_Type;

typedef struct room_chunk { //TODO: View if Room_Chunk is necessary because it just contains the room chunk type
    Chunk_Type type;
} Room_Chunk;

/**
 * Struct representing a room.
 */
typedef struct room {
    int width;
    int height;
    Room_Chunk** chunks; // 2D array of Room_Chunks[width][height]
} Room;

/**
 * Struct representing the game world.
 */
typedef struct game_world {
    int seed;
    Room*** rooms; // 2D array of Rooms[width][height] example:
    // <-     width    ->  ^
    // [0][0][1][0][2][0]   |
    // [0][1][1][1][2][1]   height
    // [0][2][1][2][2][2]   |
    // [0][3][1][3][2][3]   v
} Game_World;

/**
 * Generate a new game world.
 * @param seed The seed to use for the random number generator.
 * @return A pointer to the newly created game world.
 */
Game_World* create_world(int seed);

/**
 * Generate a new room.
 * @param seed The seed to use for the random number generator.
 * @return A pointer to the newly created room.
 */
Room* generate_room(int seed);

/**
 * Create a new room with the given width and height.
 *
 * @param width The width of the room.
 * @param height The height of the room.
 * @return A pointer to the newly created room.
 */
Room* create_room(int width, int height);


#endif //WORLD_H
