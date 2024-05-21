#include <player.h>

#include <constant.h>

#include <stdlib.h>
#include <string.h>
#include <game_controller.h>
#include <ncurses_display.h>

Player *create_player(Game_World *world, char *name, Class current_class) {
    Player *player = malloc(sizeof(Player));
    player->entity = create_entity(PLAYER, player, PLAYER_TEXTURE);
    player->name = malloc(strlen(name) + 1);
    strcpy(player->name, name);
    player->inventory = create_inventory(INVENTORY_CAPACITY);
    player->current_class = current_class;
    player->health = DEFAULT_MAX_HEALTH;
    player->max_health = DEFAULT_MAX_HEALTH;
    player->exp = 0;
    player->money = 0;

    Room *room = world->rooms[0];

    int roomCenterX = room->x + room->width / 2;
    int roomCenterY = room->y + room->height / 2;

    int id = add_entity(world, player->entity, roomCenterX, roomCenterY);

    if (id == -1) {
        free(player);
        return NULL;
    }

    return player;
}

Player *
load_player(Game_World *world, char *name, Inventory *inventory, Class current_class, int health, int max_health,
            int exp, int money, int x, int y) {
    Player *player = malloc(sizeof(Player));
    player->entity = create_entity(PLAYER, player, PLAYER_TEXTURE);
    player->name = malloc(strlen(name) + 1);
    strcpy(player->name, name);
    player->inventory = inventory;
    player->current_class = current_class;
    player->health = health;
    player->max_health = max_health;
    player->exp = exp;
    player->money = money;

    int id = add_entity(world, player->entity, x, y);

    if (id == -1) {
        free(player);
        return NULL;
    }

    return player;
}

Inventory *create_inventory(int capacity) {
    Inventory *inventory = malloc(sizeof(Inventory));
    inventory->items = malloc(sizeof(Item_Stack *) * capacity);
    inventory->index = 0;
    inventory->capacity = capacity;

    return inventory;
}

void add_item_to_inventory(Inventory *inventory, Item_Stack *item_stack) {
    if (inventory->index >= inventory->capacity) {
        return;
    }

    inventory->items[inventory->index] = item_stack;
    inventory->index++;
}

bool remove_item_from_inventory(Inventory *inventory, int index) {
    if (index < 0 || index >= inventory->index) {
        return false;
    }

    free(inventory->items[index]);
    for (int i = index; i < inventory->index - 1; i++) {
        inventory->items[i] = inventory->items[i + 1];
    }

    inventory->index--;

    return true;
}

bool have_space(Player *player) {
    Inventory* inventory = player->inventory;
    if (inventory->index >= inventory->capacity) {
        return false;
    }

    return true;
}

void player_death(Game_World* world, Player *player) {
    if (!is_game_loaded()) {
        return;
    }
    Game_Data *game = get_game_data();

    Entity *entity = player->entity;

    Room* room = world->rooms[0];

    int roomCenterX = room->x + room->width / 2;
    int roomCenterY = room->y + room->height / 2;

    free(player->inventory);
    player->inventory = create_inventory(INVENTORY_CAPACITY);
    player->health = player->max_health;
    player->exp = player->exp / 2;


    int quota_add = game->needed_money * 0.1;
    player->money += quota_add;

    Move_Callback callback = move_entity(world, entity, roomCenterX, roomCenterY);

    if (!callback.move_made) {
        remove_entity(entity->index);
        free(player->entity);
        player->entity = create_entity(PLAYER, player, PLAYER_TEXTURE);
        int id = add_entity(world, player->entity, roomCenterX, roomCenterY);
        if (id == -1) {
            //wtf
            set_current_scene(MAIN_MENU);
            unload_game();
            return;
        }
    }

    set_current_scene(GAME_OVER);
}