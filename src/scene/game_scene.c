#include <scene/game_scene.h>

#include <curses.h>
#include <ncurses_display.h>

#include <game_controller.h>

void handle_game_input() {
    Game *game = get_game();

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
    Game *game = get_game();
    Game_World *world = game->world;
    Entity* player = game->player->entity;

    int dx = 20;
    int dy = 20;
    int x =  player->x;
    int y =  player->y;


    int lignes, colonnes;
    getmaxyx(stdscr, lignes, colonnes);
    int colonnes_text = dx * 2;
    int colonnes_debut = (colonnes - colonnes_text) / 2;
    int lignes_debut = 6;
    for (int iy = y - dy; iy < y + dy - 1; iy++) {

        if (iy >= 0 && iy < world->height) {

            for (int ix = x - dx; ix < x + dx - 1; ix++) {
                if (ix >= 0 && ix < world->width) {
                    Room *room = get_room(world, ix, iy);

                    if (room == NULL) {
                        mvprintw(lignes_debut, colonnes_debut, " ");
                        mvprintw(lignes_debut, colonnes_debut, "  ");
                        colonnes_debut++;
                        continue;
                    }

                    if (!room->is_visited) {
                        mvprintw(lignes_debut, colonnes_debut, " ");
                        mvprintw(lignes_debut, colonnes_debut, "  ");
                        colonnes_debut++;
                        continue;
                    }

                    Entity *entity = get_entity(ix, iy);
                    if (entity != NULL) {
                        mvprintw(lignes_debut, colonnes_debut, "%s", entity->texture);
                        colonnes_debut++;
                    } else {
                        switch (world->chunk[ix][iy]->type) {
                            case DOOR :
                                mvprintw(lignes_debut, colonnes_debut, "D");
                                colonnes_debut++;
                                break;
                            case WALL :
                                mvprintw(lignes_debut, colonnes_debut, "|");
                                colonnes_debut++;
                                break;
                            case VOID :
                                mvprintw(lignes_debut, colonnes_debut, " ");
                                colonnes_debut++;
                                break;
                            case EMPTY :
                                mvprintw(lignes_debut, colonnes_debut, " ");
                                colonnes_debut++;
                                break;
                            default :
                                mvprintw(lignes_debut, colonnes_debut, "?");
                                colonnes_debut++;
                                break;
                        }
                    }
                }
            }
            lignes_debut++;
            colonnes_debut = (colonnes - colonnes_text) / 2;
        }
        int lignes_debut = 6;
        for (int i = y - dy; i < y + dy; i++) {
            for (int j = x - dx; j < x + dx; j++) {
                if (j == x - dx || j == x + dx - 1) {
                    mvprintw(lignes_debut, colonnes_debut, "|");
                    colonnes_debut++;
                } else if (i == y - dy || i == y + dy - 1) {
                    mvprintw(lignes_debut, colonnes_debut, "-");
                    colonnes_debut++;
                } else {
                    colonnes_debut++;
                }
            }
            colonnes_debut = (colonnes - colonnes_text) / 2;
            lignes_debut++;
        }
    }
}