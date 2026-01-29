/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack09 - String Utilities
 *
 * Description:
 *   Test program that runs three example cases for each function in
 *   `string_utils`. It prints test outputs and frees any memory
 *   allocated by the copy functions.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string_utils.h"

int stringArraysEqual(char **a, char **b, int n) {

	if(a == NULL && b == NULL) {
		return 1;
	} else if(a == NULL && b != NULL || a != NULL && b == NULL) {
		return 0;
	}

	for(int i=0; i<n; i++) {
		if( strcmp(a[i], b[i]) != 0 ) {
			return 0;
		}
	}
	return 1;
}

/* helper to free a lengthSplit result */
void freeStringArray(char **a, int pieces) {
	if (!a) return;
	for (int i = 0; i < pieces; i++) free(a[i]);
	free(a);
}

void test_replaceChar() {
	puts("Testing replaceChar (in-place)");
	char a1[] = "banana";
	replaceChar(a1, 'a', 'o');
	printf("  case1: %s -> %s\n", "banana", a1);

	char a2[] = "hello world";
	replaceChar(a2, 'l', 'x');
	printf("  case2: %s -> %s\n", "hello world", a2);

	char a3[] = "no-match";
	replaceChar(a3, 'z', 'q');
	printf("  case3: %s -> %s\n", "no-match", a3);
	puts("");
}

void test_replaceCharCopy() {
	puts("Testing replaceCharCopy (returns new string)");
	const char *s1 = "banana";
	char *r1 = replaceCharCopy(s1, 'a', 'o');
	printf("  case1: %s -> %s\n", s1, r1);
	free(r1);

	const char *s2 = "abcabc";
	char *r2 = replaceCharCopy(s2, 'b', 'B');
	printf("  case2: %s -> %s\n", s2, r2);
	free(r2);

	const char *s3 = "edge";
	char *r3 = replaceCharCopy(s3, 'x', 'y');
	printf("  case3: %s -> %s\n", s3, r3);
	free(r3);
	puts("");
}

void test_removeChar() {
	puts("Testing removeChar (in-place)");
	char b1[] = "mississippi";
	removeChar(b1, 's');
	printf("  case1: %s -> %s\n", "mississippi", b1);

	char b2[] = "aaaa";
	removeChar(b2, 'a');
	printf("  case2: %s -> %s\n", "aaaa", b2);

	char b3[] = "keep";
	removeChar(b3, 'z');
	printf("  case3: %s -> %s\n", "keep", b3);
	puts("");
}

void test_removeCharCopy() {
	puts("Testing removeCharCopy (returns new string)");
	const char *s1 = "mississippi";
	char *c1 = removeCharCopy(s1, 's');
	printf("  case1: %s -> %s\n", s1, c1);
	free(c1);

	const char *s2 = "hello";
	char *c2 = removeCharCopy(s2, 'l');
	printf("  case2: %s -> %s\n", s2, c2);
	free(c2);

	const char *s3 = "none";
	char *c3 = removeCharCopy(s3, 'x');
	printf("  case3: %s -> %s\n", s3, c3);
	free(c3);
	puts("");
}

void test_lengthSplit() {
	puts("Testing lengthSplit (length-based split)");
	const char *src = "Hello World, how are you?";
	int n = 3;
	char **split = lengthSplit(src, n);
	int pieces = (int)((strlen(src) + n - 1) / n);
	char *expected_arr[] = {"Hel","lo ","Wor","ld,"," ho","w a","re ","you","?"};
	int eq = stringArraysEqual(split, expected_arr, pieces);
	printf("  case1: %s split by %d -> %s\n", src, n, eq ? "PASS" : "FAIL");
	freeStringArray(split, pieces);

	const char *s2 = "I like turtles";
	int n2 = 4;
	char **sp2 = lengthSplit(s2, n2);
	int p2 = (int)((strlen(s2) + n2 - 1) / n2);
	char *exp2[] = {"I li","ke t","urtl","es"};
	printf("  case2: %s split by %d -> %s\n", s2, n2, stringArraysEqual(sp2, exp2, p2) ? "PASS" : "FAIL");
	freeStringArray(sp2, p2);

	const char *s3 = "abcde";
	int n3 = 2;
	char **sp3 = lengthSplit(s3, n3);
	int p3 = (int)((strlen(s3) + n3 - 1) / n3);
	char *exp3[] = {"ab","cd","e"};
	printf("  case3: %s split by %d -> %s\n", s3, n3, stringArraysEqual(sp3, exp3, p3) ? "PASS" : "FAIL");
	freeStringArray(sp3, p3);
	puts("");
}

int main(void) {
	puts("--- Hack09 string utilities tester ---");
	test_replaceChar();
	test_replaceCharCopy();
	test_removeChar();
	test_removeCharCopy();
	test_lengthSplit();
	puts("All tests complete (visual verification).\nNote: returned memory was freed where appropriate.");
	return 0;
}

