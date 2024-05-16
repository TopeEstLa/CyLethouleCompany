#include <monsters.h>

#define MONSTERS_COUNT 3
#define MAX_MONSTERS_IN_WORLD 10

#include <stdlib.h>

Monster monsters[] = { //TODO: Add ziyad monsters
        {
                .name = "Goblin",
                .texture = "g",
                .max_health = 10
        },
        {
                .name = "Orc",
                .texture = "o",
                .max_health = 20
        },
        {
                .name = "Troll",
                .texture = "t",
                .max_health = 30
        }
};

Living_Monster** living_monsters = NULL;
int living_monsters_count = 0;
int living_monsters_capacity = 0;

void init_monsters() {
    living_monsters = malloc(sizeof(Living_Monster*) * MAX_MONSTERS_IN_WORLD);
    living_monsters_capacity = MAX_MONSTERS_IN_WORLD;
    living_monsters_count = 0;
}

void cleanup_monsters() {
    for (int i = 0; i < living_monsters_count; i++) {
        free(living_monsters[i]);
    }
    free(living_monsters);

    living_monsters = NULL;
    living_monsters_capacity = 0;
    living_monsters_count = 0;
}

Living_Monster *create_living_monster(Game_World* world, Monster monster, int x, int y) {
    Living_Monster *living_monster = malloc(sizeof(Living_Monster));
    living_monster->monster = monster;
    living_monster->health = monster.max_health;

    Entity* entity = create_entity(MONSTER, living_monster, monster.texture);
    int entity_id = add_entity(world, entity, x, y);

    if (entity_id == -1) {
        free(living_monster);
        return NULL;
    }

    living_monster->entity = entity;
    living_monster->entity_id = entity_id;

    if (living_monsters_count >= living_monsters_capacity) {
        free(living_monster);
        return NULL;
    }

    living_monsters[living_monsters_count++] = living_monster;

    return living_monster;
}

void kill_monster(Living_Monster* monster) {
    bool entity_removed = remove_entity(monster->entity_id);

    if (!entity_removed) {
        return;
    }

    for (int i = 0; i < living_monsters_count; i++) {
        if (living_monsters[i] == monster) {
            free(monster);
            living_monsters[i] = living_monsters[--living_monsters_count];
            return;
        }
    }
}