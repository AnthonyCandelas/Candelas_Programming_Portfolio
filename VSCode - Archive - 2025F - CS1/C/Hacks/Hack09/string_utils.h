/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack09 - String Utilities
 *
 * Description:
 *   Header file that lists the functions used for Hack09. Each entry
 *   includes a short note about what the function does and what the
 *   caller should expect. This file is the quick reference for using
 *   the utilities in other code or tests.
 *
 * Function contracts:
 *   - void replaceChar(char *s, char oldChar, char newChar);
 *       Replaces occurrences of oldChar with newChar in-place. If s is
 *       NULL the function does nothing.
 *
 *   - char *replaceCharCopy(const char *s, char oldChar, char newChar);
 *       Returns a newly allocated string (caller frees) that is a copy
 *       of s with oldChar replaced by newChar. Returns NULL on NULL
 *       input or allocation failure.
 *
 *   - void removeChar(char *s, char c);
 *       Removes all instances of c from s in-place. Shifts subsequent
 *       characters and terminates the result. No-op on NULL input.
 *
 *   - char *removeCharCopy(const char *s, char c);
 *       Returns a newly allocated string (caller frees) with all
 *       instances of c removed. The returned buffer is sized exactly
 *       to the result. Returns NULL on NULL input or allocation failure.
 *
 *   - char **lengthSplit(const char *s, int n);
 *       Splits s into pieces of length n and returns an array of
 *       pointers to NUL-terminated strings. Each piece is separately
 *       allocated; the caller must free each string and the array.
 *       Returns NULL on NULL input or invalid n.
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>

void replaceChar(char *s, char oldChar, char newChar);

char *replaceCharCopy(const char *s, char oldChar, char newChar);

void removeChar(char *s, char c);

char *removeCharCopy(const char *s, char c);

char **lengthSplit(const char *s, int n);

#endif /* STRING_UTILS_H */

