#include "shaders.h"

static char* _get_file_content(const char* path) {
   int32_t size = 0;

   FILE* file = fopen(path, "r");
   if (file == NULL) {
      fprintf(stderr, "Failed to load file content \"%s\"\n", path);
      return NULL;
   }

   fseek(file, 0, SEEK_END);
   size = ftell(file);
   rewind(file);

   char* content = (char*) calloc(size, sizeof(char));
   fread(content, 1, size-1, file);
   //seems like it is not 100% working on linux: shader files need to have an extra linebreak at the end
   fclose(file);
   return content;
}

GLuint shader_load(char* vert_path, char* frag_path) {
   const char* vert_source = _get_file_content(vert_path);
   const char* frag_source = _get_file_content(frag_path);



   int log_length = 0;
   char* error;

   GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex_shader, 1, &vert_source, NULL);
   glCompileShader(vertex_shader);

   glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
   if (log_length > 0) {
      error = (char*) calloc(log_length + 1, sizeof(char));
      glGetShaderInfoLog(vertex_shader, log_length, NULL, error);
      fprintf(stderr, "%s\n", error);
   }



   GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment_shader, 1, &frag_source, NULL);
   glCompileShader(fragment_shader);

   glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
   if (log_length > 0) {
      error = (char*) calloc(log_length + 1, sizeof(char));
      glGetShaderInfoLog(fragment_shader, log_length, NULL, error);
      fprintf(stderr, "%s\n", error);
   }
   //free(error); //TODO:


   GLuint shader_program = glCreateProgram();
   glAttachShader(shader_program, vertex_shader);
   glAttachShader(shader_program, fragment_shader); 
   glLinkProgram(shader_program);

   glDeleteProgram(vertex_shader);
   glDeleteShader(fragment_shader);

   return shader_program;
}

void shader_set_mat3(GLuint shader, const char* uniform, mat3 mat) {
   glUniformMatrix3fv(glGetUniformLocation(shader, uniform), 1, GL_FALSE,  &mat[0][0]);
}

void shader_set_color(GLuint shader, const char* uniform, double r, double g, double b) {
   glUniform4f(glGetUniformLocation(shader, uniform), r, g, b, 1.0f);
}

void shader_delete(GLuint shader) {
   glDeleteProgram(shader);
}