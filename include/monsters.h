#ifndef MONSTERS_H
#define MONSTERS_H

#include <entities.h>
#include <game_controller.h>

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

Monster get_random_monster(int seed);

Living_Monster *create_living_monster(Game_World* world, Monster monster, int x, int y);

void kill_monster(Living_Monster* monster);

void spawn_monster(Game_Data *game_data);


#endif //MONSTERS_H
