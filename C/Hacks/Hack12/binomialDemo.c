/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 30Nov2025
 * Lab/Task: Hack12 - Binomial coefficients
 *
 * Description:
 * Small CLI to compare naive recursive and memoized implementations of
 * the binomial coefficient. Usage: `binomialDemo n k`.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "binomial.h"

static void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s n k\nCompute n choose k (naive and memoized)\n", prog);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        print_usage(argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    if (n < 0 || k < 0) {
        fprintf(stderr, "n and k must be non-negative integers\n");
        return 1;
    }

    /* verbose flag: optional third argument "-v" or "--verbose" */
    int verbose = 0;
    if (argc >= 4) {
        if (strcmp(argv[3], "-v") == 0 || strcmp(argv[3], "--verbose") == 0) verbose = 1;
    }

    clock_t start = 0, end = 0;
    long naive = 0;
    if (verbose) {
        if (n <= 30) {
            start = clock();
            naive = choose(n, k);
            end = clock();
            double naive_sec = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Naive choose(%d, %d) = %ld\n", n, k, naive);
            printf("Naive time: %.6f seconds\n", naive_sec);
        } else {
            printf("Naive choose(%d, %d) skipped (n > 30)\n", n, k);
        }
    }

    long **table = make_memo_table(n, k);
    if (!table) {
        fprintf(stderr, "Failed to allocate memo table for %d x %d\n", n + 1, k + 1);
        return 1;
    }
    start = clock();
    long memo = choose_memo(n, k, table);
    end = clock();
    double memo_sec = (double)(end - start) / CLOCKS_PER_SEC;

    /* Default (grader) output: single line exactly "C(n, k) = <value>" */
    printf("C(%d, %d) = %ld\n", n, k, memo);
    if (verbose) {
        printf("Memoized time: %.6f seconds\n", memo_sec);
    }

    free_memo_table(table, n);
    return 0;
}
