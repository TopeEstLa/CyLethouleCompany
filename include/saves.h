#ifndef SAVES_H
#define SAVES_H

#include <stdbool.h>

#include <game_controller.h>
#include <world.h>
#include <cJSON.h>

#define FORMAT_VERSION 5
#define SAVES_FOLDER "saves/"

/**
 * Create a cJSON object from a world.
 * @param world
 * @return the cJSON object created
 */
cJSON* create_world_json(Game_World* world);

/**
 * Create a cJSON object from a monster.
 * @param worldMonster the monster to create the cJSON object from
 * @return the cJSON object created
 */
cJSON* create_monster_json(World_Monster* worldMonster);

/**
 * Create a cJSON object from an item.
 * @param worldItem the item to create the cJSON object from
 * @return the cJSON object created
 */
cJSON* create_item_json(World_Item* worldItem);

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
 * Load all monsters from a cJSON object.
 * @param monsterObj the cJSON object
 * @return all monsters loaded or NULL if an error occurred
 */
World_Monster* load_monster_from_json(Game_World* world, cJSON* monsterObj);

/**
 * Load all items from a cJSON object.
 * @param itemObj the cJSON object
 * @return all items loaded or NULL if an error occurred
 */
World_Item* load_item_from_json(Game_World* world, cJSON* itemObj);

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
