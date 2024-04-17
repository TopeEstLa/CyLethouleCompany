#include <math.h>

int in_cuboid(Cuboid cuboid, int x, int y) {
    return x >= cuboid.x1 && x < cuboid.x2 && y >= cuboid.y1 && y < cuboid.y2;
}
