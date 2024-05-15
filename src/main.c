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
#include <frame_rate.h>
#include "printScreen.h"


int main() {

    initscr();
/*
    while (get_current_scene() != QUITTING) {
        //start_frame(); //useless lol :c (if using timeout());
        handle_input();

        curses_scene();

        //end_frame();
    }
*/
    //while(1){
        //clear();
        srand(time(NULL));
        Game_World *world = create_world(412);
        printf("%d\n", (*world).height);
        init_entities(world);

        init_curses();

        base_generation(world);


        Entity *player = create_entity(PLAYER, NULL, "🗿");

        add_entity(player, world->rooms[0].x + 3, world->rooms[0].y + 3);

        //printName();
        //printTimer(t);

        printf("seed %d\n", world->seed);
        printf("%d\n", (*world).height);
        //printMap(world, world->rooms[0].x + 3, world->rooms[0].y + 3, 35, 20);
        //refresh();
        free(world);
    //}


    while (1){

    }
    endwin();

    return 0;
}
