#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "canvas.h"
#include "color.h"


canvas_t* canvas(int width, int height) {

  if (width <= 0 || height <= 0) 
  {
    return NULL;
  }

  canvas_t* canvas = malloc(sizeof(canvas_t));
  if (!canvas) {
    return NULL;
  }

  canvas->width = width;
  canvas->height = height;
  canvas->pixels = calloc((size_t)(width * height), sizeof(color_t));

  if (!canvas->pixels)
  {
    free(canvas);
    return NULL;
  }
  return canvas;
}

color_t* pixel_at(canvas_t* canvas, int x, int y)
{
  if (!canvas || x < 0 || x >= canvas->width || y < 0 || y >= canvas->height) {
    return NULL;
  }
  return &canvas->pixels[y * canvas->width + x];
}

void write_pixel(canvas_t* canvas, int x, int y, color_t* color)
{
  if (!canvas || !color || x < 0 || x >= canvas->width || y < 0 || y >= canvas->height) {
    return;
  }
  canvas->pixels[y * canvas->width + x] = *color;
}

// void canvas_to_ppm(canvas_t* canvas, char* buffer)
// {
//   sprintf(buffer, "P3\n%d %d\n255\n", canvas->width, canvas->height);
// }



void free_canvas(canvas_t* canvas)
{
  if (!canvas)
  {
    return;
  }

  free(canvas->pixels);
  free(canvas);
}


void canvas_to_ppm(canvas_t* canvas, char* buffer, size_t buffer_size) {
    if (!canvas || !buffer || buffer_size == 0 || !canvas->pixels ||
        canvas->width <= 0 || canvas->height <= 0) {
        return;
    }

    int width = canvas->width;
    int height = canvas->height;
    size_t offset = 0;

    // Write PPM header
    int written = snprintf(buffer + offset, buffer_size - offset,
                           "P3\n%d %d\n255\n", width, height);
    if (written < 0 || (size_t)written >= buffer_size - offset) return;
    offset += (size_t)written;

    int line_length = 0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            color_t* color = pixel_at(canvas, x, y);
            if (!color) continue;

            int r = (int)(color->x * 255.0f + 0.5f);
            int g = (int)(color->y * 255.0f + 0.5f);
            int b = (int)(color->z * 255.0f + 0.5f);

            // Clamp values to [0, 255]
            r = (r < 0) ? 0 : (r > 255) ? 255 : r;
            g = (g < 0) ? 0 : (g > 255) ? 255 : g;
            b = (b < 0) ? 0 : (b > 255) ? 255 : b;

            char pixel_str[16];
            written = snprintf(pixel_str, sizeof(pixel_str), "%d %d %d", r, g, b);
            if (written < 0) return;

            // If adding this pixel would exceed the 70 character line limit, insert newline
            if (line_length + written + 1 > 70) {
                if (offset + 1 >= buffer_size) return;
                buffer[offset++] = '\n';
                line_length = 0;
            } else if (line_length > 0) {
                if (offset + 1 >= buffer_size) return;
                buffer[offset++] = ' ';
                line_length++;
            }

            if (offset + (size_t)written >= buffer_size) return;
            memcpy(buffer + offset, pixel_str, (size_t)written);
            offset += (size_t)written;
            line_length += written;
        }

        if (line_length > 0) {
            if (offset + 1 >= buffer_size) return;
            buffer[offset++] = '\n';
            line_length = 0;
        }
    }

    // Null-terminate if space allows
    if (offset < buffer_size) {
        buffer[offset] = '\0';
    } else if (buffer_size > 0) {
        buffer[buffer_size - 1] = '\0';  // Emergency null terminator
    }
}
