#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "coordinate.h"
#include "utils.h"

void fromStr(coordinate3d *c, char *str) {
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

void display(coordinate3d c) { printf("X: %d Y: %d Z: %d\n", c.x, c.y, c.z); }
