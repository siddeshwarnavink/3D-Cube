#include <stdio.h>
#include <stdlib.h>

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
  for (int y = 0; y < CANVAS_HEIGHT; y++) {
    for (int x = 0; x < CANVAS_WIDTH; x++) {
      for (int i = 0; i < c->items_len; i++) {
        canvas_item *itm = c->items[i];

        if (itm->point != NULL && itm->point->x == x && itm->point->y == y) {
          printf("x");
        }
      }
      printf(" ");
    }
    printf("\n");
  }
}
