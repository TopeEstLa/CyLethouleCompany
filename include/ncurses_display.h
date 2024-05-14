#ifndef TERMINAL_NCURSES_DISPLAY_H
#define TERMINAL_NCURSES_DISPLAY_H

#include <stdlib.h>
#include <stdbool.h>

#include <world.h>
#include <entities.h>

/**
 * The current scene we drawing in the terminal.
 */
typedef enum current_scene {
    MAIN_MENU,
    LOAD_MENU,
    GAME,
    GAME_OVER,
    QUITTING,
} Current_Scene;

/**
 * Set the current scene.
 * @param scene The scene to set.
 */
void set_current_scene(Current_Scene scene);

/**
 * Get the current scene.
 * @return The current scene.
 */
Current_Scene get_current_scene();

void init_curses();

void handle_input();

void curses_scene();

void curses_all_map(Game_World* world);

void curses_visited_map(Game_World* world);

#endif //TERMINAL_NCURSES_DISPLAY_H
