/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack09 - String Utilities
 *
 * Description:
 * Utility methods for string manipulation used in Hack09. All methods return
 * newly allocated String instances. Behavior for null inputs are documented;
 * they are documented per method.
 */

package unl.soc;

import java.util.ArrayList;
import java.util.List;

public class StringUtils {

	/**
	 * Replace all instances of oldChar with newChar in the given string.
	 *
	 * @param s the input string (may be null)
	 * @param oldChar character to replace
	 * @param newChar replacement character
	 * @return a new String with replacements applied, or null if s is null
	 */
	public static String replaceChar(String s, char oldChar, char newChar) {
		if (s == null) return null;
		if (s.indexOf(oldChar) == -1) return new String(s);
		StringBuilder sb = new StringBuilder(s.length());
		for (int i = 0; i < s.length(); i++) {
			char c = s.charAt(i);
			sb.append(c == oldChar ? newChar : c);
		}
		return sb.toString();
	}

	/**
	 * Remove all instances of character c from the given string.
	 *
	 * @param s the input string (may be null)
	 * @param c character to remove
	 * @return a new String with characters removed, or null if s is null
	 */
	public static String removeChar(String s, char c) {
		if (s == null) return null;
		StringBuilder sb = new StringBuilder(s.length());
		for (int i = 0; i < s.length(); i++) {
			char ch = s.charAt(i);
			if (ch != c) sb.append(ch);
		}
		return sb.toString();
	}

	/**
	 * Split the string into substrings of length n. The final substring may be
	 * shorter if the length of s is not a multiple of n.
	 *
	 * @param s the input string (must not be null)
	 * @param n the chunk length (must be > 0)
	 * @return List of substrings (may be empty if s is empty)
	 * @throws IllegalArgumentException if s is null or n <= 0
	 */
	public static List<String> lengthSplit(String s, int n) {
		if (s == null) throw new IllegalArgumentException("s must not be null");
		if (n <= 0) throw new IllegalArgumentException("n must be > 0");
		List<String> parts = new ArrayList<>((s.length() + n - 1) / n);
		for (int i = 0; i < s.length(); i += n) {
			int end = Math.min(i + n, s.length());
			parts.add(s.substring(i, end));
		}
		return parts;
	}

}
