#include <stdio.h>
#include <stdlib.h>

#include "canvas.h"
#include "coordinate.h"
#include "cube.h"

int main() {
  FILE *file = fopen("./res/points.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  canvas c;
  create_canvas(&c);

  canvas_item *cu = (canvas_item *)malloc(sizeof(canvas_item));
  if (cu == NULL) {
    perror("No cube for you. Until next time.");
    fclose(file);
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

  destroy_canvas(&c);

  return 0;
}
