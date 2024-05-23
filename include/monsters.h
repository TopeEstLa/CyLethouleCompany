#ifndef MONSTERS_H
#define MONSTERS_H

#include <entities.h>
#include <player.h>
#include <world.h>

/**
 * Struct monster "type"
 * @param name the name of the monster
 * @param texture the texture of the monster
 * @param max_health the max health of the monster
 * @param class the class of the monster for fight
 */
typedef struct Monster {
    char name[20];
    char *texture;
    int max_health;
    Class class;
} Monster;

/**
 * Representing monster in the world
 * @param monster the monster type
 * @param monster_id the id of the monster
 * @param living_id the index in the World_Monster array/list/tab
 * @param entity the entity that represent the monster
 * @param health the current health of the monster
 */
typedef struct Living_Monster {
    Monster monster;
    int monster_id;
    int living_id;
    Entity *entity;
    int health;
} Living_Monster;

/**
 * An ArrayList like for monsters
 * @param living_monsters the list/tab of living monsters
 * @param living_monsters_count the count of living monsters
 * @param living_monsters_capacity the capacity of living monsters
 */
typedef struct World_Monster {
    Living_Monster **living_monsters;
    int living_monsters_count;
    int living_monsters_capacity;
} World_Monster;

/**
 * Init the world monster with 10 capacity
 * @return a new world monster or NULL if an error occurred
 */
World_Monster *init_world_monster();

/**
 * Get a random monster template
 * @param seed the seed for the random generation
 * @return a random monster id
 */
int get_random_monster(int seed);

/**
 * Create a new living monster in the world
 * @param world the new world
 * @param world_monster the monster array list depending on the world
 * @param monster_id the id of monster template
 * @param x coordinate
 * @param y coordinate
 * @param health current health (if -1 the max health of the monster)
 * @return Living_Monster instance or NULL if an error occurred
 */
Living_Monster *create_living_monster(Game_World *world, World_Monster *world_monster, int monster_id, int x, int y, int health);

/**
 * Kill a monster in the world
 * @param world_monster the monster array list depending on the world
 * @param monster_id the index of the monster in the array/list/tab
 */
void kill_monster(World_Monster *world_monster, int monster_id);

/**
 * Spawn a monster in the world
 * @param worldMonster the monster array list depending on the world
 * @param world the world of the game
 * @param room the room where the monster will spawn
 */
void spawn_monster(World_Monster *worldMonster, Game_World *world, Room *room);

//void move_monster(Game_Data *game_data);


#endif //MONSTERS_H
