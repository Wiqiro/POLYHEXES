#include "callbacks.h"

void controls_init(enum Button controls[CONTROLS_COUNT]) {
   for (int i = 0; i < CONTROLS_COUNT; i++) {
      controls[i] = NONE;
   }
}



void handle_events(struct Window window, enum Button controls[CONTROLS_COUNT], struct GameState* game) {

   if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS) {
      if (controls[MAP_ROT_CCW] == NONE) {
         controls[MAP_ROT_CCW] = PRESSED;
         map_rotate_ccw(game->map);
      } else {
         controls[MAP_ROT_CCW] = TOGGLED;
      }
   } else {
      controls[MAP_ROT_CCW] = NONE;
   }
   
   if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS) {
      if (controls[MAP_ROT_CW] == NONE) {
         controls[MAP_ROT_CW] = PRESSED;
         map_rotate_cw(game->map);
      } else {
         controls[MAP_ROT_CW] = TOGGLED;
      }
   } else {
      controls[MAP_ROT_CW] = NONE;
   }

   if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS) {
      if (controls[POLY_UP] == NONE) {
         controls[POLY_UP] = PRESSED;
         poly_move_up(&game->poly[0], &game->poly[1], game->map);
      } else {
         controls[POLY_UP] = TOGGLED;
      }
   } else {
      controls[POLY_UP] = NONE;
   }

   if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS) {
      if (controls[POLY_DOWN] == NONE) {
         controls[POLY_DOWN] = PRESSED;
         poly_move_down(&game->poly[0], &game->poly[1], game->map);
      } else {
         controls[POLY_DOWN] = TOGGLED;
      }
   } else {
      controls[POLY_DOWN] = NONE;
   }

   if (glfwGetKey(window.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
      if (controls[POLY_ROT_INV] == NONE) {
         controls[POLY_ROT_INV] = PRESSED;
      } else {
         controls[POLY_ROT_INV] = TOGGLED;
      }
   } else {
      controls[POLY_ROT_INV] = NONE;
   }

   if (glfwGetKey(window.window, GLFW_KEY_SPACE) == GLFW_PRESS) {
      if (controls[SPEEDUP] == NONE) {
         controls[SPEEDUP] = PRESSED;
      } else {
         controls[SPEEDUP] = TOGGLED;
      }
      game_speedfall_on(game);
   } else {
      controls[SPEEDUP] = NONE;
      game_speedfall_off(game);
   }

   if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
      if (controls[POLY_LEFT_ROT] == NONE) {
         controls[POLY_LEFT_ROT] = PRESSED;
         if (controls[POLY_ROT_INV] == NONE) {
            poly_rotate_cw(&game->poly[0], game->map);
         } else {
            poly_rotate_ccw(&game->poly[0], game->map);
         }
      } else {
         controls[POLY_LEFT_ROT] = TOGGLED;
      }
   } else {
      controls[POLY_LEFT_ROT] = NONE;
   }

  if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
      if (controls[POLY_RIGHT_ROT] == NONE) {
         controls[POLY_RIGHT_ROT] = PRESSED;
         if (controls[POLY_ROT_INV] == NONE) {
            poly_rotate_cw(&game->poly[1], game->map);
         } else {
            poly_rotate_ccw(&game->poly[1], game->map);
         }
      } else {
         controls[POLY_RIGHT_ROT] = TOGGLED;
      }
   } else {
      controls[POLY_RIGHT_ROT] = NONE;
   }
}

