#include "vbo.h"

GLuint vbo_create(void* vertices, size_t size) {
   GLuint VBO;
   glGenBuffers(1, &VBO);
   vbo_bind(VBO);
   glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //TODO: maybe replace with dynamic
   vbo_unbind();

   return VBO;
}

void vbo_bind(GLuint VBO) {
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void vbo_unbind() {
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo_delete(GLuint VBO) {
   glDeleteBuffers(1, &VBO);
}