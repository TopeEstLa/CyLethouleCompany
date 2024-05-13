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
 * Check if we redraw without waiting input.
 * @return True if we redraw without waiting input.
 */
bool is_force_redraw();

/**
 * Set if we redraw without waiting input.
 * @param force True if we redraw without waiting input.
 * @return True if we redraw without waiting input.
 */
bool set_force_redraw(bool force);

void init_curses();

void handle_input();

void curses_scene();

void curses_all_map(Game_World* world);

#endif //TERMINAL_NCURSES_DISPLAY_H
