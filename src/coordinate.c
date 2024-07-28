#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "canvas.h"
#include "coordinate.h"
#include "utils.h"

void from_str(coordinate3d *c, char *str) {
  const uint s_len = strlen(str) - 3;
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

coordinate2d *to_2d(coordinate3d *c) {
  coordinate2d *c2d = (coordinate2d *)malloc(sizeof(coordinate2d));
  c2d->x = c->x / c->z;
  c2d->y = c->y / c->z;
  c2d->x = ((c2d->x * 0.5) + 0.5) * CANVAS_WIDTH / 2;
  c2d->y = ((c2d->y * 0.5) + 0.5) * CANVAS_HEIGHT / 4;
  return c2d;
}

void render_point(coordinate2d *c) {
  printf("\033[%d;%dH\u2022", (int)c->y, (int)c->x);
}

void display_2dp(coordinate2d p) { printf("X: %.2f Y: %.2f\n", p.x, p.y); }

void display_3dp(coordinate3d p) {
  printf("X: %.2f Y: %.2f Z: %.2f\n", p.x, p.y, p.z);
}
