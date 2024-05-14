#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

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
void printMap(Game_World** tab, int x, int y, int dx, int dy, int height, int width){
    if (tab == NULL || x < 0 || x > width || y < 0 || y > height){
        exit(404);
    }
    for (int i = y - dy; i <= y + dy; i++){
        if (tab[i] == NULL || i < 0 || i > height){

        } else {
            for (int j = x - dx; j <= x + dx; j++) {
                Entity *entity = get_entity(x, y);
                if (j < 0 || j > width) {

                } else {
                    //print the item to stack or the emoji of the player
                    if (entity != NULL){
                        printw("  %s", entity->texture);
                    }else {
                        //print the map : door, wall, etc ...
                        switch (tab->chunk[i][j]->type) {
                            case DOOR :
                                printw("  D ");
                                break;
                            case WALL :
                                printw("  | ");
                                break;
                            case void :
                                printw("    ");
                                break;
                            case EMPTY :
                                printw("    ");
                                break;
                            case default :
                                printw("  ? ",);
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