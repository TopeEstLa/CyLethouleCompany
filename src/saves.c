#include <saves.h>

#include <cJSON.h>
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

    for (int i = 0; i < 10; i++) {
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
