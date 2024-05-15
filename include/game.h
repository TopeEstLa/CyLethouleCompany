#ifndef GAME_H
#define GAME_H

#include <world.h>
#include <player.h>

typedef struct game {
    Game_World *world;
    Player *player;
} Game;

void set_game(Game *game);

Game *get_game();

void init_game(int seed, char* name, Class current_class);

void move_player(int x, int y);

#endif //GAME_H
