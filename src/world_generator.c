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

    int width = random_int(roomSeed, MIN_ROOM_WIDTH + 5, MAX_ROOM_WIDTH + 5);
    int height = random_int(roomSeed, MIN_ROOM_HEIGHT + 5, MAX_ROOM_HEIGHT + 5);

    baseX -= width / 2;
    baseY -= height / 2;

    int topDoorX, topDoorY, bottomDoorX, bottomDoorY, leftDoorX, leftDoorY, rightDoorX, rightDoorY;

    topDoorX = random_int(roomSeed, baseX + 4, baseX + width - 4);
    topDoorY = baseY;
    Pair topDoor = {topDoorX, topDoorY};

    bottomDoorX = random_int(roomSeed, baseX + 4, baseX + width - 4);
    bottomDoorY = baseY + height - 1;
    Pair bottomDoor = {bottomDoorX, bottomDoorY};

    leftDoorX = baseX;
    leftDoorY = random_int(roomSeed, baseY + 4, baseY + height - 4);
    Pair leftDoor = {leftDoorX, leftDoorY};

    rightDoorX = baseX + width - 1;
    rightDoorY = random_int(roomSeed, baseY + 4, baseY + height - 4);
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

/**
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

    int startX = starting_room.x;
    int startY = starting_room.y;

    if ((door_face == 0 || door_face == 2) && ((looked_door->y - height) < 0 || (looked_door->x - width) < 0)) {
        prepend_world(world, abs(looked_door->x - width) + 1, abs(looked_door->y - height) + 1);
    }

    switch (door_face) {
        case TOP:
            startX += looked_door->x;
            startY -= height;
            break;
        case BOTTOM:
            startX += looked_door->x;
            startY += starting_room.height;
            break;
        case LEFT:
            startX += width; //+1; //+ 3; Depend of the seed wtf ?
            startY += looked_door->y;
            break;
        case RIGHT:
            startX = starting_room.width;
            startY = looked_door->y;
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
    }


//    free(doors);

    int can_append = 0;
    int fail = 0;
    while (can_append != 0 && fail < 300) {


        fail++;
        can_append = can_append_room(world, new_room);
    }

    /**
    int connectedDoorX = looked_door->x;
    int connectedDoorY = looked_door->y;

    switch (door_face) {
        case TOP:
            connectedDoorY -= 1;
            break;
        case BOTTOM:
            connectedDoorY += 1;
            break;
        case LEFT:
            connectedDoorX -= 1;
            break;
        case RIGHT:
            connectedDoorX += 1;
            break;
        default:
            printf("Invalid door face\n");
            return;
    }

    Pair* connectedDoor = malloc(sizeof(Pair));

    connectedDoor->x = connectedDoorX;
    connectedDoor->y = connectedDoorY;

    new_room.doors[door_face] = connectedDoor;

    if (append_room(world, new_room) != -1) {
        printf("Room appended\n");
    } else {
        printf("Room not appended\n");
    }
} */

