/**
 * Author: Anthony Candelas
 * Date: 27OCT2025
 * Email: tsallinger2@unl.edu
 *
 * Description: Player input functions for tic-tac-toe.
 */

#ifndef PLAYER_UTILS_H
#define PLAYER_UTILS_H

#include "game_utils.h"

/**
 * Prompts the (human) player for a valid move and
 * updates the game board.  Which player (X or O)
 * is indicated by the given player.
 *
 * @param board board to modify (3x3)
 * @param player Move indicating X or O
 */
void userMove(Move **board, Move player);

#endif /* PLAYER_UTILS_H */