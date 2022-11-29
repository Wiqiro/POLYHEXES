#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define GLFW_INCLUDE_NONE


#include "game/game_state.h"
#include "inputs/callbacks.h"

#include "gfx/gfx.h"
#include "gfx/window.h"
#include "gfx/renderer.h"
#include "gfx/shaders.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/ebo.h"


int main(int argc, char* argv[]) {

   srand(time(NULL));

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

      enum Button controls[CONTROLS_COUNT];
      controls_init(controls);

   while (glfwWindowShouldClose(window.window) == false) {

      game_update(&game, poly_file);
      
      handle_events(window, controls, &game);
      
    // poly_move_down(&game.poly[0], &game.poly[1], game.map);


      render(&renderer, game.map, game.poly[1], game.poly[0]);
  
      glfwSwapBuffers(window.window);
      glfwPollEvents();

   }

   glfwDestroyWindow(window.window);
   glfwTerminate();
   return EXIT_SUCCESS;
}