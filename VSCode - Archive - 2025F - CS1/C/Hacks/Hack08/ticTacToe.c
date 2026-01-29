/**
 * Author: Anthony Candelas
 * Date: 27OCT2025
 * Email: tsallinger2@unl.edu
 *
 * Description: Main game loop for tic-tac-toe. Uses game utilities
 *              and player/computer move implementations.
 *
 * NOTE: One starter bug was fixed here — the O move was previously invoked
 *       with an incorrect literal value; the code now passes `O` to userMove.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "game_utils.h"
#include "player_utils.h"
#include "computer_player_utils.h"

/* NOTE: The starter code called userMove with a literal 0; this has been fixed
 *       so the correct `O` move is used for the second player.
 */

int main(int argc, char **argv) {

  srandom(time(NULL));

  int gameChoice = mainMenu();
  Move **board = newBoard();
  if (board == NULL) {
    fprintf(stderr, "Failed to allocate game board.\n");
    return 1;
  }

  Status s = getStatus(board);

  while (s == PLAYING) {

    /* X moves */
    printBoard(board);
    userMove(board, X);
    s = getStatus(board);
    if (s != PLAYING) {
      break;
    }

    /* O moves */
    printBoard(board);
    if (gameChoice == TWO_PLAYER) {
      /* pass O, not 0 */
      userMove(board, O);
    } else if (gameChoice == ONE_PLAYER_RANDOM) {
      randomComputerMove(board);
    } else if (gameChoice == ONE_PLAYER_SMART) {
      smartComputerMove(board);
    }
    s = getStatus(board);

  }

  printf("Final Board:\n");
  printBoard(board);
  freeBoard(board);

  if (s == O_WINS) {
    printf("O Wins!\n");
  } else if (s == X_WINS) {
    printf("X Wins!\n");
  } else if (s == TIE) {
    printf("Cats game, please play again!\n");
  }

  return 0;
}