#ifndef COORDINATE_H
#define COORDINATE_H

typedef struct coordinate3d {
  float x;
  float y;
  float z;
} coordinate3d;

typedef struct coordinate2d {
  float x;
  float y;
} coordinate2d;

void from_str(coordinate3d *c, char *str);
coordinate2d *to_2d(coordinate3d *c);
void render_point(coordinate2d *c);
void display_3dp(coordinate3d p);
void display_2dp(coordinate2d p);

#endif
