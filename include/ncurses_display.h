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
    CREATE_MENU,
    PAUSE_MENU,
    GAME,
    SHOP_MENU,
    FIGHT_SHOP,
    FIGHT_MENU,
    WIN,
    GAME_OVER,
    TIME_OVER,
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

/**
 * Initialize the ncurses library.
 */
void init_curses();

/**
 * Handle the input for the current scene.
 */
void handle_input();

/**
 * Draw the current scene.
 */
void curses_scene();

/**
 * Draw the game world.
 * @param world The game world to draw.
 */
void curses_all_map(Game_World* world);

/**
 * Draw the visited map.
 * @param world
 */
void curses_visited_map(Game_World* world);

#endif //TERMINAL_NCURSES_DISPLAY_H
