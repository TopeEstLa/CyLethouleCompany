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

    clock_t current_time = clock();
    if (current_time >= game->end_time) {
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

    mvprintw(lignes_debut-1,(colonnes - strlen("Quota: %d %d"))/2, "Quota: %d/%d\n", game->player->money, game->needed_money);
    mvprintw(lignes_debut-2, (colonnes - strlen("Remaining time: %ds"))/2,"Remaining time: %ds\n", remaining_time);

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
        lignes_debut++;
    }

    int colonne_inv = (colonnes+colonnes/3)/3;
    for (int i = 0; i < player->inventory->index; ++i) {
        Item_Stack *item_stack = player->inventory->items[i];
        if (i == 0){
            mvprintw(lignes_debut+1, colonne_inv - strlen("INVENTORY : "),"INVENTORY : |%s %s|", item_stack->texture, item_stack->name);
        } else {
            colonne_inv = colonne_inv + strlen(player->inventory->items[i-1]->name) + strlen(player->inventory->items[i-1]->texture) + 2;
            mvprintw(lignes_debut+1, colonne_inv,"|%s %s|", item_stack->texture, item_stack->name);
        }
    }
}