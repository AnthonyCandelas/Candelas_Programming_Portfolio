#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "flood_utils.h"

/**
 * Author: Anthony Candelas
 * Date: 24OCT2025
 * Email: tsallinger2@unl.edu
 *
 * Description:
 * Implementation of the flood utility functions declared in
 * `flood_utils.h`.
 *
 * NOTE: See the header for ownership and error-code details.
 */

double *convertFlow(const double *flow, int numPoints) {
    if (flow == NULL || numPoints <= 0) {
        return NULL;
    }

    const double SQM_TO_SQFT = 10.76391;
    double *converted = malloc((size_t)numPoints * sizeof(double));
    if (converted == NULL) {
        return NULL;
    }

    for (int i = 0; i < numPoints; i++) {
        converted[i] = flow[i] * SQM_TO_SQFT;
    }

    return converted;
}

int minElevation(double **elevations, int n, int m, int *minRowIndex, int *minColIndex) {
    if (elevations == NULL || n <= 0 || m <= 0 || minRowIndex == NULL || minColIndex == NULL) {
        return 1;
    }

    if (elevations[0] == NULL) {
        return 2;
    }

    double minValue = elevations[0][0];
    int rowIndex = 0;
    int colIndex = 0;

    for (int i = 0; i < n; i++) {
        if (elevations[i] == NULL) {
            return 2;
        }
        for (int j = 0; j < m; j++) {
            if (elevations[i][j] < minValue) {
                minValue = elevations[i][j];
                rowIndex = i;
                colIndex = j;
            }
        }
    }

    *minRowIndex = rowIndex;
    *minColIndex = colIndex;
    return 0;
}

double floodCapacity(double **elevations, int n, int m, double waterLevel) {
    if (elevations == NULL || n <= 0 || m <= 0) {
        return 0.0; 
    }

    double total = 0.0;

    for (int i = 0; i < n; i++) {
        if (elevations[i] == NULL) {
            return 0.0;
        }
        for (int j = 0; j < m; j++) {
            if (elevations[i][j] < waterLevel) {
                total += (waterLevel - elevations[i][j]);
            }
        }
    }

    return total;
}