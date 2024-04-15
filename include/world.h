#ifndef WORLD_H
#define WORLD_H

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
    Room** rooms; // 2D array of Rooms[width][height] example:
    // <-     width     ->  ^
    // [0][0][1][0][2][0]   |          Rooms[0->width][0] :  [0][0][1][0][2][0]
    // [0][1][1][1][2][1]   height     Rooms[0->width][1] :  [0][1][1][1][2][1]
    // [0][2][1][2][2][2]   |
    // [0][3][1][3][2][3]   v
} Game_World;



#endif //WORLD_H
