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
    int lignes, colonnes;
    start_color();
    getmaxyx(stdscr, lignes, colonnes);
    int colonnes_text = 3;
    int colonnes_debut = (colonnes - colonnes_text) / 2;
    sleep(2);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    struct timeval tv;
    gettimeofday(&tv, NULL);
    //save the actual timeofday
    long difference = tv.tv_sec - start;
    //Print in red if the difference is under 10 seconds
    if (difference <= 10){
        attron(COLOR_PAIR(1));
        mvprintw(3, colonnes_debut, "%3ld", difference);
        attroff(COLOR_PAIR(1));
    } else {
        mvprintw(3, colonnes_debut, "%3ld", difference);
    }
    refresh();

}

//Print the map on the terminal
void printMap(Game_World* world, int x, int y, int dx, int dy){
    int lignes, colonnes;

    if (world == NULL || x < 0 || x > world->width || y < 0 || y > world->height){
        exit(404);
    }
    printw("\n");
    getmaxyx(stdscr, lignes, colonnes);
    int colonnes_text = dx * 2;
    int colonnes_debut = (colonnes - colonnes_text) / 2;
    int lignes_debut = 12;
    for (int iy = y - dy; iy < y + dy; iy++){
        if (iy < 1 || iy > world->height){
            continue;
        } else {
            for (int jx = x - dx; jx < x + dx; jx++) {
                if(jx == x-dx || jx == x+dx-1){
                    mvprintw(lignes_debut, colonnes_debut, "|");
                    colonnes_debut++;
                } else if (iy == y-dy || iy == y+dy-1) {
                    mvprintw(lignes_debut, colonnes_debut, "-");
                    colonnes_debut++;
                }else if (jx < 0 || jx > world->width) {
                    continue;
                } else {
                    Entity *entity = get_entity(jx, iy);

                    //print the item to stack or the emoji of the player
                    if (entity != NULL){
                        mvprintw(lignes_debut, colonnes_debut, "%c", entity->texture);
                        colonnes_debut++;
                    }else {
                        //print the map : door, wall, etc ...
                        switch (world->chunk[jx][iy]->type) {
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
    }
    refresh();
}
WINDOW* printInventary(){


    WINDOW* win = newwin(10, 2, 1, 1);


    return win;
}