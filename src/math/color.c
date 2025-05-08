#include "color.h"
#include "tuple.h"
#include <stdlib.h>

color_t* color(double red, double green, double blue) 
{
    return tuple(red, green, blue, 0.0);
}

void hadmard_product(color_t* c1, color_t* c2) 
{
 c1->x = (*c1).x * (*c2).x;
 c1->y = (*c1).y * (*c2).y;
 c1->z = (*c1).z * (*c2).z;
}

// note: should make c2 const. But then need to change all of the inputs of tuple as well..
void add_color(color_t* c1, color_t* c2)
{
  add_tuple(c1, c2);
}

// note: should make c2 const. But then need to change all of the inputs of tuple as well..
void subtract_color(color_t* c1, color_t* c2)
{
  subtract_tuple(c1, c2);
}