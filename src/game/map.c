#include "map.h"



struct Hex* map_ptr(struct Map map, int16_t q, int16_t r) {
   if (is_in_map(map, (struct AVect) {q, r})) {
      return &map.row[r + map.radius].hex[q + map.radius - map.row[r + map.radius].qmin];
   } else {
      return NULL;
   }
}

const struct Hex map_get(struct Map map, int16_t q, int16_t r) {
   //printf("%d\n", map_ptr(map, q, r)->col);
   return *map_ptr(map, q, r);
}


struct Map map_create_and_initialize(int16_t size) {
   struct Map map;
   map.row = (struct HexArray*) malloc(sizeof(struct HexArray) * (size * 2 + 1));
   if (map.row != NULL) {
      for (int i = 0; i < size; i++) {
         map.row[i].hex = (struct Hex*) malloc(sizeof(struct Hex) * (size + i));
         map.row[i].qmin = size - i - 1;
         map.row[i].size = size + i;
      }
      for (int i = size; i < size * 2 - 1; i++) {
         map.row[i].hex = (struct Hex*) malloc(sizeof(struct Hex) * (size * 3 - i - 2));
         map.row[i].qmin = 0;
         map.row[i].size = size * 3 - i - 2;
      }

      map.rmax = size * 2 - 1;
      for (int r = 0; r < map.rmax; r++) {
         for (int q = 0; q < map.row[r].size; q++) {
            map.row[r].hex[q].col = NO_COLOR;
         }
      }
      map.row[map.rmax / 2].hex[map.rmax / 2].col = BLACK;
   }
   map.center = (struct AVect) {map.rmax / 2, map.rmax / 2};
   map.radius = size - 1;

   return map;
}

void map_delete(struct Map map) {
   for (int r = 0; r < map.rmax; r++) {
      free(map.row[r].hex);
   }
   free(map.row);
}

bool is_in_map(struct Map map, struct AVect pos) {
   return (pos.q >= -map.radius && pos.q <= map.radius && pos.r >= -map.radius && pos.r <= map.radius && pos.q + pos.r >= -map.radius && pos.q + pos.r <= map.radius);
}

bool is_colliding(struct Map map, struct Polyhex poly) {

   bool is_colliding = false;
   int i = 0;

   while (i < poly.order && is_colliding == false) {

      struct AVect test = {poly.hex[i].q + poly.pos.q, poly.hex[i].r + poly.pos.r};
      if (is_in_map(map, test)) {
         is_colliding = (map_get(map, test.q, test.r).col != NO_COLOR);
      }
      i++;
   }
   return is_colliding;
}

bool map_merge_poly(struct Map map, struct Polyhex poly) {
   bool is_out_of_map = false;
   for (int i = 0; i < poly.order; i++) {
      struct AVect test = {poly.hex[i].q + poly.pos.q, poly.hex[i].r + poly.pos.r};
      if (is_in_map(map, test)) {
         map_ptr(map, test.q, test.r)->col = poly.col;
      } else {
         is_out_of_map = true;
      }
   }
   return is_out_of_map;
}
