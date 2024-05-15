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
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long t = tv.tv_sec;
    initscr();
    //while(1){
        srand(time(NULL));
        Game_World *world = create_world(rand() % 1000);
        //printf("Generated world with seed: %d\n", world->seed);


        init_entities(world);


        base_generation(world);


        Entity *player = create_entity(PLAYER, NULL, "🗿");


        add_entity(player, world->rooms[0].x + 3, world->rooms[0].y + 3);

        printTimer(t);

        printMap(world, world->rooms[0].x + 3, world->rooms[0].y + 3, 20, 10);

        /**
        while (get_current_scene() != QUITTING) {
            //start_frame(); //useless lol :c (if using timeout());
            handle_input();

            curses_scene();

            //end_frame();
        } */

        refresh();


    //}
    getch();
    endwin();
    //clear();


    return 0;
}
