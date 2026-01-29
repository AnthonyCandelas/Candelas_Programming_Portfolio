/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-10
 * Lab/Task: Hack10
 *
 * Description:
 * Declarations for simple file utility functions used by the
 * Hack10 exercises. Functions are documented in the corresponding
 * implementation file.
 */

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stddef.h>

/**
 * Read the entire contents of a file into a single malloc'd string.
 * The returned string preserves newline characters. The caller is
 * responsible for freeing the returned buffer. On error, returns
 * NULL.
 */
char *getFileContents(const char *filePath);

/**
 * Read a file and return its lines as a NULL-terminated array of
 * malloc'd strings (no trailing newline characters). The function
 * sets *numLines to the number of lines. The caller is responsible
 * for freeing both the array and the contained strings. On error,
 * returns NULL and sets *numLines to 0.
 */
char **getFileLines(const char *filePath, int *numLines);

#endif /* FILE_UTILS_H */
