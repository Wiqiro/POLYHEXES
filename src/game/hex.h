#ifndef HEX_H
#define HEX_H

#include <stdint.h>

//TODO: palette loader
enum Color {
   RED,
   LIGHT_RED,
   BLUE,
   LIGHT_BLUE,
   AQUA,
   GREEN,
   LIGHT_GREEN,
   YELLOW,
   ORANGE,
   LIGHT_ORANGE,
   PURPLE,
   PINK,

   COLOR_TOTAL,
   BLACK,
   NO_COLOR,
};

struct AVect {
   int32_t q, r;
};

struct CVect {
   int32_t q, r, s;
};

//TODO: active/passive
struct Hex {
   enum Color col;
};

struct Polyhex {
   struct AVect* hex;
   struct AVect pos;

   int16_t order;
   enum Color col;
};

struct HexArray {
   struct Hex* hex;
   uint16_t qmin;
   uint16_t size;
};


struct Map {
   struct HexArray* row;
   int16_t rmax;
   int16_t radius;
   struct AVect center;
};

int16_t s(int16_t q, int16_t r);


#endif