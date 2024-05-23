#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include <world.h>
#include <player.h>
#include <monsters.h>
#include <items.h>
#include <unistd.h>
#include <sys/time.h>

#include <time.h>
#include <constant.h>

#define GAME_DURATION_SECONDS (GAME_DURATION * 60)

/**
 * Represents all data stored for the game
 * @param start_time The time when the game started
 * @param end_time The time when the game will end
 * @param needed_money The money needed to win the game = QUOTA
 * @param world The world of the game
 * @param world_monster The monsters array list depending on the world
 * @param world_item The items array list depending on the world
 * @param player The player
 */
typedef struct game_data {
    struct timeval start_time;
    struct timeval end_time;
    int needed_money;
    Game_World *world;
    World_Monster *world_monster;
    World_Item *world_item;
    Player *player;
} Game_Data;

/**
 * Return the current game data or null if no game is loaded
 * @return game data
 */
Game_Data* get_game_data();

/**
 * Set the current game data
 * @param game_data The game data to set
 */
void set_game_data(Game_Data *game_data);

/**
 * Check if a game is loaded
 * @return true if a game is loaded
 */
bool is_game_loaded();

/**
 * Prepare the game
 */
void prepare_game();

/**
 * Load a game from a save file
 * @param game_data The game data to load
 */
void loaded_game(Game_Data *game_data);

/**
 * Create a new game
 * @param seed seed for the random generation
 * @param name player name
 * @param current_class player class
 */
void create_game(int seed, char* name, Class current_class);

/**
 * Unload the current game
 * or do nothing if no game is loaded
 */
void unload_game();

/**
 * Update the game
 * TODO: move monster
 * Currently : check if time is over, if quota is reached
 */
void update_game();

/**
 * Get the remaining time in seconds
 * @return remaining time in seconds
 */
int get_remaining_time();

/**
 * Get the remaining time in minutes
 * @return remaining time in minutes
 */
bool is_needed_money_reached();

/**
 * Move the player to a new position
 * @param x new x position
 * @param y new y position
 */
void move_player(int x, int y);

#endif //GAME_H
