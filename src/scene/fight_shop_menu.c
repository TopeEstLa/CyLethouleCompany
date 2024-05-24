#include <scene/fight_shop_menu.h>

#include <curses.h>
#include <stdlib.h>

#include <game_controller.h>
#include <ncurses_display.h>
#include <scene/fight_shop_callback_menu.h>
#include <fight.h>

char *fight_shop_choices[] = {
        "Fiole de vie (+100 points de vie) - 10 âmes",
        "Pari risqué (double ou rien) - 15 âmes",
        "Mort instantanée (tue votre ennemi) - 150 âmes",
        "Rien ne m'intéresse",
};
int fight_shop_choice = 0;

void reset_fight_shop_fields() {
    fight_shop_choice = 0;
}

void fight_shop_handle_input() {
    int ch = getch();

    if (ch == ERR) return;

    if (!is_game_loaded()) {
        set_current_scene(MAIN_MENU);
        return;
    }

    Game_Data* game = get_game_data();

    if (!is_fight_prepared()) {
        set_current_scene(GAME);
        return;
    }

    Player *player = get_game_data()->player;

    switch (ch) {
        case KEY_UP:
            if (fight_shop_choice > 0) {
                fight_shop_choice--;
            }
            break;
        case KEY_DOWN:
            if (fight_shop_choice < 3) {
                fight_shop_choice++;
            }
            break;
        case 10:

            switch (fight_shop_choice) {
                case 0:
                    if (player->exp < 10) {
                        set_callback("Vous n'avez pas assez d'âmes pour acheter se service !");
                        set_current_scene(FIGHT_SHOP_CALLBACK);
                        break;
                    }

                    player->exp -= 10;

                    for (int i = 0; player->health < player->max_health &&  i < 100; ++i) {
                        player->health++;
                    }

                    set_callback("Vous avez récupéré 100 points de vie");
                    set_current_scene(FIGHT_SHOP_CALLBACK);
                    break;
                case 1:
                    if (player->exp < 15) {
                        set_callback("Vous n'avez pas assez d'âmes pour acheter se service !");
                        set_current_scene(FIGHT_SHOP_CALLBACK);
                        break;
                    }

                    player->exp -= 15;

                    srand(time(NULL));
                    if (rand() % 2 == 0) {
                        player->exp += 30;
                        set_callback("Vous avez gagné le pari ! Vous gagnez 30 âmes de Morlok");
                    } else {
                        set_callback("Vous avez perdu le pari ! Vous avez perdu 15 âmes !");
                    }

                    set_current_scene(FIGHT_SHOP_CALLBACK);
                    //start_fight(game->player, get_current_monster());
                    break;
                case 2:
                    if (player->exp < 150) {
                        set_callback("Vous n'avez pas assez d'âmes pour acheter se service !");
                        set_current_scene(FIGHT_SHOP_CALLBACK);
                        break;
                    }

                    player->exp -= 150;

                    Living_Monster *monster = get_current_monster();
                    monster->health = 0;
                    end_fight();
                    break;
                case 3:
                    start_fight(game->player, get_current_monster());
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void fight_shop_menu_curses() {
    if (!is_game_loaded()) return;
    Game_Data *game = get_game_data();
    Player *player = game->player;

    printw(" _______           __      __ ______  _____   _   _  ______\n"
           "|__   __|    /\\    \\ \\    / /|  ____||  __ \\ | \\ | ||  ____|\n"
           "   | |      /  \\    \\ \\  / / | |__   | |__) ||  \\| || |__\n"
           "   | |     / /\\ \\    \\ \\/ /  |  __|  |  _  / | . ` ||  __|\n"
           "   | |    / ____ \\    \\  /   | |____ | | \\ \\ | |\\  || |____\n"
           "   |_|   /_/    \\_\\    \\/    |______||_|  \\_\\|_| \\_||______|\n"
           "\n"
           "");

    printw("\n\n");
    printw("Vous possédez actuellement %d ame(s) de Morlok !\n", player->exp);
    printw("\n");
    printw("Voici les services proposés par Garedon :\n");
    printw("\n");

    for (int i = 0; i < 4; i++) {
        char a = 'O';
        if (i == fight_shop_choice) {
            a = 'X';
            attron(A_REVERSE);
        }
        printw("[%c] %s\n", a, fight_shop_choices[i]);

        if (i == fight_shop_choice) {
            attroff(A_REVERSE);
        }
    }
}