#ifndef CUBE_H
#define CUBE_H

#include "buffer.h"
#include "coordinate.h"

typedef struct cube {
  struct coordinate3d **points;
  float deg;
} cube;

void create_cube(cube **c);
void destroy_cube(cube *c);
void render_cube(cube *c, buffer *buf);
void rotate_cube(cube *c, float deg);

#endif