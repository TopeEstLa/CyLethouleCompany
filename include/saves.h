#ifndef SAVES_H
#define SAVES_H

#include <stdbool.h>

#include <game_controller.h>
#include <world.h>
#include <cJSON.h>

#define FORMAT_VERSION 3
#define SAVES_FOLDER "saves/"

/**
 * Create a cJSON object from a world.
 * @param world
 * @return the cJSON object created
 */
cJSON* create_world_json(Game_World* world);

/**
 * Save the world in a file.
 * @param world the world to save
 * @param filename the name of the file
 * @return true if the world has been saved, false otherwise
 */
bool save_world(Game_World *world, char *filename);

/**
 * Save the game in a file.
 * @param game
 * @param save_name
 * @return true if the game has been saved, false otherwise
 */
bool save_game(Game_Data *game, char *save_name);

/**
 * Load a world from a cJSON object.
 * @param worldObj the cJSON object
 * @return the world loaded or NULL if an error occurred
 */
Game_World* load_world_from_json(cJSON* worldObj);

/**
 * Load a world from a file.
 * @param filename the name of the file
 * @return the world loaded or NULL if an error occurred
 */
Game_World* load_world(char *filename);

/**
 * Load a game from a file.
 * @param save_name the name of the save
 * @return the game loaded or NULL if an error occurred
 */
Game_Data* load_game(char* save_name);


#endif //SAVES_H
