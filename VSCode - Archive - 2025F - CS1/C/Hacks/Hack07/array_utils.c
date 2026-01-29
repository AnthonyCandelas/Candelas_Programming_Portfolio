/*
* Author: Anthony Candelas
* Date: 20OCT2025
* Email: tsallinger2@unl.edu
*
* Description: Implementation of array utility functions for Hack7.
* Implements membership tests, padded copying, reversing in-place and
* reversed copy creation. All allocations are dynamic and callers are
* responsible for freeing returned pointers.
*/

#include "array_utils.h"
#include <stdlib.h>
#include <string.h>

int contains(const int *arr, int size, int x) {
  if (size <= 0) return 0;
  if (arr == NULL) return 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] == x) return 1;
  }
  return 0;
}

int containsWithin(const int *arr, int size, int x, int i, int j) {
  if (size <= 0) return 0;
  if (arr == NULL) return 0;
  if (i < 0 || j < 0 || i >= size || j >= size) return 0;
  if (i > j) return 0;
  for (int k = i; k <= j; k++) {
    if (arr[k] == x) return 1;
  }
  return 0;
}

int * paddedCopy(const int *arr, int oldSize, int newSize) {
  if (newSize < 0) return NULL;
  if (oldSize < 0) return NULL;

  int *out = (int *) malloc(sizeof(int) * (size_t)newSize);
  if (out == NULL) return NULL;

  int minCount = 0;
  if (arr != NULL && oldSize > 0) minCount = (oldSize < newSize) ? oldSize : newSize;

  if (minCount > 0) {
    memcpy(out, arr, sizeof(int) * (size_t)minCount);
  }
  if (newSize > minCount) {
    for (int i = minCount; i < newSize; i++) out[i] = 0;
  }

  return out;
}

void reverse(int *arr, int size) {
  if (size <= 0) return;
  if (arr == NULL) return;
  for (int i = 0, j = size - 1; i < j; i++, j--) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
}

int * reverseCopy(const int *arr, int size) {
  if (size <= 0) return NULL;
  if (arr == NULL) return NULL;
  int *out = (int *) malloc(sizeof(int) * (size_t)size);
  if (out == NULL) return NULL;
  for (int i = 0; i < size; i++) {
    out[i] = arr[size - 1 - i];
  }
  return out;
}
