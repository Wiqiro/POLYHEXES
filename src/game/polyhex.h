#ifndef POLYHEX_H
#define POLYHEX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


#include "hex.h"
#include "map.h"



bool poly_load(struct Polyhex* poly, FILE* file, int16_t q, int16_t r);

bool poly_move(struct Polyhex* poly, struct HexMap map, int16_t dq, int16_t dr);

void poly_rotate_cw(struct Polyhex* poly, struct HexMap map);
void poly_rotate_ccw(struct Polyhex* poly, struct HexMap map);

void poly_move_up(struct Polyhex* poly_l, struct Polyhex* poly_r, struct HexMap map);
void poly_move_down(struct Polyhex* poly_l, struct Polyhex* poly_r, struct HexMap map);



#endif