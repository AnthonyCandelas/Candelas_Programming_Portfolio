#ifndef FLOOD_UTILS_H
#define FLOOD_UTILS_H
/* Prevents multiple inclusions of the header file (avoids duplicate
 * definition errors when headers are included from more than one source)
 */

/**
 * Author: Anthony Candelas
 * Date: 24OCT2025
 * Email: tsallinger2@unl.edu
 *
 * Description:
 * Utilities used for Exam 2 to convert flow values and analyze a grid of
 * elevations for minimum values and flood capacity.
 *
 * NOTE: convertFlow returns a malloc'd buffer; the caller must free()
 * the returned pointer when finished.
 */

/**
 * Converts an array of area values from square meters to square feet.
 *
 * @param flow Pointer to an array of length numPoints containing values
 *        in square meters. Must not be NULL when numPoints > 0.
 * @param numPoints Number of elements in @p flow. Must be > 0.
 * @return A pointer to a newly allocated array (size numPoints) with
 *         values converted to square feet. The caller takes ownership
 *         of the returned buffer and must call free() when finished.
 *         Returns NULL on error (invalid arguments or allocation failure).
 */
double * convertFlow(const double *flow, int numPoints);

/**
 * Find the position of the minimum elevation in an n-by-m grid.
 *
 * @param elevations An array of n row pointers, each pointing to an array
 *        of m double values representing elevations. The rows must be
 *        non-NULL. The function does not take ownership of the memory.
 * @param n Number of rows (must be > 0).
 * @param m Number of columns per row (must be > 0).
 * @param minRowIndex Out parameter set to the 0-based row index of the
 *        minimum value on success.
 * @param minColIndex Out parameter set to the 0-based column index of the
 *        minimum value on success.
 * @return 0 on success. Non-zero error codes:
 *         - 1 : invalid arguments (NULL pointers or non-positive dimensions)
 *         - 2 : a row pointer inside @p elevations was NULL
 */
int minElevation(double **elevations, int n, int m, int *minRowIndex, int *minColIndex);

/**
 * Compute the total flood capacity of an n-by-m elevation grid for a
 * given water level. Capacity is the sum of (waterLevel - elevation)
 * for every cell where elevation < waterLevel.
 *
 * @param elevations An array of n row pointers to arrays of m doubles.
 * @param n Number of rows (> 0).
 * @param m Number of columns (> 0).
 * @param waterLevel Water level to measure capacity against.
 * @return The total capacity (same units as elevation). Returns 0.0 on
 *         error (invalid arguments or a NULL row pointer).
 */
double floodCapacity(double **elevations, int n, int m, double waterLevel);

#endif /* FLOOD_UTILS_H */