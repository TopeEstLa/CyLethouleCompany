#include <world_generator.h>

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <world.h>

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

    starting_room.doors[0] = topDoor;
    starting_room.doors[1] = bottomDoor;
    starting_room.doors[2] = leftDoor;
    starting_room.doors[3] = rightDoor;

    append_room(world, starting_room);
    generate_room(world, starting_room, 3);
}

void generate_room(Game_World* world, Room starting_room, int recursion_depth) {
    if (world == NULL || recursion_depth <= 0) {
        return;
    }

    //Generate a room for each door
    for (int i = 0; i < 4; ++i) {
        Pair door = starting_room.doors[i];
        if (door.x == -1 && door.y == -1) {
            continue;
        }

        printf("Door at %d, %d\n", door.x, door.y);
    }
}