#include <saves.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <file_utils.h>
#include <player.h>
#include <memory_utils.h>

#include <constant.h>

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

    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    long remaining_time = game->end_time.tv_sec - current_time.tv_sec;
    long useconds = game->end_time.tv_usec - current_time.tv_usec;

    if (useconds < 0) {
        remaining_time--;
        useconds += 1000000;
    }

    cJSON_AddNumberToObject(globalJson, "remaining_time", remaining_time);
    cJSON_AddNumberToObject(globalJson, "max_room", MAX_ROOM);
    cJSON_AddNumberToObject(globalJson, "needed_money", game->needed_money);

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
    int seed, width, height;

    cJSON *seedObj = cJSON_GetObjectItem(worldObj, "seed");
    if (seedObj == NULL) {
        return NULL;
    }

    seed = seedObj->valueint;

    cJSON *widthObj = cJSON_GetObjectItem(worldObj, "width");
    if (widthObj == NULL) {
        return NULL;
    }

    width = widthObj->valueint;

    cJSON *heightObj = cJSON_GetObjectItem(worldObj, "height");
    if (heightObj == NULL) {
        return NULL;
    }

    height = heightObj->valueint;

    Game_World *world = create_world_sized(seed, width, height);

    cJSON *roomsArray = cJSON_GetObjectItem(worldObj, "rooms");

    for (int i = 0; i < cJSON_GetArraySize(roomsArray); i++) {
        cJSON *roomObj = cJSON_GetArrayItem(roomsArray, i);

        int x, y, room_width, room_height;

        cJSON *xObj = cJSON_GetObjectItem(roomObj, "x");
        if (xObj == NULL) {
            free(world);
            return NULL;
        }
        x = xObj->valueint;

        cJSON *yObj = cJSON_GetObjectItem(roomObj, "y");
        if (yObj == NULL) {
            free(world);
            return NULL;
        }
        y = yObj->valueint;

        cJSON *roomWidthObj = cJSON_GetObjectItem(roomObj, "width");
        if (roomWidthObj == NULL) {
            free(world);
            return NULL;
        }
        room_width = roomWidthObj->valueint;

        cJSON *roomHeightObj = cJSON_GetObjectItem(roomObj, "height");
        if (roomHeightObj == NULL) {
            free(world);
            return NULL;
        }
        room_height = roomHeightObj->valueint;

        bool is_visited = false;
        cJSON *isVisitedObj = cJSON_GetObjectItem(roomObj, "is_visited");
        if (isVisitedObj == NULL) {
            free(world);
            return NULL;
        }
        is_visited = isVisitedObj->valueint;

        Room *room = create_room(room_width, room_height, x, y);
        if (room == NULL) {
            free(world);
            return NULL;
        }

        room->is_visited = is_visited;

        cJSON *doorsArray = cJSON_GetObjectItem(roomObj, "doors");

        for (int j = 0; j < cJSON_GetArraySize(doorsArray); j++) {
            cJSON *doorObj = cJSON_GetArrayItem(doorsArray, j);

            int index, xd, yd, is_used;
            cJSON *indexObj = cJSON_GetObjectItem(doorObj, "index");
            if (indexObj == NULL) {
                free(world);
                return NULL;
            }
            index = indexObj->valueint;


            cJSON *dxObj = cJSON_GetObjectItem(doorObj, "x");
            if (dxObj == NULL) {
                free(world);
                return NULL;
            }
            xd = dxObj->valueint;

            cJSON *dyObj = cJSON_GetObjectItem(doorObj, "y");
            if (dyObj == NULL) {
                free(world);
                return NULL;
            }
            yd = dyObj->valueint;

            cJSON *isUsedObj = cJSON_GetObjectItem(doorObj, "is_used");
            if (isUsedObj == NULL) {
                free(world);
                return NULL;
            }
            is_used = isUsedObj->valueint;


            Door *door = room->doors[index];
            door->x = xd;
            door->y = yd;
            door->is_used = is_used;
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

        int monster_id, health, x, y;

        cJSON *monster_idObj = cJSON_GetObjectItem(monster, "monster_id");
        if (monster_idObj == NULL) {
            return NULL;
        }
        monster_id = monster_idObj->valueint;

        cJSON *healthObj = cJSON_GetObjectItem(monster, "health");
        if (healthObj == NULL) {
            return NULL;
        }
        health = healthObj->valueint;

        cJSON *xObj = cJSON_GetObjectItem(monster, "x");
        if (xObj == NULL) {
            return NULL;
        }
        x = xObj->valueint;

        cJSON *yObj = cJSON_GetObjectItem(monster, "y");
        if (yObj == NULL) {
            return NULL;
        }
        y = yObj->valueint;

        create_living_monster(world, worldMonster, monster_id, x, y, health);
    }

    return worldMonster;

}


