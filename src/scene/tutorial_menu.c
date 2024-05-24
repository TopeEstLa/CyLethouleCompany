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

    printw("La Company : Missionée par Garedon, la Company a pour objectif d'empêcher Morlok à récuperer l'anneau de ces ancestres à des fins dévastatrices.\n"
           "\n"
           "\n"
           "Les fondations : Type de bâtiment multiples cachés dans les tréfonds de la Terre, une fondation est un bâtiment détenu par Morlok pour créer des ames.\n"
           "\n"
           "\n"
           "Morlok : Dernier monstre des enfers, Morlok ne veut pas que la Company faillit à son projet final : Récuperer l'anneau des Morlok.\n"
           "\n"
           "\n"
           "Garedon: Garde de l'anneau des Morlok, Garedon n'hésitera pas à apparaitre avant chaque combat pour vous aider à faillir au plan de Morlok.\n"
           "\n"
           "\n"
           "Archer : Classe polyvalente, l'archer est l'archétype du soldat fidèle : Attaque : 5 à 7, Defense : 2 à 5, Esquive : 2 à 7 \n"
           "\n"
           "\t\n"
           "Sorcier : Adepte de la magie noir, le sorcier n'hésitera pas à user de sa magie pour esquiver : Attaque : 3 à 5, Defense : 4 à 7, Esquive : 4 à 12\n"
           "\n"
           "\n"
           "Guerrier : Imposant, le guerrier n'usera que de l'attaque pour exterminer son adversaire : Attaque : 7 à 11\n"
           "\n"
           "\n"
           "Monstres : Ces obstacles, envoyés par Morlok, n'hésiteront pas à vous affaiblir pour empêcher la réussite de la mission Company : Attaque : 1 à 5, Défense : 1 à 3\n"
           "\n"
           "\n"
           "Trader : Individu vivant dans les fondations, le trader acceptera d'acheter vos items pour son projet secret !\n");


    attron(A_REVERSE);
    printw("Echap pour retourner au menu principal");
    attroff(A_REVERSE);
}
