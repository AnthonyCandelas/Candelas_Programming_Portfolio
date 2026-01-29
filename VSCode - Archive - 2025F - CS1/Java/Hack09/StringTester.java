/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack09 - String Utilities (Java)
 *
 * Description:
 * Test driver for `StringUtils`. Demonstrates at least three cases per
 * function and prints results to stdout. Tests are simple visual checks.
 */

package unl.soc;

import java.util.List;

public class StringTester {

	public static boolean printTest(String name, Object expected, Object actual) {
		boolean pass;
		if (expected == null) {
			pass = (actual == null);
		} else {
			pass = expected.equals(actual);
		}
		System.out.println("[" + name + "] expected: " + expected + " | actual: " + actual + (pass ? "  PASS" : "  FAIL"));
		return pass;
	}

	public static void main(String[] args) {
	/* replaceChar tests */
	System.out.println("Testing replaceChar:");
		int failures = 0;
		if (!printTest("replace1", "bonono", StringUtils.replaceChar("banana", 'a', 'o'))) failures++;
		if (!printTest("replace2", "hexxo worxd", StringUtils.replaceChar("hello world", 'l', 'x'))) failures++;
		if (!printTest("replace-null", null, StringUtils.replaceChar(null, 'a', 'b'))) failures++;

	System.out.println();

	/* removeChar tests */
	System.out.println("Testing removeChar:");
		if (!printTest("remove1", "miiippi", StringUtils.removeChar("mississippi", 's'))) failures++;
		if (!printTest("remove2", "", StringUtils.removeChar("aaaa", 'a'))) failures++;
		if (!printTest("remove3", "keep", StringUtils.removeChar("keep", 'z'))) failures++;

	System.out.println();

	/* lengthSplit tests */
	System.out.println("Testing lengthSplit:");
		String sample = "Hello World, how are you?";
		List<String> parts = StringUtils.lengthSplit(sample, 3);
		System.out.println("input: \"" + sample + "\" n=3 -> " + parts);
	/* expected size 9 as in assignment example */
	if (!printTest("lengthSplit-size", 9, parts.size())) failures++;

	/* additional lengthSplit edge cases */
		List<String> p2 = StringUtils.lengthSplit("abcd", 2);
		if (!printTest("lengthSplit-abcd", java.util.Arrays.asList("ab", "cd"), p2)) failures++;

		List<String> p3 = StringUtils.lengthSplit("abc", 5);
		if (!printTest("lengthSplit-short", java.util.Arrays.asList("abc"), p3)) failures++;

		System.out.println();
		if (failures == 0) {
			System.out.println("All tests passed.");
			System.exit(0);
		} else {
			System.out.println(failures + " test(s) failed.");
			System.exit(1);
		}
	}
}
