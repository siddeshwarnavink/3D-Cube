#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "coordinate.h"
#include "cube.h"
#include "utils.h"

void create_cube(cube **c) {
  *c = (cube *)malloc(sizeof(cube));
  (*c)->points = (coordinate3d **)malloc(8 * sizeof(coordinate3d *));
  (*c)->deg = 0;

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

// bresenham algorithm
void render_line(coordinate2d *p1, coordinate2d *p2, buffer *buf) {
  int x0 = (int)p1->x;
  int y0 = (int)p1->y;
  int x1 = (int)p2->x;
  int y1 = (int)p2->y;

  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  while (1) {
    append_buffer(buf, string_printf("\033[%d;%dH\u2022", y0, x0));
    if (x0 == x1 && y0 == y1)
      break;
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void render_cube(cube *c, buffer *buf) {
  coordinate2d **screen_points =
      (coordinate2d **)malloc(8 * sizeof(coordinate2d *));

  for (int i = 0; i < 8; i++) {
    screen_points[i] = project_point(c->points[i], c->deg);
  }

  // square A
  render_line(screen_points[0], screen_points[1], buf);
  render_line(screen_points[1], screen_points[2], buf);
  render_line(screen_points[2], screen_points[3], buf);
  render_line(screen_points[3], screen_points[0], buf);

  // square B
  render_line(screen_points[4], screen_points[5], buf);
  render_line(screen_points[5], screen_points[6], buf);
  render_line(screen_points[6], screen_points[7], buf);
  render_line(screen_points[7], screen_points[0], buf);

  // lines in middle
  render_line(screen_points[0], screen_points[4], buf);
  render_line(screen_points[1], screen_points[5], buf);
  render_line(screen_points[2], screen_points[6], buf);
  render_line(screen_points[3], screen_points[7], buf);

  // cleanup
  for (int i = 0; i < 8; i++) {
    free(screen_points[i]);
  }

  free(screen_points);
}

void rotate_cube(cube *c, float deg) {
  float sum = c->deg + deg;
  c->deg = (sum > 360) ? 360 - sum : sum;
}
