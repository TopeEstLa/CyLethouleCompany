#ifndef MONSTERS_H
#define MONSTERS_H

#include <entities.h>

typedef struct Monster {
    char name[20];
    char* texture;
    int max_health;
} Monster;

typedef struct Living_Monster {
    Monster monster;
    Entity* entity;
    int entity_id;
    int health;
} Living_Monster;

void init_monsters();

void cleanup_monsters();

Living_Monster *create_living_monster(Game_World* world, Monster monster, int x, int y);

void kill_monster(Living_Monster* monster);


#endif //MONSTERS_H
