#ifndef CUBE_H
#define CUBE_H

#include "coordinate.h"

typedef struct cube {
  struct coordinate3d **points;
} cube;

void create_cube(cube **c);
void destroy_cube(cube *c);
void render_cube(cube *c);

#endif
