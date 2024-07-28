#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "canvas.h"
#include "coordinate.h"
#include "utils.h"

void from_str(coordinate3d *c, char *str) {
  const unsigned int s_len = strlen(str) - 3;
  char *s = (char *)malloc(s_len * sizeof(char));
  strncpy(s, str + 1, s_len);

  const char d[] = ",";

  char *token = strtok(s, d);
  clean_string(token);
  c->x = atoi(token);

  token = strtok(NULL, d);
  clean_string(token);
  c->y = atoi(token);

  token = strtok(NULL, d);
  clean_string(token);
  c->z = atoi(token);

  free(s);
}

coordinate2d *project_point(coordinate3d *c, float theta) {
  /*
  // For rotating along x-axis
  float y_rotated = c->y * cos(theta) - c->z * sin(theta);
  float z_rotated = c->y * sin(theta) + c->z * cos(theta);

  coordinate2d *screen_point = (coordinate2d *)malloc(sizeof(coordinate2d));
  screen_point->x =
      (int)(c->x * CANVAS_WIDTH / (2 * DISTANCE)) + CANVAS_WIDTH / 2;
  screen_point->y =
      (int)(-y_rotated * CANVAS_HEIGHT / (2 * DISTANCE)) + CANVAS_HEIGHT / 2;
  return screen_point;
  */

  // For rotating along y-axis
  float x_rotated = c->x * cos(theta) + c->z * sin(theta);
  float z_rotated = -c->x * sin(theta) + c->z * cos(theta);

  coordinate2d *screen_point = (coordinate2d *)malloc(sizeof(coordinate2d));
  screen_point->x =
      (int)(x_rotated * CANVAS_WIDTH / (2 * DISTANCE)) + CANVAS_WIDTH / 2;
  screen_point->y =
      (int)(-c->y * CANVAS_HEIGHT / (2 * DISTANCE)) + CANVAS_HEIGHT / 2;
  return screen_point;
}

void render_point(coordinate2d *c, buffer *buf) {
  append_buffer(buf, string_printf("\033[%d;%dH\u2022",
                                   CANVAS_HEIGHT - (int)c->y, (int)c->x));
}

void display_2dp(coordinate2d p) { printf("X: %.2f Y: %.2f\n", p.x, p.y); }

void display_3dp(coordinate3d p) {
  printf("X: %.2f Y: %.2f Z: %.2f\n", p.x, p.y, p.z);
}
