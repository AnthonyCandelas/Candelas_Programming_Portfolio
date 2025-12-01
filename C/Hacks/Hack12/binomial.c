/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 30Nov2025
 * Lab/Task: Hack12 - Binomial coefficients
 *
 * Description:
 * Implementations of naive and memoized binomial coefficient routines.
 *
 * Notes:
 * - The memo table uses -1 as the sentinel for "not computed".
 */

#include "binomial.h"
#include <stdlib.h>

long choose(int n, int k) {
    if (k < 0 || n < 0) return 0;
    if (k > n) return 0;
    if (k == 0 || k == n) return 1L;
    return choose(n-1, k) + choose(n-1, k-1);
}

/* Allocate a (n+1) x (k+1) memo table. Each cell is initialized to -1. */
long **make_memo_table(int n, int k) {
    if (n < 0 || k < 0) return NULL;
    long **table = malloc((size_t)(n + 1) * sizeof(long *));
    if (!table) return NULL;
    for (int i = 0; i <= n; ++i) {
        table[i] = malloc((size_t)(k + 1) * sizeof(long));
        if (!table[i]) {
            for (int j = 0; j < i; ++j) free(table[j]);
            free(table);
            return NULL;
        }
        for (int j = 0; j <= k; ++j) table[i][j] = -1L;
    }
    return table;
}

/* Free a memo table allocated by make_memo_table. */
void free_memo_table(long **table, int n) {
    if (!table) return;
    for (int i = 0; i <= n; ++i) free(table[i]);
    free(table);
}

/* Memoized top-down computation. Falls back to `choose` if table is NULL. */
long choose_memo(int n, int k, long **table) {
    if (k < 0 || n < 0) return 0;
    if (k > n) return 0;
    if (k == 0 || k == n) return 1L;
    if (!table) return choose(n, k);
    if (table[n][k] != -1L) return table[n][k];
    long a = choose_memo(n - 1, k, table);
    long b = choose_memo(n - 1, k - 1, table);
    table[n][k] = a + b;
    return table[n][k];
}
