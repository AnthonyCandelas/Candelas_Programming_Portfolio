#include <stdlib.h>
#include <stdio.h>

#include "game_utils.h"
#include "utils.h"

/**
 * Author: Anthony Candelas
 * Date: 27OCT2025
 * Email: tsallinger2@unl.edu
 *
 * Description: Implementations for board creation, copying, printing,
 *              freeing, and status checks for the tic-tac-toe board.
 *
 * NOTE: This file includes small bug fixes applied to the starter code:
 *  - `copyBoard` now returns a true deep copy (not the original pointer).
 *  - `getStatus` index checks and PLAYING detection were corrected.
 *  - `freeBoard` now guards against NULL row pointers before freeing.
 */

/*
 * Description: Free the board and its rows.
 * NOTE: Safe to call with `board == NULL`.
 */
void freeBoard(Move **board) {
  if (board == NULL) return;
  for (int i = 0; i < 3; i++) {
    if (board[i] != NULL) {
      free(board[i]);
    }
  }
  free(board);
  return;
}

/*
 * Description: Create a deep copy of the board.
 * NOTE: Returns NULL if memory cannot be allocated or if input is NULL.
 */
Move ** copyBoard(Move **board) {
  if (board == NULL) return NULL;
  Move **copy = newBoard();
  if (copy == NULL) return NULL;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      copy[i][j] = board[i][j];
    }
  }
  return copy;
}

/*
 * Description: Allocate and initialize a new (3x3) board with all cells == NONE.
 * NOTE: Caller takes ownership and must call freeBoard when done.
 */
Move ** newBoard() {
  Move **board = (Move **) malloc(3 * sizeof(Move *));
  if (board == NULL) return NULL;
  for (int i = 0; i < 3; i++) {
    board[i] = (Move *) malloc(3 * sizeof(Move));
    if (board[i] == NULL) {
      /* clean up previously allocated rows on failure */
      for (int k = 0; k < i; k++) free(board[k]);
      free(board);
      return NULL;
    }
    for (int j = 0; j < 3; j++) {
      board[i][j] = NONE;
    }
  }
  return board;
}

/*
 * Description: Print the board to stdout in a clear, human-readable layout.
 * NOTE: If `board` is NULL nothing is printed.
 */
void printBoard(Move **board) {
  if (board == NULL) return;

  printf("\n");
  for (int i = 0; i < 3; i++) {
    printf("  ");
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == X) {
        printf("  X  ");
      } else if (board[i][j] == O) {
        printf("  O  ");
      } else {
        printf(" (%d) ", (i*3 + j + 1));
      }
      if (j < 2) {
        printf(" | ");
      }
    }
    printf("\n");
    if (i < 2) {
      printf("  ------+-------+------\n");
    }
  }
  printf("\n");
  return;
}

/*
 * Description: Prompt the user to select a game mode and validate the choice.
 * NOTE: If the user selects an invalid option the program exits (matches starter behavior).
 */
GameMode mainMenu() {

  int choice = 0;
  printf("Welcome to Tic-Tac-Toe!!\n");
  printf("========================\n");
  printf("Menu\n");
  printf("(1) 2-player game\n");
  printf("(2) 1-player game vs random computer\n");
  printf("(3) 1-player game vs smart-ish computer\n");
  scanf("%d", &choice);
  if (choice < 1 || choice > 3) {
    printf("Invalid choice, please play again.\n");
    exit(1);
  }

  return (GameMode)choice;
}

/*
 * Description: Determine the current status of the board: PLAYING, O_WINS, X_WINS, or TIE.
 * NOTE: Small fixes applied to starter logic for correct detection of wins and PLAYING state.
 */
Status getStatus(Move **board) {
  if (board == NULL) return PLAYING; /* defensive */

  /* Check X wins */
  if (
      /* rows */
      (board[0][0] == X && board[0][1] == X && board[0][2] == X) ||
      (board[1][0] == X && board[1][1] == X && board[1][2] == X) ||
      (board[2][0] == X && board[2][1] == X && board[2][2] == X) ||
      /* cols */
      (board[0][0] == X && board[1][0] == X && board[2][0] == X) ||
      (board[0][1] == X && board[1][1] == X && board[2][1] == X) ||
      (board[0][2] == X && board[1][2] == X && board[2][2] == X) ||
      /* diagonals */
      (board[0][0] == X && board[1][1] == X && board[2][2] == X) ||
      (board[0][2] == X && board[1][1] == X && board[2][0] == X)
     ) {
    return X_WINS;
  }

  /* Check O wins */
  if (
      /* rows */
      (board[0][0] == O && board[0][1] == O && board[0][2] == O) ||
      (board[1][0] == O && board[1][1] == O && board[1][2] == O) ||
      (board[2][0] == O && board[2][1] == O && board[2][2] == O) ||
      /* cols */
      (board[0][0] == O && board[1][0] == O && board[2][0] == O) ||
      (board[0][1] == O && board[1][1] == O && board[2][1] == O) ||
      (board[0][2] == O && board[1][2] == O && board[2][2] == O) ||
      /* diagonals */
      (board[0][0] == O && board[1][1] == O && board[2][2] == O) ||
      (board[0][2] == O && board[1][1] == O && board[2][0] == O)
     ) {
    return O_WINS;
  }

  /* If any cell is NONE, the game is still PLAYING */
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == NONE) {
        return PLAYING;
      }
    }
  }

  /* Otherwise it's a tie */
  return TIE;
}