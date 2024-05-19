#include <curses.h>
#include <ncurses_display.h>

#include <game_controller.h>
#include <monsters.h>

int main() {
    init_curses();

    while (get_current_scene() != QUITTING) {
        handle_input();
        clear();

        update_game();

        curses_scene();
        refresh();
    }

    endwin();

    return 0;
}