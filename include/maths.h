#ifndef MATHS_H
#define MATHS_H

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
 * Struct representing a pair of integers.
 * @param x The x value of the pair.
 * @param y The y value of the pair.
 */
typedef struct pair {
    int x, y;
} Pair;

/**
 * Check if a point is in a cuboid.
 * @param cuboid The cuboid to check.
 * @param x The x position of the point.
 * @param y The y position of the point.
 * @return 1 if the point is in the cuboid, 0 otherwise.
 */
int in_cuboid(Cuboid cuboid, int x, int y);

/**
 * Generate a random integer between min and max.
 * @param seed
 * @param min
 * @param max
 * @return A random integer between min and max.
 */
int random_int(int seed, int min, int max);

/**
 * Get the maximum of two integers.
 * @param a
 * @param b
 * @return the maximum of a and b.
 */
int max(int a, int b);

/**
 * Get the minimum of two integers.
 * @param a
 * @param b
 * @return  the minimum of a and b.
 */
int min(int a, int b);


unsigned int max2(unsigned int a, unsigned int b);


#endif //MATHS_H
