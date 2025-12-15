/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 09Dec2025
 * Lab/Task: Lab14 - Kaprekar numbers (C)
 *
 * Description:
 * Header for Kaprekar utilities exposing the isKaprekar prototype.
 */

#include <stdbool.h>

/**
 * Tests whether the given input n is a Kaprekar number in base-10.
 * A Kaprekar number is a non-negative integer whose square can be split
 * into two positive integers that sum to the original number.
 */
bool isKaprekar(int n);
