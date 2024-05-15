#include <player.h>

#include <stdlib.h>


Player* create_player(Game_World* world, char* name, Class current_class) {
    Player* player = malloc(sizeof(Player));
    player->entity = create_entity(PLAYER, player, "x");
    player->name = name;
    player->current_class = current_class;
    player->health = 100;
    player->exp = 0;

    Room room = world->rooms[0];

    int roomCenterX = room.x + room.width / 2;
    int roomCenterY = room.y + room.height / 2;

    add_entity(player->entity, roomCenterX, roomCenterY);

    return player;
}

