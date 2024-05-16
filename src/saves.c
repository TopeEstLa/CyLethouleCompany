#include <saves.h>

#include "../libs/include/cJSON.h"
#include <stdio.h>
#include <stdlib.h>

#include <file_utils.h>
#include <player.h>

cJSON* create_world_json(Game_World* world) {
    cJSON *worldObj = cJSON_CreateObject();

    if (world == NULL) {
        return worldObj;
    }

    cJSON_AddNumberToObject(worldObj, "seed", world->seed);
    cJSON_AddNumberToObject(worldObj, "width", world->width);
    cJSON_AddNumberToObject(worldObj, "height", world->height);

    cJSON *roomArray = cJSON_CreateArray();

    for (int i = 0; i < world->room_count; i++) {
        cJSON *roomObj = cJSON_CreateObject();

        Room *room = world->rooms[i];

        cJSON_AddNumberToObject(roomObj, "index", i);
        cJSON_AddNumberToObject(roomObj, "x", room->x);
        cJSON_AddNumberToObject(roomObj, "y", room->y);
        cJSON_AddNumberToObject(roomObj, "width", room->width);
        cJSON_AddNumberToObject(roomObj, "height", room->height);
        cJSON_AddBoolToObject(roomObj, "is_visited", room->is_visited);

        cJSON *doorsArray = cJSON_CreateArray();

        for (int j = 0; j < 4; j++) {
            Door *door = room->doors[j];

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

    return worldObj;
}

bool save_world(Game_World *world, char *filename) {
    cJSON *globalJson = cJSON_CreateObject();

    cJSON_AddNumberToObject(globalJson, "format_version", FORMAT_VERSION);

    cJSON *worldObj = create_world_json(world);

    cJSON_AddItemToObject(globalJson, "world", worldObj);

    bool result = save_json(filename, globalJson);

    cJSON_Delete(globalJson);

    return result;
}

bool save_game(Game_Data *game, char *save_name) {
    if (game == NULL) {
        return false;
    }

    cJSON *globalJson = cJSON_CreateObject();

    cJSON_AddNumberToObject(globalJson, "format_version", FORMAT_VERSION);

    cJSON *worldObj = create_world_json(game->world);

    Player *player = game->player;
    cJSON *playerObj = cJSON_CreateObject();

    cJSON_AddStringToObject(playerObj, "name", player->name);
    cJSON_AddNumberToObject(playerObj, "class", player->current_class);
    cJSON_AddNumberToObject(playerObj, "health", player->health);
    cJSON_AddNumberToObject(playerObj, "exp", player->exp);
    cJSON_AddNumberToObject(playerObj, "x", player->entity->x);
    cJSON_AddNumberToObject(playerObj, "y", player->entity->y);

    cJSON_AddItemToObject(globalJson, "world", worldObj);
    cJSON_AddItemToObject(globalJson, "player", playerObj);

    bool result = save_json(save_name, globalJson);

    cJSON_Delete(globalJson);

    return result;
}

Game_World* load_world_from_json(cJSON* worldObj) {
    int seed = cJSON_GetObjectItem(worldObj, "seed")->valueint;
    int width = cJSON_GetObjectItem(worldObj, "width")->valueint;
    int height = cJSON_GetObjectItem(worldObj, "height")->valueint;

    Game_World *world = create_world_sized(seed, width, height);

    cJSON *roomsArray = cJSON_GetObjectItem(worldObj, "rooms");

    for (int i = 0; i < cJSON_GetArraySize(roomsArray); i++) {
        cJSON *roomObj = cJSON_GetArrayItem(roomsArray, i);

        int x = cJSON_GetObjectItem(roomObj, "x")->valueint;
        int y = cJSON_GetObjectItem(roomObj, "y")->valueint;
        int room_width = cJSON_GetObjectItem(roomObj, "width")->valueint;
        int room_height = cJSON_GetObjectItem(roomObj, "height")->valueint;
        bool is_visited = cJSON_GetObjectItem(roomObj, "is_visited")->valueint;

        Room *room = create_room(room_width, room_height, x, y);
        room->is_visited = is_visited;

        cJSON *doorsArray = cJSON_GetObjectItem(roomObj, "doors");

        for (int j = 0; j < cJSON_GetArraySize(doorsArray); j++) {
            cJSON *doorObj = cJSON_GetArrayItem(doorsArray, j);

            int index = cJSON_GetObjectItem(doorObj, "index")->valueint;

            Door *door = room->doors[index];
            door->x = cJSON_GetObjectItem(doorObj, "x")->valueint;
            door->y = cJSON_GetObjectItem(doorObj, "y")->valueint;
            door->is_used = cJSON_GetObjectItem(doorObj, "is_used")->valueint;

            room->doors[j] = door;
        }

        append_room(world, room);
    }

    return world;
}

Game_World *load_world(char *filename) {
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

    Game_World *world = load_world_from_json(worldObj);


    cJSON_Delete(globalJson);

    return world;
}

Game_Data *load_game(char *save_name) {
    cJSON *globalJson = load_json(save_name);

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

    Game_World *world = load_world_from_json(worldObj);

    cJSON *playerObj = cJSON_GetObjectItem(globalJson, "player");

    if (playerObj == NULL) {
        cJSON_Delete(globalJson);
        return NULL;
    }

    char *name = cJSON_GetObjectItem(playerObj, "name")->valuestring;
    Class current_class = cJSON_GetObjectItem(playerObj, "class")->valueint;
    int health = cJSON_GetObjectItem(playerObj, "health")->valueint;
    int exp = cJSON_GetObjectItem(playerObj, "exp")->valueint;
    int x = cJSON_GetObjectItem(playerObj, "x")->valueint;
    int y = cJSON_GetObjectItem(playerObj, "y")->valueint;

    Player *player = load_player(world, name, current_class, health, exp, x, y);

    Game_Data *game = malloc(sizeof(Game_Data));
    game->world = world;
    game->player = player;

    cJSON_Delete(globalJson);

    return game;
}