/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 09Dec2025
 * Lab/Task: Lab14 - Kaprekar numbers (C)
 *
 * Description:
 * Utility function to determine if an integer is a Kaprekar number
 * by splitting its square into two parts that sum to the original.
 */
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "kaprekar_utils.h"

bool isKaprekar(int n) {

  if(n < 1) {
    return false;
  }

  int i;
  long square = n * (long) n;
  int numDigits = (int) log10(square) + 1;
  long modulus = 1;
  long first, second;

  for(i=1; i<=numDigits; i++) {
    modulus *= 10;

    first = square / modulus;
    second = square % modulus;

    if(n == first + second && second > 0) {
      return true;
    }
  }
  return false;

}
