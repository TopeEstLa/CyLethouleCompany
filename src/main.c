#include <curses.h>
#include <ncurses_display.h>

#include <game_controller.h>
#include <monsters.h>

int main() {
    init_curses();

    //create_game(12, "aa", WARRIOR);
    //set_current_scene(GAME);

    while (get_current_scene() != QUITTING) {
        handle_input();

        /*if (get_current_scene() == GAME && is_game_loaded()) {
            spawn_monster(get_game_data()->world);
        }*/

        curses_scene();
    }

    endwin();

    return 0;
}