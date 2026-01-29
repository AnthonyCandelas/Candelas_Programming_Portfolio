# makefile for a horse game
#
# Originally created by Tony Schneider 2012/02/18

CC = gcc
CCFLAGS = -Iinclude -std=c99

all: horse

horse: main.o gameFunctions.o
	$(CC) $(CCFLAGS) obj/main.o obj/gameFunctions.o -o horse -lm

main.o: src/main.c
	@mkdir -p obj
	$(CC) $(CCFLAGS) -c src/main.c -o obj/$@

gameFunctions.o: src/gameFunctions.c include/gameFunctions.h
	@mkdir -p obj
	$(CC) $(CCFLAGS) -c src/gameFunctions.c -o obj/$@

clean:
	rm -rf obj/*o
