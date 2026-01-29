/*
 * Author: Anthony Candelas
 * Date: 24OCT2025
 * Email: tsallinger2@unl.edu
 *
 * Description:
 * CSCE 155E/H - Fall 2025 Exam 2 Tester
 * This file is used for local debugging and testing of the flood utility
 * functions implemented in flood_utils.c. It should not be submitted.
 * It calls each function, prints the results, and verifies basic functionality.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "flood_utils.h"

/**
 * A utility function to print an array of n double values
 */
void printArray(const double *arr, int n);

int main(int argc, char **argv) {

    /* argc/argv are unused in this tester; cast to void to silence warnings */
    (void)argc;
    (void)argv;

    int errorCode;

    double flow[] = {350, 352.5, 351.2, 355.2, 354.0};
    double *sqftFlow = convertFlow(flow, 5);
    printf("Square Feet Flow: ");
    printArray(sqftFlow, 5);
    free(sqftFlow); // prevent memory leak

    double **map = (double **) malloc(sizeof(double *) * 3);
    double a[] = {9.50, 4.75, 7.25, 8.25, 8.25};
    double b[] = {8.50, 9.35, 6.45, 6.50, 7.25};
    double c[] = {7.50, 8.60, 4.50, 5.50, 5.75};
    map[0] = a;
    map[1] = b;
    map[2] = c;
    int n = 3, m = 5;

    int minRowIndex, minColIndex;
    errorCode = minElevation(map, n, m, &minRowIndex, &minColIndex);
    if (errorCode == 0) {
        printf("Minimum location: (%d, %d) = %.2f\n",
               minRowIndex, minColIndex, map[minRowIndex][minColIndex]);
    } else {
        printf("Error finding minimum elevation.\n");
    }

    double capacity = floodCapacity(map, n, m, 6.0);
    if (!isnan(capacity)) {
        printf("Total flood capacity: %.2f\n", capacity);
    } else {
        printf("Flood capacity computation failed.\n");
    }

    free(map);
    return 0;
}

void printArray(const double *arr, int n) {
    if (arr == NULL || n <= 0) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (int i = 0; i < n - 1; i++) {
        printf("%.2f, ", arr[i]);
    }
    printf("%.2f]\n", arr[n - 1]);
}