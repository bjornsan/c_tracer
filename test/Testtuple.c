#include "unity.h"
#include "tuple.h"


void setUp()
{

}

void tearDown()
{

}

void test_tuple_with_w_1_is_a_point()
{
    tuple_t t = init_tuple(4.3, -4.2, 3.1, 1.0);
    TEST_ASSERT_EQUAL_FLOAT(4.3, t.x);
    TEST_ASSERT_EQUAL_FLOAT(-4.2, t.y);
    TEST_ASSERT_EQUAL_FLOAT(3.1, t.z);
    TEST_ASSERT_EQUAL_FLOAT(1.0, t.w);
    TEST_ASSERT_TRUE(is_point(t));
    TEST_ASSERT_FALSE(is_vector(t));
}

void test_tuple_with_w_0_is_a_vector()
{
    tuple_t t = init_tuple(4.3, -4.2, 3.1, 0.0);
    TEST_ASSERT_EQUAL_FLOAT(4.3, t.x);
    TEST_ASSERT_EQUAL_FLOAT(-4.2, t.y);
    TEST_ASSERT_EQUAL_FLOAT(3.1, t.z);
    TEST_ASSERT_EQUAL_FLOAT(0.0, t.w);
    TEST_ASSERT_FALSE(is_point(t));
    TEST_ASSERT_TRUE(is_vector(t));
}

void test_creates_tuples_with_w_1()
{
    TEST_ASSERT_TRUE(tuple_is_equal(init_point(4.0, -4.0, 3.0), init_tuple(4.0, -4.0, 3.0, 1.0)));
}

void test_creates_tuples_with_w_0()
{
    tuple_t vector = init_vector(4.0, -4.0, 3.0);
    TEST_ASSERT_TRUE(tuple_is_equal(init_vector(4.0, -4.0, 3.0), init_tuple(4.0, -4.0, 3.0, 0.0)));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_tuple_with_w_1_is_a_point);
    RUN_TEST(test_tuple_with_w_0_is_a_vector);
    RUN_TEST(test_creates_tuples_with_w_1);
    RUN_TEST(test_creates_tuples_with_w_0);

    UNITY_END();

    return 0;
}