#include <shop.h>

#include <stdlib.h>
#include <ncurses_display.h>

bool spawn_shop(Game_World *world) {
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
    Inventory* inventory = player->inventory;
    int estimated_value = estimate_inventory_value(player);
    player->money += estimated_value;
    free(inventory);
    player->inventory = create_inventory(INVENTORY_CAPACITY);
}

void sell_item(Player* player, int item_index) {
    Inventory* inventory = player->inventory;
    if (item_index < 0 || item_index >= inventory->index) {
        return;
    }

    Item_Stack* item_stack = inventory->items[item_index];
    player->money += item_stack->price;
    remove_item_from_inventory(inventory, item_index);
}

int estimate_inventory_value(Player* player) {
    int value = 0;
    Inventory* inventory = player->inventory;
    for (int i = 0; i < inventory->index; i++) {
        Item_Stack* item_stack = inventory->items[i];
        value += item_stack->price;
    }

    return value;
}