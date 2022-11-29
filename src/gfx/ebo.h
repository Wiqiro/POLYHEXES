#ifndef EBO_H
#define EBO_H

#include "gfx.h"

GLuint ebo_create(GLuint* indices, size_t size);

void ebo_bind(GLuint EBO);

void ebo_unbind();

void ebo_delete(GLuint EBO);

#endif