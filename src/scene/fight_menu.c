#include <scene/fight_menu.h>

#include <curses.h>
#include <fight.h>
#include <string.h>
#include <game_controller.h>
#include <math.h>
#include <stdlib.h>

void fight_input() {
    int ch = getch();

    if (ch == ERR) return;

    if (ch == 10) {
        if (is_fight_ended()) {
            end_fight();
            return;
        } else {
            set_fight_speedup(true);
        }
    }
}

void fight_menu_curses() {
    if (!is_fight_started()) return;
    Player *player = get_game_data()->player;

    printw("  _____   ____   __  __  ____             _______   _____\n"
           " / ____| / __ \\ |  \\/  ||  _ \\     /\\    |__   __| / ____|\n"
           "| |     | |  | || \\  / || |_) |   /  \\      | |   | (___\n"
           "| |     | |  | || |\\/| ||  _ <   / /\\ \\     | |    \\___ \\\n"
           "| |____ | |__| || |  | || |_) | / ____ \\    | |    ____) |\n"
           " \\_____| \\____/ |_|  |_||____/ /_/    \\_\\   |_|   |_____/\n"
           "\n"
           "");

    printw("\n");
    if (!is_fight_ended()) {
        printw("Appuyez sur Entrée pour accélérer le combat\n\n");
    }

    int window_width, window_height;
    getmaxyx(stdscr, window_height, window_width);
    int used_height = 13;

    mvprintw(used_height, 0, "%s - %d PV", player->name, player->health);
    mvprintw(used_height, window_width / 2, "%s - %d PV", get_current_monster()->monster.name,
             get_current_monster()->health);
    used_height += 2;

    int log_count = get_fight_log_size();

    int used_height_for_log = window_height - used_height - 3;
    if (is_fight_ended()) {
        used_height_for_log -= 6;
    }

    int start = 0;

    if (log_count > used_height_for_log) {
        start = log_count - used_height_for_log;
        if (start < 0) start = 0;
    }

    for (int i = start; i < log_count; ++i) {
        Fight_Log log = get_fight_log()[i];
        used_height++;

        if (log_count - 1 == i && is_fight_ended()) {
            printw("\n");
            used_height++;

            attron(A_REVERSE);

            int print_width = (window_width / 2) - strlen(log.action);

            if (print_width < 0) print_width = window_width / 2;

            mvprintw(used_height, print_width, log.action, log.attacker_name, log.defender_name, log.damage);
            attroff(A_REVERSE);
            continue;
        }

        if (log_count - 1 == i)
            attron(A_REVERSE);

        if (strcmp(log.attacker_name, player->name) == 0)
            mvprintw(used_height, 0, log.action, log.attacker_name, log.defender_name, log.damage);
        else
            mvprintw(used_height, window_width / 2, log.action, log.attacker_name, log.defender_name, log.damage);

        if (log_count - 1 == i)
            attroff(A_REVERSE);
    }

    printw("\n\n");

    if (is_fight_ended()) {
        if (fight_win()) {
            printw("Vous avez gagné le combat !\n");
        } else {
            printw("Vous avez perdu le combat !\n");
        }

        printw("\n\n");
        attron(A_REVERSE);
        printw("Retour au jeu");
        attroff(A_REVERSE);
    }
}