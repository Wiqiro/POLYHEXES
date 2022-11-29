#include "window.h"

bool window_init(struct Window* self, int16_t width, int16_t height) {
   glewExperimental = true;

   if (glfwInit() == false) {
      fprintf(stderr, "Failed to initialize GLFW\n");
      return false;
   }
   glfwWindowHint(GLFW_SAMPLES, 32); // 4x antialiasing
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // major version
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor version
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // modern opengl

   self->window = glfwCreateWindow(1920, 1080, "OpenGL", NULL, NULL);
   if (self->window == NULL) {
      fprintf(stderr, "Failed to create window\n");
      glfwTerminate();
      return false;
   }
   glfwMakeContextCurrent(self->window);

   glewExperimental = true;
   if (glewInit() != GLEW_OK) {
      fprintf(stderr,"Failed to initialize GLEW\n");
      glfwDestroyWindow(self->window);
      glfwTerminate();
      return false;
   }
   glViewport(0, 0, width, height);
   self->width = width;
   self->height = height;
   return true;
}