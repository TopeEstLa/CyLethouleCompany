#include <curses.h>
#include <ncurses_display.h>


int main() {
    init_curses();

    while (get_current_scene() != QUITTING) {
        handle_input();

        curses_scene();
    }

    endwin();

    return 0;
}