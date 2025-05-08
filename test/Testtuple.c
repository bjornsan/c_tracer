#include "unity.h"
#include <stdlib.h>
#include "tuple.h"
#include "color.h"


void setUp(void)
{

}

void tearDown(void)
{

}

void test_tuple_with_w_1_is_a_point(void)
{
    tuple_t* t = tuple(4.3, -4.2, 3.1, 1.0);
    TEST_ASSERT_EQUAL_FLOAT(4.3, t->x);
    TEST_ASSERT_EQUAL_FLOAT(-4.2, t->y);
    TEST_ASSERT_EQUAL_FLOAT(3.1, t->z);
    TEST_ASSERT_EQUAL_FLOAT(1.0, t->w);
    TEST_ASSERT_TRUE(is_point(t));
    TEST_ASSERT_FALSE(is_vector(t));
}

void test_tuple_with_w_0_is_a_vector(void)
{
    tuple_t* t = tuple(4.3, -4.2, 3.1, 0.0);
    TEST_ASSERT_EQUAL_FLOAT(4.3, t->x);
    TEST_ASSERT_EQUAL_FLOAT(-4.2, t->y);
    TEST_ASSERT_EQUAL_FLOAT(3.1, t->z);
    TEST_ASSERT_EQUAL_FLOAT(0.0, t->w);
    TEST_ASSERT_FALSE(is_point(t));
    TEST_ASSERT_TRUE(is_vector(t));
}

void test_creates_tuples_with_w_1(void)
{
    TEST_ASSERT_TRUE(tuple_is_equal(point(4.0, -4.0, 3.0), tuple(4.0, -4.0, 3.0, 1.0)));
}

void test_creates_tuples_with_w_0(void)
{
    TEST_ASSERT_TRUE(tuple_is_equal(vector(4.0, -4.0, 3.0), tuple(4.0, -4.0, 3.0, 0.0)));
}

void test_add_tuple(void)
{
    tuple_t* t1 = tuple(3.0, -2.0, 5.0, 1.0);
    tuple_t* t2 = tuple(-2.0, 3.0, 1.0, 0.0);
    add_tuple(t1, t2);

    TEST_ASSERT_TRUE(tuple_is_equal(t1, tuple(1.0, 1.0, 6.0, 1.0)));

    free(t1);
    free(t2);

    t1 = NULL;
    t2 = NULL;
}

void test_subtract_two_points(void)
{
    tuple_t* t1 = point(3.0, 2.0, 1.0);
    tuple_t* t2 = point(5.0, 6.0, 7.0);

    subtract_tuple(t1, t2);

    TEST_ASSERT_TRUE(tuple_is_equal(t1, vector(-2.0, -4.0, -6.0)));

    free(t1);
    free(t2);

    t1 = NULL;
    t2 = NULL;
}

void test_subtract_a_vector_from_a_point(void)
{
    tuple_t* t1 = point(3.0, 2.0, 1.0);
    tuple_t* t2 = vector(5.0, 6.0, 7.0);

    subtract_tuple(t1, t2);

    TEST_ASSERT_TRUE(tuple_is_equal(t1, point(-2.0, -4.0, -6.0)));

    free(t1);
    free(t2);

    t1 = NULL;
    t2 = NULL;
}

void test_subtracting_two_vectors(void)
{
    tuple_t* t1 = vector(3.0, 2.0, 1.0);
    tuple_t* t2 = vector(5.0, 6.0, 7.0);

    subtract_tuple(t1, t2);

    TEST_ASSERT_TRUE(tuple_is_equal(t1, vector(-2.0, -4.0, -6.0)));

    free(t1);
    free(t2);

    t1 = NULL;
    t2 = NULL;
}

void test_subtracting_a_vector_from_the_zero_vector(void)
{
    tuple_t* t1 = vector(0.0, 0.0, 0.0);
    tuple_t* t2 = vector(1.0, -2.0, 3.0);

    subtract_tuple(t1, t2);

    TEST_ASSERT_TRUE(tuple_is_equal(t1, vector(-1.0, 2.0, -3.0)));

    free(t1);
    free(t2);

    t1 = NULL;
    t2 = NULL;
}

void test_negating_a_tuple(void)
{
    tuple_t* t1 = tuple(1.0, -2.0, 3.0, -4.0);
    negate(t1);

    TEST_ASSERT_TRUE(tuple_is_equal(t1, tuple(-1.0, 2.0, -3.0, 4.0)));

    free(t1);
    t1 = NULL;
}

void test_multiplying_a_tuple_by_a_scalar(void)
{
    tuple_t* t1 = tuple(1.0, -2.0, 3.0, -4.0);
    multiply_scalar(t1, 3.5);
    TEST_ASSERT_TRUE(tuple_is_equal(t1, tuple(3.5, -7.0, 10.5, -14.0)));
    free(t1);
    t1 = NULL;
}

void test_multiplying_a_tuple_by_a_fraction(void)
{
    tuple_t* t1 = tuple(1.0, -2.0, 3.0, -4.0);
    multiply_scalar(t1, 0.5);
    TEST_ASSERT_TRUE(tuple_is_equal(t1, tuple(0.5, -1.0, 1.5, -2.0)));
    free(t1);
    t1 = NULL;
}

