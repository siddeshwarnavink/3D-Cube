#ifndef LUMINOUS_H
#define LUMINOUS_H

#define LIGHT_X 18
#define LIGHT_Y 10
#define LIGHT_Z -2
#define LIGHT_DISTANCE 22

#include "buffer.h"

float calculate_brightness(int x, int y, float z);
void set_color(float brightness, buffer *buf);
char get_symbol(float brightness);
void reset_color(buffer *buf);

#endif
