#include <memory_utils.h>

void free_world(Game_World *world) {
    for (int i = 0; i < world->width; ++i) {
        for (int j = 0; j < world->height; ++j) {
            free(world->chunk[i][j]);
        }

        free(world->chunk[i]);
    }

    free(world->chunk);
    free(world->rooms);
    free(world);
}

void free_player(Player *player) {
    free(player->inventory->items);
    free(player->inventory);
    free(player->name);
    free(player);
}

void free_game_data(Game_Data *game_data) {
    free_world(game_data->world);
    free(game_data->world_monster->living_monsters);
    free(game_data->world_monster);
    free(game_data->world_item->dropped_items);
    free(game_data->world_item);
    free_player(game_data->player);
    free(game_data);
}
