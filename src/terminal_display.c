#include <terminal_display.h>
#include <stdio.h>

void print_all_map(Game_World* world) {
    if (world == NULL) {
        return;
    }

    for (int i = 0; i < world->width; ++i) {
        printf("%d ", i);
        printf(" ");
    }

    printf("\n");

    for (int i = 0; i < world->height; i++) {
        for (int j = 0; j < world->width; j++) {
            switch (world->chunk[j][i]->type) {
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

void print_visited_map(Game_World* world) {
    if (world == NULL) {
        return;
    }

    for (int i = 0; i < world->width; ++i) {
        printf("%d ", i);
        printf(" ");
    }

    printf("\n");

    for (int i = 0; i < world->height; i++) {
        for (int j = 0; j < world->width; j++) {
            Room room = get_room(world, j, i);
            if ((room.x != -1 && room.y != -1) && !room.is_visited) {
                printf(" ");
                printf("  ");
                continue;
            }
            switch (world->chunk[j][i]->type) {
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