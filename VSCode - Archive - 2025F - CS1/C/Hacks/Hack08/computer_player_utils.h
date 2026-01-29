/**
 * Makes a random move on the given board
 * The computer player is always assumed to be O
 */
#ifndef COMPUTER_PLAYER_UTILS_H
#define COMPUTER_PLAYER_UTILS_H

#include "game_utils.h" /* for Move, Status, and board helpers */

void randomComputerMove(Move **board);

/**
 * Given the current board along with who plays next
 * (X or O), determines the number of "winning" combinations
 * recursively.  Actually returns the number of wins/ties
 * since as the second player, a computer player can only
 * play to a tie game.
 */
int numWinningCombos(Move **board, Move nextMove);

/**
 * Given the current board, the computer plays the next
 * best (ie least worst) move.
 */
void smartComputerMove(Move **board);

/**
 * Determines the the best row/column combination to play
 * next given the current board.
 */
void findBestMove(Move **board, int *row, int *col);

#endif /* COMPUTER_PLAYER_UTILS_H */
