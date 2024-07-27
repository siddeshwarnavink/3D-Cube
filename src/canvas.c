#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "canvas.h"

void create_canvas(canvas *c) {
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
    if (c->items[i]->point != NULL) {
      free(c->items[i]->point);
    }
  }
}

void render_canvas(canvas *c) {
  for (;;) {
    printf("\033[2J\033[u");
    for (int i = 0; i < c->items_len; i++) {
      canvas_item *itm = c->items[i];
      // render point
      if (itm->point != NULL) {
        printf("\033[%d;%dHx", (int)itm->point->x, (int)itm->point->y);
      }
    }
    usleep(33000);
  }
}
