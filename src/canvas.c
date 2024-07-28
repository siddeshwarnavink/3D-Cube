#include <stdlib.h>
#include <unistd.h>

#include "buffer.h"
#include "canvas.h"
#include "coordinate.h"
#include "cube.h"

void create_canvas(canvas *c, buffer *b) {
  c->buf = b;
  c->items = (canvas_item **)malloc(sizeof(canvas_item *));
  c->items_len = 0;
}

void append_canvas(canvas *c, canvas_item *ci) {
  c->items = (canvas_item **)realloc(c->items, (c->items_len + 1) *
                                                   sizeof(canvas_item *));
  c->items[c->items_len] = ci;
  c->items_len++;
}

void destroy_canvas(canvas *c) {
  for (int i = 0; i < c->items_len; i++) {
    canvas_item *itm = c->items[i];
    switch (itm->type) {
    case ITEM_TYPE_CUBE:
      destroy_cube(itm->data.cube);
      break;
    case ITEM_TYPE_2DPOINT:
      free(itm->data.point);
      break;
    }
  }
}

void render_canvas(canvas *c) {
  for (;;) {
    append_buffer(c->buf, "\033[2J\033[u");
    for (int i = 0; i < c->items_len; i++) {
      canvas_item *itm = c->items[i];

      switch (itm->type) {
      case ITEM_TYPE_CUBE:
        render_cube(itm->data.cube, c->buf);
        rotate_cube(itm->data.cube, 0.1);
        break;
      case ITEM_TYPE_2DPOINT:
        render_point(itm->data.point, c->buf);
        break;
      }
    }
    render_buffer(c->buf);
    clear_buffer(c->buf);
    usleep(33000);
  }
}
