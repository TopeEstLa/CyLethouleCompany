#include <game.h>

#include <stdlib.h>
#include <world.h>
#include <world_generator.h>
#include <curses.h>

Game *game;

void set_game(Game *game) {
    game = game;
}

Game *get_game() {
    return game;
}

void init_game(int seed, char* name, Class current_class) {
    game = malloc(sizeof(Game));

    Game_World* world = create_world(seed);
    base_generation(world);

    init_entities(world);

    Player* player = create_player(world, name, current_class);

    game->world = world;
    game->player = player;
}

void move_player(int x, int y) {
    Player* player = game->player;
    Entity* entity = player->entity;

    if (entity == NULL) {
        return;
    }

    Move_Callback move_callback = move_entity(entity, x, y);

    if (!move_callback.move_made) return;

    if (move_callback.reason == ENTITY_COLLISION) {
        Entity* collided_entity = move_callback.collided_entity;
        if (entity == NULL) return;

        if (collided_entity->type == MONSTER) {
            //TODO FIGHT !
        }
    }

    if (move_callback.reason == DOOR_COLLISION) {

    }

    Room room = get_room(game->world, entity->x, entity->y);
    if ((room.x != -1 && room.y != -1) && !room.is_visited) {
        room.is_visited = true;
        game->player->exp += 10;
        printw("You have visited a new room! You gained 10 exp!\n");
    }

}
