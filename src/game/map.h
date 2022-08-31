#ifndef MAP_H
#define MAP_H


#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <stdio.h>

#include "hex.h"



struct Hex* map_ptr(struct Map map, int16_t q, int16_t r);

const struct Hex map_get(struct Map map, int16_t q, int16_t r);

struct Map map_create_and_initialize(int16_t size);

void map_delete(struct Map map);

bool is_in_map(struct Map map, struct AVect pos);

bool is_colliding(struct Map map, struct Polyhex poly);

bool map_merge_poly(struct Map map, struct Polyhex poly);

void map_rotate_cw(struct Map map);

void map_rotate_ccw(struct Map map);


#endif