#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "game_utils.h"
#include "player_utils.h"

/**
 * Author: Anthony Candelas
 * Date: 27OCT2025
 * Email: tsallinger2@unl.edu
 *
 * Description: Prompt the human player to select a move (1-9) and update the board.
 * NOTE: This implementation keeps prompting until a valid, unused square is chosen.
 * NOTE: Fixed index calculation from starter code.
 */

/*
 * Description: Prompt the (human) player for a valid move and update the board.
 * NOTE: Reads an integer 1-9, validates range and whether the cell is empty, and
 *       re-prompts on invalid input. Uses flushInput() to clear leftover stdin.
 */
void userMove(Move **board, Move player) {
  if (board == NULL) return;

  int input = 0;
  while (1) {
    printf("Please enter a choice (1-9): ");
    if (scanf("%d", &input) != 1) {
      flushInput();
      printf("Error: invalid input, try again.\n");
      continue;
    }
    flushInput();
    if (input < 1 || input > 9) {
      printf("Error: input is out of range, try again.\n");
      continue;
    }
    int row = (input - 1) / 3;
    int col = (input - 1) % 3;
    if (board[row][col] != NONE) {
      printf("Error: that choice was already made.\n");
      continue;
    }
    /* set the move and return */
    board[row][col] = player;
    return;
  }
}