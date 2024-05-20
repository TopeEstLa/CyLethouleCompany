#include <items.h>

#include <stdlib.h>

Item_Stack existing_item[2] = {
        {"Grand Axe", "A", GRAND_AXE},
        {"Bolt",      "B", BOLT},
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

    itemStack->name = existing_item[item_id].name;
    itemStack->texture = existing_item[item_id].texture;
    itemStack->material = existing_item[item_id].material;

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

    Entity* entity = get_entity(x, y);
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
    int item_seed = world->seed + room->x + room->y + room->height + room->width + world_item->dropped_items_capacity +
                    world_item->dropped_items_count + world->room_count + world->room_capacity;
    int spawn_count = random_int(
            item_seed, 1, 2);

    for (int i = 0; i < spawn_count; i++) {
        int x = random_int(item_seed + i + spawn_count, room->x + 1,
                           room->x + room->width - 1);
        int y = random_int(item_seed + i + x + spawn_count, room->y + 1,
                           room->y + room->height - 1);

        int item_id = random_int(item_seed + i, 0, ITEM_COUNT);

        Item_Stack *itemStack = create_item_stack(item_id);

        if (itemStack == NULL) {
            continue;
        }

        Dropped_Item *dropItem = drop_item(world, world_item, itemStack, x, y);

        if (dropItem == NULL) {
            continue;
        }

    }
}