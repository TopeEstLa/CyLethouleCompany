#ifndef MONSTERS_H
#define MONSTERS_H

#include <entities.h>
#include <player.h>
#include <world.h>

typedef struct Monster {
    char name[20];
    char *texture;
    int max_health;
    Class class;
} Monster;

typedef struct Living_Monster {
    Monster monster;
    int monster_id;
    int living_id;
    Entity *entity;
    int health;
} Living_Monster;

typedef struct World_Monster {
    Living_Monster **living_monsters;
    int living_monsters_count;
    int living_monsters_capacity;
} World_Monster;

World_Monster *init_world_monster();

int get_random_monster(int seed);

Living_Monster *create_living_monster(Game_World *world, World_Monster *world_monster, int monster_id, int x, int y, int health);

void kill_monster(World_Monster *world_monster, int monster_id);

void spawn_monster(World_Monster *worldMonster, Game_World *world, Room *room);

//void move_monster(Game_Data *game_data);


#endif //MONSTERS_H
