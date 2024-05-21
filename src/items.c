#include <items.h>

#include <stdlib.h>
#include <string.h>
#include <constant.h>
#include <game_controller.h>
#include <shop.h>

Item_Stack existing_item[2] = {
        {"Grand Axe", "A", 20, GRAND_AXE},
        {"Bolt",      "B", 30, BOLT},
};

World_Item *init_world_item() {
    World_Item *world_item = malloc(sizeof(World_Item));
    if (world_item == NULL) {
        return NULL;
    }

    world_item->dropped_items = malloc(sizeof(Dropped_Item *) * 10);
    if (world_item->dropped_items == NULL) {
        free(world_item);
        return NULL;
    }

    world_item->dropped_items_count = 0;
    world_item->dropped_items_capacity = 10;

    return world_item;
}

Item_Stack *create_item_stack(int item_id) {
    if (item_id < 0 || item_id >= ITEM_COUNT) {
        return NULL;
    }

    Item_Stack *itemStack = malloc(sizeof(Item_Stack));
    if (itemStack == NULL) {
        return NULL;
    }

    itemStack->name = malloc(strlen(existing_item[item_id].name) + 1);
    strcpy(itemStack->name, existing_item[item_id].name);
    itemStack->texture = malloc(strlen(existing_item[item_id].texture) + 1);
    strcpy(itemStack->texture, existing_item[item_id].texture);
    itemStack->material = existing_item[item_id].material;
    itemStack->price = existing_item[item_id].price;

    return itemStack;
}

Item_Stack *create_formatted_item_stack(char *name, char *texture, int price, Material material) {
    Item_Stack *itemStack = malloc(sizeof(Item_Stack));
    if (itemStack == NULL) {
        return NULL;
    }

    itemStack->name = malloc(strlen(name) + 1);
    strcpy(itemStack->name, name);
    itemStack->texture = malloc(strlen(texture) + 1);
    strcpy(itemStack->texture, texture);
    itemStack->price = price;
    itemStack->material = material;

    return itemStack;
}

Dropped_Item *drop_item(Game_World *world, World_Item *world_item, Item_Stack *item_stack, int x, int y) {
    if (world_item->dropped_items_count >= world_item->dropped_items_capacity) {
        return NULL;
    }

    Dropped_Item *dropped_item = malloc(sizeof(Dropped_Item));
    if (dropped_item == NULL) {
        return NULL;
    }

    dropped_item->item = item_stack;
    dropped_item->dropped_id = world_item->dropped_items_count;
    dropped_item->entity = create_entity(ITEM, dropped_item, item_stack->texture);

    Entity *entity = get_entity(x, y);
    if (entity != NULL) {
        free(dropped_item);
        return NULL;
    }

    int id = add_entity(world, dropped_item->entity, x, y);
    if (id == -1) {
        free(dropped_item);
        return NULL;
    }

    world_item->dropped_items[world_item->dropped_items_count] = dropped_item;
    world_item->dropped_items_count++;

    return dropped_item;
}

Item_Stack *pickup_item(World_Item *world_item, int dropped_id) {
    if (world_item == NULL) {
        return NULL;
    }

    if (dropped_id < 0 || dropped_id >= world_item->dropped_items_count) {
        return NULL;
    }

    Dropped_Item *dropped_item = world_item->dropped_items[dropped_id];
    if (dropped_item == NULL) {
        return NULL;
    }

    Item_Stack *item_stack = dropped_item->item;

    bool success = remove_entity(dropped_item->entity->index);

    if (success) {
        int index = dropped_item->dropped_id;
        free(world_item->dropped_items[index]);
        for (int i = index; i < world_item->dropped_items_count - 1; i++) {
            world_item->dropped_items[i] = world_item->dropped_items[i + 1];
            world_item->dropped_items[i]->dropped_id = i;
        }
        world_item->dropped_items_count--;
    } else {
        return NULL;
    }

    return item_stack;
}

void spawn_item(World_Item *world_item, Game_World *world, Room *room) {
    if (!is_game_loaded()) return;
    Game_Data *game = get_game_data();

    int item_seed = world->seed + room->x + room->y + room->height + room->width + world_item->dropped_items_capacity +
                    world_item->dropped_items_count + world->room_count + world->room_capacity;

    int spawn_count = 0;
    if (MAX_ROOM != -1) {
        spawn_count = random_int(
                item_seed, 4, 9); //dopping item spawn to ensure that the player can get the quota
    } else if (count_visited_rooms(world) < 7) {
        spawn_count = random_int(item_seed, 0, 2);
    } else {
        int estimated_value = estimate_value_in_world(world_item);
        int start_needed_money = game->needed_money;
        int actual_money = game->player->money;
        int inventory_value = estimate_inventory_value(game->player);

        int needed_money = start_needed_money - actual_money - estimated_value - inventory_value;
        if (needed_money <= 0) {
            spawn_count = random_int(item_seed, 0, 3);
        } else {
            if (needed_money < 50) {
                spawn_count = random_int(item_seed, 0, 1);
            } else if (needed_money < 100) {
                spawn_count = random_int(item_seed, 1, 3);
            } else {
                spawn_count = random_int(item_seed, 2, 5);
            }
        }
    }


    int try = 0;
    int spawned = 0;

    while (try < spawn_count+20 && spawned < spawn_count) {
        int x = random_int(item_seed + try, room->x + 1, room->x + room->width - 1);
        int y = random_int(item_seed + try + x, room->y + 1, room->y + room->height - 1);

        int item_id = random_int(item_seed + try, 0, ITEM_COUNT);

        Item_Stack *itemStack = create_item_stack(item_id);

        if (itemStack == NULL) {
            try++;
            continue;
        }

        Dropped_Item *dropItem = drop_item(world, world_item, itemStack, x, y);

        if (dropItem == NULL) {
            try++;
            continue;
        }

        try++;
        spawned++;
    }
}

int estimate_value_in_world(World_Item *world_item) {
    int value = 0;
    for (int i = 0; i < world_item->dropped_items_count; i++) {
        value += world_item->dropped_items[i]->item->price;
    }
    return value;
}