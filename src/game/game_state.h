#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdint.h>
#include <time.h>

#include <GLFW/glfw3.h>

#include "hex.h"
#include "map.h"
#include "polyhex.h"

struct GameState {
   struct HexMap map;
   struct Polyhex poly[4];

   uint16_t stage;
   uint64_t* score; //1 score per stage
   uint32_t hex_count;

   double base_tick, tick;
   bool speedfall;
};

struct GameState game_new(FILE* file);
void game_update(struct GameState* game, FILE* file);
void game_speedfall_on(struct GameState* game);
void game_speedfall_off(struct GameState* game);

#endif