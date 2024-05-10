#ifndef TERMINAL_DISPLAY_H
#define TERMINAL_DISPLAY_H

#include <world.h>

/**
 * Print the map of the world in the terminal.
 * @param world
 */
void print_all_map(Game_World* world);

/**
 * Print the visited map of the world in the terminal.
 * @param world
 */
void print_visited_map(Game_World* world);


#endif //TERMINAL_DISPLAY_H
