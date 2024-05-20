#ifndef PLAYER_H
#define PLAYER_H

#include <entities.h>
#include <items.h>

#define INVENTORY_CAPACITY 3

typedef enum class {
    ARCHER,
    WIZARD,
    WARRIOR,
} Class;

typedef struct inventory {
    Item_Stack** items;
    int index;
    int capacity;
} Inventory;

typedef struct player {
    Entity* entity;
    char* name;
    Inventory* inventory;
    Class current_class;
    int health;
    int max_health;
    int exp;
} Player;

Player* create_player(Game_World* world, char* name, Class current_class);

Player* load_player(Game_World* world, char* name, Inventory* inventory, Class current_class, int health, int max_health, int exp, int x, int y);

Inventory* create_inventory(int capacity);

void add_item_to_inventory(Inventory* inventory, Item_Stack* item_stack);


#endif //PLAYER_H
