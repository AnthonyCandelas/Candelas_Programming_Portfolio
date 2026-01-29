/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-10
 * Lab/Task: Hack10
 *
 * Implementation of simple file utilities used by Hack10.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "file_utils.h"

#define READ_BUF 2048

char *getFileContents(const char *filePath) {
  if (filePath == NULL) return NULL;
  FILE *in = fopen(filePath, "rb");
  if (in == NULL) return NULL;

  if (fseek(in, 0, SEEK_END) != 0) {
    fclose(in);
    return NULL;
  }
  long sz = ftell(in);
  if (sz < 0) sz = 0;
  rewind(in);

  /* allocate buffer (add one for NUL) */
  char *buf = (char *)malloc((size_t)sz + 1);
  if (buf == NULL) {
    fclose(in);
    return NULL;
  }

  size_t read = fread(buf, 1, (size_t)sz, in);
  buf[read] = '\0';
  fclose(in);
  return buf;
}

char **getFileLines(const char *filePath, int *numLines) {
  if (numLines == NULL) return NULL;
  *numLines = 0;
  if (filePath == NULL) return NULL;

  FILE *in = fopen(filePath, "r");
  if (in == NULL) return NULL;

  size_t cap = 16;
  char **lines = (char **)malloc(sizeof(char *) * cap);
  if (lines == NULL) { fclose(in); return NULL; }

  char buf[READ_BUF];
  int count = 0;
  while (fgets(buf, sizeof(buf), in) != NULL) {
    size_t len = strlen(buf);
    /* chomp newline(s) */
    while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
      buf[--len] = '\0';
    }
    char *copy = (char *)malloc(len + 1);
    if (copy == NULL) {
      /* free previously allocated lines */
      for (int i = 0; i < count; i++) free(lines[i]);
      free(lines);
      fclose(in);
      *numLines = 0;
      return NULL;
    }
    memcpy(copy, buf, len + 1);

    if ((size_t)count >= cap) {
      size_t ncap = cap * 2;
      char **tmp = (char **)realloc(lines, sizeof(char *) * ncap);
      if (tmp == NULL) {
        free(copy);
        for (int i = 0; i < count; i++) free(lines[i]);
        free(lines);
        fclose(in);
        *numLines = 0;
        return NULL;
      }
      lines = tmp;
      cap = ncap;
    }
    lines[count++] = copy;
  }
  fclose(in);

  /* shrink to fit */
  if ((size_t)count < cap) {
    char **tmp = (char **)realloc(lines, sizeof(char *) * count);
    if (tmp != NULL) lines = tmp;
  }

  *numLines = count;
  return lines;
}
