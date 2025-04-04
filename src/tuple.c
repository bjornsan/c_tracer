#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "tuple.h"

tuple_t* tuple(double x, double y, double z, double w)
{
  tuple_t* tuple = (tuple_t*)calloc(1, sizeof(tuple_t));

  tuple->x = x;
  tuple->y = y;
  tuple->z = z;
  tuple->w = w;

  return tuple;
}

point3d* point(double x, double y, double z)
{
  return tuple(x, y, z, W_POINT);
}

vector3d* vector(double x, double y, double z)
{
  return tuple(x, y, z, W_VECTOR);
}

bool is_point(tuple_t* tuple)
{
  return tuple->w == W_POINT;
}

bool is_vector(tuple_t* tuple)
{
  return tuple->w == W_VECTOR;
}

void add_tuple(tuple_t* tuple, tuple_t* other) 
{
  tuple->x = tuple->x + other->x;
  tuple->y = tuple->y + other->y;
  tuple->z = tuple->z + other->z;
  tuple->w = tuple->w + other->w;
}

void subtract_tuple(tuple_t* tuple, tuple_t* other)
{
  tuple->x = tuple->x - other->x;
  tuple->y = tuple->y - other->y;
  tuple->z = tuple->z - other->z;
  tuple->w = tuple->w - other->w;
}

void multiply_tuple(tuple_t* tuple, tuple_t* other)
{
  tuple->x = tuple->x * other->x;
  tuple->y = tuple->y * other->y;
  tuple->z = tuple->z * other->z;
  tuple->w = tuple->w * other->w;
}

void multiply_scalar(tuple_t* tuple, double scalar)
{
  tuple->x = tuple->x * scalar;
  tuple->y = tuple->y * scalar;
  tuple->z = tuple->z * scalar;
  tuple->w = tuple->w * scalar;
}

void divide_scalar(tuple_t* tuple, double scalar)
{
  tuple->x = tuple->x / scalar;
  tuple->y = tuple->y / scalar;
  tuple->z = tuple->z / scalar;
  tuple->w = tuple->w / scalar;
}

void negate(tuple_t* tuple)
{
  tuple->x = tuple->x * -1;
  tuple->y = tuple->y * -1;
  tuple->z = tuple->z * -1;
  tuple->w = tuple->w * -1;
}

/**
 * Calculataes the magnitude of a vector. In other words, the length.
 * 
 * @param vector The vector to calculate the magnitude for.
 */
double magnitude(vector3d* vector)
{
  return sqrt(pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2) + pow(vector->w, 2));
}

/**
 * Normalizes a vector to a unitvector.
 * 
 * @param vector: The vector that shall be normalized. 
 * 
 * The passed in vector will be changed to save memory.
 */
void normal(vector3d* vector)
{
  double mag = magnitude(vector);
  vector->x = vector->x / mag;
  vector->y = vector->y / mag;
  vector->z = vector->z / mag;
  vector->w = vector->w / mag;
}

double dot(tuple_t* t1, tuple_t* t2)
{
  return (t1->x * t2->x) + 
         (t1->y * t2->y) +
         (t1->z * t2->z) +
         (t1->w * t2->w);
}

vector3d* cross(vector3d* v1, vector3d* v2)
{
  return vector((v1->y * v2->z - v1->z * v2->y), (v1->z * v2->x - v1->x * v2->z), (v1->x * v2->y - v1->y * v2->x));
}

bool double_equals(double x, double y)
{
  return abs(x-y) < EPSILON;
}

bool tuple_is_equal(tuple_t* t1, tuple_t* t2)
{
    return (double_equals(t1->x, t2->x) && double_equals(t1->y, t2->y) && double_equals(t1->z, t2->z) && double_equals(t1->w, t2->w));
}