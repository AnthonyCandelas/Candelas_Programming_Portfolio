/*
* Author: Anthony Candelas
* Date: 20OCT2025
* Email: tsallinger2@unl.edu
*
* Description: Header file for Hack7 array utilities. Declares functions for
* checking membership, padded copying, reversing arrays, and helpers used in
* the array utilities tester. All functions use defensive checks and return
* NULL or 0 for invalid inputs where appropriate.
*/

#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdlib.h>

/**
 * Determines if the integer array contains x anywhere.
 *
 * @param arr pointer to array (may not be NULL if size > 0)
 * @param size number of elements in arr
 * @param x value to search for
 * @return 1 if found, 0 otherwise (or 0 if invalid inputs)
 */
int contains(const int *arr, int size, int x);

/**
 * Determines if the integer array contains x within indices [i, j].
 *
 * @param arr pointer to array
 * @param size number of elements in arr
 * @param x value to search for
 * @param i start index (inclusive)
 * @param j end index (inclusive)
 * @return 1 if found in range, 0 otherwise (or 0 for invalid inputs)
 */
int containsWithin(const int *arr, int size, int x, int i, int j);

/**
 * Creates a deep copy of `arr` with newSize. If newSize < oldSize,
 * copies only the first newSize elements. If newSize > oldSize, copies
 * all old elements and pads remaining elements with zeros.
 *
 * @param arr source array (may be NULL if oldSize == 0)
 * @param oldSize size of source array
 * @param newSize size of requested new array
 * @return pointer to dynamically allocated array (caller must free),
 *         or NULL on error (invalid params or allocation failure).
 */
int * paddedCopy(const int *arr, int oldSize, int newSize);

/**
 * Reverses elements in-place in the given array.
 *
 * @param arr array to reverse (must not be NULL if size > 0)
 * @param size number of elements
 * @return void (no return value). If arr is NULL or size <= 0, function is noop.
 */
void reverse(int *arr, int size);

/**
 * Returns a newly allocated array with elements of `arr` in reverse order.
 *
 * @param arr source array
 * @param size number of elements
 * @return new dynamically allocated reversed copy or NULL on error.
 */
int * reverseCopy(const int *arr, int size);

#endif
