#ifndef MAP_H
#define MAP_H


#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <stdio.h>

#include "hex.h"



struct Hex* map_ptr(struct HexMap map, int16_t q, int16_t r);
const struct Hex map_get(struct HexMap map, int16_t q, int16_t r);

struct HexMap map_create_and_initialize(int16_t size);
void map_delete(struct HexMap map);

bool is_in_map(struct HexMap map, struct AVect pos);
bool is_colliding(struct HexMap map, struct Polyhex poly);
bool map_merge_poly(struct HexMap map, struct Polyhex poly);

void map_rotate_cw(struct HexMap map);
void map_rotate_ccw(struct HexMap map);

bool map_ring_is_full(struct HexMap map, int16_t radius);
void map_ring_delete(struct HexMap map, int16_t radius);
void map_ring_fall(struct HexMap map, int16_t radius);


#endif