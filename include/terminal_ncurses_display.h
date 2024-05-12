#ifndef TERMINAL_NCURSES_DISPLAY_H
#define TERMINAL_NCURSES_DISPLAY_H

#include <stdlib.h>

#include <world.h>
#include <entities.h>

void init_curses();

void curses_all_map(Game_World* world);

#endif //TERMINAL_NCURSES_DISPLAY_H
