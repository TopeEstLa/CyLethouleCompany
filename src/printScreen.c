#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


WINDOW* printTimer(struct timeval current) {
    start_color();
    WINDOW *win = newwin(1, 12, 1, 1);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int difference = tv.tv_sec - current.tv_sec;
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

WINDOW* printMap(char** tab, int x, int y, int dx, int dy, int height, int width){


    if (tab == NULL || x < 0 || x > width || y < 0 || y > height){

        exit(404);
    }


    WINDOW* win = newwin(2*dy, 2*dx, 1, 1);


    for (int i = y - dy; i <= y + dy; i++){

        if (tab[i] == NULL || i < 0 || i > height){

        } else {

            for (int j = x - dx; j <= x + dx; j++) {
                if (j < 0 || j > width) {

                } else {
                    mvwprintw(win, i - (y - dy), j - (x - dx), "%c", tab[i][j]);
                }
            }

            printw("\n");
        }

    }


    wrefresh(win);
    return win;
}
WINDOW* printInventary(){


    WINDOW* win = newwin(10, 2, 1, 1);


    return win;
}
int main() {


    initscr();
    printTimer();
    printMap(tab, 0, 0, 2, 2, 20, 20);

    return 0;
}