void generate_room(Game_World *world, Room starting_room, int door_face, int recursion_depth) {
    Pair *looked_door = starting_room.doors[door_face];

    if (looked_door->x == -1 && looked_door->y == -1) {
        printf("Door not initialized\n");
        return;
    }

    int roomSeed = (world->seed + door_face + world->room_count) * world->room_capacity;

    int width = random_int((roomSeed + looked_door->x), MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
    int height = random_int((roomSeed + looked_door->y), MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);

    if ((door_face == TOP || door_face == LEFT) && ((looked_door->y - height) < 0 || (looked_door->x - width) < 0)) {
        prepend_world(world, abs(looked_door->x - width), abs(looked_door->y - height));
    }

    int startX, startY;

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
            startX = looked_door->x - width;
            startY = looked_door->y - height / 2;
            break;
        case RIGHT:
            startX = looked_door->x + 1;
            startY = looked_door->y - height / 2 - 1;
            break;
        default:
            printf("Invalid door face\n");
            return;
    }

    Room new_room = create_room(width, height, startX, startY);

    int conflict_id = can_append_room(world, new_room);

    int fail = 0;
    while (conflict_id != -1 && fail < 300) {
        Room conflict_room = world->rooms[conflict_id];

        /** TODO: Resize the room to avoid conflict
        int resize_startX = startX;
        int resize_startY = startY;

        int resize_width = width;
        int resize_height = height;


        if (new_room.x < conflict_room.x + conflict_room.width && new_room.x + new_room.width > conflict_room.x) {
            printf("Conflict on the x axis\n");
            resize_startX = conflict_room.x + conflict_room.width + 1;
        }

        if (new_room.y < conflict_room.y + conflict_room.height && new_room.y + new_room.height > conflict_room.y) {
            printf("Conflict on the y axis\n");
            resize_startY = conflict_room.y + conflict_room.height + 1;
        }



        /*
        if (new_room.x > conflict_room.x && new_room.x < conflict_room.x + conflict_room.width) {
            printf("Conflict on the x axis with startX\n");
            resize_startX = conflict_room.x + conflict_room.width + 1;
        }
        if (new_room.x + new_room.width > conflict_room.x &&
            new_room.x + new_room.width < conflict_room.x + conflict_room.width) {
            printf("Conflict on the x axis with endX\n");
            resize_width = conflict_room.x - new_room.x - 1;
        }

        if (new_room.y > conflict_room.y && new_room.y < conflict_room.y + conflict_room.height) {
            printf("Conflict on the y axis with startY\n");
            resize_startY = conflict_room.y + conflict_room.height + 1;
        }

        if (new_room.y + new_room.height > conflict_room.y &&
            new_room.y + new_room.height < conflict_room.y + conflict_room.height) {
            printf("Conflict on the y axis with endY\n");
            resize_height = conflict_room.y - new_room.y - 1;
        } */


        int resize_width = random_int((roomSeed + looked_door->x + conflict_id), MIN_ROOM_WIDTH - 1,
                                      MAX_ROOM_WIDTH - 1);
        int resize_height = random_int((roomSeed + looked_door->y + conflict_id), MIN_ROOM_HEIGHT - 1,
                                       MAX_ROOM_HEIGHT - 1);

        int resize_startX, resize_startY;

        switch (door_face) {
            case TOP:
                resize_startX = looked_door->x - width / 2;
                resize_startY = looked_door->y - height - fail; // Move the room up
                break;
            case BOTTOM:
                resize_startX = looked_door->x - width / 2;
                resize_startY = looked_door->y + 1 + fail; // Move the room down
                break;
            case LEFT:
                resize_startX = looked_door->x - width - fail; // Move the room to the left
                resize_startY = looked_door->y - height / 2;
                break;
            case RIGHT:
                resize_startX = looked_door->x + 1 + fail; // Move the room to the right
                resize_startY = looked_door->y - height / 2 - 1;
                break;
            default:
                printf("Invalid door face\n");
                return;
        }

        new_room = create_room(resize_width, resize_height, resize_startX, resize_startY);
        conflict_id = can_append_room(world, new_room);
        fail++;
    }


    int connectedDoorX = looked_door->x;
    int connectedDoorY = looked_door->y;

    switch (door_face) {
        case TOP:
            connectedDoorY -= 1;
            break;
        case BOTTOM:
            connectedDoorY += 1;
            break;
        case LEFT:
            connectedDoorX -= 1;
            break;
        case RIGHT:
            connectedDoorX += 1;
            break;
        default:
            printf("Invalid door face\n");
            return;
    }

    Pair *connectedDoor = malloc(sizeof(Pair));

    connectedDoor->x = connectedDoorX;
    connectedDoor->y = connectedDoorY;

    int putted_door_face;

    switch (door_face) {
        case TOP:
            putted_door_face = BOTTOM;
            break;
        case BOTTOM:
            putted_door_face = TOP;
            break;
        case LEFT:
            putted_door_face = RIGHT;
            break;
        case RIGHT:
            putted_door_face = LEFT;
            break;
    }

    new_room.doors[putted_door_face] = connectedDoor;

    for (int i = 0; i < 4; i++) {
        if (i == putted_door_face) continue;

        int doorSeed = roomSeed+i+putted_door_face+looked_door->x+looked_door->y;

        int chance = random_int(doorSeed, 0, 1);
        if (chance == 0) continue;

        int doorX, doorY;
        switch (i) {
            case TOP:
                doorX = random_int(doorSeed, new_room.x + 1, new_room.x + new_room.width - 2);
                doorY = new_room.y;
                break;
            case BOTTOM:
                doorX = random_int(doorSeed, new_room.x + 1, new_room.x + new_room.width - 2);
                doorY = new_room.y + new_room.height - 1;
                break;
            case LEFT:
                doorX = new_room.x;
                doorY = random_int(doorSeed, new_room.y + 1, new_room.y + new_room.height - 2);
                break;
            case RIGHT:
                doorX = new_room.x + new_room.width - 1;
                doorY = random_int(doorSeed, new_room.y + 1, new_room.y + new_room.height - 2);
                break;
            default:
                printf("Invalid door face\n");
                return;
        }

        Pair* door = malloc(sizeof(Pair));
        door->x = doorX;
        door->y = doorY;
        new_room.doors[i] = door;
    }

    printf("Door Face: %d\n", door_face);
    printf("Fail: %d\n", fail);

    if (append_room(world, new_room) != -1) {
        printf("Room appended\n");
    } else {
        printf("Room not appended\n");
        printf("Room INFO:\n");
        printf("Width: %d\n", new_room.width);
        printf("Height: %d\n", new_room.height);
        printf("X: %d\n", new_room.x);
        printf("Y: %d\n", new_room.y);
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