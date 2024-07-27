#include <stdio.h>
#include <stdlib.h>

#include "coordinate.h"
#include "cube.h"

void create_cube(cube **c) {
  *c = (cube *)malloc(sizeof(cube));
  (*c)->points = (coordinate3d **)malloc(8 * sizeof(coordinate3d *));

  for (int i = 0; i < 8; i++) {
    (*c)->points[i] = (coordinate3d *)malloc(sizeof(coordinate3d));
  }
}

void destroy_cube(cube *c) {
  for (int i = 0; i < 8; i++) {
    if (c->points[i] != NULL) {
      free(c->points[i]);
    }
  }
  free(c->points);
  free(c);
}

void render_square(coordinate2d *p1, coordinate2d *p2, coordinate2d *p3) {
  for (int y = p1->y; y <= p3->y; y++) {
    for (int x = p1->x; x <= p2->x; x++) {
      printf("\033[%d;%dH*", x, y);
    }
  }
}

void render_cube(cube *c) {
  coordinate2d **screen_points =
      (coordinate2d **)malloc(8 * sizeof(coordinate2d *));

  // map 3d points to 2d
  for (int i = 0; i < 8; i++) {
    screen_points[i] = to_2d(c->points[i]);
  }

  // screen_points 0-3 square A, 4-7 square B
  render_square(screen_points[0], screen_points[1], screen_points[2]);
  render_square(screen_points[4], screen_points[5], screen_points[6]);

  // cleanup
  for (int i = 0; i < 8; i++) {
    free(screen_points[i]);
  }

  free(screen_points);
}
