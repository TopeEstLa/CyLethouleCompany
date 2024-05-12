#ifndef TERMINAL_NCURSES_DISPLAY_H
#define TERMINAL_NCURSES_DISPLAY_H

#include <stdlib.h>

#include <world.h>
#include <entities.h>

typedef enum current_scene {
    MAIN_MENU,
    GAME,
    GAME_OVER,
} Current_Scene;


void init_curses();

void curses_all_map(Game_World* world);

#endif //TERMINAL_NCURSES_DISPLAY_H
