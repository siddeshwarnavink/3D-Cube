#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

void create_buffer(buffer *b,  unsigned int max) {
  b->value = (char *)malloc(max * sizeof(char));
  if (b->value == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  b->value[0] = '\0';
  b->size = 0;
  b->max = max;
}

void append_buffer(buffer *b, const char *s) {
   unsigned int s_len = strlen(s);
  if (b->size + s_len >= b->max) {
    fprintf(stderr, "Buffer overflow, cannot append string\n\n");
    printf("===========\n");
    printf("Buffer size=%d\nCurrent Buffer Size=%d\nString size=%d\n", b->max,
           b->size, s_len);
    printf("===========\n\n");
    exit(1);
  }

  strcat(b->value, s);
  b->size += s_len;
}

void render_buffer(buffer *b) { printf("%s", b->value); }

void clear_buffer(buffer *b) {
  b->value[0] = '\0';
  b->size = 0;
}

void destroy_buffer(buffer *b) {
  free(b->value);
  b->value = NULL;
  b->size = 0;
  b->max = 0;
}
