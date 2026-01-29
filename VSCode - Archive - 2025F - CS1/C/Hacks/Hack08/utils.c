/**
 * Collection of misc utility functions.
 *
 * There are no bugs in this file.
 */
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

void flushInput() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) { }
  return;
}
