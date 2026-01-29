/**
 * Author: Anthony Candelas
 * Date: 27OCT2025
 * Email: tsallinger2@unl.edu
 *
 * Description: Prototypes and enums for tic-tac-toe game utilities.
 *              Header uses include-guards and doc-style comments.
 */

#ifndef GAME_UTILS_H
#define GAME_UTILS_H

/**
 * Game modes supported by the tic-tac-toe program.
 */
typedef enum {
  TWO_PLAYER        = 1,
  ONE_PLAYER_RANDOM = 2,
  ONE_PLAYER_SMART  = 3,
  ZERO_PLAYER       = 4,
} GameMode;

/**
 * Represents a board cell move.
 */
typedef enum {
  NONE,
  O,
  X,
} Move;

/**
 * Current game status.
 */
typedef enum {
  PLAYING,
  O_WINS,
  X_WINS,
  TIE,
} Status;

/**
 * Create a new tic-tac-toe board with all entries initialized
 * to NONE.
 *
 * @return newly allocated (3x3) board. Caller takes ownership and must free.
 */
Move ** newBoard();

/**
 * Creates a deep copy of the given tic-tac-toe board.
 *
 * @param board existing board (3x3). If NULL, returns NULL.
 * @return new deep copy or NULL on error.
 */
Move ** copyBoard(Move **board);

/**
 * Frees up the given board (and its rows). Safe to call with NULL.
 *
 * @param board board previously returned by newBoard() or copyBoard()
 */
void freeBoard(Move **board);

/**
 * Prints the given game board to stdout. If board is NULL, prints nothing.
 *
 * @param board board to print.
 */
void printBoard(Move **board);

/**
 * Prompts the user to choose a game mode and returns their choice.
 * If the choice is invalid the program exits (behavior matches starter code).
 *
 * @return selected GameMode
 */
GameMode mainMenu();

/**
 * Determines the status of the given board: PLAYING, O_WINS, X_WINS, or TIE.
 *
 * @param board a 3x3 board (rows must be non-NULL).
 * @return Status
 */
Status getStatus(Move **board);

#endif /* GAME_UTILS_H */