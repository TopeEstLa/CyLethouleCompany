#include <entities.h>
#include <stdlib.h>

Entity** entities;
int entities_count;
int entities_capacity;

void init_entities() {
    entities = malloc(sizeof(Entity*) * 10);
    entities_count = 0;
    entities_capacity = 10;
}

Entity* create_entity(Entity_Type type, void* data) {
    Entity* entity = malloc(sizeof(Entity));
    entity->type = type;
    entity->data = data;
    entity->x = -1;
    entity->y = -1;
    return entity;
}

bool add_entity(Entity* entity, int x, int y) {
    Entity* existing_entity = get_entity(x, y);

    if (existing_entity != NULL) {
        return false;
    }

    if (entities_count >= entities_capacity) {
        entities_capacity *= 2;
        entities = realloc(entities, sizeof(Entity*) * entities_capacity);
        if (entities == NULL) {
            return false;
        }
    }

    entity->x = x;
    entity->y = y;
    entities[entities_count++] = entity;

    return true;
}

bool remove_entity(Entity* entity, int x, int y) {


    return false;
}

Entity* get_entity(int x, int y) {
    for (int i = 0; i < entities_count; i++) {
        Entity* entity = entities[i];
        if (entity->x == x && entity->y == y) {
            return entity;
        }
    }

    return NULL;
}

void move_entity(Entity* entity, int new_x, int new_y) {
    Entity* existing_entity = get_entity(new_x, new_y);

    if (existing_entity != NULL) {
        return;
    }

    entity->x = new_x;
    entity->y = new_y;
}