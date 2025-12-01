package unl.soc;

/**
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 01Dec2025
 * Lab/Task: Hack12 - Binomial coefficients (naive recursion + memoization)
 *
 * Description:
 * This class implements two approaches to computing binomial
 * coefficients ("n choose k"): a naive recursive implementation that
 * returns a primitive `long`, and a memoized top-down implementation
 * that returns a `BigInteger` to support very large values.
 *
 * Notes:
 * - The memoized method uses a static `Map<Pair<Integer,Integer>,BigInteger>`
 *   as a cache. Pair is implemented as a small immutable nested class.
 * - The `main` method accepts command-line arguments `n k` and prints
 *   results and timings for both implementations. The naive run is
 *   skipped for large `n` to avoid excessive runtime.
 */

import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;

/** Utilities for computing binomial coefficients. */
public class Binomial {

	/**
	 * Simple immutable pair of integers used as map keys for caching.
	 */
	private static final class Pair {
		final int n;
		final int k;

		Pair(int n, int k) {
			this.n = n;
			this.k = k;
		}

		@Override
		public boolean equals(Object o) {
			if (this == o) return true;
			if (!(o instanceof Pair)) return false;
			Pair p = (Pair) o;
			return n == p.n && k == p.k;
		}

		@Override
		public int hashCode() {
			return 31 * n + k;
		}
	}

	/** Cache for memoized BigInteger results. */
	private static final Map<Pair, BigInteger> CACHE = new HashMap<>();

	/**
	 * Naive recursive computation of C(n,k) using Pascal's rule.
	 *
	 * This method uses `long` and may overflow for large n/k. It is
	 * intentionally simple for benchmarking and correctness testing.
	 *
	 * @param n number of items (non-negative)
	 * @param k items to choose (non-negative)
	 * @return C(n,k) as a long, or 0 for invalid inputs
	 */
	public static long chooseNaive(int n, int k) {
		if (n < 0 || k < 0) return 0L;
		if (k > n) return 0L;
		if (k == 0 || k == n) return 1L;
		return chooseNaive(n - 1, k) + chooseNaive(n - 1, k - 1);
	}

	/**
	 * Memoized computation of C(n,k) returning a BigInteger. Uses a
	 * static Map<Pair,Integer> cache to avoid repeated work.
	 *
	 * @param n number of items (non-negative)
	 * @param k items to choose (non-negative)
	 * @return C(n,k) as a BigInteger (0 for invalid inputs)
	 */
	public static BigInteger binomial(int n, int k) {
		if (n < 0 || k < 0) return BigInteger.ZERO;
		if (k > n) return BigInteger.ZERO;
		if (k == 0 || k == n) return BigInteger.ONE;

		Pair key = new Pair(n, k);
		BigInteger cached = CACHE.get(key);
		if (cached != null) return cached;

		BigInteger a = binomial(n - 1, k);
		BigInteger b = binomial(n - 1, k - 1);
		BigInteger result = a.add(b);
		CACHE.put(key, result);
		return result;
	}

	/**
	 * Command-line entry point. Usage: `java Java.Hack12.Binomial n k`.
	 * Prints results and timings for the naive (guarded) and memoized
	 * implementations.
	 */
	public static void main(String[] args) {
		if (args.length < 2) {
			System.err.println("Usage: java Java.Hack12.Binomial n k");
			return;
		}
		int n, k;
		try {
			n = Integer.parseInt(args[0]);
			k = Integer.parseInt(args[1]);
		} catch (NumberFormatException e) {
			System.err.println("n and k must be integers");
			return;
		}

		if (n < 0 || k < 0) {
			System.err.println("n and k must be non-negative");
			return;
		}

		/* parse optional verbose flag (third argument) */
		boolean verbose = false;
		if (args.length >= 3) {
			if ("-v".equals(args[2]) || "--verbose".equals(args[2])) verbose = true;
		}

		if (verbose) {
			/* Attempt naive run only for moderately small n to avoid long runs. */
			if (n <= 30) {
				long t0 = System.nanoTime();
				long naive = chooseNaive(n, k);
				long t1 = System.nanoTime();
				double sec = (t1 - t0) / 1e9;
				System.out.printf("Naive choose(%d, %d) = %d\n", n, k, naive);
				System.out.printf("Naive time: %.6f seconds\n", sec);
			} else {
				System.out.printf("Naive choose(%d, %d) skipped (n > 30)\n", n, k);
			}
		}

		/* Memoized BigInteger computation */
		long m0 = System.nanoTime();
		BigInteger ans = binomial(n, k);
		long m1 = System.nanoTime();
		double msec = (m1 - m0) / 1e9;

		/* Default (grader) output: single line exactly "C(n, k) = <value>" */
		System.out.printf("C(%d, %d) = %s\n", n, k, ans.toString());
		if (verbose) System.out.printf("Memoized time: %.6f seconds\n", msec);
	}
}
