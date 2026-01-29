/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-10
 * Lab/Task: Hack10
 *
 * Simple tester for file_utils functions. This creates small temporary
 * files and verifies that getFileContents and getFileLines behave as
 * expected. This is a visual tester - not required for grading.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"

int main(void) {
  /* We'll run 3 cases for each function as requested:
     1) empty file
     2) small multi-line file
     3) file with blank lines and CRLF endings
  */

  const char *names[3] = { "/tmp/fut_case1.txt", "/tmp/fut_case2.txt", "/tmp/fut_case3.txt" };

  /* Case 1: empty file */
  FILE *f = fopen(names[0], "w");
  if (!f) return 1;
  fclose(f);

  /* Case 2: small multi-line file */
  f = fopen(names[1], "w");
  if (!f) return 1;
  fprintf(f, "alpha\nbeta\ngamma\n");
  fclose(f);

  /* Case 3: blank lines and CRLF endings */
  f = fopen(names[2], "w");
  if (!f) return 1;
  fprintf(f, "one\r\n\r\nthree\r\n");
  fclose(f);

  for (int case_i = 0; case_i < 3; case_i++) {
    int nlines = -1;
    char *contents = getFileContents(names[case_i]);
    char **lines = getFileLines(names[case_i], &nlines);

    printf("--- Case %d: file=%s ---\n", case_i+1, names[case_i]);

    if (contents != NULL) {
      printf("getFileContents length=%zu\n", strlen(contents));
      /* print a short preview */
      printf("contents preview:\n%s\n", contents[0] ? contents : "(empty)");
      free(contents);
    } else {
      printf("getFileContents: NULL\n");
    }

    if (lines != NULL) {
      printf("getFileLines -> %d lines\n", nlines);
      for (int i = 0; i < nlines; i++) {
        printf("  [%d] '%s'\n", i, lines[i]);
        free(lines[i]);
      }
      free(lines);
    } else {
      printf("getFileLines: NULL\n");
    }
    printf("\n");
  }

  /* cleanup */
  for (int i = 0; i < 3; i++) remove(names[i]);
  printf("Expanded tests complete.\n");
  return 0;
}
