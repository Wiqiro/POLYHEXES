#include "ebo.h"

GLuint ebo_create(GLuint* indices, size_t size) {
   GLuint EBO;
   glGenBuffers(1, &EBO);
   ebo_bind(EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW); //TODO: maybe replace with dynamic
   //ebo_unbind();

   return EBO;
}

void ebo_bind(GLuint EBO) {
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void ebo_unbind() {
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ebo_delete(GLuint EBO) {
   glDeleteBuffers(1, &EBO);
}