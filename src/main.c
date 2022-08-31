#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define GLFW_INCLUDE_NONE

#include "game/map.h"

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


   struct Window window;
   window_init(&window, 1920, 1080);

   struct Renderer renderer;
   renderer_init(&renderer, 1920, 1080, 60, 4);


   struct Map map = map_create_and_initialize(10);
   
   struct Polyhex poly, poly2;
   poly_load(&poly, poly_file, 15, 0);
   poly_load(&poly2, poly_file, -15, 0);


   while (glfwWindowShouldClose(window.window) == false) {

      if (clock() - timer > 400) {
         if (!poly_move(&poly, map, -1, 0)) {
            map_merge_poly(map, poly);
            poly_load(&poly, poly_file, 15, 0);
         }
         if (!poly_move(&poly2, map, 1, 0)) {
            map_merge_poly(map, poly2);
            poly_load(&poly2, poly_file, -15, 0);
         }
         /* poly_rotate_cw(&poly, map);
         poly_rotate_cw(&poly2, map); */
         map_rotate_ccw(map);
         timer  = clock();
      }

      render(&renderer, map, poly, poly2);
  
      glfwSwapBuffers(window.window);
      glfwPollEvents();

   }

   glfwDestroyWindow(window.window);
   glfwTerminate();
   return EXIT_SUCCESS;
}