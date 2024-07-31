#include <math.h>
#include <stdlib.h>

#include "buffer.h"
#include "luminous.h"
#include "utils.h"

float calculate_brightness(int x, int y, float z) {
  float distance =
      sqrt(pow(x - LIGHT_X, 2) + pow(y - LIGHT_Y, 2) + pow(z - LIGHT_Z, 2));
  float brightness = fmax(0, 1 - distance / LIGHT_DISTANCE);
  return brightness;
}

char get_symbol(float brightness) {
  int index = roundf(brightness * 10);
  return ".,-~:;=!*#$@"[index];
}

void set_color(float brightness, buffer *buf) {
  int intensity = (int)(brightness * 255);
  char *color_str =
      string_printf("\033[38;2;%d;%d;%dm", intensity, intensity, intensity);
  append_buffer(buf, color_str);
  free(color_str);
}

void reset_color(buffer *buf) { append_buffer(buf, "\033[0m"); }
