#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include <world.h>
#include <player.h>
#include <monsters.h>
#include <items.h>

#include <time.h>

#define GAME_DURATION 10 //in minutes

typedef struct game_data {
    clock_t start_time;
    clock_t end_time;
    Game_World *world;
    World_Monster *world_monster;
    World_Item *world_item;
    Player *player;
} Game_Data;

Game_Data* get_game_data();

void set_game_data(Game_Data *game_data);

bool is_game_loaded();

void prepare_game();

void loaded_game(Game_Data *game_data);

void create_game(int seed, char* name, Class current_class);

void unload_game();

void update_game();

int get_remaining_time();

void move_player(int x, int y);

#endif //GAME_H
