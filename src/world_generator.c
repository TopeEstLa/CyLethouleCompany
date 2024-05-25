#include <world_generator.h>

#include <stdio.h>
#include <stdlib.h>
#include <maths.h>

#include <world.h>
#include <constant.h>

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

    bottomDoorX = random_int(roomSeed + 1, baseX + 4, baseX + width - 4);
    bottomDoorY = baseY + height - 1;

    leftDoorX = baseX;
    leftDoorY = random_int(roomSeed + 2, baseY + 4, baseY + height - 4);

    rightDoorX = baseX + width - 1;
    rightDoorY = random_int(roomSeed + 3, baseY + 4, baseY + height - 4);

    Room *starting_room = create_room(width, height, baseX, baseY);
    if (starting_room == NULL) {
        exit(100); //Can do nothing for this issue so we exit (exit code 100 = FAILED TO CREATE DEFAULT ROOM)
    }

    Door *topDoor = starting_room->doors[TOP];
    topDoor->x = topDoorX;
    topDoor->y = topDoorY;

    Door *bottomDoor = starting_room->doors[BOTTOM];
    bottomDoor->x = bottomDoorX;
    bottomDoor->y = bottomDoorY;

    Door *leftDoor = starting_room->doors[LEFT];
    leftDoor->x = leftDoorX;
    leftDoor->y = leftDoorY;

    Door *rightDoor = starting_room->doors[RIGHT];
    rightDoor->x = rightDoorX;
    rightDoor->y = rightDoorY;

    starting_room->is_visited = true;

    world->prepared_rooms_count = 1;
    append_room(world, starting_room);

    generate_rooms(world, starting_room, 1);

    if (MAX_ROOM == -1) {
        for (int i = 1; i < 5; i++) {
            Room *room = world->rooms[i];
            generate_rooms(world, room, PREGENERATION_DEPTH);
        }
    }
}

void generate_rooms(Game_World *world, Room *starting_room, int recursion_depth) {
    if (world == NULL || recursion_depth <= 0) {
        return;
    }

    for (int i = 0; i < 4; ++i) {
        Door *door = starting_room->doors[i];

        if (door == NULL) continue;

        if (i == starting_room->start_door) continue;
        if (door->x == -1 && door->y == -1) continue;
        if (door->is_used) continue;

        generate_room(world, starting_room, i, recursion_depth);
    }
}

void generate_room(Game_World *world, Room *starting_room, int door_face, int recursion_depth) {
    if (world == NULL || recursion_depth <= 0) {
        return;
    }

    Door *looked_door = starting_room->doors[door_face];

    if (looked_door->x == -1 && looked_door->y == -1) {
        return;
    }

    if (looked_door->is_used) return;

    if (starting_room->start_door == door_face) {
        return;
    }

    int roomSeed = (world->seed + door_face + world->room_count) * world->room_capacity;

    int width = random_int((roomSeed + looked_door->x), MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
    int height = random_int((roomSeed + looked_door->y), MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);

    if ((door_face == TOP || door_face == LEFT) && ((looked_door->y - height) < 0 || (looked_door->x - width) < 0)) {
        prepend_world(world, width + (width / 2), height + (height / 2));
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
            startY = looked_door->y - height / 2; //- 1;
            break;
        default:
            return;
    }

    Room *new_room = create_room(width, height, startX, startY);
    if (new_room == NULL) {
        world->chunk[looked_door->x][looked_door->y]->type = WALL;

        looked_door->x = -1;
        looked_door->y = -1;
        looked_door->is_used = false;
        world->prepared_rooms_count--;
        return;
    }

    int conflict_id = can_append_room(world, new_room);

    int fail = 0;
    while ((conflict_id != -1 && conflict_id != -2) && fail < 300) {
        Room *conflict_room = world->rooms[conflict_id];

        new_room = resize_room(new_room, conflict_room, door_face, looked_door);

        if (new_room == NULL) {
            world->chunk[looked_door->x][looked_door->y]->type = WALL;

            looked_door->x = -1;
            looked_door->y = -1;
            looked_door->is_used = false;
            world->prepared_rooms_count--;
            return;
        }

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

    Door *connectedDoor = new_room->doors[putted_door_face];

    connectedDoor->x = connectedDoorX;
    connectedDoor->y = connectedDoorY;
    connectedDoor->is_used = true;

    new_room->start_door = putted_door_face;

    int added_door = 0;
    int max_added_door = 4;

    if (MAX_ROOM != -1) {
        int dif = MAX_ROOM - world->prepared_rooms_count;
        if (dif < 0) dif = 0;
        max_added_door = dif;
    }

    for (int i = 0; i < 4; i++) {
        if (i == putted_door_face) continue;
        if (added_door >= max_added_door) break;

        int doorSeed = roomSeed + i + putted_door_face + looked_door->x + looked_door->y;

        int chance = random_int(doorSeed, 0, 1);
        if (chance == 0) continue;

        int doorX, doorY;
        switch (i) {
            case TOP:
                doorX = random_int(doorSeed + TOP, new_room->x + 1, new_room->x + new_room->width - 2);
                doorY = new_room->y;
                break;
            case BOTTOM:
                doorX = random_int(doorSeed + BOTTOM, new_room->x + 1, new_room->x + new_room->width - 2);
                doorY = new_room->y + new_room->height - 1;
                break;
            case LEFT:
                doorX = new_room->x;
                doorY = random_int(doorSeed + LEFT, new_room->y + 1, new_room->y + new_room->height - 2);
                break;
            case RIGHT:
                doorX = new_room->x + new_room->width - 1;
                doorY = random_int(doorSeed + RIGHT, new_room->y + 1, new_room->y + new_room->height - 2);
                break;
            default:
                return;
        }

        Door *door = new_room->doors[i];
        door->x = doorX;
        door->y = doorY;
        door->is_used = false;
        new_room->doors[i] = door;
        added_door++;
    }

    if (is_room_valid(new_room)) {
        if (append_room(world, new_room) != -1) {
            generate_rooms(world, new_room, recursion_depth - 1);
            looked_door->is_used = true;
        } else {
            world->chunk[looked_door->x][looked_door->y]->type = WALL;

            looked_door->x = -1;
            looked_door->y = -1;
            looked_door->is_used = false;
            world->prepared_rooms_count--;
        }
    } else {
        world->chunk[looked_door->x][looked_door->y]->type = WALL;

        looked_door->x = -1;
        looked_door->y = -1;
        looked_door->is_used = false;
        world->prepared_rooms_count--;
    }
}

Room *resize_room(Room *room, Room *conflictRoom, int door_face, Door *door) {

    int xRightC = conflictRoom->x + conflictRoom->width;
    int yBottomC = conflictRoom->y + conflictRoom->height;

    int xRightR = room->x + room->width;
    int yBottomR = room->y + room->height;

    if ((conflictRoom->x < xRightR && xRightC > room->x) && (conflictRoom->y < yBottomR && yBottomC > room->y)) {
        int left_overlap = max(conflictRoom->x, room->x);
        int right_overlap = min(xRightC, xRightR);
        int top_overlap = max(conflictRoom->y, room->y);
        int bottom_overlap = min(yBottomC, yBottomR);

        int overlap_width = right_overlap - left_overlap;
        int overlap_height = bottom_overlap - top_overlap;

        int new_width = room->width - overlap_width;
        int new_height = room->height - overlap_height;

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
                return NULL;
        }

        return create_room(new_width, new_height, new_x, new_y);
    }

    return room;
}

int is_room_valid(Room *room) {
    return room->width >= MIN_ROOM_WIDTH && room->height >= MIN_ROOM_HEIGHT;
}