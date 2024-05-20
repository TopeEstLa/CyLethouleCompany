#include <entities.h>
#include <stdlib.h>
#include <string.h>

Entity **entities = NULL;
int entities_count = 0;
int entities_capacity = 0;

void init_entities() {
    entities = malloc(sizeof(Entity *) * 10);
    entities_count = 0;
    entities_capacity = 10;
}

void cleanup_entities() {
    for (int i = 0; i < entities_count; i++) {
        free(entities[i]);
    }
    free(entities);

    entities = NULL;
    entities_count = 0;
    entities_capacity = 0;
}

Entity *create_entity(Entity_Type type, void *data, char *texture) {
    Entity *entity = malloc(sizeof(Entity));
    entity->type = type;
    entity->data = data;
    entity->texture = texture;
    entity->x = -1;
    entity->y = -1;
    entity->index = -1;
    return entity;
}

int add_entity(Game_World *world, Entity *entity, int x, int y) {
    if (x < 0 || x >= world->width || y < 0 || y >= world->height) {
        return -1;
    }

    Chunk *chunk = get_chunk(world, x, y);
    if (chunk == NULL) {
        return -1;
    }

    if (chunk->type == WALL || chunk->type == VOID) {
        return -1;
    }

    Entity *existing_entity = get_entity(x, y);

    if (existing_entity != NULL) {
        return -1;
    }

    if (entities_count >= entities_capacity) {
        entities_capacity *= 2;
        entities = realloc(entities, sizeof(Entity *) * entities_capacity);
        if (entities == NULL) {
            return -1;
        }
    }

    entity->x = x;
    entity->y = y;
    entity->index = entities_count;
    entities[entities_count] = entity;
    entities_count++;

    return entity->index;
}

bool remove_entity(int index) {
    if (index < 0 || index >= entities_count) {
        return false;
    }

    free(entities[index]);
    for (int i = index; i < entities_count-1; i++) {
        entities[i] = entities[i + 1];
        entities[i]->index = i;
    }

    entities_count--;
    return true;
}

Entity *get_entity(int x, int y) {
    for (int i = 0; i < entities_count; i++) {
        Entity *entity = entities[i];
        if (entity->x == x && entity->y == y) {
            return entity;
        }
    }

    return NULL;
}

Move_Callback move_entity(Game_World *world, Entity *entity, int new_x, int new_y) {
    Chunk *chunk = world->chunk[new_x][new_y];


    Move_Callback callback;
    callback.collided_entity = NULL;
    callback.reason = NO_REASON;
    callback.move_made = false;

    if (chunk == NULL) {
        return callback;
    }

    Entity *existing_entity = get_entity(new_x, new_y);

    if (existing_entity != NULL) {
        callback.collided_entity = existing_entity;
        callback.reason = ENTITY_COLLISION;


        if (existing_entity->type == ITEM) {
            callback.move_made = true;
            entity->x = new_x;
            entity->y = new_y;
            return callback;
        }

        return callback;
    }

    if (chunk->type == WALL || chunk->type == VOID) {
        callback.reason = WALL_COLLISION;
        return callback;
    }

    if (chunk->type == DOOR) {
        callback.reason = DOOR_COLLISION;
        callback.move_made = true;
        entity->x = new_x;
        entity->y = new_y;
        return callback;
    }

    entity->x = new_x;
    entity->y = new_y;
    callback.move_made = true;

    return callback;
}

void prepend_entity(int width_to_add, int height_to_add) {
    for (int i = entities_count - 1; i >= 0; i--) {
        Entity *entity = entities[i];
        entity->x += width_to_add;
        entity->y += height_to_add;
    }
}