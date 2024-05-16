#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdlib.h>

#include <game_controller.h>
#include <world.h>
#include <player.h>
#include <entities.h>

void free_world(Game_World *world);

void free_player(Player *player);

void free_game_data(Game_Data *game_data);

#endif //MEMORY_UTILS_H
