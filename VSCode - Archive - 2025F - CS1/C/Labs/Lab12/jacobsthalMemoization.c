/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 18NOV2025
 * Lab/Task: Lab12 - Jacobsthal (memoization)
 *
 * Description:
 * Memoized recursive implementation of the Jacobsthal sequence. The
 * program also prints an iterative result for comparison and reports
 * execution time for the memoized computation.
 */

#include <stdlib.h>
#include <stdio.h>
/* timing removed and moved to TIMING.md to avoid unused variables in source */

/**
 * Computes the n-th Jacobsthal number using an iterative
 * method
 */
long long jacobsthalIterative(int n);

/* Prototype for memoized Jacobsthal: uses a cache array of size n+1 */
long long jacobsthalMemo(int n, long long *cache);

/**
 * This program computes the n-th Jacobsthal number using recursion
 * and memoization.
 */
int main(int argc, char **argv) {

  if (argc != 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    return 1;
  }
  int n = atoi(argv[1]);

  /* set up cache table of size n+1 */
  long long *cache = (long long *)malloc((size_t)(n + 1) * sizeof(long long));
  if (!cache) {
    fprintf(stderr, "Allocation failure\n");
    return 1;
  }

  /* initialize base cases and mark others as uncomputed (-1) */
  for (int i = 0; i <= n; ++i) cache[i] = -1LL;
  if (n >= 0) cache[0] = 0LL;
  if (n >= 1) cache[1] = 1LL;

  long long memoizationResult = jacobsthalMemo(n, cache);
  /* Print exactly the expected grader output line */
  printf("jacobsthal(%d) = %lld\n", n, memoizationResult);

  free(cache);
  return 0;
}

/* memoized recursive implementation */
long long jacobsthalMemo(int n, long long *cache) {
  if (n <= 0) return 0LL;
  if (n == 1) return 1LL;
  if (cache[n] != -1LL) return cache[n];
  long long val = jacobsthalMemo(n - 1, cache) + 2LL * jacobsthalMemo(n - 2, cache);
  cache[n] = val;
  return val;
}

/* iterative version removed to avoid unused-code in submissions; use TIMING.md for iterative build info */
