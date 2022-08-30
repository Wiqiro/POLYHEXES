#ifndef VAO_H
#define VAO_H

#include "gfx.h"
#include "vbo.h"

GLuint vao_create();

void vao_bind(GLuint VAO);

void vao_attrib(GLuint VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, size_t offset);

void vao_unbind();

void vao_delete(GLuint VAO);

#endif