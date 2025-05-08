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

void test_colors_are_red_green_blue_tuples(void)
{
    color_t* c1 = color(-0.5, 0.4, 1.7);
    TEST_ASSERT_EQUAL_FLOAT(-0.5, c1->x);
    TEST_ASSERT_EQUAL_FLOAT(0.4, c1->y);
    TEST_ASSERT_EQUAL_FLOAT(1.7, c1->z);
}

void test_adding_colors(void)
{
    color_t* c1 = color(0.9, 0.6, 0.75);
    color_t* c2 = color(0.7, 0.1, 0.25);
    add_color(c1, c2);

    TEST_ASSERT_EQUAL_FLOAT(1.6, c1->x);
    TEST_ASSERT_EQUAL_FLOAT(0.7, c1->y);
    TEST_ASSERT_EQUAL_FLOAT(1.0, c1->z);

    free(c1);
    free(c2);
}

void test_subtracting_colors(void)
{
    color_t* c1 = color(0.9, 0.6, 0.75);
    color_t* c2 = color(0.7, 0.1, 0.25);
    subtract_color(c1, c2);

    TEST_ASSERT_EQUAL_FLOAT(0.2, c1->x);
    TEST_ASSERT_EQUAL_FLOAT(0.5, c1->y);
    TEST_ASSERT_EQUAL_FLOAT(0.5, c1->z);
    
    free(c1);
    free(c2);
}

void test_multiplying_color_by_scalar(void)
{
    color_t* c1 = color(0.2, 0.3, 0.4);
    multiply_scalar(c1, 2.0);

    TEST_ASSERT_EQUAL_FLOAT(0.4, c1->x);
    TEST_ASSERT_EQUAL_FLOAT(0.6, c1->y);
    TEST_ASSERT_EQUAL_FLOAT(0.8, c1->z);
    free(c1);
}

void test_multiplying_colors(void)
{
    color_t* c1 = color(1.0, 0.2, 0.4);
    color_t* c2 = color(0.9, 1.0, 0.1);
    hadmard_product(c1, c2);

    TEST_ASSERT_EQUAL_FLOAT(0.9, c1->x);
    TEST_ASSERT_EQUAL_FLOAT(0.2, c1->y);
    TEST_ASSERT_EQUAL_FLOAT(0.04, c1->z);
    
    free(c1);
    free(c2);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_colors_are_red_green_blue_tuples);
    RUN_TEST(test_adding_colors);
    RUN_TEST(test_subtracting_colors);
    RUN_TEST(test_multiplying_color_by_scalar);
    RUN_TEST(test_multiplying_colors);


    UNITY_END();

    return 0;
}