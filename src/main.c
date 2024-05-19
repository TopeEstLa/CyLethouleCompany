#include <curses.h>
#include <ncurses_display.h>

#include <game_controller.h>
#include <unistd.h>

int main() {
    init_curses();

    while (get_current_scene() != QUITTING) {
        handle_input();

        update_game();

        curses_scene();
    }

    endwin();

    return 0;
}