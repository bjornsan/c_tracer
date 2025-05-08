#ifndef COLOR_H
#define COLOR_H

#include "tuple.h"

color_t* color(double red, double green, double blue);
void add_color(color_t* c1, color_t* c2);
void subtract_color(color_t* c1, color_t* c2);
void hadmard_product(color_t* c1, color_t* c2); 

#endif /* COLOR_H */