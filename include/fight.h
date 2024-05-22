#ifndef FIGHT_H
#define FIGHT_H

#include <monsters.h>
#include <player.h>

typedef struct fight_log {
    char* attacker_name;
    char* defender_name;
    char* action;
    int damage;
} Fight_Log;

Fight_Log *get_fight_log();

int get_fight_log_size();

bool is_fight_started();

bool is_fight_ended();

bool fight_win();

Living_Monster* get_current_monster();

void add_fight_log(char* attacker_name, char* defender_name, char* action, int damage);

void calculate_stats(Class aClass, int *attack, int *defense, int *dodge);

void prepare_fight(Living_Monster *monster);

void start_fight(Player *player, Living_Monster *monster);

void end_fight();

#endif //FIGHT_H
