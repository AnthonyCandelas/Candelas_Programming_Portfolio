#
# Author: Anthony Candelas
# Date: 27OCT2025
# Email: tsallinger2@unl.edu
#
# Description:
# Makefile for the tic-tac-toe project. Builds executables and object files.
# Use "make" to build and "make clean" to remove artifacts.
#

CC = gcc
FLAGS = -Wall -std=gnu99 -g
INCLUDES =

.PHONY: all clean run

all: ticTacToe

ticTacToe: utils.o game_utils.o player_utils.o computer_player_utils.o ticTacToe.c
	$(CC) $(FLAGS) utils.o game_utils.o player_utils.o computer_player_utils.o ticTacToe.c -o ticTacToe $(INCLUDES)

game_utils.o: game_utils.c game_utils.h
	$(CC) $(FLAGS) -c game_utils.c -o game_utils.o $(INCLUDES)

player_utils.o: player_utils.c player_utils.h
	$(CC) $(FLAGS) -c player_utils.c -o player_utils.o $(INCLUDES)

computer_player_utils.o: computer_player_utils.c computer_player_utils.h
	$(CC) $(FLAGS) -c computer_player_utils.c -o computer_player_utils.o $(INCLUDES)

utils.o: utils.c utils.h
	$(CC) $(FLAGS) -c utils.c -o utils.o $(INCLUDES)

clean:
	rm -Rf *~ *.o ticTacToe.dSYM ticTacToe

run: ticTacToe
	./ticTacToe