/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 18NOV2025
 * Lab/Task: Lab12 - Palindrome
 *
 * Description:
 * Recursive palindrome checker. The recursive function ignores
 * non-alphanumeric characters and is case-insensitive so phrases
 * such as "rats live on no evil star" are recognized as palindromes.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * This function returns 1 if the given (sub)string is a palindrome.
 * It is recursive and ignores non-alphanumeric characters, comparing
 * letters case-insensitively.
 */
int isPalindrome(const char *str, int leftIndex, int rightIndex);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: isPalindrome word\n");
    return 1;
  }

  int isPal = isPalindrome(argv[1], 0, (int)strlen(argv[1]) - 1);
  if (isPal) {
    printf("is a palindrome!\n");
  } else {
    printf("is NOT a palindrome!\n");
  }
  return 0;
}

int isPalindrome(const char *str, int leftIndex, int rightIndex) {
  while (leftIndex < rightIndex && !isalnum((unsigned char)str[leftIndex])) leftIndex++;
  while (leftIndex < rightIndex && !isalnum((unsigned char)str[rightIndex])) rightIndex--;

  if (leftIndex >= rightIndex) return 1;

  char a = tolower((unsigned char)str[leftIndex]);
  char b = tolower((unsigned char)str[rightIndex]);
  if (a != b) return 0;
  return isPalindrome(str, leftIndex + 1, rightIndex - 1);
}
