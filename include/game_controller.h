#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include <world.h>
#include <player.h>

typedef struct game_data {
    Game_World *world;
    Player *player;
} Game_Data;

Game_Data* get_game_data();

void set_game_data(Game_Data *game_data);

bool is_game_loaded();

void prepare_game();

void loaded_game(Game_Data *game_data);

void create_game(int seed, char* name, Class current_class);

void unload_game();

void move_player(int x, int y);

#endif //GAME_H
