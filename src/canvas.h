#ifndef RENDERER_H
#define RENDERER_H

#define CANVAS_WIDTH 30
#define CANVAS_HEIGHT 30

#include <sys/types.h>

#include "buffer.h"
#include "coordinate.h"
#include "cube.h"

typedef enum { ITEM_TYPE_2DPOINT, ITEM_TYPE_CUBE } canvas_item_type;

typedef union canvas_item_data {
  coordinate2d *point;
  cube *cube;
} canvas_item_data;

typedef struct canvas_item {
  canvas_item_type type;
  canvas_item_data data;
} canvas_item;

typedef struct canvas {
  buffer *buf;
  uint items_len;
  canvas_item **items;
} canvas;

void create_canvas(canvas *c, buffer *b);
void destroy_canvas(canvas *c);
void append_canvas(canvas *c, canvas_item *ci);
void render_canvas(canvas *c);

#endif
