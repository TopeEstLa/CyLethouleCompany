#ifndef SHOP_H
#define SHOP_H

#include <world.h>
#include <player.h>

#define TRADER_TEXTURE "T"

bool spawn_shop(Game_World *world);

void open_shop(Player* player);

int estimate_inventory_value(Player* player);

void sell_inventory(Player* player);

void sell_item(Player* player, int item_index);

#endif //SHOP_H
