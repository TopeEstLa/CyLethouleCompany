#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

void flushStdIn(){
    int  a;
    char c;
    do{
        a = scanf("%c", &c);
    } while(a==1 && c != '\n' );
}

WINDOW* printTimer(int* time){


    WINDOW * win = newwin(1, 12, 1, 1);


    while (*time >= 0){
        mvwprintw(win, 0, 0, "%3d", *time);
        wrefresh(win);
        *time = *time - 1;
        sleep(1);
    }


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