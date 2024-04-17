#ifndef MATH_H
#define MATH_H

/**
 * Struct representing a cuboid.
 * @param x1 The x1 position of the cuboid.
 * @param y1 The y1 position of the cuboid.
 * @param x2 The x2 position of the cuboid.
 * @param y2 The y2 position of the cuboid.
 */
typedef struct cuboid {
    int x1, y1;
    int x2, y2;
} Cuboid;

/**
 * Check if a point is in a cuboid.
 * @param cuboid The cuboid to check.
 * @param x The x position of the point.
 * @param y The y position of the point.
 * @return 1 if the point is in the cuboid, 0 otherwise.
 */
int in_cuboid(Cuboid cuboid, int x, int y);

#endif //MATH_H