World_Item *load_item_from_json(Game_World *world, cJSON *itemObj) {
    World_Item *worldItem = init_world_item();

    cJSON *itemsArray = cJSON_GetObjectItem(itemObj, "items");

    for (int i = 0; i < cJSON_GetArraySize(itemsArray); i++) {
        cJSON *item = cJSON_GetArrayItem(itemsArray, i);
        if (item == NULL) {
            free(worldItem);
            return NULL;
        }

        char *name;
        char *texture;
        int price, material;

        cJSON *item_stack_json = cJSON_GetObjectItem(item, "item_stack");
        if (item_stack_json == NULL) {
            free(worldItem);
            return NULL;
        }

        cJSON *nameObj = cJSON_GetObjectItem(item_stack_json, "name");
        if (nameObj == NULL) {
            free(worldItem);
            return NULL;
        }
        name = nameObj->valuestring;

        cJSON *textureObj = cJSON_GetObjectItem(item_stack_json, "texture");
        if (textureObj == NULL) {
            free(worldItem);
            return NULL;
        }
        texture = textureObj->valuestring;

        cJSON *priceObj = cJSON_GetObjectItem(item_stack_json, "price");
        if (priceObj == NULL) {
            free(worldItem);
            return NULL;
        }
        price = priceObj->valueint;

        cJSON *materialObj = cJSON_GetObjectItem(item_stack_json, "material");
        if (materialObj == NULL) {
            free(worldItem);
            return NULL;
        }
        material = materialObj->valueint;

        Item_Stack *item_stack = create_formatted_item_stack(name, texture, price, material);
        if (item_stack == NULL) {
            free(worldItem);
            return NULL;
        }

        int dx, dy;

        cJSON *xObj = cJSON_GetObjectItem(item, "x");
        if (xObj == NULL) {
            free(worldItem);
            return NULL;
        }
        dx = xObj->valueint;

        cJSON *yObj = cJSON_GetObjectItem(item, "y");
        if (yObj == NULL) {
            free(worldItem);
            return NULL;
        }
        dy = yObj->valueint;

        Dropped_Item *dropped_item = drop_item(world, worldItem, item_stack, dx, dy);
        if (dropped_item == NULL) {
            free(worldItem);
            return NULL;
        }
    }

    return worldItem;

}

Player *load_player_from_json(Game_World *world, cJSON *playerObj) {
    char *name;
    Class current_class;
    int health, max_health, exp, money, x, y;

    cJSON *nameObj = cJSON_GetObjectItem(playerObj, "name");
    if (nameObj == NULL) {
        return NULL;
    }
    name = nameObj->valuestring;

    cJSON *currentClassObj = cJSON_GetObjectItem(playerObj, "class");
    if (currentClassObj == NULL) {
        return NULL;
    }
    current_class = currentClassObj->valueint;

    cJSON *healthObj = cJSON_GetObjectItem(playerObj, "health");
    if (healthObj == NULL) {
        return NULL;
    }
    health = healthObj->valueint;

    cJSON *maxHealthObj = cJSON_GetObjectItem(playerObj, "max_health");
    if (maxHealthObj == NULL) {
        return NULL;
    }
    max_health = maxHealthObj->valueint;

    cJSON *expObj = cJSON_GetObjectItem(playerObj, "exp");
    if (expObj == NULL) {
        return NULL;
    }
    exp = expObj->valueint;

    cJSON *moneyObj = cJSON_GetObjectItem(playerObj, "money");
    if (moneyObj == NULL) {
        return NULL;
    }
    money = moneyObj->valueint;

    cJSON *xObj = cJSON_GetObjectItem(playerObj, "x");
    if (xObj == NULL) {
        return NULL;
    }

    x = xObj->valueint;

    cJSON *yObj = cJSON_GetObjectItem(playerObj, "y");
    if (yObj == NULL) {
        return NULL;
    }
    y = yObj->valueint;


    Inventory *inventory = create_inventory(INVENTORY_CAPACITY);
    if (inventory == NULL) {
        return NULL;
    }

    cJSON *inventoryArray = cJSON_GetObjectItem(playerObj, "inventory");
    for (int i = 0; i < cJSON_GetArraySize(inventoryArray); i++) {
        cJSON *item = cJSON_GetArrayItem(inventoryArray, i);
        if (item == NULL) {
            free(inventory);
            return NULL;
        }

        char *item_name;
        char *texture;
        int price, material;

        cJSON *item_nameObj = cJSON_GetObjectItem(item, "name");
        if (item_nameObj == NULL) {
            free(inventory);
            return NULL;
        }
        item_name = item_nameObj->valuestring;

        cJSON *textureObj = cJSON_GetObjectItem(item, "texture");
        if (textureObj == NULL) {
            free(inventory);
            return NULL;
        }
        texture = textureObj->valuestring;

        cJSON *priceObj = cJSON_GetObjectItem(item, "price");
        if (priceObj == NULL) {
            free(inventory);
            return NULL;
        }
        price = priceObj->valueint;

        cJSON *materialObj = cJSON_GetObjectItem(item, "material");
        if (materialObj == NULL) {
            free(inventory);
            return NULL;
        }
        material = materialObj->valueint;

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

    cJSON *maxRoom = cJSON_GetObjectItem(globalJson, "max_room");
    if (maxRoom == NULL) {
        cJSON_Delete(globalJson);
        return NULL;
    }

    if (MAX_ROOM != maxRoom->valueint) {
        cJSON_Delete(globalJson);
        return NULL;
    }

    cJSON *remainingTime = cJSON_GetObjectItem(globalJson, "remaining_time");
    if (remainingTime == NULL) {
        cJSON_Delete(globalJson);
        return NULL;
    }

    cJSON *neededMoney = cJSON_GetObjectItem(globalJson, "needed_money");
    if (neededMoney == NULL) {
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

    Player *player = load_player_from_json(world, playerObj);
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

    gettimeofday(&game->start_time, NULL);
    game->end_time.tv_sec = game->start_time.tv_sec + remaining_time;

    game->needed_money = neededMoney->valueint;
    game->world = world;
    game->world_monster = worldMonster;
    game->world_item = worldItem;
    game->player = player;

    cJSON_Delete(globalJson);

    return game;
}