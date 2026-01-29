/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack07 - List Utilities
 *
 * Description:
 * Utility methods for working with Lists of Integer values. Includes search
 * and transformation helpers used in Hack07.
 */

package unl.soc;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class ListUtils {

    /**
     * Returns true if the list contains x anywhere.
     *
     * @param list the list to search (may not be null)
     * @param x    the target integer
     * @return true if x is found, false otherwise
     * @throws IllegalArgumentException if list is null
     */
    public static boolean contains(List<Integer> list, int x) {
        if (list == null) throw new IllegalArgumentException("list must not be null");
        return list.contains(Integer.valueOf(x));
    }

    /**
     * Returns true if the list contains x between indices i and j (inclusive).
     *
     * @param list the list to search (may not be null)
     * @param x    the target integer
     * @param i    start index (inclusive)
     * @param j    end index (inclusive)
     * @return true if x is found in range [i, j], false otherwise
     * @throws IllegalArgumentException if list is null or indices invalid
     */
    public static boolean containsWithin(List<Integer> list, int x, int i, int j) {
        if (list == null) throw new IllegalArgumentException("list must not be null");
        if (i < 0 || j < 0 || i >= list.size() || j >= list.size() || i > j) {
            throw new IllegalArgumentException("invalid indices");
        }
        for (int idx = i; idx <= j; idx++) {
            if (list.get(idx) == x) return true;
        }
        return false;
    }

    /**
     * Returns a new deep copy of the list with the requested newSize.
     * If newSize < original size, copies first newSize elements.
     * If newSize > original size, pads with zeros.
     *
     * @param list    original list (may not be null)
     * @param newSize desired new size (>= 0)
     * @return new List<Integer> of length newSize
     * @throws IllegalArgumentException if list is null or newSize < 0
     */
    public static List<Integer> paddedCopy(List<Integer> list, int newSize) {
        if (list == null) throw new IllegalArgumentException("list must not be null");
        if (newSize < 0) throw new IllegalArgumentException("newSize must be >= 0");

        List<Integer> out = new ArrayList<>(newSize);
        int toCopy = Math.min(list.size(), newSize);
        for (int i = 0; i < toCopy; i++) out.add(list.get(i));
        for (int i = toCopy; i < newSize; i++) out.add(0);
        return out;
    }

    /**
     * Reverses the list in place.
     *
     * @param list list to reverse (may not be null)
     * @throws IllegalArgumentException if list is null
     */
    public static void reverse(List<Integer> list) {
        if (list == null) throw new IllegalArgumentException("list must not be null");
        Collections.reverse(list);
    }

    /**
     * Returns a new reversed deep copy of the given list.
     *
     * @param list list to copy (may not be null)
     * @return new List<Integer> containing elements in reverse order
     * @throws IllegalArgumentException if list is null
     */
    public static List<Integer> reverseCopy(List<Integer> list) {
        if (list == null) throw new IllegalArgumentException("list must not be null");
        List<Integer> copy = new ArrayList<>(list);
        Collections.reverse(copy);
        return copy;
    }
}