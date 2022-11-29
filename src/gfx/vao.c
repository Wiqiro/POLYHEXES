#include "vao.h"

GLuint vao_create() {
   GLuint VAO;
   glGenVertexArrays(1, &VAO);
   return VAO;
}

void vao_bind(GLuint VAO) {
   glBindVertexArray(VAO);
}

void vao_attrib(GLuint VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, size_t offset) {
   vbo_bind(VBO);
   glVertexAttribPointer(layout, size, type, GL_FALSE, stride, (void*)offset);
   glEnableVertexAttribArray(layout);
   vbo_unbind();
}

void vao_unbind() {
   glBindVertexArray(0);
}

void vao_delete(GLuint VAO) {
   glDeleteVertexArrays(1, &VAO);
}