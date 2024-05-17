#include <curses.h>
#include <ncurses_display.h>

#include <game_controller.h>
#include <monsters.h>

int main() {
    init_curses();

    while (get_current_scene() != QUITTING) {
        handle_input();

        if (get_current_scene() == GAME && is_game_loaded()) {
            spawn_monster(get_game_data());
        }

        curses_scene();
    }

    endwin();

    return 0;
}