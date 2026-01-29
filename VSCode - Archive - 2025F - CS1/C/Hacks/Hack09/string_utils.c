/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack09 - String Utilities
 *
 * Description:
 *   This file contains the actual implementations of the string
 *   utilities used in Hack09. The functions here perform simple
 *   operations such as replacing characters, removing characters,
 *   and splitting a string into fixed-length pieces. Helper code that
 *   needs these functions should include `string_utils.h`.
 */

#include "string_utils.h"
#include <stdlib.h>
#include <string.h>

void replaceChar(char *s, char oldChar, char newChar) {
	if (s == NULL) return;
	for (size_t i = 0; s[i] != '\0'; i++) {
		if (s[i] == oldChar) s[i] = newChar;
	}
}

char *replaceCharCopy(const char *s, char oldChar, char newChar) {
	if (s == NULL) return NULL;
	size_t len = strlen(s);
	char *out = (char *)malloc(len + 1);
	if (!out) return NULL;
	for (size_t i = 0; i <= len; i++) {
		char c = s[i];
		out[i] = (c == oldChar) ? newChar : c;
	}
	return out;
}

void removeChar(char *s, char c) {
	if (s == NULL) return;
	size_t write = 0;
	for (size_t read = 0; s[read] != '\0'; read++) {
		if (s[read] != c) {
			s[write++] = s[read];
		}
	}
	s[write] = '\0';
}

char *removeCharCopy(const char *s, char c) {
	if (s == NULL) return NULL;
	size_t len = strlen(s);
	size_t keep = 0;
	for (size_t i = 0; i < len; i++) if (s[i] != c) keep++;
	char *out = (char *)malloc(keep + 1);
	if (!out) return NULL;
	size_t j = 0;
	for (size_t i = 0; i < len; i++) {
		if (s[i] != c) out[j++] = s[i];
	}
	out[j] = '\0';
	return out;
}

char **lengthSplit(const char *s, int n) {
	if (s == NULL || n <= 0) return NULL;
	size_t len = strlen(s);
	if (len == 0) return NULL;
	size_t pieces = (len + (size_t)n - 1) / (size_t)n;
	char **out = (char **)malloc(sizeof(char *) * pieces);
	if (!out) return NULL;
	for (size_t i = 0; i < pieces; i++) {
		size_t start = i * (size_t)n;
		size_t remain = (start < len) ? (len - start) : 0;
		size_t piece_len = (remain >= (size_t)n) ? (size_t)n : remain;
		out[i] = (char *)malloc(piece_len + 1);
		if (!out[i]) {
			for (size_t k = 0; k < i; k++) free(out[k]);
			free(out);
			return NULL;
		}
		if (piece_len > 0) memcpy(out[i], s + start, piece_len);
		out[i][piece_len] = '\0';
	}
	return out;
}


