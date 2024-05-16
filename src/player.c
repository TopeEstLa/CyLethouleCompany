#include <player.h>

#include <stdlib.h>


Player* create_player(Game_World* world, char* name, Class current_class) {
    Player* player = malloc(sizeof(Player));
    player->entity = create_entity(PLAYER, player, "x");
    player->name = name;
    player->current_class = current_class;
    player->health = 100;
    player->exp = 0;

    Room* room = world->rooms[0];

    int roomCenterX = room->x + room->width / 2;
    int roomCenterY = room->y + room->height / 2;

    add_entity(world, player->entity, roomCenterX, roomCenterY);

    return player;
}

Player* load_player(Game_World* world, char* name, Class current_class, int health, int exp, int x, int y) {
    Player* player = malloc(sizeof(Player));
    player->entity = create_entity(PLAYER, player, "x");
    player->name = name;
    player->current_class = current_class;
    player->health = health;
    player->exp = exp;

    add_entity(world, player->entity, x, y);

    return player;
}

