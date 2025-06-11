#ifndef CANVAS_H
#define CANVAS_H

#include "color.h"

typedef struct canvas
{
  int width;
  int height;
  color_t* pixels;
}canvas_t;

/**
 * @brief Create a canvas object, and initialize it parameter provided
 *        dimensions.
 * 
 * @param width The canvas width
 * @param height The canvas height
 * @return A pointer to the canvas.
 */
canvas_t* canvas(int width, int height);

/**
 * @brief Free the canvas and the pixel array it contains.
 * 
 * @param canvas The canvas to free.
 * @return none
 */
void free_canvas(canvas_t* canvas);

/**
 * @brief write a color to a spcific pixel
 *        Note that the pixels is a 1D array, so access is done by 
 *        the following formula.
 * 
 *        pixel = cavas->pixels[y * canvas->width + x] 
 * 
 * @param canvas The canvas to draw to.
 * @param x The x coordinate
 * @param y The y coordinate
 * @param color The color to write to the pixel.
 * @return nothing
 */
void write_pixel(canvas_t* c, int x, int y, color_t* color);

/**
 * @brief Get a specific pixel from the canvas.
 *        Note that the pixels is a 1D array, so access is done by 
 *        the following formula.
 * 
 *        pixel = cavas->pixels[y * canvas->width + x] 
 * 
 * @param canvas The canvas to draw to.
 * @param x The x coordinate
 * @param y The y coordinate
 * @return a pointer to the color at that pixel.
 */
color_t* pixel_at(canvas_t* canvas, int x, int y);

// void canvas_to_ppm(canvas_t* canvas, char* buffer);
void canvas_to_ppm(canvas_t* canvas, char* buffer, size_t buffer_size);

#endif /* CANVAS_H */