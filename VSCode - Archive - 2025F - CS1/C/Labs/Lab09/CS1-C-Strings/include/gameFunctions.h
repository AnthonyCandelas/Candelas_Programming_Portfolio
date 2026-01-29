/**
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 28OCT2025
 * Lab: Lab09
 * Description: Function prototypes for Lab09 (CS1 C-Strings) helper routines.
 */

#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

/**
 * Description: Initialize a blank guessing string of given length.
 *              Sets the first `length` characters of `dest` to '_' and
 *              null-terminates the string.
 *
 * Parameters:
 *  - length: number of characters (not including the null terminator)
 *  - dest: character array to populate (must be large enough)
 *
 * Returns: void
 */
void initializeBlankString(int length, char dest[]);

/**
 * Description: Print a string's characters separated by spaces, followed by a newline.
 *
 * Parameters:
 *  - s: input string to print
 *
 * Returns: void
 */
void printWithSpaces(const char s[]);

int revealGuessedLetter(const char solution[], char revealed[], char guess);

int checkGuess(const char a[], const char b[]);

/**
 * Sets the game up and runs the main loop for a single word.
 *
 * Parameters:
 *  - wordToGuess: the target word to be guessed (null-terminated)
 */
void startGame(char *wordToGuess);

/** Clear the terminal screen (UNIX-like terminals). */
void clearScreen(void);

/** Draw part of the horse based on guessedSoFar / allowedGuesses ratio. */
void drawHorse(int guessedSoFar, int allowedGuesses);

#endif /* GAMEFUNCTIONS_H */
