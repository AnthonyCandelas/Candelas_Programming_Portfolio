#include <stdio.h>
#include <math.h>
#include <string.h>

#include "gameFunctions.h"

/**
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 28OCT2025
 * Lab: Lab09
 * Description: Implementations of helper functions for the Lab09 hangman game.
 */

void initializeBlankString(int length, char dest[]) {
  int i;
  for (i = 0; i < length; i++)
    dest[i] = '_';
  dest[length] = '\0';
}

void printWithSpaces(const char s[]) {
  size_t i, n = strlen(s);
  for (i = 0; i < n; i++)
    printf("%c ", s[i]);
  printf("\n");
}

int revealGuessedLetter(const char solution[], char revealed[], char guess) {
  int changed = 0;
  size_t i, n = strlen(solution);
  for (i = 0; i < n; i++) {
    if (solution[i] == guess && revealed[i] != guess) {
      revealed[i] = guess;
      changed = 1;
    }
  }
  return changed;
}

int checkGuess(const char a[], const char b[]) { return strcmp(a, b) == 0 ? 1 : 0; }

void startGame(char word[25]) {
  int won = 0;
  int numBadGuesses = 0;
  int possibleBadGuesses;
  int charRevealed;
  char guess;
  char revealedLetters[25];

  initializeBlankString(strlen(word), revealedLetters);
  clearScreen();

  printf("Please enter the total number of incorrect guesses you would like to be able to make: ");
  scanf("%d", &possibleBadGuesses);
  printWithSpaces(revealedLetters);

  while (numBadGuesses <= possibleBadGuesses && !won) {
    printf("Enter a letter to guess: ");
    scanf(" %c", &guess);

  charRevealed = revealGuessedLetter(word, revealedLetters, guess);
    won = checkGuess(word, revealedLetters);

    if (!charRevealed) {
      numBadGuesses++;
    }

    drawHorse(numBadGuesses, possibleBadGuesses);
    printWithSpaces(revealedLetters);
  }

  if (won) {
    printf("Congratulations!  You correctly guessed the word %s\n", word);
  } else {
    printf("You've run out of guesses.  The correct word was %s\n", word);
  }
}

/**
 * drawHorse: Print a portion of a horse ASCII-art based on the ratio of
 *            guessedSoFar to allowedGuesses.
 */
void drawHorse(int guessedSoFar, int allowedGuesses) {
  const char *horsey[29] = {"   Y8baadP\"\"\"\"\"\"\"\"Yba,_",
                      "aaadP\"'             `\"\"Yb,",
                      "`Y8(                    `\"Yb,",
                      "  `Y,                      `Yba,",
                      "    Y,  (O)                   `Yba,",
                      "    `Y,                          \"\"Yba,________,,aaddddbbbaa,,____,aa,_",
                      "     `Y,       ,aa                   `\"\"\"\"\"\"\"\"\"\"''          ``\"\"\"\"''  \"Y,",
                      "       Y,      d'8                                                \"Ya   `Y,",
                      "       `b      8 8                                                  `Y,   Y,",
                      "        Ya o  ,8 8                                                    b   `b",
                      "         Yb,_,dP 8                                                    Y    8",
                      "          `\"\"\"\"  Y                                                    8    8",
                      "                 I,                                                   8    8",
                      "                 `b                                                   P    [",
                      "                  `b                                                 d'    [",
                      "                   d                                                ,P     [",
                      "                 ,d'    ,PY,         ,P\"YaaaaaaP\"Ybaaa,,_           d'     [",
                      "                d\"    ,P\"  Y,        d'           8'  `\"\"db,       d'      8",
                      "               d'   ,P\"    `Y,       8            I,     d'\"b,     8a      P",
                      "              d(    (       `Y,      P            `b    ,P  `Y,    8`Ya___d'",
                      "              \"Y,   \"b,      `Y,    ,I             8    d'   `8    8  `\"\"\"'",
                      "                \"Y,   \"b,  __ `8,   d'            ,8   ,P     8    8",
                      "                  \"Y,   \"bd88b `b   8             I'   d'     Y,   8",
                      "                    \"Y,    888b 8   8             8   ,P      `b   8",
                      "                      \"Ya,,d888b8   P            d'  ,P'       8   Y,",
                      "                         `\"\"\"\",d\"  ,I        ,adPb__aP'        Y   `b",
                      "                           ,a8P,__aP'       d888888P'         ,d    8",
                      "                          d8888888'         88888888       ,d888bbaaP",
                      "                          88888888                         88888888'"};

  clearScreen();

  /* Determine how much of the horse to print and print it. */
  double ratio = (double)guessedSoFar / (double)allowedGuesses;
  int linesToDraw = floor(ratio * 28);
  linesToDraw = linesToDraw <= 29 ? linesToDraw : 29;

  int i;
  for (i = 29 - linesToDraw; i < 29; i++) {
    printf("%s\n", horsey[i]);
  }
}

/** Clear the terminal screen (ANSI sequences used for UNIX-like terminals). */
void clearScreen(void) {
  printf("\033[2J");
  printf("\033[0;0f");
  printf("\n");
}
