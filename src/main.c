#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define GLFW_INCLUDE_NONE

#include "game/map.h"
#include "game/game_state.h"


#include "gfx/gfx.h"
#include "gfx/window.h"
#include "gfx/renderer.h"
#include "gfx/shaders.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/ebo.h"


int main(int argc, char* argv[]) {

   srand(time(NULL));
   clock_t timer = clock();

   FILE* poly_file = fopen("ressources/polyhexes/polyhexes", "r");
   if (poly_file == NULL) {
      fprintf(stderr, "ERROR: Failed to open polyomino file\n");
      return EXIT_FAILURE;
   }

   struct GameState game = game_new(poly_file);   


   struct Window window;
   window_init(&window, 1920, 1080);

   struct Renderer renderer;
   renderer_init(&renderer, 1920, 1080, 60, 6);


   struct HexMap map = map_create_and_initialize(10);
   
   struct Polyhex game.poly_r, game.poly_l;
   poly_load(&game.poly_r, poly_file, 15, 0);
   poly_load(&game.poly_l, poly_file, -15, 0);

   while (glfwWindowShouldClose(window.window) == false) {

      if (clock() - timer > 400) {
         if (!poly_move(&game.poly_r, map, -1, 0)) {
            map_merge_poly(map, game.poly_r);
            poly_load(&game.poly_r, poly_file, 15, 0);
         }
         if (!poly_move(&game.poly_l, map, 1, 0)) {
            map_merge_poly(map, game.poly_l);
            poly_load(&game.poly_l, poly_file, -15, 0);
         }
         timer  = clock();
      }
      
      if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS) {
         map_rotate_cw(map);
      }
      //TODO: EU keyboard + cooldown
      if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS) {
         map_rotate_cw(map);
      }
      if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
         if (!glfwGetKey(window.window, GLFW_KEY_LEFT_CONTROL)) {
            poly_rotate_cw(&game.poly_l, map);
         } else {
            poly_rotate_ccw(&game.poly_l, map);
         }
      }
      if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
         if (!glfwGetKey(window.window, GLFW_KEY_LEFT_CONTROL)) {
            poly_rotate_cw(&game.poly_r, map);
         } else {
            poly_rotate_ccw(&game.poly_r, map);
         }
      }
      
     


      render(&renderer, map, game.poly_r, game.poly_l);
  
      glfwSwapBuffers(window.window);
      glfwPollEvents();

   }

   glfwDestroyWindow(window.window);
   glfwTerminate();
   return EXIT_SUCCESS;
}