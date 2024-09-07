#include <stdio.h>
#include "tuple.h"

int main(int argc, char *argv[])
{
    tuple_t t = init_tuple(4.3, -4.2, 3.1, 1.0);

    printf("x: %f, y: %f, z: %f, w: %f\n", t.x, t.y, t.z, t.w);

    return 0;
}