#include <stdio.h>
#include <stdlib.h>

#include "canvas.h"
#include "coordinate.h"

int main() {
  FILE *file = fopen("./res/points.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  canvas c;
  create_canvas(&c);

  char line[50];

  while (fgets(line, 50, file)) {
    coordinate3d *c = (coordinate3d *)malloc(sizeof(coordinate3d));
    if (c == NULL) {
      perror("Ran out of memory. Goodbye!");
      fclose(file);
      return EXIT_FAILURE;
    }

    from_str(c, line);
    // display(*c);
    free(c);
  }

  coordinate2d *p1 = (coordinate2d *)malloc(sizeof(coordinate2d));
  p1->x = 1;
  p1->y = 1;
  canvas_item ci1;
  ci1.point = p1;

  coordinate2d *p2 = (coordinate2d *)malloc(sizeof(coordinate2d));
  p2->x = 12;
  p2->y = 3;
  canvas_item ci2;
  ci2.point = p2;

  append_canvas(&c, &ci1);
  append_canvas(&c, &ci2);

  render_canvas(&c);

  fclose(file);
  destroy_canvas(&c);

  return 0;
}
