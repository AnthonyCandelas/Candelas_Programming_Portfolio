# Windows placeholder Makefile
# This project uses `build_windows.ps1` on Windows and `Makefile.posix` on POSIX systems.
all:
	@echo "On Windows, run build_windows.ps1 instead."

clean:
	@echo "Run build_windows.ps1 -Clean or remove files manually on Windows."
# POSIX Makefile for compiling Hack11
CC=gcc
CFLAGS=-std=c11 -Wall -Wextra
LDLIBS=-lm

SRC=airport.c airportTester.c
OBJ=$(SRC:.c=.o)

all: airportTester

airportTester: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f airportTester $(OBJ)
