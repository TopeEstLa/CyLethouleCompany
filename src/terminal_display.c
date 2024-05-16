#include <terminal_display.h>
#include <stdio.h>

#include <entities.h>

void print_all_map(Game_World *world) {
    if (world == NULL) {
        return;
    }

    for (int i = 0; i < world->width; ++i) {
        printf("%d ", i);
        printf(" ");
    }

    printf("\n");

    for (int y = 0; y < world->height; y++) {
        for (int x = 0; x < world->width; x++) {
            Entity *entity = get_entity(x, y);

            if (entity != NULL) {
                printf("%s", entity->texture);
                printf("  ");
                continue;
            }

            switch (world->chunk[x][y]->type) {
                case DOOR:
                    printf("D");
                    printf("  ");
                    break;
                case WALL:
                    printf("|");
                    printf("  ");
                    break;
                case VOID:
                    printf(" ");
                    printf("  ");
                    break;
                case EMPTY:
                    printf(" ");
                    printf("  ");
                    break;
                default:
                    printf("?");
                    printf("  ");
                    break;
            }
        }
        printf("\n");
    }
}

void print_visited_map(Game_World *world) {
    if (world == NULL) {
        return;
    }

    for (int i = 0; i < world->width; ++i) {
        printf("%d ", i);
        printf(" ");
    }

    printf("\n");

    for (int y = 0; y < world->height; y++) {
        for (int x = 0; x < world->width; x++) {
            Room* room = get_room(world, x, y);
            if (room == NULL) {
                printf(" ");
                printf("  ");
                continue;
            }

            if (!room->is_visited) {
                printf(" ");
                printf("  ");
            }

            Entity *entity = get_entity(x, y);

            if (entity != NULL) {
                printf("%s", entity->texture);
                printf("  ");
                continue;
            }

            switch (world->chunk[x][y]->type) {
                case DOOR:
                    printf("D");
                    printf("  ");
                    break;
                case WALL:
                    printf("|");
                    printf("  ");
                    break;
                case VOID:
                    printf(" ");
                    printf("  ");
                    break;
                case EMPTY:
                    printf(" ");
                    printf("  ");
                    break;
                default:
                    printf("?");
                    printf("  ");
                    break;
            }
        }
        printf("\n");
    }
}