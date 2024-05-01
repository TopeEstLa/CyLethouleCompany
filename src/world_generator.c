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

    int roomCenterX = baseX + width / 2;
    int roomCenterY = baseY + height / 2;

    world->chunk[roomCenterX][roomCenterY]->type = WALL;

    generate_rooms(world, starting_room, 1);

    for (int i = 1; i < 5; i++) {
        Room room = world->rooms[i];
        generate_rooms(world, room, 3);
    }
}

void generate_rooms(Game_World *world, Room starting_room, int recursion_depth) {
    if (world == NULL || recursion_depth <= 0) {
        return;
    }

    for (int i = 0; i < 4; ++i) {
        Pair* door = starting_room.doors[i];

        if (door->x == -1 && door->y == -1) continue;

        generate_room(world, starting_room, i, recursion_depth);
    }
}

void generate_room(Game_World *world, Room starting_room, int door_face, int recursion_depth) {
    if (world == NULL || recursion_depth <= 0) {
        return;
    }

    Pair *looked_door = starting_room.doors[door_face];

    if (looked_door->x == -1 && looked_door->y == -1) {
        return;
    }

    if (starting_room.start_door==door_face) {
        return;
    }

    int roomSeed = (world->seed + door_face + world->room_count) * world->room_capacity;

    int width = random_int((roomSeed + looked_door->x), MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
    int height = random_int((roomSeed + looked_door->y), MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);

    if ((door_face == TOP || door_face == LEFT) && ((looked_door->y - height) < 0 || (looked_door->x - width) < 0)) {
        prepend_world(world, width + (width/2), height + (height/2));
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
            return;
    }

    Room new_room = create_room(width, height, startX, startY);

    int conflict_id = can_append_room(world, new_room);

    int fail = 0;
    while (conflict_id != -1 && fail < 300) {
        Room conflict_room = world->rooms[conflict_id];

        new_room = resize_room(new_room, conflict_room, door_face, looked_door);
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
    new_room.start_door = putted_door_face;

    for (int i = 0; i < 4; i++) {
        if (i == putted_door_face) continue;

        int doorSeed = roomSeed + i + putted_door_face + looked_door->x + looked_door->y;

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

        Pair *door = malloc(sizeof(Pair));
        door->x = doorX;
        door->y = doorY;
        new_room.doors[i] = door;
    }

    if (is_room_valid(new_room)) {
        if (append_room(world, new_room) != -1) {
            printf("Room appended\n");
            generate_rooms(world, new_room, recursion_depth - 1);
        } else {
            printf("Room not appended\n");
            printf("Removing doors lol\n");

            world->chunk[looked_door->x][looked_door->y]->type = WALL;

            Pair door = {-1, -1};
            starting_room.doors[door_face] = &door;
        }
    } else {
        printf("Room not appended\n");
        printf("Removing doors lol\n");

        world->chunk[looked_door->x][looked_door->y]->type = WALL;

        Pair door = {-1, -1};
        starting_room.doors[door_face] = &door;
    }
}

Room resize_room(Room room, Room conflictRoom, int door_face, Pair* door) {

    int xRightC = conflictRoom.x + conflictRoom.width;
    int yBottomC = conflictRoom.y + conflictRoom.height;

    int xRightR = room.x + room.width;
    int yBottomR = room.y + room.height;

    if ((conflictRoom.x < xRightR && xRightC > room.x) && (conflictRoom.y < yBottomR && yBottomC > room.y)) {
        int left_overlap = max(conflictRoom.x, room.x);
        int right_overlap = min(xRightC, xRightR);
        int top_overlap = max(conflictRoom.y, room.y);
        int bottom_overlap = min(yBottomC, yBottomR);

        int overlap_width = right_overlap - left_overlap;
        int overlap_height = bottom_overlap - top_overlap;

        int new_width = room.width - overlap_width;
        int new_height = room.height - overlap_height;

        int new_x, new_y;

        switch (door_face) {
            case TOP:
                new_x = door->x - new_width / 2;
                new_y = door->y - new_height;
                break;
            case BOTTOM:
                new_x = door->x - new_width / 2;
                new_y = door->y + 1;
                break;
            case LEFT:
                new_x = door->x - new_width;
                new_y = door->y - new_height / 2;
                break;
            case RIGHT:
                new_x = door->x + 1;
                new_y = door->y - new_height / 2 - 1;
                break;
            default:
                printf("Invalid door face\n");
        }

        return create_room(new_width, new_height, new_x, new_y);
    }

    return room;
}

int is_room_valid(Room room) {
    return room.width >= MIN_ROOM_WIDTH && room.height >= MIN_ROOM_HEIGHT;
}