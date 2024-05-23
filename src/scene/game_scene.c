#include <scene/game_scene.h>

#include <curses.h>
#include <ncurses_display.h>
#include <string.h>

#include <game_controller.h>

#include <locale.h>

void handle_game_input() {

    Game_Data *game = get_game_data();

    int ch = getch();
    if (ch == ERR)
        return;

    Player *player = game->player;
    Entity *playerEntity = player->entity;

    switch (ch) {
        case 27:
            set_current_scene(PAUSE_MENU);
            break;
        case KEY_UP:
            move_player(playerEntity->x, playerEntity->y - 1);
            break;
        case KEY_DOWN:
            move_player(playerEntity->x, playerEntity->y + 1);
            break;
        case KEY_LEFT:
            move_player(playerEntity->x - 1, playerEntity->y);
            break;
        case KEY_RIGHT:
            move_player(playerEntity->x + 1, playerEntity->y);
            break;
        default:
            break;
    }
}

void game_scene_curses() {
    if (!is_game_loaded()) {
        set_current_scene(MAIN_MENU);
        return;
    }

    Game_Data *game = get_game_data();
    Game_World *world = game->world;
    Player *player = game->player;
    Entity *player_entity = player->entity;

    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    struct timeval end = game->end_time;

    if (current_time.tv_sec > end.tv_sec || (current_time.tv_sec == end.tv_sec && current_time.tv_usec >= end.tv_usec)) {
        set_current_scene(TIME_OVER);
        return;
    }

    int lignes, colonnes;
    int dx = 40;
    int dy = 10;
    getmaxyx(stdscr, lignes, colonnes);

    int x = player_entity->x;
    int y = player_entity->y;

    int colonnes_text = dx;
    int colonnes_debut =  colonnes/2 - colonnes_text;
    int lignes_debut = 6;
    int remaining_time = get_remaining_time();

    mvprintw(lignes_debut-1,(colonnes - strlen("Remaining time: %ds   "))/2, "|     Quota : %3d/%3d    |", game->player->money, game->needed_money);
    mvprintw(lignes_debut-2, (colonnes - strlen("Remaining time: %ds   "))/2,"| Remaining time: %3ds   |", remaining_time);
    mvprintw(lignes_debut-3, (colonnes - strlen("Remaining time: %ds   "))/2,"__________________________", remaining_time);

    if (world == NULL || player == NULL) {
        return;
    }





    for (int iy = y - dy; iy < y + dy - 1; iy++) {
        if (iy >= 0 && iy < world->height) {
            int current_colonnes = colonnes_debut;
            for (int ix = x - dx; ix < x + dx - 1; ix++) {
                if (ix >= 0 && ix < world->width) {
                    Room *room = get_room(world, ix, iy);

                    if (room == NULL || !room->is_visited) {
                        mvprintw(lignes_debut, current_colonnes, " ");
                        current_colonnes++;
                        continue;
                    }

                    Entity *entity = get_entity(ix, iy);
                    if (entity != NULL) {
                        mvprintw(lignes_debut, current_colonnes, "%s", entity->texture);
                    } else {
                        Chunk *chunk = get_chunk(world, ix, iy);

                        if (chunk == NULL) {
                            mvprintw(lignes_debut, current_colonnes, " ");
                            current_colonnes++;
                            continue;
                        }

                        switch (chunk->type) {
                            case DOOR:
                                mvprintw(lignes_debut, current_colonnes, "۩");
                                break;
                            case WALL:
                                if (chunk->direction == EAST || chunk->direction == WEST) {
                                    mvprintw(lignes_debut, current_colonnes, "║");
                                } else if (chunk->direction == NORTH || chunk->direction == SOUTH) {
                                    mvprintw(lignes_debut, current_colonnes, "═");
                                } else if (chunk->direction == NORTH_WEST) {
                                    mvprintw(lignes_debut, current_colonnes, "╔");
                                } else if (chunk->direction == NORTH_EAST) {
                                    mvprintw(lignes_debut, current_colonnes, "╗");
                                } else if (chunk->direction == SOUTH_WEST) {
                                    mvprintw(lignes_debut, current_colonnes, "╚");
                                } else if (chunk->direction == SOUTH_EAST) {
                                    mvprintw(lignes_debut, current_colonnes, "╝");
                                }
                                break;
                            case VOID:
                            case EMPTY:
                                mvprintw(lignes_debut, current_colonnes, " ");
                                break;
                            default:
                                mvprintw(lignes_debut, current_colonnes, "?");
                                break;
                        }
                    }
                    current_colonnes++;
                }
            }
            lignes_debut++;
        }
    }

    lignes_debut = 6;
    colonnes_text = dx * 2;
    colonnes_debut = (colonnes - colonnes_text) / 2;
    int colStartInventory = 0;
    for (int i = y - dy; i < y + dy; i++) {
        int current_colonnes = colonnes_debut;
        for (int j = x - dx; j < x + dx; j++) {
            if (j == x - dx || j == x + dx - 1) {
                mvprintw(lignes_debut, current_colonnes, "|");
            } else if (i == y - dy || i == y + dy - 1) {
                mvprintw(lignes_debut, current_colonnes, "-");
            }
            current_colonnes++;
        }
        colStartInventory = current_colonnes;
        lignes_debut++;
    }
    mvprintw(lignes_debut, colonnes/2 - strlen(player->name) - strlen("The player has"), "The player %s has : %4d pv", player->name, player->health);
    mvprintw(lignes_debut+1, colonnes/2 - strlen(player->name) - strlen("The player has"), "The player %s has : %4d exp", player->name, player->exp);
    mvprintw(lignes_debut+2, colonnes/2 - strlen(player->name) - strlen("Money :"), "Money : %4d$", player->money);
    mvprintw(lignes_debut-5, colStartInventory+1,"INVENTORY");
    int lenghtA = 0;
    int lenghtB = 0;
    for (int i = 0; i < player->inventory->index; ++i) {
        Item_Stack *item_stack = player->inventory->items[i];
            mvprintw(lignes_debut-i-2, colStartInventory+1,"%s %s", item_stack->texture, item_stack->name);
        if (strcmp(item_stack->name, "Grand Axe") == 0){
            lenghtA =  strlen(item_stack->texture)+ strlen(item_stack->name);
        } else if (strcmp(item_stack->name, "Bold") == 0){
            lenghtB =  strlen(item_stack->texture)+ strlen(item_stack->name);
        }
    }

    /*for (int i = lignes_debut - 6; i < lignes_debut; i++){
        for (int j = colStartInventory+1; j < max2(strlen("INVENTORY"), max2 (lenghtA, lenghtB)); j++){
            if (j == (max2(strlen("INVENTORY"), max2 (lenghtA, lenghtB)))-1){
                mvprintw(i, j+1 , "|");
            } else if (i == lignes_debut-6 || i == lignes_debut){
                mvprintw(i, j + 1 , "_");
            }
        }
    }*/
    for (int i = 0; i < 6; i++){
        mvprintw(lignes_debut-i-1, colStartInventory+1+max2(strlen("INVENTORY"), max2 (lenghtA, lenghtB)),"|");
    }
    for (int i = 0; i <= max2(strlen("INVENTORY"), max2 (lenghtA, lenghtB)) ; i++){
        mvprintw(lignes_debut-6, colStartInventory+i,"-");
    }
    for (int i = 0; i <= max2(strlen("INVENTORY"), max2 (lenghtA, lenghtB)) ; i++){
        mvprintw(lignes_debut-1, colStartInventory+i,"-");
    }
}