void test_divide_a_tuple_by_a_scalar(void)
{
    tuple_t* t1 = tuple(1.0, -2.0, 3.0, -4.0);
    divide_scalar(t1, 2);
    TEST_ASSERT_TRUE(tuple_is_equal(t1, tuple(0.5, -1.0, 1.5, -2.0)));
    free(t1);
    t1 = NULL;
}

void test_computing_the_magnitude_of_vector_1_0_0(void)
{
    vector3d* v = vector(1.0, 0.0, 0.0);
    double m = magnitude(v);
    TEST_ASSERT(double_equals(m, 1.0));
    free(v);
    v = NULL;
}

void test_computing_the_magnitude_of_vector_0_1_0(void)
{
    vector3d* v = vector(0.0, 1.0, 0.0);
    double m = magnitude(v);
    TEST_ASSERT(double_equals(m, 1.0));
    free(v);
    v = NULL;
}

void test_computing_the_magnitude_of_vector_0_0_1(void)
{
    vector3d* v = vector(0.0, 0.0, 1.0);
    double m = magnitude(v);
    TEST_ASSERT(double_equals(m, 1.0));
    free(v);
    v = NULL;
}

void test_computing_the_magnitude_of_vector_1_2_3(void)
{
    vector3d* v = vector(1.0, 2.0, 3.0);
    double m = magnitude(v);
    TEST_ASSERT(double_equals(m, sqrt(14)));
    free(v);
    v = NULL;
}

void test_computing_the_magnitude_of_vector_n1_n2_n3(void)
{
    vector3d* v = vector(-1.0, -2.0, -3.0);
    double m = magnitude(v);
    TEST_ASSERT(double_equals(m, sqrt(14)));
    free(v);
    v = NULL;
}

void test_normalizing_vector_4_0_0_gives_1_0_0(void)
{
    vector3d* v = vector(4.0, 0.0, 0.0);
    normal(v);
    TEST_ASSERT(tuple_is_equal(v, vector(1.0, 0.0, 0.0)));
    free(v);
    v = NULL;
}

void test_normalizing_vector_1_2_3(void)
{
    vector3d* v = vector(1.0, 2.0, 3.0);
    normal(v);
    TEST_ASSERT(tuple_is_equal(v, vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14))));
    free(v);
    v = NULL;
}

void test_the_magnitude_of_a_normalized_vector(void)
{
    vector3d* v = vector(1.0, 2.0, 3.0);
    normal(v);
    double m = magnitude(v);
    TEST_ASSERT(double_equals(m, 1.0));
    free(v);
    v = NULL;
}

void test_the_dot_product_of_two_tuples()
{
    vector3d* v1 = vector(1.0, 2.0, 3.0);
    vector3d* v2 = vector(2.0, 3.0, 4.0);
    double d = dot(v1, v2);
    TEST_ASSERT(double_equals(20.0, d));
}

void test_the_cross_product_of_two_vectors()
{
    vector3d* v1 = vector(1.0, 2.0, 3.0);
    vector3d* v2 = vector(2.0, 3.0, 4.0);
    
    vector3d* c1 = cross(v1, v2);
    vector3d* c2 = cross(v2, v1);

    TEST_ASSERT(tuple_is_equal(c1, vector(-1.0, 2.0, -1.0)));
    TEST_ASSERT(tuple_is_equal(c2, vector(1.0, -2.0, 1.0)));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_tuple_with_w_1_is_a_point);
    RUN_TEST(test_tuple_with_w_0_is_a_vector);
    RUN_TEST(test_creates_tuples_with_w_1);
    RUN_TEST(test_creates_tuples_with_w_0);
    RUN_TEST(test_add_tuple);
    RUN_TEST(test_subtract_two_points);
    RUN_TEST(test_subtract_a_vector_from_a_point);
    RUN_TEST(test_subtracting_two_vectors);
    RUN_TEST(test_subtracting_a_vector_from_the_zero_vector);
    RUN_TEST(test_negating_a_tuple);
    RUN_TEST(test_multiplying_a_tuple_by_a_scalar);
    RUN_TEST(test_multiplying_a_tuple_by_a_fraction);
    RUN_TEST(test_divide_a_tuple_by_a_scalar);
    RUN_TEST(test_computing_the_magnitude_of_vector_1_0_0);
    RUN_TEST(test_computing_the_magnitude_of_vector_0_1_0);
    RUN_TEST(test_computing_the_magnitude_of_vector_0_0_1);
    RUN_TEST(test_computing_the_magnitude_of_vector_1_2_3);
    RUN_TEST(test_computing_the_magnitude_of_vector_n1_n2_n3);
    RUN_TEST(test_normalizing_vector_4_0_0_gives_1_0_0);
    RUN_TEST(test_normalizing_vector_1_2_3);
    RUN_TEST(test_the_magnitude_of_a_normalized_vector);
    RUN_TEST(test_the_dot_product_of_two_tuples);
    RUN_TEST(test_the_cross_product_of_two_vectors);

    UNITY_END();

    return 0;
}