#include <entities.h>
#include <stdlib.h>

Game_World* world;
Entity **entities;
int entities_count;
int entities_capacity;

void init_entities(Game_World *world_ptr) {
    world = world_ptr;

    entities = malloc(sizeof(Entity *) * 10);
    entities_count = 0;
    entities_capacity = 10;
}

Entity *create_entity(Entity_Type type, void *data, char texture) {
    Entity *entity = malloc(sizeof(Entity));
    entity->type = type;
    entity->data = data;
    entity->texture = texture;
    entity->x = -1;
    entity->y = -1;
    return entity;
}

bool add_entity(Entity *entity, int x, int y) {
    if (x < 0 || x >= world->width || y < 0 || y >= world->height) {
        return false;
    }

    Chunk *chunk = world->chunk[x][y];

    if (chunk->type != EMPTY) {
        return false;
    }

    Entity *existing_entity = get_entity(x, y);

    if (existing_entity != NULL) {
        return false;
    }

    if (entities_count >= entities_capacity) {
        entities_capacity *= 2;
        entities = realloc(entities, sizeof(Entity *) * entities_capacity);
        if (entities == NULL) {
            return false;
        }
    }

    entity->x = x;
    entity->y = y;
    entities[entities_count++] = entity;

    return true;
}

bool remove_entity(int x, int y) {
    for (int i = 0; i < entities_count; i++) {
        Entity *entity = entities[i];
        if (entity->x == x && entity->y == y) {
            free(entity);
            for (int j = i; j < entities_count - 1; j++) {
                entities[j] = entities[j + 1];
            }
            entities_count--;
            return true;
        }
    }

    return false;
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

Move_Callback move_entity(Entity *entity, int new_x, int new_y) {
    Entity *existing_entity = get_entity(new_x, new_y);

    Move_Callback callback;

    if (existing_entity != NULL) {
        callback.collided_entity = existing_entity;
        callback.move_made = false;
    } else {
        callback.collided_entity = NULL;
        callback.move_made = true;

        entity->x = new_x;
        entity->y = new_y;
    }

    return callback;
}