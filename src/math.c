#include <stdlib.h>
#include <stdio.h>

#include <math.h>

int in_cuboid(Cuboid cuboid, int x, int y) {
    return x >= cuboid.x1 && x < cuboid.x2 && y >= cuboid.y1 && y < cuboid.y2;
}

int random_int(int seed, int min, int max) {
    if (min > max) {
        printf("Error: min is greater than max\n");
        return min;
    }

    srand(seed);
    return min + rand() % (max - min + 1);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}