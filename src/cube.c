#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "coordinate.h"
#include "cube.h"
#include "line.h"
#include "utils.h"

void create_cube(cube **c) {
  *c = (cube *)malloc(sizeof(cube));
  (*c)->points = (coordinate3d **)malloc(8 * sizeof(coordinate3d *));
  (*c)->theta_x = 0;
  (*c)->theta_y = 10;

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

void render_cube(cube *c, buffer *buf) {
  coordinate2d **screen_points =
      (coordinate2d **)malloc(8 * sizeof(coordinate2d *));

  for (int i = 0; i < 8; i++) {
    screen_points[i] = project_point(c->points[i], c->theta_x, c->theta_y);
  }

  append_buffer(
      buf, string_printf("\033[0;0Hθx=%.1f; θy=%.1f", c->theta_x, c->theta_y));

  // square A
  render_line(screen_points[0], screen_points[1], buf);
  render_line(screen_points[1], screen_points[2], buf);
  render_line(screen_points[2], screen_points[3], buf);
  render_line(screen_points[3], screen_points[0], buf);

  // square B
  render_line(screen_points[4], screen_points[5], buf);
  render_line(screen_points[5], screen_points[6], buf);
  render_line(screen_points[6], screen_points[7], buf);
  render_line(screen_points[7], screen_points[4], buf);

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
  float sum = c->theta_y + deg;
  c->theta_y = (sum > 360) ? 0 : sum;
}
