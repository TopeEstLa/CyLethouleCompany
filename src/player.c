#include <player.h>

#include <stdlib.h>
#include <string.h>


Player *create_player(Game_World *world, char *name, Class current_class) {
    Player *player = malloc(sizeof(Player));
    player->entity = create_entity(PLAYER, player, "ର");
    player->name = malloc(strlen(name) + 1);
    strcpy(player->name, name);
    player->current_class = current_class;
    player->health = 100;
    player->max_health = 100;
    player->exp = 0;

    Room *room = world->rooms[0];

    int roomCenterX = room->x + room->width / 2;
    int roomCenterY = room->y + room->height / 2;

    int id = add_entity(world, player->entity, roomCenterX, roomCenterY);

    if (id == -1) {
        free(player);
        return NULL;
    }

    player->entity_id = id;

    return player;
}

Player *load_player(Game_World *world, char *name, Class current_class, int health, int max_health, int exp, int x, int y) {
    Player *player = malloc(sizeof(Player));
    player->entity = create_entity(PLAYER, player, "ର");
    player->name = malloc(strlen(name) + 1);
    strcpy(player->name, name);
    player->current_class = current_class;
    player->health = health;
    player->max_health = max_health;
    player->exp = exp;

    int id = add_entity(world, player->entity, x, y);

    if (id == -1) {
        free(player);
        return NULL;
    }

    player->entity_id = id;

    return player;
}

