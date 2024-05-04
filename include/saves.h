#ifndef SAVES_H
#define SAVES_H

#include <stdbool.h>

#include <world.h>

#define FORMAT_VERSION 1
#define FOLDER "saves/"

bool save_world(Game_World *world, char *filename);

Game_World* load_world(char *filename);

#endif //SAVES_H
