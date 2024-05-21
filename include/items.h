#ifndef ITEMS_H
#define ITEMS_H

#include <entities.h>

#define ITEM_COUNT 2

typedef enum material {
    GRAND_AXE,
    BOLT,
} Material;

typedef struct item_stack {
    char *name;
    char *texture;
    int price;
    Material material;
} Item_Stack;

typedef struct dropped_item {
    Item_Stack *item;
    int dropped_id;
    Entity *entity;
} Dropped_Item;

typedef struct World_Item {
    Dropped_Item **dropped_items;
    int dropped_items_count;
    int dropped_items_capacity;
} World_Item;

World_Item *init_world_item();

Item_Stack *create_item_stack(int item_id);

Item_Stack* create_formatted_item_stack(char *name, char *texture, int price, Material material);

Dropped_Item *drop_item(Game_World *world, World_Item *world_item, Item_Stack *itemStack, int x, int y);

Item_Stack* pickup_item(World_Item *world_item, int dropped_id);

void spawn_item(World_Item *world_item, Game_World *world, Room *room);


#endif //ITEMS_H
