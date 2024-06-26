#include <stdlib.h>

#include <maths.h>


int random_int(int seed, int min, int max) {
    int used_min = min;
    int used_max = max;

    if (min > max) {
        used_min = max;
        used_max = min;
    }

    srand(seed);
    return used_min + rand() % (used_max - used_min + 1);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

unsigned int max2(unsigned int a, unsigned int b) {
    if (a > b) {
        return a;
    } else if (a < b) {
        return b;
    } else {
        return a;
    }
}