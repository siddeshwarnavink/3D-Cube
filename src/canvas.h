#ifndef RENDERER_H
#define RENDERER_H

#define CANVAS_WIDTH 40
#define CANVAS_HEIGHT 20

#include <sys/types.h>

#include "coordinate.h"

typedef union canvas_item {
  coordinate2d *point;
} canvas_item;

typedef struct canvas {
  uint items_len;
  canvas_item **items;
} canvas;

void create_canvas(canvas *c);
void destroy_canvas(canvas *c);
void append_canvas(canvas *c, canvas_item *ci);
void render_canvas(canvas *c);

#endif
