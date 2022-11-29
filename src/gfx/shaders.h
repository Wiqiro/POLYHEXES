#ifndef SHADERS_H
#define SHADERS_H

#include <stdlib.h>
#include <stdio.h>

#include "gfx.h"

GLuint shader_load(char* vert_path, char* frag_path);
void shader_set_mat3(GLuint shader, const char* uniform, mat3 mat);
void shader_set_color(GLuint shader, const char* uniform, double r, double g, double b);
void shader_activate(GLuint shader);
void shader_delete(GLuint shader);

#endif