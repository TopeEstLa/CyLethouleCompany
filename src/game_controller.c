#include <game_controller.h>

#include <stdlib.h>
#include <world.h>
#include <world_generator.h>
#include <curses.h>
#include <memory_utils.h>
#include <monsters.h>
#include <ncurses_display.h>

Game_Data *game_data = NULL;

Game_Data *get_game_data() {
    return game_data;
}

void set_game_data(Game_Data *new_game_data) {
    game_data = new_game_data;
}

bool is_game_loaded() {
    return game_data != NULL;
}

void prepare_game() {
    init_entities();
}

void loaded_game(Game_Data *new_game_data) {
    set_game_data(new_game_data);
}

void create_game(int seed, char *name, Class current_class) {
    prepare_game();

    Game_Data *game = malloc(sizeof(Game_Data));
    if (game == NULL) {
        return;
    }

    Game_World *world = create_world(seed);
    base_generation(world);

    Player *player = create_player(world, name, current_class);
    World_Monster* world_monster = init_world_monster();

    game->world = world;
    game->player = player;
    game->world_monster = world_monster;

    set_game_data(game);
}

void unload_game() {
    cleanup_entities();

    Game_Data *game = get_game_data();
    if (game == NULL) {
        return;
    }

    set_game_data(NULL);
    free_game_data(game);
}

void update_game() {
    if (get_current_scene() != GAME) return;
    if (!is_game_loaded()) return;

    game_data->frame_count++;
}

void move_player(int x, int y) {
    Player *player = game_data->player;
    Entity *entity = player->entity;

    if (entity == NULL) {
        return;
    }

    Move_Callback move_callback = move_entity(game_data->world, entity, x, y);

    if (move_callback.reason == ENTITY_COLLISION) {
        Entity *collided_entity = move_callback.collided_entity;
        if (collided_entity == NULL) return;

        if (collided_entity->type == MONSTER) {
            //TODO fight
            Living_Monster *monster = collided_entity->data;
            kill_monster(game_data->world_monster, monster->living_id);
        } else if (collided_entity->type == ITEM) {
            //TODO PICKUP
        }
    }

    if (move_callback.reason == DOOR_COLLISION) {
        Room *room = get_room(game_data->world, entity->x, entity->y);
        if (room != NULL) {
            generate_rooms(game_data->world, room, 1);
        }
    }

    if (!move_callback.move_made) {
        return;
    }

    Room *room = get_room(game_data->world, entity->x, entity->y);
    if (room == NULL) {
        return;
    }

    if (!room->is_visited) {
        room->is_visited = true;
        spawn_monster(game_data->world_monster, game_data->world, room);
        game_data->player->exp += 10;
    }

}
