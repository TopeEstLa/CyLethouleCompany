#ifndef PLAYER_H
#define PLAYER_H

#include <entities.h>
#include <items.h>

/**
 * The class of the player.
 */
typedef enum class {
    ARCHER,
    WIZARD,
    WARRIOR,
    MONSTER_CLASS,
} Class;

/**
 * The inventory of the player.
 * @param items the items in the inventory
 * @param index the index of the next item to add
 * @param capacity the capacity of the inventory used by constant INVENTORY_CAPACITY
 */
typedef struct inventory {
    Item_Stack **items;
    int index;
    int capacity;
} Inventory;

/**
 * The player struct.
 * @param entity the entity of the player
 * @param name the name of the player
 * @param inventory the inventory of the player
 * @param current_class the class of the player
 * @param health the current health of the player
 * @param max_health the max health of the player
 * @param exp the experience of the player
 * @param money the money of the player
 */
typedef struct player {
    Entity *entity;
    char *name;
    Inventory *inventory;
    Class current_class;
    int health;
    int max_health;
    int exp;
    int money;
} Player;

/**
 * Create a new player.
 * @param world world of the player
 * @param name name of the player
 * @param current_class class of the player
 * @return the player created or NULL if an error occurred
 */
Player *create_player(Game_World *world, char *name, Class current_class);

/**
 * Load a player from a save.
 * @param world world of the player
 * @param name name of the player
 * @param inventory inventory of the player
 * @param current_class class of the player
 * @param health the current health of the player
 * @param max_health the max health of the player
 * @param exp the experience of the player
 * @param money the money of the player
 * @param x coordinate
 * @param y coordinate
 * @return the player loaded or NULL if an error occurred
 */
Player *load_player(Game_World *world, char *name, Inventory *inventory, Class current_class, int health, int max_health,
            int exp, int money, int x, int y);

/**
 * Create a new inventory.
 * @param capacity capacity of the inventory
 * @return the inventory created or NULL if an error occurred
 */
Inventory *create_inventory(int capacity);

/**
 * Add an item to the inventory.
 * @param inventory the inventory to add the item to
 * @param item_stack the item to add
 */
void add_item_to_inventory(Inventory *inventory, Item_Stack *item_stack);

/**
 * Remove an item from the inventory.
 * @param inventory the inventory to remove the item from
 * @param index the index of the item to remove
 * @return true if the item has been removed, false otherwise
 */
bool remove_item_from_inventory(Inventory *inventory, int index);

/**
 * Have space in the inventory.
 * @param player the player to check
 * @return true if the player has space in the inventory, false otherwise
 */
bool have_space(Player *player);

/**
 * Manage the player death.
 * @param world the world of the player
 * @param player the player to manage the death
 */
void player_death(Game_World* world, Player *player);


#endif //PLAYER_H
