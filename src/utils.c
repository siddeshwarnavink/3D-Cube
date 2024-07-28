#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
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

char *string_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  int size = vsnprintf(NULL, 0, format, args);

  char *result = (char *)malloc(size + 1);
  if (!result) {
    va_end(args);
    return NULL;
  }

  va_start(args, format);
  vsnprintf(result, size + 1, format, args);
  va_end(args);

  return result;
}
