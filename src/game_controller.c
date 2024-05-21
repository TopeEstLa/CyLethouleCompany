#include <game_controller.h>

#include <stdlib.h>
#include <world.h>
#include <world_generator.h>
#include <curses.h>
#include <memory_utils.h>
#include <monsters.h>
#include <ncurses_display.h>

#include <curses.h>

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
    if (world == NULL) {
        return;
    }

    base_generation(world);

    Player *player = create_player(world, name, current_class);
    if (player == NULL) {
        return;
    }

    World_Monster* world_monster = init_world_monster();
    if (world_monster == NULL) {
        return;
    }

    World_Item *world_item = init_world_item();
    if (world_item == NULL) {
        return;
    }

    game->start_time = clock();
    game->end_time = game->start_time + (60000 * GAME_DURATION);
    game->needed_money = random_int(world->seed + world->room_count, 100, 500);
    game->world = world;
    game->player = player;
    game->world_monster = world_monster;
    game->world_item = world_item;

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

    clock_t current_time = clock();
    if (current_time >= get_game_data()->end_time) {
        set_current_scene(TIME_OVER);
        return;
    }

}

int get_remaining_time() {
    if (!is_game_loaded()) return 0;

    clock_t current_time = clock();
    Game_Data *game = get_game_data();
    clock_t remaining_time = (game->end_time - current_time);
    return remaining_time / 1000;
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
            if (have_space(player)) {
                Dropped_Item *item = collided_entity->data;
                Item_Stack *item_stack = pickup_item(game_data->world_item, item->dropped_id);
                add_item_to_inventory(player->inventory, item_stack);
            }
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
        spawn_item(game_data->world_item, game_data->world, room);
        game_data->player->exp += 10;
    }

}
