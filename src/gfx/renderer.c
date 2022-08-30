#include "renderer.h"


static GLfloat vertices[] = {
    0.0f,     0.0f,  //middle
    0.0f,     1.0f, //up
    0.866f,   0.5f, //upper right
    0.866f,  -0.5f, //lower right
    0.0f,    -1.0f,  //down
   -0.866f,  -0.5f, //lower right
   -0.866f,   0.5f,//upper right
};

static GLuint indices[] = {
   0, 1, 2,
   0, 2, 3,
   0, 3, 4,
   0, 4, 5,
   0, 5, 6,
   0, 6, 1,
};



bool renderer_init(struct Renderer* self, int16_t width, int16_t height, int16_t hex_size, int16_t border_size) {
   self->shader = shader_load("ressources/shaders/hexagon.vert", "ressources/shaders/default.frag");
   if (self->shader == 0) {
      
      return false;
   }


   glUseProgram(self->shader);

   self->VAO = vao_create();
   vao_bind(self->VAO);

   self->hex_VBO = vbo_create(vertices, sizeof(vertices));
   vbo_bind(self->hex_VBO);
   vao_attrib(self->hex_VBO, 0, 2, GL_FLOAT, 2 * sizeof(float), 0);

   self->EBO = ebo_create(indices, sizeof(indices));

   glm_mat3_zero(self->proj_mat);
   self->proj_mat[0][0] = 1.0f / width;
   self->proj_mat[1][1] = 1.0f / height;

   shader_set_mat3(self->shader, "proj", self->proj_mat);
   self->hex_size = hex_size;
   self->border_size = border_size;


   return true;
}


static void _render_hex(struct Renderer* self, struct AVect pos, enum Color col) {
   mat3 model;
   vec2 offset = {(float) (pos.q + pos.r / 2.0f) * sqrt(3) * (float) (self->hex_size - self->border_size / 2),
                  (float) (-pos.r) * 1.5f * (float) (self->hex_size - self->border_size / 2)};

   if (col != NO_COLOR) {
      shader_set_color(self->shader, "color", 0.0f, 0.0f, 0.0f);
   } else {
      shader_set_color(self->shader, "color", 0.65f, 0.65f, 0.65f);
   }
      glm_mat3_identity(model);
      glm_translate2d(model, offset);
      glm_scale2d_uni(model, self->hex_size);
      shader_set_mat3(self->shader, "model", model);
      glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)0);
      

      switch (col) {
      case RED:
         shader_set_color(self->shader, "color", 0.96f, 0.5f, 0.58f);
         break;
      case LIGHT_RED:
         shader_set_color(self->shader, "color", 0.96f, 0.51f, 0.44f);
         break;
      case BLUE:
         shader_set_color(self->shader, "color", 0.54f, 0.55f, 0.76f);
         break;
      case LIGHT_BLUE:
         shader_set_color(self->shader, "color", 0.58f, 0.79f, 0.89f);
         break;
      case AQUA:
         shader_set_color(self->shader, "color", 0.62f, 0.85f, 0.85f);
         break;
      case GREEN:
         shader_set_color(self->shader, "color", 0.59f, 0.82f, 0.66f);
         break;
      case LIGHT_GREEN:
         shader_set_color(self->shader, "color", 0.79f, 0.88f, 0.54f);
         break;
      case YELLOW:
         shader_set_color(self->shader, "color", 1.0f, 0.94f, 0.62f);
         break;
      case ORANGE:
         shader_set_color(self->shader, "color", 0.97f, 0.65f, 0.33f);
         break;
      case LIGHT_ORANGE:
         shader_set_color(self->shader, "color", 1.0f, 0.81f, 0.47f);
         break;
      case PURPLE:
         shader_set_color(self->shader, "color", 0.89f, 0.72f, 0.83f);
         break;
      case PINK:
         shader_set_color(self->shader, "color", 0.95f, 0.56f, 0.74f);
         break;
      case BLACK:
         shader_set_color(self->shader, "color", 0.09f, 0.09f, 0.09f);
         break;
      default:
         shader_set_color(self->shader, "color", 0.15, 0.15, 0.15);
         break;
      }

      glm_mat3_identity(model);
      glm_translate2d(model, offset);
      glm_scale2d_uni(model, self->hex_size - self->border_size);
      shader_set_mat3(self->shader, "model", model);
      glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)0);
}



static void _clear_bg(double r, double g, double b) {
   glClearColor(r, g, b, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
}



void render(struct Renderer* self, struct Map map, struct Polyhex poly) {
   vao_bind(self->hex_VBO);
   ebo_bind(self->EBO);

   _clear_bg(0.09f, 0.09f, 0.09f);

   struct AVect hex_pos;
   

   for (int r = 0; r < map.rmax; r++) {
      for (int q = 0; q < map.row[r].size; q++) {
         hex_pos = (struct AVect) {q + map.row[r].qmin - map.center.q, r - map.center.r};
         _render_hex(self, hex_pos, map.row[r].hex[q].col);
      }
   }

   for (int i = 0; i < poly.order; i++) {
      hex_pos = (struct AVect) {poly.hex[i].q + poly.pos.q, poly.hex[i].r + poly.pos.r};
      _render_hex(self, hex_pos, poly.col);
   }
}

void renderer_destroy(struct Renderer self) {
   vao_delete(self.VAO);
   vbo_delete(self.hex_VBO);
   ebo_delete(self.EBO);
}