#include <math.h>

#include "buffer.h"
#include "luminous.h"
#include "utils.h"

float calculate_brightness(int x, int y) {
  float distance = sqrt(pow(x - LIGHT_X, 2) + pow(y - LIGHT_Y, 2));
  float brightness = fmax(0, 1 - distance / LIGHT_DISTANCE);
  return brightness;
}

void set_color(float brightness, buffer *buf) {
  int intensity = (int)(brightness * 255);
  append_buffer(buf, string_printf("\033[38;2;%d;%d;%dm", intensity, intensity,
                                   intensity));
}

void reset_color(buffer *buf) { append_buffer(buf, "\033[0m"); }
