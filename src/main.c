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
    coordinate3d *co = (coordinate3d *)malloc(sizeof(coordinate3d));
    if (co == NULL) {
      perror("Ran out of memory. Goodbye!");
      fclose(file);
      return EXIT_FAILURE;
    }

    from_str(co, line);

    coordinate2d *p = to_2d(co);
    p->x = ((p->x * 0.5) + 0.5) * CANVAS_WIDTH / 2;
    p->y = ((p->y * 0.5) + 0.5) * CANVAS_HEIGHT / 2;

    canvas_item *itm = (canvas_item *)malloc(sizeof(coordinate2d));
    itm->point = p;

    append_canvas(&c, itm);

    free(co);
  }

  render_canvas(&c);

  fclose(file);
  destroy_canvas(&c);

  return 0;
}
