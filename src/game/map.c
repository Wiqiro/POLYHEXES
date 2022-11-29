#include "map.h"



struct Hex* map_ptr(struct HexMap map, int16_t q, int16_t r) {
   if (is_in_map(map, (struct AVect) {q, r})) {
      return &map.row[r + map.radius].hex[q + map.radius - map.row[r + map.radius].qmin];
   } else {
      return NULL;
   }
}

const struct Hex map_get(struct HexMap map, int16_t q, int16_t r) {
   //printf("%d\n", map_ptr(map, q, r)->col);
   return *map_ptr(map, q, r);
}


struct HexMap map_create_and_initialize(int16_t size) {
   struct HexMap map;
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
            map.row[r].hex[q].col = NO_COLOR ;
         }
      }
      map.row[map.rmax / 2].hex[map.rmax / 2].col = BLACK;
   }
   map.center = (struct AVect) {map.rmax / 2, map.rmax / 2};
   map.radius = size - 1;

   return map;
}

void map_delete(struct HexMap map) {
   for (int r = 0; r < map.rmax; r++) {
      free(map.row[r].hex);
   }
   free(map.row);
}

bool is_in_map(struct HexMap map, struct AVect pos) {
   return (abs(pos.q) <= map.radius && abs(pos.r) <= map.radius && abs(pos.q + pos.r) <= map.radius);
}

bool is_colliding(struct HexMap map, struct Polyhex poly) {

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

bool map_merge_poly(struct HexMap map, struct Polyhex poly) {
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


//TODO: collision check
void map_rotate_cw(struct HexMap map) {
   for (int q = 1; q <= map.radius; q++) {
      for (int r = 0; r <= map.radius - q; r++) {
         int16_t s = -q - r;
         struct Hex tmp = map_get(map, q, r);

         *map_ptr(map, q, r) = *map_ptr(map, -s, -q);
         *map_ptr(map, -s, -q) = *map_ptr(map, r, s);
         *map_ptr(map, r, s) = *map_ptr(map, -q, -r);
         *map_ptr(map, -q, -r) = *map_ptr(map, s, q);
         *map_ptr(map, s, q) = *map_ptr(map, -r, -s);
         *map_ptr(map, -r, -s) = tmp;
      }
   }
}

void map_rotate_ccw(struct HexMap map) {
   for (int q = 1; q <= map.radius; q++) {
      for (int r = 0; r <= map.radius - q; r++) {
         int16_t s = -q - r;
         struct Hex tmp = map_get(map, q, r);

         *map_ptr(map, q, r) = *map_ptr(map, -r, -s);
         *map_ptr(map, -r, -s) = *map_ptr(map, s, q);
         *map_ptr(map, s, q) = *map_ptr(map, -q, -r);
         *map_ptr(map, -q, -r) = *map_ptr(map, r, s);
         *map_ptr(map, r, s) = *map_ptr(map, -s, -q);
         *map_ptr(map, -s, -q) = tmp;

      }
   }
}

bool map_ring_is_full(struct HexMap map, int16_t radius) {
   if (radius <= map.radius) {
      bool is_full = true;
      int i = 0;

      while (i < radius && is_full) {
         is_full = (map_get(map, radius, -i).col != NO_COLOR && map_get(map, radius - i, -radius).col != NO_COLOR
                  && map_get(map, -i, i - radius).col != NO_COLOR && map_get(map, -radius, i).col != NO_COLOR
                  && map_get(map, i - radius, radius).col != NO_COLOR && map_get(map, i, radius - i).col != NO_COLOR);
         i++;
      }
      return is_full;
   } else {
      return false;
   }
}

void map_ring_delete(struct HexMap map, int16_t radius) {
   if (radius <= map.radius) {
      for (int i = 0; i < radius; i++) {
         map_ptr(map, radius, -i)->col = NO_COLOR;
         map_ptr(map, radius - i, -radius)->col = NO_COLOR;
         map_ptr(map, -i, i - radius)->col = NO_COLOR;
         map_ptr(map, -radius, i)->col = NO_COLOR;
         map_ptr(map, i - radius, radius)->col = NO_COLOR;
         map_ptr(map, i, radius - i)->col = NO_COLOR;
      }
   }
}

void map_ring_fall(struct HexMap map, int16_t radius) {
   if (radius < map.radius) {
      for (int i = 0; i < radius - 1; i++) {
         *map_ptr(map, radius - 1, -i) = *map_ptr(map, radius, -i - 1);
         *map_ptr(map, radius - i - 1, -(radius - 1)) = *map_ptr(map, radius - i - 1, -radius);
         *map_ptr(map, -i, i - radius + 1) = *map_ptr(map, -i - 1, i - radius - 1);
         *map_ptr(map, -(radius - 1), i) = *map_ptr(map, radius, i + 1);
         *map_ptr(map, i - (radius - 1), radius - 1) = *map_ptr(map, i - (radius - 1), radius);
         *map_ptr(map, i, radius - i - 1) = *map_ptr(map, i + 1, radius - i - 1);
      }
      map_ring_delete(map, radius);
   }
}