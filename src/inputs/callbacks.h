#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "../gfx/gfx.h"
#include "../gfx/window.h"

#include "../game/game_state.h"

enum Controls {
   POLY_LEFT_ROT,
   POLY_RIGHT_ROT,
   POLY_ROT_INV,
   POLY_UP,
   POLY_DOWN,
   MAP_ROT_CW,
   MAP_ROT_CCW,
   MENU,
   SPEEDUP,

   CONTROLS_COUNT,
};

enum Button {
   NONE,
   PRESSED,
   TOGGLED,
};

void controls_init(enum Button controls[CONTROLS_COUNT]);

void handle_events(struct Window window, enum Button controls[CONTROLS_COUNT], struct GameState* game);


#endif