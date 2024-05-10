#ifndef SAVES_H
#define SAVES_H

#include <stdbool.h>

#include <world.h>

#define FORMAT_VERSION 1
#define FOLDER "saves/"

/**
 * Save the world in a file.
 * @param world the world to save
 * @param filename the name of the file
 * @return true if the world has been saved, false otherwise
 */
bool save_world(Game_World *world, char *filename);

/**
 * Load a world from a file.
 * @param filename the name of the file
 * @return the world loaded or NULL if an error occurred
 */
Game_World* load_world(char *filename);

#endif //SAVES_H
