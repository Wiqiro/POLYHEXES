#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <stdint.h>

#include "gfx.h"

struct Window {
   GLFWwindow* window;
   int16_t width, height;
};

bool window_init(struct Window* self, int16_t width, int16_t height);

#endif