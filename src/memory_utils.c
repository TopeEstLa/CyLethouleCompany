#include <memory_utils.h>

void free_world(Game_World *world) {
    for (int i = 0; i < world->width; ++i) {
        for (int j = 0; j < world->height; ++j) {
            free(world->chunk[i][j]);
        }

        free(world->chunk[i]);
    }

    for (int i = 0; i < world->room_count; ++i) {

        for (int j = 0; j < 4; ++j) {
            Door *door = world->rooms[i]->doors[j];
            free(door);
        }

        free(world->rooms[i]);
    }

    free(world->chunk);
    free(world->rooms);
    free(world);
}

void free_monster(World_Monster *monster) {
    for (int i = 0; i < monster->living_monsters_count; ++i) {
        free(monster->living_monsters[i]);
    }

    free(monster->living_monsters);
    free(monster);
}

void free_item(World_Item *item) {
    for (int i = 0; i < item->dropped_items_count; ++i) {
        free(item->dropped_items[i]);
    }

    free(item->dropped_items);
    free(item);
}

void free_player(Player *player) {
    for (int i = 0; i < player->inventory->index; ++i) {
        free(player->inventory->items[i]);
    }

    free(player->inventory->items);

    free(player->inventory);
    free(player->name);
    free(player);
}

void free_game_data(Game_Data *game_data) {
    free_world(game_data->world);
    free_monster(game_data->world_monster);
    free_item(game_data->world_item);
    free_player(game_data->player);
    free(game_data);
}
