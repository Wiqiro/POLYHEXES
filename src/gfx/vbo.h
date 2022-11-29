#ifndef VBO_H
#define VBO_H

#include "gfx.h"

GLuint vbo_create(void* vertices, size_t size);
void vbo_bind(GLuint VBO);
void vbo_unbind();
void vbo_delete(GLuint VBO);

#endif