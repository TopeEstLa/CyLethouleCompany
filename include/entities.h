#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdbool.h>
#include <world.h>

/**
 * The type of entity in the world
 */
typedef enum entity_type {
    TRADER,
    PLAYER,
    MONSTER,
    ITEM,
} Entity_Type;

/**
 * The entity in the world
 * @para type The type of entity
 * @para data void* -> The value accept all type of pointer
 * @param texture The texture of the entity
 * @param index The index of the entity
 * @param x The x position of the entity
 */
typedef struct entity {
    Entity_Type type;
    void *data;
    char *texture;
    int index;
    int x, y;
} Entity;

/**
 * The reason why the move was canceled
 */
typedef enum cancel_move_reason {
    ENTITY_COLLISION,
    WALL_COLLISION,
    DOOR_COLLISION,
    NO_REASON,
} Cancel_Move_Reason;

/**
 * The callback for the move_entity function
 * @param collided_entity The entity that was collided with
 * @param reason The reason why the move was canceled
 * @param move_made Whether the move was made
 */
typedef struct move_callback {
    Entity *collided_entity;
    Cancel_Move_Reason reason;
    bool move_made;
} Move_Callback;

/**
 * Initialize entities list
 * with a default capacity of 10
 */
void init_entities();

/**
 * Free the memory of the entities list
 */
void cleanup_entities();

/**
 * Create a new entity
 * @param type entity type
 * @param data special entity data
 * @param texture entity texture
 * @return the new entity
 */
Entity *create_entity(Entity_Type type, void *data, char *texture);

/**
 * Add an entity to the world
 * @param world world to add the entity
 * @param entity entity to add
 * @param x x coordinate
 * @param y  y coordinate
 * @return the entity index in the array
 */
int add_entity(Game_World *world, Entity *entity, int x, int y);

/**
 * Remove an entity from the world
 * @param entity_id entity index returned by add_entity
 * @return true if the entity was removed
 */
bool remove_entity(int entity_id);

/**
 * Get an entity at a specific position
 * @param x
 * @param y
 * @return Entity at the position or NULL
 */
Entity *get_entity(int x, int y);

/**
 * Move an entity to a new position
 * @param world world to move the entity
 * @param entity entity to move
 * @param new_x new x position
 * @param new_y new y position
 * @return Move_Callback with the result of the move (collided entity, reason, move made)
 */
Move_Callback move_entity(Game_World *world, Entity *entity, int new_x, int new_y);

/**
 * When the world prepend, change the position of the entities
 * @param width_to_add
 * @param height_to_add
 */
void prepend_entity(int width_to_add, int height_to_add);

#endif //ENTITIES_H
