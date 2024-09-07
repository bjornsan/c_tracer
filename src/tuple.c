#include <stdbool.h>
#include "tuple.h"

tuple_t init_tuple(double x, double y, double z, double w)
{
  tuple_t tuple =
  {
    .x = x,
    .y = y, 
    .z = z,
    .w = w
  };
  return tuple;
}

tuple_t init_point(double x, double y, double z)
{
  return init_tuple(x, y, z, W_POINT);
}

tuple_t init_vector(double x, double y, double z)
{
  return init_tuple(x, y, z, W_VECTOR);
}

bool is_point(tuple_t tuple)
{
  return tuple.w == W_POINT;
}

bool is_vector(tuple_t tuple)
{
  return tuple.w == W_VECTOR;
}

bool double_equals(double x, double y)
{
  if ( ( (x -y) * -1 ) < EPSILON ) 
  {
    return true;
  } 
  else 
  {
    return false;
  }
}

bool tuple_is_equal(tuple_t t1, tuple_t t2)
{
    return (double_equals(t1.x, t2.x) && double_equals(t1.y, t2.y) && double_equals(t1.z, t2.z) && double_equals(t1.w, t2.w));
}