#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <sys/time.h>

#include <world.h>
#include <ncurses_display.h>
#include <terminal_display.h>
#include <world_generator.h>
#include <entities.h>
#include <file_utils.h>
#include <saves.h>
#include <game_controller.h>
#include "printScreen.h"
#include <unistd.h>


int main() {
    init_curses();
    
    while (get_current_scene() != QUITTING) {
        handle_input();

        curses_scene();
    }

    endwin();

    return 0;
}