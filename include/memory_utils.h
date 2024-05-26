#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdlib.h>

#include <game_controller.h>
#include <world.h>
#include <player.h>
#include <entities.h>

/**
 * Clean the memory of the world struct
 * @param world The world to free
 */
void free_world(Game_World *world);

/**
 * Clean the memory of a monster struct
 * @param monster The monster to free
 */
void free_monster(World_Monster *monster);

/**
 * Clean the memory of an item struct
 * @param item
 */
void free_item(World_Item *item);

/**
 * Clean the memory of a player struct
 * @param player The player to free
 */
void free_player(Player *player);

/**
 * Clean the memory of a game data struct
 * @param game_data The game data to free
 */
void free_game_data(Game_Data *game_data);

#endif //MEMORY_UTILS_H
