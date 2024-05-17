#ifndef PLAYER_H
#define PLAYER_H

#include <entities.h>

typedef enum class {
    ARCHER,
    WIZARD,
    WARRIOR,
} Class;

typedef struct player {
    Entity* entity;
    int entity_id;
    char* name;
    Class current_class;
    int health;
    int max_health;
    int exp;
} Player;

Player* create_player(Game_World* world, char* name, Class current_class);

Player* load_player(Game_World* world, char* name, Class current_class, int health, int max_health, int exp, int x, int y);

#endif //PLAYER_H
