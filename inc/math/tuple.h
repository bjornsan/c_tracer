#ifndef TUPLE_H
#define TUPLE_H

#include <stdbool.h>

#define EPSILON         0.00001               /* precision for comparing float and double values */
#define W_POINT         1.0                   /* the w component value for a point */
#define W_VECTOR        0.0                   /* the w component value for a vecotr */
#define vector3d        tuple_t 
#define point3d         tuple_t
#define color_t         tuple_t

/**
 * @brief A structure composing a tuple
 */
typedef struct
{
  double x;
  double y;
  double z;
  double w;
}tuple_t;

/**
 * @brief intitializes a tuple
 * 
 * @param x
 * @param y
 * @param z
 * @param w
 * 
 * @return tuple_t
 */
tuple_t* tuple(double x, double y, double z, double w);

/**
 * @brief Initializes a point
 * 
 * @param x
 * @param y
 * @param z
 * 
 * @returns tuple_t with w = 1.0
 */
point3d* point(double x, double y, double z);

/**
 * @brief Initializes a vector
 * 
 * @param x
 * @param y
 * @param z
 * 
 * @returns tuple_t with w = 0.0
 */
vector3d* vector(double x, double y, double z);

/**
 * @brief checks if a given tuple is a point
 * 
 * @param tuple - the tuple to check (of type tuple_t)
 * 
 * @returns true if tuple is a point, false otherwise
 */
bool is_point(tuple_t* tuple);

/**
 * @brief checks if a given tuple is a vector
 * 
 * @param tuple - the tuple to check (of type tuple_t)
 */
bool is_vector(tuple_t* tuple);

void add_tuple(tuple_t* tuple, tuple_t* other);

void subtract_tuple(tuple_t* tuple, tuple_t* other);

void multiply_tuple(tuple_t* tuple, tuple_t* other);
 
void multiply_scalar(tuple_t* tuple, double scalar);

void divide_scalar(tuple_t* tuple, double scalar);

void negate(tuple_t* tuple);

double magnitude(tuple_t* tuple);

void normal(vector3d* vector);

double dot(tuple_t* t1, tuple_t* t2);

vector3d* cross(vector3d* v1, vector3d* v2);
/** 
 * @brief compare a double using EPSILON
 * 
 * @param x
 * @param y
 * 
 * @returns true if x == y, false otherwise
 */
bool double_equals(double x, double y);

/**
 * @brief comare if a t1 is equal to t2. Internally comare each element using
 *        doulbe_equals.
 * 
 * @param t1
 * @param t2
 * 
 * @returns true if t1 == t2, false otherwise
 */
bool tuple_is_equal(tuple_t* t1, tuple_t* t2);



#endif /* TUPLE_H */