#include <curses.h>
#include <ncurses_display.h>

#include <game_controller.h>
#include <file_utils.h>

int main() {
    init_curses();
    create_folder("saves");

    while (get_current_scene() != QUITTING) {
        handle_input();

        update_game();

        curses_scene();
    }

    endwin();

    return 0;
}