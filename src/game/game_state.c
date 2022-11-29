#include "game_state.h"


//TODO: replace with options
static int16_t POLY_DIST = 15;
static int16_t MAP_SIZE = 10;
static uint16_t BASE_TICK = 400;


struct GameState game_new(FILE* file) {
   struct GameState game;
   game.map = map_create_and_initialize(MAP_SIZE);
   poly_load(&game.poly[0], file, -POLY_DIST, 0);
   poly_load(&game.poly[1], file, POLY_DIST, 0);
   poly_load(&game.poly[2], file, -POLY_DIST, 0);
   poly_load(&game.poly[3], file, POLY_DIST, 0);

   game.stage = 0;
   game.score = 0;
   game.hex_count = 0;
   game.base_tick = BASE_TICK;
   game.tick = game.base_tick;
   game.last_tick = clock();
   game.speedfall = false;
   return game;
}

void game_update(struct GameState* game, FILE* file) {
   for (int i = 1; i < game->map.radius; i++) {
      if (map_ring_is_full(game->map, i)) {
         map_ring_delete(game->map, i);
         //map_ring_fall(game->map, i + 1);
      }
   }
   
   if (clock() - game->last_tick > game->tick) {
      if (!poly_move(&game->poly[0], game->map, 1, 0)) {
         map_merge_poly(game->map, game->poly[0]);
         //TODO: replace with poly[3/4]
         poly_load(&game->poly[0], file, -POLY_DIST, 0);
      }
      if (!poly_move(&game->poly[1], game->map, -1, 0)) {
         map_merge_poly(game->map, game->poly[1]);
         poly_load(&game->poly[1], file, POLY_DIST, 0);
      }
      game->last_tick = clock();
   }
}

void game_speedfall_on(struct GameState* game) {
   game->tick = game->base_tick / 5;
   game->speedfall = true;
}


void game_speedfall_off(struct GameState* game) {
   game->tick = game->base_tick;
   game->speedfall = false;
}