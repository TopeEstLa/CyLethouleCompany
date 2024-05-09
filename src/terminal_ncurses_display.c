#include <terminal_ncurses_display.h>

#include <curses.h>

void curses_all_map(Game_World* world) {
    if (world == NULL) {
        return;
    }


    clear();

    for (int y = 0; y < world->height; y++) {
        for (int x = 0; x < world->width; x++) {
            Entity *entity = get_entity(x, y);

            if (entity != NULL) {
                printw("%c", entity->texture);
                continue;
            }

            switch (world->chunk[x][y]->type) {
                case DOOR:
                    printw("D");
                    break;
                case WALL:
                    mvprintw(x, y, "|");
                    break;
                case VOID:
                    mvprintw(x, y, " ");
                    break;
                case EMPTY:
                    mvprintw(x, y, " ");
                    break;
                default:
                    mvprintw(x, y, "?");
                    break;
            }
        }
    }

    refresh();
}
