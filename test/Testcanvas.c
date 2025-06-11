#include "unity.h"
#include <stdlib.h>
#include "tuple.h"
#include "color.h"
#include "canvas.h"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_creating_a_canvas(void)
{
    canvas_t* c = canvas(10, 20);

    TEST_ASSERT_NOT_NULL(c);
    
    TEST_ASSERT_EQUAL(c->width, 10);
    TEST_ASSERT_EQUAL(c->height, 20);

    for (int i = 0; i < c->height; i++) {
      for (int j = 0; j < c->width; j++) 
      {
        TEST_ASSERT(tuple_is_equal(&c->pixels[i * c->width + j], color(0.0, 0.0, 0.0)));

      }
    }

    free_canvas(c);
}

void test_write_pixel_to_canvas(void)
{
  canvas_t*c = canvas(10, 20);
  color_t* red = color(1.0, 0.0, 0.0);
  write_pixel(c, 2, 3, red);
  TEST_ASSERT(tuple_is_equal(pixel_at(c, 2, 3), red));

  free_canvas(c);
}

void test_constructing_the_ppm_header(void)
{
  canvas_t* c = canvas(5, 3);
  char ppm[c->width * c->height];
  canvas_to_ppm(c, ppm, 100);
  const char* expected = "P3\n5 3\n255\n";
  TEST_ASSERT_EQUAL_STRING(expected, ppm);
  free_canvas(c);
}

void test_constructing_the_ppm_pixel_data()
{
  canvas_t* c = canvas(5, 3);
  color_t* c1 = color(1.5, 0.0, 0.0);  // Red
  color_t* c2 = color(0.0, 0.5, 0.0);  // Green
  color_t* c3 = color(-0.5, 0.0, 1.0); // Blue
  
  write_pixel(c, 0, 0, c1);
  write_pixel(c, 2, 1, c2);
  write_pixel(c, 4, 2, c3);

  // Allocate a buffer with a sufficient size to hold the PPM output
  size_t buffer_size = 1024 * c->width * c->height * 12;
  char buffer[buffer_size];
  
  // Call canvas_to_ppm with the allocated buffer
  canvas_to_ppm(c, buffer, buffer_size);

  // Update the expected output based on line breaks after every 70 characters
  const char* expected = 
    "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
    "0 0 0 0 128 0 0 0 0 0 0 0 0 0 0\n"
    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
  
  TEST_ASSERT_EQUAL_STRING(expected, buffer);

  free_canvas(c);
}


int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_creating_a_canvas);
    RUN_TEST(test_write_pixel_to_canvas);
    RUN_TEST(test_constructing_the_ppm_header);
    RUN_TEST(test_constructing_the_ppm_pixel_data);

    UNITY_END();

    return 0;
}