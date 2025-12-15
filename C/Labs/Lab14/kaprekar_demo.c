/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 09Dec2025
 * Lab/Task: Lab14 - Kaprekar numbers (C)
 *
 * Description:
 * Simple demo program that tests if a given number is a Kaprekar number.
 */
#include <stdlib.h>
#include <stdio.h>

#include "kaprekar_utils.h"

int main(int argc, char **argv) {

  if(argc != 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    exit(1);
  }

  int n = atoi(argv[1]);

  if(isKaprekar(n)) {
    printf("%d is a Kaprekar Number!\n", n);
  } else {
    printf("%d is not a Kaprekar Number!\n", n);
  }

  return 0;
}
