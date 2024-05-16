#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdbool.h>
#include <world.h>

typedef enum entity_type {
    PLAYER,
    MONSTER,
    ITEM,
} Entity_Type;

typedef struct entity {
    Entity_Type type;
    void *data;
    char *texture;
    int x, y;
} Entity;

typedef enum cancel_move_reason {
    ENTITY_COLLISION,
    WALL_COLLISION,
    DOOR_COLLISION,
    NO_REASON,
} Cancel_Move_Reason;

typedef struct move_callback {
    Entity *collided_entity;
    Cancel_Move_Reason reason;
    bool move_made;
} Move_Callback;

void init_entities();

void cleanup_entities();

Entity *create_entity(Entity_Type type, void *data, char *texture);

int add_entity(Game_World *world, Entity *entity, int x, int y);

bool remove_entity(int entity_id);

Entity *get_entity(int x, int y);

Move_Callback move_entity(Game_World *gameWorld, Entity *entity, int new_x, int new_y);

void prepend_entity(int width_to_add, int height_to_add);

#endif //ENTITIES_H
