#include <ncurses.h>

int Choose_Option(int choice){
    int choose = getch();
    switch(choose){
        case KEY_UP :
            if (choice > 0){
                choice--;
            }
            break;
        case KEY_DOWN :
            if (choice < 2){
                choice++;
            }
            break;
        case '\n' :
            choice = 5;
            break;
    }
    return choice;
}
void Terminal_Game_Start(){
    printw(" _             _    _                    _         _____\n"
           "| |           | |  | |                  | |       / ____|\n"
           "| |       ___ | |_ | |__    ___   _   _ | |  ___ | |       ___   _ __ ___   _ __    __ _  _ __   _   _\n"
           "| |      / _ \\| __|| '_ \\  / _ \\ | | | || | / _ \\| |      / _ \\ | '_ ` _ \\ | '_ \\  / _` || '_ \\ | | | |\n"
           "| |____ |  __/| |_ | | | || (_) || |_| || ||  __/| |____ | (_) || | | | | || |_) || (_| || | | || |_| |\n"
           "|______| \\___| \\__||_| |_| \\___/  \\__,_||_| \\___| \\_____| \\___/ |_| |_| |_|| .__/  \\__,_||_| |_| \\__, |\n"
           "                                                                           | |                    __/ |\n"
           "                                                                           |_|                   |___/\n");

    printw("\n\n");
    refresh();
    char *tab[] ={
            "New Game",
            "Load a Game",
            "Quit",
    };
    for (int i = 0; i < 3; i++){
        printw("[%d] %s\n", i, tab[i]);
    }
    int choice = 0;
    choice = Choose_Option(choice);
    int selected_option = -1;

    for (int i = 0; i < 3; i++){
        if (i == choice) {
            selected_option = i;
            attron(A_REVERSE);
            printw("[%d] ",i);
            attroff(A_REVERSE);
            printw(": %s\n", tab[i]);
        } else {
            printw("[%d] : %s\n",i, tab[i]);
        }
        if (i = selected_option && choice == 5){
            switch (i) {
                case 0 :
                    break;
                case1 :
                    break;
                case 2 :
                    break;
            }

        }
    }
    refresh();
}
int main(){
    initscr();
    Terminal_Game_Start();
    return 0;
}