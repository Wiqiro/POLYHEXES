#ifndef RENDERER_H
#define RENDERER_H

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "gfx.h"
#include "shaders.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "../game/hex.h"
#include "../game/polyhex.h"
#include "../game/map.h"

struct Renderer {
   GLint shader;

   GLint VAO;
   GLint hex_VBO;
   GLint EBO;

   int16_t hex_size, border_size;
   mat3 proj_mat;
};

bool renderer_init(struct Renderer* self, int16_t width, int16_t height, int16_t hex_size, int16_t border_size);
void render(struct Renderer* self, struct HexMap map, struct Polyhex poly, struct Polyhex poly2);
void renderer_destroy(struct Renderer self);



#endif