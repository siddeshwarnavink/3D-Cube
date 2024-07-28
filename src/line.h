#ifndef LINE_H
#define LINE_H

#include "buffer.h"
#include "coordinate.h"

// draw line using bresenham algorithm
void render_line(coordinate2d *p1, coordinate2d *p2, buffer *buf);

#endif
