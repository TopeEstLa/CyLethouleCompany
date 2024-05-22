#include <game_controller.h>

#include <stdlib.h>
#include <world.h>
#include <world_generator.h>
#include <curses.h>
#include <memory_utils.h>
#include <monsters.h>
#include <ncurses_display.h>
#include <shop.h>
#include <constant.h>
#include <fight.h>

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

    bool is_spawn = spawn_shop(new_game_data->world);

    if (!is_spawn) {
        unload_game();
        set_current_scene(MAIN_MENU);
        return;
    }

    set_current_scene(GAME);
}

void create_game(int seed, char *name, Class current_class) {
    prepare_game();

    Game_Data *game = malloc(sizeof(Game_Data));
    if (game == NULL) {
        cleanup_entities();
        return;
    }

    Game_World *world = create_world(seed);
    if (world == NULL) {
        free(game);
        return;
    }

    base_generation(world);

    Player *player = create_player(world, name, current_class);
    if (player == NULL) {
        free(game);
        free_world(world);
        return;
    }

    World_Monster* world_monster = init_world_monster();
    if (world_monster == NULL) {
        free(game);
        free_world(world);
        free_player(player);
        return;
    }

    World_Item *world_item = init_world_item();
    if (world_item == NULL) {
        free(game);
        free_world(world);
        free_player(player);
        free(world_monster);
        return;
    }

    game->start_time = clock();
    game->end_time = game->start_time + GAME_DURATION_SECONDS * CLOCKS_PER_SEC;

    if (MAX_ROOM != -1) {
        game->needed_money = random_int(world->seed + world->room_count, 30, 150); //nerft quota if max room is not infinite
    } else {
        game->needed_money = random_int(world->seed + world->room_count, 100, 500);
    }

    game->world = world;
    game->player = player;
    game->world_monster = world_monster;
    game->world_item = world_item;

    bool is_spawn = spawn_shop(world);

    if (!is_spawn) {
        free(game);
        free_world(world);
        free_player(player);
        free(world_monster);
        free(world_item);
        return;
    }

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
    Game_Data *game = get_game_data();

    clock_t current_time = clock();
    if (current_time >= get_game_data()->end_time) {
        set_current_scene(TIME_OVER);
        return;
    }

    if (is_needed_money_reached()) {
        set_current_scene(WIN);
        return;
    }

    bool door_available = any_door_not_used(game->world);

    bool all_visited = count_visited_rooms(game->world) == game->world->room_count -1;

    if (!door_available && all_visited) {
        int estimated_value = estimate_value_in_world(game->world_item);
        int start_needed_money = game->needed_money;
        int actual_money = game->player->money;
        int inventory_value = estimate_inventory_value(game->player);

        int current_needed_money = start_needed_money - actual_money - estimated_value - inventory_value;

        if (current_needed_money <= 0) {
            return;
        }

        int random_room = random_int(game->world->seed + game->player->money + game->player->exp, 0, get_game_data()->world->room_count - 1);
        Room *room = game->world->rooms[random_room];

        spawn_item(game->world_item, game->world, room); //re spawning item
    }
}

int get_remaining_time() {
    if (!is_game_loaded()) return 0;
    Game_Data *game = get_game_data();

    int remaining_seconds = (game->end_time - clock()) / CLOCKS_PER_SEC;
    return remaining_seconds;
}

bool is_needed_money_reached() {
    if (!is_game_loaded()) return false;
    Game_Data *game = get_game_data();

    return game->player->money >= game->needed_money;
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
            Living_Monster *monster = collided_entity->data;
            prepare_fight(monster);
        } else if (collided_entity->type == ITEM) {
            if (have_space(player)) {
                Dropped_Item *item = collided_entity->data;
                Item_Stack *item_stack = pickup_item(game_data->world_item, item->dropped_id);
                add_item_to_inventory(player->inventory, item_stack);
            }
        } else if (collided_entity->type == TRADER) {
            open_shop(player);
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
