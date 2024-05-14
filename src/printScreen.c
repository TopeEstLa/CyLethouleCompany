#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "entities.h"
#include "world.h"

//Print the timer on the terminal
WINDOW* printTimer(struct timeval current) {

    start_color();
    WINDOW *win = newwin(1, 12, 1, 1);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    struct timeval tv;
    gettimeofday(&tv, NULL);
    //save the actual timeofday
    int difference = tv.tv_sec - current.tv_sec;
    //Print in red if the difference is under 10 seconds
    if (difference <= 10){
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 0, "%3d", difference);
        wattroff(win, COLOR_PAIR(1));
    } else {
        mvwprintw(win, 0, 0, "%3d", difference);
    }
    wrefresh(win);
    return win;
}

//Print the map on the terminal
void printMap(Game_World* world, int x, int y, int dx, int dy){
    if (world == NULL || x < 0 || x > world->width || y < 0 || y > world->height){
        exit(404);
    }
    for (int i = y - dy; i < y + dy; i++){
        if (i < 0 || i > world->height){
            continue;
        } else {
            for (int j = x - dx; j < x + dx; j++) {
                if (j < 0 || j > world->width) {
                    continue;
                } else {
                    Entity *entity = get_entity(x, y);

                    //print the item to stack or the emoji of the player
                    if (entity != NULL){
                        printw("  %s", entity->texture);
                    }else {
                        //print the map : door, wall, etc ...
                        switch (world->chunk[j][i]->type) {
                            case DOOR :
                                printw("  D ");
                                break;
                            case WALL :
                                printw("  | ");
                                break;
                            case VOID :
                                printw("    ");
                                break;
                            case EMPTY :
                                printw("    ");
                                break;
                            default :
                                printw("  ? ");
                                break;
                        }
                    }
                }
            }
            printw("\n");
        }
    }
    refresh();
}
WINDOW* printInventary(){


    WINDOW* win = newwin(10, 2, 1, 1);


    return win;
}