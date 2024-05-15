#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>


#include "entities.h"
#include "world.h"
void printName(){
    int lignes, colonnes;
    char* tab[] = {
            " _             _    _                    _         _____",
            "| |           | |  | |                  | |       / ____|",
            "| |       ___ | |_ | |__    ___   _   _ | |  ___ | |       ___   _ __ ___   _ __    __ _  _ __   _   _",
            "| |      / _ \\| __|| '_ \\  / _ \\ | | | || | / _ \\| |      / _ \\ | '_ ` _ \\ | '_ \\  / _` || '_ \\ | | | |",
            "| |____ |  __/| |_ | | | || (_) || |_| || ||  __/| |____ | (_) || | | | | || |_) || (_| || | | || |_| |",
            "|______| \\___| \\__||_| |_| \\___/  \\__,_||_| \\___| \\_____| \\___/ |_| |_| |_|| .__/  \\__,_||_| |_| \\__, |",
            "                                                                           | |                    __/ |",
            "                                                                           |_|                   |___/",
    };
    getmaxyx(stdscr, lignes, colonnes);
    int colonnes_text = strlen(tab[3]);
    int colonnes_debut = (colonnes - colonnes_text) / 2;
    int lignes_debut = 1;
    for (int i = 0; i < 8; i++){
        mvprintw(lignes_debut, colonnes_debut, "%s", tab[i]);
        lignes_debut++;
    }

}
//Print the timer on the terminal
void printTimer(long start) {
    unsigned int lignes, colonnes;
    char* tab[] ={
            "TIMER :",
    };
    start_color();
    getmaxyx(stdscr, lignes, colonnes);
    unsigned int colonnes_text = 3;
    unsigned int colonnes_debut = (colonnes) - strlen(tab[0]) - 8;
    sleep(2);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    struct timeval tv;
    gettimeofday(&tv, NULL);
    //save the actual timeofday
    long difference = tv.tv_sec - start;
    //Print in red if the difference is under 10 seconds
    if (difference <= 10){
        attron(A_BOLD);
        attron(COLOR_PAIR(1));
        mvprintw(3, colonnes_debut, " %s %3ld", tab[0],difference);
        attroff(COLOR_PAIR(1));
        attroff(A_BOLD);
    } else {
        mvprintw(3, colonnes_debut, "TIMER : %3ld", difference);
    }
    refresh();

}

//Print the map on the terminal
void printMap(Game_World* world, int x, int y, int dx, int dy) {
    int lignes, colonnes;

    if (world == NULL || x < 0 || x > world->width || y < 0 || y > world->height) {

    }

    getmaxyx(stdscr, lignes, colonnes);
    int colonnes_text = dy * 2;
    int colonnes_debut = (colonnes - colonnes_text) / 2;
    int lignes_debut = 6;
    for (int ix = x - dx; ix < x + dx - 1; ix++) {

        if (ix >= 0 && ix < world->width) {

            for (int iy = y - dy; iy < y + dy - 1; iy++) {
                if (iy >= 0 && iy < world->height) {
                    Room room = get_room(world, ix, iy);

                    if ((room.x != -1 && room.y != -1) && !room.is_visited) {
                        mvprintw(lignes_debut, colonnes_debut, " ");
                        mvprintw(lignes_debut, colonnes_debut, "  ");
                        colonnes_debut++;
                        continue;
                    }

                    Entity *entity = get_entity(ix, iy);
                    if (entity != NULL) {
                        mvprintw(lignes_debut, colonnes_debut, "%c", entity->texture);
                        colonnes_debut++;
                    } else {
                        switch (world->chunk[ix][iy]->type) {
                            case DOOR :
                                mvprintw(lignes_debut, colonnes_debut, "D");
                                colonnes_debut++;
                                break;
                            case WALL :
                                mvprintw(lignes_debut, colonnes_debut, "|");
                                colonnes_debut++;
                                break;
                            case VOID :
                                mvprintw(lignes_debut, colonnes_debut, " ");
                                colonnes_debut++;
                                break;
                            case EMPTY :
                                mvprintw(lignes_debut, colonnes_debut, " ");
                                colonnes_debut++;
                                break;
                            default :
                                mvprintw(lignes_debut, colonnes_debut, "?");
                                colonnes_debut++;
                                break;
                        }
                    }
                }
            }
            lignes_debut++;
            colonnes_debut = (colonnes - colonnes_text) / 2;
        }
        int lignes_debut = 6;
        for (int i = x - dx; i < x + dx; i++) {
            for (int j = y - dy; j < y + dy; j++) {
                if (i == x - dx || i == x + dx - 1) {
                    mvprintw(lignes_debut, colonnes_debut, "-");
                    colonnes_debut++;
                } else if (j == y - dy || j == y + dy - 1) {
                    mvprintw(lignes_debut, colonnes_debut, "|");
                    colonnes_debut++;
                } else {
                    colonnes_debut++;
                }
            }
            colonnes_debut = (colonnes - colonnes_text) / 2;
            lignes_debut++;
        }
    }
    refresh();
}
WINDOW* printInventary(){


    WINDOW* win = newwin(10, 2, 1, 1);


    return win;
}