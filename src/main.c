#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

#include <world.h>
#include <ncurses_display.h>
#include <terminal_display.h>
#include <world_generator.h>
#include <entities.h>
#include <file_utils.h>
#include <saves.h>
#include <frame_rate.h>


int main() {
    srand(time(NULL));
    Game_World *world = create_world(rand() % 1000);

    init_entities(world);

    base_generation(world);

    Entity *player = create_entity(PLAYER, NULL, '@');

    add_entity(player, world->rooms[0].x + 3, world->rooms[0].y + 3);

    init_curses();

    if (create_folder(SAVES_FOLDER)) {
        //printf("Folder created successfully\n");
    } else {
        //printf("Folder could not be created\n");
    }

    save_world(world, "saves/world.json");


    int shouldQuit = 0;
    set_force_redraw(true);
    while (shouldQuit == 0) {
        start_frame();
        if (!is_force_redraw())
            handle_input();

        if (is_force_redraw())
            set_force_redraw(false);

        curses_scene();

        end_frame();
    }

    endwin();

    return 0;
}
