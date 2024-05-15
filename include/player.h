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
    char* name;
    Class current_class;
    int health;
    int exp;
} Player;

Player* create_player(Game_World* world, char* name, Class current_class);


#endif //PLAYER_H
