#ifndef MATHS_H
#define MATHS_H

/**
 * Generate a random integer between min and max.
 * @param seed The seed for the random generation.
 * @param mi The minimum value.
 * @param max The maximum value.
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

// ???
unsigned int max2(unsigned int a, unsigned int b);


#endif //MATHS_H
