#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdbool.h>

typedef enum entity_type {
    PLAYER,
    MONSTER,
    ITEM,
} Entity_Type;

typedef struct entity {
    Entity_Type type;
    void* data;
    int x, y;
} Entity;

void init_entities();

Entity* create_entity(Entity_Type type, void* data);

bool add_entity(Entity* entity, int x, int y);

bool remove_entity(Entity* entity, int x, int y);

Entity* get_entity(int x, int y);

void move_entity(Entity* entity, int new_x, int new_y);

#endif //ENTITIES_H
