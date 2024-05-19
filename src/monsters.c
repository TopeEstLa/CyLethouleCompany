#include <monsters.h>

#include <stdlib.h>
#include <string.h>

#include <scene/game_scene.h>
#include <curses.h>

#define MONSTERS_COUNT 3


Monster monsters[] = { //TODO: Add ziyad monsters
        {
                .name = "Goblin",
                .texture = "ఠ",
                .max_health = 10
        },
        {
                .name = "Orc",
                .texture = "ద",
                .max_health = 20
        },
        {
                .name = "Troll",
                .texture = "ௐ",
                .max_health = 30
        }
};

Living_Monster **living_monsters = NULL;
int living_monsters_count = 0;
int living_monsters_capacity = 0;

void init_monsters() {
    living_monsters = malloc(sizeof(Living_Monster *) * 10);
    living_monsters_capacity = 10;
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

Monster get_random_monster(int seed) {
    return monsters[random_int(seed, 0, MONSTERS_COUNT - 1)];
}

Living_Monster *create_living_monster(Game_World *world, Monster monster, int x, int y) {
    Living_Monster *living_monster = malloc(sizeof(Living_Monster));
    living_monster->monster = monster;
    living_monster->health = monster.max_health;

    Entity* placed_entity = get_entity(x, y);
    if (placed_entity != NULL) {
        free(living_monster);
        return NULL;
    }

    Entity *entity = create_entity(MONSTER, living_monster, monster.texture);
    int entity_id = add_entity(world, entity, x, y);

    if (entity_id == -1) {
        free(living_monster);
        return NULL;
    }

    living_monster->entity = entity;

    if (living_monsters_count >= living_monsters_capacity) {
        free(living_monster);
        return NULL;
    }

    living_monster->living_id = living_monsters_count;
    living_monsters[living_monsters_count] = living_monster;
    living_monsters_count++;

    return living_monster;
}

void kill_monster(Living_Monster *monster) {
    bool entity_removed = remove_entity(monster->entity->index);

    if (!entity_removed) {
        return;
    }

    int index = monster->living_id;
    free(living_monsters[index]);
    for (int i = index; i < living_monsters_count - 1; i++) {
        living_monsters[i] = living_monsters[i + 1];
        living_monsters[i]->living_id = i;
    }

    living_monsters_count--;
}

void spawn_monster(Game_Data *gameData) {
    if (living_monsters_count >= 10) {
        return;
    }

    Game_World *world = gameData->world;

}