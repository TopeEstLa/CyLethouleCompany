#include <monsters.h>

#include <stdlib.h>
#include <string.h>

#define MONSTERS_COUNT 3

Monster monsters[] = { //TODO: Add ziyad monsters
        {
                .name = "Goblin",
                .texture = "ఠ",
                .max_health = 10,
                .class = ARCHER
        },
        {
                .name = "Orc",
                .texture = "ద",
                .max_health = 20,
                .class = WARRIOR
        },
        {
                .name = "Troll",
                .texture = "ௐ",
                .max_health = 30,
                .class = WIZARD
        }
};

World_Monster *init_world_monster() {
    World_Monster *world_monster = malloc(sizeof(World_Monster));
    world_monster->living_monsters = malloc(sizeof(Living_Monster *) * 10);
    world_monster->living_monsters_count = 0;
    world_monster->living_monsters_capacity = 10;
    return world_monster;
}

int get_random_monster(int seed) {
    return random_int(seed, 0, MONSTERS_COUNT - 1);
}

Living_Monster *create_living_monster(Game_World *world, World_Monster *world_monster, int monster_id, int x, int y, int health) {
    if (monster_id < 0 || monster_id >= MONSTERS_COUNT) {
        return NULL;
    }

    Monster monster = monsters[monster_id];

    int l_health = 0;
    if (health == -1) {
        l_health = monster.max_health;
    } else {
        l_health = health;
    }

    Living_Monster *living_monster = malloc(sizeof(Living_Monster));
    living_monster->monster = monster;
    living_monster->monster_id = monster_id;
    living_monster->health = l_health;

    Entity *placed_entity = get_entity(x, y);
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


    if (world_monster->living_monsters_count >= world_monster->living_monsters_capacity) {
        world_monster->living_monsters_capacity *= 2;
        world_monster->living_monsters = realloc(world_monster->living_monsters,
                                                 sizeof(Living_Monster *) * world_monster->living_monsters_capacity);
        if (world_monster->living_monsters == NULL) {
            free(living_monster);
            return NULL;
        }
    }

    living_monster->living_id = world_monster->living_monsters_count;
    world_monster->living_monsters[world_monster->living_monsters_count] = living_monster;
    world_monster->living_monsters_count++;

    return living_monster;
}

void kill_monster(World_Monster *world_monster, int monster_id) {
    Living_Monster *living_monster = world_monster->living_monsters[monster_id];
    Entity *living_entity = living_monster->entity;

    if (living_entity == NULL) {
        return;
    }

    if (living_entity->index < 0 && living_entity->index >= world_monster->living_monsters_count) {
        return;
    }

    bool removed = remove_entity(living_entity->index);

    if (removed) {
        free(world_monster->living_monsters[monster_id]);
        int index = monster_id;
        for (int i = index; i < world_monster->living_monsters_count - 1; i++) {
            world_monster->living_monsters[i] = world_monster->living_monsters[i + 1];
            world_monster->living_monsters[i]->living_id = i;
        }
        world_monster->living_monsters_count--;
    }
}

void spawn_monster(World_Monster *worldMonster, Game_World *world, Room *room) {
    int spawn_count = random_int(world->seed + room->x + room->y + room->height + room->width, 0, 2);

    for (int i = 0; i < spawn_count; i++) {
        int x = random_int(world->seed + room->x + room->y + room->height + room->width + i, room->x + 1,
                           room->x + room->width - 1);
        int y = random_int(world->seed + room->x + room->y + room->height + room->width + i, room->y + 1,
                           room->y + room->height - 1);

        int monster = get_random_monster(world->seed + room->x + room->y + room->height + room->width + i + x + y);
        Living_Monster *liv = create_living_monster(world, worldMonster, monster, x, y, -1);

        if (liv == NULL) {
            return;
        }

    }
}