#include <stdio.h>
#include <string.h>

#include "utils.h"

void clean_string(char *s) {
  char *src = s, *dst = s;

  while (*src) {
    // utf-8 minus sign
    if (*src == '\xE2' && *(src + 1) == '\x88' && *(src + 2) == '\x92') {
      *dst++ = '-';
      src += 3;
    } else if ((unsigned char)*src < 128) {
      *dst++ = *src++;
    } else {
      src++;
    }
  }
  *dst = '\0';
}

void debug_print(char *s) {
  printf("(%s)  ->  ", s);
  for (int i = 0; i < strlen(s); i++) {
    printf("'%d'\t", s[i]);
  }
  printf("\n");
}
