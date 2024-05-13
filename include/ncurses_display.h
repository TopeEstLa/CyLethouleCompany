#ifndef TERMINAL_NCURSES_DISPLAY_H
#define TERMINAL_NCURSES_DISPLAY_H

#include <stdlib.h>

#include <world.h>
#include <entities.h>

typedef enum current_scene {
    MAIN_MENU,
    LOAD_MENU,
    GAME,
    GAME_OVER,
} Current_Scene;

void set_current_scene(Current_Scene scene);

Current_Scene get_current_scene();

void init_curses();

void handle_input();

void curses_scene();

void curses_all_map(Game_World* world);

#endif //TERMINAL_NCURSES_DISPLAY_H
