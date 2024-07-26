#include <stdio.h>
#include <stdlib.h>

#include "coordinate.h"

int main() {
  FILE *file = fopen("./res/points.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  char line[50];

  while (fgets(line, 50, file)) {
    coordinate3d *c = (coordinate3d *)malloc(sizeof(coordinate3d));
    fromStr(c, line);
    display(*c);
    free(c);
  }

  fclose(file);

  return 0;
}
