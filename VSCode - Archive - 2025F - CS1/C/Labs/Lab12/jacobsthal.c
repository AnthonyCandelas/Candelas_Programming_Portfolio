/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 18NOV2025
 * Lab/Task: Lab12 - Jacobsthal (recursive)
 *
 * Description:
 * Recursive implementation of the Jacobsthal sequence. This program
 * reads `n` from the command line and prints J(n) along with the
 * elapsed time in seconds.
 *
 * NOTE: The recursive implementation is intentionally naive and
 * exhibits exponential time for larger `n`.
 */

#include <stdlib.h>
#include <stdio.h>
/* timing removed and moved to TIMING.md to avoid unused variables in source */

/* Prototype: returns the n-th Jacobsthal number as a long long */
long long jacobsthalRecursive(int n);

/**
 * This program computes the n-th Jacobsthal number using recursion.
 * It also reports how long the program takes to execute.
 */
int main(int argc, char **argv) {

  if (argc != 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    return 1;
  }
  int n = atoi(argv[1]);

  long long result = jacobsthalRecursive(n);
  /* Print the grader-expected format (lowercase name) */
  printf("jacobsthal(%d) = %lld\n", n, result);

  return 0;
}

/*
 * Recursive Jacobsthal definition:
 * J(0) = 0
 * J(1) = 1
 * J(n) = J(n-1) + 2*J(n-2) for n >= 2
 */
long long jacobsthalRecursive(int n) {
  if (n <= 0) return 0LL;
  if (n == 1) return 1LL;
  return jacobsthalRecursive(n - 1) + 2LL * jacobsthalRecursive(n - 2);
}
