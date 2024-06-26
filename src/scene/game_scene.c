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

char *format_time(int seconds) {
    char *result = (char *) malloc(12 * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    int minutes = seconds / 60;
    seconds = seconds % 60;

    if (minutes > 0) {
        snprintf(result, 12, "%dm %ds", minutes, seconds); //format a char* like printf("%d", ...)
    } else {
        snprintf(result, 12, "%ds", seconds);
    }

    return result;
}

char *concat_string(char *a, char *b, char *c) {
    char *result = (char *) malloc((strlen(a) + strlen(b) + strlen(c) + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    strcpy(result, a);
    strcat(result, b);
    strcat(result, c);

    return result;
}

char *format_timer(int remain_time) {
    char *formatted_time = format_time(remain_time);

    char *time_end_display = "";

    int formatted_time_size = strlen(formatted_time);

    if (formatted_time_size == 6) {
        time_end_display = malloc(3 * sizeof(char));
        if (time_end_display == NULL) {
            return "";
        }

        time_end_display[0] = ' ';
        time_end_display[1] = '|';
        time_end_display[2] = '\0';
    } else {
        time_end_display = malloc((6 - formatted_time_size) + 2 * sizeof(char));
        if (time_end_display == NULL) {
            return "";
        }

        for (int i = 0; i < 6 - formatted_time_size + 1; i++) {
            time_end_display[i] = ' ';
        }

        time_end_display[6 - formatted_time_size + 1] = '|';
        time_end_display[6 - formatted_time_size + 2] = '\0';
    }

    return concat_string("Temps restant: ", formatted_time, time_end_display);
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


    if (current_time.tv_sec > end.tv_sec ||
        (current_time.tv_sec == end.tv_sec && current_time.tv_usec >= end.tv_usec)) {
        set_current_scene(TIME_OVER);
        return;
    }


    int lines, cols;
    int dx = 40;
    int dy = 10;
    getmaxyx(stdscr, lines, cols);


    int x = player_entity->x;
    int y = player_entity->y;


    int cols_txt = dx;
    int col_start = cols / 2 - cols_txt;
    int lines_start = 6;
    int remaining_time = get_remaining_time();
    char *timer = format_timer(remaining_time);

    mvprintw(lines_start - 1, (cols - strlen(timer)) / 2, "|     Quota : %3d/%3d    |", game->player->money,
             game->needed_money);
    mvprintw(lines_start - 2, (cols - strlen(timer)) / 2, "|  %s", timer);
    mvprintw(lines_start - 3, (cols - strlen(timer)) / 2, "__________________________");


    if (world == NULL || player == NULL) {
        return;
    }


    for (int iy = y - dy; iy < y + dy - 1; iy++) {
        if (iy >= 0 && iy < world->height) {
            int current_cols = col_start;
            for (int ix = x - dx; ix < x + dx - 1; ix++) {
                if (ix >= 0 && ix < world->width) {
                    Room *room = get_room(world, ix, iy);

                    if (room == NULL || !room->is_visited) {
                        mvprintw(lines_start, current_cols, " ");
                        current_cols++;
                        continue;
                    }

                    Entity *entity = get_entity(ix, iy);
                    if (entity != NULL) {
                        mvprintw(lines_start, current_cols, "%s", entity->texture);
                    } else {
                        Chunk *chunk = get_chunk(world, ix, iy);

                        if (chunk == NULL) {
                            mvprintw(lines_start, current_cols, " ");
                            current_cols++;
                            continue;
                        }

                        switch (chunk->type) {
                            case DOOR:
                                mvprintw(lines_start, current_cols, "۩");
                                break;
                            case WALL:
                                if (chunk->direction == EAST || chunk->direction == WEST) {
                                    mvprintw(lines_start, current_cols, "║");
                                } else if (chunk->direction == NORTH || chunk->direction == SOUTH) {
                                    mvprintw(lines_start, current_cols, "═");
                                } else if (chunk->direction == NORTH_WEST) {
                                    mvprintw(lines_start, current_cols, "╔");
                                } else if (chunk->direction == NORTH_EAST) {
                                    mvprintw(lines_start, current_cols, "╗");
                                } else if (chunk->direction == SOUTH_WEST) {
                                    mvprintw(lines_start, current_cols, "╚");
                                } else if (chunk->direction == SOUTH_EAST) {
                                    mvprintw(lines_start, current_cols, "╝");
                                }
                                break;
                            case VOID:
                            case EMPTY:
                                mvprintw(lines_start, current_cols, " ");
                                break;
                            default:
                                mvprintw(lines_start, current_cols, "?");
                                break;
                        }
                    }
                    current_cols++;
                }
            }
            lines_start++;
        }
    }


    lines_start = 6;
    cols_txt = dx * 2;
    col_start = (cols - cols_txt) / 2;
    int colStartInventory = 0;
    for (int i = y - dy; i < y + dy; i++) {
        int current_cols = col_start;
        for (int j = x - dx; j < x + dx; j++) {
            if (j == x - dx || j == x + dx - 1) {
                mvprintw(lines_start, current_cols, "|");
            } else if (i == y - dy || i == y + dy - 1) {
                mvprintw(lines_start, current_cols, "-");
            }
            current_cols++;
        }
        colStartInventory = current_cols;
        lines_start++;
    }


    mvprintw(lines_start - 10, colStartInventory, "%s", player->name);
    mvprintw(lines_start - 9, colStartInventory, "%3d pv", player->health);
    mvprintw(lines_start - 8, colStartInventory, "%3d âme(s)", player->exp);
    mvprintw(lines_start - 7, colStartInventory, "Argent : %4d$", player->money);
    mvprintw(lines_start - 5, colStartInventory, "INVENTAIRE :");


    int lenghtA = 0;
    int lenghtB = 0;

    for (int i = 0; i < player->inventory->index; ++i) {
        Item_Stack *item_stack = player->inventory->items[i];
        mvprintw(lines_start - 4 + i, colStartInventory, "%s %s", item_stack->texture, item_stack->name);
        if (strcmp(item_stack->name, "Grand Axe") == 0) {
            lenghtA = strlen(item_stack->texture) + strlen(item_stack->name);
        } else if (strcmp(item_stack->name, "Bold") == 0) {
            lenghtB = strlen(item_stack->texture) + strlen(item_stack->name);
        }
    }


    max2(max2(max2(max2(max2(strlen("INVENTAIRE :"), max2(lenghtA, lenghtB)), strlen(player->name)), strlen("pv") + 4),
              strlen("âme(s)") + 4),
         strlen("Argent :") + 5);
    for (int i = 0; i < 11; i++) {
        mvprintw(lines_start - i - 1, colStartInventory + 1 + max2(max2(
                                                                           max2(max2(max2(strlen("INVENTAIRE :"), max2(lenghtA, lenghtB)), strlen(player->name)),
                                                                                strlen("pv") + 4), strlen("âme(s)") + 4),
                                                                   strlen("Argent :") + 5), "|");
    }
    for (int i = 0; i <= max2(max2(
                                      max2(max2(max2(strlen("INVENTAIRE :"), max2(lenghtA, lenghtB)), strlen(player->name)), strlen("pv") + 4),
                                      strlen("âme(s)") + 4),
                              strlen("Argent :") + 5); i++) {
        mvprintw(lines_start - 6, colStartInventory + i, "-");
    }
    for (int i = 0; i <= max2(max2(
                                      max2(max2(max2(strlen("INVENTAIRE :"), max2(lenghtA, lenghtB)), strlen(player->name)), strlen("pv") + 4),
                                      strlen("âme(s)") + 4),
                              strlen("Argent :") + 5); i++) {
        mvprintw(lines_start - 1, colStartInventory + i, "-");
    }
    for (int i = 0; i <= max2(max2(
                                      max2(max2(max2(strlen("INVENTAIRE :"), max2(lenghtA, lenghtB)), strlen(player->name)), strlen("pv") + 4),
                                      strlen("âme(s)") + 4),
                              strlen("Argent :") + 5); i++) {
        mvprintw(lines_start - 11, colStartInventory + i, "-");
    }
}