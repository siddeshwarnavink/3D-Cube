#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "canvas.h"
#include "coordinate.h"
#include "cube.h"

FILE *file;
bool file_open = true;
buffer b;
canvas c;
canvas_item *cu;

void cleanup() {
  printf("\033[?25h");
  if (file_open) {
    file_open = false;
    fclose(file);
  }
  destroy_canvas(&c);
  destroy_buffer(&b);
}

void handle_sigint(int sig) {
  if (sig > 1) {
    cleanup();
    exit(1);
  }
}

int main() {
  signal(SIGINT, handle_sigint);
  printf("\033[?25l");

  file = fopen("./res/points.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    cleanup();
    return EXIT_FAILURE;
  }

  create_buffer(&b, 20480);
  create_canvas(&c, &b);

  cu = (canvas_item *)malloc(sizeof(canvas_item));
  if (cu == NULL) {
    perror("No cube for you. Until next time.");
    cleanup();
    return EXIT_FAILURE;
  }

  cu->type = ITEM_TYPE_CUBE;

  int cu_points_len = 0;
  create_cube(&(cu->data.cube));

  char line[50];

  while (fgets(line, 50, file)) {
    from_str(cu->data.cube->points[cu_points_len], line);
    cu_points_len++;
  }

  append_canvas(&c, cu);
  render_canvas(&c);

  cleanup();

  return 0;
}
