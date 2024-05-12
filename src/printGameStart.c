#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
void flushStdIn(){
    int  a;
    char c;
    do{
        a = scanf("%c", &c);
    } while(a==1 && c != '\n' );
}
void printStart(){
    initscr();

    noecho(); // No print of the caracter selected
    curs_set(0); // Mask the Cursor
    clear(); // delete the terminal print
    refresh(); // refresh the terminal

    // tab of the game selector
    char* Game_mode[]={
            "1 - Facile",
            "2 - Intermédiaire",
            "3 - Difficile",
            "4 - Charger une session",
            "5 - Quitter",
    };
    // print the game selector
    for (int i = 0; i < 4; i++){
        printw("%s\n",Game_mode[i]);
        refresh();
    }
    int a = -1;
    int res = 0;
    // Choose a game mode
    do{ res = 0;
        printw("Tapez le numéro de votre choix\n");
        refresh();
        res = scanw("%d", &a);
        a = a - 1;
        //flushStdIn();
    } while(a<0 || a > 4 || res != 1);

    // enter to the game world selected
    switch (a) {
        case 0:
            printw("Game in mode EASY\n");
            break;
        case 1:
            printw("Game in mode Intermédiare\n");
            break;
        case 2:
            printw("Game in mode Difficile\n");
            break;
        case 3:
            printw("Select a session\n");
            break;
        case 4:
            printw("SEE YOU SOON\n");
            endwin();
            break;
    }
    refresh();
    endwin();
}
int main() {
    printStart();

    return 0;
}
