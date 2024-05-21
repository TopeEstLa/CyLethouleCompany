#include <saves.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <file_utils.h>
#include <player.h>
#include <memory_utils.h>

cJSON *create_world_json(Game_World *world) {
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

cJSON *create_monster_json(World_Monster *worldMonster) {
    if (worldMonster == NULL) {
        return NULL;
    }

    cJSON *monsterObj = cJSON_CreateObject();

    if (monsterObj == NULL) {
        return NULL;
    }

    cJSON *monstersArray = cJSON_CreateArray();
    for (int i = 0; i < worldMonster->living_monsters_count; ++i) {
        Living_Monster *livingMonster = worldMonster->living_monsters[i];
        cJSON *monster = cJSON_CreateObject();
        cJSON_AddNumberToObject(monster, "monster_id", livingMonster->monster_id);
        cJSON_AddNumberToObject(monster, "health", livingMonster->health);
        cJSON_AddNumberToObject(monster, "x", livingMonster->entity->x);
        cJSON_AddNumberToObject(monster, "y", livingMonster->entity->y);
        cJSON_AddItemToArray(monstersArray, monster);
    }

    cJSON_AddItemToObject(monsterObj, "monsters", monstersArray);

    return monsterObj;

}

cJSON *create_item_json(World_Item *worldItem) {
    if (worldItem == NULL) {
        return NULL;
    }

    cJSON *itemObj = cJSON_CreateObject();

    if (itemObj == NULL) {
        return NULL;
    }

    cJSON *itemsArray = cJSON_CreateArray();
    for (int i = 0; i < worldItem->dropped_items_count; ++i) {
        Dropped_Item *droppedItem = worldItem->dropped_items[i];
        cJSON *item = cJSON_CreateObject();

        cJSON *item_stack = cJSON_CreateObject();
        cJSON_AddStringToObject(item_stack, "name", droppedItem->item->name);
        cJSON_AddStringToObject(item_stack, "texture", droppedItem->item->texture);
        cJSON_AddNumberToObject(item_stack, "price", droppedItem->item->price);
        cJSON_AddNumberToObject(item_stack, "material", droppedItem->item->material);

        cJSON_AddItemToObject(item, "item_stack", item_stack);

        cJSON_AddNumberToObject(item, "x", droppedItem->entity->x);
        cJSON_AddNumberToObject(item, "y", droppedItem->entity->y);
        cJSON_AddItemToArray(itemsArray, item);
    }

    cJSON_AddItemToObject(itemObj, "items", itemsArray);

    return itemObj;
}

cJSON *create_player_json(Player *player) {
    if (player == NULL) {
        return NULL;
    }

    cJSON *playerObj = cJSON_CreateObject();

    if (playerObj == NULL) {
        return NULL;
    }

    cJSON_AddStringToObject(playerObj, "name", player->name);
    cJSON_AddNumberToObject(playerObj, "class", player->current_class);
    cJSON_AddNumberToObject(playerObj, "health", player->health);
    cJSON_AddNumberToObject(playerObj, "max_health", player->max_health);
    cJSON_AddNumberToObject(playerObj, "exp", player->exp);
    cJSON_AddNumberToObject(playerObj, "money", player->money);
    cJSON_AddNumberToObject(playerObj, "x", player->entity->x);
    cJSON_AddNumberToObject(playerObj, "y", player->entity->y);

    Inventory *inventory = player->inventory;
    cJSON *inventoryArray = cJSON_CreateArray();
    for (int i = 0; i < inventory->index; ++i) {
        Item_Stack *item_stack = inventory->items[i];
        cJSON *item = cJSON_CreateObject();
        cJSON_AddStringToObject(item, "name", item_stack->name);
        cJSON_AddStringToObject(item, "texture", item_stack->texture);
        cJSON_AddNumberToObject(item, "price", item_stack->price);
        cJSON_AddNumberToObject(item, "material", item_stack->material);
        cJSON_AddItemToArray(inventoryArray, item);
    }

    cJSON_AddItemToObject(playerObj, "inventory", inventoryArray);

    return playerObj;

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

    int remaining_time = (int) ((game->end_time - clock()));

    cJSON_AddNumberToObject(globalJson, "remaining_time", remaining_time);

    cJSON *worldObj = create_world_json(game->world);
    if (worldObj == NULL) {
        cJSON_Delete(globalJson);
        return false;
    }

    cJSON *monsterObj = create_monster_json(game->world_monster);
    if (monsterObj == NULL) {
        cJSON_Delete(globalJson);
        return false;
    }

    cJSON *itemObj = create_item_json(game->world_item);
    if (itemObj == NULL) {
        cJSON_Delete(globalJson);
        return false;
    }

    cJSON *playerObj = create_player_json(game->player);
    if (playerObj == NULL) {
        cJSON_Delete(globalJson);
        return false;
    }

    cJSON_AddItemToObject(globalJson, "world", worldObj);
    cJSON_AddItemToObject(globalJson, "monster", monsterObj);
    cJSON_AddItemToObject(globalJson, "item", itemObj);
    cJSON_AddItemToObject(globalJson, "player", playerObj);

    bool result = save_json(save_name, globalJson);

    cJSON_Delete(globalJson);

    return result;
}

Game_World *load_world_from_json(cJSON *worldObj) {
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

World_Monster *load_monster_from_json(Game_World *world, cJSON *monsterObj) {
    World_Monster *worldMonster = init_world_monster();

    cJSON *monstersArray = cJSON_GetObjectItem(monsterObj, "monsters");

    for (int i = 0; i < cJSON_GetArraySize(monstersArray); i++) {
        cJSON *monster = cJSON_GetArrayItem(monstersArray, i);

        int monster_id = cJSON_GetObjectItem(monster, "monster_id")->valueint;
        int health = cJSON_GetObjectItem(monster, "health")->valueint;
        int x = cJSON_GetObjectItem(monster, "x")->valueint;
        int y = cJSON_GetObjectItem(monster, "y")->valueint;

        create_living_monster(world, worldMonster, monster_id, x, y, health);
    }

    return worldMonster;

}



World_Item *load_item_from_json(Game_World *world, cJSON *itemObj) {
    World_Item *worldItem = init_world_item();

    cJSON *itemsArray = cJSON_GetObjectItem(itemObj, "items");

    for (int i = 0; i < cJSON_GetArraySize(itemsArray); i++) {
        cJSON *item = cJSON_GetArrayItem(itemsArray, i);

        cJSON *item_stack_json = cJSON_GetObjectItem(item, "item_stack");
        char *name = cJSON_GetObjectItem(item_stack_json, "name")->valuestring;
        char *texture = cJSON_GetObjectItem(item_stack_json, "texture")->valuestring;
        int price = cJSON_GetObjectItem(item_stack_json, "price")->valueint;
        int material = cJSON_GetObjectItem(item_stack_json, "material")->valueint;

        Item_Stack* item_stack = create_formatted_item_stack(name, texture, price, material);
        if (item_stack == NULL) {
            free(worldItem);
            return NULL;
        }

        int x = cJSON_GetObjectItem(item, "x")->valueint;
        int y = cJSON_GetObjectItem(item, "y")->valueint;

        Dropped_Item *dropped_item = drop_item(world, worldItem, item_stack, x, y);
        if (dropped_item == NULL) {
            free(worldItem);
            return NULL;
        }
    }

    return worldItem;

}

Player* load_player_from_json(Game_World* world, cJSON* playerObj) {
    char *name = cJSON_GetObjectItem(playerObj, "name")->valuestring;
    Class current_class = cJSON_GetObjectItem(playerObj, "class")->valueint;
    int health = cJSON_GetObjectItem(playerObj, "health")->valueint;
    int max_health = cJSON_GetObjectItem(playerObj, "max_health")->valueint;
    int exp = cJSON_GetObjectItem(playerObj, "exp")->valueint;
    int money = cJSON_GetObjectItem(playerObj, "money")->valueint;
    int x = cJSON_GetObjectItem(playerObj, "x")->valueint;
    int y = cJSON_GetObjectItem(playerObj, "y")->valueint;

    Inventory *inventory = create_inventory(INVENTORY_CAPACITY);
    if (inventory == NULL) {
        return NULL;
    }

    cJSON *inventoryArray = cJSON_GetObjectItem(playerObj, "inventory");
    for (int i = 0; i < cJSON_GetArraySize(inventoryArray); i++) {
        cJSON *item = cJSON_GetArrayItem(inventoryArray, i);

        char *item_name = cJSON_GetObjectItem(item, "name")->valuestring;
        char *texture = cJSON_GetObjectItem(item, "texture")->valuestring;
        int price = cJSON_GetObjectItem(item, "price")->valueint;
        int material = cJSON_GetObjectItem(item, "material")->valueint;

        Item_Stack *item_stack = create_formatted_item_stack(item_name, texture, price, material);
        if (item_stack == NULL) {
            return NULL;
        }


        add_item_to_inventory(inventory, item_stack);
    }

    Player *player = load_player(world, name, inventory, current_class, health, max_health, exp, money, x, y);
    return player;
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

    cJSON *remainingTime = cJSON_GetObjectItem(globalJson, "remaining_time");
    if (remainingTime == NULL) {
        cJSON_Delete(globalJson);
        return NULL;
    }

    cJSON *worldObj = cJSON_GetObjectItem(globalJson, "world");

    if (worldObj == NULL) {
        cJSON_Delete(globalJson);
        return NULL;
    }

    Game_World *world = load_world_from_json(worldObj);
    if (world == NULL) {
        cJSON_Delete(globalJson);
        return NULL;
    }

    cJSON *playerObj = cJSON_GetObjectItem(globalJson, "player");

    if (playerObj == NULL) {
        free_world(world);
        cJSON_Delete(globalJson);
        return NULL;
    }

    Player* player = load_player_from_json(world, playerObj);
    if (player == NULL) {
        free_world(world);
        cJSON_Delete(globalJson);
        return NULL;
    }

    cJSON *monsterObj = cJSON_GetObjectItem(globalJson, "monster");
    if (monsterObj == NULL) {
        free_player(player);
        free_world(world);
        cJSON_Delete(globalJson);
        return NULL;
    }

    World_Monster *worldMonster = load_monster_from_json(world, monsterObj);
    if (worldMonster == NULL) {
        free(player);
        free_world(world);
        cJSON_Delete(globalJson);
        return NULL;
    }

    cJSON *itemObj = cJSON_GetObjectItem(globalJson, "item");
    if (itemObj == NULL) {
        free_player(player);
        free_world(world);
        cJSON_Delete(globalJson);
        return NULL;
    }

    World_Item *worldItem = load_item_from_json(world, itemObj);
    if (worldItem == NULL) {
        free(player);
        free_world(world);
        cJSON_Delete(globalJson);
        return NULL;
    }


    Game_Data *game = malloc(sizeof(Game_Data));
    int remaining_time = remainingTime->valueint;
    game->start_time = clock();
    game->end_time = game->start_time + remaining_time;

    game->world = world;
    game->world_monster = worldMonster;
    game->world_item = worldItem;
    game->player = player;

    cJSON_Delete(globalJson);

    return game;
}