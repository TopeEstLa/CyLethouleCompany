#include <world_generator.h>

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <world.h>
#include <terminal_display.h>

void base_generation(Game_World *world) {
    if (world == NULL) {
        return;
    }

    int baseX = world->width / 2;
    int baseY = world->height / 2;

    int roomSeed = world->seed;

    int width = random_int(roomSeed, MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
    int height = random_int(roomSeed, MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);

    baseX -= width / 2;
    baseY -= height / 2;

    int topDoorX, topDoorY, bottomDoorX, bottomDoorY, leftDoorX, leftDoorY, rightDoorX, rightDoorY;

    topDoorX = random_int(roomSeed, baseX + 1, baseX + width - 2);
    topDoorY = baseY;
    Pair topDoor = {topDoorX, topDoorY};

    bottomDoorX = random_int(roomSeed, baseX + 1, baseX + width - 2);
    bottomDoorY = baseY + height - 1;
    Pair bottomDoor = {bottomDoorX, bottomDoorY};

    leftDoorX = baseX;
    leftDoorY = random_int(roomSeed, baseY + 1, baseY + height - 2);
    Pair leftDoor = {leftDoorX, leftDoorY};

    rightDoorX = baseX + width - 1;
    rightDoorY = random_int(roomSeed, baseY + 1, baseY + height - 2);
    Pair rightDoor = {rightDoorX, rightDoorY};

    Room starting_room = create_room(width, height, baseX, baseY);

    starting_room.doors[TOP] = &topDoor;
    starting_room.doors[BOTTOM] = &bottomDoor;
    starting_room.doors[LEFT] = &leftDoor;
    starting_room.doors[RIGHT] = &rightDoor;

    append_room(world, starting_room);
    generate_rooms(world, starting_room, 3);
}

void generate_rooms(Game_World *world, Room starting_room, int recursion_depth) {
    if (world == NULL || recursion_depth <= 0) {
        return;
    }

    for (int i = 0; i < 4; ++i) {
        generate_room(world, starting_room, i, recursion_depth);
    }
}

void generate_room(Game_World *world, Room starting_room, int door_face, int recursion_depth) {
    Pair *looked_door = starting_room.doors[door_face];

    if (looked_door->x == -1 && looked_door->y == -1) {
        printf("Door not initialized\n");
        return;
    }

    int roomSeed = (world->seed + door_face + world->room_count) * world->room_capacity;

    int width = random_int((roomSeed + looked_door->x), MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
    int height = random_int((roomSeed + looked_door->y), MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);

    int doorNumber = random_int(roomSeed, 1, 4);

    int startX, startY;

    if ((door_face == 0 || door_face == 2) && ((looked_door->y - height) < 0 || (looked_door->x - width) < 0)) {
        prepend_world(world, abs(looked_door->x - width) + 1, abs(looked_door->y - height) + 1);
    }

    switch (door_face) {
        case TOP:
            startX = looked_door->x - width / 2;
            startY = looked_door->y - height;
            break;
        case BOTTOM:
            startX = looked_door->x - width / 2;
            startY = looked_door->y + 1;
            break;
        case LEFT:
            startX = looked_door->x - width; //+1; //+ 3; Depend of the seed wtf ?
            startY = looked_door->y - height / 2;
            break;
        case RIGHT:
            startX = looked_door->x + 1;
            startY = looked_door->y - height / 2;
            break;
        default:
            printf("Invalid door face\n");
            return;
    }

//    int* doors = random_door(door_face, doorNumber, roomSeed);

    Room new_room = create_room(width, height, startX, startY);



    /**
    for (int j = 0; j < doorNumber; ++j) {
        printf("Generating door %d for room %d\n", j, door_face);
        Pair new_door = {0, 0};

        int changingX = random_int(roomSeed, startX + 1, startX + width - 2);
        int changingY = random_int(roomSeed, startY + 1, startY + height - 2);

        if (doors[j] == door_face) {
            changingX = looked_door->x;
            changingY = looked_door->y;
        }

        switch (doors[j]) {
            case 0:
                new_door.x = changingX;
                new_door.y = startY;
                break;
            case 1:
                new_door.x = changingX;
                new_door.y = startY + height - 1;
                break;
            case 2:
                new_door.x = startX;
                new_door.y = changingY;
                break;
            case 3:
                new_door.x = startX + width - 1;
                new_door.y = changingY;
                break;
        }
        new_room.doors[j] = &new_door;
    } */


//    free(doors);

    int can_append = can_append_room(world, new_room);
    int fail = 0;
    while (can_append != 0 && fail < 300) {
        Room blocking_room = world->rooms[can_append];

        switch (door_face) {
            case TOP:
            case BOTTOM:
                if (new_room.x < blocking_room.x) {
                    new_room.x = blocking_room.x - new_room.width;
                } else {
                    new_room.x = blocking_room.x + blocking_room.width;
                }
                break;
            case LEFT:
            case RIGHT:
                if (new_room.y < blocking_room.y) {
                    new_room.y = blocking_room.y - new_room.height;
                } else {
                    new_room.y = blocking_room.y + blocking_room.height;
                }
                break;
            default:
                printf("Invalid door face\n");
        }

        if (door_face == LEFT) {
            if (new_room.height > MIN_ROOM_HEIGHT) {
                new_room.height -= 1;
            }
        } else if (door_face == RIGHT) {
            if (new_room.width > MIN_ROOM_WIDTH) {
                new_room.width -= 1;
            }
        } else {

            if (new_room.width > MIN_ROOM_WIDTH) {
                new_room.width -= 1;
            }

            if (new_room.height > MIN_ROOM_HEIGHT) {
                new_room.height -= 1;
            }
        }

        fail++;
        can_append = can_append_room(world, new_room);
    }

    int connectedDoorX = looked_door->x;
    int connectedDoorY = looked_door->y;

    switch (door_face) {
        case TOP:
            connectedDoorY = new_room.y + new_room.height;
            break;
        case BOTTOM:
            connectedDoorY = new_room.y - 1;
            break;
        case LEFT:
            connectedDoorX = new_room.x + new_room.width;
            break;
        case RIGHT:
            connectedDoorX = new_room.x - 1;
            break;
        default:
            printf("Invalid door face\n");
            return;
    }

    Pair connectedDoor = {connectedDoorX, connectedDoorY};
    new_room.doors[door_face] = &connectedDoor;

    if (append_room(world, new_room) != -1) {
        printf("Room appended\n");
    } else {
        printf("Room not appended\n");
    }
}


int *random_door(int forced_face, int max_door, int seed) {
    int *door = malloc(sizeof(int) * max_door);
    door[0] = forced_face;
    for (int i = 1; i < max_door; ++i) {
        int face_index;
        int max = 0;
        do {
            face_index = random_int(seed, 0, 3);
            max++;
        } while (face_index == forced_face && max++ < 10);
        door[i] = face_index;
    }

    return door;
}