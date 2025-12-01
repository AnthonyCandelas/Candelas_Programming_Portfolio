/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 30Nov2025
 * Lab/Task: Hack12 - Binomial coefficients
 *
 * Description:
 * Declarations for computing binomial coefficients using a naive
 * recursive implementation and a memoized (top-down) variant.
 *
 * Notes:
 * - The memo table created by `make_memo_table` must be freed with
 *   `free_memo_table` when no longer needed.
 * - Large inputs may overflow a C `long`; callers should ensure inputs
 *   are in a safe range for their platform.
 */

#ifndef HACK12_BINOMIAL_H
#define HACK12_BINOMIAL_H

#include <stddef.h>

/*
 * choose - Compute the binomial coefficient "n choose k" using naive
 * recursion (Pascal's rule).
 *
 * Parameters:
 *  - n, k: non-negative integers (if k>n behavior: returns 0)
 *
 * Returns:
 *  - the value of C(n,k) as a long, or 0 for invalid inputs. May
 *    overflow for large n/k.
 */
long choose(int n, int k);

/*
 * choose_memo - Top-down memoized version of choose. `table` must be a
 * (n+1) x (k+1) array created by `make_memo_table` and initialized to -1.
 *
 * Ownership:
 *  - The function does not allocate or free `table`; caller retains ownership.
 */
long choose_memo(int n, int k, long **table);

/*
 * make_memo_table - Allocate a (n+1) x (k+1) table for memoization.
 *
 * Returns:
 *  - pointer to the table or NULL on allocation failure.
 */
long **make_memo_table(int n, int k);

/*
 * free_memo_table - Free a table previously returned by make_memo_table.
 *
 * Parameters:
 *  - table: pointer returned by make_memo_table (may be NULL)
 *  - n: original n passed to make_memo_table (used to free rows)
 */
void free_memo_table(long **table, int n);

#endif /* HACK12_BINOMIAL_H */
