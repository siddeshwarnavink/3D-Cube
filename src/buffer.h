#ifndef BUFFER_H
#define BUFFER_H

// a simple string buffer
typedef struct buffer {
  char *value;
   unsigned int size;
   unsigned int max;
} buffer;

// create a buffer object
void create_buffer(buffer *b,  unsigned int max);
// add string to the buffer
void append_buffer(buffer *b, const char *s);
// print the buffer value to stdout
void render_buffer(buffer *b);
// clear the contents of the buffer
void clear_buffer(buffer *b);
// cleanup the buffer memory allocation
void destroy_buffer(buffer *b);

#endif
