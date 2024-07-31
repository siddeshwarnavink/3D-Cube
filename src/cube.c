#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "coordinate.h"
#include "cube.h"
#include "luminous.h"
#include "utils.h"

void create_cube(cube **c) {
  *c = (cube *)malloc(sizeof(cube));
  (*c)->points = (coordinate3d **)malloc(8 * sizeof(coordinate3d *));
  (*c)->theta_x = 0.3;
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

void shade_square(coordinate2d *p1, coordinate2d *p2, coordinate2d *p3,
                  coordinate2d *p4, buffer *buf) {
  int min_x = (int)fmin(fmin(p1->x, p2->x), fmin(p3->x, p4->x));
  int max_x = (int)fmax(fmax(p1->x, p2->x), fmax(p3->x, p4->x));
  int min_y = (int)fmin(fmin(p1->y, p2->y), fmin(p3->y, p4->y));
  int max_y = (int)fmax(fmax(p1->y, p2->y), fmax(p3->y, p4->y));

  for (int y = min_y; y <= max_y; ++y) {
    for (int x = min_x; x <= max_x; ++x) {
      float cp1 = (p2->x - p1->x) * (y - p1->y) - (p2->y - p1->y) * (x - p1->x);
      float cp2 = (p3->x - p2->x) * (y - p2->y) - (p3->y - p2->y) * (x - p2->x);
      float cp3 = (p4->x - p3->x) * (y - p3->y) - (p4->y - p3->y) * (x - p3->x);
      float cp4 = (p1->x - p4->x) * (y - p4->y) - (p1->y - p4->y) * (x - p4->x);

      if ((cp1 >= 0 && cp2 >= 0 && cp3 >= 0 && cp4 >= 0) ||
          (cp1 <= 0 && cp2 <= 0 && cp3 <= 0 && cp4 <= 0)) {
        float brightness = calculate_brightness(x, y);
        set_color(brightness, buf);
        char *shade_str = string_printf("\033[%d;%dH@", y, x);
        append_buffer(buf, shade_str);
        reset_color(buf);
        free(shade_str);
      }
    }
  }
}

void render_cube(cube *c, buffer *buf) {
  coordinate2d **screen_points =
      (coordinate2d **)malloc(8 * sizeof(coordinate2d *));

  for (int i = 0; i < 8; i++) {
    screen_points[i] = project_point(c->points[i], c->theta_x, c->theta_y);
  }

  // char *debug_str =
  //     string_printf("\033[0;0Hθx=%.1f; θy=%.1f", c->theta_x, c->theta_y);
  // append_buffer(buf, debug_str);
  // free(debug_str);

  // // square B (back)
  shade_square(screen_points[4], screen_points[5], screen_points[6],
               screen_points[7], buf);

  // side squares
  shade_square(screen_points[0], screen_points[3], screen_points[4],
               screen_points[7], buf);
  shade_square(screen_points[0], screen_points[1], screen_points[4],
               screen_points[5], buf);
  shade_square(screen_points[1], screen_points[2], screen_points[5],
               screen_points[6], buf);
  shade_square(screen_points[2], screen_points[3], screen_points[6],
               screen_points[7], buf);

  // // square A (front)
  shade_square(screen_points[0], screen_points[1], screen_points[2],
               screen_points[3], buf);

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
