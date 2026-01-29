/*
* Author: Anthony Candelas
* Date: 12OCT2025
* Email: tsallinger2@unl.edu
*
* Description: In this header file for Lab07 array utilities. This document declares functions for
* generating random arrays, computing statistics, filtering arrays, and
* creating multiplication tables. Follow the provided prototypes exactly.
*/

#ifndef ARRAY_UTILS_H
/**
 * The #ifndef and #endif are macros,
 * these are simple statements that cutoff
 * the executeable code, I mainly use it for
 * documents that are or may be re-used in the future
 * e.g., the colorUtils files
 */
#define ARRAY_UTILS_H

#include <stdlib.h>
#include <stdio.h>

/**
 * Prints the given integer array to the standard output
 */
void printArray(const int *arr, int n);

/**
 * Prints the given (n x m) integer table to the standard
 * output.
 */
void printTable(int **table, int n, int m);

/**
 * Generates an array of integers of the given size filled
 * with random integer values between 0 and 100 (exclusive).
 * This function assumes that the random number generator
 * has already been seeded.
 *
 * Returns a pointer to a dynamically allocated array which
 * the caller must free when finished.
 */
int * generateRandomArray(int size);

/**
 * Sums the elements in the given array.
 */
int getSum(const int *arr, int size);

/**
 * Frees the given (n x m) table.  Only the first parameter
 * (n, number of rows) is necessary to free the table.
 */
void freeTable(int **table, int n);

/**
 * Computes the mean (average) of the elements in arr.
 * Returns 0.0 if arr is NULL or size <= 0.
 */
double getMean(const int *arr, int size);

/**
 * Returns the minimum element in arr. If arr is NULL or size <= 0,
 * returns 0 (caller should avoid calling with invalid args).
 */
int getMin(const int *arr, int size);

/**
 * Returns the index of the minimum element in arr. If arr is NULL
 * or size <= 0, returns -1.
 */
int getIndexOfMin(const int *arr, int size);

/**
 * Returns the maximum element in arr. If arr is NULL or size <= 0,
 * returns 0.
 */
int getMax(const int *arr, int size);

/**
 * Returns the index of the maximum element in arr. If arr is NULL
 * or size <= 0, returns -1.
 */
int getIndexOfMax(const int *arr, int size);

/**
 * Creates and returns a new array containing elements from arr
 * that are >= threshold. The size of the returned array is written
 * to resultSize. Caller must free the returned array. If no elements
 * match, returns an allocated array of size 0 (or NULL, but this
 * implementation returns NULL and sets *resultSize = 0).
 */
int * filterThreshold(const int *arr, int size, int threshold, int *resultSize);

/**
 * Creates an n x m multiplication table and returns it as a
 * dynamically allocated 2-D array (array of pointers). Caller must
 * free each row and then the array of row pointers using freeTable().
 */
int **createMultiplicationTable(int n, int m);

#endif /* ARRAY_UTILS_H */
