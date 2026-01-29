/*
* Author: Anthony Candelas
* Date: 12OCT2025
* Email: tsallinger2@unl.edu
*
* Description: This file implements Lab07 array utility functions. This uses dynamic
* allocation for arrays returned to callers. The caller is responsible
* for freeing returned memory where applicable.
*/

#include <stdlib.h>
#include <stdio.h>

#include "array_utils.h"

void printArray(const int *arr, int n) {
  if(arr == NULL) {
    printf("[null]\n");
    return;
  }
  if (n <= 0) {
    printf("[ ]\n");
    return;
  }
  printf("[ ");
  for(int i=0; i<n-1; i++) {
    printf("%d, ", arr[i]);
  }
  printf("%d ]\n", arr[n-1]);
  return;
}

void printTable(int **table, int n, int m) {
  if(table == NULL) {
    printf("[null]\n");
    return;
  }
  for(int i=0; i<n; i++) {
    printArray(table[i], m);
  }
  return;
}

int * generateRandomArray(int size) {
  if(size <= 0) {
    return NULL;
  }

  /* Allocate on the heap so the array remains valid after returning. */
  int *randomArr = (int *) malloc(sizeof(int) * size);
  if(randomArr == NULL) {
    fprintf(stderr, "Memory allocation failed in generateRandomArray.\n");
    exit(EXIT_FAILURE);
  }

  for(int i=0; i<size; i++) {
    randomArr[i] = rand() % 100;
  }
  return randomArr;
}

int getSum(const int *arr, int size) {
  if(arr == NULL) {
    return 0;
  }
  int total = 0;
  for(int i=0; i<size; i++) {
    total += arr[i];
  }
  return total;
}

void freeTable(int **table, int n) {
  if(table == NULL) {
    return;
  }
  for(int i=0; i<n; i++) {
    free(table[i]);
  }
  free(table);
}

double getMean(const int *arr, int size) {
  if (arr == NULL || size <= 0) {
    return 0.0;
  }
  return (double)getSum(arr, size) / (double)size;
}

int getMin(const int *arr, int size) {
  if (arr == NULL || size <= 0) return 0;
  int min = arr[0];
  for (int i = 1; i < size; i++) {
    if (arr[i] < min) min = arr[i];
  }
  return min;
}

int getIndexOfMin(const int *arr, int size) {
  if (arr == NULL || size <= 0) return -1;
  int minIndex = 0;
  for (int i = 1; i < size; i++) {
    if (arr[i] < arr[minIndex]) minIndex = i;
  }
  return minIndex;
}

int getMax(const int *arr, int size) {
  if (arr == NULL || size <= 0) return 0;
  int max = arr[0];
  for (int i = 1; i < size; i++) {
    if (arr[i] > max) max = arr[i];
  }
  return max;
}

int getIndexOfMax(const int *arr, int size) {
  if (arr == NULL || size <= 0) return -1;
  int maxIndex = 0;
  for (int i = 1; i < size; i++) {
    if (arr[i] > arr[maxIndex]) maxIndex = i;
  }
  return maxIndex;
}

int * filterThreshold(const int *arr, int size, int threshold, int *resultSize) {
  if (arr == NULL || size <= 0 || resultSize == NULL) {
    if (resultSize) *resultSize = 0;
    return NULL;
  }

  /* First pass: count how many meet the criteria */
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] >= threshold) count++;
  }

  if (count == 0) {
    *resultSize = 0;
    return NULL;
  }

  int *out = (int *) malloc(sizeof(int) * count);
  if (out == NULL) {
    fprintf(stderr, "Memory allocation failed in filterThreshold.\n");
    exit(EXIT_FAILURE);
  }

  int j = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] >= threshold) {
      out[j++] = arr[i];
    }
  }

  *resultSize = count;
  return out;
}

int **createMultiplicationTable(int n, int m) {
  if (n <= 0 || m <= 0) return NULL;

  int **table = (int **) malloc(sizeof(int *) * n);
  if (table == NULL) {
    fprintf(stderr, "Memory allocation failed in createMultiplicationTable.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++) {
    table[i] = (int *) malloc(sizeof(int) * m);
    if (table[i] == NULL) {
      fprintf(stderr, "Memory allocation failed in createMultiplicationTable.\n");
      /* free previously allocated rows before exiting to be tidy */
      for (int k = 0; k < i; k++) free(table[k]);
      free(table);
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < m; j++) {
      table[i][j] = (i + 1) * (j + 1);
    }
  }
  return table;
}
