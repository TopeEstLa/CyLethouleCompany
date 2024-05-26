#include <scene/tutorial_menu.h>

#include <curses.h>

#include <ncurses_display.h>

void tutorial_handle_input() {
    int ch = getch();

    switch (ch) {
        case 27:
            set_current_scene(MAIN_MENU);
            break;
        default:
            break;
    }
}

void tutorial_menu_curses() {
    printw(" _____    ____   _   _  _   _  ______  ______   _____\n"
           "|  __ \\  / __ \\ | \\ | || \\ | ||  ____||  ____| / ____|\n"
           "| |  | || |  | ||  \\| ||  \\| || |__   | |__   | (___\n"
           "| |  | || |  | || . ` || . ` ||  __|  |  __|   \\___ \\\n"
           "| |__| || |__| || |\\  || |\\  || |____ | |____  ____) |\n"
           "|_____/  \\____/ |_| \\_||_| \\_||______||______||_____/\n"
           "\n"
           "");

    printw("\n\n");

    printw("La Company : Missionnée par Garedon, la Company a pour objectif d'empêcher Morlok à récupérer l'anneau de ces ancêtres à des fins dévastatrices..\n"
           "\n"
           "Morlok : Dernier monstre des enfers, Morlok ne veut pas que la Company faillit à son projet final : Récupérer l'anneau des Morlok.\n"
           "\n"
           "Garedon: Garde de la station spatiale de la Cosmic Yonder, Garedon n'hésitera pas à apparaître avant chaque combat pour vous aider à faillir au plan de Morlok.\n"
           "\n"
           "Archer : Classe polyvalente, l'archer est l'archétype du soldat fidèle : Attaque : 5 à 7, Defense : 2 à 5, Esquive : 2 à 7 \n"
           "\n"
           "Sorcier : Adepte de la magie noir, le sorcier n'hésitera pas à user de sa magie pour esquiver : Attaque : 3 à 5, Defense : 4 à 7, Esquive : 4 à 12\n"
           "\n"
           "Guerrier : Imposant, le guerrier n'usera que de l'attaque pour exterminer son adversaire : Attaque : 7 à 11\n"
           "\n"
           "Monstres : Créés par Morlok à l’aide de son âme et des avancées biologiques de la station, des Goblis (10 pv), des Orcs (20pv) et des Trolls (30pv) n'hésiteront pas à vous affaiblir pour empêcher la réussite de la mission Company  : Attaque : 1 à 11, Défense : 1 à 3\n"
           "\n"
           "Trader : Individu vivant dans les fondations, le trader achetera vos items afin d’en puiser les ressources pour gérer la maintenance du vaisseau.  \n");


    attron(A_REVERSE);
    printw("Echap pour retourner au menu principal");
    attroff(A_REVERSE);
}
