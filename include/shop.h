#ifndef SHOP_H
#define SHOP_H

#include <world.h>
#include <player.h>

#define TRADER_TEXTURE "T"

/**
 * Spawn a shop in the world.
 * @param world the world to spawn the shop in
 * @return true if the shop has been spawned, false otherwise
 */
bool spawn_shop(Game_World *world);

/**
 * Open the shop for the player.
 * @param player
 */
void open_shop(Player* player);

/**
 * Estimate the value of the player's inventory.
 * @param player
 * @return total value of the inventory
 */
int estimate_inventory_value(Player* player);

/**
 * Sell an item from the player's inventory.
 * @param player
 */
void sell_inventory(Player* player);

/**
 * Sell an item from the player's inventory.
 * @param player
 * @param item_index index of the item to sell
 */
void sell_item(Player* player, int item_index);

#endif //SHOP_H
