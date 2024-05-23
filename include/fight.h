#ifndef FIGHT_H
#define FIGHT_H

#include <monsters.h>
#include <player.h>

/**
 * Fight log structure
 * @param attacker_name: The name of the attacker
 * @param defender_name: The name of the defender
 * @param action: a char* that describe the action that was made
 * @param damage: The damage that was made or other things ^^

 */
typedef struct fight_log {
    char* attacker_name;
    char* defender_name;
    char* action;
    int damage;
} Fight_Log;

/**
 * Get the fight log
 * @return The fight log
 */
Fight_Log *get_fight_log();

/**
 * Get the size of the fight log
 * @return The size of the fight log
 */
int get_fight_log_size();

/**
 * if a fight is prepared
 * @return true if a fight is prepared
 */
bool is_fight_prepared();

/**
 * if a fight is started
 * @return true if a fight is started
 */
bool is_fight_started();

/**
 * if a fight is ended
 * @return true if a fight is ended
 */
bool is_fight_ended();

/**
 * if the player win the fight
 * @return true if the player win the fight
 */
bool fight_win();

/**
 * Speed up fight draw
 * @param speedup true if the fight should be speed up
 */
void set_fight_speedup(bool speedup);

/**
 * Get the fight speedup
 * @return true if the fight speedup is enabled
 */
bool get_fight_speedup();

/**
 * Get the fighted monster
 * @return The monster that is currently fighting
 */
Living_Monster* get_current_monster();

/**
 * Add a fight log (ArrayList like management)
 * @param attacker_name attacker name
 * @param defender_name defender name
 * @param action action description
 * @param damage damage made
 */
void add_fight_log(char* attacker_name, char* defender_name, char* action, int damage);

/**
 * Calculate the player stats of a class
 * @param aClass class of the entity
 * @param attack a pointer to the attack to set
 * @param defense a pointer to the defense to set
 * @param dodge a pointer to the dodge to set
 */
void calculate_stats(Class aClass, int *attack, int *defense, int *dodge);

/**
 * Prepare the fight
 * @param monster The monster to fight
 */
void prepare_fight(Living_Monster *monster);

/**
 * Start the fight
 * @param player The player
 * @param monster The monster
 */
void start_fight(Player *player, Living_Monster *monster);

/**
 * End the fight
 */
void end_fight();

#endif //FIGHT_H
