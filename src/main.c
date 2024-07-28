#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "canvas.h"
#include "coordinate.h"
#include "cube.h"

FILE *file;
canvas c;
canvas_item *cu;

void cleanup() {
  if (file != NULL) {
    fclose(file);
  }
  destroy_canvas(&c);
}

void handle_sigint(int sig) {
  if (sig > 1) {
    cleanup();
    exit(1);
  }
}

int main() {
  signal(SIGINT, handle_sigint);

  file = fopen("./res/points.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    cleanup();
    return EXIT_FAILURE;
  }

  create_canvas(&c);

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

  fclose(file);

  append_canvas(&c, cu);
  render_canvas(&c);

  cleanup();

  return 0;
}
