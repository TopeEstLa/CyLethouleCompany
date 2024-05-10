#include <saves.h>

#include "../libs/include/cJSON.h"
#include <stdio.h>

#include <file_utils.h>


bool save_world(Game_World *world, char *filename) {
    cJSON *globalJson = cJSON_CreateObject();

    cJSON_AddNumberToObject(globalJson, "format_version", FORMAT_VERSION);

    cJSON *worldObj = cJSON_CreateObject();

    cJSON_AddNumberToObject(worldObj, "seed", world->seed);
    cJSON_AddNumberToObject(worldObj, "width", world->width);
    cJSON_AddNumberToObject(worldObj, "height", world->height);

    cJSON *roomArray = cJSON_CreateArray();

    for (int i = 0; i < world->room_count; i++) {
        cJSON *roomObj = cJSON_CreateObject();

        Room room = world->rooms[i];

        cJSON_AddNumberToObject(roomObj, "index", i);
        cJSON_AddNumberToObject(roomObj, "x", room.x);
        cJSON_AddNumberToObject(roomObj, "y", room.y);
        cJSON_AddNumberToObject(roomObj, "width", room.width);
        cJSON_AddNumberToObject(roomObj, "height", room.height);
        cJSON_AddBoolToObject(roomObj, "is_visited", room.is_visited);

        cJSON *doorsArray = cJSON_CreateArray();

        for (int j = 0; j < 4; j++) {
            Door *door = room.doors[j];

            cJSON *doorObj = cJSON_CreateObject();
            cJSON_AddNumberToObject(doorObj, "index", j);
            cJSON_AddNumberToObject(doorObj, "x", door->x);
            cJSON_AddNumberToObject(doorObj, "y", door->y);
            cJSON_AddBoolToObject(doorObj, "is_used", door->is_used);
            cJSON_AddItemToArray(doorsArray, doorObj);
        }

        cJSON_AddItemToObject(roomObj, "doors", doorsArray);

        cJSON_AddItemToArray(roomArray, roomObj);
    }

    cJSON_AddItemToObject(worldObj, "rooms", roomArray);

    cJSON_AddItemToObject(globalJson, "world", worldObj);

    bool result = save_json(filename, globalJson);

    cJSON_Delete(globalJson);

    return result;
}

Game_World* load_world(char *filename) {
    cJSON *globalJson = load_json(filename);

    if (globalJson == NULL) {
        return NULL;
    }

    cJSON *formatVersion = cJSON_GetObjectItem(globalJson, "format_version");

    if (formatVersion == NULL || formatVersion->valueint != FORMAT_VERSION) {
        cJSON_Delete(globalJson);
        printf("Format version is not correct\n");
        return NULL;
    }

    cJSON *worldObj = cJSON_GetObjectItem(globalJson, "world");

    if (worldObj == NULL) {
        cJSON_Delete(globalJson);
        return NULL;
    }

    int seed = cJSON_GetObjectItem(worldObj, "seed")->valueint;
    int width = cJSON_GetObjectItem(worldObj, "width")->valueint;
    int height = cJSON_GetObjectItem(worldObj, "height")->valueint;

    Game_World* world = create_world_sized(seed, width, height);

    cJSON *roomsArray = cJSON_GetObjectItem(worldObj, "rooms");

    for (int i = 0; i < cJSON_GetArraySize(roomsArray); i++) {
        cJSON *roomObj = cJSON_GetArrayItem(roomsArray, i);

        int x = cJSON_GetObjectItem(roomObj, "x")->valueint;
        int y = cJSON_GetObjectItem(roomObj, "y")->valueint;
        int room_width = cJSON_GetObjectItem(roomObj, "width")->valueint;
        int room_height = cJSON_GetObjectItem(roomObj, "height")->valueint;
        bool is_visited = cJSON_GetObjectItem(roomObj, "is_visited")->valueint;

        Room room = create_room(room_width, room_height, x, y);
        room.is_visited = is_visited;

        cJSON *doorsArray = cJSON_GetObjectItem(roomObj, "doors");

        for (int j = 0; j < cJSON_GetArraySize(doorsArray); j++) {
            cJSON *doorObj = cJSON_GetArrayItem(doorsArray, j);

            int index = cJSON_GetObjectItem(doorObj, "index")->valueint;

            Door *door = room.doors[index];
            door->x = cJSON_GetObjectItem(doorObj, "x")->valueint;
            door->y = cJSON_GetObjectItem(doorObj, "y")->valueint;
            door->is_used = cJSON_GetObjectItem(doorObj, "is_used")->valueint;

            room.doors[j] = door;
        }

        append_room(world, room);
    }

    cJSON_Delete(globalJson);

    return world;
}