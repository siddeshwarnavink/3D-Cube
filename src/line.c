#include <stdlib.h>

#include "line.h"
#include "luminous.h"
#include "utils.h"

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
    float brightness = calculate_brightness(x0, y0);
    set_color(brightness, buf);
    char *line_str = string_printf("\033[%d;%dH\u2022", y0, x0);
    append_buffer(buf, line_str);
    reset_color(buf);
    free(line_str);

    if (x0 == x1 && y0 == y1) {
      break;
    }
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
