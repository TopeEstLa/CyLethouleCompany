#include <game_controller.h>

#include <stdlib.h>
#include <world.h>
#include <world_generator.h>
#include <curses.h>

Game_Data *game_data = NULL;

Game_Data* get_game_data() {
    return game_data;
}

void set_game_data(Game_Data *game_data) {
    game_data = game_data;
}

bool is_game_loaded() {
    return game_data != NULL;
}


void init_game(int seed, char* name, Class current_class) {
    Game_Data *game = malloc(sizeof(Game_Data));
    if (game == NULL) {
        return;
    }

    Game_World* world = create_world(seed);
    base_generation(world);

    init_entities(world);

    Player* player = create_player(world, name, current_class);

    game->world = world;
    game->player = player;

    set_game_data(game);
}

void unload_game() {

}

void move_player(int x, int y) {
    Player* player = game_data->player;
    Entity* entity = player->entity;

    if (entity == NULL) {
        return;
    }

    Move_Callback move_callback = move_entity(game_data->world, entity, x, y);


    if (!move_callback.move_made) return;

    if (move_callback.reason == ENTITY_COLLISION) {
        Entity* collided_entity = move_callback.collided_entity;
        if (collided_entity == NULL) return;

        if (collided_entity->type == MONSTER) {
            //TODO FIGHT !
        } else if (collided_entity->type == ITEM) {
            //TODO PICKUP
        }
    }

    if (move_callback.reason == DOOR_COLLISION) {
        Room* room = get_room(game_data->world, entity->x, entity->y);
        if (room != NULL) {
            generate_rooms(game_data->world, room, 1);
        }
    }

    Room* room = get_room(game_data->world, entity->x, entity->y); //TODO switch to pointer
    if (room == NULL) {
        return;
    }

    if (!room->is_visited) {
        room->is_visited = true;
        game_data->player->exp += 10;
    }

}
