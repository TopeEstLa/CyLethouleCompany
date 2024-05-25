#include <shop.h>

#include <stdlib.h>
#include <ncurses_display.h>
#include <game_controller.h>
#include <constant.h>

bool spawn_shop(Game_World *world) {
    if (world == NULL) {
        return false;
    }

    if (world->room_count == 0) {
        return false;
    }

    Room *room = world->rooms[0];

    int x = room->x + 1;
    int y = room->y + 1;

    Entity *shop = create_entity(TRADER, NULL, TRADER_TEXTURE);

    int id = add_entity(world, shop, x, y);

    if (id == -1) {
        free(shop);
        return false;
    }

    return true;
}

void open_shop(Player* player) {
    set_current_scene(SHOP_MENU);
}

void sell_inventory(Player* player) {
    if (player == NULL) {
        return;
    }

    Inventory* inventory = player->inventory;
    int estimated_value = estimate_inventory_value(player);
    player->money += estimated_value;
    free(inventory);
    player->inventory = create_inventory(INVENTORY_CAPACITY);
    if (player->inventory == NULL) {
        set_current_scene(GAME_OVER);
    }

    if (is_needed_money_reached()) {
        set_current_scene(WIN);
    }
}

void sell_item(Player* player, int item_index) {
    if (player == NULL) {
        return;
    }

    Inventory* inventory = player->inventory;
    if (item_index < 0 || item_index >= inventory->index) {
        return;
    }

    Item_Stack* item_stack = inventory->items[item_index];
    player->money += item_stack->price;
    remove_item_from_inventory(inventory, item_index);

    if (is_needed_money_reached()) {
        set_current_scene(WIN);
    }
}

int estimate_inventory_value(Player* player) {
    if (player == NULL) {
        return 0;
    }

    int value = 0;
    Inventory* inventory = player->inventory;
    for (int i = 0; i < inventory->index; i++) {
        Item_Stack* item_stack = inventory->items[i];
        value += item_stack->price;
    }

    return value;
}