#ifndef ITEMS_H
#define ITEMS_H

#include <entities.h>

#define ITEM_COUNT 2

/**
 * Material item type (Like Minecraft)
 */
typedef enum material {
    GRAND_AXE,
    BOLT,
} Material;

/**
 * Item stack structure
 * @param name the display name of the item
 * @param texture the texture of the item
 * @param price the price of the item for selling it in the shop and advancing to the QUOTA
 * @param material the material of the item
 */
typedef struct item_stack {
    char *name;
    char *texture;
    int price;
    Material material;
} Item_Stack;

/**
 * Dropped item structure is the item that is on the floor
 * @param item the item stack
 * @param dropped_id the id of the dropped item in the World_Item arraylist
 * @param entity the entity that represent the item
 */
typedef struct dropped_item {
    Item_Stack *item;
    int dropped_id;
    Entity *entity;
} Dropped_Item;

/**
 * World item structure
 * Its a arraylist like only for dropped items
 * @param dropped_items the list/tab of dropped items
 * @param dropped_items_count the count of dropped items
 * @param dropped_items_capacity the capacity of dropped items
 */
typedef struct World_Item {
    Dropped_Item **dropped_items;
    int dropped_items_count;
    int dropped_items_capacity;
} World_Item;

/**
 * Create a new world item
 * @return a new world item or NULL if an error occurred
 */
World_Item *init_world_item();

/**
 * Create a new item_stack from a template defined in items.c
 * @param item_id template id
 * @return the new Item_Stack instance or NULL if an error occurred
 */
Item_Stack *create_item_stack(int item_id);

/**
 * Create a new item_stack from a field (used for save loading)
 * @param name display name
 * @param texture texture
 * @param price price
 * @param material material
 * @return
 */
Item_Stack* create_formatted_item_stack(char *name, char *texture, int price, Material material);

/**
 * Drop an item on the floor of the world
 * @param world World of the game
 * @param world_item The world item
 * @param itemStack Item to drop
 * @param x coordinate
 * @param y coordinate
 * @return Dropped ITem instance or NULL if an error occurred
 */
Dropped_Item *drop_item(Game_World *world, World_Item *world_item, Item_Stack *itemStack, int x, int y);

/**
 * Pickup an item from the floor
 * @param world_item World of the game
 * @param dropped_id The index to pick in the world array/list/tab
 * @return
 */
Item_Stack* pickup_item(World_Item *world_item, int dropped_id);

/**
 * Spawn items in a room of the world
 * @param world_item items list where we add the items
 * @param world the world where we spawn the items
 * @param room the target room
 */
void spawn_item(World_Item *world_item, Game_World *world, Room *room);

/**
 * Estimate total value of the items in the world
 * @param world_item the world item
 * @return total value
 */
int estimate_value_in_world(World_Item *world_item);

#endif //ITEMS_H
