#ifndef LUMINOUS_H
#define LUMINOUS_H

#define LIGHT_X 15
#define LIGHT_Y 5
#define LIGHT_DISTANCE 15

#include "buffer.h"

float calculate_brightness(int x, int y);
void set_color(float brightness, buffer *buf);
void reset_color(buffer *buf);

#endif
