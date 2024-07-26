#ifndef COORDINATE_H
#define COORDINATE_H

typedef struct coordinate3d {
  int x;
  int y;
  int z;
} coordinate3d;

typedef struct coordinate2d {
  int x;
  int y;
} coordinate2d;

void from_str(coordinate3d *c, char *str);
void display(coordinate3d c);

#endif
