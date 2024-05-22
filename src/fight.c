#include <fight.h>

#include <stdlib.h>
#include <maths.h>
#include <time.h>
#include <string.h>
#include <ncurses_display.h>
#include <unistd.h>
#include <game_controller.h>

Fight_Log *fight_log = NULL;
int fight_log_size = 0;
int fight_log_capacity = 20;
bool fight_started = false;
Living_Monster *current_monster = NULL;

Fight_Log *get_fight_log() {
    return fight_log;
}

int get_fight_log_size() {
    return fight_log_size;
}

bool is_fight_prepared() {
    return current_monster != NULL;
}

bool is_fight_started() {
    return fight_started;
}

bool is_fight_ended() {
    Game_Data* game_data = get_game_data();
    if (!is_game_loaded()) return true;
    return game_data->player->health <= 0 || current_monster->health <= 0;
}

bool fight_win() {
    return current_monster->health <= 0;
}

Living_Monster* get_current_monster() {
    return current_monster;
}

void add_fight_log(char* attacker_name, char* defender_name, char* action, int damage) {
    if (fight_log_size >= fight_log_capacity) {
        fight_log_capacity *= 2;
        fight_log = realloc(fight_log, sizeof(Fight_Log) * fight_log_capacity);
    }

    Fight_Log log;
    log.attacker_name = malloc(strlen(attacker_name) + 1);
    log.defender_name = malloc(strlen(defender_name) + 1);
    log.action = malloc(strlen(action) + 1);
    strcpy(log.attacker_name, attacker_name);
    strcpy(log.defender_name, defender_name);
    strcpy(log.action, action);
    log.damage = damage;
    fight_log[fight_log_size] = log;
    fight_log_size++;
}

void calculate_stats(Class aClass, int *attack, int *defense, int *dodge) {
    switch (aClass) {
        case WARRIOR:
            *attack = random_int(time(NULL), 7, 11);
            *defense = 0;
            *dodge = 0;
            break;
        case ARCHER:
            *attack = random_int(time(NULL), 5, 7);
            *defense = random_int(time(NULL), 2, 5);
            *dodge = random_int(time(NULL), 2, 7);
            break;
        case WIZARD:
            *attack = random_int(time(NULL), 3, 5);
            *defense = random_int(time(NULL), 4, 7);
            *dodge = random_int(time(NULL), 4, 12);
            break;
    }

}

void prepare_fight(Living_Monster *monster) {
    fight_log = malloc(sizeof(Fight_Log) * 20);
    fight_log_size = 0;
    fight_log_capacity = 20;
    fight_started = false;
    current_monster = monster;
}

void start_fight(Player *player, Living_Monster *monster) {
    fight_started = true;
    int player_attack = 0;
    int player_defense = 0;
    int player_dodge = 0;

    int monster_attack = 0;
    int monster_defense = 0;
    int monster_dodge = 0;

    do {
        calculate_stats(player->current_class, &player_attack, &player_defense, &player_dodge);
        calculate_stats(monster->monster.class, &monster_attack, &monster_defense, &monster_dodge);

        if (player_attack < monster_dodge) {
            add_fight_log(player->name, monster->monster.name, "%s A attaquer %s mais celui si a esquiver\n", 0);
        } else {
            int degats = player_attack - monster_defense;
            if (degats < 0) degats = 0;
            monster->health -= degats;
            add_fight_log(player->name, monster->monster.name, "%s a attaqué %s et lui a infligé %d dégats\n", degats);
        }

        if (monster->health <= 0) {
            monster->health = 0;
            break;
        }

        curses_scene();
        usleep(1000000); //in micro second (Literally steals the gameloop here)

        if (monster_attack < player_dodge) {
            add_fight_log(monster->monster.name, player->name, "%s A attaquer %s mais celui si a esquiver\n", 0);
        } else {
            int degats = monster_attack - player_defense;
            if (degats < 0) degats = 0;
            player->health -= degats;
            add_fight_log(monster->monster.name, player->name, "%s a attaqué %s et lui a infligé %d dégats\n", degats);
        }

        if (player->health <= 0) {
            player->health = 0;
            break;
        }

        curses_scene();
        usleep(1000000); //in micro second (Literally steals the gameloop here)
    } while (player->health > 0 && monster->health > 0);

    if (player->health <= 0) {
        add_fight_log(monster->monster.name, player->name, "%s a tué %s\n", 0);
    } else {
        add_fight_log(player->name, monster->monster.name, "%s a tué %s Vous avez donc gagner %d Exp\n", 10);
        player->exp += 10;
    }

}

void end_fight() {
    fight_started = false;
    free(fight_log);
    fight_log = NULL;
    fight_log_size = 0;
    fight_log_capacity = 0;

    Game_Data* game_data = get_game_data();

    if (current_monster->health <= 0) {
        kill_monster(game_data->world_monster, current_monster->living_id);
    }

    current_monster = NULL;

    if (game_data->player->health <= 0) {
        player_death(game_data->world, game_data->player);
        set_current_scene(GAME_OVER);
        return;
    }

    set_current_scene(GAME);
}


